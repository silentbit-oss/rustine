/*
 * aptX encoder utility
 * Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
 * Rust translation (C) 2026
 *
 * Read README file for license details.  Due to license abuse
 * this program must not be used in any Freedesktop project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

use std::env;
use std::io::{self, Read, Write};
use std::process;

use libopenaptx::{
    OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH,
    aptx_major, aptx_minor, aptx_patch,
    aptx_init, aptx_finish, aptx_encode, aptx_encode_finish,
};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = env::args().collect();
    let program_name = args.get(0).map(|s| s.as_str()).unwrap_or("openaptxenc");

    let mut hd = 0;

    // Parse command line arguments
    for i in 1..args.len() {
        if args[i] == "-h" || args[i] == "--help" {
            eprintln!("aptX encoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
                     OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH,
                     aptx_major, aptx_minor, aptx_patch);
            eprintln!();
            eprintln!("This utility encodes a raw 24 bit signed stereo");
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
            eprintln!("        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | {} > sample.aptx", program_name);
            process::exit(1);
        } else if args[i] == "--hd" {
            hd = 1;
        } else {
            eprintln!("{}: Invalid option {}", program_name, args[i]);
            process::exit(1);
        }
    }

    // Initialize aptX context
    let mut ctx = match aptx_init(hd) {
        Some(c) => c,
        None => {
            eprintln!("{}: Cannot initialize aptX encoder", program_name);
            process::exit(1);
        }
    };

    let mut ret = 0;
    let mut input_buffer = vec![0u8; 512 * 3 * 2 * 4];
    let mut output_buffer = vec![0u8; 512 * 6];

    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    loop {
        // Read input data
        let length = match stdin.read(&mut input_buffer) {
            Ok(0) => break, // EOF
            Ok(n) => n,
            Err(_) => {
                eprintln!("{}: aptX encoding failed to read input data", program_name);
                ret = 1;
                break;
            }
        };

        // Encode the data
        let mut written: usize = 0;
        let output_buffer_len = output_buffer.len();
        let processed = aptx_encode(
            &mut ctx,
            &input_buffer[..length],
            length,
            &mut output_buffer,
            output_buffer_len,
            &mut written,
        );

        // Check if all input was processed
        if processed != length {
            eprintln!("{}: aptX encoding stopped in the middle of the sample, dropped {} byte{}",
                     program_name,
                     length - processed,
                     if length - processed != 1 { "s" } else { "" });
            ret = 1;
        }

        // Write output data
        if written > 0 {
            if let Err(_) = stdout.write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX encoding failed to write encoded data", program_name);
                ret = 1;
                break;
            }
        }

        // If we didn't process all input, stop
        if processed != length {
            break;
        }
    }

    // Finish encoding (flush remaining samples)
    let mut written: usize = 0;
    let output_buffer_len = output_buffer.len();
    if aptx_encode_finish(&mut ctx, &mut output_buffer, output_buffer_len, &mut written) != 0 {
        if written > 0 {
            if let Err(_) = stdout.write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX encoding failed to write encoded data", program_name);
                ret = 1;
            }
        }
    }

    // Clean up
    aptx_finish(ctx);

    process::exit(ret);
}
