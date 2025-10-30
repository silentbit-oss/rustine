use libc::FILE;
use translate_without_break_down::*;
use std::env;
use std::process;
use std::ffi::CStr;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::path::MAIN_SEPARATOR as PATH_SEP;
use std::os::raw::c_char;
pub fn main() {
    const PATH_SEP: Char = '/';
    // Type size checks
    if !(std::mem::size_of::<Int32>() == 4 
        && std::mem::size_of::<UInt32>() == 4 
        && std::mem::size_of::<Int16>() == 2 
        && std::mem::size_of::<UInt16>() == 2 
        && std::mem::size_of::<Char>() == 4
        && std::mem::size_of::<UChar>() == 1) {
        configError();
    }

    // Initialize global variables
    OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap().take();
    smallMode.store(false, Ordering::SeqCst);
    KEEP_INPUT_FILES.store(false, Ordering::SeqCst);
    forceOverwrite.store(false, Ordering::SeqCst);
    noisy.store(true, Ordering::SeqCst);
    VERBOSITY.store(0, Ordering::SeqCst);
    BLOCK_SIZE_100K.store(9, Ordering::SeqCst);
    TEST_FAILS_EXIST.store(false, Ordering::SeqCst);
    UNZ_FAILS_EXIST.store(false, Ordering::SeqCst);
    NUM_FILE_NAMES.store(0, Ordering::SeqCst);
    NUM_FILES_PROCESSED.store(0, Ordering::SeqCst);
    WORK_FACTOR.store(30, Ordering::SeqCst);
    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
    EXIT_VALUE.store(0, Ordering::SeqCst);

    // Signal handling
    unsafe {
        libc::signal(libc::SIGSEGV, mySIGSEGVorSIGBUScatcher as usize);
    }

    // Initialize file names
    {
        let mut in_name = IN_NAME.lock().unwrap();
        copyFileName(&mut in_name[..], &['(', 'n', 'o', 'n', 'e', ')']);
        
        let mut out_name = outName.lock().unwrap();
        copyFileName(&mut out_name[..], &['(', 'n', 'o', 'n', 'e', ')']);
        
        let mut prog_name_really = PROG_NAME_REALLY.lock().unwrap();
        let args: Vec<String> = std::env::args().collect();
        let argv0: Vec<Char> = args[0].chars().collect();
        copyFileName(&mut prog_name_really[..], &argv0);
    }

    // Set progName
    {
        let prog_name_really = PROG_NAME_REALLY.lock().unwrap();
        let mut prog_name = PROG_NAME.lock().unwrap();
        //prog_name.copy_from_slice(&prog_name_really[..]);
        prog_name[..prog_name_really.len()].copy_from_slice(&prog_name_really[..]);
        
        // Find last path separator
        let mut last_sep = 0;
        for (i, &c) in prog_name_really.iter().enumerate() {
            if c == PATH_SEP {
                last_sep = i;
            }
        }
        
        if last_sep > 0 {
            //prog_name.copy_from_slice(&prog_name_really[last_sep + 1..]);
            let source_slice = &prog_name_really[last_sep + 1..];
            prog_name[..source_slice.len()].copy_from_slice(source_slice);
        }
    }

    // Process arguments
    let mut arg_list: Option<Box<Cell>> = None;
    addFlagsFromEnvVar(&mut arg_list, 'B');
    addFlagsFromEnvVar(&mut arg_list, 'B');
    
    let args: Vec<String> = std::env::args().collect();
    
    println!("=======================>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> args ==> {:?}", args);
    for i in 1..args.len() {
        arg_list = snocString(arg_list, &args[i]);
        // TODO: Implement APPEND_FILESPEC equivalent
    }

    LONGEST_FILE_NAME.store(7, Ordering::SeqCst);
    NUM_FILE_NAMES.store(0, Ordering::SeqCst);
    let mut decode = true;

    // Count file names and find longest
    //let mut current = &arg_list;
    //while let Some(cell) = current {
    //    if let Some(name) = &cell.name {
    //        let name_str: String = name.to_string();
    //        if name_str == "--" {
    //            decode = false;
    //            current = &cell.link;
    //            continue;
    //        }
    //        
    //        if name_str.starts_with('-') && decode {
    //            current = &cell.link;
    //            continue;
    //        }
    //        
    //        NUM_FILE_NAMES.fetch_add(1, Ordering::SeqCst);
    //        let len = name_str.len() as Int32;
    //        if LONGEST_FILE_NAME.load(Ordering::SeqCst) < len {
    //            LONGEST_FILE_NAME.store(len, Ordering::SeqCst);
    //        }
    //    }
    //    current = &cell.link;
    //}

    NUM_FILE_NAMES.fetch_add(1, Ordering::SeqCst);
    NUM_FILE_NAMES.fetch_add(1, Ordering::SeqCst);

    // Set srcMode
    if NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 {
        srcMode.store(1, Ordering::SeqCst);
    } else {
        srcMode.store(3, Ordering::SeqCst);
    }

    // Set opMode based on program name
    {
        let prog_name = PROG_NAME.lock().unwrap();
        let name_str: String = prog_name.iter().collect();
        
        if name_str.contains("unzip") || name_str.contains("UNZIP") {
            OPMODE.store(2, Ordering::SeqCst);
        } else if name_str.contains("z2cat") || name_str.contains("Z2CAT") 
                || name_str.contains("zcat") || name_str.contains("ZCAT") {
            OPMODE.store(2, Ordering::SeqCst);
            if NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 {
                OPMODE.store(1, Ordering::SeqCst);
            } else {
                OPMODE.store(2, Ordering::SeqCst);
            }
        } else {
            OPMODE.store(1, Ordering::SeqCst);
        }
    }

    // Process command line options
    let mut current = &arg_list;
    while let Some(cell) = current {
        if let Some(name) = &cell.name {
            let name_str: String = name.to_string();
            if name_str == "--" {
                break;
            }
            
            if name_str.starts_with('-') && !name_str.starts_with("--") {
                for c in name_str.chars().skip(1) {
                    match c {
                        'c' => OPMODE.store(2, Ordering::SeqCst),
                        'd' => OPMODE.store(2, Ordering::SeqCst),
                        'z' => OPMODE.store(1, Ordering::SeqCst),
                        'f' => forceOverwrite.store(true, Ordering::SeqCst),
                        't' => OPMODE.store(3, Ordering::SeqCst),
                        'k' => KEEP_INPUT_FILES.store(true, Ordering::SeqCst),
                        's' => smallMode.store(true, Ordering::SeqCst),
                        'q' => noisy.store(false, Ordering::SeqCst),
                        '1'..='9' => BLOCK_SIZE_100K.store(c.to_digit(10).unwrap() as i32, Ordering::SeqCst),
                        'V' | 'L' => {
                            license();
                            process::exit(0);
                        },
                        'v' => { VERBOSITY.fetch_add(1, Ordering::SeqCst); },
                        'h' => {
                            usage(PROG_NAME.lock().unwrap()[0]);
                            process::exit(0);
                        },
                        _ => {
                            eprintln!("{}: Bad flag `{}'", PROG_NAME.lock().unwrap().iter().collect::<String>(), name_str);
                            usage(PROG_NAME.lock().unwrap()[0]);
                            process::exit(1);
                        }
                    }
                }
            }
        }
        current = &cell.link;
    }

    // Process long options
    let mut current = &arg_list;
    while let Some(cell) = current {
        if let Some(name) = &cell.name {
            let name_str: String = name.to_string();
            if name_str == "--" {
                break;
            }
            
            match name_str.as_str() {
                "--stdout" => OPMODE.store(2, Ordering::SeqCst),
                "--decompress" => OPMODE.store(2, Ordering::SeqCst),
                "--compress" => OPMODE.store(1, Ordering::SeqCst),
                "--force" => forceOverwrite.store(true, Ordering::SeqCst),
                "--test" => OPMODE.store(3, Ordering::SeqCst),
                "--keep" => KEEP_INPUT_FILES.store(true, Ordering::SeqCst),
                "--small" => smallMode.store(true, Ordering::SeqCst),
                "--quiet" => noisy.store(false, Ordering::SeqCst),
                "--version" | "--license" => {
                    license();
                    process::exit(0);
                },
                "--exponential" => WORK_FACTOR.store(1, Ordering::SeqCst),
                "--repetitive-best" | "--repetitive-fast" => redundant(Some(name)),
                "--fast" => BLOCK_SIZE_100K.store(1, Ordering::SeqCst),
                "--best" => BLOCK_SIZE_100K.store(9, Ordering::SeqCst),
                "--verbose" => { VERBOSITY.fetch_add(1, Ordering::SeqCst); },
                "--help" => {
                    usage(PROG_NAME.lock().unwrap()[0]);
                    process::exit(0);
                },
                _ if name_str.starts_with("--") => {
                    eprintln!("{}: Bad flag `{}'", PROG_NAME.lock().unwrap().iter().collect::<String>(), name_str);
                    usage(PROG_NAME.lock().unwrap()[0]);
                    process::exit(1);
                },
                _ => {}
            }
        }
        current = &cell.link;
    }

    // Final checks and adjustments
    if VERBOSITY.load(Ordering::SeqCst) > 4 {
        VERBOSITY.store(4, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) == 1 && smallMode.load(Ordering::SeqCst) && BLOCK_SIZE_100K.load(Ordering::SeqCst) > 2 {
        BLOCK_SIZE_100K.store(2, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) == 3 && OPMODE.load(Ordering::SeqCst) == 2 {
        eprintln!("{}: -c and -t cannot be used together.", PROG_NAME.lock().unwrap().iter().collect::<String>());
        process::exit(1);
    }

    if OPMODE.load(Ordering::SeqCst) == 2 && NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 {
        OPMODE.store(1, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) != 1 {
        BLOCK_SIZE_100K.store(0, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) == 3 {
        unsafe {
            libc::signal(libc::SIGINT, mySignalCatcher as usize);
            libc::signal(libc::SIGTERM, mySignalCatcher as usize);
        }
    }

    // Main operation
    println!("OPCODE: {}",OPMODE.load(Ordering::SeqCst));
    match OPMODE.load(Ordering::SeqCst) {
        1 => { // compress
            if srcMode.load(Ordering::SeqCst) == 1 {
                println!("-------------------------------------------here 1");
                compress(None);
            } else {
                println!("-------------------------------------------here 3");
                let mut decode = true;
                let mut current = &arg_list;
                println!("{:?}", arg_list);
                while let Some(cell) = current {
                    println!("while");
                    if let Some(name) = &cell.name {
                        println!("first if in while");
                        let name_str: String = name.to_string();
                        if name_str == "--" {
                            println!("second if in while");
                            decode = false;
                            current = &cell.link;
                            continue;
                        }
                        
                        if name_str.starts_with('-') && decode {
                            println!("third if in while");
                            current = &cell.link;
                            continue;
                        }
                        
                        NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
                        let name_chars: Vec<Char> = name_str.chars().collect();
                        println!("-------------------------------------------here 2");
                        compress(Some(&name_chars));
                    }
                    current = &cell.link;
                }
                //let chars: Vec<char> = "src/sample1.ref".chars().collect();
                //compress(Some(&chars));
            }
        },
        2 => { // uncompress
            UNZ_FAILS_EXIST.store(false, Ordering::SeqCst);
            if OPMODE.load(Ordering::SeqCst) == 1 {
                uncompress(None);
            } else {
                let mut decode = true;
                let mut current = &arg_list;
                while let Some(cell) = current {
                    if let Some(name) = &cell.name {
                        let name_str: String = name.to_string();
                        if name_str == "--" {
                            decode = false;
                            current = &cell.link;
                            continue;
                        }
                        
                        if name_str.starts_with('-') && decode {
                            current = &cell.link;
                            continue;
                        }
                        
                        NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
                        let name_chars: Vec<Char> = name_str.chars().collect();
                        uncompress(Some(&name_chars));
                    }
                    current = &cell.link;
                }
            }
            
            if UNZ_FAILS_EXIST.load(Ordering::SeqCst) {
                setExit(2);
                process::exit(EXIT_VALUE.load(Ordering::SeqCst));
            }
        },
        3 => { // test
            TEST_FAILS_EXIST.store(false, Ordering::SeqCst);
            if OPMODE.load(Ordering::SeqCst) == 1 {
                testf(None);
            } else {
                let mut decode = true;
                let mut current = &arg_list;
                while let Some(cell) = current {
                    if let Some(name) = &cell.name {
                        let name_str: String = name.to_string();
                        if name_str == "--" {
                            decode = false;
                            current = &cell.link;
                            continue;
                        }
                        
                        if name_str.starts_with('-') && decode {
                            current = &cell.link;
                            continue;
                        }
                        
                        NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
                        let name_chars: Vec<Char> = name_str.chars().collect();
                        testf(Some(&name_chars));
                    }
                    current = &cell.link;
                }
            }
            
            if TEST_FAILS_EXIST.load(Ordering::SeqCst) {
                if noisy.load(Ordering::SeqCst) {
                    eprintln!("\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n");
                }
                setExit(2);
                process::exit(EXIT_VALUE.load(Ordering::SeqCst));
            }
        },
        _ => {}
    }

    // Clean up
    let mut current = arg_list;
    while let Some(mut cell) = current {
        current = cell.link.take();
        // Memory is automatically freed when Box goes out of scope
    }

    process::exit(EXIT_VALUE.load(Ordering::SeqCst));
}
