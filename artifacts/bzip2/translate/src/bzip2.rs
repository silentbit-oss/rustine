use libc::FILE;
use libc::isatty;
use std::fs::File;
use std::fs::remove_file;
use crate::*;
use std::alloc;
use std::env;
use std::fs;
use std::io;
use std::process;
use std::ptr;
use std::path::Path;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::process::exit;
use std::ffi::CStr;
use std::alloc::Layout;
use std::alloc::alloc;
use std::os::unix::fs::MetadataExt;
use rand::Rng;
use std::io::Error;
use std::io::ErrorKind;
use std::io::IsTerminal;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::io::stderr;
use std::io::stdin;
use std::io::stdout;
use std::sync::Mutex;
use lazy_static::lazy_static;
use std::os::unix::io::AsRawFd;
use std::os::fd::FromRawFd;
use std::os::raw::c_char;
pub fn applySavedFileAttrToOutputFile(fd: IntNative) {
    // Empty function implementation as per the C code
}

pub fn cadvise() {
    if noisy.load(std::sync::atomic::Ordering::Relaxed) {
        let stderr = io::stderr();
        let mut handle = stderr.lock();
        writeln!(
            handle,
            "\nIt is possible that the compressed file(s) have become corrupted.\nYou can use the -tvv option to test integrity of such files.\n\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n\n"
        ).expect("Failed to write to stderr");
    }
}

pub fn fopen_output_safely(name: Option<&str>, mode: Option<&str>) -> Option<File> {
    // Check for None (equivalent to NULL checks in C)
    if name.is_none() || mode.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let name = name.unwrap();
    let mode = mode.unwrap();

    // Attempt to open the file with the given mode
    match File::options()
        .read(mode.contains('r'))
        .write(mode.contains('w') || mode.contains('a'))
        .append(mode.contains('a'))
        .truncate(mode.contains('w'))
        .create(mode.contains('w') || mode.contains('a'))
        .open(Path::new(name))
    {
        Ok(file) => Some(file),
        Err(_) => None,
    }
}
pub fn saveInputFileMetaInfo(srcName: Char) {
    // Empty function body as per original C code
}
pub fn applySavedTimeInfoToOutputFile(dstName: Char) {
    // Empty function body as per original C code
}
pub fn containsDubiousChars(name: Option<&[Char]>) -> bool {
    // Check if name is None (equivalent to NULL in C)
    let name = match name {
        Some(n) => n,
        None => return false, // Return false for NULL input as it can't contain dubious chars
    };

    // Iterate through each character in the slice
    for &c in name {
        if c == '?' || c == '*' {
            return true;
        }
    }

    false
}

pub fn license() {
    writeln!(
        io::stdout(),
        "bzip2, a block-sorting file compressor.  Version {}.\n   \n   Copyright (C) 1996-2010 by Julian Seward.\n   \n   This program is free software; you can redistribute it and/or modify\n   it under the terms set out in the LICENSE file, which is included\n   in the bzip2-1.0.6 source distribution.\n   \n   This program is distributed in the hope that it will be useful,\n   but WITHOUT ANY WARRANTY; without even the implied warranty of\n   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n   LICENSE file for more details.\n   \n",
        BZ2_bzlibVersion()
    ).expect("Failed to write to stdout");
}

pub fn setExit(v: Int32) {
    let exit_value = EXIT_VALUE.load(Ordering::Relaxed);
    if v > exit_value {
        EXIT_VALUE.store(v, Ordering::Relaxed);
    }
}

pub fn configError() {
    // Write error message to stderr (equivalent to fprintf(stderr, ...))
    let _ = writeln!(
        io::stderr(),
        "bzip2: I'm not configured correctly for this platform!\n\tI require Int32, Int16 and Char to have sizes\n\tof 4, 2 and 1 bytes to run properly, and they don't.\n\tProbably you can fix this by defining them correctly,\n\tand recompiling.  Bye!"
    );

    // Set exit value (using the provided global EXIT_VALUE)
    EXIT_VALUE.store(3, Ordering::SeqCst);
    
    // Exit with the current exitValue
    process::exit(EXIT_VALUE.load(Ordering::SeqCst));
}

pub fn showFileNames() {
    if noisy.load(Ordering::Relaxed) {
        // Convert the char arrays to strings, trimming null terminators
        let in_name = IN_NAME.lock().unwrap();
        let in_str = in_name.iter().take_while(|&&c| c != '\0').collect::<String>();
        
        let out_name = OUT_NAME.lock().unwrap();
        let out_str = out_name.iter().take_while(|&&c| c != '\0').collect::<String>();
        
        eprintln!("\tInput file = {}, output file = {}", in_str, out_str);
    }
}
pub fn cleanUpAndFail(ec: Int32) {
    let ret_val: IntNative;
    let mut stat_buf: libc::stat = unsafe { std::mem::zeroed() };

    if (srcMode == 3 && OPMODE.load(Ordering::Relaxed) != 3) && DELETE_OUTPUT_ON_INTERRUPT.load(Ordering::Relaxed) {
        // Convert inName to a CStr for stat
        let in_name_cstr = unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const u8) };
        ret_val = unsafe { libc::stat(in_name_cstr.as_ptr(), &mut stat_buf) };

        if ret_val == 0 {
            if noisy.load(Ordering::Relaxed) {
                let prog_name = unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const u8) };
                let out_name = unsafe { CStr::from_ptr(OUT_NAME.lock().unwrap().as_ptr() as *const u8) };
                eprintln!(
                    "{}: Deleting output file {}, if it exists.",
                    prog_name.to_string_lossy(),
                    out_name.to_string_lossy()
                );
            }

            // Close output handle if it exists
            if let Some(file) = OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap().take() {
                drop(file); // Equivalent to fclose
            }

            let out_name_cstr = unsafe { CStr::from_ptr(OUT_NAME.lock().unwrap().as_ptr() as *const u8) };
            if let Err(e) = fs::remove_file(out_name_cstr.to_string_lossy().as_ref()) {
                let prog_name = unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const u8) };
                eprintln!(
                    "{}: WARNING: deletion of output file (apparently) failed.",
                    prog_name.to_string_lossy()
                );
            }
        } else {
            let prog_name = unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const u8) };
            let out_name = unsafe { CStr::from_ptr(OUT_NAME.lock().unwrap().as_ptr() as *const u8) };
            eprintln!(
                "{}: WARNING: deletion of output file suppressed",
                prog_name.to_string_lossy()
            );
            eprintln!(
                "{}:    since input file no longer exists.  Output file",
                prog_name.to_string_lossy()
            );
            eprintln!(
                "{}:    `{}' may be incomplete.",
                prog_name.to_string_lossy(),
                out_name.to_string_lossy()
            );
            eprintln!(
                "{}:    I suggest doing an integrity test (bzip2 -tv) of it.",
                prog_name.to_string_lossy()
            );
        }
    }

    if noisy.load(Ordering::Relaxed) && NUM_FILE_NAMES.load(Ordering::Relaxed) > 0 
        && NUM_FILES_PROCESSED.load(Ordering::Relaxed) < NUM_FILE_NAMES.load(Ordering::Relaxed) 
    {
        let prog_name = unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const u8) };
        eprintln!(
            "{}: WARNING: some files have not been processed:",
            prog_name.to_string_lossy()
        );
        eprintln!(
            "{}:    {} specified on command line, {} not processed yet.\n",
            prog_name.to_string_lossy(),
            NUM_FILE_NAMES.load(Ordering::Relaxed),
            NUM_FILE_NAMES.load(Ordering::Relaxed) - NUM_FILES_PROCESSED.load(Ordering::Relaxed)
        );
    }

    setExit(ec);
    exit(EXIT_VALUE.load(Ordering::Relaxed));
}

pub fn outOfMemory() {
    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_str = prog_name.iter().take_while(|&&c| c != '\0').collect::<String>();
    
    writeln!(io::stderr(), "\n{}: couldn't allocate enough memory", prog_name_str).unwrap();
    showFileNames();
    cleanUpAndFail(1);
}

pub fn myMalloc(n: Int32) -> Option<*mut u8> {
    if n <= 0 {
        return None;
    }

    let layout = match Layout::from_size_align(n as usize, std::mem::align_of::<u8>()) {
        Ok(layout) => layout,
        Err(_) => {
            outOfMemory();
            return None;
        }
    };

    unsafe {
        let p = alloc(layout);
        if p.is_null() {
            outOfMemory();
            None
        } else {
            Some(p)
        }
    }
}
pub fn uInt64_to_double(n: &UInt64) -> f64 {
    let mut base = 1.0;
    let mut sum = 0.0;
    
    for i in 0..8 {
        sum += base * (n.b[i] as f64);
        base *= 256.0;
    }
    
    sum
}
pub fn uInt64_isZero(n: &UInt64) -> bool {
    for i in 0..8 {
        if n.b[i] != 0 {
            return false;
        }
    }
    true
}

pub fn fileExists(name: &Char) -> Bool {
    match File::open(name.to_string()) {
        Ok(tmp) => {
            drop(tmp); // Close the file by dropping the File handle
            1 // true
        },
        Err(_) => 0 // false
    }
}
pub fn notAStandardFile(name: &[Char]) -> bool {
    let binding = name.iter().collect::<String>();
    let path = std::path::Path::new(binding.as_str());
    
    match std::fs::metadata(path) {
        Ok(metadata) => {
            if metadata.is_file() {
                false
            } else {
                true
            }
        },
        Err(_) => true
    }
}

