use lazy_static::lazy_static;
use libc::FILE;
use std::env;
use std::fs::File;
use std::io::Write;
use std::io;
use std::path::Path;
use translate_without_break_down::*;
use std::ffi::CStr;
use libc::c_char;
use std::process;
// Global variables from the original C code
static mut progName: [c_char; 2000] = [0; 2000];
static mut inFileName: [c_char; 2000] = [0; 2000];
static mut outFileName: [c_char; 2000] = [0; 2000];
static mut bStart: [MaybeUInt64; 50001] = [0; 50001];
static mut bEnd: [MaybeUInt64; 50001] = [0; 50001];
static mut rbStart: [MaybeUInt64; 50000] = [0; 50000];
static mut rbEnd: [MaybeUInt64; 50000] = [0; 50000];

pub fn main() {
    let args: Vec<String> = std::env::args().collect();
    let argc = args.len() as i32;
    let mut argv: Vec<*mut c_char> = Vec::new();
    
    for arg in &args {
        argv.push(std::ffi::CString::new(arg.as_str()).unwrap().into_raw());
    }
    
    let result = main_internal(argc, argv.as_mut_ptr());
    
    // Clean up the CStrings
    for ptr in argv {
        unsafe {
            let _ = std::ffi::CString::from_raw(ptr);
        }
    }
    
    process::exit(result);
}

