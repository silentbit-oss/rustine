// test_csv.rs - Test suite for libcsv
// Safe Rust translation of test_csv.c - no unsafe code!

use std::cell::RefCell;
use std::process;

// Import from parent library
extern crate csv as libcsv;
use libcsv::*;

// Test event types
const CSV_END: i32 = 0;
const CSV_COL: i32 = 1;
const CSV_ROW: i32 = 2;
const CSV_ERR: i32 = 3;

// Event structure
#[derive(Clone)]
struct event {
    event_type: i32,
    retval: i32,
    size: usize,
    data: Option<Vec<u8>>,
}

// Test state (global like in C)
thread_local! {
    static EVENT_PTR: RefCell<usize> = RefCell::new(0);
    static EVENT_IDX: RefCell<i32> = RefCell::new(0);
    static ROW: RefCell<usize> = RefCell::new(0);
    static COL: RefCell<usize> = RefCell::new(0);
    static EXPECTED_EVENTS: RefCell<Vec<event>> = RefCell::new(Vec::new());
    static TEST_NAME: RefCell<String> = RefCell::new(String::new());
}

fn fail_parser(message: &str) {
    TEST_NAME.with(|name| {
        EVENT_IDX.with(|idx| {
            eprintln!("Parser test {} failed on event {}: {}", name.borrow(), idx.borrow(), message);
        });
    });
    process::exit(1);
}

fn fail_writer(test_name: &str, message: &str) {
    eprintln!("Writer test {} failed: {}", test_name, message);
    process::exit(1);
}

