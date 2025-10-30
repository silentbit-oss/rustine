use libc::FILE;
use translate::*;
use std::env;
use std::process;
use std::ffi::CStr;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;
use std::os::raw::c_char;
pub fn main() -> std::process::ExitCode {
    let mut i: Int32 = 0;
    let mut j: Int32 = 0;
    let mut tmp: Vec<Char> = Vec::new();
    let mut tmp_idx: usize = 0;
    let mut argList: Option<Box<Cell>> = None;
    let mut argList_idx: usize = 0;
    let mut aa: Option<Box<Cell>> = None;
    let mut aa_idx: u32 = 0;
    let mut decode: Bool = 1;
    let mut src_mode: Int32 = 0; // Local variable to replace atomic operations

    // Type size checks
    if std::mem::size_of::<Int32>() != 4
        || std::mem::size_of::<u32>() != 4
        || std::mem::size_of::<i16>() != 2
        || std::mem::size_of::<u16>() != 2
        || std::mem::size_of::<Char>() != 1
        || std::mem::size_of::<u8>() != 1
    {
        configError();
    }

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

    i = 0;
    j = 0;

    unsafe {
        libc::signal(libc::SIGSEGV, mySIGSEGVorSIGBUScatcher as usize);
    }

    copyFileName(&mut IN_NAME.lock().unwrap()[..], &['(', 'n', 'o', 'n', 'e', ')']);
    copyFileName(&mut OUT_NAME.lock().unwrap()[..], &['(', 'n', 'o', 'n', 'e', ')']);

    let args: Vec<String> = std::env::args().collect();
    let argv0 = args[0].as_str();
    let mut prog_name_really = PROG_NAME_REALLY.lock().unwrap();
    for (i, c) in argv0.chars().enumerate() {
        prog_name_really[i] = c;
    }
    prog_name_really[argv0.len()] = '\0';

    let mut prog_name = PROG_NAME.lock().unwrap();
    *prog_name = ['\0'; 2000];
    for (i, c) in argv0.chars().enumerate() {
        prog_name[i] = c;
    }
    prog_name[argv0.len()] = '\0';

    for (i, c) in prog_name_really.iter().enumerate() {
        if *c == '/' {
            let remaining = &prog_name_really[i + 1..];
            for (j, c) in remaining.iter().enumerate() {
                prog_name[j] = *c;
            }
            break;
        }
    }

    addFlagsFromEnvVar(&mut argList, &'B');
    addFlagsFromEnvVar(&mut argList, &'B');

    for arg in args.iter().skip(1) {
        // APPEND_FILESPEC implementation would go here
    }

    LONGEST_FILE_NAME.store(7, Ordering::SeqCst);
    NUM_FILE_NAMES.store(0, Ordering::SeqCst);
    decode = 1;

    let mut current = argList.as_ref();
    while let Some(cell) = current {
        if let Some(name) = &cell.name {
            let name_str = unsafe { CStr::from_ptr(name.as_ref() as *const Char as *const c_char) };
            if name_str.to_bytes() == b"--" {
                decode = 0;
                current = cell.link.as_ref();
                continue;
            }

            if name_str.to_bytes()[0] == b'-' && decode != 0 {
                current = cell.link.as_ref();
                continue;
            }

            NUM_FILE_NAMES.fetch_add(1, Ordering::SeqCst);
            let len = name_str.to_bytes().len() as Int32;
            if LONGEST_FILE_NAME.load(Ordering::SeqCst) < len {
                LONGEST_FILE_NAME.store(len, Ordering::SeqCst);
            }
        }
        current = cell.link.as_ref();
    }

    if NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 {
        src_mode = 1; // Direct assignment instead of atomic store
    } else {
        src_mode = 3; // Direct assignment instead of atomic store
    }

    OPMODE.store(1, Ordering::SeqCst);
    let prog_name_str = unsafe { CStr::from_ptr(prog_name.as_ptr() as *const c_char) };
    if prog_name_str.to_bytes().contains(&b"unzip"[0]) || prog_name_str.to_bytes().contains(&b"UNZIP"[0]) {
        OPMODE.store(2, Ordering::SeqCst);
    }
    if prog_name_str.to_bytes().contains(&b"z2cat"[0])
        || prog_name_str.to_bytes().contains(&b"Z2CAT"[0])
        || prog_name_str.to_bytes().contains(&b"zcat"[0])
        || prog_name_str.to_bytes().contains(&b"ZCAT"[0])
    {
        OPMODE.store(2, Ordering::SeqCst);
        src_mode = if NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 {
            1
        } else {
            2
        }; // Direct assignment instead of atomic store
    }

    let mut current = argList.as_ref();
    while let Some(cell) = current {
        helper_main_5(&mut j, cell);
        current = cell.link.as_ref();
    }

    let mut current = argList.as_ref();
    while let Some(cell) = current {
        helper_main_1(&mut aa, &mut decode, &[], argList_idx, &[]);
        current = cell.link.as_ref();
    }

    if VERBOSITY.load(Ordering::SeqCst) > 4 {
        VERBOSITY.store(4, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) == 1
        && smallMode.load(Ordering::SeqCst)
        && BLOCK_SIZE_100K.load(Ordering::SeqCst) > 2
    {
        BLOCK_SIZE_100K.store(2, Ordering::SeqCst);
    }

    if OPMODE.load(Ordering::SeqCst) == 3 && src_mode == 2 { // Direct read instead of atomic load
        eprintln!("{}: -c and -t cannot be used together.", prog_name_str.to_str().unwrap());
        process::exit(1);
    }

    if src_mode == 2 && NUM_FILE_NAMES.load(Ordering::SeqCst) == 0 { // Direct read instead of atomic load
        src_mode = 1; // Direct assignment instead of atomic store
    }

    if OPMODE.load(Ordering::SeqCst) != 1 {
        BLOCK_SIZE_100K.store(0, Ordering::SeqCst);
    }

    if src_mode == 3 { // Direct read instead of atomic load
        unsafe {
            libc::signal(libc::SIGINT, mySignalCatcher as usize);
            libc::signal(libc::SIGTERM, mySignalCatcher as usize);
        }
    }

    match OPMODE.load(Ordering::SeqCst) {
        1 => helper_main_1(&mut aa, &mut decode, &[], argList_idx, &[]),
        2 => helper_main_2(&mut aa_idx, &mut decode, argList.as_ref().unwrap(), argList_idx as u32, argList.as_ref().unwrap()),
        _ => helper_main_3(&mut aa_idx, &mut decode, argList.as_ref().unwrap(), argList_idx as u32, argList.as_ref().unwrap()),
    }

    let mut current = argList;
    while let Some(mut cell) = current {
        let aa2 = cell.link.take();
        current = aa2;
    }

    std::process::ExitCode::from(EXIT_VALUE.load(Ordering::SeqCst) as u8)
}