fn main_internal(argc: i32, argv: *mut *mut c_char) -> i32 {
    let mut inFile: Option<File> = None;
    let mut outFile: Option<File> = None;
    let mut bsIn: Option<BitStream> = None;
    let mut bsWr: Option<BitStream> = None;
    let mut b: i32;
    let mut wrBlock: i32 = 0;
    let mut currBlock: i32 = 0;
    let mut rbCtr: i32 = 0;
    let mut bitsRead: MaybeUInt64 = 0;
    let mut buffHi: u32 = 0;
    let mut buffLo: u32 = 0;
    let mut blockCRC: u32 = 0;
    let mut ofs: i32;
    let mut k: i32;

    unsafe {
        if argc < 1 {
            eprintln!("Invalid argc value");
            process::exit(1);
        }
        let prog_name_ptr = *argv;
        let prog_name_cstr = CStr::from_ptr(prog_name_ptr);
        let prog_name_bytes = prog_name_cstr.to_bytes();
        let copy_len = std::cmp::min(prog_name_bytes.len(), 1999);
        
        // Convert u8 bytes to i8 (c_char) for copy
        let mut prog_name_chars: Vec<c_char> = Vec::with_capacity(copy_len);
        for &byte in &prog_name_bytes[..copy_len] {
            prog_name_chars.push(byte as c_char);
        }
        progName[..copy_len].copy_from_slice(&prog_name_chars);
        progName[copy_len] = 0;
    }

    unsafe {
        inFileName[0] = 0;
        outFileName[0] = 0;
    }
    
    eprintln!("bzip2recover 1.0.6: extracts blocks from damaged .bz2 files.");
    
    if argc != 2 {
        unsafe {
            let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
            eprint!("{}: usage is `{} damaged_file_name'.\n", 
                   prog_name_cstr.to_string_lossy(),
                   prog_name_cstr.to_string_lossy());
        }
        
        match std::mem::size_of::<MaybeUInt64>() {
            8 => eprintln!("\trestrictions on size of recovered file: None"),
            4 => {
                eprintln!("\trestrictions on size of recovered file: 512 MB");
                eprintln!("\tto circumvent, recompile with MaybeUInt64 as an\n\tunsigned 64-bit int.");
            }
            _ => eprintln!("\tsizeof(MaybeUInt64) is not 4 or 8 -- configuration error."),
        }
        
        process::exit(1);
    }

    unsafe {
        let filename_ptr = *argv.offset(1);
        let filename_cstr = CStr::from_ptr(filename_ptr);
        let filename_len = filename_cstr.to_bytes().len();
        
        if filename_len >= (2000 - 20) {
            let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
            eprint!("{}: supplied filename is suspiciously (>= {} chars) long.  Bye!\n", 
                   prog_name_cstr.to_string_lossy(),
                   filename_len);
            process::exit(1);
        }
        
        let filename_bytes = filename_cstr.to_bytes();
        let copy_len = std::cmp::min(filename_bytes.len(), 1999);
        
        // Convert u8 bytes to i8 (c_char) for copy
        let mut filename_chars: Vec<c_char> = Vec::with_capacity(copy_len);
        for &byte in &filename_bytes[..copy_len] {
            filename_chars.push(byte as c_char);
        }
        inFileName[..copy_len].copy_from_slice(&filename_chars);
        inFileName[copy_len] = 0;
    }

    // Open input file
    let in_file_path = unsafe { CStr::from_ptr(inFileName.as_ptr() as *const c_char).to_string_lossy() };
    inFile = match File::open(&*in_file_path) {
        Ok(file) => Some(file),
        Err(_) => {
            unsafe {
                let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
                eprint!("{}: can't read `{}'\n", 
                       prog_name_cstr.to_string_lossy(),
                       in_file_path);
            }
            process::exit(1);
        }
    };

    bsIn = unsafe { bs_open_read_stream(Some(inFile.take().unwrap())) };
    unsafe {
        let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
        eprint!("{}: searching for block boundaries ...\n", prog_name_cstr.to_string_lossy());
    }

    bitsRead = 0;
    buffHi = 0;
    buffLo = 0;
    currBlock = 0;
    unsafe {
        bStart[currBlock as usize] = 0;
    }
    rbCtr = 0;

    loop {
        b = unsafe { bsGetBit(bsIn.as_mut().unwrap()) };
        bitsRead += 1;
        
        if b == 2 {
            unsafe {
                if (bitsRead >= bStart[currBlock as usize]) && ((bitsRead - bStart[currBlock as usize]) >= 40) {
                    bEnd[currBlock as usize] = bitsRead - 1;
                    if currBlock > 0 {
                        eprint!("   block {} runs from {} to {} (incomplete)\n", 
                               currBlock, bStart[currBlock as usize], bEnd[currBlock as usize]);
                    }
                } else {
                    currBlock -= 1;
                }
            }
            currBlock -= 1;
            break;
        }
        
        buffHi = (buffHi << 1) | (buffLo >> 31);
        buffLo = (buffLo << 1) | ((b & 1) as u32);
        
        if (((buffHi & 0x0000ffff) == 0x00003141) && (buffLo == 0x59265359)) || 
           (((buffHi & 0x0000ffff) == 0x00001772) && (buffLo == 0x45385090)) {
            
            unsafe {
                if bitsRead > 49 {
                    bEnd[currBlock as usize] = bitsRead - 49;
                } else {
                    bEnd[currBlock as usize] = 0;
                }
                
                if (currBlock > 0) && ((bEnd[currBlock as usize] - bStart[currBlock as usize]) >= 130) {
                    eprint!("   block {} runs from {} to {}\n", 
                           rbCtr + 1, bStart[currBlock as usize], bEnd[currBlock as usize]);
                    rbStart[rbCtr as usize] = bStart[currBlock as usize];
                    rbEnd[rbCtr as usize] = bEnd[currBlock as usize];
                    rbCtr += 1;
                }
                
                if currBlock >= 50000 {
                    tooManyBlocks(50000);
                }
                
                currBlock += 1;
                bStart[currBlock as usize] = bitsRead;
            }
        }
    }

    unsafe { bsClose(bsIn.take().unwrap()) };
    
    if rbCtr < 1 {
        unsafe {
            let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
            eprint!("{}: sorry, I couldn't find any block boundaries.\n", 
                   prog_name_cstr.to_string_lossy());
        }
        process::exit(1);
    }

    unsafe {
        let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
        eprint!("{}: splitting into blocks\n", prog_name_cstr.to_string_lossy());
    }

    // Reopen input file
    inFile = match File::open(&*in_file_path) {
        Ok(file) => Some(file),
        Err(_) => {
            unsafe {
                let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
                eprint!("{}: can't open `{}'\n", 
                       prog_name_cstr.to_string_lossy(),
                       in_file_path);
            }
            process::exit(1);
        }
    };

    bsIn = unsafe { bs_open_read_stream(Some(inFile.take().unwrap())) };
    blockCRC = 0;
    bsWr = None;
    bitsRead = 0;
    outFile = None;
    wrBlock = 0;

    loop {
        b = unsafe { bsGetBit(bsIn.as_mut().unwrap()) };
        
        if b == 2 {
            break;
        }
        
        buffHi = (buffHi << 1) | (buffLo >> 31);
        buffLo = (buffLo << 1) | ((b & 1) as u32);
        
        unsafe {
            if bitsRead == (47 + rbStart[wrBlock as usize]) {
                blockCRC = (buffHi << 16) | (buffLo >> 16);
            }
            
            if bsWr.is_some() && (bitsRead >= rbStart[wrBlock as usize]) && (bitsRead <= rbEnd[wrBlock as usize]) {
                bsPutBit(bsWr.as_mut().unwrap(), b);
            }
        }
        
        bitsRead += 1;
        
        unsafe {
            if bitsRead == (rbEnd[wrBlock as usize] + 1) {
                if bsWr.is_some() {
                    // Use bsPutBit to write the bytes instead of bsPutUChar
                    // Write 0x17 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x17 >> (7 - i)) & 1);
                    }
                    // Write 0x72 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x72 >> (7 - i)) & 1);
                    }
                    // Write 0x45 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x45 >> (7 - i)) & 1);
                    }
                    // Write 0x38 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x38 >> (7 - i)) & 1);
                    }
                    // Write 0x50 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x50 >> (7 - i)) & 1);
                    }
                    // Write 0x90 as bits
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x90 >> (7 - i)) & 1);
                    }
                    // Write blockCRC as 32 bits
                    for i in 0..32 {
                        // FIX: bsPutBit expects `Int32`; cast the masked bit from u32 to i32.
                        bsPutBit(
                            bsWr.as_mut().unwrap(),
                            ((blockCRC >> (31 - i)) & 1) as i32,
                        );
                    }
                    bsClose(bsWr.take().unwrap());
                    outFile = None;
                }
                
                if wrBlock >= rbCtr {
                    break;
                }
                
                wrBlock += 1;
            } else if bitsRead == rbStart[wrBlock as usize] {
                // Clear outFileName
                for k in 0..2000 {
                    outFileName[k as usize] = 0;
                }

                unsafe {
                    // Copy inFileName to outFileName
                    let in_file_name_cstr = CStr::from_ptr(inFileName.as_ptr() as *const c_char);
                    let in_file_name_bytes = in_file_name_cstr.to_bytes();
                    let copy_len = std::cmp::min(in_file_name_bytes.len(), 1999);
                    
                    // Convert u8 bytes to i8 (c_char) for copy
                    let mut in_file_name_chars: Vec<c_char> = Vec::with_capacity(copy_len);
                    for &byte in &in_file_name_bytes[..copy_len] {
                        in_file_name_chars.push(byte as c_char);
                    }
                    outFileName[..copy_len].copy_from_slice(&in_file_name_chars);
                    outFileName[copy_len] = 0;

                    // Find last '/' or use beginning
                    let mut split_ptr = std::ptr::null_mut();
                    let out_file_name_ptr = outFileName.as_mut_ptr() as *mut c_char;
                    
                    split_ptr = libc::strrchr(out_file_name_ptr, '/' as i32);
                    
                    if split_ptr.is_null() {
                        split_ptr = out_file_name_ptr;
                    } else {
                        split_ptr = split_ptr.offset(1);
                    }
                    
                    ofs = (split_ptr as isize - out_file_name_ptr as isize) as i32;
                    
                    // Format the split part
                    let format_str = b"rec%5d\0";
                    libc::sprintf(split_ptr, format_str.as_ptr() as *const c_char, wrBlock + 1);
                    
                    // Replace spaces with zeros
                    let mut current_ptr = split_ptr;
                    while *current_ptr != 0 {
                        if *current_ptr == ' ' as c_char {
                            *current_ptr = '0' as c_char;
                        }
                        current_ptr = current_ptr.offset(1);
                    }
                    
                    // Append the original filename suffix
                    let in_file_name_ptr = inFileName.as_ptr() as *const c_char;
                    let suffix_ptr = in_file_name_ptr.offset(ofs as isize);
                    libc::strcat(out_file_name_ptr, suffix_ptr);
                    
                    // Add .bz2 extension if needed
                    let out_file_name_cstr = CStr::from_ptr(out_file_name_ptr);
                    let out_file_name_bytes = out_file_name_cstr.to_bytes();
                    let out_file_name_chars: Vec<Char> = out_file_name_bytes.iter().map(|&b| b as Char).collect();
                    if !endsInBz2(&out_file_name_chars) {
                        let bz2_ext = b".bz2\0";
                        libc::strcat(out_file_name_ptr, bz2_ext.as_ptr() as *const c_char);
                    }
                    
                    let out_file_name_cstr = CStr::from_ptr(out_file_name_ptr);
                    eprint!("   writing block {} to `{}' ...\n", 
                           wrBlock + 1, 
                           out_file_name_cstr.to_string_lossy());
                    
                    // Open output file
                    let out_file_path = out_file_name_cstr.to_string_lossy();
                    outFile = match File::create(&*out_file_path) {
                        Ok(file) => Some(file),
                        Err(_) => {
                            let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
                            eprint!("{}: can't write `{}'\n", 
                                   prog_name_cstr.to_string_lossy(),
                                   out_file_path);
                            process::exit(1);
                        }
                    };
                    
                    bsWr = bs_open_write_stream(Some(outFile.take().unwrap()));
                    // Write BZ header using bsPutBit
                    // Write 'B' (0x42)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x42 >> (7 - i)) & 1);
                    }
                    // Write 'Z' (0x5a)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x5a >> (7 - i)) & 1);
                    }
                    // Write 'h' (0x68)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x68 >> (7 - i)) & 1);
                    }
                    // Write '9' (0x30 + 9 = 0x39)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x39 >> (7 - i)) & 1);
                    }
                    // Write '1' (0x31)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x31 >> (7 - i)) & 1);
                    }
                    // Write 'A' (0x41)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x41 >> (7 - i)) & 1);
                    }
                    // Write 'Y' (0x59)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x59 >> (7 - i)) & 1);
                    }
                    // Write '&' (0x26)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x26 >> (7 - i)) & 1);
                    }
                    // Write 'S' (0x53)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x53 >> (7 - i)) & 1);
                    }
                    // Write 'Y' (0x59)
                    for i in 0..8 {
                        bsPutBit(bsWr.as_mut().unwrap(), (0x59 >> (7 - i)) & 1);
                    }
                }
            }
        }
    }

    unsafe {
        let prog_name_cstr = CStr::from_ptr(progName.as_ptr() as *const c_char);
        eprint!("{}: finished\n", prog_name_cstr.to_string_lossy());
    }
    
    0
}