use crate::*;
use lazy_static::lazy_static;
use libc::FILE;
use std::fs::File;
use std::io::ErrorKind;
use std::io::Read;
use std::io::Write;
use std::io;
use std::process;
use std::sync::atomic::Ordering;


pub fn readError() {
    let prog_name = PROG_NAME.lock().unwrap();
    let in_file_name = IN_FILE_NAME.lock().unwrap();
    
    let prog_name_str = prog_name.iter().collect::<String>();
    let in_file_name_str = in_file_name.iter().collect::<String>();
    
    writeln!(
        io::stderr(),
        "{}: I/O error reading `{}`, possible reason follows.",
        prog_name_str,
        in_file_name_str
    ).unwrap();
    
    perror(&prog_name_str);
    
    writeln!(
        io::stderr(),
        "{}: warning: output file(s) may be incomplete.",
        prog_name_str
    ).unwrap();
    
    process::exit(1);
}

fn perror(s: &str) {
    eprintln!("{}: {}", s, io::Error::last_os_error());
}
pub fn writeError() {
    let prog_name = PROG_NAME.lock().unwrap();
    let in_file_name = IN_FILE_NAME.lock().unwrap();
    
    // Convert char arrays to strings, trimming null terminators
    let prog_name_str = prog_name.iter()
        .take_while(|&&c| c != '\0')
        .collect::<String>();
    let in_file_name_str = in_file_name.iter()
        .take_while(|&&c| c != '\0')
        .collect::<String>();

    // Write error messages to stderr
    writeln!(io::stderr(), "{}: I/O error reading `{}`, possible reason follows.", prog_name_str, in_file_name_str).unwrap();
    perror(&prog_name_str);
    writeln!(io::stderr(), "{}: warning: output file(s) may be incomplete.", prog_name_str).unwrap();
    process::exit(1);
}

pub fn malloc_fail(n: Int32) {
    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_str = prog_name.iter().collect::<String>();
    eprintln!("{}: malloc failed on request for {} bytes.", prog_name_str, n);
    eprintln!("{}: warning: output file(s) may be incomplete.", prog_name_str);
    process::exit(1);
}

pub fn bs_open_read_stream(stream: Option<File>) -> Option<BitStream> {
    Some(BitStream {
        handle: stream,
        buffer: 0,
        buff_live: 0,
        mode: 'r',
    })
}

pub fn bs_open_write_stream(stream: Option<File>) -> Option<BitStream> {
    Some(BitStream {
        handle: stream,
        buffer: 0,
        buff_live: 0,
        mode: 'w',
    })
}
pub fn endsInBz2(name: &[Char]) -> bool {
    let n = name.len();
    if n <= 4 {
        return false;
    }
    (name[n - 4] == '.') && (name[n - 3] == 'b') && (name[n - 2] == 'z') && (name[n - 1] == '2')
}
pub fn tooManyBlocks(max_handled_blocks: Int32) {
    // Lock the mutexes to access the global variables
    let prog_name = PROG_NAME.lock().unwrap();
    let in_file_name = IN_FILE_NAME.lock().unwrap();
    
    // Convert the C-style strings to Rust strings with proper pointer casting
    let prog_name_str = unsafe { 
        std::ffi::CStr::from_ptr(prog_name.as_ptr() as *const i8) 
    }.to_string_lossy();
    let in_file_name_str = unsafe { 
        std::ffi::CStr::from_ptr(in_file_name.as_ptr() as *const i8) 
    }.to_string_lossy();

    eprintln!(
        "{}: `{}' appears to contain more than {} blocks",
        prog_name_str, in_file_name_str, max_handled_blocks
    );
    eprintln!(
        "{}: and cannot be handled.  To fix, increase",
        prog_name_str
    );
    eprintln!(
        "{}: BZ_MAX_HANDLED_BLOCKS in bzip2recover.c, and recompile.",
        prog_name_str
    );
    
    process::exit(1);
}

pub fn bsGetBit(bs: &mut BitStream) -> Int32 {
    if bs.buff_live > 0 {
        bs.buff_live -= 1;
        (bs.buffer >> bs.buff_live) & 0x1
    } else {
        let mut byte = [0u8; 1];
        let ret_val = match bs.handle.as_mut().unwrap().read_exact(&mut byte) {
            Ok(_) => byte[0] as Int32,
            Err(e) => {
                if e.kind() != std::io::ErrorKind::UnexpectedEof {
                    readError();
                }
                return 2;
            }
        };

        bs.buff_live = 7;
        bs.buffer = ret_val;
        (bs.buffer >> 7) & 0x1
    }
}

pub fn bsPutBit(bs: &mut BitStream, bit: Int32) {
    if bs.buff_live == 8 {
        if let Some(ref mut handle) = bs.handle {
            let ret_val = handle.write(&[bs.buffer as u8]);
            if ret_val.is_err() || ret_val.unwrap() != 1 {
                writeError();
            } else {
                bytesOut.fetch_add(1, Ordering::Relaxed);
                bs.buff_live = 1;
                bs.buffer = bit & 0x1;
            }
        } else {
            writeError();
        }
    } else {
        bs.buffer = (bs.buffer << 1) | (bit & 0x1);
        bs.buff_live += 1;
    }
}
pub fn bsClose(mut bs: BitStream) {
    if bs.mode == 'w' {
        // Handle buffered bits
        while bs.buff_live < 8 {
            bs.buff_live += 1;
            bs.buffer <<= 1;
        }

        // Write the buffer
        if let Some(ref mut handle) = bs.handle {
            let ret_val = handle.write(&[bs.buffer as u8]);
            if let Err(e) = ret_val {
                if e.kind() == ErrorKind::Other {
                    writeError();
                }
            }
            bytesOut.fetch_add(1, Ordering::Relaxed);
            
            let ret_val = handle.flush();
            if let Err(e) = ret_val {
                if e.kind() == ErrorKind::Other {
                    writeError();
                }
            }
        }
    }

    // Close the file
    if let Some(handle) = bs.handle {
        let ret_val = handle.sync_all();
        if let Err(e) = ret_val {
            if bs.mode == 'w' {
                writeError();
            } else {
                readError();
            }
        }
    }
    // BitStream will be dropped here (no explicit free needed in Rust)
}