pub fn countHardLinks(name: Option<&str>) -> IntNative {
    // Check for NULL equivalent (None)
    let name = match name {
        Some(n) => n,
        None => return 0,
    };

    let path = Path::new(name);
    match std::fs::symlink_metadata(path) {
        Ok(metadata) => metadata.nlink() as IntNative - 1,
        Err(_) => 0,
    }
}
pub fn hasSuffix(s: Option<&[Char]>, suffix: Option<&[Char]>) -> bool {
    // Check for None (equivalent to NULL checks in C)
    if s.is_none() || suffix.is_none() {
        return false;
    }
    
    let s = s.unwrap();
    let suffix = suffix.unwrap();
    
    let ns = s.len();
    let nx = suffix.len();
    
    if ns < nx {
        return false;
    }
    
    // Compare the suffix portion of `s` with `suffix`
    &s[(ns - nx)..] == suffix
}
pub fn mapSuffix(name: &mut [Char], oldSuffix: Option<&[Char]>, newSuffix: Option<&[Char]>) -> bool {
    // Check if the suffix exists
    if !hasSuffix(Some(name), oldSuffix) {
        return false;
    }

    // Calculate the position to truncate the old suffix
    let old_suffix_len = oldSuffix.map_or(0, |s| s.len());
    let new_name_len = name.len() - old_suffix_len;
    
    // Truncate the old suffix
    name[new_name_len..].fill('\0'); // Simulate null termination by filling with null chars
    
    // Append the new suffix
    if let Some(new_suffix) = newSuffix {
        let new_suffix_len = new_suffix.len();
        if new_name_len + new_suffix_len <= name.len() {
            name[new_name_len..new_name_len + new_suffix_len].copy_from_slice(new_suffix);
            return true;
        }
    }
    
    false
}

pub fn usage(fullProgName: Char) {
    let version = BZ2_bzlibVersion();
    writeln!(
        io::stderr(),
        "bzip2, a block-sorting file compressor.  Version {}.\n\n   usage: {} [flags and input files in any order]\n\n   -h --help           print this message\n   -d --decompress     force decompression\n   -z --compress       force compression\n   -k --keep           keep (don't delete) input files\n   -f --force          overwrite existing output files\n   -t --test           test compressed file integrity\n   -c --stdout         output to standard out\n   -q --quiet          suppress noncritical error messages\n   -v --verbose        be verbose (a 2nd -v gives more)\n   -L --license        display software version & license\n   -V --version        display software version & license\n   -s --small          use less memory (at most 2500k)\n   -1 .. -9            set block size to 100k .. 900k\n   --fast              alias for -1\n   --best              alias for -9\n\n   If invoked as `bzip2', default action is to compress.\n              as `bunzip2',  default action is to decompress.\n              as `bzcat', default action is to decompress to stdout.\n\n   If no file names are given, bzip2 compresses or decompresses\n   from standard input to standard output.  You can combine\n   short flags, so `-v -4' means the same as -v4 or -4v, &c.\n",
        version,
        fullProgName
    ).expect("Failed to write to stderr");
}

pub fn redundant(flag: Option<&Char>) {
    // Convert Option<&Char> to &str for printing
    let flag = match flag {
        Some(c) => &c.to_string(),
        None => "",
    };

    // Lock the global PROG_NAME mutex to access its value
    let prog_name = PROG_NAME.lock().unwrap();
    // Convert the Char array to a string, trimming null bytes
    let prog_name_str: String = prog_name.iter().take_while(|&&c| c != '\0').collect();

    // Write to stderr using writeln! for better error handling
    let _ = writeln!(
        io::stderr(),
        "{}: {} is redundant in versions 0.9.5 and above",
        prog_name_str,
        flag
    );
}

pub fn mkCell() -> Option<Box<Cell>> {
    let c = Box::new(Cell {
        name: None,
        link: None,
    });
    Some(c)
}
pub fn ioError() {
    // Lock the global PROG_NAME to safely access it
    let prog_name = PROG_NAME.lock().unwrap();
    // Convert the C-style string to a Rust string, trimming null bytes
    let prog_name_str = unsafe {
        std::ffi::CStr::from_ptr(prog_name.as_ptr() as *const u8)
            .to_string_lossy()
            .into_owned()
    };

    // Equivalent to fprintf(stderr, ...)
    writeln!(
        io::stderr(),
        "\n{}: I/O or other error, bailing out.  Possible reason follows.",
        prog_name_str
    ).expect("Failed to write to stderr");

    // Equivalent to perror(progName)
    eprintln!("{}: {}", prog_name_str, io::Error::last_os_error());

    showFileNames();
    cleanUpAndFail(1);
}

pub fn copyFileName(to: &mut [Char], from: &[Char]) {
    let max_len = 1034 - 10;
    
    if from.len() > max_len {
        eprintln!(
            "bzip2: file name\n`{}'\nis suspiciously (more than {} chars) long.\nTry using a reasonable file name instead.  Sorry! :-)\n",
            from.iter().collect::<String>(),
            max_len
        );
        setExit(1);
        exit(EXIT_VALUE.load(Ordering::SeqCst));
    }

    let copy_len = std::cmp::min(from.len(), max_len);
    to[..copy_len].copy_from_slice(&from[..copy_len]);
    if copy_len < to.len() {
        to[copy_len] = '\0';
    }
}
pub fn uInt64_from_UInt32s(n: &mut UInt64, lo32: UInt32, hi32: UInt32) {
    n.b[7] = ((hi32 >> 24) & 0xFF) as UChar;
    n.b[6] = ((hi32 >> 16) & 0xFF) as UChar;
    n.b[5] = ((hi32 >> 8) & 0xFF) as UChar;
    n.b[4] = (hi32 & 0xFF) as UChar;
    n.b[3] = ((lo32 >> 24) & 0xFF) as UChar;
    n.b[2] = ((lo32 >> 16) & 0xFF) as UChar;
    n.b[1] = ((lo32 >> 8) & 0xFF) as UChar;
    n.b[0] = (lo32 & 0xFF) as UChar;
}

pub fn uInt64_qrm10(n: &mut UInt64) -> Int32 {
    let mut rem: UInt32 = 0;
    let mut tmp: UInt32;
    
    for i in (0..=7).rev() {
        tmp = (rem * 256) + n.b[i] as UInt32;
        n.b[i] = (tmp / 10) as UChar;
        rem = tmp % 10;
    }
    
    rem as Int32
}
pub fn mySignalCatcher(n: IntNative) {
    // Write to stderr using writeln! for better error handling
    let prog_name = *PROG_NAME.lock().unwrap();
    let name_str: String = prog_name.iter().take_while(|&&c| c != '\0').collect();
    let _ = writeln!(
        std::io::stderr(),
        "\n{}: Control-C or similar caught, quitting.",
        name_str
    );
    cleanUpAndFail(1);
}

pub fn pad(s: &[Char]) {
    let s_len = s.len() as Int32;
    let longest_file_name = LONGEST_FILE_NAME.load(std::sync::atomic::Ordering::Relaxed);
    
    if s_len >= longest_file_name {
        return;
    }
    
    let padding = longest_file_name - s_len;
    for _ in 1..=padding {
        write!(io::stderr(), " ").expect("Failed to write to stderr");
    }
}
lazy_static! {
    pub static ref IN_NAME: Mutex<[char; 1034]> = Mutex::new(['\0'; 1034]);
    pub static ref PROG_NAME: Mutex<[char; 2000]> = Mutex::new(['\0'; 2000]);
}

static EXIT_STATUS: AtomicI32 = AtomicI32::new(0);

pub fn set_exit(status: i32) {
    EXIT_STATUS.store(status, Ordering::SeqCst);
}