fn test_parser(
    test_name: &str,
    options: u8,
    input: &[u8],
    expected: &[event],
    delimiter: u8,
    quote: u8,
    space_func: Option<fn(u8) -> i32>,
    term_func: Option<fn(u8) -> i32>,
) {
    // Initialize expected events in thread-local storage
    EXPECTED_EVENTS.with(|events| {
        events.borrow_mut().clear();
        for e in expected {
            events.borrow_mut().push(e.clone());
        }
    });

    TEST_NAME.with(|name| {
        *name.borrow_mut() = test_name.to_string();
    });

    // Test with different chunk sizes
    for size in 1..=input.len() {
        let mut bytes_processed = 0;
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

        csv_init(&mut p, options);
        csv_set_delim(&mut p, delimiter);
        csv_set_quote(&mut p, quote);
        csv_set_space_func(&mut p, space_func);
        csv_set_term_func(&mut p, term_func);

        ROW.with(|r| *r.borrow_mut() = 1);
        COL.with(|c| *c.borrow_mut() = 1);
        EVENT_PTR.with(|ptr| *ptr.borrow_mut() = 0);
        EVENT_IDX.with(|idx| *idx.borrow_mut() = 1);

        while bytes_processed < input.len() {
            let bytes = std::cmp::min(size, input.len() - bytes_processed);
            let chunk = &input[bytes_processed..bytes_processed + bytes];

            // Create closures for callbacks
            let mut cb1 = |data: Option<&[u8]>| {
                EXPECTED_EVENTS.with(|events| {
                    EVENT_PTR.with(|ptr| {
                        EVENT_IDX.with(|idx| {
                            COL.with(|col| {
                                let events_vec = events.borrow();
                                let event_ptr_val = *ptr.borrow();

                                if event_ptr_val >= events_vec.len() {
                                    fail_parser("unexpected event");
                                }

                                let event = &events_vec[event_ptr_val];

                                // Make sure we were expecting a column
                                if event.event_type != CSV_COL {
                                    fail_parser("didn't expect a column");
                                }

                                // Check the actual size against the expected size
                                let actual_len = data.map(|d| d.len()).unwrap_or(0);
                                if event.size != actual_len {
                                    fail_parser("actual data length doesn't match expected data length");
                                }

                                // Check the actual data against the expected data
                                match (&event.data, data) {
                                    (None, None) => {},
                                    (Some(expected_data), Some(actual_data)) => {
                                        if expected_data.as_slice() != actual_data {
                                            fail_parser("actual data doesn't match expected data");
                                        }
                                    },
                                    _ => {
                                        fail_parser("actual data doesn't match expected data");
                                    }
                                }

                                *idx.borrow_mut() += 1;
                                *ptr.borrow_mut() += 1;
                                *col.borrow_mut() += 1;
                            });
                        });
                    });
                });
            };

            let mut cb2 = |c: i32| {
                EXPECTED_EVENTS.with(|events| {
                    EVENT_PTR.with(|ptr| {
                        EVENT_IDX.with(|idx| {
                            COL.with(|col| {
                                ROW.with(|row| {
                                    let events_vec = events.borrow();
                                    let event_ptr_val = *ptr.borrow();

                                    if event_ptr_val >= events_vec.len() {
                                        fail_parser("unexpected event");
                                    }

                                    let event = &events_vec[event_ptr_val];

                                    // Make sure we were expecting the end of a row
                                    if event.event_type != CSV_ROW {
                                        fail_parser("didn't expect end of row");
                                    }

                                    // Check that the row ended with the character we expected
                                    if event.retval != c {
                                        fail_parser("row ended with unexpected character");
                                    }

                                    *idx.borrow_mut() += 1;
                                    *ptr.borrow_mut() += 1;
                                    *col.borrow_mut() = 1;
                                    *row.borrow_mut() += 1;
                                });
                            });
                        });
                    });
                });
            };

            let retval = csv_parse(&mut p, chunk, &mut cb1, &mut cb2);

            if retval != bytes {
                EVENT_PTR.with(|ptr| {
                    EXPECTED_EVENTS.with(|events| {
                        let event_ptr_val = *ptr.borrow();
                        let events_vec = events.borrow();
                        if event_ptr_val < events_vec.len() && events_vec[event_ptr_val].event_type == CSV_ERR {
                            csv_free(&mut p);
                            return;
                        } else {
                            fail_parser("unexpected parse error occurred");
                        }
                    });
                });
                return;
            }
            bytes_processed += bytes;
        }

        // Create closures for csv_fini
        let mut cb1 = |data: Option<&[u8]>| {
            EXPECTED_EVENTS.with(|events| {
                EVENT_PTR.with(|ptr| {
                    EVENT_IDX.with(|idx| {
                        COL.with(|col| {
                            let events_vec = events.borrow();
                            let event_ptr_val = *ptr.borrow();

                            if event_ptr_val >= events_vec.len() {
                                fail_parser("unexpected event");
                            }

                            let event = &events_vec[event_ptr_val];

                            if event.event_type != CSV_COL {
                                fail_parser("didn't expect a column");
                            }

                            let actual_len = data.map(|d| d.len()).unwrap_or(0);
                            if event.size != actual_len {
                                fail_parser("actual data length doesn't match expected data length");
                            }

                            match (&event.data, data) {
                                (None, None) => {},
                                (Some(expected_data), Some(actual_data)) => {
                                    if expected_data.as_slice() != actual_data {
                                        fail_parser("actual data doesn't match expected data");
                                    }
                                },
                                _ => {
                                    fail_parser("actual data doesn't match expected data");
                                }
                            }

                            *idx.borrow_mut() += 1;
                            *ptr.borrow_mut() += 1;
                            *col.borrow_mut() += 1;
                        });
                    });
                });
            });
        };

        let mut cb2 = |c: i32| {
            EXPECTED_EVENTS.with(|events| {
                EVENT_PTR.with(|ptr| {
                    EVENT_IDX.with(|idx| {
                        COL.with(|col| {
                            ROW.with(|row| {
                                let events_vec = events.borrow();
                                let event_ptr_val = *ptr.borrow();

                                if event_ptr_val >= events_vec.len() {
                                    fail_parser("unexpected event");
                                }

                                let event = &events_vec[event_ptr_val];

                                if event.event_type != CSV_ROW {
                                    fail_parser("didn't expect end of row");
                                }

                                if event.retval != c {
                                    fail_parser("row ended with unexpected character");
                                }

                                *idx.borrow_mut() += 1;
                                *ptr.borrow_mut() += 1;
                                *col.borrow_mut() = 1;
                                *row.borrow_mut() += 1;
                            });
                        });
                    });
                });
            });
        };

        let result = csv_fini(&mut p, &mut cb1, &mut cb2);

        if result != 0 {
            EVENT_PTR.with(|ptr| {
                EXPECTED_EVENTS.with(|events| {
                    let event_ptr_val = *ptr.borrow();
                    let events_vec = events.borrow();
                    if event_ptr_val < events_vec.len() && events_vec[event_ptr_val].event_type == CSV_ERR {
                        csv_free(&mut p);
                        return;
                    } else {
                        fail_parser("unexpected parse error occurred");
                    }
                });
            });
            return;
        }

        csv_free(&mut p);

        EVENT_PTR.with(|ptr| {
            EXPECTED_EVENTS.with(|events| {
                let event_ptr_val = *ptr.borrow();
                let events_vec = events.borrow();
                if event_ptr_val >= events_vec.len() || events_vec[event_ptr_val].event_type != CSV_END {
                    fail_parser("unexpected end of input");
                }
            });
        });
    }
}

