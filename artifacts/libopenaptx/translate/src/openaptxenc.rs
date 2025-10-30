use crate::*;
use std::io::Write;
use std::io::Read;
use std::io;


pub fn helper_main_2(hd_ref: &mut i32, argv: &[String], i: usize) -> io::Result<()> {
    let hd = *hd_ref;
    if argv[i] == "-h" || argv[i] == "--help" {
        writeln!(io::stderr(), "aptX encoder utility {}.{}.{} (using libopenaptx {}.{}.{})", 0, 2, 1, APTX_MAJOR, APTX_MINOR, APTX_PATCH)?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "This utility encodes a raw 24 bit signed stereo")?;
        writeln!(io::stderr(), "samples from stdin to aptX or aptX HD on stdout")?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "Usage:")?;
        writeln!(io::stderr(), "        {} [options]", argv[0])?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "Options:")?;
        writeln!(io::stderr(), "        -h, --help   Display this help")?;
        writeln!(io::stderr(), "        --hd         Encode to aptX HD")?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "Examples:")?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "        {} < sample.s24le > sample.aptx", argv[0])?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "        {} --hd < sample.s24le > sample.aptxhd", argv[0])?;
        writeln!(io::stderr())?;
        writeln!(io::stderr(), "        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | {} > sample.aptx", argv[0])?;
        Ok(())
    } else if argv[i] == "--hd" {
        *hd_ref = 1;
        Ok(())
    } else {
        writeln!(io::stderr(), "{}: Invalid option {}", argv[0], argv[i])?;
        Ok(())
    }
}
pub fn helper_main_1(
    ret_ref: &mut i32,
    length_ref: &mut usize,
    processed_ref: &mut usize,
    argv: &[String],
    written: &mut usize,
    ctx: &mut Aptx_Context,
) -> bool {
    let mut ret = *ret_ref;
    let mut length = *length_ref;
    let mut processed = *processed_ref;

    // Read from stdin
    let input_buffer = &mut INPUT_BUFFER.lock().unwrap();
    match io::stdin().read_exact(&mut input_buffer[..length]) {
        Ok(()) => {
            length = input_buffer.len();
        }
        Err(e) if e.kind() == io::ErrorKind::UnexpectedEof => {
            length = 0;
        }
        Err(_) => {
            eprintln!("{}: aptX encoding failed to read input data", argv[0]);
            ret = 1;
            *ret_ref = ret;
            *length_ref = length;
            *processed_ref = processed;
            return false;
        }
    }

    if length == 0 {
        *ret_ref = ret;
        *length_ref = length;
        *processed_ref = processed;
        return false;
    }

    // Process encoding
    let output_buffer = &mut OUTPUT_BUFFER.lock().unwrap();
    processed = aptx_encode(ctx, &input_buffer[..length], &mut output_buffer[..], written);

    if processed != length {
        let dropped = length - processed;
        eprintln!(
            "{}: aptX encoding stopped in the middle of the sample, dropped {} byte{}",
            argv[0],
            dropped,
            if dropped != 1 { "s" } else { "" }
        );
        ret = 1;
    }

    // Write to stdout
    if io::stdout().write_all(&output_buffer[..*written]).is_err() {
        eprintln!("{}: aptX encoding failed to write encoded data", argv[0]);
        ret = 1;
        *ret_ref = ret;
        *length_ref = length;
        *processed_ref = processed;
        return false;
    }

    if processed != length {
        *ret_ref = ret;
        *length_ref = length;
        *processed_ref = processed;
        return false;
    }

    *ret_ref = ret;
    *length_ref = length;
    *processed_ref = processed;
    true
}
