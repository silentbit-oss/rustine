use translate_new::*;
use std::env;
use std::process;
use std::io::Read;
use std::io::Write;
use std::io;
use std::ffi::CStr;
use lazy_static::lazy_static;

pub fn main() -> io::Result<()> {
	println!("* main");
    let args: Vec<String> = std::env::args().collect();
    let mut hd = false;
    let mut ret = 0;
    
    // Parse command line arguments
    for arg in args.iter().skip(1) {
        if arg == "-h" || arg == "--help" {
            eprintln!("aptX decoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
                APTX_MAJOR, APTX_MINOR, APTX_PATCH,
                APTX_MAJOR, APTX_MINOR, APTX_PATCH);
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
            eprintln!("        {} [options]", args[0]);
            eprintln!();
            eprintln!("Options:");
            eprintln!("        -h, --help   Display this help");
            eprintln!("        --hd         Decode from aptX HD");
            eprintln!();
            eprintln!("Examples:");
            eprintln!();
            eprintln!("        {} < sample.aptx > sample.s24le", args[0]);
            eprintln!();
            eprintln!("        {} --hd < sample.aptxhd > sample.s24le", args[0]);
            eprintln!();
            eprintln!("        {} < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -", args[0]);
            process::exit(1);
        } else if arg == "--hd" {
            hd = true;
        } else {
            eprintln!("{}: Invalid option {}", args[0], arg);
            process::exit(1);
        }
    }

    let mut ctx = match aptx_init(hd) {
        Some(ctx) => ctx,
        None => {
            eprintln!("{}: Cannot initialize aptX decoder", args[0]);
            process::exit(1);
        }
    };

    let mut input_buffer = INPUT_BUFFER.lock().unwrap();
    let mut output_buffer = OUTPUT_BUFFER.lock().unwrap();
    
    let mut length = io::stdin().read(&mut input_buffer[..6])?;
    
    // Check for aptX/aptX HD signatures
    if length >= 4 && &input_buffer[..4] == b"\x4b\xbf\x4b\xbf" {
        if hd {
            eprintln!("{}: Input looks like start of aptX audio stream (not aptX HD), try without --hd", args[0]);
        }
    } else if length >= 6 && &input_buffer[..6] == b"\x73\xbe\xff\x73\xbe\xff" {
        if !hd {
            eprintln!("{}: Input looks like start of aptX HD audio stream, try with --hd", args[0]);
        }
    } else {
        if length >= 4 && &input_buffer[..4] == b"\x6b\xbf\x6b\xbf" {
            eprintln!("{}: Input looks like start of standard aptX audio stream, which is not supported yet", args[0]);
        } else {
            eprintln!("{}: Input does not look like start of aptX nor aptX HD audio stream", args[0]);
        }
    }

    let mut syncing = false;
    let mut synced = 0;
    let mut written = 0;
    let mut dropped = 0;

    while length > 0 {
        let processed = aptx_decode_sync(
            &mut ctx,
            &input_buffer[..length],
            &mut output_buffer[..],
            &mut written,
            &mut synced,
            &mut dropped,
        );

        if synced == 0 {
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", args[0]);
                syncing = true;
                ret = 1;
            }
            if dropped > 0 {
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}",
                    args[0], dropped, if dropped != 1 { "s" } else { "" });
                syncing = false;
                ret = 1;
            }
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", args[0]);
                syncing = true;
                ret = 1;
            }
        } else {
            if dropped > 0 {
                if !syncing {
                    eprintln!("{}: aptX decoding failed, synchronizing", args[0]);
                }
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}",
                    args[0], dropped, if dropped != 1 { "s" } else { "" });
                syncing = false;
                ret = 1;
            } else if syncing {
                eprintln!("{}: aptX synchronization successful", args[0]);
                syncing = false;
                ret = 1;
            }
        }

        if processed != length {
            eprintln!("{}: aptX decoding failed", args[0]);
            ret = 1;
            break;
        }

        length = match io::stdin().read(&mut input_buffer[..]) {
            Ok(0) => 0,
            Ok(n) => n,
            Err(e) => {
                eprintln!("{}: aptX decoding failed to read input data: {}", args[0], e);
                ret = 1;
                0
            }
        };

        if length == 0 && written >= 6 * 2 {
            written -= 6 * 2;
        }

        if written > 0 {
            if let Err(e) = io::stdout().write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX decoding failed to write decoded data: {}", args[0], e);
                ret = 1;
                break;
            }
        }
    }

    dropped = aptx_decode_sync_finish(&mut ctx);
    if dropped > 0 && !syncing {
        eprintln!("{}: aptX decoding stopped in the middle of the sample, dropped {} byte{}",
            args[0], dropped, if dropped != 1 { "s" } else { "" });
        ret = 1;
    } else if syncing {
        eprintln!("{}: aptX synchronization failed", args[0]);
        ret = 1;
    }

    aptx_finish(Some(ctx));
    process::exit(ret);
}