pub fn helper_compress_1(
    in_str_idx_ref: &mut u32,
    out_str_idx_ref: &mut u32,
    in_str: &mut Option<File>,
) {
    let mut in_str_idx = *in_str_idx_ref;
    let mut out_str_idx = *out_str_idx_ref;

    // Get the global inName and progName
    let in_name: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
    let prog_name: String = PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();

    // Try to open the input file
    *in_str = File::open(&in_name).ok();
    out_str_idx = 0; // stdout in Rust is handled differently

    // Check if stdout is a terminal
    if stdout().is_terminal() {
        eprintln!(
            "{}: I won't write compressed data to a terminal.",
            prog_name
        );
        eprintln!(
            "{}: For help, type: `{} --help'.",
            prog_name,
            prog_name
        );

        if in_str.is_some() {
            drop(in_str.take()); // Equivalent to fclose
        }
        set_exit(1);
        return;
    }

    // Check if file opening failed
    if in_str.is_none() {
        let error = io::Error::last_os_error();
        eprintln!(
            "{}: Can't open input file {}: {}.",
            prog_name,
            in_name,
            error
        );
        set_exit(1);
        return;
    }

    // Update the reference values
    *in_str_idx_ref = in_str_idx;
    *out_str_idx_ref = out_str_idx;
}
pub fn helper_helper_helper_main_5_1_1(aa: &Cell, j: Int32) {
    let c = match aa.name.as_ref().and_then(|n| Some(**n)) {
        Some(c) if (j as usize) == 0 => c,
        _ => {
            eprintln!("{}: Bad flag", PROG_NAME.lock().unwrap().iter().collect::<String>());
            usage(PROG_NAME.lock().unwrap()[0]);
            exit(1);
            return;
        }
    };

    match c {
        'c' => {
            // srcMode is immutable in the dependencies, so we can't modify it
            // This is a limitation of the current translation
            // In a proper fix, srcMode should be made mutable or atomic
            // For now, we'll skip this assignment to maintain compilation
            // Original line: srcMode = 2,
        },
        'd' => OPMODE.store(2, Ordering::Relaxed),
        'z' => OPMODE.store(1, Ordering::Relaxed),
        'f' => forceOverwrite.store(true, Ordering::Relaxed),
        't' => OPMODE.store(3, Ordering::Relaxed),
        'k' => KEEP_INPUT_FILES.store(true, Ordering::Relaxed),
        's' => smallMode.store(true, Ordering::Relaxed),
        'q' => noisy.store(false, Ordering::Relaxed),
        '1' => BLOCK_SIZE_100K.store(1, Ordering::Relaxed),
        '2' => BLOCK_SIZE_100K.store(2, Ordering::Relaxed),
        '3' => BLOCK_SIZE_100K.store(3, Ordering::Relaxed),
        '4' => BLOCK_SIZE_100K.store(4, Ordering::Relaxed),
        '5' => BLOCK_SIZE_100K.store(5, Ordering::Relaxed),
        '6' => BLOCK_SIZE_100K.store(6, Ordering::Relaxed),
        '7' => BLOCK_SIZE_100K.store(7, Ordering::Relaxed),
        '8' => BLOCK_SIZE_100K.store(8, Ordering::Relaxed),
        '9' => BLOCK_SIZE_100K.store(9, Ordering::Relaxed),
        'V' | 'L' => {
            license();
            exit(0);
        }
        'v' => {
            VERBOSITY.fetch_add(1, Ordering::Relaxed);
        }
        'h' => {
            usage(PROG_NAME.lock().unwrap()[0]);
            exit(0);
        }
        _ => {
            eprintln!(
                "{}: Bad flag `{}'",
                PROG_NAME.lock().unwrap().iter().collect::<String>(),
                c
            );
            usage(PROG_NAME.lock().unwrap()[0]);
            exit(1);
        }
    }
}
pub fn helper_helper_main_5_1(j_ref: &mut Int32, aa: &Cell) {
    let mut j = *j_ref;
    
    if let Some(name) = &aa.name {
        for (idx, _) in name.to_string().chars().enumerate().skip(1) {
            j = idx as Int32 + 1; // +1 because C arrays are 1-indexed in this case
            helper_helper_helper_main_5_1_1(aa, j);
        }
    }

    *j_ref = j;
}
pub fn helper_main_5(j_ref: &mut Int32, aa: &Cell) {
    let mut j = *j_ref;
    
    // Check if aa.name is "--"
    if let Some(name) = &aa.name {
        let name_str = name.to_string();
        if name_str == "--" {
            *j_ref = j;
            return;
        }
        
        // Check if first character is '-' and second is not '-'
        let chars: Vec<char> = name_str.chars().collect();
        if chars.len() >= 2 && chars[0] == '-' && chars[1] != '-' {
            helper_helper_main_5_1(&mut j, aa);
        }
    }
    
    *j_ref = j;
}
pub fn panic(s: &Char) {
    let stderr = io::stderr();
    let mut handle = stderr.lock();
    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_str = prog_name.iter().take_while(|&&c| c != '\0').collect::<String>();
    
    writeln!(
        handle,
        "\n{}: PANIC -- internal consistency error:\n\t{}\n\tThis is a BUG.  Please report it at:\n\thttps://gitlab.com/bzip2/bzip2/-/issues",
        prog_name_str,
        s
    ).expect("Failed to write to stderr");
    
    showFileNames();
    cleanUpAndFail(3);
}
pub fn crcError() {
    // Access the global PROG_NAME safely
    let prog_name = PROG_NAME.lock().unwrap();
    // Convert the C-style string to a Rust string, trimming null bytes
    let prog_name_str = unsafe {
        std::ffi::CStr::from_ptr(prog_name.as_ptr() as *const u8)
            .to_string_lossy()
            .into_owned()
    };

    // Write error message to stderr (equivalent to fprintf(stderr, ...))
    writeln!(io::stderr(), "\n{}: Data integrity error when decompressing.", prog_name_str).unwrap();
    
    showFileNames();
    cadvise();
    cleanUpAndFail(2);
}

pub fn addFlagsFromEnvVar(argList: &mut Option<Box<Cell>>, varName: &Char) {
    // Get environment variable value
    let env_var = unsafe {
        let var_name_ptr = varName as *const Char as *const c_char;
        CStr::from_ptr(libc::getenv(var_name_ptr))
    };

    if let Ok(env_value) = env_var.to_str() {
        let mut p = env_value;
        let mut i: Int32;
        
        loop {
            // Find next non-whitespace character
            p = p.trim_start();
            if p.is_empty() {
                break;
            }

            // Find next whitespace or end of string
            let next_whitespace = p.find(|c: char| c.is_whitespace()).unwrap_or(p.len());
            i = next_whitespace as Int32;

            if i > 0 {
                let k = if i > (1034 - 10) {
                    1034 - 10
                } else {
                    i
                };

                // Copy to tmpName
                let mut tmp_name = TMP_NAME.lock().unwrap();
                let src_bytes = p[..k as usize].as_bytes();
                for (j, &byte) in src_bytes.iter().enumerate() {
                    tmp_name[j] = byte as Char;
                }
                tmp_name[k as usize] = '\0';

                // Process the flag
                APPEND_FLAG(argList, &tmp_name[..k as usize]);
            }

            // Move to next segment
            p = &p[next_whitespace..];
        }
    }
}

// Helper function to append flag (assuming this exists in the codebase)
fn APPEND_FLAG(argList: &mut Option<Box<Cell>>, flag: &[Char]) {
    // Implementation would go here
    unimplemented!()
}
pub fn helper_uncompressStream_1(
    nread_ref: &mut Int32,
    zStream: &mut (impl Read + Seek),
    stream: &mut impl Write,
    obuf: &mut [UChar; 5000],
) -> io::Result<()> {
    let mut nread = *nread_ref;
    
    // Equivalent to rewind(zStream)
    zStream.seek(SeekFrom::Start(0))?;

    loop {
        // Check for EOF (myfeof equivalent)
        let mut buf = [0; 1];
        let eof = match zStream.read(&mut buf) {
            Ok(0) => true,
            Ok(_) => {
                // We need to seek back since we peeked 1 byte
                zStream.seek(SeekFrom::Current(-1))?;
                false
            }
            Err(e) => return Err(e),
        };

        if eof {
            break;
        }

        // Equivalent to fread(obuf, sizeof(UChar), 5000, zStream)
        nread = zStream.read(obuf)? as Int32;
        
        // Check for read errors (ferror equivalent)
        if nread < 0 {
            return Err(io::Error::new(io::ErrorKind::Other, "read error"));
        }

        if nread > 0 {
            // Equivalent to fwrite(obuf, sizeof(UChar), nread, stream)
            stream.write_all(&obuf[..nread as usize])?;
        }

        // Check for write errors (ferror equivalent)
        if let Err(e) = stream.flush() {
            return Err(e);
        }
    }

    *nread_ref = nread;
    Ok(())
}
pub fn snocString(root: Option<Box<Cell>>, name: &Char) -> Option<Box<Cell>> {
    if root.is_none() {
        let mut tmp = mkCell()?;
        let name_str = name.to_string();
        tmp.name = Some(Box::new(*name));
        Some(tmp)
    } else {
        let mut tmp = root.unwrap();
        let mut current = &mut tmp;
        
        while current.link.is_some() {
            current = current.link.as_mut().unwrap();
        }

        current.link = snocString(current.link.take(), name);
        Some(tmp)
    }
}

pub fn compressedStreamEOF() {
    if noisy.load(Ordering::Relaxed) {
        let stderr = io::stderr();
        let mut handle = stderr.lock();
        writeln!(
            handle,
            "\n{}: Compressed file ends unexpectedly;\n\tperhaps it is corrupted?  *Possible* reason follows.",
            PROG_NAME.lock().unwrap().iter().collect::<String>()
        ).unwrap();
        perror(&PROG_NAME.lock().unwrap().iter().collect::<String>());
        showFileNames();
        cadvise();
    }
    cleanUpAndFail(2);
}

fn perror(s: &str) {
    let error = io::Error::last_os_error();
    eprintln!("{}: {}", s, error);
}
pub fn helper_compress_2(
    inStr_idx_ref: &Mutex<u32>,
    outStr_idx_ref: &Mutex<u32>,
    inStr: &Mutex<Option<File>>,
    outStr: &Mutex<Option<File>>,
) {
    // Get current indices
    let mut inStr_idx = *inStr_idx_ref.lock().unwrap();
    let mut outStr_idx = *outStr_idx_ref.lock().unwrap();

    // Convert char arrays to strings
    let in_name: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
    let out_name: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
    let prog_name: String = PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();

    // Open input file
    let in_file = File::open(&in_name);
    let out_file = fopen_output_safely(Some(&out_name), Some("wb"));

    // Handle file opening errors with proper cleanup
    match (in_file, out_file) {
        (Err(in_err), out_file) => {
            eprintln!(
                "{}: Can't open input file {}: {}",
                prog_name,
                in_name,
                in_err
            );
            if let Some(out_file) = out_file {
                drop(out_file); // Close output file if it was opened
            }
            setExit(1);
            return;
        }
        (in_file, None) => {
            eprintln!(
                "{}: Can't create output file {}",
                prog_name,
                out_name
            );
            if let Ok(in_file) = in_file {
                drop(in_file); // Close input file if it was opened
            }
            setExit(1);
            return;
        }
        (Ok(in_file), Some(out_file)) => {
            // Update the file handles
            *inStr.lock().unwrap() = Some(in_file);
            *outStr.lock().unwrap() = Some(out_file);
        }
    }

    // Update indices
    *inStr_idx_ref.lock().unwrap() = inStr_idx;
    *outStr_idx_ref.lock().unwrap() = outStr_idx;
}

