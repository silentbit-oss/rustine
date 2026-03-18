use translate_new::*;
use std::env;
use std::io;
use std::process;
use std::io::Read;
use std::io::Write;
pub fn main() -> io::Result<()> {
	println!("* main");
    let args: Vec<String> = std::env::args().collect();
    let mut hd = false;
    let mut ret = 0;

    for arg in args.iter().skip(1) {
        if arg == "-h" || arg == "--help" {
            eprintln!("aptX encoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
                APTX_MAJOR, APTX_MINOR, APTX_PATCH,
                APTX_MAJOR, APTX_MINOR, APTX_PATCH);
            eprintln!();
            eprintln!("This utility encodes a raw 24 bit signed stereo");
            eprintln!("samples from stdin to aptX or aptX HD on stdout");
            eprintln!();
            eprintln!("Usage:");
            eprintln!("        {} [options]", args[0]);
            eprintln!();
            eprintln!("Options:");
            eprintln!("        -h, --help   Display this help");
            eprintln!("        --hd         Encode to aptX HD");
            eprintln!();
            eprintln!("Examples:");
            eprintln!();
            eprintln!("        {} < sample.s24le > sample.aptx", args[0]);
            eprintln!();
            eprintln!("        {} --hd < sample.s24le > sample.aptxhd", args[0]);
            eprintln!();
            eprintln!("        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | {} > sample.aptx", args[0]);
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
            eprintln!("{}: Cannot initialize aptX encoder", args[0]);
            process::exit(1);
        }
    };

    loop {
        let mut input_buffer = INPUT_BUFFER.lock().unwrap();
        let length = match io::stdin().read(&mut *input_buffer) {
            Ok(0) => break,
            Ok(len) => len,
            Err(e) => {
                eprintln!("{}: aptX encoding failed to read input data: {}", args[0], e);
                ret = 1;
                break;
            }
        };

        let mut output_buffer = OUTPUT_BUFFER.lock().unwrap();
        let mut written = 0;
        let processed = aptx_encode(&mut ctx, &input_buffer[..length], &mut *output_buffer, &mut written);

        if processed != length {
            eprintln!(
                "{}: aptX encoding stopped in the middle of the sample, dropped {} byte{}",
                args[0],
                length - processed,
                if (length - processed) != 1 { "s" } else { "" }
            );
            ret = 1;
        }

        if io::stdout().write_all(&output_buffer[..written]).is_err() {
            eprintln!("{}: aptX encoding failed to write encoded data", args[0]);
            ret = 1;
            break;
        }

        if processed != length {
            break;
        }
    }

    let mut output_buffer = OUTPUT_BUFFER.lock().unwrap();
    let output_len = output_buffer.len();
    let mut written = 0;
    if aptx_encode_finish(&mut ctx, &mut *output_buffer, output_len, &mut written) != 0 {
        if io::stdout().write_all(&output_buffer[..written]).is_err() {
            eprintln!("{}: aptX encoding failed to write encoded data", args[0]);
            ret = 1;
        }
    }

    aptx_finish(Some(ctx));
    process::exit(ret);
}
