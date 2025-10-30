use libc::FILE;
use crate::*;
use std::io;
use std::process;
use lazy_static::lazy_static;
use std::fs::File;
use std::ffi::CStr;
use std::io::ErrorKind;
use std::io::Read;
use std::io::Write;
use std::sync::atomic::Ordering;

pub fn readError() {
    // Convert the global variables to strings
    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_bytes: Vec<u8> = prog_name.iter().map(|&c| c as u8).collect();
    let prog_name_str = String::from_utf8_lossy(&prog_name_bytes);
    let prog_name_str = prog_name_str.trim_end_matches('\0');

    let in_file_name = IN_FILE_NAME.lock().unwrap();
    let in_file_name_bytes: Vec<u8> = in_file_name.iter().map(|&c| c as u8).collect();
    let in_file_name_str = String::from_utf8_lossy(&in_file_name_bytes);
    let in_file_name_str = in_file_name_str.trim_end_matches('\0');

    // Equivalent to fprintf(stderr, ...)
    writeln!(
        io::stderr(),
        "{}: I/O error reading `{}`, possible reason follows.",
        prog_name_str,
        in_file_name_str
    ).unwrap();

    // Equivalent to perror(progName)
    eprintln!("{}: {}", prog_name_str, io::Error::last_os_error());

    // Equivalent to fprintf(stderr, ...)
    writeln!(
        io::stderr(),
        "{}: warning: output file(s) may be incomplete.",
        prog_name_str
    ).unwrap();

    // Equivalent to exit(1)
    process::exit(1);
}

pub fn writeError() {
    let prog_name = PROG_NAME.lock().unwrap();
    let in_file_name = IN_FILE_NAME.lock().unwrap();
    
    // Convert char arrays to strings, trimming null bytes
    let prog_name_str = prog_name.iter()
        .take_while(|&&c| c != '\0')
        .collect::<String>();
    let in_file_name_str = in_file_name.iter()
        .take_while(|&&c| c != '\0')
        .collect::<String>();

    // Equivalent to fprintf(stderr, ...)
    writeln!(io::stderr(), "{}: I/O error reading `{}', possible reason follows.", prog_name_str, in_file_name_str)
        .expect("Failed to write to stderr");
    
    // Equivalent to perror(progName)
    eprintln!("{}: {}", prog_name_str, io::Error::last_os_error());
    
    // Equivalent to fprintf(stderr, ...)
    writeln!(io::stderr(), "{}: warning: output file(s) may be incomplete.", prog_name_str)
        .expect("Failed to write to stderr");
    
    // Equivalent to exit(1)
    process::exit(1);
}
lazy_static! {
    pub static ref PROG_NAME: std::sync::Mutex<[char; 2000]> =
        std::sync::Mutex::new(['\0'; 2000]);
}

pub fn malloc_fail(n: Int32) {
    let prog_name = PROG_NAME.lock().unwrap();
    let prog_name_str = prog_name.iter().take_while(|&&c| c != '\0').collect::<String>();
    
    eprintln!(
        "{}: malloc failed on request for {} bytes.",
        prog_name_str,
        n
    );
    eprintln!(
        "{}: warning: output file(s) may be incomplete.",
        prog_name_str
    );
    process::exit(1);
}

pub fn bsOpenReadStream(stream: Option<File>) -> Option<BitStream> {
    Some(BitStream {
        handle: stream,
        buffer: 0,
        buff_live: 0,
        mode: 'r',
    })
}

pub fn bsOpenWriteStream(stream: Option<File>) -> Option<BitStream> {
    Some(BitStream {
        handle: stream,
        buffer: 0,
        buff_live: 0,
        mode: 'w',
    })
}
pub fn endsInBz2(name: &str) -> bool {
    let n = name.len();
    if n <= 4 {
        return false;
    }
    let chars: Vec<char> = name.chars().collect();
    (chars[n - 4] == '.') && (chars[n - 3] == 'b') && (chars[n - 2] == 'z') && (chars[n - 1] == '2')
}
pub fn tooManyBlocks(max_handled_blocks: Int32) {
    // Convert the global variables to Rust strings safely
    let prog_name = unsafe {
        CStr::from_ptr(PROG_NAME.lock().unwrap().as_ptr() as *const u8)
            .to_string_lossy()
            .into_owned()
    };
    let in_file_name = unsafe {
        CStr::from_ptr(IN_FILE_NAME.lock().unwrap().as_ptr() as *const u8)
            .to_string_lossy()
            .into_owned()
    };

    eprintln!(
        "{}: `{}' appears to contain more than {} blocks",
        prog_name, in_file_name, max_handled_blocks
    );
    eprintln!(
        "{}: and cannot be handled.  To fix, increase",
        prog_name
    );
    eprintln!(
        "{}: BZ_MAX_HANDLED_BLOCKS in bzip2recover.c, and recompile.",
        prog_name
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
        if let Some(handle) = &mut bs.handle {
            let ret_val = handle.write(&[bs.buffer as u8]);
            if ret_val.is_err() {
                writeError();
            } else {
                bytesOut.fetch_add(1, Ordering::Relaxed);
                bs.buff_live = 1;
                bs.buffer = bit & 0x1;
            }
        }
    } else {
        bs.buffer = (bs.buffer << 1) | (bit & 0x1);
        bs.buff_live += 1;
    }
}
pub fn bsClose(mut bs: BitStream) {
    if bs.mode == 'w' {
        {
            while bs.buff_live < 8 {
                bs.buff_live += 1;
                bs.buffer <<= 1;
            }

            if let Some(ref mut handle) = bs.handle {
                match handle.write(&[bs.buffer as u8]) {
                    Ok(_) => {
                        bytesOut.fetch_add(1, Ordering::SeqCst);
                        if let Err(e) = handle.flush() {
                            if e.kind() != ErrorKind::BrokenPipe {
                                writeError();
                            }
                        }
                    }
                    Err(e) => {
                        if e.kind() != ErrorKind::BrokenPipe {
                            writeError();
                        }
                    }
                }
            }
        }
    }

    if let Some(handle) = bs.handle {
        if let Err(e) = handle.sync_all() {
            if bs.mode == 'w' {
                if e.kind() != ErrorKind::BrokenPipe {
                    writeError();
                }
            } else if e.kind() != ErrorKind::BrokenPipe {
                readError();
            }
        }
    }
    // BitStream will be dropped here, which will close the file if still open
}