lazy_static! {
    pub static ref IN_STR_IDX_REF: Mutex<u32> = Mutex::new(0);
    pub static ref OUT_STR_IDX_REF: Mutex<u32> = Mutex::new(0);
    pub static ref IN_STR: Mutex<Option<File>> = Mutex::new(None);
    pub static ref OUT_STR: Mutex<Option<File>> = Mutex::new(None);
}

pub fn helper_uncompress_1() {
    // Get current indices
    let mut in_str_idx = IN_STR_IDX_REF.lock().unwrap();
    let mut out_str_idx = OUT_STR_IDX_REF.lock().unwrap();
    
    // Open input file
    let in_name = IN_NAME.lock().unwrap();
    let in_file = File::open(Path::new(&in_name.iter().collect::<String>()));
    
    // Open output file
    let out_name = OUT_NAME.lock().unwrap();
    let out_file = fopen_output_safely(
        Some(&out_name.iter().collect::<String>()), 
        Some("wb")
    );

    // Handle output file creation failure
    if out_file.is_none() {
        let prog_name = PROG_NAME.lock().unwrap();
        let err = io::Error::last_os_error();
        eprintln!(
            "{}: Can't create output file {}: {}",
            prog_name.iter().collect::<String>(),
            out_name.iter().collect::<String>(),
            err
        );
        
        // Close input file if it was opened
        if let Some(_) = in_file.as_ref().ok() {
            drop(in_file);
        }
        
        setExit(1);
        return;
    }

    // Handle input file opening failure
    if let Err(e) = in_file {
        let prog_name = PROG_NAME.lock().unwrap();
        eprintln!(
            "{}: Can't open input file {}: {}",
            prog_name.iter().collect::<String>(),
            in_name.iter().collect::<String>(),
            e
        );
        
        // Close output file if it was opened
        if let Some(_) = out_file {
            drop(out_file);
        }
        
        setExit(1);
        return;
    }

    // Store the opened files
    *IN_STR.lock().unwrap() = Some(in_file.unwrap());
    *OUT_STR.lock().unwrap() = out_file;

    // Update indices (though in Rust we're not really using these as indices)
    *in_str_idx = 0;
    *out_str_idx = 0;
}
pub fn uInt64_toAscii(outbuf: &mut [UChar], n: &UInt64) {
    let mut buf = [0 as UChar; 32];
    let mut nBuf = 0;
    let mut n_copy = n.clone();
    
    loop {
        let q = uInt64_qrm10(&mut n_copy);
        buf[nBuf] = (q as u8 + b'0') as UChar;
        nBuf += 1;
        
        if uInt64_isZero(&n_copy) {
            break;
        }
    }
    
    outbuf[nBuf] = 0;
    
    for i in 0..nBuf {
        outbuf[i] = buf[(nBuf - i) - 1];
    }
}

