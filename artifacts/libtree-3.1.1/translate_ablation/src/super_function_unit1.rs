use crate::*;
use glob::glob;
use std::ffi::CStr;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Error;
use std::io::ErrorKind;
use std::io::Read;
use std::os::raw::c_char;pub fn helper_helper_parse_ld_config_file_1_1(
    begin_idx_ref: &mut u32,
    st: &mut StringTableT,
    path: &str,
    tmp: &mut [u8; 4096],
    begin: &str,
    end: &str,
) {
    let mut begin_idx = *begin_idx_ref;
    begin_idx += 8;

    // Skip whitespace
    while begin
        .chars()
        .nth(begin_idx as usize)
        .map_or(false, |c| c.is_whitespace())
    {
        begin_idx += 1;
    }

    if begin.chars().nth(begin_idx as usize) != Some('/') {
        // Find last '/' in path
        let wd = path.rfind('/').unwrap_or(path.len());
        let wd_len = wd;
        let include_len = end.len() - begin_idx as usize + 1;

        if (wd_len + 1 + include_len) >= 4096 {
            return;
        }

        // Copy path part
        tmp[..wd_len].copy_from_slice(&path.as_bytes()[..wd_len]);
        tmp[wd_len] = b'/';
        
        // Copy include part
        let include_start = begin_idx as usize;
        let include_end = include_start + include_len - 1;
        tmp[wd_len + 1..wd_len + 1 + include_len]
            .copy_from_slice(&begin.as_bytes()[include_start..=include_end]);
        
        // Null-terminate (though Rust strings don't need this)
        tmp[wd_len + 1 + include_len] = 0;
    }

    ld_conf_globbing(st, begin);
    *begin_idx_ref = begin_idx;
}

pub fn helper_parse_ld_config_file_1(
    c_ref: &mut i32,
    st: &mut StringTableT,
    path: &str,
    fptr: &mut impl std::io::Read,
    line: &mut [u8; 4096],
    tmp: &mut [u8; 4096],
) {
    let mut c = *c_ref;
    let mut line_len = 0;

    // Read line from file
    while {
        let mut buf = [0u8; 1];
        if fptr.read_exact(&mut buf).is_err() {
            c = -1; // EOF
            false
        } else {
            c = buf[0] as i32;
            c != b'\n' as i32 && c != -1
        }
    } {
        if line_len < 4095 {
            line[line_len] = c as u8;
            line_len += 1;
        }
    }

    line[line_len] = b'\0';
    let line_str = unsafe { std::ffi::CStr::from_ptr(line.as_ptr() as *const i8) };
    let mut line_str = line_str.to_str().unwrap_or("");

    // Trim leading whitespace
    line_str = line_str.trim_start();

    // Remove comments
    let comment_pos = line_str.find('#');
    let line_str = if let Some(pos) = comment_pos {
        &line_str[..pos]
    } else {
        line_str
    };

    // Trim trailing whitespace
    let line_str = line_str.trim_end();

    if line_str.is_empty() {
        *c_ref = c;
        return;
    }

    if line_str.starts_with("include") && line_str[7..].starts_with(char::is_whitespace) {
        let mut begin_idx = 0;
        helper_helper_parse_ld_config_file_1_1(
            &mut begin_idx,
            st,
            path,
            tmp,
            line_str,
            line_str,
        );
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

pub fn parse_ld_config_file(st: &mut StringTableT, path: &str) -> Result<(), std::io::Error> {

    // Open the file, returning an error if it fails
    let fptr = File::open(path)?;
    let mut reader = BufReader::new(fptr);

    // Initialize buffers
    let mut line = [0u8; 4096];
    let mut tmp = [0u8; 4096];
    let mut c = 0;

    // Read lines until EOF
    loop {
        helper_parse_ld_config_file_1(
            &mut c,
            st,
            path,
            &mut reader,
            &mut line,
            &mut tmp,
        );
        if c == -1 {
            break;
        }
    }

    Ok(())
}

pub fn ld_conf_globbing(st: &mut StringTableT, pattern: &str) -> i32 {
    let mut result = glob::GlobResult::new();
    
    // Perform the glob operation
    let status = match glob::glob(pattern) {
        Ok(paths) => {
            result.gl_pathv = paths.collect();
            glob::GLOB_SUCCESS
        }
        Err(e) => match e {
            glob::GlobError::NoSpace => glob::GLOB_NOSPACE,
            glob::GlobError::Aborted => glob::GLOB_ABORTED,
            glob::GlobError::NoMatch => glob::GLOB_NOMATCH,
            _ => glob::GLOB_NOSPACE, // default to no space for other errors
        },
    };

    match status {
        glob::GLOB_NOSPACE | glob::GLOB_ABORTED => {
            return 1;
        }
        glob::GLOB_NOMATCH => {
            return 0;
        }
        _ => {}
    }

    let mut code = 0;
    for path in result.gl_pathv.iter() {
        if parse_ld_config_file(st, path).is_err() {
            code |= 1;
        }
    }

    code
}

// Mock glob implementation since we don't have the actual C glob details
mod glob {
    pub const GLOB_SUCCESS: i32 = 0;
    pub const GLOB_NOSPACE: i32 = 1;
    pub const GLOB_ABORTED: i32 = 2;
    pub const GLOB_NOMATCH: i32 = 3;

    #[derive(Debug)]
    pub enum GlobError {
        NoSpace,
        Aborted,
        NoMatch,
    }

    pub struct GlobResult {
        pub gl_pathv: Vec<String>,
    }

    impl GlobResult {
        pub fn new() -> Self {
            Self { gl_pathv: Vec::new() }
        }
    }

    pub fn glob(pattern: &str) -> Result<impl Iterator<Item = String>, GlobError> {
        // This is a simplified mock implementation
        // In a real implementation, this would use the `glob` crate
        Ok(std::iter::empty())
    }
}