fn test_writer(
    test_name: &str,
    input: &[u8],
    expected: &[u8],
) {
    let mut temp = vec![0u8; input.len() * 2 + 2];
    let actual_len = csv_write(Some(&mut temp), input);

    if actual_len != expected.len() {
        fail_writer(test_name, "actual length doesn't match expected length");
    }

    if &temp[..actual_len] != expected {
        fail_writer(test_name, "actual data doesn't match expected data");
    }
}

fn test_writer2(
    test_name: &str,
    input: &[u8],
    expected: &[u8],
    quote: u8,
) {
    let mut temp = vec![0u8; input.len() * 2 + 2];
    let actual_len = csv_write2(Some(&mut temp), input, quote);

    if actual_len != expected.len() {
        fail_writer(test_name, "actual length doesn't match expected length");
    }

    if &temp[..actual_len] != expected {
        fail_writer(test_name, "actual data doesn't match expected data");
    }
}

fn main() {
    println!("Running libcsv tests...");

    // ============================================================================
    // TEST DATA DEFINITIONS
    // ============================================================================

    let test01_data = b" 1,2 ,  3         ,4,5\r\n";
    let test02_data = b",,,,,\n";
    let test03_data = b"\",\",\",\",\"\"";
    let test04_data = b"\"I call our world Flatland,\n\
not because we call it so,\n\
but to make its nature clearer\n\
to you, my happy readers,\n\
who are privileged to live in Space.\"";
    let test05_data = b"\"\"\"a,b\"\"\",,\" \"\"\"\" \",\"\"\"\"\" \",\" \"\"\"\"\",\"\"\"\"\"\"";
    let test06_data = b"\" a, b ,c \", a b  c,";
    let test07_data = b"\" \"\" \" \" \"\" \"";
    let test07b_data = b"\" \"\" \" \" \"\" \"";
    // test08_data: " abc" (6) + 45 spaces + 7 lines of 53 spaces + 42 spaces + ", "123" (8) = 472 chars
    let test08_data: &[u8] = &{
        let mut v = Vec::new();
        v.extend_from_slice(b"\" abc\"");  // 6 bytes
        v.extend_from_slice(&[b' '; 45]);  // 45 spaces (total 51 for line 1)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 2)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 3)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 4)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 5)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 6)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 7)
        v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 8)
        v.extend_from_slice(&[b' '; 42]);  // 42 spaces
        v.extend_from_slice(b"\", \"123\"");  // 8 bytes
        v  // Total: 6 + 45 + 7*53 + 42 + 8 = 6 + 45 + 371 + 42 + 8 = 472
    };
    let test09_data = b"";
    let test10_data = b"a\n";
    let test11_data = b"1,2 ,3,4\n";
    let test12_data = b"\n\n\n\n";
    let test12b_data = b"\n\n\n\n";
    let test13_data = b"\"abc\"";
    let test14_data = b"1, 2, 3,\n\r\n  \"4\", \r,";
    let test15_data = b"1, 2, 3,\n\r\n  \"4\", \r\"\"";
    let test16_data = b"\"1\",\"2\",\" 3 ";
    let test16b_data = b"\"1\",\"2\",\" 3 ";
    let test17_data = b" a\x00b\x00c ";
    let test19_data = b"  , \"\" ,";

    // Custom tests
    let custom01_data = b"'''a;b''';;' '''' ';''''' ';' ''''';''''''";

    // ============================================================================
    // EXPECTED RESULTS
    // ============================================================================

    // |1|2|3|4|5|
    let test01_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"3".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"4".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"5".to_vec()) },
        event { event_type: CSV_ROW, retval: 0x0d, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |||||||
    let test02_results = [
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |,|,||
    let test03_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b",".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b",".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    let test04_results = [
        event { event_type: CSV_COL, retval: 0, size: 147, data: Some(b"I call our world Flatland,\n\
not because we call it so,\n\
but to make its nature clearer\n\
to you, my happy readers,\n\
who are privileged to live in Space.".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |"a,b"|| "" |"" | ""|""|
    let test05_results = [
        event { event_type: CSV_COL, retval: 0, size: 5, data: Some(b"\"a,b\"".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 4, data: Some(b" \"\" ".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b"\"\" ".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b" \"\"".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 2, data: Some(b"\"\"".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // | a, b ,c |a b  c||
    let test06_results = [
        event { event_type: CSV_COL, retval: 0, size: 9, data: Some(b" a, b ,c ".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 6, data: Some(b"a b  c".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // | " " " " |
    let test07_results = [
        event { event_type: CSV_COL, retval: 0, size: 9, data: Some(b" \" \" \" \" ".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // Will cause error with CSV_STRICT set
    let test07b_results = [
        event { event_type: CSV_ERR, retval: 0, size: 0, data: None },
    ];

    // test08_results: " abc"" (5) + 46 spaces + 7 lines of 53 spaces + 41 spaces = 463 chars
    let test08_results = [
        event { event_type: CSV_COL, retval: 0, size: 463, data: Some({
            let mut v = Vec::new();
            v.extend_from_slice(b" abc\"");  // 5 bytes
            v.extend_from_slice(&[b' '; 46]);  // 46 spaces (total 51 for line 1)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 2)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 3)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 4)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 5)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 6)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 7)
            v.extend_from_slice(&[b' '; 53]);  // 53 spaces (line 8)
            v.extend_from_slice(&[b' '; 41]);  // 41 spaces (line 9)
            v  // Total: 5 + 46 + 7*53 + 41 = 5 + 46 + 371 + 41 = 463
        }) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b"123".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // empty
    let test09_results = [
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |a|
    let test10_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"a".to_vec()) },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |1|2|3|4|
    let test11_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"3".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"4".to_vec()) },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // empty
    let test12_results = [
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // Test CSV_REPALL_NL
    let test12b_results = [
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |abc|
    let test13_results = [
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b"abc".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |1|2|3||
    // |4||
    // |||
    let test14_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"3".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"4".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: 0x0d, size: 1, data: None },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: -1, size: 0, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |1|2|3||
    // |4||
    // ||
    let test15_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"3".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: 0x0a, size: 1, data: None },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"4".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: 0x0d, size: 1, data: None },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_ROW, retval: -1, size: 0, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |1|2| 3 |
    let test16_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b" 3 ".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // Will cause an error with CSV_STRICT_FINI set
    let test16b_results = [
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"1".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 1, data: Some(b"2".to_vec()) },
        event { event_type: CSV_ERR, retval: 0, size: 0, data: None },
    ];

    // |a\0b\0c|
    let test17_results = [
        event { event_type: CSV_COL, retval: 0, size: 5, data: Some(b"a\x00b\x00c".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // Test CSV_EMPTY_IS_NULL
    let test19_results = [
        event { event_type: CSV_COL, retval: 0, size: 0, data: None },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: None },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // |'a;b'|| '' |'' | ''|''|
    let custom01_results = [
        event { event_type: CSV_COL, retval: 0, size: 5, data: Some(b"'a;b'".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 0, data: Some(Vec::new()) },
        event { event_type: CSV_COL, retval: 0, size: 4, data: Some(b" '' ".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b"'' ".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 3, data: Some(b" ''".to_vec()) },
        event { event_type: CSV_COL, retval: 0, size: 2, data: Some(b"''".to_vec()) },
        event { event_type: CSV_ROW, retval: -1, size: 1, data: None },
        event { event_type: CSV_END, retval: 0, size: 0, data: None },
    ];

    // ============================================================================
    // PARSER TESTS
    // ============================================================================

    test_parser("test01", 0, test01_data, &test01_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test01", CSV_STRICT, test01_data, &test01_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test01", CSV_STRICT | CSV_EMPTY_IS_NULL, test01_data, &test01_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test02", 0, test02_data, &test02_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test02", CSV_STRICT, test02_data, &test02_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test03", 0, test03_data, &test03_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test03", CSV_STRICT, test03_data, &test03_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test04", 0, test04_data, &test04_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test04", CSV_STRICT, test04_data, &test04_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test05", 0, test05_data, &test05_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test05", CSV_STRICT, test05_data, &test05_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test05", CSV_STRICT | CSV_STRICT_FINI, test05_data, &test05_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test06", 0, test06_data, &test06_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test06", CSV_STRICT, test06_data, &test06_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test07", 0, test07_data, &test07_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test07b", CSV_STRICT, test07b_data, &test07b_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test08", 0, test08_data, &test08_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test09", 0, test09_data, &test09_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test09", CSV_EMPTY_IS_NULL, test09_data, &test09_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test10", 0, test10_data, &test10_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test11", 0, test11_data, &test11_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test11", CSV_EMPTY_IS_NULL, test11_data, &test11_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test12", 0, test12_data, &test12_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test12", CSV_EMPTY_IS_NULL, test12_data, &test12_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test12b", CSV_REPALL_NL, test12b_data, &test12b_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test12b", CSV_REPALL_NL | CSV_EMPTY_IS_NULL, test12b_data, &test12b_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test13", 0, test13_data, &test13_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test14", 0, test14_data, &test14_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test14", CSV_STRICT, test14_data, &test14_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test15", 0, test15_data, &test15_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test15", CSV_STRICT, test15_data, &test15_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test16", 0, test16_data, &test16_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test16", CSV_STRICT, test16_data, &test16_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test16b", CSV_STRICT | CSV_STRICT_FINI, test16b_data, &test16b_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test16", 0, test16_data, &test16_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test16", CSV_STRICT, test16_data, &test16_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test17", 0, test17_data, &test17_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test17", CSV_STRICT, test17_data, &test17_results, CSV_COMMA, CSV_QUOTE, None, None);
    test_parser("test17", CSV_STRICT | CSV_EMPTY_IS_NULL, test17_data, &test17_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("test19", CSV_EMPTY_IS_NULL, test19_data, &test19_results, CSV_COMMA, CSV_QUOTE, None, None);

    test_parser("custom01", 0, custom01_data, &custom01_results, b';', b'\'', None, None);

    // ============================================================================
    // WRITER TESTS
    // ============================================================================

    test_writer("writer01", b"abc", b"\"abc\"");
    test_writer("writer02", b"\"\"\"\"\"\"\"\"", b"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");

    test_writer2("writer03", b"abc", b"'abc'", b'\'');
    test_writer2("writer04", b"''''''''", b"''''''''''''''''''", b'\'');

    println!("All tests passed");
}