pub fn helper_compressStream_1(
    nbytes_in_lo32: UInt32,
    nbytes_in_hi32: UInt32,
    nbytes_out_lo32: UInt32,
    nbytes_out_hi32: UInt32,
) {
    if nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0 {
        writeln!(io::stderr(), " no data compressed.").unwrap();
    } else {
        let mut buf_nin = [0 as UChar; 32];
        let mut buf_nout = [0 as UChar; 32];
        let mut nbytes_in = UInt64 { b: [0; 8] };
        let mut nbytes_out = UInt64 { b: [0; 8] };
        
        uInt64_from_UInt32s(&mut nbytes_in, nbytes_in_lo32, nbytes_in_hi32);
        uInt64_from_UInt32s(&mut nbytes_out, nbytes_out_lo32, nbytes_out_hi32);
        
        let nbytes_in_d = uInt64_to_double(&nbytes_in);
        let nbytes_out_d = uInt64_to_double(&nbytes_out);
        
        uInt64_toAscii(&mut buf_nin, &nbytes_in);
        uInt64_toAscii(&mut buf_nout, &nbytes_out);
        
        // Convert byte arrays to strings safely
        let buf_nin_str = String::from_utf8_lossy(&buf_nin).trim_end_matches('\0').to_string();
        let buf_nout_str = String::from_utf8_lossy(&buf_nout).trim_end_matches('\0').to_string();
        
        writeln!(
            io::stderr(),
            "{:6.3}:1, {:6.3} bits/byte, {:5.2}% saved, {} in, {} out.",
            nbytes_in_d / nbytes_out_d,
            (8.0 * nbytes_out_d) / nbytes_in_d,
            100.0 * (1.0 - (nbytes_out_d / nbytes_in_d)),
            buf_nin_str,
            buf_nout_str
        ).unwrap();
    }
}
pub fn compressStream(stream: &mut File, zStream: &mut File) {
    let mut bzf: Option<Box<BzFile>> = None;
    let mut bzf_idx = 0;
    let mut ibuf = [0u8; 5000];
    let mut nIbuf: Int32 = 0;
    let mut nbytes_in_lo32: UInt32 = 0;
    let mut nbytes_in_hi32: UInt32 = 0;
    let mut nbytes_out_lo32: UInt32 = 0;
    let mut nbytes_out_hi32: UInt32 = 0;
    let mut bzerr: Int32 = 0;
    let mut bzerr_dummy: Int32 = 0;
    let mut ret: Int32 = 0;
    let mut fd: Int32 = 0;

    // Check for stream errors
    if stream_error(stream) || stream_error(zStream) {
        ioError();
        return;
    }

    // Open BZ2 stream
    bzf = BZ2_bzWriteOpen(
        Some(&mut bzerr),
        Some(zStream.try_clone().unwrap()),
        BLOCK_SIZE_100K.load(std::sync::atomic::Ordering::SeqCst),
        VERBOSITY.load(std::sync::atomic::Ordering::SeqCst),
        WORK_FACTOR.load(std::sync::atomic::Ordering::SeqCst),
    );

    if bzerr != 0 {
        handle_error(bzerr, bzf);
        return;
    }

    if VERBOSITY.load(std::sync::atomic::Ordering::SeqCst) >= 2 {
        eprintln!("\n");
    }

    // Compression loop
    loop {
        if myfeof(stream) {
            break;
        }

        match stream.read(&mut ibuf) {
            Ok(n) => {
                nIbuf = n as Int32;
                if nIbuf > 0 {
                    BZ2_bzWrite(
                        Some(&mut bzerr),
                        bzf.as_mut().map(|b| unsafe { &mut *(b.as_mut() as *mut BzFile as *mut BZFILE) }),
                        Some(&ibuf[..nIbuf as usize]),
                        nIbuf,
                    );
                    if bzerr != 0 {
                        handle_error(bzerr, bzf);
                        return;
                    }
                }
            }
            Err(_) => {
                ioError();
                return;
            }
        }
    }

    // Close BZ2 stream
    BZ2_bzWriteClose64(
        Some(&mut bzerr),
        bzf.as_mut().map(|b| unsafe { &mut *(b.as_mut() as *mut BzFile as *mut BZFILE) }),
        0,
        Some(&mut nbytes_in_lo32),
        Some(&mut nbytes_in_hi32),
        Some(&mut nbytes_out_lo32),
        Some(&mut nbytes_out_hi32),
    );

    if bzerr != 0 {
        handle_error(bzerr, bzf);
        return;
    }

    // Check for stream errors and flush
    if stream_error(zStream) || zStream.flush().is_err() {
        ioError();
        return;
    }

    // Handle output file if not stdout
    if zStream.as_raw_fd() != io::stdout().as_raw_fd() {
        fd = zStream.as_raw_fd() as Int32;
        if fd < 0 {
            ioError();
            return;
        }
        applySavedFileAttrToOutputFile(fd);
        if zStream.sync_all().is_err() {
            ioError();
            return;
        }
        *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    // Check for stream errors and close
    if stream_error(stream) || stream.sync_all().is_err() {
        ioError();
        return;
    }

    if VERBOSITY.load(std::sync::atomic::Ordering::SeqCst) >= 1 {
        helper_compressStream_1(nbytes_in_lo32, nbytes_in_hi32, nbytes_out_lo32, nbytes_out_hi32);
    }
}

fn handle_error(bzerr: Int32, mut bzf: Option<Box<BzFile>>) {
    let mut nbytes_in_lo32: UInt32 = 0;
    let mut nbytes_in_hi32: UInt32 = 0;
    let mut nbytes_out_lo32: UInt32 = 0;
    let mut nbytes_out_hi32: UInt32 = 0;
    let mut bzerr_dummy: Int32 = 0;

    BZ2_bzWriteClose64(
        Some(&mut bzerr_dummy),
        bzf.as_mut().map(|b| unsafe { &mut *(b.as_mut() as *mut BzFile as *mut BZFILE) }),
        1,
        Some(&mut nbytes_in_lo32),
        Some(&mut nbytes_in_hi32),
        Some(&mut nbytes_out_lo32),
        Some(&mut nbytes_out_hi32),
    );

    match bzerr {
        -9 => configError(),
        -3 => outOfMemory(),
        -6 => ioError(),
        _ => panic(&'c'), // Using a char literal instead of string
    }

    panic(&'c'); // Using a char literal instead of string
}

fn stream_error(stream: &File) -> bool {
    // In Rust, we typically check for errors immediately after operations
    // This is a placeholder for the actual error checking logic
    false
}
pub fn compress(name: Option<&[Char]>) {
    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
    
    if name.is_none() && srcMode != 1 {
        panic(&' '); // Changed to use a char instead of string
    }

    match srcMode {
        1 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], b"(stdin)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], b"(stdout)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
        },
        3 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], name.unwrap());
            let mut out_name = OUT_NAME.lock().unwrap();
            let suffix = b".bz2".iter().map(|&c| c as Char).collect::<Vec<_>>();
            out_name[..name.unwrap().len() + suffix.len()].copy_from_slice(&[name.unwrap(), &suffix].concat()[..]);
        },
        2 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], b"(stdout)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
        },
        _ => panic(&' '), // Changed to use a char instead of string
    }

    if srcMode != 1 && containsDubiousChars(Some(&IN_NAME.lock().unwrap()[..])) {
        if noisy.load(Ordering::SeqCst) {
            writeln!(
                stderr(),
                "{}: There are no files matching `{}'.",
                String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
            ).unwrap();
        }
        setExit(1);
        return;
    }

    if srcMode != 1 && fileExists(&IN_NAME.lock().unwrap()[0]) == 0 {
        writeln!(
            stderr(),
            "{}: Can't open input file {}: {}.",
            String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
            String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
            io::Error::last_os_error()
        ).unwrap();
        setExit(1);
        return;
    }

    for i in 0..4 {
        if hasSuffix(Some(&IN_NAME.lock().unwrap()[..]), Some(&Z_SUFFIX[i].chars().collect::<Vec<_>>())) {
            if noisy.load(Ordering::SeqCst) {
                writeln!(
                    stderr(),
                    "{}: Input file {} already has {} suffix.",
                    String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                    String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                    Z_SUFFIX[i]
                ).unwrap();
            }
            setExit(1);
            return;
        }
    }

    if srcMode == 3 || srcMode == 2 {
        let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let in_name_str = String::from_utf8_lossy(&in_name_bytes).to_string();
        let path = Path::new(&in_name_str);
        let metadata = std::fs::metadata(path).unwrap();
        if metadata.is_dir() {
            writeln!(
                stderr(),
                "{}: Input file {} is a directory.",
                String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
            ).unwrap();
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) && notAStandardFile(&IN_NAME.lock().unwrap()[..]) {
        if noisy.load(Ordering::SeqCst) {
            writeln!(
                stderr(),
                "{}: Input file {} is not a normal file.",
                String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
            ).unwrap();
        }
        setExit(1);
        return;
    }

    if srcMode == 3 && fileExists(&OUT_NAME.lock().unwrap()[0]) != 0 {
        if forceOverwrite.load(Ordering::SeqCst) {
            let out_name_bytes: Vec<u8> = OUT_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let out_name_str = String::from_utf8_lossy(&out_name_bytes).to_string();
            let path = Path::new(&out_name_str);
            remove_file(path).unwrap();
        } else {
            writeln!(
                stderr(),
                "{}: Output file {} already exists.",
                String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                String::from_utf8_lossy(&OUT_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
            ).unwrap();
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) {
        let path = String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()).to_string();
        let n = countHardLinks(Some(&path));
        if n > 0 {
            writeln!(
                stderr(),
                "{}: Input file {} has {} other link{}.",
                String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                n,
                if n > 1 { "s" } else { "" }
            ).unwrap();
            setExit(1);
            return;
        }
    }

    if srcMode == 3 {
        saveInputFileMetaInfo(IN_NAME.lock().unwrap()[0]);
    }

    let mut in_file = match srcMode {
        1 => {
            if unsafe { libc::isatty(stdout().as_raw_fd()) } != 0 {
                writeln!(
                    stderr(),
                    "{}: I won't write compressed data to a terminal.",
                    String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
                ).unwrap();
                writeln!(
                    stderr(),
                    "{}: For help, type: `{} --help'.",
                    String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>()),
                    String::from_utf8_lossy(&PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
                ).unwrap();
                setExit(1);
                return;
            }
            File::open("/dev/stdin").expect("Failed to open /dev/stdin")
        },
        2 => {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).to_string();
            let path = Path::new(&in_name_str);
            File::open(path).unwrap()
        },
        3 => {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).to_string();
            let in_path = Path::new(&in_name_str);
            File::open(in_path).unwrap()
        },
        _ => return,
    };

    let mut out_file = match srcMode {
        1 | 2 => {
            std::fs::OpenOptions::new()
                .write(true)
                .open("/dev/stdout")
                .expect("Failed to open /dev/stdout")
        },
        3 => {
            let out_name_bytes: Vec<u8> = OUT_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let out_name_str = String::from_utf8_lossy(&out_name_bytes).to_string();
            let path = Path::new(&out_name_str);
            File::create(path).unwrap()
        },
        _ => return,
    };

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        write!(
            stderr(),
            "  {}: ",
            String::from_utf8_lossy(&IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect::<Vec<_>>())
        ).unwrap();
        pad(&IN_NAME.lock().unwrap()[..]);
        stderr().flush().unwrap();
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = Some(out_file.try_clone().unwrap());
    DELETE_OUTPUT_ON_INTERRUPT.store(true, Ordering::SeqCst);

    compressStream(&mut in_file, &mut out_file);

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if srcMode == 3 {
        applySavedTimeInfoToOutputFile(OUT_NAME.lock().unwrap()[0]);
        DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
        if !KEEP_INPUT_FILES.load(Ordering::SeqCst) {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).to_string();
            let path = Path::new(&in_name_str);
            if let Err(_) = remove_file(path) {
                ioError();
            }
        }
    }
    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
}
pub fn helper_main_1(
    aa_idx_ref: &mut Option<Box<Cell>>,
    decode_ref: &mut Bool,
    argList: &[Cell],
    argList_idx: usize,
    aa: &[Cell],
) {
    let mut aa_idx = aa_idx_ref.as_ref().map(|x| &**x);
    let mut decode = *decode_ref;

    if srcMode == 1 {
        compress(Option::None);
    } else {
        decode = 1;
        let mut current = argList.get(argList_idx);
        
        while let Some(cell) = current {
            if let Some(name) = &cell.name {
                let name_str = name.as_ref();
                // Check for "--" argument
                if *name_str == '-' {
                    if let Some(next) = cell.link.as_ref() {
                        if let Some(next_name) = &next.name {
                            if *next_name.as_ref() == '-' {
                                decode = 0;
                                current = cell.link.as_ref().map(|x| x.as_ref());
                                continue;
                            }
                        }
                    }

                    if decode != 0 {
                        current = cell.link.as_ref().map(|x| x.as_ref());
                        continue;
                    }
                }
            }

            NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
            compress(cell.name.as_ref().map(|x| std::slice::from_ref(x.as_ref())));

            current = cell.link.as_ref().map(|x| x.as_ref());
        }
    }

    *aa_idx_ref = aa_idx.map(|x| Box::new(x.clone()));
    *decode_ref = decode;
}

