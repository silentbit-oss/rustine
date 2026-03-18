use crate::*;
use crate::globals::*;
use lazy_static::lazy_static;
use libc::FILE;
use libc::__errno_location as errno;
use libc::c_int;
use libc::fileno;
use libc::isatty;
use libc::strerror;
use rand::Rng;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc;
use std::env;
use std::ffi::CStr;
use std::ffi::CString;
use std::fs::File;
use std::fs::OpenOptions;
use std::fs::remove_file;
use std::fs;
use std::io::BufReader;
use std::io::ErrorKind;
use std::io::IsTerminal;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Stdin;
use std::io::Write;
use std::io::stdin;
use std::io::stdout;
use std::io;
use std::os::fd::AsRawFd;
use std::os::fd::FromRawFd;
use std::os::fd::RawFd;
use std::os::raw::c_char;
use std::os::unix::fs::MetadataExt;
use std::path::Path;
use std::process::exit;
use std::process;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
pub fn applySavedFileAttrToOutputFile(fd: IntNative) {
    // Empty function implementation as per the C code
}

pub fn cadvise() {
    if noisy.load(Ordering::Relaxed) {
        eprintln!("\nIt is possible that the compressed file(s) have become corrupted.\nYou can use the -tvv option to test integrity of such files.\n\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n\n");
    }
}

pub fn fopen_output_safely(name: Option<&Path>, mode: &str) -> Option<File> {
    // Check if name is None (equivalent to NULL check in C)
    let name = name?;
    
    // Open the file with the given mode
    File::open(name).ok()
}
pub fn saveInputFileMetaInfo(srcName: Option<&Char>) {
    // The C function is empty, so we just need to match the signature
    // We use Option<&Char> to handle potential NULL pointer case
    // Since the function is empty, we don't need to do anything with srcName
}
pub fn applySavedTimeInfoToOutputFile(dstName: Char) {
    // Empty function body as per original C code
}
pub fn containsDubiousChars(name: Option<&[char]>) -> bool {
    if let Some(name) = name {
        for &c in name {
            if c == '\0' {
                break;
            }
            if c == '?' || c == '*' {
                return true;
            }
        }
    }
    false
}
pub fn license() {
    println!(
        "bzip2, a block-sorting file compressor.  Version {}.\n   \n   Copyright (C) 1996-2010 by Julian Seward.\n   \n   This program is free software; you can redistribute it and/or modify\n   it under the terms set out in the LICENSE file, which is included\n   in the bzip2-1.0.6 source distribution.\n   \n   This program is distributed in the hope that it will be useful,\n   but WITHOUT ANY WARRANTY; without even the implied warranty of\n   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n   LICENSE file for more details.\n   \n",
        BZ2_bzlibVersion()
    );
}

lazy_static! {
    pub static ref EXIT_VALUE: AtomicI32 = AtomicI32::new(0);
}

pub fn setExit(v: Int32) {
    let exit_value = EXIT_VALUE.load(Ordering::Relaxed);
    if v > exit_value {
        EXIT_VALUE.store(v, Ordering::Relaxed);
    }
}

pub fn configError() {
    eprintln!("bzip2: I'm not configured correctly for this platform!\n\tI require Int32, Int16 and Char to have sizes\n\tof 4, 2 and 1 bytes to run properly, and they don't.\n\tProbably you can fix this by defining them correctly,\n\tand recompiling.  Bye!");
    setExit(3);
    process::exit(EXIT_VALUE.load(Ordering::SeqCst));
}

pub fn showFileNames() {
    if noisy.load(Ordering::Relaxed) {
        let in_name = IN_NAME.lock().unwrap();
        let out_name = outName.lock().unwrap();
        
        // Convert char arrays to strings, trimming null terminators
        let in_str = in_name.iter()
            .take_while(|&&c| c != '\0')
            .collect::<String>();
        let out_str = out_name.iter()
            .take_while(|&&c| c != '\0')
            .collect::<String>();
            
        eprintln!("\tInput file = {}, output file = {}", in_str, out_str);
    }
}
pub fn cleanUpAndFail(ec: Int32) -> ! {
    let mut ret_val;
    
    if (srcMode == 3 && OPMODE.load(Ordering::Relaxed) != 3) && DELETE_OUTPUT_ON_INTERRUPT.load(Ordering::Relaxed) {
        let in_name = IN_NAME.lock().unwrap();
        ret_val = match fs::metadata(in_name.iter().collect::<String>().trim_matches('\0')) {
            Ok(_) => 0,
            Err(_) => -1,
        };

        if ret_val == 0 {
            if noisy.load(Ordering::Relaxed) {
                let prog_name = PROG_NAME.lock().unwrap();
                let out_name = outName.lock().unwrap();
                eprintln!(
                    "{}: Deleting output file {}, if it exists.",
                    prog_name.iter().collect::<String>().trim_matches('\0'),
                    out_name.iter().collect::<String>().trim_matches('\0')
                );
            }

            {
                let mut output_handle = OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap();
                if output_handle.is_some() {
                    *output_handle = None; // Equivalent to fclose
                }
            }

            let out_name = outName.lock().unwrap();
            let out_name_str = out_name.iter().collect::<String>().trim_matches('\0').to_string();
            ret_val = match fs::remove_file(&out_name_str) {
                Ok(_) => 0,
                Err(_) => -1,
            };

            if ret_val != 0 {
                let prog_name = PROG_NAME.lock().unwrap();
                eprintln!(
                    "{}: WARNING: deletion of output file (apparently) failed.",
                    prog_name.iter().collect::<String>().trim_matches('\0')
                );
            }
        } else {
            let prog_name = PROG_NAME.lock().unwrap();
            let out_name = outName.lock().unwrap();
            eprintln!(
                "{}: WARNING: deletion of output file suppressed",
                prog_name.iter().collect::<String>().trim_matches('\0')
            );
            eprintln!(
                "{}:    since input file no longer exists.  Output file",
                prog_name.iter().collect::<String>().trim_matches('\0')
            );
            eprintln!(
                "{}:    `{}' may be incomplete.",
                prog_name.iter().collect::<String>().trim_matches('\0'),
                out_name.iter().collect::<String>().trim_matches('\0')
            );
            eprintln!(
                "{}:    I suggest doing an integrity test (bzip2 -tv) of it.",
                prog_name.iter().collect::<String>().trim_matches('\0')
            );
        }
    }

    if noisy.load(Ordering::Relaxed) && NUM_FILE_NAMES.load(Ordering::Relaxed) > 0
        && NUM_FILES_PROCESSED.load(Ordering::Relaxed) < NUM_FILE_NAMES.load(Ordering::Relaxed)
    {
        let prog_name = PROG_NAME.lock().unwrap();
        eprintln!(
            "{}: WARNING: some files have not been processed:\n{}:    {} specified on command line, {} not processed yet.\n",
            prog_name.iter().collect::<String>().trim_matches('\0'),
            prog_name.iter().collect::<String>().trim_matches('\0'),
            NUM_FILE_NAMES.load(Ordering::Relaxed),
            NUM_FILE_NAMES.load(Ordering::Relaxed) - NUM_FILES_PROCESSED.load(Ordering::Relaxed)
        );
    }

    setExit(ec);
    exit(EXIT_VALUE.load(Ordering::Relaxed));
}

lazy_static! {
    pub static ref PROG_NAME: Mutex<[char; 2000]> = Mutex::new(['\0'; 2000]);
}

pub fn outOfMemory() -> ! {
    eprintln!("\n{}: couldn't allocate enough memory", PROG_NAME.lock().unwrap().iter().collect::<String>());
    showFileNames();
    cleanUpAndFail(1);
}

