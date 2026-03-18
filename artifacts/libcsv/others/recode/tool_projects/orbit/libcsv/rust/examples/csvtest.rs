// csvtest.rs - reads CSV data from stdin and output properly formed equivalent
// Safe Rust translation of csvtest.c - no unsafe code!

use std::io::{self, Read};
use std::cell::RefCell;
use std::process;

extern crate csv as libcsv;
use libcsv::*;

thread_local! {
    static PUT_COMMA: RefCell<bool> = RefCell::new(false);
}

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
    let mut buffer = [0u8; 1];

    loop {
        match handle.read(&mut buffer) {
            Ok(0) => break, // EOF
            Ok(_) => {
                let mut cb1 = |data: Option<&[u8]>| {
                    PUT_COMMA.with(|put_comma| {
                        if *put_comma.borrow() {
                            print!(",");
                        }

                        // Write the CSV field
                        print!("\"");
                        if let Some(bytes) = data {
                            for &byte in bytes {
                                if byte == b'"' {
                                    print!("\"\"");
                                } else {
                                    print!("{}", byte as char);
                                }
                            }
                        }
                        print!("\"");

                        *put_comma.borrow_mut() = true;
                    });
                };

                let mut cb2 = |_c: i32| {
                    PUT_COMMA.with(|put_comma| {
                        *put_comma.borrow_mut() = false;
                    });
                    println!();
                };

                let retval = csv_parse(&mut p, &buffer[..1], &mut cb1, &mut cb2);

                if retval != 1 {
                    eprintln!("Error: {}", csv_strerror(csv_error(&p)));
                    process::exit(1);
                }
            }
            Err(e) => {
                eprintln!("Error reading stdin: {}", e);
                process::exit(1);
            }
        }
    }

    let mut cb1 = |data: Option<&[u8]>| {
        PUT_COMMA.with(|put_comma| {
            if *put_comma.borrow() {
                print!(",");
            }

            print!("\"");
            if let Some(bytes) = data {
                for &byte in bytes {
                    if byte == b'"' {
                        print!("\"\"");
                    } else {
                        print!("{}", byte as char);
                    }
                }
            }
            print!("\"");

            *put_comma.borrow_mut() = true;
        });
    };

    let mut cb2 = |_c: i32| {
        PUT_COMMA.with(|put_comma| {
            *put_comma.borrow_mut() = false;
        });
        println!();
    };

    csv_fini(&mut p, &mut cb1, &mut cb2);
    csv_free(&mut p);
}