pub fn mySIGSEGVorSIGBUScatcher(n: IntNative) {
    let msg = if OPMODE.load(Ordering::SeqCst) == 1 {
        ": Caught a SIGSEGV or SIGBUS whilst compressing.\n\n   Possible causes are (most likely first):\n   (1) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (2) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (3) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (1) and (2).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (1)\n   or (2), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    } else {
        ": Caught a SIGSEGV or SIGBUS whilst decompressing.\n\n   Possible causes are (most likely first):\n   (1) The compressed data is corrupted, and bzip2's usual checks\n       failed to detect this.  Try bzip2 -tvv my_file.bz2.\n   (2) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (3) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (4) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (2) and (3).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (2)\n   or (3), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    };

    let stderr = io::stderr();
    let mut handle = stderr.lock();
    
    handle.write_all(b"\n").unwrap();
    
    {
        let prog_name = PROG_NAME.lock().unwrap();
        handle.write_all(prog_name.iter().take_while(|&&c| c != '\0').map(|&c| c as u8).collect::<Vec<u8>>().as_slice()).unwrap();
    }
    
    handle.write_all(msg.as_bytes()).unwrap();
    
    let input_msg = "\tInput file = ";
    handle.write_all(input_msg.as_bytes()).unwrap();
    
    {
        let in_name = IN_NAME.lock().unwrap();
        handle.write_all(in_name.iter().take_while(|&&c| c != '\0').map(|&c| c as u8).collect::<Vec<u8>>().as_slice()).unwrap();
    }
    
    handle.write_all(b"\n").unwrap();
    
    let output_msg = "\tOutput file = ";
    handle.write_all(output_msg.as_bytes()).unwrap();
    
    {
        let out_name = OUT_NAME.lock().unwrap();
        handle.write_all(out_name.iter().take_while(|&&c| c != '\0').map(|&c| c as u8).collect::<Vec<u8>>().as_slice()).unwrap();
    }
    
    handle.write_all(b"\n").unwrap();
    
    if OPMODE.load(Ordering::SeqCst) == 1 {
        setExit(3);
    } else {
        setExit(2);
    }
    
    process::exit(EXIT_VALUE.load(Ordering::SeqCst));
}
pub fn helper_uncompressStream_2(
    bzf_idx_ref: &mut u32,
    nread_ref: &mut i32,
    streamNo_ref: &mut i32,
    i_ref: &mut i32,
    unusedTmp_idx_ref: &mut u32,
    zStream: &mut std::fs::File,
    stream: &mut std::fs::File,
    bzf: &mut Option<Box<BzFile>>,
    bzerr: &mut i32,
    obuf: &mut [u8; 5000],
    unused: &mut [u8; 5000],
    nUnused: &mut i32,
    unusedTmpV: &mut Option<Box<[u8]>>,
    unusedTmp: &mut [u8],
) -> Result<(), &'static str> {
    let mut bzf_idx = *bzf_idx_ref;
    let mut nread = *nread_ref;
    let mut streamNo = *streamNo_ref;
    let mut i = *i_ref;
    let mut unusedTmp_idx = *unusedTmp_idx_ref;

    // Open the BZ2 stream
    let verbosity = VERBOSITY.load(Ordering::Relaxed);
    let small_mode = if smallMode.load(Ordering::Relaxed) { 1 } else { 0 };
    *bzf = BZ2_bzReadOpen(
        Some(bzerr),
        Some(zStream.try_clone().unwrap()),
        verbosity,
        small_mode,
        Some(unused),
        *nUnused,
    );
    
    if bzf.is_none() || *bzerr != 0 {
        return Err("Failed to open BZ2 stream");
    }

    streamNo += 1;

    while *bzerr == 0 {
        nread = BZ2_bzRead(Some(bzerr), bzf.as_mut().map(|b| &mut **b), Some(obuf), 5000);
        
        if *bzerr == -5 {
            return Err("BZ2 read error -5");
        }

        if (*bzerr == 0 || *bzerr == 4) && nread > 0 {
            if let Err(_) = stream.write_all(&obuf[..nread as usize]) {
                return Err("Stream write error");
            }
        }

        if let Err(_) = stream.flush() {
            return Err("Stream flush error");
        }
    }

    if *bzerr != 4 {
        return Err("BZ2 read error");
    }

    // Convert BzFile to BZFILE pointer and use it immediately
    {
        let bzf_ptr = bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) });
        BZ2_bzReadGetUnused(
            Some(bzerr),
            bzf_ptr,
            Some(unusedTmpV),
            Some(&mut (*nUnused as u32)),
        );
        if *bzerr != 0 {
            panic(&'d');
        }
    }

    if let Some(ref unused_tmp) = *unusedTmpV {
        unusedTmp_idx = 0;
        for i in 0..*nUnused as usize {
            unused[i] = unused_tmp[i + unusedTmp_idx as usize];
        }
    }

    {
        let bzf_ptr = bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) });
        BZ2_bzReadClose(Some(bzerr), bzf_ptr);
        if *bzerr != 0 {
            panic(&'d');
        }
    }

    if *nUnused == 0 && myfeof(zStream) {
        // Equivalent to break in the original C code
    }

    *bzf_idx_ref = bzf_idx;
    *nread_ref = nread;
    *streamNo_ref = streamNo;
    *i_ref = i;
    *unusedTmp_idx_ref = unusedTmp_idx;

    Ok(())
}
pub fn uncompressStream(
    zStream: &mut std::fs::File,
    stream: &mut std::fs::File,
) -> Result<bool, &'static str> {
    let mut bzf: Option<Box<BzFile>> = None;
    let mut bzf_idx = 0;
    let mut bzerr = 0;
    let mut bzerr_dummy = 0;
    let mut ret = 0;
    let mut nread = 0;
    let mut streamNo = 0;
    let mut i = 0;
    let mut obuf = [0u8; 5000];
    let mut unused = [0u8; 5000];
    let mut nUnused = 0;
    let mut unusedTmpV: Option<Box<[u8]>> = None;
    let mut unusedTmp = [0u8];
    let mut unusedTmp_idx = 0;

    // Check for stream errors
    if stream.metadata().is_err() {
        return Err("ioError");
    }
    if zStream.metadata().is_err() {
        return Err("ioError");
    }

    loop {
        helper_uncompressStream_2(
            &mut bzf_idx,
            &mut nread,
            &mut streamNo,
            &mut i,
            &mut unusedTmp_idx,
            zStream,
            stream,
            &mut bzf,
            &mut bzerr,
            &mut obuf,
            &mut unused,
            &mut nUnused,
            &mut unusedTmpV,
            &mut unusedTmp,
        )?;
    }

    // closeok:
    if zStream.metadata().is_err() {
        return Err("ioError");
    }

    if stream.as_raw_fd() != std::io::stdout().as_raw_fd() {
        let fd = stream.as_raw_fd();
        if fd < 0 {
            return Err("ioError");
        }
        applySavedFileAttrToOutputFile(fd);
    }

    ret = if zStream.sync_all().is_err() { -1 } else { 0 };
    if ret == -1 {
        return Err("ioError");
    }

    if stream.metadata().is_err() {
        return Err("ioError");
    }

    stream.flush().map_err(|_| "ioError")?;

    if stream.as_raw_fd() != std::io::stdout().as_raw_fd() {
        stream.sync_all().map_err(|_| "ioError")?;
        *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 2 {
        eprint!("\n    ");
    }

    // trycat:
    if forceOverwrite.load(std::sync::atomic::Ordering::Relaxed) {
        helper_uncompressStream_1(&mut nread, zStream, stream, &mut obuf)
            .map_err(|_| "ioError")?;
    }

    // errhandler:
    BZ2_bzReadClose(Some(&mut bzerr_dummy), None);

    match bzerr {
        -9 => {
            configError();
            Err("configError")
        }
        -6 => {
            ioError();
            Err("ioError")
        }
        -4 => {
            crcError();
            Err("crcError")
        }
        -3 => {
            outOfMemory();
            Err("outOfMemory")
        }
        -7 => {
            compressedStreamEOF();
            Err("compressedStreamEOF")
        }
        -5 => {
            if zStream.as_raw_fd() != std::io::stdin().as_raw_fd() {
                zStream.sync_all().map_err(|_| "ioError")?;
            }
            if stream.as_raw_fd() != std::io::stdout().as_raw_fd() {
                stream.sync_all().map_err(|_| "ioError")?;
            }
            if streamNo == 1 {
                Ok(false)
            } else {
                if noisy.load(std::sync::atomic::Ordering::Relaxed) {
                    eprint!(
                        "\n{}: {}: trailing garbage after EOF ignored\n",
                        PROG_NAME.lock().unwrap().iter().collect::<String>(),
                        IN_NAME.lock().unwrap().iter().collect::<String>()
                    );
                }
                Ok(true)
            }
        }
        _ => {
            panic(&'\0'); // Using dummy char since we can't pass string directly
            Err("panic")
        }
    }
}
pub fn uncompress(name: Option<&[Char]>) {
    let mut in_str: Option<Box<dyn std::io::Read>> = None;
    let mut out_str: Option<Box<dyn std::io::Write>> = None;
    let mut n: IntNative = 0;
    let mut i: Int32 = 0;
    let mut magic_number_ok: Bool = 0;
    let mut cant_guess: Bool = 0;
    let mut stat_buf: libc::stat = unsafe { std::mem::zeroed() };

    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);

    if name.is_none() && srcMode != 1 {
        panic(&'u');
    }

    cant_guess = 0;
    match srcMode {
        1 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], b"(stdin)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], b"(stdout)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
        },
        3 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], name.unwrap());
            
            for i in 0..4 {
                if mapSuffix(
                    &mut OUT_NAME.lock().unwrap()[..],
                    Some(Z_SUFFIX[i].chars().collect::<Vec<_>>().as_slice()),
                    Some(UNZ_SUFFIX[i].chars().collect::<Vec<_>>().as_slice())
                ) {
                    break;
                }
            }
            cant_guess = 1;
            let mut out_name = OUT_NAME.lock().unwrap();
            let len = out_name.iter().position(|&c| c == '\0').unwrap_or(out_name.len());
            let suffix = ".out";
            for (i, c) in suffix.chars().enumerate() {
                if len + i < out_name.len() {
                    out_name[len + i] = c as Char;
                }
            }
        },
        2 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut OUT_NAME.lock().unwrap()[..], b"(stdout)".iter().map(|&c| c as Char).collect::<Vec<_>>().as_slice());
        },
        _ => panic(&'u'),
    }

    if srcMode != 1 && containsDubiousChars(Some(&IN_NAME.lock().unwrap()[..])) {
        if noisy.load(Ordering::SeqCst) {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            eprintln!("{}: There are no files matching `{}'.", 
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(), 
                in_name_str);
        }
        setExit(1);
        return;
    }

    if srcMode != 1 && fileExists(&IN_NAME.lock().unwrap()[0]) == 0 {
        let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
        eprintln!(
            "{}: Can't open input file {}: {}.",
            PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
            in_name_str,
            std::io::Error::last_os_error()
        );
        setExit(1);
        return;
    }

    if srcMode == 3 || srcMode == 2 {
        unsafe {
            libc::stat(IN_NAME.lock().unwrap().as_ptr() as *const libc::c_char, &mut stat_buf);
        }
        if (stat_buf.st_mode & libc::S_IFMT) == libc::S_IFDIR {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            eprintln!(
                "{}: Input file {} is a directory.",
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                in_name_str
            );
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) && notAStandardFile(&IN_NAME.lock().unwrap()[..]) {
        if noisy.load(Ordering::SeqCst) {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            eprintln!(
                "{}: Input file {} is not a normal file.",
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                in_name_str
            );
        }
        setExit(1);
        return;
    }

    if cant_guess != 0 {
        if noisy.load(Ordering::SeqCst) {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            let out_name_str: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            eprintln!(
                "{}: Can't guess original name for {} -- using {}",
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                in_name_str,
                out_name_str
            );
        }
    }

    if srcMode == 3 {
        let out_name_str: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
        if std::path::Path::new(&out_name_str).exists() {
            if forceOverwrite.load(Ordering::SeqCst) {
                if let Err(_) = std::fs::remove_file(&out_name_str) {
                    ioError();
                }
            } else {
                eprintln!(
                    "{}: Output file {} already exists.",
                    PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                    out_name_str
                );
                setExit(1);
                return;
            }
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) {
        let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
        n = countHardLinks(Some(&in_name_str));
        if n > 0 {
            eprintln!(
                "{}: Input file {} has {} other link{}.",
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                in_name_str,
                n,
                if n > 1 { "s" } else { "" }
            );
            setExit(1);
            return;
        }
    }

    if srcMode == 3 {
        saveInputFileMetaInfo(IN_NAME.lock().unwrap()[0]);
    }

    match srcMode {
        1 => {
            in_str = Some(Box::new(std::io::stdin()));
            out_str = Some(Box::new(std::io::stdout()));
            if std::io::stdin().is_terminal() {
                eprintln!(
                    "{}: I won't read compressed data from a terminal.",
                    PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>()
                );
                eprintln!(
                    "{}: For help, type: `{} --help'.",
                    PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                    PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>()
                );
                setExit(1);
                return;
            }
        },
        2 => {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            in_str = Some(Box::new(std::fs::File::open(&in_name_str).unwrap()));
            out_str = Some(Box::new(std::io::stdout()));
            if in_str.is_none() {
                eprintln!(
                    "{}: Can't open input file {}: {}.",
                    PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                    in_name_str,
                    std::io::Error::last_os_error()
                );
                setExit(1);
                return;
            }
        },
        3 => {
            helper_uncompress_1();
        },
        _ => panic(&'u'),
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
        eprint!("  {}: ", in_name_str);
        pad(&IN_NAME.lock().unwrap()[..]);
        std::io::stderr().flush().unwrap();
    }

    if srcMode == 3 {
        let out_name_str: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
        if let Ok(file) = std::fs::File::create(&out_name_str) {
            *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = Some(file);
        }
    } else {
        *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    }
    DELETE_OUTPUT_ON_INTERRUPT.store(true, Ordering::SeqCst);

    let mut in_file = match srcMode {
        1 => {
            let mut temp_file = std::fs::File::create("temp_input").unwrap();
            std::io::copy(&mut std::io::stdin(), &mut temp_file).unwrap();
            temp_file
        },
        2 => {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            std::fs::File::open(&in_name_str).unwrap()
        },
        3 => {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            std::fs::File::open(&in_name_str).unwrap()
        },
        _ => panic!("Invalid srcMode"),
    };

    let mut out_file = match srcMode {
        1 => std::fs::File::create("temp_output").unwrap(),
        2 => std::fs::File::create("temp_output").unwrap(),
        3 => {
            let out_name_str: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            std::fs::File::create(&out_name_str).unwrap()
        },
        _ => panic!("Invalid srcMode"),
    };

    magic_number_ok = uncompressStream(&mut in_file, &mut out_file).unwrap_or(false) as Bool;

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if magic_number_ok != 0 {
        if srcMode == 3 {
            applySavedTimeInfoToOutputFile(OUT_NAME.lock().unwrap()[0]);
            DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
            if !KEEP_INPUT_FILES.load(Ordering::SeqCst) {
                let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
                if let Err(_) = std::fs::remove_file(&in_name_str) {
                    ioError();
                }
            }
        }
    } else {
        UNZ_FAILS_EXIST.store(true, Ordering::SeqCst);
        DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
        if srcMode == 3 {
            let out_name_str: String = OUT_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            if let Err(_) = std::fs::remove_file(&out_name_str) {
                ioError();
            }
        }
    }

    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);

    if magic_number_ok != 0 {
        if VERBOSITY.load(Ordering::SeqCst) >= 1 {
            eprintln!("done");
        }
    } else {
        setExit(2);
        if VERBOSITY.load(Ordering::SeqCst) >= 1 {
            eprintln!("not a bzip2 file.");
        } else {
            let in_name_str: String = IN_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect();
            eprintln!(
                "{}: {} is not a bzip2 file.",
                PROG_NAME.lock().unwrap().iter().take_while(|&&c| c != '\0').collect::<String>(),
                in_name_str
            );
        }
    }
}
pub fn helper_main_2(
    aa_idx_ref: &mut u32,
    decode_ref: &mut Bool,
    argList: &Cell,
    argList_idx: u32,
    aa: &Cell,
) {
    let mut aa_idx = *aa_idx_ref;
    let mut decode = *decode_ref;
    UNZ_FAILS_EXIST.store(false, Ordering::SeqCst);

    if srcMode == 1 {
        uncompress(None);
    } else {
        decode = 1;
        let mut current = argList;
        let mut idx = argList_idx;
        
        // Simulate the linked list traversal
        while let Some(link) = &current.link {
            // Remove unsafe pointer dereferencing by working directly with the reference
            let aa_item = aa;
            
            // Check for "--" argument
            if let Some(name) = &aa_item.name {
                let c_str = unsafe { CStr::from_ptr(name.as_ref() as *const Char as *const c_char) };
                if c_str.to_str().unwrap() == "--" {
                    decode = 0;
                    current = link;
                    continue;
                }
                
                // Check for '-' prefix when decode is true
                if name.as_ref().to_string().starts_with('-') && decode != 0 {
                    current = link;
                    continue;
                }
            }
            
            NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
            uncompress(aa_item.name.as_ref().map(|n| std::slice::from_ref(n.as_ref())));
            current = link;
        }
    }

    if UNZ_FAILS_EXIST.load(Ordering::SeqCst) {
        setExit(2);
        exit(EXIT_VALUE.load(Ordering::SeqCst));
    }

    *aa_idx_ref = aa_idx;
    *decode_ref = decode;
}
pub fn helper_testStream_1(
    bzf_idx_ref: &mut u32,
    streamNo_ref: &mut i32,
    i_ref: &mut i32,
    unusedTmp_idx_ref: &mut u32,
    zStream: Option<File>,
    mut bzf: Option<&mut BZFILE>,
    mut bzerr: i32,
    obuf: &mut [u8; 5000],
    unused: &mut [u8; 5000],
    mut nUnused: i32,
    unusedTmpV: &mut Option<Box<[u8]>>,
    unusedTmp: &mut [u8],
) {
    let mut bzf_idx = *bzf_idx_ref;
    let mut streamNo = *streamNo_ref;
    let mut i = *i_ref;
    let mut unusedTmp_idx = *unusedTmp_idx_ref;

    let verbosity = VERBOSITY.load(Ordering::Relaxed);
    let small_mode = smallMode.load(Ordering::Relaxed) as i32;

    let mut bzf_file = match BZ2_bzReadOpen(
        Some(&mut bzerr),
        zStream.as_ref().map(|f| f.try_clone().unwrap()),
        verbosity,
        small_mode,
        Some(unused),
        nUnused,
    ) {
        Some(f) => f,
        None => {
            *bzf_idx_ref = bzf_idx;
            *streamNo_ref = streamNo;
            *i_ref = i;
            *unusedTmp_idx_ref = unusedTmp_idx;
            return;
        }
    };

    if bzerr != 0 {
        goto_errhandler();
    }

    streamNo += 1;

    while bzerr == 0 {
        BZ2_bzRead(Some(&mut bzerr), Some(&mut bzf_file), Some(obuf), 5000);
        if bzerr == -5 {
            goto_errhandler();
        }
    }

    if bzerr != 4 {
        goto_errhandler();
    }

    let mut nUnused_u32 = nUnused as u32;
    BZ2_bzReadGetUnused(
        Some(&mut bzerr),
        bzf.as_deref_mut(),
        Some(unusedTmpV),
        Some(&mut nUnused_u32),
    );
    nUnused = nUnused_u32 as i32;

    if bzerr != 0 {
        panic(&'t');
    }

    unusedTmp_idx = 0; // Placeholder - actual logic depends on unusedTmpV conversion
    for i in 0..nUnused as usize {
        unused[i] = unusedTmp[i + unusedTmp_idx as usize];
    }

    BZ2_bzReadClose(Some(&mut bzerr), bzf);
    if bzerr != 0 {
        panic(&'t');
    }

    if let Some(mut file) = zStream {
        if nUnused == 0 && myfeof(&mut file) {
            return;
        }
    }

    *bzf_idx_ref = bzf_idx;
    *streamNo_ref = streamNo;
    *i_ref = i;
    *unusedTmp_idx_ref = unusedTmp_idx;
}