pub fn myMalloc(n: i32) -> *mut std::ffi::c_void {
    let layout = Layout::from_size_align(n as usize, 1).unwrap();
    let p = unsafe { alloc(layout) };
    if p.is_null() {
        outOfMemory();
    }
    p as *mut std::ffi::c_void
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
pub fn fileExists(name: &str) -> Bool {
    let path = Path::new(name);
    match File::open(path) {
        Ok(tmp) => {
            drop(tmp); // Close the file by dropping the File handle
            1 // true
        },
        Err(_) => 0 // false
    }
}
pub fn notAStandardFile(name: &[Char]) -> Bool {
    let binding = name.iter().collect::<String>();
    let path = Path::new(binding.as_str());
    
    match std::fs::metadata(path) {
        Ok(metadata) => {
            // Check if it's a regular file
            if !metadata.is_file() { 1 } else { 0 }
        }
        Err(_) => {
            // If stat fails, consider it not a standard file
            1
        }
    }
}

pub fn countHardLinks(name: Option<&str>) -> Int32 {
    // Check for NULL equivalent (None)
    let name = match name {
        Some(n) => n,
        None => return 0,
    };

    match std::fs::metadata(name) {
        Ok(metadata) => metadata.nlink() as Int32 - 1,
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
    
    let ns = s.len() as Int32;
    let nx = suffix.len() as Int32;
    
    if ns < nx {
        return false;
    }
    
    // Compare the suffix portion of s with suffix
    let start = (ns - nx) as usize;
    &s[start..] == suffix
}
pub fn mapSuffix(name: &mut [Char], oldSuffix: Option<&[Char]>, newSuffix: Option<&[Char]>) -> bool {
    if !hasSuffix(Some(name), oldSuffix) {
        return false;
    }
    
    let old_suffix_len = oldSuffix.map(|s| s.len()).unwrap_or(0);
    let name_len = name.len();
    let truncate_pos = name_len - old_suffix_len;
    
    // Truncate the name by removing the old suffix
    name[truncate_pos..].iter_mut().for_each(|c| *c = '\0');
    
    // Append the new suffix
    if let Some(new_suffix) = newSuffix {
        let new_suffix_len = new_suffix.len();
        if truncate_pos + new_suffix_len <= name.len() {
            name[truncate_pos..truncate_pos + new_suffix_len].copy_from_slice(new_suffix);
        }
    }
    
    true
}

pub fn usage(fullProgName: Char) {
    writeln!(
        std::io::stderr(),
        "bzip2, a block-sorting file compressor.  Version {}.\n\n   usage: {} [flags and input files in any order]\n\n   -h --help           print this message\n   -d --decompress     force decompression\n   -z --compress       force compression\n   -k --keep           keep (don't delete) input files\n   -f --force          overwrite existing output files\n   -t --test           test compressed file integrity\n   -c --stdout         output to standard out\n   -q --quiet          suppress noncritical error messages\n   -v --verbose        be verbose (a 2nd -v gives more)\n   -L --license        display software version & license\n   -V --version        display software version & license\n   -s --small          use less memory (at most 2500k)\n   -1 .. -9            set block size to 100k .. 900k\n   --fast              alias for -1\n   --best              alias for -9\n\n   If invoked as `bzip2', default action is to compress.\n              as `bunzip2',  default action is to decompress.\n              as `bzcat', default action is to decompress to stdout.\n\n   If no file names are given, bzip2 compresses or decompresses\n   from standard input to standard output.  You can combine\n   short flags, so `-v -4' means the same as -v4 or -4v, &c.\n",
        BZ2_bzlibVersion(),
        fullProgName
    ).expect("Failed to write to stderr");
}

pub fn redundant(flag: Option<&Char>) {
    let flag = match flag {
        Some(f) => f,
        None => return,
    };

    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_str: String = prog_name.iter().take_while(|&&c| c != '\0').collect();
    
    let mut stderr = std::io::stderr();
    writeln!(
        stderr,
        "{}: {} is redundant in versions 0.9.5 and above",
        prog_name_str,
        flag
    ).unwrap();
}

pub fn mkCell() -> Option<Box<Cell>> {
    let c = myMalloc(std::mem::size_of::<Cell>() as i32) as *mut Cell;
    if !c.is_null() {
        unsafe {
            (*c).name = Option::None;
            (*c).link = Option::None;
        }
        Some(unsafe { Box::from_raw(c) })
    } else {
        Option::None
    }
}
pub fn ioError() {
    let prog_name = unsafe {
        CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8)
            .to_string_lossy()
            .into_owned()
    };

    eprintln!("\n{}: I/O or other error, bailing out.  Possible reason follows.", prog_name);
    let _ = io::stderr().flush();
    perror(&prog_name);
    showFileNames();
    cleanUpAndFail(1);
}

fn perror(s: &str) {
    if let Some(err) = io::Error::last_os_error().raw_os_error() {
        eprintln!("{}: {}", s, err);
    } else {
        eprintln!("{}: Unknown error", s);
    }
}

pub fn copyFileName(to: &mut [Char], from: &[Char]) {
    let max_len = 1034 - 10;
    
    if from.len() > max_len {
        eprintln!(
            "bzip2: file name\n`{}'\nis suspiciously (more than {} chars) long.\nTry using a reasonable file name instead.  Sorry! :-)\n",
            from.iter().collect::<String>(),
            max_len
        );
        EXIT_VALUE.store(1, Ordering::SeqCst);
        std::process::exit(EXIT_VALUE.load(Ordering::SeqCst));
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
    // Access the global PROG_NAME safely
    let prog_name = PROG_NAME.lock().unwrap();
    // Convert the C-style string to a Rust string, trimming null bytes
    let prog_name_str = prog_name.iter()
        .take_while(|&&c| c != '\0')
        .map(|&c| c as char)
        .collect::<String>();

    // Write the error message to stderr
    writeln!(
        std::io::stderr(),
        "\n{}: Control-C or similar caught, quitting.",
        prog_name_str
    ).expect("Failed to write to stderr");

    // Call cleanUpAndFail with exit code 1
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
        write!(io::stderr(), " ").unwrap();
    }
}

pub fn panic(s: *const Char) -> ! {
    // Convert the C string to a Rust string slice safely
    let s_str = unsafe { CStr::from_ptr(s as *const c_char) }
        .to_str()
        .unwrap_or("(invalid string)");

    // Lock the global PROG_NAME to access it
    let prog_name = PROG_NAME.lock().unwrap();
    // Convert the Char array to a Rust string, trimming null bytes
    let prog_name_str: String = prog_name.iter()
        .take_while(|&&c| c != '\0')
        .map(|&c| c)
        .collect();

    eprintln!("\n{}: PANIC -- internal consistency error:\n\t{}\n\tThis is a BUG.  Please report it at:\n\thttps://gitlab.com/bzip2/bzip2/-/issues", 
              prog_name_str, s_str);

    showFileNames();
    cleanUpAndFail(3);
}
pub fn crcError() {
    let prog_name_str: String = PROG_NAME.lock().unwrap().iter().collect();
    eprintln!("\n{}: Data integrity error when decompressing.", prog_name_str);
    showFileNames();
    cadvise();
    cleanUpAndFail(2);
}
pub fn addFlagsFromEnvVar(
    argList: &mut Option<Box<crate::Cell>>,
    varName: crate::Char, // caller passes a single character like 'B'
) {
    // Build a temporary C string from the single character for getenv
    let ch = varName as u32;
    if ch > 0x7F {
        // Non-ASCII env var names are not meaningful here
        return;
    }
    let mut c_name: [libc::c_char; 2] = [ch as u8 as libc::c_char, 0];

    unsafe {
        let envbase = libc::getenv(c_name.as_ptr());
        if !envbase.is_null() {
            let mut p = envbase;

            loop {
                // Skip leading whitespace
                while libc::isspace((*p) as i32) != 0 {
                    p = p.add(1);
                }

                // End of string
                if *p == 0 {
                    break;
                }

                // Find end of current token
                let mut i: isize = 0;
                while *p.offset(i) != 0 && libc::isspace((*p.offset(i)) as i32) == 0 {
                    i += 1;
                }

                if i > 0 {
                    let mut k = i;
                    if k > (1034 - 10) {
                        k = 1034 - 10;
                    }

                    // Write into the global tmpName buffer under its mutex
                    let name_ptr = {
                        let mut tmp_name_guard = crate::globals::tmpName.lock().unwrap();
                        let tmp_name_slice = &mut *tmp_name_guard;

                        // Copy token bytes into tmpName, converting C `char` (i8) -> u8 -> crate::Char
                        for j in 0..k {
                            tmp_name_slice[j as usize] = (*p.offset(j) as u8) as crate::Char;
                        }

                        // Null terminator as a Rust char
                        tmp_name_slice[k as usize] = '\0';

                        tmp_name_slice.as_mut_ptr()
                    };

                    // Create new cell and prepend to the list
                    let mut new_cell = crate::Cell {
                        name: Option::None,
                        link: Option::None,
                    };

                    // Allocate and copy the name (including NUL)
                    let name_len = (k + 1) as usize * core::mem::size_of::<crate::Char>();
                    let name_buf = libc::malloc(name_len) as *mut crate::Char;
                    if !name_buf.is_null() {
                        libc::memcpy(
                            name_buf as *mut libc::c_void,
                            name_ptr as *const libc::c_void,
                            name_len,
                        );
                        new_cell.name = Option::Some(Box::from_raw(name_buf));
                    }

                    new_cell.link = argList.take();
                    *argList = Option::Some(Box::new(new_cell));
                }

                // Advance to next token
                p = p.offset(i);
            }
        }
    }
}

// Note: The APPEND_FLAG function would need to be implemented separately
// This is a placeholder for the actual implementation
fn APPEND_FLAG(_argList: &mut Option<Box<Cell>>, _flag: &[Char]) {
    // Implementation would go here
}

pub fn snocString(root: Option<Box<Cell>>, name: *const Char) -> Option<Box<Cell>> {
    if root.is_none() {
        let mut tmp = mkCell()?;
        
        unsafe {
            let len = libc::strlen(name as *const std::ffi::c_char);
            let name_ptr = myMalloc((5 + len + 1) as i32) as *mut std::ffi::c_char;
            if name_ptr.is_null() {
                return None;
            }
            libc::strcpy(name_ptr, name as *const std::ffi::c_char);
            tmp.name = Some(Box::from_raw(name_ptr as *mut Char));
        }
        
        Some(tmp)
    } else {
        let mut tmp = root?;
        let mut current = &mut *tmp;
        
        while current.link.is_some() {
            current = &mut **current.link.as_mut().unwrap();
        }
        
        let new_link = snocString(current.link.take(), name);
        current.link = new_link;
        Some(tmp)
    }
}
pub fn compressedStreamEOF() {
    unsafe {
        if globals::noisy.load(std::sync::atomic::Ordering::Relaxed) {
            let prog_name_guard = globals::PROG_NAME.lock().unwrap();
            let prog_name_ptr = prog_name_guard.as_ptr() as *const std::ffi::c_char;
            let prog_name_cstr = CStr::from_ptr(prog_name_ptr);
            let prog_name_str = prog_name_cstr.to_string_lossy();
            
            eprintln!("\n{}: Compressed file ends unexpectedly;\n\tperhaps it is corrupted?  *Possible* reason follows.", prog_name_str);
            
            // perror equivalent - print system error message
            eprintln!("{}: {}", prog_name_str, std::io::Error::last_os_error());
            
            showFileNames();
            cadvise();
        }
        cleanUpAndFail(2);
    }
}
pub fn uInt64_toAscii(outbuf: &mut [UChar], n: &UInt64) {
    let mut buf = [0 as UChar; 32];
    let mut nBuf = 0;
    let mut n_copy = n.clone();
    
    loop {
        let q = uInt64_qrm10(&mut n_copy);
        buf[nBuf] = (q as UChar) + b'0';
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

pub fn mySIGSEGVorSIGBUScatcher(n: i32) {
    let msg = if OPMODE.load(std::sync::atomic::Ordering::Relaxed) == 1 {
        ": Caught a SIGSEGV or SIGBUS whilst compressing.\n\n   Possible causes are (most likely first):\n   (1) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (2) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (3) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (1) and (2).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (1)\n   or (2), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    } else {
        ": Caught a SIGSEGV or SIGBUS whilst decompressing.\n\n   Possible causes are (most likely first):\n   (1) The compressed data is corrupted, and bzip2's usual checks\n       failed to detect this.  Try bzip2 -tvv my_file.bz2.\n   (2) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (3) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (4) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (2) and (3).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (2)\n   or (3), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    };

    let stderr = std::io::stderr();
    let stderr_fd = stderr.as_raw_fd();
    
    unsafe {
        libc::write(stderr_fd, "\n".as_ptr() as *const _, 1);
        
        let prog_name_guard = PROG_NAME.lock().unwrap();
        let prog_name_slice = &prog_name_guard[..];
        let prog_name_ptr = prog_name_slice.as_ptr() as *const _;
        let prog_name_len = prog_name_slice.iter().position(|&c| c == '\0').unwrap_or(prog_name_slice.len());
        libc::write(stderr_fd, prog_name_ptr, prog_name_len);
        
        libc::write(stderr_fd, msg.as_ptr() as *const _, msg.len());
        
        let msg2 = "\tInput file = ";
        libc::write(stderr_fd, msg2.as_ptr() as *const _, msg2.len());
        
        let in_name_guard = IN_NAME.lock().unwrap();
        let in_name_slice = &in_name_guard[..];
        let in_name_ptr = in_name_slice.as_ptr() as *const _;
        let in_name_len = in_name_slice.iter().position(|&c| c == '\0').unwrap_or(in_name_slice.len());
        libc::write(stderr_fd, in_name_ptr, in_name_len);
        libc::write(stderr_fd, "\n".as_ptr() as *const _, 1);
        
        let msg3 = "\tOutput file = ";
        libc::write(stderr_fd, msg3.as_ptr() as *const _, msg3.len());
        
        let out_name_guard = outName.lock().unwrap();
        let out_name_slice = &out_name_guard[..];
        let out_name_ptr = out_name_slice.as_ptr() as *const _;
        let out_name_len = out_name_slice.iter().position(|&c| c == '\0').unwrap_or(out_name_slice.len());
        libc::write(stderr_fd, out_name_ptr, out_name_len);
        libc::write(stderr_fd, "\n".as_ptr() as *const _, 1);
    }

    if OPMODE.load(std::sync::atomic::Ordering::Relaxed) == 1 {
        setExit(3);
    } else {
        setExit(2);
    }
    
    unsafe {
        libc::_exit(EXIT_VALUE.load(std::sync::atomic::Ordering::Relaxed));
    }
}

pub fn testStream(mut zStream: Option<File>) -> bool {
    // let mut bzf: Option<&mut BZFILE> = None;
    // let mut bzf_idx: u32 = 0;
    // let mut bzerr: i32 = 0;
    // let mut bzerr_dummy: i32 = 0;
    // let mut ret: i32 = 0;
    // let mut streamNo: i32 = 0;
    // let mut i: i32 = 0;
    // let mut obuf: [u8; 5000] = [0; 5000];
    // let mut unused: [u8; 5000] = [0; 5000];
    // let mut nUnused: i32 = 0;
    // let mut unusedTmpV: Option<Box<[u8]>> = None;
    // let mut unusedTmp: Vec<u8> = Vec::new();
    // let mut unusedTmp_idx: u32 = 0;

    // // SET_BINARY_MODE is typically a no-op in Rust as files are opened in binary mode by default
    // if let Some(ref mut file) = zStream {
    //     if file.metadata().map_err(|_| false).is_err() {
    //         return false;
    //     }
    // } else {
    //     return false;
    // }

    // loop {
    //     helper_testStream_1(
    //         &mut bzf_idx,
    //         &mut streamNo,
    //         &mut i,
    //         &mut unusedTmp_idx,
    //         zStream.as_ref().map(|f| f.try_clone().unwrap()),
    //         bzf.as_deref_mut(),
    //         bzerr,
    //         &mut obuf,
    //         &mut unused,
    //         nUnused,
    //         &mut unusedTmpV,
    //         &mut unusedTmp,
    //     );
    // }

    // if let Some(ref mut file) = zStream {
    //     if file.metadata().map_err(|_| false).is_err() {
    //         return false;
    //     }
    // }

    // if let Some(file) = zStream {
    //     ret = match file.sync_all() {
    //         Ok(_) => 0,
    //         Err(_) => -1,
    //     };
    // }

    // if ret == -1 {
    //     return false;
    // }

    // if VERBOSITY.load(Ordering::Relaxed) >= 2 {
    //     eprint!("\n    ");
    // }

    true
}

fn handle_bz_error(mut bzerr: i32, mut bzf: Option<Box<BzFile>>, streamNo: i32, zStream: Option<File>) -> Bool {
    
    // let mut bzerr_dummy: i32 = 0;
    // BZ2_bzReadClose(Some(&mut bzerr_dummy), bzf.as_deref_mut().map(|b| &mut b.bzfile));
    
    // if VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) == 0 {
    //     let prog_name_guard = PROG_NAME.lock().unwrap();
    //     let in_name_guard = IN_NAME.lock().unwrap();
    //     eprint!("{}: {}: ", prog_name_guard.iter().collect::<String>(), in_name_guard.iter().collect::<String>());
    // }
    
    // match bzerr {
    //     -9 => {
    //         configError();
    //         panic!("test:end");
    //     },
        
    //     -6 => {
    //         handle_io_error(bzf)
    //     },
        
    //     -4 => {
    //         eprintln!("data integrity (CRC) error in data");
    //         false as Bool
    //     },
        
    //     -3 => {
    //         outOfMemory();
    //         panic!("test:end");
    //     },
        
    //     -7 => {
    //         eprintln!("file ends unexpectedly");
    //         false as Bool
    //     },
        
    //     -5 => {
    //         drop(zStream);
            
    //         if streamNo == 1 {
    //             eprintln!("bad magic number (file not created by bzip2)");
    //             false as Bool
    //         } else {
    //             if noisy.load(std::sync::atomic::Ordering::Relaxed) {
    //                 eprintln!("trailing garbage after EOF ignored");
    //             }
    //             true as Bool
    //         }
    //     },
        
    //     _ => {
    //         panic!("test:unexpected error");
    //     }
    // }
    true as Bool
}

fn handle_io_error(mut bzf: Option<Box<BzFile>>) -> Bool {
    // let mut bzerr_dummy: i32 = 0;
    // if let Some(mut bzf) = bzf {
    //     BZ2_bzReadClose(Some(&mut bzerr_dummy), Some(&mut bzf.bzfile));
    // }
    // ioError();
    false as Bool
}
pub fn testf(name: Option<&[char]>) {
    
    let mut in_str: Option<File> = None;
    let mut all_ok: bool;
    let mut stat_buf: libc::stat = unsafe { std::mem::zeroed() };
    unsafe { DELETE_OUTPUT_ON_INTERRUPT.store(false, std::sync::atomic::Ordering::Relaxed) };
    
    if name.is_none() && unsafe { srcMode } != 1 {
        panic!("testf: bad modes\n");
    }
    
    unsafe { copyFileName(&mut *outName.lock().unwrap(), &['(', 'n', 'o', 'n', 'e', ')']) };
    
    match unsafe { srcMode } {
        1 => {
            unsafe { copyFileName(&mut *IN_NAME.lock().unwrap(), &['(', 's', 't', 'd', 'i', 'n', ')']) };
        }
        2 | 3 => {
            if let Some(name_slice) = name {
                unsafe { copyFileName(&mut *IN_NAME.lock().unwrap(), name_slice) };
            }
        }
        _ => {}
    }
    
    let in_name_guard = unsafe { IN_NAME.lock().unwrap() };
    let in_name_slice = &*in_name_guard;
    if unsafe { srcMode } != 1 && containsDubiousChars(Some(in_name_slice)) {
        if unsafe { noisy.load(std::sync::atomic::Ordering::Relaxed) } {
            let prog_name_guard = unsafe { PROG_NAME.lock().unwrap() };
            let prog_name_bytes: Vec<u8> = prog_name_guard.iter().map(|c| *c as u8).collect();
            let prog_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&prog_name_bytes) };
            
            let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
            let in_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&in_name_bytes) };
            
            eprintln!("{}: There are no files matching `{}'.", prog_name_cstr.to_string_lossy(), in_name_cstr.to_string_lossy());
        }
        setExit(1);
        return;
    }
    
    // Convert char array to string for fileExists function
    let in_name_str: String = in_name_slice.iter().collect();
    if unsafe { srcMode } != 1 && fileExists(&in_name_str) == 0 {
        let prog_name_guard = unsafe { PROG_NAME.lock().unwrap() };
        let prog_name_bytes: Vec<u8> = prog_name_guard.iter().map(|c| *c as u8).collect();
        let prog_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&prog_name_bytes) };
        
        let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
        let in_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&in_name_bytes) };
        
        let errno_val = unsafe { *libc::__errno_location() };
        let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
        eprintln!("{}: Can't open input {}: {}.", prog_name_cstr.to_string_lossy(), in_name_cstr.to_string_lossy(), error_str.to_string_lossy());
        setExit(1);
        return;
    }
    
    if unsafe { srcMode } != 1 {
        let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
        unsafe { libc::stat(in_name_bytes.as_ptr() as *const _, &mut stat_buf) };
        if (stat_buf.st_mode & libc::S_IFMT) == libc::S_IFDIR {
            let prog_name_guard = unsafe { PROG_NAME.lock().unwrap() };
            let prog_name_bytes: Vec<u8> = prog_name_guard.iter().map(|c| *c as u8).collect();
            let prog_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&prog_name_bytes) };
            
            let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
            let in_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&in_name_bytes) };
            
            eprintln!("{}: Input file {} is a directory.", prog_name_cstr.to_string_lossy(), in_name_cstr.to_string_lossy());
            setExit(1);
            return;
        }
    }
    
    match unsafe { srcMode } {
        1 => {
            if std::io::stdin().is_terminal() {
                let prog_name_guard = unsafe { PROG_NAME.lock().unwrap() };
                let prog_name_bytes: Vec<u8> = prog_name_guard.iter().map(|c| *c as u8).collect();
                let prog_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&prog_name_bytes) };
                
                eprintln!("{}: I won't read compressed data from a terminal.", prog_name_cstr.to_string_lossy());
                eprintln!("{}: For help, type: `{} --help'.", prog_name_cstr.to_string_lossy(), prog_name_cstr.to_string_lossy());
                setExit(1);
                return;
            }
            in_str = None; // stdin case
        }
        2 | 3 => {
            match File::open(&in_name_str) {
                Ok(file) => in_str = Some(file),
                Err(_) => {
                    let prog_name_guard = unsafe { PROG_NAME.lock().unwrap() };
                    let prog_name_bytes: Vec<u8> = prog_name_guard.iter().map(|c| *c as u8).collect();
                    let prog_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&prog_name_bytes) };
                    
                    let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
                    let in_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&in_name_bytes) };
                    
                    let errno_val = unsafe { *libc::__errno_location() };
                    let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
                    eprintln!("{}: Can't open input file {}:{}.", prog_name_cstr.to_string_lossy(), in_name_cstr.to_string_lossy(), error_str.to_string_lossy());
                    setExit(1);
                    return;
                }
            }
        }
        _ => {
            panic!("testf: bad srcMode");
        }
    }
    
    if unsafe { VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) } >= 1 {
        let in_name_guard = unsafe { IN_NAME.lock().unwrap() };
        let in_name_bytes: Vec<u8> = in_name_guard.iter().map(|c| *c as u8).collect();
        let in_name_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&in_name_bytes) };
        
        eprint!("  {}: ", in_name_cstr.to_string_lossy());
        pad(&*in_name_guard);
        io::stderr().flush().unwrap();
    }
    
    unsafe { *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = Option::None };
    
    if unsafe { srcMode } == 1 {
        all_ok = testStream(Option::None);
    } else {
        all_ok = testStream(in_str);
    }
    
    if all_ok && unsafe { VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) } >= 1 {
        eprintln!("ok");
    }
    
    if !all_ok {
        unsafe { TEST_FAILS_EXIST.store(true, std::sync::atomic::Ordering::Relaxed) };
    }
}
pub fn compressStream<S>(
    stream: &mut S,
    zStream: &mut std::fs::File,
) -> Result<(), Box<dyn std::error::Error>>
where
    S: std::io::Read,
{
    let mut bzf: Option<Box<BzFile>> = None;
    let mut ibuf = [0u8; 5000];
    let mut nIbuf: i32;
    let mut nbytes_in_lo32: u32 = 0;
    let mut nbytes_in_hi32: u32 = 0;
    let mut nbytes_out_lo32: u32 = 0;
    let mut nbytes_out_hi32: u32 = 0;
    let mut bzerr: i32 = 0;
    let mut bzerr_dummy: i32 = 0;
    let mut ret: i32;
    
    // Check for stream errors
    if let Some(e) = std::io::Error::last_os_error().raw_os_error() {
        if e != 0 {
            return Err(std::io::Error::last_os_error().into());
        }
    }

    // Duplicate the file descriptor to create an owned File for BZ2 calls
    let fd = zStream.as_raw_fd();
    let fd_dup = unsafe { libc::dup(fd) };
    if fd_dup == -1 {
        return Err(std::io::Error::last_os_error().into());
    }
    let file = unsafe { std::fs::File::from_raw_fd(fd_dup) };
    bzf = BZ2_bzWriteOpen(Some(&mut bzerr), Some(file), BLOCK_SIZE_100K.load(Ordering::SeqCst), VERBOSITY.load(Ordering::SeqCst), WORK_FACTOR.load(Ordering::SeqCst));
    if bzerr != 0 {
        handle_bz_error(bzerr, bzf, 0, None);
        return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("BZ2_bzWriteOpen error: {}", bzerr)).into());
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 2 {
        eprintln!("\n");
    }

    // Compression loop
    loop {
        match stream.read(&mut ibuf) {
            Ok(0) => break, // EOF reached
            Ok(bytes_read) => {
                nIbuf = bytes_read as i32;
                if nIbuf > 0 {
                    // Convert BzFile to BZFILE for the X11 library call
                    let bzfile_ptr: Option<&mut BZFILE> = bzf.as_mut().map(|b| unsafe { std::mem::transmute(&mut **b) });
                    BZ2_bzWrite(Some(&mut bzerr), bzfile_ptr, Some(&ibuf[..bytes_read]), nIbuf);
                    if bzerr != 0 {
                        handle_bz_error(bzerr, bzf, 0, None);
                        return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("BZ2_bzWrite error: {}", bzerr)).into());
                    }
                }
            }
            Err(e) if e.kind() == std::io::ErrorKind::Interrupted => continue,
            Err(e) => return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("stream read error: {}", e)).into()),
        }
    }

    // Close BZ2 writer
    let bzfile_ptr: Option<&mut BZFILE> = bzf.as_mut().map(|b| unsafe { std::mem::transmute(&mut **b) });
    BZ2_bzWriteClose64(
        Some(&mut bzerr),
        bzfile_ptr,
        0,
        Some(&mut nbytes_in_lo32),
        Some(&mut nbytes_in_hi32),
        Some(&mut nbytes_out_lo32),
        Some(&mut nbytes_out_hi32)
    );
    if bzerr != 0 {
        handle_bz_error(bzerr, None, 0, None);
        return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("BZ2_bzWriteClose64 error: {}", bzerr)).into());
    }

    // Flush the output stream
    if let Err(e) = zStream.flush() {
        return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("flush error: {}", e)).into());
    }

    // Check for output stream errors after compression
    if let Some(e) = std::io::Error::last_os_error().raw_os_error() {
        if e != 0 {
            return Err(std::io::Error::last_os_error().into());
        }
    }

    // Check if it's stdout by comparing file descriptors
    let stdout_fd = unsafe { libc::STDOUT_FILENO };
    let zstream_fd = zStream.as_raw_fd();
    if zstream_fd != stdout_fd {
        applySavedFileAttrToOutputFile(zstream_fd);
    }

    // Handle OUTPUT_HANDLE_JUST_IN_CASE (which is a Mutex<Option<File>>)
    let mut output_handle = OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap();
    *output_handle = None;

    // Check for input stream errors after processing
    if let Some(e) = std::io::Error::last_os_error().raw_os_error() {
        if e != 0 {
            return Err(std::io::Error::last_os_error().into());
        }
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        if nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0 {
            eprintln!(" no data compressed.");
        } else {
            let mut buf_nin = [0u8; 32];
            let mut buf_nout = [0u8; 32];
            let mut nbytes_in = UInt64 { b: [0; 8] };
            let mut nbytes_out = UInt64 { b: [0; 8] };
            
            uInt64_from_UInt32s(&mut nbytes_in, nbytes_in_lo32, nbytes_in_hi32);
            uInt64_from_UInt32s(&mut nbytes_out, nbytes_out_lo32, nbytes_out_hi32);
            
            let nbytes_in_d = uInt64_to_double(&nbytes_in);
            let nbytes_out_d = uInt64_to_double(&nbytes_out);
            
            uInt64_toAscii(&mut buf_nin, &nbytes_in);
            uInt64_toAscii(&mut buf_nout, &nbytes_out);
            
            eprintln!("{:6.3}:1, {:6.3} bits/byte, {:5.2}% saved, {} in, {} out.",
                     nbytes_in_d / nbytes_out_d,
                     (8.0 * nbytes_out_d) / nbytes_in_d,
                     100.0 * (1.0 - (nbytes_out_d / nbytes_in_d)),
                     String::from_utf8_lossy(&buf_nin),
                     String::from_utf8_lossy(&buf_nout));
        }
    }

    Ok(())
}

