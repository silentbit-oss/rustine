use std::env;
use std::io::{self, Read, Write};
use openaptxrs::{AptxContext, CodecMode, OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH};

// Static sizing calculations matching the C logic
const INPUT_BUFFER_SIZE: usize = 512 * 6;
// 512 * 3 * 2 * 6 + 3 * 2 * 4 = 18,456 bytes
const OUTPUT_BUFFER_SIZE: usize = (512 * 3 * 2 * 6) + (3 * 2 * 4);

fn print_help(program_name: &str) {
    eprintln!(
        "aptX decoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
        OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH,
        OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH
    );
    eprintln!();
    eprintln!("This utility decodes aptX or aptX HD audio stream");
    eprintln!("from stdin to a raw 24 bit signed stereo on stdout");
    eprintln!();
    eprintln!("When input is damaged it tries to synchronize and recover");
    eprintln!();
    eprintln!("Non-zero return value indicates that input was damaged");
    eprintln!("and some bytes from input aptX audio stream were dropped");
    eprintln!();
    eprintln!("Usage:");
    eprintln!("        {} [options]", program_name);
    eprintln!();
    eprintln!("Options:");
    eprintln!("        -h, --help   Display this help");
    eprintln!("        --hd         Decode from aptX HD");
    eprintln!();
    eprintln!("Examples:");
    eprintln!();
    eprintln!("        {} < sample.aptx > sample.s24le", program_name);
    eprintln!();
    eprintln!("        {} --hd < sample.aptxhd > sample.s24le", program_name);
    eprintln!();
    eprintln!(
        "        {} < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -",
        program_name
    );
}

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let program_name = args.get(0).map(|s| s.as_str()).unwrap_or("aptx_decode");

    let mut hd = false;

    // Process CLI arguments
    for arg in args.iter().skip(1) {
        match arg.as_str() {
            "-h" | "--help" => {
                print_help(program_name);
                std::process::exit(1);
            }
            "--hd" => {
                hd = true;
            }
            _ => {
                eprintln!("{}: Invalid option {}", program_name, arg);
                std::process::exit(1);
            }
        }
    }

    let mode = if hd { CodecMode::Hd } else { CodecMode::Standard };
    let mut ctx = AptxContext::new(mode);

    let mut stdin = io::stdin().lock();
    let mut stdout = io::stdout().lock();

    let mut input_buffer = vec![0u8; INPUT_BUFFER_SIZE];
    let mut output_buffer = vec![0u8; OUTPUT_BUFFER_SIZE];

    // Read initial 6 bytes to run codec heuristics detection
    let mut initial_bytes = [0u8; 6];
    let mut length = 0;
    
    // Read up to 6 bytes safely handling early EOF loops
    while length < 6 {
        match stdin.read(&mut initial_bytes[length..]) {
            Ok(0) => break,
            Ok(n) => length += n,
            Err(e) => return Err(e),
        }
    }

    // Try to guess the stream type exactly like the original C logic
    if length >= 4 && &initial_bytes[0..4] == b"\x4b\xbf\x4b\xbf" {
        if hd {
            eprintln!("{}: Input looks like start of aptX audio stream (not aptX HD), try without --hd", program_name);
        }
    } else if length >= 6 && &initial_bytes[0..6] == b"\x73\xbe\xff\x73\xbe\xff" {
        if !hd {
            eprintln!("{}: Input looks like start of aptX HD audio stream, try with --hd", program_name);
        }
    } else if length >= 4 && &initial_bytes[0..4] == b"\x6b\xbf\x6b\xbf" {
        eprintln!("{}: Input looks like start of standard aptX audio stream, which is not supported yet", program_name);
    } else {
        eprintln!("{}: Input does not look like start of aptX nor aptX HD audio stream", program_name);
    }

    // Pre-populate input buffer with the bytes we read for validation
    input_buffer[..length].copy_from_slice(&initial_bytes[..length]);

    let mut ret = 0;
    let mut syncing = false;

    while length > 0 {
        // Run continuous synchronization decoding step
        let result = ctx.decode_sync(&input_buffer[..length], &mut output_buffer);
        let mut written = result.output_written;

        // Process synchronization messaging state machine rules
        if !result.is_synced {
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", program_name);
                syncing = true;
                ret = 1;
            }
            if result.bytes_dropped > 0 {
                eprintln!(
                    "{}: aptX synchronization successful, dropped {} byte{}",
                    program_name,
                    result.bytes_dropped,
                    if result.bytes_dropped != 1 { "s" } else { "" }
                );
                syncing = false;
                ret = 1;
            }
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", program_name);
                syncing = true;
                ret = 1;
            }
        } else if result.bytes_dropped > 0 {
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", program_name);
            }
            eprintln!(
                "{}: aptX synchronization successful, dropped {} byte{}",
                program_name,
                result.bytes_dropped,
                if result.bytes_dropped != 1 { "s" } else { "" }
            );
            syncing = false;
            ret = 1;
        } else if syncing {
            eprintln!("{}: aptX synchronization successful", program_name);
            syncing = false;
            ret = 1;
        }

        // If the implementation breaks step halfway, abort immediately
        if result.input_consumed != length {
            eprintln!("{}: aptX decoding failed", program_name);
            ret = 1;
            break;
        }

        // Read the next block sequence from stdin stream
        match stdin.read(&mut input_buffer) {
            Ok(0) => length = 0, // EOF reached cleanly
            Ok(n) => length = n,
            Err(e) => {
                eprintln!("{}: aptX decoding failed to read input data: {}", program_name, e);
                ret = 1;
                length = 0;
            }
        }

        // Drop padding samples at final trailing audio boundary alignment (6 * 2 = 12 bytes)
        if length == 0 && written >= 12 {
            written -= 12;
        }

        if written > 0 {
            if let Err(e) = stdout.write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX decoding failed to write decoded data: {}", program_name, e);
                ret = 1;
                break;
            }
        }
    }

    // Wrap up residual trailing context buffers safely
    let final_dropped = ctx.decode_sync_finish();
    if final_dropped > 0 && !syncing {
        eprintln!(
            "{}: aptX decoding stopped in the middle of the sample, dropped {} byte{}",
            program_name,
            final_dropped,
            if final_dropped != 1 { "s" } else { "" }
        );
        ret = 1;
    } else if syncing {
        eprintln!("{}: aptX synchronization failed", program_name);
        ret = 1;
    }

    stdout.flush()?;

    if ret != 0 {
        std::process::exit(ret);
    }
    Ok(())
}