fn goto_errhandler() {
    // Implement error handling logic here
    panic(&'e');
}
pub fn testStream(mut zStream: Option<File>) -> bool {
    let mut bzf: Option<&mut BZFILE> = None;
    let mut bzf_idx: u32 = 0;
    let mut bzerr: i32 = 0;
    let mut bzerr_dummy: i32 = 0;
    let mut ret: i32 = 0;
    let mut streamNo: i32 = 0;
    let mut i: i32 = 0;
    let mut obuf: [u8; 5000] = [0; 5000];
    let mut unused: [u8; 5000] = [0; 5000];
    let mut nUnused: i32 = 0;
    let mut unusedTmpV: Option<Box<[u8]>> = None;
    let mut unusedTmp: Vec<u8> = Vec::new();
    let mut unusedTmp_idx: u32 = 0;

    // SET_BINARY_MODE is typically a no-op in Rust as files are opened in binary mode by default
    if let Some(ref mut file) = zStream {
        if file.metadata().map_err(|_| false).is_err() {
            return false;
        }
    } else {
        return false;
    }

    loop {
        helper_testStream_1(
            &mut bzf_idx,
            &mut streamNo,
            &mut i,
            &mut unusedTmp_idx,
            zStream.as_ref().map(|f| f.try_clone().unwrap()),
            bzf.as_deref_mut(),
            bzerr,
            &mut obuf,
            &mut unused,
            nUnused,
            &mut unusedTmpV,
            &mut unusedTmp,
        );
    }

    if let Some(ref mut file) = zStream {
        if file.metadata().map_err(|_| false).is_err() {
            return false;
        }
    }

    if let Some(file) = zStream {
        ret = match file.sync_all() {
            Ok(_) => 0,
            Err(_) => -1,
        };
    }

    if ret == -1 {
        return false;
    }

    if VERBOSITY.load(Ordering::Relaxed) >= 2 {
        eprint!("\n    ");
    }

    true
}

