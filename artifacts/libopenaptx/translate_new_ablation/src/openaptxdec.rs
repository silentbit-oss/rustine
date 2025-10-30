use lazy_static::lazy_static;
use std::env;
use std::ffi::CStr;
use std::io::Read;
use std::io::Write;
use std::io;
use std::process;
use translate_new::*;

pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    let argc = args.len();
    let argv: Vec<&str> = args.iter().map(|s| s.as_str()).collect();

    let mut hd = false;
    let mut ret = 0;

    for i in 1..argc {
        if argv[i] == "-h" || argv[i] == "--help" {
            eprintln!("aptX decoder utility {}.{}.{} (using libopenaptx {}.{}.{})", 0, 2, 1, APTX_MAJOR, APTX_MINOR, APTX_PATCH);
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
            eprintln!("        {} [options]", argv[0]);
            eprintln!();
            eprintln!("Options:");
            eprintln!("        -h, --help   Display this help");
            eprintln!("        --hd         Decode from aptX HD");
            eprintln!();
            eprintln!("Examples:");
            eprintln!();
            eprintln!("        {} < sample.aptx > sample.s24le", argv[0]);
            eprintln!();
            eprintln!("        {} --hd < sample.aptxhd > sample.s24le", argv[0]);
            eprintln!();
            eprintln!("        {} < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -", argv[0]);
            return Ok(());
        } else if argv[i] == "--hd" {
            hd = true;
        } else {
            eprintln!("{}: Invalid option {}", argv[0], argv[i]);
            return Ok(());
        }
    }

    let mut ctx = match aptx_init(hd) {
        Some(ctx) => ctx,
        None => {
            eprintln!("{}: Cannot initialize aptX decoder", argv[0]);
            return Ok(());
        }
    };

    let mut input_buffer_guard = INPUT_BUFFER.lock().unwrap();
    let input_buffer = &mut *input_buffer_guard;
    let mut output_buffer_guard = OUTPUT_BUFFER.lock().unwrap();
    let output_buffer = &mut *output_buffer_guard;

    let mut length = match io::stdin().read(&mut input_buffer[..6]) {
        Ok(len) => len,
        Err(_) => 0,
    };

    if length >= 4 && &input_buffer[0..4] == b"\x4b\xbf\x4b\xbf" {
        if hd {
            eprintln!("{}: Input looks like start of aptX audio stream (not aptX HD), try without --hd", argv[0]);
        }
    } else if length >= 6 && &input_buffer[0..6] == b"\x73\xbe\xff\x73\xbe\xff" {
        if !hd {
            eprintln!("{}: Input looks like start of aptX HD audio stream, try with --hd", argv[0]);
        }
    } else {
        if length >= 4 && &input_buffer[0..4] == b"\x6b\xbf\x6b\xbf" {
            eprintln!("{}: Input looks like start of standard aptX audio stream, which is not supported yet", argv[0]);
        } else {
            eprintln!("{}: Input does not look like start of aptX nor aptX HD audio stream", argv[0]);
        }
    }

    let mut syncing = false;
    let mut synced = 0;
    let mut dropped = 0;
    let mut written = 0;

    while length > 0 {
        let processed = aptx_decode_sync(
            &mut *ctx,
            &input_buffer[..length],
            &mut output_buffer[..],
            &mut written,
            &mut synced,
            &mut dropped,
        );

        if synced == 0 {
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", argv[0]);
                syncing = true;
                ret = 1;
            }
            if dropped > 0 {
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}", argv[0], dropped, if dropped != 1 { "s" } else { "" });
                syncing = false;
                ret = 1;
            }
            if !syncing {
                eprintln!("{}: aptX decoding failed, synchronizing", argv[0]);
                syncing = true;
                ret = 1;
            }
        } else {
            if dropped > 0 {
                if !syncing {
                    eprintln!("{}: aptX decoding failed, synchronizing", argv[0]);
                }
                eprintln!("{}: aptX synchronization successful, dropped {} byte{}", argv[0], dropped, if dropped != 1 { "s" } else { "" });
                syncing = false;
                ret = 1;
            } else if syncing {
                eprintln!("{}: aptX synchronization successful", argv[0]);
                syncing = false;
                ret = 1;
            }
        }

        if processed != length {
            eprintln!("{}: aptX decoding failed", argv[0]);
            ret = 1;
            break;
        }

        length = match io::stdin().read(input_buffer) {
            Ok(len) => len,
            Err(_) => {
                if std::io::Error::last_os_error().raw_os_error().is_some() {
                    eprintln!("{}: aptX decoding failed to read input data", argv[0]);
                    ret = 1;
                }
                0
            }
        };

        if length == 0 && std::io::Error::last_os_error().raw_os_error().is_none() && written >= 6 * 2 {
            written -= 6 * 2;
        }

        if written > 0 {
            if io::stdout().write_all(&output_buffer[..written]).is_err() {
                eprintln!("{}: aptX decoding failed to write decoded data", argv[0]);
                ret = 1;
                break;
            }
        }
    }

    let dropped_final = aptx_decode_sync_finish(&mut *ctx);
    if dropped_final > 0 && !syncing {
        eprintln!("{}: aptX decoding stopped in the middle of the sample, dropped {} byte{}", argv[0], dropped_final, if dropped_final != 1 { "s" } else { "" });
        ret = 1;
    } else if syncing {
        eprintln!("{}: aptX synchronization failed", argv[0]);
        ret = 1;
    }

    aptx_finish(Some(ctx));
    if ret != 0 {
        Err("aptX decoding failed".into())
    } else {
        Ok(())
    }
}
