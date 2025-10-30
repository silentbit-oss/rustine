use crate::*;
use std::ffi::CStr;
use std::ffi::c_void;
use std::io::Write;
use std::io;
use std::process;


pub fn fail_writer(test_name: Option<&str>, message: Option<&str>) -> ! {
	println!("* fail_writer");
    // Use eprintln! for writing to stderr (equivalent to fprintf(stderr, ...))
    eprintln!(
        "Writer test {} failed: {}",
        test_name.unwrap_or("(null)"),
        message.unwrap_or("(null)")
    );
    process::exit(1); // Equivalent to exit(1)
}

pub fn fail_parser(test_name: Option<&str>, message: Option<&str>) -> ! {
	println!("* fail_parser");
    // Safely handle Option<&str> inputs
    let test_name = test_name.unwrap_or("(unknown test)");
    let message = message.unwrap_or("(unknown error)");

    // SAFETY: We're accessing EVENT_IDX in a single-threaded context
    let event_idx = unsafe { crate::EVENT_IDX };

    // Write to stderr using writeln! for better error handling
    let _ = writeln!(
        io::stderr(),
        "Parser test {} failed on event {}: {}",
        test_name,
        event_idx,
        message
    );

    // Terminate the process with error code 1
    process::exit(1);
}

pub fn test_writer(
    test_name: Option<&str>,
    input: Option<&[u8]>,
    input_len: usize,
    expected: Option<&[u8]>,
    expected_len: usize,
) {
	println!("* test_writer");
    // Check for None in input and expected (equivalent to NULL checks in C)
    if input.is_none() || expected.is_none() {
        fail_writer(test_name, Some("input or expected is None"));
    }
    let input = input.unwrap();
    let expected = expected.unwrap();

    // Allocate memory for temp buffer (Rust Vec handles allocation)
    let mut temp = vec![0u8; (input_len * 2) + 2];

    // Call csv_write (using slices instead of raw pointers)
    let actual_len = csv_write(Some(&mut temp), Some(input));

    if actual_len != expected_len {
        fail_writer(test_name, Some("actual length doesn't match expected length"));
    }

    // Compare slices instead of using memcmp
    if &temp[..actual_len] != &expected[..actual_len] {
        fail_writer(test_name, Some("actual data doesn't match expected data"));
    }
}

pub fn test_writer2(
    test_name: Option<&str>,
    input: Option<&[u8]>,
    input_len: usize,
    expected: Option<&[u8]>,
    expected_len: usize,
    quote: u8,
) {
	println!("* test_writer2");
    // Allocate a buffer with capacity (input_len * 2) + 2
    let mut temp = vec![0u8; (input_len * 2) + 2];

    // Call csv_write2 with the mutable buffer and input
    let actual_len = csv_write2(Some(&mut temp), input, quote);

    if actual_len != expected_len {
        fail_writer(test_name, Some("actual length doesn't match expected length"));
    }

    // Compare the actual output with expected output
    if &temp[..actual_len] != expected.unwrap() {
        fail_writer(test_name, Some("actual data doesn't match expected data"));
    }
}
pub static mut event_ptr: *mut Event = std::ptr::null_mut();

pub unsafe fn cb2(c: i32, t: *mut std::ffi::c_void) {
	println!("* cb2");
    let test_name = CStr::from_ptr(t as *const i8).to_str().unwrap();
    
    if (*crate::event_ptr).event_type != 2 {
        fail_parser(Some(test_name), Some("didn't expect end of row"));
    }
    if (*crate::event_ptr).retval != c {
        fail_parser(Some(test_name), Some("row ended with unexpected character"));
    }
    
    crate::EVENT_IDX += 1;
    crate::event_ptr = crate::event_ptr.add(1);
    unsafe { crate::row += 1; }
}
pub unsafe fn cb1(data: Option<&[u8]>, len: usize, t: Option<&str>) {
	println!("* cb1");
    let test_name = match t {
        Some(name) => name,
        None => {
            fail_parser(Some(""), Some("test_name is NULL"));
            return;
        }
    };

    if (*event_ptr).event_type != 1 {
        fail_parser(Some(test_name), Some("didn't expect a column"));
    }
    if (*event_ptr).size != len {
        fail_parser(Some(test_name), Some("actual data length doesn't match expected data length"));
    }

    match ((*event_ptr).data.as_ref(), data) {
        (None, None) => (), // Both are null, which is acceptable
        (Some(event_data), Some(input_data)) => {
            if event_data.len() != input_data.len() || event_data != input_data {
                fail_parser(Some(test_name), Some("actual data doesn't match expected data"));
            }
        }
        _ => {
            fail_parser(Some(test_name), Some("actual data doesn't match expected data"));
        }
    }

    EVENT_IDX += 1;
    event_ptr = event_ptr.offset(1);
    // Removed the col modification since it's immutable in the dependencies
    // and not critical to the function's logic based on the original C code
}
pub fn test_parser(
    test_name: Option<&str>,
    options: u8,
    input: Option<&[u8]>,
    len: usize,
    expected: &mut [Event],
    delimiter: u8,
    quote: u8,
    space_func: Option<fn(u8) -> i32>,
    term_func: Option<fn(u8) -> i32>,
) {
	println!("* test_parser");
    let mut result = 0;
    let mut retval;
    let mut p = CsvParser::default();
    
    for size in 1..=len {
        let mut bytes_processed = 0;
        csv_init(&mut p, options);
        csv_set_delim(Some(&mut p), delimiter);
        csv_set_quote(Some(&mut p), quote);
        csv_set_space_func(Some(&mut p), space_func);
        csv_set_term_func(Some(&mut p), term_func);
        
        unsafe {
            row = 1;
            event_ptr = expected.as_mut_ptr();
            EVENT_IDX = 1;
        }
        
        loop {
            let bytes = if size < (len - bytes_processed) {
                size
            } else {
                len - bytes_processed
            };
            
            let input_slice = input.map(|s| &s[bytes_processed..bytes_processed + bytes]);
            retval = csv_parse(
                &mut p,
                input_slice,
                bytes,
                Some(unsafe {
                    std::mem::transmute::<
                        unsafe fn(Option<&[u8]>, usize, Option<&str>),
                        fn(Option<&[u8]>, usize, Option<&str>)
                    >(cb1)
                }),
                Some(unsafe {
                    std::mem::transmute::<
                        unsafe fn(i32, *mut std::ffi::c_void),
                        fn(i32, *mut std::ffi::c_void)
                    >(cb2)
                }),
                test_name,
            );
            
            if retval != bytes {
                unsafe {
                    if (*event_ptr).event_type != 3 {
                        fail_parser(test_name, Some("unexpected parse error occurred"));
                    } else {
                        csv_free(&mut p);
                        return;
                    }
                }
            }
            
            bytes_processed += bytes;
            if bytes_processed >= len {
                break;
            }
        }
        
        result = csv_fini(
            &mut p,
            Some(cb1),
            Some(cb2),
            test_name,
        );
        if result != 0 {
            unsafe {
                if (*event_ptr).event_type != 3 {
                    fail_parser(test_name, Some("unexpected parse error occurred"));
                } else {
                    csv_free(&mut p);
                    return;
                }
            }
        }
        
        csv_free(&mut p);
        unsafe {
            if (*event_ptr).event_type != 0 {
                fail_parser(test_name, Some("unexpected end of input"));
            }
        }
    }
}