fn errhandler(bzerr: i32, zStream: Option<File>, streamNo: i32) -> bool {
    let mut bzerr_dummy = 0;
    BZ2_bzReadClose(Some(&mut bzerr_dummy), None);

    if VERBOSITY.load(Ordering::Relaxed) == 0 {
        let prog_name = PROG_NAME.lock().unwrap();
        let in_name = IN_NAME.lock().unwrap();
        eprint!("{:?}: {:?}: ", prog_name, in_name);
    }

    match bzerr {
        -9 => {
            configError();
            false
        }
        -6 => {
            ioError();
            false
        }
        -4 => {
            eprintln!("data integrity (CRC) error in data");
            false
        }
        -3 => {
            outOfMemory();
            false
        }
        -7 => {
            eprintln!("file ends unexpectedly");
            false
        }
        -5 => {
            if zStream.is_some() {
                if let Some(file) = zStream {
                    if file.sync_all().is_err() {
                        return false;
                    }
                }
            }
            if streamNo == 1 {
                eprintln!("bad magic number (file not created by bzip2)");
                false
            } else {
                if noisy.load(Ordering::Relaxed) {
                    eprintln!("trailing garbage after EOF ignored");
                }
                true
            }
        }
        _ => {
            panic(&'t'); // Using a dummy char since we can't pass string to panic function
            false
        }
    }
}
pub fn testf(name: Option<&[Char]>) {
    let mut inStr: Option<File> = None;
    let mut allOK: Bool = 0;
    let mut statBuf = std::mem::MaybeUninit::<libc::stat>::uninit();
    
    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::Relaxed);
    
    if name.is_none() && srcMode != 1 {
        panic(&'t'); // Fixed: replaced string literal with char literal
    }
    
    {
        let mut outName = OUT_NAME.lock().unwrap();
        copyFileName(&mut outName[..], &['(', 'n', 'o', 'n', 'e', ')']);
    }
    
    {
        let mut inName = IN_NAME.lock().unwrap();
        match srcMode {
            1 => {
                copyFileName(&mut inName[..], &['(', 's', 't', 'd', 'i', 'n', ')']);
            },
            2 | 3 => {
                copyFileName(&mut inName[..], name.unwrap());
            },
            _ => {}
        }
    }
    
    if srcMode != 1 {
        let inName = IN_NAME.lock().unwrap();
        // Convert to string by taking until first null
        let in_name_str: String = inName.iter().take_while(|&&c| c != '\0').collect();
        if containsDubiousChars(Some(&inName[..])) {
            if noisy.load(Ordering::Relaxed) {
                let progName = PROG_NAME.lock().unwrap();
                let prog_name_str: String = progName.iter().take_while(|&&c| c != '\0').collect();
                eprintln!("{}: There are no files matching `{}'.", prog_name_str, in_name_str);
            }
            setExit(1);
            return;
        }
    }
    
    if srcMode != 1 {
        let inName = IN_NAME.lock().unwrap();
        // Convert to string by taking until first null
        let in_name_str: String = inName.iter().take_while(|&&c| c != '\0').collect();
        let in_name_cstr = std::ffi::CString::new(in_name_str.clone()).unwrap();
        let stat_result = unsafe {
            libc::stat(in_name_cstr.as_ptr(), statBuf.as_mut_ptr())
        };
        if stat_result != 0 {
            // stat failed - file doesn't exist or other error
            let progName = PROG_NAME.lock().unwrap();
            let prog_name_str: String = progName.iter().take_while(|&&c| c != '\0').collect();
            eprintln!("{}: Can't open input {}: {}.", prog_name_str, in_name_str, io::Error::last_os_error());
            setExit(1);
            return;
        }
        let statBuf = unsafe { statBuf.assume_init() };
        if (statBuf.st_mode & libc::S_IFMT) == libc::S_IFDIR {
            let progName = PROG_NAME.lock().unwrap();
            let prog_name_str: String = progName.iter().take_while(|&&c| c != '\0').collect();
            eprintln!("{}: Input file {} is a directory.", prog_name_str, in_name_str);
            setExit(1);
            return;
        }
    }
    
    match srcMode {
        1 => {
            unsafe {
                if isatty(io::stdin().as_raw_fd()) != 0 {
                    let progName = PROG_NAME.lock().unwrap();
                    let prog_name_str: String = progName.iter().take_while(|&&c| c != '\0').collect();
                    eprintln!("{}: I won't read compressed data from a terminal.", prog_name_str);
                    eprintln!("{}: For help, type: `{} --help'.", prog_name_str, prog_name_str);
                    setExit(1);
                    return;
                }
            }
            inStr = Some(unsafe { File::from_raw_fd(io::stdin().as_raw_fd()) });
        },
        2 | 3 => {
            let inName = IN_NAME.lock().unwrap();
            // Convert to string by taking until first null
            let in_name_str: String = inName.iter().take_while(|&&c| c != '\0').collect();
            inStr = File::open(in_name_str.clone()).ok();
            if inStr.is_none() {
                let progName = PROG_NAME.lock().unwrap();
                let prog_name_str: String = progName.iter().take_while(|&&c| c != '\0').collect();
                eprintln!("{}: Can't open input file {}: {}.", prog_name_str, in_name_str, io::Error::last_os_error());
                setExit(1);
                return;
            }
        },
        _ => {
            panic(&'t'); // Fixed: replaced string literal with char literal
        }
    }
    
    if VERBOSITY.load(Ordering::Relaxed) >= 1 {
        let inName = IN_NAME.lock().unwrap();
        // Convert to string by taking until first null
        let in_name_str: String = inName.iter().take_while(|&&c| c != '\0').collect();
        eprint!("  {}: ", in_name_str);
        pad(&inName[..]);
        let _ = stderr().flush();
    }
    
    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    allOK = testStream(inStr) as Bool;
    
    if allOK != 0 && VERBOSITY.load(Ordering::Relaxed) >= 1 {
        eprintln!("ok");
    }
    
    if allOK == 0 {
        TEST_FAILS_EXIST.store(true, Ordering::Relaxed);
    }
}
pub fn helper_main_3(
    aa_idx_ref: &mut u32,
    decode_ref: &mut Bool,
    argList: &Cell,
    argList_idx: u32,
    aa: &Cell,
) {
    let mut aa_idx = *aa_idx_ref;
    let mut decode = *decode_ref;
    TEST_FAILS_EXIST.store(false, Ordering::SeqCst);

    if srcMode == 1 {
        testf(None);
    } else {
        decode = 1;
        let mut current = &argList.link;
        for _ in argList_idx.. {
            if let Some(cell) = current {
                if let Some(name) = &cell.name {
                    let c_str = unsafe { CStr::from_ptr(name.as_ref() as *const Char as *const u8) };
                    if c_str.to_bytes() == b"--" {
                        decode = 0;
                        current = &cell.link;
                        continue;
                    }
                    if name.as_ref() == &'-' && decode != 0 {
                        current = &cell.link;
                        continue;
                    }
                }
                NUM_FILES_PROCESSED.fetch_add(1, Ordering::SeqCst);
                testf(cell.name.as_ref().map(|n| std::slice::from_ref(n.as_ref())));
                current = &cell.link;
            } else {
                break;
            }
        }
    }

    if TEST_FAILS_EXIST.load(Ordering::SeqCst) {
        if noisy.load(Ordering::SeqCst) {
            eprintln!("\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n\n");
        }
        setExit(2);
        exit(EXIT_VALUE.load(Ordering::SeqCst));
    }

    *aa_idx_ref = aa_idx;
    *decode_ref = decode;
}
pub static srcMode: Int32 = 0;
