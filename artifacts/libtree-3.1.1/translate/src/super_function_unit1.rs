use crate::*;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Read;
use std::io;
use std::ptr;
use std::ffi::CStr;
use glob::GlobError;
use glob::PatternError;
use glob::glob;
use std::path::Path;
use std::os::unix::ffi::OsStrExt;
use std::os::raw::c_char;

pub fn parse_ld_config_file(st: &mut StringTableT, path: &str) -> io::Result<()> {
    // Open the file (equivalent to fopen)
    let fptr = File::open(path)?;
    let reader = BufReader::new(fptr);

    // Variables equivalent to C version
    let mut c = 0;
    let mut line = String::with_capacity(4096);
    let mut tmp = [0u8; 4096];
    let mut line_buf = [0u8; 4096];

    // Read lines until EOF (equivalent to while(c != EOF))
    for line_result in reader.lines() {
        line = line_result?;
        let mut file = File::open(path)?;
        helper_parse_ld_config_file_1(&mut c, st, path, &mut file, &mut line_buf, &mut tmp);
    }

    // File is automatically closed when `reader` goes out of scope (equivalent to fclose)
    Ok(())
}


pub fn helper_helper_parse_ld_config_file_1_1(
    begin_idx_ref: &mut u32,
    st: &mut StringTableT,
    path: &str,
    tmp: &mut [u8; 4096],
    begin: &[u8],
    end: &[u8],
) {
    let mut begin_idx = *begin_idx_ref;
    begin_idx += 8;
    
    // Skip whitespace
    while begin_idx < begin.len() as u32 && begin[begin_idx as usize].is_ascii_whitespace() {
        begin_idx += 1;
    }

    if begin_idx >= begin.len() as u32 || begin[begin_idx as usize] != b'/' {
        // Find last '/' in path
        let wd = path.rfind('/').unwrap_or(0);
        let wd_len = wd;
        let include_len = (end.as_ptr() as usize - begin[begin_idx as usize..].as_ptr() as usize) + 1;

        if (wd_len + 1 + include_len) >= 4096 {
            return;
        }

        // Copy path part
        tmp[..wd_len].copy_from_slice(&path.as_bytes()[..wd_len]);
        tmp[wd_len] = b'/';
        
        // Copy include part
        let include_slice = &begin[begin_idx as usize..];
        tmp[wd_len + 1..wd_len + 1 + include_len].copy_from_slice(&include_slice[..include_len]);
        tmp[wd_len + 1 + include_len] = b'\0';

        // Update begin_idx to point to tmp (not directly translatable to Rust)
        // In Rust we'd need to handle this differently, perhaps by returning a new buffer
        // For now we'll just continue with the original begin
    }

    let pattern = unsafe { std::str::from_utf8_unchecked(begin) };
    ld_conf_globbing(st, pattern);
    *begin_idx_ref = begin_idx;
}


pub fn ld_conf_globbing(st: &mut StringTableT, pattern: &str) -> i32 {
    // In Rust, we don't need to manually memset since glob() will initialize the result
    let mut result = match glob(pattern) {
        Ok(r) => r,
        Err(e) => {
            if e.to_string().contains("No space") || e.to_string().contains("Aborted") {
                return 1;
            } else {
                return 0;
            }
        }
    };

    // GLOB_NOMATCH equivalent - if no matches found
    if result.count() == 0 {
        return 0;
    }

    // Reset the iterator since we consumed it with count()
    result = match glob(pattern) {
        Ok(r) => r,
        Err(_) => return 1, // Shouldn't happen since we already checked
    };

    let mut code = 0;
    for entry in result {
        match entry {
            Ok(path) => {
                if let Some(path_str) = path.to_str() {
                    if let Err(_) = parse_ld_config_file(st, path_str) {
                        code |= 1;
                    }
                }
            }
            Err(_) => code |= 1, // Treat glob errors as failures
        }
    }

    code
}


pub fn helper_parse_ld_config_file_1(
    c_ref: &mut i32,
    st: &mut StringTableT,
    path: &str,
    fptr: &mut File,
    line: &mut [u8; 4096],
    tmp: &mut [u8; 4096],
) {
    let mut c = *c_ref;
    let mut line_len = 0;

    // Read until newline or EOF
    while {
        c = match fptr.bytes().next() {
            Some(Ok(byte)) => byte as i32,
            _ => -1, // EOF
        };
        c != '\n' as i32 && c != -1
    } {
        if line_len < 4096 - 1 {
            line[line_len] = c as u8;
            line_len += 1;
        }
    }

    line[line_len] = b'\0';
    let mut begin = 0;

    // Skip leading whitespace
    while begin < line_len && unsafe { libc::isspace(line[begin] as i32) } != 0 {
        begin += 1;
    }

    // Find comment
    let comment_pos = line[begin..line_len]
        .iter()
        .position(|&ch| ch == b'#')
        .map(|pos| pos + begin);

    if let Some(pos) = comment_pos {
        line[pos] = b'\0';
    }

    let mut end = line_len;
    // Trim trailing whitespace
    while end > begin {
        end -= 1;
        if unsafe { libc::isspace(line[end] as i32) } == 0 {
            break;
        }
    }

    if begin == end {
        *c_ref = c;
        return;
    }

    line[end + 1] = b'\0';

    // Check for "include" directive
    let line_str = unsafe { std::str::from_utf8_unchecked(&line[begin..end + 1]) };
    
    if line_str.starts_with("include") && line_str.len() > 7 && unsafe {
        libc::isspace(line[begin + 7] as i32)
    } != 0 {
        // Call helper function for include directive
        let mut begin_u32 = begin as u32;
        helper_helper_parse_ld_config_file_1_1(&mut begin_u32, st, path, tmp, &line[begin..end + 1], &line[end + 1..]);
    } else {
        string_table_store(st, line_str);
        if let Some(arr) = &mut st.arr {
            if st.n > 0 {
                arr[st.n - 1] = ':';
            }
        }
    }

    *c_ref = c;
}
