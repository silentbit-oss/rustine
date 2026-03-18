use std::env;
use std::io::{self, Read, Write};
use openaptxrs::{AptxContext, CodecMode, OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH};

// Replicating static buffers using sizing configurations:
// input_buffer size: 512 * 3 bytes * 2 channels * 4 samples = 12,288 bytes
const INPUT_BUFFER_SIZE: usize = 512 * 3 * 2 * 4;
// output_buffer size: 512 * 6 = 3,072 bytes
const OUTPUT_BUFFER_SIZE: usize = 512 * 6;

fn print_help(program_name: &str) {
    eprintln!(
        "aptX encoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
        OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH,
        OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH
    );
    eprintln!();
    eprintln!("This utility encodes raw 24 bit signed stereo");
    eprintln!("samples from stdin to aptX or aptX HD on stdout");
    eprintln!();
    eprintln!("Usage:");
    eprintln!("        {} [options]", program_name);
    eprintln!();
    eprintln!("Options:");
    eprintln!("        -h, --help   Display this help");
    eprintln!("        --hd         Encode to aptX HD");
    eprintln!();
    eprintln!("Examples:");
    eprintln!();
    eprintln!("        {} < sample.s24le > sample.aptx", program_name);
    eprintln!();
    eprintln!("        {} --hd < sample.s24le > sample.aptxhd", program_name);
    eprintln!();
    eprintln!(
        "        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | {} > sample.aptx",
        program_name
    );
}

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let program_name = args.get(0).map(|s| s.as_str()).unwrap_or("aptx_encode");
    
    let mut mode = CodecMode::Standard;

    // Command-line argument parsing
    for arg in args.iter().skip(1) {
        match arg.as_str() {
            "-h" | "--help" => {
                print_help(program_name);
                std::process::exit(1);
            }
            "--hd" => {
                mode = CodecMode::Hd;
            }
            _ => {
                eprintln!("{}: Invalid option {}", program_name, arg);
                std::process::exit(1);
            }
        }
    }

    let mut ctx = AptxContext::new(mode);
    
    // Lock stdin and stdout streams for high performance
    let mut stdin = io::stdin().lock();
    let mut stdout = io::stdout().lock();

    let mut input_buffer = vec![0u8; INPUT_BUFFER_SIZE];
    let mut output_buffer = vec![0u8; OUTPUT_BUFFER_SIZE];
    
    let mut exit_code = 0;

    loop {
        // Read chunks from stdin
        let length = stdin.read(&mut input_buffer)?;
        if length == 0 {
            break; // End of File reached
        }

        // Slice input buffer exactly to the number of read bytes
        let (processed, written) = ctx.encode(&input_buffer[..length], &mut output_buffer);

        if processed != length {
            let dropped = length - processed;
            eprintln!(
                "{}: aptX encoding stopped in the middle of the sample, dropped {} byte{}",
                program_name,
                dropped,
                if dropped != 1 { "s" } else { "" }
            );
            exit_code = 1;
        }

        // Write encoded chunk safely out to stdout
        if written > 0 {
            if let Err(e) = stdout.write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX encoding failed to write encoded data: {}", program_name, e);
                std::process::exit(1);
            }
        }

        if processed != length {
            break;
        }
    }

    // Flush remaining sample latency to match aptX frame requirements
    match ctx.encode_finish(&mut output_buffer) {
        Ok(written) => {
            if written > 0 {
                if let Err(e) = stdout.write_all(&output_buffer[..written]) {
                    eprintln!("{}: aptX encoding failed to write encoded data: {}", program_name, e);
                    exit_code = 1;
                }
            }
        }
        Err(e) => {
            eprintln!("{}: aptX encoding finish failed: {}", program_name, e);
            exit_code = 1;
        }
    }

    // Ensure everything is flushed out to the OS pipeline cleanly
    stdout.flush()?;

    if exit_code != 0 {
        std::process::exit(exit_code);
    }

    Ok(())
}
