// csvfix.rs - CSV fixing utility
// Safe Rust translation of csvfix.c - no unsafe code!

use std::io::{self, Read, Write};

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

    csv_init(&mut p, 0);

    let stdin = io::stdin();
    let mut handle = stdin.lock();
    let mut buffer = vec![0u8; 1024];

    loop {
        match handle.read(&mut buffer) {
            Ok(0) => break, // EOF
            Ok(n) => {
                let mut cb1 = |data: Option<&[u8]>| {
                    let stdout = io::stdout();
                    let mut handle = stdout.lock();
                    if let Some(bytes) = data {
                        let _ = csv_fwrite(&mut handle, bytes);
                    } else {
                        let _ = handle.write_all(b"\"\"");
                    }
                    let _ = handle.write_all(b",");
                };

                let mut cb2 = |_c: i32| {
                    let stdout = io::stdout();
                    let mut handle = stdout.lock();
                    let _ = handle.write_all(b"\n");
                };

                let retval = csv_parse(&mut p, &buffer[..n], &mut cb1, &mut cb2);

                if retval != n {
                    eprintln!("Error: {}", csv_strerror(csv_error(&p)));
                    std::process::exit(1);
                }
            }
            Err(e) => {
                eprintln!("Error reading stdin: {}", e);
                std::process::exit(1);
            }
        }
    }

    let mut cb1 = |data: Option<&[u8]>| {
        let stdout = io::stdout();
        let mut handle = stdout.lock();
        if let Some(bytes) = data {
            let _ = csv_fwrite(&mut handle, bytes);
        } else {
            let _ = handle.write_all(b"\"\"");
        }
        let _ = handle.write_all(b",");
    };

    let mut cb2 = |_c: i32| {
        let stdout = io::stdout();
        let mut handle = stdout.lock();
        let _ = handle.write_all(b"\n");
    };

    csv_fini(&mut p, &mut cb1, &mut cb2);
    csv_free(&mut p);
}
