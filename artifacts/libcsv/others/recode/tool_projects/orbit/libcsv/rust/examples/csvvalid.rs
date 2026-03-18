// csvvalid.rs - CSV validation utility
// Safe Rust translation of csvvalid.c - no unsafe code!

use std::io::Read;

extern crate csv as libcsv;
use libcsv::*;

fn main() {
    let mut p = csv_parser {
        pstate: 0,
        quoted: 0,
        spaces: 0,
        entry_buf: Vec::new(),
        entry_pos: 0,
        entry_size: 0,
        status: 0,
        options: 0,
        quote_char: 0,
        delim_char: 0,
        is_space: None,
        is_term: None,
        blk_size: 0,
    };

    csv_init(&mut p, CSV_STRICT | CSV_STRICT_FINI);

    let stdin = std::io::stdin();
    let mut handle = stdin.lock();
    let mut buffer = vec![0u8; 1024];

    loop {
        match handle.read(&mut buffer) {
            Ok(0) => break, // EOF
            Ok(n) => {
                let mut cb1 = |_data: Option<&[u8]>| {
                    // No-op field callback
                };

                let mut cb2 = |_c: i32| {
                    // No-op row callback
                };

                let retval = csv_parse(&mut p, &buffer[..n], &mut cb1, &mut cb2);

                if retval != n {
                    eprintln!("Invalid CSV: {}", csv_strerror(csv_error(&p)));
                    std::process::exit(1);
                }
            }
            Err(e) => {
                eprintln!("Error reading stdin: {}", e);
                std::process::exit(1);
            }
        }
    }

    let mut cb1 = |_data: Option<&[u8]>| {
        // No-op field callback
    };

    let mut cb2 = |_c: i32| {
        // No-op row callback
    };

    let result = csv_fini(&mut p, &mut cb1, &mut cb2);

    if result != 0 {
        eprintln!("Invalid CSV: {}", csv_strerror(csv_error(&p)));
        std::process::exit(1);
    }

    csv_free(&mut p);

    println!("Valid CSV");
}
