use libc::FILE;
use std::fs::File;
use crate::*;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::path::Path;
use lazy_static::lazy_static;
use std::alloc;
use std::env;
use std::fs;
use std::io;
use std::process;
use std::ptr;
use std::io::BufReader;
use std::io::ErrorKind;
use std::io::Read;
use std::io::Seek;
use std::io::Stdin;
use std::io::Write;
use std::io::stdin;
use std::io::stdout;
use std::process::exit;
use std::sync::Mutex;
use std::alloc::Layout;
use std::alloc::alloc;
use std::os::unix::fs::MetadataExt;
use std::ffi::CStr;
use std::ffi::CString;
use rand::Rng;
use std::os::fd::AsRawFd;
use std::os::fd::FromRawFd;
use std::os::raw::c_char;
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

pub fn myMalloc(n: Int32) -> Option<*mut u8> {
    let layout = match Layout::from_size_align(n as usize, 1) {
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
    // In Rust, we don't need to manually allocate memory like in C
    // Instead, we can directly create a Box with the default values
    Some(Box::new(Cell {
        name: None,
        link: None,
    }))
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
pub fn addFlagsFromEnvVar(argList: &mut Option<Box<Cell>>, varName: Char) {
    lazy_static! {
        static ref TMP_NAME: Mutex<[Char; 1034]> = Mutex::new(['\0'; 1034]);
    }

    let env_var = env::var(varName.to_string()).ok()
        .and_then(|s| CString::new(s).ok())
        .map(|cstr| cstr.as_ptr());

    if let Some(env_ptr) = env_var {
        let env_cstr = unsafe { CStr::from_ptr(env_ptr) };
        if let Ok(env_value) = env_cstr.to_str() {
            let mut p = env_value;
            let mut i: Int32;
            let mut j: Int32;
            let mut k: Int32;

            loop {
                if p.is_empty() {
                    break;
                }

                // Skip leading whitespace
                p = p.trim_start();

                // Find next whitespace or end of string
                let end = p.find(|c: char| c.is_whitespace()).unwrap_or(p.len());
                if end > 0 {
                    k = end as Int32;
                    if k > (1034 - 10) {
                        k = 1034 - 10;
                    }

                    let mut tmp_name = TMP_NAME.lock().unwrap();
                    for j in 0..k as usize {
                        tmp_name[j] = p.chars().nth(j).unwrap_or('\0');
                    }
                    tmp_name[k as usize] = '\0';

                    // Assuming APPEND_FLAG is implemented elsewhere
                    APPEND_FLAG(argList, &tmp_name[..k as usize]);
                }

                p = &p[end..];
            }
        }
    }
}

// Note: The APPEND_FLAG function would need to be implemented separately
// This is a placeholder for the actual implementation
fn APPEND_FLAG(_argList: &mut Option<Box<Cell>>, _flag: &[Char]) {
    // Implementation would go here
}

pub fn snocString(root: Option<Box<Cell>>, name: &Char) -> Option<Box<Cell>> {
    if root.is_none() {
        let mut tmp = mkCell()?;
        let name_len = name.to_string().len();
        tmp.name = Some(Box::new(*name));
        Some(tmp)
    } else {
        let mut root = root.unwrap();
        let mut tmp = &mut root;
        
        while tmp.link.is_some() {
            tmp = tmp.link.as_mut().unwrap();
        }
        
        tmp.link = snocString(tmp.link.take(), name);
        Some(root)
    }
}
pub fn compressedStreamEOF() {
    if noisy.load(Ordering::Relaxed) {
        eprintln!(
            "\n{}: Compressed file ends unexpectedly;\n\tperhaps it is corrupted?  *Possible* reason follows.",
            PROG_NAME.lock().unwrap().iter().collect::<String>()
        );
        perror(&PROG_NAME.lock().unwrap().iter().collect::<String>());
        showFileNames();
        cadvise();
    }
    cleanUpAndFail(2);
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

pub fn mySIGSEGVorSIGBUScatcher(n: IntNative) {
    let msg = if OPMODE.load(Ordering::Relaxed) == 1 {
        ": Caught a SIGSEGV or SIGBUS whilst compressing.\n\n   Possible causes are (most likely first):\n   (1) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (2) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (3) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (1) and (2).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (1)\n   or (2), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    } else {
        ": Caught a SIGSEGV or SIGBUS whilst decompressing.\n\n   Possible causes are (most likely first):\n   (1) The compressed data is corrupted, and bzip2's usual checks\n       failed to detect this.  Try bzip2 -tvv my_file.bz2.\n   (2) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (3) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (4) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (2) and (3).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (2)\n   or (3), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n"
    };

    let stderr = io::stderr();
    let mut stderr = stderr.lock();

    let _ = writeln!(stderr);
    
    {
        let prog_name = PROG_NAME.lock().unwrap();
        let prog_name_str = prog_name.iter().take_while(|&&c| c != '\0').collect::<String>();
        let _ = write!(stderr, "{}", prog_name_str);
    }

    let _ = write!(stderr, "{}", msg);

    let input_msg = "\tInput file = ";
    let _ = write!(stderr, "{}", input_msg);
    
    {
        let in_name = IN_NAME.lock().unwrap();
        let in_name_str = in_name.iter().take_while(|&&c| c != '\0').collect::<String>();
        let _ = write!(stderr, "{}", in_name_str);
    }

    let _ = writeln!(stderr);

    let output_msg = "\tOutput file = ";
    let _ = write!(stderr, "{}", output_msg);
    
    {
        let out_name = outName.lock().unwrap();
        let out_name_str = out_name.iter().take_while(|&&c| c != '\0').collect::<String>();
        let _ = write!(stderr, "{}", out_name_str);
    }

    let _ = writeln!(stderr);

    if OPMODE.load(Ordering::Relaxed) == 1 {
        setExit(3);
    } else {
        setExit(2);
    }

    process::exit(EXIT_VALUE.load(Ordering::Relaxed));
}
pub fn testStream(mut zStream: File) -> Result<bool, Box<dyn std::error::Error>> {
    let mut bzf: Option<Box<BzFile>> = None;
    let mut bzerr: Int32 = 0;
    let mut bzerr_dummy: Int32 = 0;
    let mut streamNo: Int32 = 0;
    let mut obuf = [0u8; 5000];
    let mut unused = [0u8; 5000];
    let mut nUnused: u32 = 0;
    let mut unusedTmp: Option<Box<[u8]>> = None;

    if zStream.stream_position().is_err() {
        return Err(Box::new(std::io::Error::new(ErrorKind::Other, "IO error")));
    }

    loop {
        bzf = BZ2_bzReadOpen(
            Some(&mut bzerr),
            Some(zStream.try_clone()?),
            VERBOSITY.load(Ordering::SeqCst),
            smallMode.load(Ordering::SeqCst) as Int32,
            Some(unsafe { std::mem::transmute::<&[u8], &[Char]>(&unused[..nUnused as usize]) }),
            nUnused as Int32,
        );

        if bzf.is_none() || bzerr != 0 {
            break;
        }

        streamNo += 1;
        bzerr = 0;

        while bzerr == 0 {
            let obuf_len = obuf.len() as Int32;
            BZ2_bzRead(
                Some(&mut bzerr),
                bzf.as_mut().map(|b| &mut **b),
                Some(&mut obuf),
                obuf_len,
            );
            if bzerr == -5 {
                break;
            }
        }

        if bzerr != 4 {
            break;
        }

        BZ2_bzReadGetUnused(
            Some(&mut bzerr),
            bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) }),
            Some(&mut unusedTmp),
            Some(&mut nUnused),
        );
        if bzerr != 0 {
            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(
                std::ffi::CString::new("test:bzReadGetUnused").unwrap().as_ptr()
            )});
        }

        if let Some(ref tmp) = unusedTmp {
            for i in 0..nUnused as usize {
                if i < unused.len() {
                    unused[i] = tmp[i];
                }
            }
        }

        BZ2_bzReadClose(
            Some(&mut bzerr),
            bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) }),
        );
        if bzerr != 0 {
            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(
                std::ffi::CString::new("test:bzReadGetUnused").unwrap().as_ptr()
            )});
        }

        if nUnused == 0 && myfeof(&mut zStream) {
            return Ok(true);
        }
    }

    if zStream.stream_position().is_err() {
        return Err(Box::new(std::io::Error::new(ErrorKind::Other, "IO error")));
    }

    if let Err(_) = zStream.sync_all() {
        return Err(Box::new(std::io::Error::new(ErrorKind::Other, "IO error")));
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 2 {
        eprint!("\n    ");
    }

    match bzerr {
        -9 => {
            configError();
            Err(Box::new(std::io::Error::new(ErrorKind::Other, "Config error")))
        }
        -6 => {
            ioError();
            Err(Box::new(std::io::Error::new(ErrorKind::Other, "IO error")))
        }
        -4 => {
            eprintln!("data integrity (CRC) error in data");
            Ok(false)
        }
        -3 => {
            outOfMemory();
            Err(Box::new(std::io::Error::new(ErrorKind::Other, "Out of memory")))
        }
        -7 => {
            eprintln!("file ends unexpectedly");
            Ok(false)
        }
        -5 => {
            if streamNo == 1 {
                eprintln!("bad magic number (file not created by bzip2)");
                Ok(false)
            } else {
                if noisy.load(Ordering::SeqCst) {
                    eprintln!("trailing garbage after EOF ignored");
                }
                Ok(true)
            }
        }
        _ => {
            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(
                std::ffi::CString::new("test:unexpected error").unwrap().as_ptr()
            )});
            Err(Box::new(std::io::Error::new(ErrorKind::Other, "Unexpected error")))
        }
    }
}
pub fn testf(name: Option<&[Char]>) {
    let mut in_str: Option<File> = None;
    let mut in_str_idx: Option<std::io::Stdin> = None;
    let mut all_ok: Bool = 0;
    let mut stat_buf = std::mem::MaybeUninit::<libc::stat>::uninit();

    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);

    if name.is_none() && srcMode != 1 {
        panic("testf: bad modes\n".as_ptr() as *const Char);
    }

    {
        let mut out_name = outName.lock().unwrap();
        copyFileName(&mut *out_name, &['(', 'n', 'o', 'n', 'e', ')']);
    }

    {
        let mut in_name = IN_NAME.lock().unwrap();
        match srcMode {
            1 => copyFileName(&mut *in_name, &['(', 's', 't', 'd', 'i', 'n', ')']),
            2 | 3 => {
                if let Some(name) = name {
                    copyFileName(&mut *in_name, name);
                }
            }
            _ => panic("testf: bad srcMode".as_ptr() as *const Char),
        }
    }

    if srcMode != 1 {
        let in_name = IN_NAME.lock().unwrap();
        if containsDubiousChars(Some(&*in_name)) {
            if noisy.load(Ordering::SeqCst) {
                let prog_name = PROG_NAME.lock().unwrap();
                eprintln!(
                    "{}: There are no files matching `{}'.",
                    String::from_iter(prog_name.iter().take_while(|&&c| c != '\0')),
                    String::from_iter(in_name.iter().take_while(|&&c| c != '\0'))
                );
            }
            setExit(1);
            return;
        }

        let in_name_str = String::from_iter(in_name.iter().take_while(|&&c| c != '\0'));
        if fileExists(&in_name_str) == 0 {
            let prog_name = PROG_NAME.lock().unwrap();
            eprintln!(
                "{}: Can't open input {}: {}.",
                String::from_iter(prog_name.iter().take_while(|&&c| c != '\0')),
                in_name_str,
                std::io::Error::last_os_error()
            );
            setExit(1);
            return;
        }
    }

    match srcMode {
        1 => {
            if unsafe { libc::isatty(libc::STDIN_FILENO) } != 0 {
                let prog_name = PROG_NAME.lock().unwrap();
                eprintln!(
                    "{}: I won't read compressed data from a terminal.",
                    String::from_iter(prog_name.iter().take_while(|&&c| c != '\0'))
                );
                eprintln!(
                    "{}: For help, type: `{} --help'.",
                    String::from_iter(prog_name.iter().take_while(|&&c| c != '\0')),
                    String::from_iter(prog_name.iter().take_while(|&&c| c != '\0'))
                );
                setExit(1);
                return;
            }
            // Create a temporary file to read stdin into
            let temp_path = std::env::temp_dir().join("bzip2_temp");
            let mut temp_file = File::create(&temp_path).expect("Failed to create temporary file");
            std::io::copy(&mut std::io::stdin(), &mut temp_file).expect("Failed to copy stdin to temp file");
            temp_file.seek(std::io::SeekFrom::Start(0)).expect("Failed to seek temp file");
            in_str = Some(temp_file);
        }
        2 | 3 => {
            let in_name = IN_NAME.lock().unwrap();
            let in_name_str = String::from_iter(in_name.iter().take_while(|&&c| c != '\0'));
            in_str = File::open(&in_name_str).ok();
            if in_str.is_none() {
                let prog_name = PROG_NAME.lock().unwrap();
                eprintln!(
                    "{}: Can't open input file {}: {}.",
                    String::from_iter(prog_name.iter().take_while(|&&c| c != '\0')),
                    in_name_str,
                    std::io::Error::last_os_error()
                );
                setExit(1);
                return;
            }
        }
        _ => panic("testf: bad srcMode".as_ptr() as *const Char),
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        let in_name = IN_NAME.lock().unwrap();
        let in_name_str = String::from_iter(in_name.iter().take_while(|&&c| c != '\0'));
        eprint!("  {}: ", in_name_str);
        pad(&*in_name);
        std::io::stderr().flush().unwrap();
    }

    {
        let mut output_handle = OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap();
        *output_handle = None;
    }

    all_ok = match srcMode {
        1 | 2 | 3 => {
            if let Some(stream) = in_str {
                testStream(stream).unwrap_or(false) as Bool
            } else {
                0
            }
        }
        _ => 0,
    };

    if all_ok != 0 && VERBOSITY.load(Ordering::SeqCst) >= 1 {
        eprintln!("ok");
    }

    if all_ok == 0 {
        TEST_FAILS_EXIST.store(true, Ordering::SeqCst);
    }
}
pub fn compressStream(stream: &mut (impl Read + Seek), zStream: &mut File) {
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
    let mut buf_nin = [0u8; 32];
    let mut buf_nout = [0u8; 32];
    let mut nbytes_in = UInt64 { b: [0; 8] };
    let mut nbytes_out = UInt64 { b: [0; 8] };
    let mut nbytes_in_d: f64 = 0.0;
    let mut nbytes_out_d: f64 = 0.0;

    if stream.seek(std::io::SeekFrom::Current(0)).is_err() {
        ioError();
    }
    if zStream.seek(std::io::SeekFrom::Current(0)).is_err() {
        ioError();
    }

    bzf = BZ2_bzWriteOpen(
        Some(&mut bzerr),
        Some(zStream.try_clone().unwrap()),
        BLOCK_SIZE_100K.load(Ordering::SeqCst),
        VERBOSITY.load(Ordering::SeqCst),
        WORK_FACTOR.load(Ordering::SeqCst),
    );

    if bzerr != 0 {
        goto_errhandler(&mut bzerr, &mut bzf, &mut bzerr_dummy, &mut nbytes_in_lo32, &mut nbytes_in_hi32, &mut nbytes_out_lo32, &mut nbytes_out_hi32);
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 2 {
        eprintln!("\n");
    }

    loop {
        if myfeof(stream) {
            break;
        }

        match stream.read(&mut ibuf) {
            Ok(n) => nIbuf = n as Int32,
            Err(_) => {
                ioError();
            }
        }

        if nIbuf > 0 {
            BZ2_bzWrite(
                Some(&mut bzerr),
                bzf.as_mut().map(|b| unsafe { &mut *(b.as_mut() as *mut BzFile as *mut BZFILE) }),
                Some(&ibuf[..nIbuf as usize]),
                nIbuf,
            );
        }

        if bzerr != 0 {
            goto_errhandler(&mut bzerr, &mut bzf, &mut bzerr_dummy, &mut nbytes_in_lo32, &mut nbytes_in_hi32, &mut nbytes_out_lo32, &mut nbytes_out_hi32);
        }
    }

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
        goto_errhandler(&mut bzerr, &mut bzf, &mut bzerr_dummy, &mut nbytes_in_lo32, &mut nbytes_in_hi32, &mut nbytes_out_lo32, &mut nbytes_out_hi32);
    }

    if zStream.seek(std::io::SeekFrom::Current(0)).is_err() {
        ioError();
    }

    if let Err(_) = zStream.flush() {
        ioError();
    }

    if zStream.as_raw_fd() != std::io::stdout().as_raw_fd() {
        fd = zStream.as_raw_fd();
        if fd < 0 {
            ioError();
        }
        applySavedFileAttrToOutputFile(fd);
        if let Err(_) = zStream.sync_all() {
            ioError();
        }
        *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if stream.seek(std::io::SeekFrom::Current(0)).is_err() {
        ioError();
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        if nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0 {
            eprintln!(" no data compressed.");
        } else {
            uInt64_from_UInt32s(&mut nbytes_in, nbytes_in_lo32, nbytes_in_hi32);
            uInt64_from_UInt32s(&mut nbytes_out, nbytes_out_lo32, nbytes_out_hi32);
            nbytes_in_d = uInt64_to_double(&nbytes_in);
            nbytes_out_d = uInt64_to_double(&nbytes_out);
            uInt64_toAscii(&mut buf_nin, &nbytes_in);
            uInt64_toAscii(&mut buf_nout, &nbytes_out);
            eprintln!(
                "{:6.3}:1, {:6.3} bits/byte, {:5.2}% saved, {} in, {} out.",
                nbytes_in_d / nbytes_out_d,
                (8.0 * nbytes_out_d) / nbytes_in_d,
                100.0 * (1.0 - (nbytes_out_d / nbytes_in_d)),
                String::from_utf8_lossy(&buf_nin),
                String::from_utf8_lossy(&buf_nout)
            );
        }
    }

    fn goto_errhandler(
        bzerr: &mut Int32,
        bzf: &mut Option<Box<BzFile>>,
        bzerr_dummy: &mut Int32,
        nbytes_in_lo32: &mut UInt32,
        nbytes_in_hi32: &mut UInt32,
        nbytes_out_lo32: &mut UInt32,
        nbytes_out_hi32: &mut UInt32,
    ) -> ! {
        BZ2_bzWriteClose64(
            Some(bzerr_dummy),
            bzf.as_mut().map(|b| unsafe { &mut *(b.as_mut() as *mut BzFile as *mut BZFILE) }),
            1,
            Some(nbytes_in_lo32),
            Some(nbytes_in_hi32),
            Some(nbytes_out_lo32),
            Some(nbytes_out_hi32),
        );

        match *bzerr {
            -9 => configError(),
            -3 => outOfMemory(),
            -6 => ioError(),
            _ => panic(b"compress:unexpected error\0".as_ptr() as *const Char),
        }

        panic(b"compress:end\0".as_ptr() as *const Char);
    }
}

pub fn uncompressStream(zStream: &mut File, stream: &mut File) -> bool {
    let mut bzf: Option<Box<BzFile>> = None;
    let mut bzerr: Int32 = 0;
    let mut bzerr_dummy: Int32 = 0;
    let mut nread: Int32 = 0;
    let mut streamNo: Int32 = 0;
    let mut obuf: [UChar; 5000] = [0; 5000];
    let mut unused: [UChar; 5000] = [0; 5000];
    let mut nUnused: u32 = 0;
    let mut unusedTmp: Option<Box<[u8]>> = None;

    if stream.stream_error() || zStream.stream_error() {
        ioError();
        return false;
    }

    loop {
        bzf = BZ2_bzReadOpen(
            Some(&mut bzerr),
            zStream.try_clone().ok(),
            VERBOSITY.load(Ordering::SeqCst),
            smallMode.load(Ordering::SeqCst) as Int32,
            Some(unsafe { std::mem::transmute::<&[UChar], &[Char]>(&unused[..nUnused as usize]) }),
            nUnused as Int32,
        );

        if bzf.is_none() || bzerr != 0 {
            break;
        }

        streamNo += 1;
        while bzerr == 0 {
            let mut bzf_ref = bzf.as_mut().map(|b| &mut **b);
            nread = BZ2_bzRead(Some(&mut bzerr), bzf_ref, Some(&mut obuf), 5000);
            if bzerr == -5 {
                if forceOverwrite.load(Ordering::SeqCst) {
                    zStream.rewind().unwrap();
                    loop {
                        if myfeof(zStream) {
                            break;
                        }
                        nread = zStream.read(&mut obuf).unwrap() as Int32;
                        if zStream.stream_error() {
                            ioError();
                            return false;
                        }
                        if nread > 0 {
                            stream.write_all(&obuf[..nread as usize]).unwrap();
                            if stream.stream_error() {
                                ioError();
                                return false;
                            }
                        }
                    }
                    break;
                } else {
                    let mut bzf_ref = bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) });
                    BZ2_bzReadClose(Some(&mut bzerr_dummy), bzf_ref);
                    match bzerr {
                        -9 => configError(),
                        -6 => ioError(),
                        -4 => crcError(),
                        -3 => outOfMemory(),
                        -7 => compressedStreamEOF(),
                        -5 => {
                            if streamNo == 1 {
                                return false;
                            } else if noisy.load(Ordering::SeqCst) {
                                eprintln!("\n{:?}: {:?}: trailing garbage after EOF ignored", 
                                    PROG_NAME.lock().unwrap(), IN_NAME.lock().unwrap());
                            }
                            return true;
                        }
                        _ => {
                            let msg = std::ffi::CString::new("decompress:unexpected error").unwrap();
                            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(msg.as_ptr()) });
                        }
                    }
                }
            }

            if (bzerr == 0 || bzerr == 4) && nread > 0 {
                stream.write_all(&obuf[..nread as usize]).unwrap();
                if stream.stream_error() {
                    ioError();
                    return false;
                }
            }
        }

        if bzerr != 4 {
            break;
        }

        let mut bzf_ref = bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) });
        BZ2_bzReadGetUnused(Some(&mut bzerr), bzf_ref, Some(&mut unusedTmp), Some(&mut nUnused));
        if bzerr != 0 {
            let msg = std::ffi::CString::new("decompress:bzReadGetUnused").unwrap();
            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(msg.as_ptr()) });
        }

        if let Some(ref unused_data) = unusedTmp {
            for i in 0..nUnused as usize {
                unused[i] = unused_data[i];
            }
        }

        let mut bzf_ref = bzf.as_mut().map(|b| unsafe { std::mem::transmute::<&mut BzFile, &mut BZFILE>(&mut **b) });
        BZ2_bzReadClose(Some(&mut bzerr), bzf_ref);
        if bzerr != 0 {
            let msg = std::ffi::CString::new("decompress:bzReadGetUnused").unwrap();
            panic(unsafe { std::mem::transmute::<*const i8, *const Char>(msg.as_ptr()) });
        }

        if nUnused == 0 && myfeof(zStream) {
            break;
        }
    }

    if zStream.stream_error() {
        ioError();
        return false;
    }

    if !stream.stream_is_stdout() {
        let fd = stream.as_raw_fd();
        if fd < 0 {
            ioError();
            return false;
        }
        applySavedFileAttrToOutputFile(fd);
    }

    if let Err(_) = zStream.sync_all() {
        ioError();
        return false;
    }

    if stream.stream_error() {
        ioError();
        return false;
    }

    if let Err(_) = stream.flush() {
        ioError();
        return false;
    }

    if !stream.stream_is_stdout() {
        if let Err(_) = stream.sync_all() {
            ioError();
            return false;
        }
        *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 2 {
        eprint!("\n    ");
    }

    true
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
pub fn compress(name: Option<&[Char]>) {
    enum InFile {
        Stdin(std::io::Cursor<Vec<u8>>),
        File(std::io::BufReader<std::fs::File>),
    }

    impl std::io::Read for InFile {
        fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
            match self {
                InFile::Stdin(cursor) => cursor.read(buf),
                InFile::File(reader) => reader.read(buf),
            }
        }
    }

    impl std::io::Seek for InFile {
        fn seek(&mut self, pos: std::io::SeekFrom) -> std::io::Result<u64> {
            match self {
                InFile::Stdin(cursor) => cursor.seek(pos),
                InFile::File(reader) => reader.seek(pos),
            }
        }
    }

    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
    
    if name.is_none() && srcMode != 1 {
        panic(&"compress: bad modes\n".chars().collect::<Vec<_>>()[0]);
    }

    match srcMode {
        1 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], &"(stdin)".chars().collect::<Vec<_>>());
            copyFileName(&mut outName.lock().unwrap()[..], &"(stdout)".chars().collect::<Vec<_>>());
        },
        3 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut outName.lock().unwrap()[..], name.unwrap());
            let mut out_name = outName.lock().unwrap();
            let len = out_name.iter().position(|&c| c == '\0').unwrap_or(out_name.len());
            let suffix = ".bz2".chars().collect::<Vec<_>>();
            for (i, &c) in suffix.iter().enumerate() {
                if i + len < out_name.len() {
                    out_name[i + len] = c;
                }
            }
        },
        2 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut outName.lock().unwrap()[..], &"(stdout)".chars().collect::<Vec<_>>());
        },
        _ => panic(&"compress: bad srcMode".chars().collect::<Vec<_>>()[0]),
    }

    if srcMode != 1 && containsDubiousChars(Some(&IN_NAME.lock().unwrap()[..])) {
        if noisy.load(Ordering::SeqCst) {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
            eprintln!("{}: There are no files matching `{}'.", prog_name_str, in_name_str);
        }
        setExit(1);
        return;
    }

    if srcMode != 1 && fileExists(&IN_NAME.lock().unwrap().iter().collect::<String>()) == 0 {
        let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
        let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
        eprintln!("{}: Can't open input file {}: {}.", prog_name_str, in_name_str, io::Error::last_os_error());
        setExit(1);
        return;
    }

    for i in 0..4 {
        if hasSuffix(Some(&IN_NAME.lock().unwrap()[..]), Some(&Z_SUFFIX[i].chars().collect::<Vec<_>>())) {
            if noisy.load(Ordering::SeqCst) {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
                eprintln!("{}: Input file {} already has {} suffix.", prog_name_str, in_name_str, Z_SUFFIX[i]);
            }
            setExit(1);
            return;
        }
    }

    if srcMode == 3 || srcMode == 2 {
        let in_name_str = IN_NAME.lock().unwrap().iter().collect::<String>();
        let metadata = match std::fs::metadata(&Path::new(&in_name_str)) {
            Ok(m) => m,
            Err(e) => {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
                eprintln!("{}: Input file {} is a directory.", prog_name_str, in_name_str);
                setExit(1);
                return;
            }
        };
        if metadata.is_dir() {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
            eprintln!("{}: Input file {} is a directory.", prog_name_str, in_name_str);
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) && notAStandardFile(&IN_NAME.lock().unwrap()[..]) != 0 {
        if noisy.load(Ordering::SeqCst) {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
            eprintln!("{}: Input file {} is not a normal file.", prog_name_str, in_name_str);
        }
        setExit(1);
        return;
    }

    if srcMode == 3 && fileExists(&outName.lock().unwrap().iter().collect::<String>()) != 0 {
        if forceOverwrite.load(Ordering::SeqCst) {
            let out_name_str = outName.lock().unwrap().iter().collect::<String>();
            if let Err(e) = std::fs::remove_file(&Path::new(&out_name_str)) {
                ioError();
            }
        } else {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
            let out_name_bytes: Vec<u8> = outName.lock().unwrap().iter().map(|&c| c as u8).collect();
            let out_name_str = CStr::from_bytes_with_nul(&out_name_bytes).unwrap().to_str().unwrap();
            eprintln!("{}: Output file {} already exists.", prog_name_str, out_name_str);
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) {
        let n = countHardLinks(Some(&IN_NAME.lock().unwrap().iter().collect::<String>()));
        if n > 0 {
            let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
            let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
            let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
            eprintln!("{}: Input file {} has {} other link{}.", prog_name_str, in_name_str, n, if n > 1 { "s" } else { "" });
            setExit(1);
            return;
        }
    }

    if srcMode == 3 {
        saveInputFileMetaInfo(Some(&IN_NAME.lock().unwrap()[0]));
    }

    let mut in_file: Option<InFile> = match srcMode {
        1 => {
            let mut buffer = Vec::new();
            match io::stdin().read_to_end(&mut buffer) {
                Ok(_) => Some(InFile::Stdin(std::io::Cursor::new(buffer))),
                Err(e) => {
                    let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                    let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                    eprintln!("{}: Failed to read stdin: {}.", prog_name_str, e);
                    setExit(1);
                    return;
                }
            }
        },
        2 | 3 => {
            let in_name_str = IN_NAME.lock().unwrap().iter().collect::<String>();
            match File::open(&Path::new(&in_name_str)) {
                Ok(f) => Some(InFile::File(std::io::BufReader::new(f))),
                Err(e) => {
                    let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                    let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                    let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                    let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
                    eprintln!("{}: Can't open input file {}: {}.", prog_name_str, in_name_str, e);
                    setExit(1);
                    return;
                }
            }
        },
        _ => None,
    };

    let mut out_file: Option<File> = match srcMode {
        1 | 2 => {
            if unsafe { libc::isatty(libc::STDOUT_FILENO) } != 0 {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                eprintln!("{}: I won't write compressed data to a terminal.", prog_name_str);
                eprintln!("{}: For help, type: `{} --help'.", prog_name_str, prog_name_str);
                setExit(1);
                return;
            }
            let stdout_fd = libc::STDOUT_FILENO;
            let fd = unsafe { libc::dup(stdout_fd) };
            if fd == -1 {
                let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                let e = io::Error::last_os_error();
                eprintln!("{}: Failed to duplicate stdout: {}.", prog_name_str, e);
                setExit(1);
                return;
            }
            Some(unsafe { File::from_raw_fd(fd) })
        },
        3 => {
            let out_name_str = outName.lock().unwrap().iter().collect::<String>();
            match File::create(&Path::new(&out_name_str)) {
                Ok(f) => Some(f),
                Err(e) => {
                    let prog_name_bytes: Vec<u8> = PROG_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
                    let prog_name_str = CStr::from_bytes_with_nul(&prog_name_bytes).unwrap().to_str().unwrap();
                    let out_name_bytes: Vec<u8> = outName.lock().unwrap().iter().map(|&c| c as u8).collect();
                    let out_name_str = CStr::from_bytes_with_nul(&out_name_bytes).unwrap().to_str().unwrap();
                    eprintln!("{}: Can't create output file {}: {}.", prog_name_str, out_name_str, e);
                    setExit(1);
                    return;
                }
            }
        },
        _ => None,
    };

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        let in_name_bytes: Vec<u8> = IN_NAME.lock().unwrap().iter().map(|&c| c as u8).collect();
        let in_name_str = CStr::from_bytes_with_nul(&in_name_bytes).unwrap().to_str().unwrap();
        eprint!("  {}: ", in_name_str);
        pad(&IN_NAME.lock().unwrap()[..]);
        io::stderr().flush().unwrap();
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = match srcMode {
        3 => {
            let out_name_str = outName.lock().unwrap().iter().collect::<String>();
            Some(File::open(&Path::new(&out_name_str)).unwrap())
        },
        _ => None,
    };
    DELETE_OUTPUT_ON_INTERRUPT.store(true, Ordering::SeqCst);

    match srcMode {
        1 | 2 | 3 => {
            if let (Some(ref mut in_file), Some(ref mut out_file)) = (in_file.as_mut(), out_file.as_mut()) {
                compressStream(in_file, out_file);
            }
        },
        _ => panic(&"compress: bad srcMode".chars().collect::<Vec<_>>()[0]),
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if srcMode == 3 {
        applySavedTimeInfoToOutputFile(outName.lock().unwrap()[0]);
        DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
        if !KEEP_INPUT_FILES.load(Ordering::SeqCst) {
            let in_name_str = IN_NAME.lock().unwrap().iter().collect::<String>();
            if let Err(e) = std::fs::remove_file(&Path::new(&in_name_str)) {
                ioError();
            }
        }
    }
    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
}
pub fn uncompress(name: Option<&[Char]>) {
    let mut in_str: Option<File> = None;
    let mut out_str: Option<File> = None;
    let mut n: Int32 = 0;
    let mut i: Int32 = 0;
    let mut magic_number_ok: Bool = 0;
    let mut cant_guess: Bool = 0;
    let mut stat_buf: std::mem::MaybeUninit<libc::stat> = std::mem::MaybeUninit::uninit();

    DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);

    if name.is_none() && srcMode != 1 {
        panic("uncompress: bad modes\n".as_ptr() as *const Char);
    }

    cant_guess = 0;
    match srcMode {
        1 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], &['(', 's', 't', 'd', 'i', 'n', ')']);
            copyFileName(&mut outName.lock().unwrap()[..], &['(', 's', 't', 'd', 'o', 'u', 't', ')']);
        }
        3 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut outName.lock().unwrap()[..], name.unwrap());
            for i in 0..4 {
                if mapSuffix(
                    &mut outName.lock().unwrap()[..],
                    Some(&Z_SUFFIX[i].chars().collect::<Vec<_>>()),
                    Some(&UNZ_SUFFIX[i].chars().collect::<Vec<_>>()),
                ) {
                    break;
                }
            }
            cant_guess = 1;
            let mut out_name = outName.lock().unwrap();
            let len = out_name.iter().position(|&c| c == '\0').unwrap_or(out_name.len());
            out_name[len..len + 4].copy_from_slice(&['.', 'o', 'u', 't']);
        }
        2 => {
            copyFileName(&mut IN_NAME.lock().unwrap()[..], name.unwrap());
            copyFileName(&mut outName.lock().unwrap()[..], &['(', 's', 't', 'd', 'o', 'u', 't', ')']);
        }
        _ => {}
    }

    if srcMode != 1 && containsDubiousChars(Some(&IN_NAME.lock().unwrap()[..])) {
        if noisy.load(Ordering::SeqCst) {
            eprintln!(
                "{}: There are no files matching `{}'.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
            );
        }
        setExit(1);
        return;
    }

    if srcMode != 1 && fileExists(unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()) == 0 {
        eprintln!(
            "{}: Can't open input file {}: {}.",
            unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
            unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
            io::Error::last_os_error()
        );
        setExit(1);
        return;
    }

    if srcMode == 3 || srcMode == 2 {
        if false {
            eprintln!(
                "{}: Input file {} is a directory.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
            );
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) && notAStandardFile(&IN_NAME.lock().unwrap()[..]) != 0 {
        if noisy.load(Ordering::SeqCst) {
            eprintln!(
                "{}: Input file {} is not a normal file.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
            );
        }
        setExit(1);
        return;
    }

    if cant_guess != 0 && noisy.load(Ordering::SeqCst) {
        eprintln!(
            "{}: Can't guess original name for {} -- using {}",
            unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
            unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
            unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
        );
    }

    if srcMode == 3 && fileExists(unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()) != 0 {
        if forceOverwrite.load(Ordering::SeqCst) {
            std::fs::remove_file(Path::new(unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap())).unwrap_or_else(|_| ioError());
        } else {
            eprintln!(
                "{}: Output file {} already exists.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
            );
            setExit(1);
            return;
        }
    }

    if srcMode == 3 && !forceOverwrite.load(Ordering::SeqCst) {
        n = countHardLinks(Some(unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()));
        if n > 0 {
            eprintln!(
                "{}: Input file {} has {} other link{}.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                n,
                if n > 1 { "s" } else { "" }
            );
            setExit(1);
            return;
        }
    }

    if srcMode == 3 {
        saveInputFileMetaInfo(Some(&IN_NAME.lock().unwrap()[0]));
    }

    match srcMode {
        1 => {
            in_str = Some(unsafe { File::from_raw_fd(libc::STDIN_FILENO) });
            out_str = Some(unsafe { File::from_raw_fd(libc::STDOUT_FILENO) });
            if unsafe { libc::isatty(libc::STDIN_FILENO) } != 0 {
                eprintln!(
                    "{}: I won't read compressed data from a terminal.",
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
                );
                eprintln!(
                    "{}: For help, type: `{} --help'.",
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
                );
                setExit(1);
                return;
            }
        }
        2 => {
            in_str = File::open(Path::new(unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap())).ok();
            out_str = Some(unsafe { File::from_raw_fd(libc::STDOUT_FILENO) });
            if in_str.is_none() {
                eprintln!(
                    "{}: Can't open input file {}:{}.",
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    io::Error::last_os_error()
                );
                setExit(1);
                return;
            }
        }
        3 => {
            in_str = File::open(Path::new(unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap())).ok();
            out_str = fopen_output_safely(Some(Path::new(unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap())), "wb");
            if out_str.is_none() {
                eprintln!(
                    "{}: Can't create output file {}: {}.",
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    io::Error::last_os_error()
                );
                if in_str.is_some() {
                    in_str = None;
                }
                setExit(1);
                return;
            }
            if in_str.is_none() {
                eprintln!(
                    "{}: Can't open input file {}: {}.",
                    unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                    io::Error::last_os_error()
                );
                if out_str.is_some() {
                    out_str = None;
                }
                setExit(1);
                return;
            }
        }
        _ => {
            panic("uncompress: bad srcMode".as_ptr() as *const Char);
        }
    }

    if VERBOSITY.load(Ordering::SeqCst) >= 1 {
        eprint!("  {}: ", unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap());
        pad(&IN_NAME.lock().unwrap()[..]);
        io::stderr().flush().unwrap();
    }

    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = out_str.take();
    DELETE_OUTPUT_ON_INTERRUPT.store(true, Ordering::SeqCst);

    magic_number_ok = uncompressStream(&mut in_str.as_ref().unwrap().try_clone().unwrap(), &mut out_str.as_ref().unwrap().try_clone().unwrap()) as Bool;
    *OUTPUT_HANDLE_JUST_IN_CASE.lock().unwrap() = None;

    if magic_number_ok != 0 {
        if srcMode == 3 {
            applySavedTimeInfoToOutputFile(outName.lock().unwrap()[0]);
            DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
            if !KEEP_INPUT_FILES.load(Ordering::SeqCst) {
                let ret_val = std::fs::remove_file(Path::new(unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()));
                if ret_val.is_err() {
                    ioError();
                }
            }
        }
    } else {
        UNZ_FAILS_EXIST.store(true, Ordering::SeqCst);
        DELETE_OUTPUT_ON_INTERRUPT.store(false, Ordering::SeqCst);
        if srcMode == 3 {
            let ret_val = std::fs::remove_file(Path::new(unsafe { CStr::from_ptr(outName.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()));
            if ret_val.is_err() {
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
            eprintln!(
                "{}: {} is not a bzip2 file.",
                unsafe { CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap(),
                unsafe { CStr::from_ptr(IN_NAME.lock().unwrap().as_ptr() as *const i8) }.to_str().unwrap()
            );
        }
    }
}