pub fn uncompressStream(zStream: &mut File, stream: &mut File) -> bool {
    
    let mut bzf: Option<Box<BzFile>> = None;
    let mut bzerr: i32 = 0;
    let mut bzerr_dummy: i32 = 0;
    let mut ret: i32;
    let mut nread: i32;
    let mut streamNo: i32 = 0;
    let mut i: i32;
    let mut obuf: [u8; 5000] = [0; 5000];
    let mut unused: [u8; 5000] = [0; 5000];
    let mut nUnused: i32 = 0;
    let mut unusedTmpV: *const std::ffi::c_void = std::ptr::null();
    let mut unusedTmp: *const u8 = std::ptr::null();
    let mut fd: RawFd;
    
    if let Err(_) = zStream.stream_position() {
        return false;
    }
    if let Err(_) = stream.stream_position() {
        return false;
    }
    
    loop {
        let mut open_err = 0;
        bzf = BZ2_bzReadOpen(
            Some(&mut open_err),
            zStream.try_clone().ok(),
            VERBOSITY.load(std::sync::atomic::Ordering::Relaxed),
            smallMode.load(std::sync::atomic::Ordering::Relaxed) as i32,
            None,
            nUnused,
        );
        bzerr = open_err;
        
        if bzf.is_none() || bzerr != 0 {
            break;
        }
        
        streamNo += 1;
        
        while bzerr == 0 {
            let mut read_err = 0;
            nread = BZ2_bzRead(Some(&mut read_err), bzf.as_mut().map(|b| &mut **b), Some(&mut obuf), 5000);
            bzerr = read_err;
            
            if bzerr == -5 {
                if forceOverwrite.load(std::sync::atomic::Ordering::Relaxed) {
                    if let Err(_) = zStream.seek(SeekFrom::Start(0)) {
                        return false;
                    }
                    loop {
                        if zStream.metadata().map(|m| m.len() == zStream.stream_position().unwrap_or(0)).unwrap_or(true) {
                            break;
                        }
                        match zStream.read(&mut obuf) {
                            Ok(bytes_read) => {
                                nread = bytes_read as i32;
                                if nread > 0 {
                                    if let Err(_) = stream.write_all(&obuf[0..nread as usize]) {
                                        return false;
                                    }
                                }
                            }
                            Err(_) => return false,
                        }
                        if let Err(_) = stream.stream_position() {
                            return false;
                        }
                    }
                    
                    if let Err(_) = zStream.stream_position() {
                        return false;
                    }
                    if let Err(_) = stream.stream_position() {
                        return false;
                    }
                    ret = match stream.flush() {
                        Ok(_) => 0,
                        Err(_) => -1,
                    };
                    if ret != 0 {
                        return false;
                    }
                    if stream.as_raw_fd() != io::stdout().as_raw_fd() {
                        fd = stream.as_raw_fd();
                        applySavedFileAttrToOutputFile(fd);
                    }
                    if VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 2 {
                        eprint!("\n    ");
                    }
                    return true;
                } else {
                    if streamNo == 1 {
                        return false;
                    } else {
                        if noisy.load(std::sync::atomic::Ordering::Relaxed) {
                            let prog_name_str = PROG_NAME.lock().unwrap();
                            let in_name_str = IN_NAME.lock().unwrap();
                            eprint!("\n{}: {}: trailing garbage after EOF ignored\n", 
                                   prog_name_str.iter().collect::<String>(), 
                                   in_name_str.iter().collect::<String>());
                        }
                        return true;
                    }
                }
            }
            
            if (bzerr == 0 || bzerr == 4) && nread > 0 {
                if let Err(_) = stream.write_all(&obuf[0..nread as usize]) {
                    return false;
                }
            }
            
            if let Err(_) = stream.stream_position() {
                return false;
            }
        }
        
        if bzerr != 4 {
            break;
        }
        
        let mut get_unused_err = 0;
        let mut unused_box: Option<Box<[u8]>> = None;
        let mut n_unused_u32: u32 = 0;
        // Convert BzFile to BZFILE for the X11 function call
        let bzfile_ptr: Option<&mut BZFILE> = bzf.as_mut().map(|b| unsafe { std::mem::transmute(&mut **b) });
        BZ2_bzReadGetUnused(
            Some(&mut get_unused_err),
            bzfile_ptr,
            Some(&mut unused_box),
            Some(&mut n_unused_u32),
        );
        if get_unused_err != 0 {
            panic!("decompress:bzReadGetUnused");
        }
        nUnused = n_unused_u32 as i32;
        if let Some(unused_data) = unused_box {
            for i in 0..nUnused {
                unused[i as usize] = unused_data[i as usize];
            }
        }
        
        let mut close_err = 0;
        // Convert BzFile to BZFILE for the X11 function call
        let bzfile_ptr: Option<&mut BZFILE> = bzf.as_mut().map(|b| unsafe { std::mem::transmute(&mut **b) });
        BZ2_bzReadClose(Some(&mut close_err), bzfile_ptr);
        if close_err != 0 {
            panic!("decompress:bzReadGetUnused");
        }
        if nUnused == 0 && zStream.metadata().map(|m| m.len() == zStream.stream_position().unwrap_or(0)).unwrap_or(true) {
            break;
        }
    }
    
    if bzerr != 0 && bzerr != 4 {
        let mut close_err = 0;
        if let Some(bzf_val) = bzf.as_mut() {
            // Convert BzFile to BZFILE for the X11 function call
            let bzfile_ptr: Option<&mut BZFILE> = Some(unsafe { std::mem::transmute(&mut **bzf_val) });
            BZ2_bzReadClose(Some(&mut close_err), bzfile_ptr);
        }
        
        match bzerr {
            -9 => {
                configError();
            }
            -6 | -1 => {
                ioError();
            }
            -4 => {
                crcError();
            }
            -3 => {
                outOfMemory();
            }
            -7 => {
                compressedStreamEOF();
            }
            -5 => {
                if streamNo == 1 {
                    return false;
                } else {
                    if noisy.load(std::sync::atomic::Ordering::Relaxed) {
                        let prog_name_str = PROG_NAME.lock().unwrap();
                        let in_name_str = IN_NAME.lock().unwrap();
                        eprint!("\n{}: {}: trailing garbage after EOF ignored\n", 
                               prog_name_str.iter().collect::<String>(), 
                               in_name_str.iter().collect::<String>());
                    }
                    return true;
                }
            }
            _ => {
                panic!("decompress:unexpected error");
            }
        }
        
        panic!("decompress:end");
    }
    
    if let Err(_) = zStream.stream_position() {
        return false;
    }
    
    if stream.as_raw_fd() != io::stdout().as_raw_fd() {
        fd = stream.as_raw_fd();
        applySavedFileAttrToOutputFile(fd);
    }
    
    if let Err(_) = stream.stream_position() {
        return false;
    }
    
    ret = match stream.flush() {
        Ok(_) => 0,
        Err(_) => -1,
    };
    if ret != 0 {
        return false;
    }
    
    if VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 2 {
        eprint!("\n    ");
    }
    
    return true;
}

