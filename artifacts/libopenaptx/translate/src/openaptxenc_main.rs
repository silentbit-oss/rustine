use translate::*;
use std::env;
use std::io::Write;
use std::io::Read;
pub fn main() -> std::io::Result<()> {
    let args: Vec<String> = std::env::args().collect();
    let argc = args.len();
    let mut hd = 0;
    let mut ret = 0;
    let mut length = 0;
    let mut processed = 0;
    let mut written = 0;

    // Process command line arguments
    for i in 1..argc {
        helper_main_2(&mut hd, &args, i)?;
    }

    // Initialize aptX context
    let mut ctx = match aptx_init(hd) {
        Some(ctx) => ctx,
        Option::None => {
            eprintln!("{}: Cannot initialize aptX encoder", args[0]);
            return Ok(());
        }
    };

    // Main processing loop
    while {
        let mut input = [0u8; 1024];
        match std::io::stdin().read(&mut input) {
            Ok(0) => false, // EOF
            Ok(n) => {
                length = n;
                helper_main_1(&mut ret, &mut length, &mut processed, &args, &mut written, &mut ctx)
            }
            Err(e) => {
                eprintln!("{}: Error reading input: {}", args[0], e);
                ret = 1;
                false
            }
        }
    } {}

    // Finalize encoding
    let mut output_buffer = [0u8; (((512 * 3) * 2) * 6) + ((3 * 2) * 4)];
    let output_buffer_len = output_buffer.len();
    if aptx_encode_finish(&mut ctx, &mut output_buffer, output_buffer_len, &mut written) != 0 {
        if std::io::stdout().write_all(&output_buffer[..written]).is_err() {
            eprintln!("{}: aptX encoding failed to write encoded data", args[0]);
            ret = 1;
        }
    }

    aptx_finish(Some(ctx));
    
    if ret != 0 {
        std::process::exit(1);
    }
    Ok(())
}
