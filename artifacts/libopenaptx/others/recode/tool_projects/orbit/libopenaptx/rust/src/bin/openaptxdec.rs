/*
 * aptX decoder utility
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
    aptx_init, aptx_finish, aptx_decode_sync, aptx_decode_sync_finish,
};

fn main() {
    let args: Vec<String> = env::args().collect();
    let program_name = args.get(0).map(|s| s.as_str()).unwrap_or("openaptxdec");

    let mut hd = 0;

    // Parse command line arguments
    for i in 1..args.len() {
        if args[i] == "-h" || args[i] == "--help" {
            eprintln!("aptX decoder utility {}.{}.{} (using libopenaptx {}.{}.{})",
                     OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH,
                     aptx_major, aptx_minor, aptx_patch);
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
            eprintln!("        {} < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -", program_name);
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
            eprintln!("{}: Cannot initialize aptX decoder", program_name);
            process::exit(1);
        }
    };

    // Try to guess type of input stream based on the first six bytes
    // Encoder produces fixed first sample because aptX predictor has fixed values
    let mut input_buffer = vec![0u8; 512 * 6];
    let mut output_buffer = vec![0u8; 512 * 3 * 2 * 6 + 3 * 2 * 4];

    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    let mut length = match stdin.read(&mut input_buffer[..6]) {
        Ok(n) => n,
        Err(_) => 0,
    };

    if length >= 4 && &input_buffer[..4] == b"\x4b\xbf\x4b\xbf" {
        if hd != 0 {
            eprintln!("{}: Input looks like start of aptX audio stream (not aptX HD), try without --hd", program_name);
        }
    } else if length >= 6 && &input_buffer[..6] == b"\x73\xbe\xff\x73\xbe\xff" {
        if hd == 0 {
            eprintln!("{}: Input looks like start of aptX HD audio stream, try with --hd", program_name);
        }
    } else {
        if length >= 4 && &input_buffer[..4] == b"\x6b\xbf\x6b\xbf" {
            eprintln!("{}: Input looks like start of standard aptX audio stream, which is not supported yet", program_name);
        } else {
            eprintln!("{}: Input does not look like start of aptX nor aptX HD audio stream", program_name);
        }
    }

    let mut ret = 0;
    let mut syncing = 0;

    while length > 0 {
        let mut written: usize = 0;
        let mut synced: i32 = 0;
        let mut dropped: usize = 0;
        let output_buffer_len = output_buffer.len();

        let processed = aptx_decode_sync(
            &mut ctx,
            &input_buffer[..length],
            length,
            &mut output_buffer,
            output_buffer_len,
            &mut written,
            &mut synced,
            &mut dropped,
        );

        // Check all possible states of synced, syncing and dropped status
        if synced == 0 {
            if syncing == 0 {
                eprintln!("{}: aptX decoding failed, synchronizing", program_name);
                syncing = 1;
                ret = 1;
            }
            if dropped != 0 {
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}",
                         program_name, dropped, if dropped != 1 { "s" } else { "" });
                syncing = 0;
                ret = 1;
            }
            if syncing == 0 {
                eprintln!("{}: aptX decoding failed, synchronizing", program_name);
                syncing = 1;
                ret = 1;
            }
        } else {
            if dropped != 0 {
                if syncing == 0 {
                    eprintln!("{}: aptX decoding failed, synchronizing", program_name);
                }
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}",
                         program_name, dropped, if dropped != 1 { "s" } else { "" });
                syncing = 0;
                ret = 1;
            } else if syncing != 0 {
                eprintln!("{}: aptX synchronization successful", program_name);
                syncing = 0;
                ret = 1;
            }
        }

        // If we have not decoded all supplied samples then decoding unrecoverably failed
        if processed != length {
            eprintln!("{}: aptX decoding failed", program_name);
            ret = 1;
            break;
        }

        // Read next chunk of input data
        length = match stdin.read(&mut input_buffer) {
            Ok(0) => 0, // EOF
            Ok(n) => n,
            Err(_) => {
                eprintln!("{}: aptX decoding failed to read input data", program_name);
                ret = 1;
                0
            }
        };

        // On the end of the input stream last two decoded samples are just padding and not real data
        if length == 0 && ret == 0 && written >= 6 * 2 {
            written -= 6 * 2;
        }

        // Write decoded output
        if written > 0 {
            if let Err(_) = stdout.write_all(&output_buffer[..written]) {
                eprintln!("{}: aptX decoding failed to write decoded data", program_name);
                ret = 1;
                break;
            }
        }
    }

    // Finish decoding
    let dropped = aptx_decode_sync_finish(&mut ctx);
    if dropped != 0 && syncing == 0 {
        eprintln!("{}: aptX decoding stopped in the middle of the sample, dropped {} byte{}",
                 program_name, dropped, if dropped != 1 { "s" } else { "" });
        ret = 1;
    } else if syncing != 0 {
        eprintln!("{}: aptX synchronization failed", program_name);
        ret = 1;
    }

    // Clean up
    aptx_finish(ctx);

    process::exit(ret);
}