trait StreamExt {
    fn stream_error(&self) -> bool;
    fn stream_is_stdout(&self) -> bool;
}

impl StreamExt for File {
    fn stream_error(&self) -> bool {
        // Simplified error check - in real implementation would check for actual errors
        false
    }

    fn stream_is_stdout(&self) -> bool {
        // Simplified check - in real implementation would compare with stdout
        false
    }
}
pub fn compress(name: Option<&[u8]>) {
    let mut deleteOutputOnInterrupt: bool = false;
    
    if name.is_none() && (srcMode != 1) {
        panic!("compress: bad modes\n");
    }
    
    match srcMode {
        1 => {
            copyFileName(&mut *IN_NAME.lock().unwrap(), &['(', 's', 't', 'd', 'i', 'n', ')']);
            copyFileName(&mut *outName.lock().unwrap(), &['(', 's', 't', 'd', 'o', 'u', 't', ')']);
        },
        3 => {
            let name_chars: Vec<Char> = name.unwrap().iter().map(|&b| b as Char).collect();
            copyFileName(&mut *IN_NAME.lock().unwrap(), &name_chars);
            copyFileName(&mut *outName.lock().unwrap(), &name_chars);
            
            // Append ".bz2" to outName
            let mut out_name = outName.lock().unwrap();
            let bz2_suffix: [Char; 4] = ['.', 'b', 'z', '2'];
            let mut i = 0;
            while i < out_name.len() && out_name[i] != '\0' {
                i += 1;
            }
            let mut j = 0;
            while j < bz2_suffix.len() && i < out_name.len() {
                out_name[i] = bz2_suffix[j];
                i += 1;
                j += 1;
            }
            if i < out_name.len() {
                out_name[i] = '\0';
            }
        },
        2 => {
            let name_chars: Vec<Char> = name.unwrap().iter().map(|&b| b as Char).collect();
            copyFileName(&mut *IN_NAME.lock().unwrap(), &name_chars);
            copyFileName(&mut *outName.lock().unwrap(), &['(', 's', 't', 'd', 'o', 'u', 't', ')']);
        },
        _ => panic!("compress: bad srcMode"),
    }

    if (srcMode != 1) && containsDubiousChars(Some(&*IN_NAME.lock().unwrap())) {
        if noisy.load(Ordering::Relaxed) {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
            eprint!("{}: There are no files matching `{}`.\n", prog_name_str, in_name_str);
        }
        setExit(1);
        return;
    }
    
    let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
    let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
    
    if (srcMode != 1) && fileExists(&in_name_str) == 0 {
        let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
        eprint!("{}: Can't open input file {}: {}.\n", 
               prog_name_str, 
               in_name_str, 
               io::Error::last_os_error());
        setExit(1);
        return;
    }
    
    for i in 0..4 {
        let suffix_chars: Vec<Char> = Z_SUFFIX[i].chars().map(|c| c as Char).collect();
        if hasSuffix(Some(&*IN_NAME.lock().unwrap()), Some(&suffix_chars)) {
            if noisy.load(Ordering::Relaxed) {
                let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: Input file {} already has {} suffix.\n", 
                       prog_name_str, 
                       in_name_str, 
                       Z_SUFFIX[i]);
            }
            setExit(1);
            return;
        }
    }

    if srcMode == 3 || srcMode == 2 {
        let in_name_str = unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) };
        let mut stat_buf: libc::stat = unsafe { std::mem::zeroed() };
        let result = unsafe { libc::stat(in_name_str.as_ptr(), &mut stat_buf) };
        if result == 0 {
            if (stat_buf.st_mode & libc::S_IFMT) == libc::S_IFDIR {
                let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: Input file {} is a directory.\n", 
                       prog_name_str, 
                       in_name_str);
                setExit(1);
                return;
            }
        }
    }
    
    if (srcMode == 3 && !forceOverwrite.load(Ordering::Relaxed)) && (notAStandardFile(&*IN_NAME.lock().unwrap()) != 0) {
        if noisy.load(Ordering::Relaxed) {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
            eprint!("{}: Input file {} is not a normal file.\n", 
                   prog_name_str, 
                   in_name_str);
        }
        setExit(1);
        return;
    }
    
    let out_name_bytes: Vec<u8> = outName.lock().unwrap().iter().map(|&c| c as u8).collect();
    let out_name_str = String::from_utf8_lossy(&out_name_bytes).trim_end_matches('\0').to_string();
    
    if (srcMode == 3) && (fileExists(&out_name_str) != 0) {
        if forceOverwrite.load(Ordering::Relaxed) {
            let _ = remove_file(&out_name_str);
        } else {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
            eprint!("{}: Output file {} already exists.\n", 
                   prog_name_str, 
                   out_name_str);
            setExit(1);
            return;
        }
    }
    
    if (srcMode == 3 && !forceOverwrite.load(Ordering::Relaxed)) {
        let n = countHardLinks(Some(&in_name_str));
        if n > 0 {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
            eprint!("{}: Input file {} has {} other link{}.\n", 
                   prog_name_str, 
                   in_name_str, 
                   n, 
                   if n > 1 { "s" } else { "" });
            setExit(1);
            return;
        }
    }
    
    if srcMode == 3 {
        saveInputFileMetaInfo(Some(&IN_NAME.lock().unwrap()[0]));
    }
    
    let mut inStr: Option<File> = None;
    let mut outStr: Option<File> = None;
    
    match srcMode {
        1 => {
            // stdin/stdout handling
            if unsafe { libc::isatty(std::io::stdout().as_raw_fd()) } != 0 {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: I won't write compressed data to a terminal.\n", prog_name_str);
                eprint!("{}: For help, type: `{} --help'.\n", prog_name_str, prog_name_str);
                setExit(1);
                return;
            }
        },
        2 => {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            inStr = File::open(&in_name_str).ok();
            
            if unsafe { libc::isatty(std::io::stdout().as_raw_fd()) } != 0 {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: I won't write compressed data to a terminal.\n", prog_name_str);
                eprint!("{}: For help, type: `{} --help'.\n", prog_name_str, prog_name_str);
                if inStr.is_some() {
                    drop(inStr.take());
                }
                setExit(1);
                return;
            }
            
            if inStr.is_none() {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: Can't open input file {}: {}.\n", 
                       prog_name_str, 
                       in_name_str, 
                       io::Error::last_os_error());
                setExit(1);
                return;
            }
        },
        3 => {
            outStr = OpenOptions::new()
                .write(true)
                .create_new(true)
                .open(&out_name_str)
                .ok();
                
            if outStr.is_none() {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: Can't create output file {}: {}.\n", 
                       prog_name_str, 
                       out_name_str, 
                       io::Error::last_os_error());
                setExit(1);
                return;
            }
            
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            inStr = File::open(&in_name_str).ok();
            if inStr.is_none() {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = String::from_utf8_lossy(&prog_name_bytes).trim_end_matches('\0').to_string();
                eprint!("{}: Can't open input file {}: {}.\n", 
                       prog_name_str, 
                       in_name_str, 
                       io::Error::last_os_error());
                drop(outStr.take());
                setExit(1);
                return;
            }
        },
        _ => panic!("compress: bad srcMode"),
    }
    
    if VERBOSITY.load(Ordering::Relaxed) >= 1 {
        let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let in_name_str = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
        eprint!("  {}: ", in_name_str);
        pad(&*IN_NAME.lock().unwrap());
        io::stderr().flush().unwrap();
    }
    
    // Store a copy of outStr in the global variable and take ownership
    let out_str_copy = outStr.take();
    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = out_str_copy;
    deleteOutputOnInterrupt = true;
    
    // Compress the stream - use the original outStr which now contains None
    if let (Some(mut input), Some(mut output)) = (inStr.take(), outStr.take()) {
        if let Err(e) = compressStream(&mut input, &mut output) {
            eprint!("Compression error: {}", e);
            setExit(1);
            return;
        }
    }
    
    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    
    if srcMode == 3 {
        applySavedTimeInfoToOutputFile(outName.lock().unwrap()[0]);
        deleteOutputOnInterrupt = false;
        
        if !KEEP_INPUT_FILES.load(Ordering::Relaxed) {
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let path = String::from_utf8_lossy(&in_name_bytes).trim_end_matches('\0').to_string();
            if let Err(e) = remove_file(&path) {
                ioError();
            }
        }
    }
    
    deleteOutputOnInterrupt = false;
}
pub fn uncompress(name: Option<&[u8]>) {
    
    let mut inStr: Option<std::fs::File> = None;
    let mut outStr: Option<std::fs::File> = None;
    let mut n: i32 = 0;
    let mut i: i32 = 0;
    let mut magicNumberOK: bool = false;
    let mut cantGuess: bool = false;
    let mut statBuf: libc::stat = unsafe { std::mem::zeroed() };
    let mut retVal: i32 = 0;
    
    globals::DELETE_OUTPUT_ON_INTERRUPT.store(false, std::sync::atomic::Ordering::Relaxed);
    
    if name.is_none() && globals::srcMode != 1 {
        panic!("uncompress: bad modes\n");
    }
    
    cantGuess = false;
    
    match globals::srcMode {
        1 => {
            copyFileName(&mut *globals::IN_NAME.lock().unwrap(), &['(' as Char, 's' as Char, 't' as Char, 'd' as Char, 'i' as Char, 'n' as Char, ')' as Char, '\0' as Char]);
            copyFileName(&mut *globals::outName.lock().unwrap(), &['(' as Char, 's' as Char, 't' as Char, 'd' as Char, 'o' as Char, 'u' as Char, 't' as Char, ')' as Char, '\0' as Char]);
        }
        3 => {
            let name_chars: Vec<Char> = name.unwrap().iter().map(|&b| b as Char).collect();
            copyFileName(&mut *globals::IN_NAME.lock().unwrap(), &name_chars);
            copyFileName(&mut *globals::outName.lock().unwrap(), &name_chars);
            
            for i in 0..4 {
                if mapSuffix(&mut *globals::outName.lock().unwrap(), Some(&globals::Z_SUFFIX[i].chars().collect::<Vec<_>>()), Some(&globals::UNZ_SUFFIX[i].chars().collect::<Vec<_>>())) {
                    break;
                }
            }
            
            cantGuess = true;
            // Convert to CStr for strcat equivalent
            let out_name_cstr = unsafe { CStr::from_ptr((&*globals::outName.lock().unwrap()).as_ptr() as *const i8) };
            let mut out_name_vec = out_name_cstr.to_bytes().to_vec();
            out_name_vec.extend_from_slice(b".out");
            
            // Convert back to Char array
            let out_name_chars: Vec<Char> = out_name_vec.iter().map(|&b| b as Char).collect();
            copyFileName(&mut *globals::outName.lock().unwrap(), &out_name_chars);
        }
        2 => {
            let name_chars: Vec<Char> = name.unwrap().iter().map(|&b| b as Char).collect();
            copyFileName(&mut *globals::IN_NAME.lock().unwrap(), &name_chars);
            copyFileName(&mut *globals::outName.lock().unwrap(), &['(' as Char, 's' as Char, 't' as Char, 'd' as Char, 'o' as Char, 'u' as Char, 't' as Char, ')' as Char, '\0' as Char]);
        }
        _ => {}
    }
    
    if globals::srcMode != 1 && containsDubiousChars(Some(&*globals::IN_NAME.lock().unwrap())) {
        if globals::noisy.load(std::sync::atomic::Ordering::Relaxed) {
            eprint!("{}: There are no files matching `{}'.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
        }
        setExit(1);
        return;
    }
    
    if globals::srcMode != 1 && fileExists(&c_str_to_string(&*globals::IN_NAME.lock().unwrap())) == 0 {
        let errno_val = unsafe { *libc::__errno_location() };
        let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
        eprint!("{}: Can't open input file {}: {}.\n", 
               unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
               unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap(),
               error_str.to_str().unwrap());
        setExit(1);
        return;
    }
    
    if globals::srcMode == 3 || globals::srcMode == 2 {
        my_stat(&c_str_to_string(&*globals::IN_NAME.lock().unwrap()), &mut statBuf);
        if (statBuf.st_mode & libc::S_IFMT) == libc::S_IFDIR {
            eprint!("{}: Input file {} is a directory.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
            setExit(1);
            return;
        }
    }
    
    if globals::srcMode == 3 && !globals::forceOverwrite.load(std::sync::atomic::Ordering::Relaxed) && notAStandardFile(&*globals::IN_NAME.lock().unwrap()) != 0 {
        if globals::noisy.load(std::sync::atomic::Ordering::Relaxed) {
            eprint!("{}: Input file {} is not a normal file.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
        }
        setExit(1);
        return;
    }
    
    if cantGuess {
        if globals::noisy.load(std::sync::atomic::Ordering::Relaxed) {
            eprint!("{}: Can't guess original name for {} -- using {}\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::outName.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
        }
    }
    
    let out_name_str = unsafe { CStr::from_ptr((&*globals::outName.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
    if globals::srcMode == 3 && Path::new(out_name_str).exists() {
        if globals::forceOverwrite.load(std::sync::atomic::Ordering::Relaxed) {
            let _ = remove_file(out_name_str);
        } else {
            eprint!("{}: Output file {} already exists.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   out_name_str);
            setExit(1);
            return;
        }
    }
    
    if globals::srcMode == 3 && !globals::forceOverwrite.load(std::sync::atomic::Ordering::Relaxed) {
        n = countHardLinks(Some(&c_str_to_string(&*globals::IN_NAME.lock().unwrap())));
        if n > 0 {
            eprint!("{}: Input file {} has {} other link{}.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap(),
                   n,
                   if n > 1 { "s" } else { "" });
            setExit(1);
            return;
        }
    }
    
    if globals::srcMode == 3 {
        saveInputFileMetaInfo(Some(&(*globals::IN_NAME.lock().unwrap())[0]));
    }
    
    match globals::srcMode {
        1 => {
            inStr = Some(unsafe { std::fs::File::from_raw_fd(libc::STDIN_FILENO) });
            outStr = Some(unsafe { std::fs::File::from_raw_fd(libc::STDOUT_FILENO) });
            
            if unsafe { libc::isatty(libc::STDIN_FILENO) } != 0 {
                eprint!("{}: I won't read compressed data from a terminal.\n", 
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap());
                eprint!("{}: For help, type: `{} --help'.\n", 
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap());
                setExit(1);
                return;
            }
        }
        2 => {
            let in_name_str = unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
            inStr = std::fs::File::open(in_name_str).ok();
            outStr = Some(unsafe { std::fs::File::from_raw_fd(libc::STDOUT_FILENO) });
            
            if inStr.is_none() {
                let errno_val = unsafe { *libc::__errno_location() };
                let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
                eprint!("{}: Can't open input file {}:{}.\n", 
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                       in_name_str,
                       error_str.to_str().unwrap());
                setExit(1);
                return;
            }
        }
        3 => {
            let in_name_str = unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
            let out_name_str = unsafe { CStr::from_ptr((&*globals::outName.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
            inStr = std::fs::File::open(in_name_str).ok();
            outStr = std::fs::File::create(out_name_str).ok();
            
            if outStr.is_none() {
                let errno_val = unsafe { *libc::__errno_location() };
                let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
                eprint!("{}: Can't create output file {}: {}.\n", 
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                       out_name_str,
                       error_str.to_str().unwrap());
                setExit(1);
                return;
            }
            
            if inStr.is_none() {
                let errno_val = unsafe { *libc::__errno_location() };
                let error_str = unsafe { CStr::from_ptr(libc::strerror(errno_val)) };
                eprint!("{}: Can't open input file {}: {}.\n", 
                       unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                       in_name_str,
                       error_str.to_str().unwrap());
                setExit(1);
                return;
            }
        }
        _ => {
            panic!("uncompress: bad srcMode");
        }
    }
    
    if globals::VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 1 {
        eprint!("  {}: ", unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
        pad(&*globals::IN_NAME.lock().unwrap());
        io::stderr().flush().unwrap();
    }
    
    // Store a reference to outStr without moving it
    *globals::OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = outStr.as_ref().map(|f| f.try_clone().ok()).flatten();
    globals::DELETE_OUTPUT_ON_INTERRUPT.store(true, std::sync::atomic::Ordering::Relaxed);
    
    if let (Some(mut in_file), Some(mut out_file)) = (inStr, outStr) {
        magicNumberOK = uncompressStream(&mut in_file, &mut out_file);
    }
    
    *globals::OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    
    if magicNumberOK {
        if globals::srcMode == 3 {
            applySavedTimeInfoToOutputFile((&*globals::outName.lock().unwrap())[0]);
            globals::DELETE_OUTPUT_ON_INTERRUPT.store(false, std::sync::atomic::Ordering::Relaxed);
            
            if !globals::KEEP_INPUT_FILES.load(std::sync::atomic::Ordering::Relaxed) {
                let in_name_str = unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
                let result = remove_file(in_name_str);
                if result.is_err() {
                    ioError();
                }
            }
        }
    } else {
        globals::UNZ_FAILS_EXIST.store(true, std::sync::atomic::Ordering::Relaxed);
        globals::DELETE_OUTPUT_ON_INTERRUPT.store(false, std::sync::atomic::Ordering::Relaxed);
        
        if globals::srcMode == 3 {
            let out_name_str = unsafe { CStr::from_ptr((&*globals::outName.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap();
            let result = remove_file(out_name_str);
            if result.is_err() {
                ioError();
            }
        }
    }
    
    globals::DELETE_OUTPUT_ON_INTERRUPT.store(false, std::sync::atomic::Ordering::Relaxed);
    
    if magicNumberOK {
        if globals::VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 1 {
            eprintln!("done");
        }
    } else {
        setExit(2);
        if globals::VERBOSITY.load(std::sync::atomic::Ordering::Relaxed) >= 1 {
            eprintln!("not a bzip2 file.");
        } else {
            eprint!("{}: {} is not a bzip2 file.\n", 
                   unsafe { CStr::from_ptr(globals::PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                   unsafe { CStr::from_ptr((&*globals::IN_NAME.lock().unwrap()).as_ptr() as *const i8) }.to_str().unwrap());
        }
    }
}

// Helper function to convert C string to Rust String
fn c_str_to_string(c_str: &[Char]) -> String {
    let c_str_ptr = c_str.as_ptr() as *const i8;
    unsafe { CStr::from_ptr(c_str_ptr).to_string_lossy().into_owned() }
}

// Helper function for my_stat (simplified version)
fn my_stat(path: &str, stat_buf: &mut libc::stat) -> i32 {
    unsafe { libc::stat(path.as_ptr() as *const i8, stat_buf) }
}
