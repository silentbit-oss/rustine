// csvinfo.rs - CSV information utility
// Safe Rust translation of csvinfo.c - no unsafe code!

use std::io::Read;
use std::cell::RefCell;

extern crate csv as libcsv;
use libcsv::*;

struct counts {
    fields: usize,
    rows: usize,
}

thread_local! {
    static COUNTS: RefCell<counts> = RefCell::new(counts { fields: 0, rows: 0 });
}

fn is_space(c: u8) -> i32 {
    if c == CSV_SPACE || c == CSV_TAB {
        1
    } else {
        0
    }
}

fn is_term(c: u8) -> i32 {
    if c == CSV_CR || c == CSV_LF {
        1
    } else {
        0
    }
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
    csv_set_space_func(&mut p, Some(is_space));
    csv_set_term_func(&mut p, Some(is_term));

    let stdin = std::io::stdin();
    let mut handle = stdin.lock();
    let mut buffer = vec![0u8; 1024];

    loop {
        match handle.read(&mut buffer) {
            Ok(0) => break, // EOF
            Ok(n) => {
                let mut cb1 = |_data: Option<&[u8]>| {
                    COUNTS.with(|counts| {
                        counts.borrow_mut().fields += 1;
                    });
                };

                let mut cb2 = |_c: i32| {
                    COUNTS.with(|counts| {
                        counts.borrow_mut().rows += 1;
                    });
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

    let mut cb1 = |_data: Option<&[u8]>| {
        COUNTS.with(|counts| {
            counts.borrow_mut().fields += 1;
        });
    };

    let mut cb2 = |_c: i32| {
        COUNTS.with(|counts| {
            counts.borrow_mut().rows += 1;
        });
    };

    csv_fini(&mut p, &mut cb1, &mut cb2);
    csv_free(&mut p);

    COUNTS.with(|counts| {
        let c = counts.borrow();
        println!("Fields: {}", c.fields);
        println!("Rows: {}", c.rows);
    });
}
