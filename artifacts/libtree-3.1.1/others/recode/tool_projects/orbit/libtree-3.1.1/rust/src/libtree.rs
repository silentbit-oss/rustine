// Core implementation for libtree
// Translation from C libtree.c to Rust

use std::fmt;
use std::error::Error;
use std::fs::File;
use std::io::{Read, Seek, SeekFrom};
use std::os::unix::fs::MetadataExt;

// Constants
pub const SMALL_VEC_SIZE: usize = 16;
pub const MAX_RECURSION_DEPTH: usize = 32;
pub const MAX_PATH_LENGTH: usize = 4096;

pub const BITS32: u8 = 1;
pub const BITS64: u8 = 2;

// ELF constants
pub const ET_EXEC: u16 = 2;
pub const ET_DYN: u16 = 3;
pub const PT_NULL: u32 = 0;
pub const PT_LOAD: u32 = 1;
pub const PT_DYNAMIC: u32 = 2;
pub const DT_NULL: i64 = 0;
pub const DT_NEEDED: i64 = 1;
pub const DT_STRTAB: i64 = 5;
pub const DT_SONAME: i64 = 14;
pub const DT_RPATH: i64 = 15;
pub const DT_RUNPATH: i64 = 29;

// Color codes
pub const REGULAR_RED: &str = "\x1b[0;31m";
pub const BOLD_RED: &str = "\x1b[1;31m";
pub const CLEAR: &str = "\x1b[0m";

// Tree rendering characters
pub const LIGHT_HORIZONTAL: &str = "─";
pub const LIGHT_QUADRUPLE_DASH_VERTICAL: &str = "┊";
pub const LIGHT_UP_AND_RIGHT: &str = "└";
pub const LIGHT_VERTICAL: &str = "│";
pub const LIGHT_VERTICAL_AND_RIGHT: &str = "├";
pub const JUST_INDENT: &str = "    ";

// Error types
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LibtreeError {
    InvalidMagic = 11,
    InvalidClass = 12,
    InvalidData = 13,
    InvalidHeader = 14,
    InvalidBits = 15,
    InvalidEndianness = 16,
    NoExecOrDyn = 17,
    InvalidPhoff = 18,
    InvalidProgHeader = 19,
    CantStat = 20,
    InvalidDynamicSection = 21,
    InvalidDynamicArrayEntry = 22,
    NoStrtab = 23,
    InvalidSoname = 24,
    InvalidRpath = 25,
    InvalidRunpath = 26,
    InvalidNeeded = 27,
    DependencyNotFound = 28,
    NoPtLoad = 29,
    VaddrsNotOrdered = 30,
    CouldNotOpenFile = 31,
    IncompatibleIsa = 32,
}

impl fmt::Display for LibtreeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let msg = match self {
            LibtreeError::InvalidMagic => "Invalid ELF magic bytes",
            LibtreeError::InvalidClass => "Invalid ELF class",
            LibtreeError::InvalidData => "Invalid ELF data encoding",
            LibtreeError::InvalidHeader => "Invalid ELF header",
            LibtreeError::InvalidBits => "Invalid bits",
            LibtreeError::InvalidEndianness => "Invalid endianness",
            LibtreeError::NoExecOrDyn => "Not an executable or dynamic library",
            LibtreeError::InvalidPhoff => "Invalid program header offset",
            LibtreeError::InvalidProgHeader => "Invalid program header",
            LibtreeError::CantStat => "Cannot stat file",
            LibtreeError::InvalidDynamicSection => "Invalid dynamic section",
            LibtreeError::InvalidDynamicArrayEntry => "Invalid dynamic array entry",
            LibtreeError::NoStrtab => "No string table",
            LibtreeError::InvalidSoname => "Invalid soname",
            LibtreeError::InvalidRpath => "Invalid rpath",
            LibtreeError::InvalidRunpath => "Invalid runpath",
            LibtreeError::InvalidNeeded => "Invalid needed entry",
            LibtreeError::DependencyNotFound => "Dependency not found",
            LibtreeError::NoPtLoad => "No PT_LOAD segment",
            LibtreeError::VaddrsNotOrdered => "Virtual addresses not ordered",
            LibtreeError::CouldNotOpenFile => "Could not open file",
            LibtreeError::IncompatibleIsa => "Incompatible ISA",
        };
        write!(f, "{}", msg)
    }
}

impl Error for LibtreeError {}

pub type LibtreeResult<T> = Result<T, LibtreeError>;

// Core data structures
#[derive(Clone, Copy, Debug)]
pub struct compat_t {
    pub any: bool,
    pub class: u8,
    pub machine: u16,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum how_t {
    INPUT,
    DIRECT,
    RPATH,
    LD_LIBRARY_PATH,
    RUNPATH,
    LD_SO_CONF,
    DEFAULT,
}

#[derive(Clone, Copy, Debug)]
pub struct found_t {
    pub how: how_t,
    pub depth: usize,
}

pub struct string_table_t {
    pub arr: Vec<u8>,
    pub n: usize,
    pub capacity: usize,
}

impl string_table_t {
    pub fn new() -> Self {
        Self {
            arr: Vec::new(),
            n: 0,
            capacity: 0,
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct visited_file_t {
    pub st_dev: u64,
    pub st_ino: u64,
}

pub struct visited_file_array_t {
    pub arr: Vec<visited_file_t>,
}

impl visited_file_array_t {
    pub fn new() -> Self {
        Self { arr: Vec::new() }
    }
}

pub struct libtree_state_t {
    pub verbosity: i32,
    pub path: bool,
    pub color: bool,
    pub ld_conf_file: String,
    pub max_depth: usize,
    pub string_table: string_table_t,
    pub visited: visited_file_array_t,
    pub PLATFORM: String,
    pub LIB: String,
    pub OSNAME: String,
    pub OSREL: String,
    pub rpath_offsets: [usize; MAX_RECURSION_DEPTH],
    pub ld_library_path_offset: usize,
    pub default_paths_offset: usize,
    pub ld_so_conf_offset: usize,
    pub found_all_needed: [bool; MAX_RECURSION_DEPTH],
}

pub struct small_vec_u64_t {
    buf: [u64; SMALL_VEC_SIZE],
    heap: Option<Vec<u64>>,
    n: usize,
}

impl small_vec_u64_t {
    pub fn new() -> Self {
        Self {
            buf: [0; SMALL_VEC_SIZE],
            heap: None,
            n: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.n
    }
}

// Function stubs
pub fn utoa(v: usize) -> String {
    v.to_string()
}

pub fn small_vec_u64_init(v: &mut small_vec_u64_t) {
    v.buf = [0; SMALL_VEC_SIZE];
    v.heap = None;
    v.n = 0;
}

pub fn small_vec_u64_append(v: &mut small_vec_u64_t, val: u64) {
    // Fast path: still using stack buffer
    if v.n < SMALL_VEC_SIZE {
        v.buf[v.n] = val;
        v.n += 1;
        return;
    }

    // Slow path: need to move to heap or grow heap
    if v.n == SMALL_VEC_SIZE {
        // First time moving to heap
        let mut heap_vec = Vec::with_capacity(2 * SMALL_VEC_SIZE);
        heap_vec.extend_from_slice(&v.buf);
        heap_vec.push(val);
        v.heap = Some(heap_vec);
        v.n += 1;
    } else {
        // Already on heap
        if let Some(ref mut heap) = v.heap {
            heap.push(val);
            v.n += 1;
        }
    }
}

pub fn small_vec_u64_free(v: &mut small_vec_u64_t) {
    // In Rust, the Drop trait handles cleanup automatically.
    // This function is kept for API compatibility but is essentially a no-op.
    // The heap Vec will be automatically dropped when the struct goes out of scope.
    v.heap = None;
    v.n = 0;
}

pub fn host_is_little_endian() -> bool {
    cfg!(target_endian = "little")
}

pub fn is_ascending_order(v: &[u64]) -> bool {
    v.windows(2).all(|w| w[0] < w[1])
}

pub fn string_table_maybe_grow(t: &mut string_table_t, n: usize) {
    // The likely case of not having to resize
    if t.n + n <= t.capacity {
        return;
    }

    // Otherwise give twice the amount of required space
    t.capacity = 2 * (t.n + n);
    t.arr.reserve(t.capacity - t.arr.capacity());
}

pub fn string_table_store(t: &mut string_table_t, s: &str) {
    let len = s.len() + 1;
    string_table_maybe_grow(t, len);
    t.arr.extend_from_slice(s.as_bytes());
    t.arr.push(0); // Null terminator
    t.n = t.arr.len();
}

pub fn string_table_copy_from_file<R: Read>(t: &mut string_table_t, reader: &mut R) -> std::io::Result<()> {
    let mut byte = [0u8; 1];
    loop {
        match reader.read_exact(&mut byte) {
            Ok(()) => {
                string_table_maybe_grow(t, 1);
                t.arr.push(byte[0]);
                t.n += 1;
                if byte[0] == 0 {
                    break;
                }
            }
            Err(e) if e.kind() == std::io::ErrorKind::UnexpectedEof => {
                // EOF reached before null terminator
                string_table_maybe_grow(t, 1);
                t.arr.push(0);
                t.n += 1;
                break;
            }
            Err(e) => return Err(e),
        }
    }
    Ok(())
}

pub fn is_in_exclude_list(soname: &str) -> bool {
    const EXCLUDE_LIST: &[&str] = &[
        "ld-linux-aarch64.so",
        "ld-linux-armhf.so",
        "ld-linux-x86-64.so",
        "ld-linux.so",
        "ld64.so",
        "libc.musl-aarch64.so",
        "libc.musl-armhf.so",
        "libc.musl-i386.so",
        "libc.musl-x86_64.so",
        "libc.so",
        "libdl.so",
        "libgcc_s.so",
        "libm.so",
        "libstdc++.so",
    ];

    if soname.is_empty() {
        return false;
    }

    // Strip version numbers and dots from the right
    let trimmed = soname.trim_end_matches(|c: char| c.is_ascii_digit() || c == '.');

    // Check if the soname starts with any excluded prefix
    EXCLUDE_LIST.iter().any(|&excluded| trimmed.starts_with(excluded))
}

pub fn tree_preamble(s: &libtree_state_t, depth: usize) {
    if depth == 0 {
        return;
    }

    const LIGHT_VERTICAL_WITH_INDENT: &str = "│   ";

    for i in 0..depth - 1 {
        print!("{}", if s.found_all_needed[i] { JUST_INDENT } else { LIGHT_VERTICAL_WITH_INDENT });
    }

    print!("{}", if s.found_all_needed[depth - 1] {
        "└── "
    } else {
        "├── "
    });
}

pub fn apply_exclude_list(
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut small_vec_u64_t,
    s: &libtree_state_t,
) {
    let mut i = 0;
    while i < *needed_not_found {
        // Get the offset for the current needed library
        let offset = if needed_buf_offsets.n <= SMALL_VEC_SIZE {
            needed_buf_offsets.buf[i] as usize
        } else {
            needed_buf_offsets.heap.as_ref().unwrap()[i] as usize
        };

        // Get the library name from the string table
        let lib_name = std::str::from_utf8(
            &s.string_table.arr[offset..s.string_table.arr.len()]
        )
        .unwrap_or("")
        .split('\0')
        .next()
        .unwrap_or("");

        // If in exclude list, swap to the back
        if is_in_exclude_list(lib_name) {
            // Swap current with the last unfound needed
            if needed_buf_offsets.n <= SMALL_VEC_SIZE {
                let tmp = needed_buf_offsets.buf[i];
                needed_buf_offsets.buf[i] = needed_buf_offsets.buf[*needed_not_found - 1];
                needed_buf_offsets.buf[*needed_not_found - 1] = tmp;
            } else {
                let heap = needed_buf_offsets.heap.as_mut().unwrap();
                let tmp = heap[i];
                heap[i] = heap[*needed_not_found - 1];
                heap[*needed_not_found - 1] = tmp;
            }
            *needed_not_found -= 1;
            // Don't increment i, check the swapped element
        } else {
            i += 1;
        }
    }
}

pub fn check_absolute_paths(
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut small_vec_u64_t,
    depth: usize,
    s: &mut libtree_state_t,
    compat: compat_t,
) -> LibtreeResult<()> {
    let mut exit_code = Ok(());
    let mut i = 0;

    while i < *needed_not_found {
        // Get the offset for the current needed library
        let offset = if needed_buf_offsets.n <= SMALL_VEC_SIZE {
            needed_buf_offsets.buf[i] as usize
        } else {
            needed_buf_offsets.heap.as_ref().unwrap()[i] as usize
        };

        // Get the library name from the string table
        let lib_name = std::str::from_utf8(
            &s.string_table.arr[offset..s.string_table.arr.len()]
        )
        .unwrap_or("")
        .split('\0')
        .next()
        .unwrap_or("");

        // Skip dt_needed that do not contain /
        if !lib_name.contains('/') {
            i += 1;
            continue;
        }

        // Check if path is too long
        if lib_name.len() >= MAX_PATH_LENGTH {
            i += 1;
            continue;
        }

        // Copy the path
        let path = lib_name.to_string();

        s.found_all_needed[depth] = *needed_not_found <= 1;
        let mut err: Option<&str> = None;

        // If it is not an absolute path, we bail
        if !path.starts_with('/') {
            err = Some(" is not absolute");
            exit_code = Err(LibtreeError::DependencyNotFound);
        } else {
            let code = recurse(
                &path,
                depth + 1,
                s,
                compat,
                found_t { how: how_t::DIRECT, depth: 0 },
            );

            if code == Err(LibtreeError::DependencyNotFound) {
                exit_code = Err(LibtreeError::DependencyNotFound);
            }

            // Check if there was an issue with the direct dep and ignore errors
            // of transient deps
            if code.is_err() && code != Err(LibtreeError::DependencyNotFound) {
                err = Some(" not found");
            }
        }

        if let Some(err_msg) = err {
            tree_preamble(s, depth + 1);
            if s.color {
                print!("{}", BOLD_RED);
            }
            print!("{}", path);
            print!("{}", err_msg);
            print!("{}", if s.color { format!("{}\n", CLEAR) } else { "\n".to_string() });
        }

        // Handled this library, so swap to the back
        if needed_buf_offsets.n <= SMALL_VEC_SIZE {
            let tmp = needed_buf_offsets.buf[i];
            needed_buf_offsets.buf[i] = needed_buf_offsets.buf[*needed_not_found - 1];
            needed_buf_offsets.buf[*needed_not_found - 1] = tmp;
        } else {
            let heap = needed_buf_offsets.heap.as_mut().unwrap();
            let tmp = heap[i];
            heap[i] = heap[*needed_not_found - 1];
            heap[*needed_not_found - 1] = tmp;
        }
        *needed_not_found -= 1;
    }

    exit_code
}

pub fn check_search_paths(
    reason: found_t,
    mut offset: usize,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut small_vec_u64_t,
    depth: usize,
    s: &mut libtree_state_t,
    compat: compat_t,
) -> LibtreeResult<()> {
    let mut exit_code = Ok(());
    let mut path = String::with_capacity(MAX_PATH_LENGTH);

    // Need to work around borrow checker by copying the search path string first
    let st_len = s.string_table.arr.len();

    while offset < st_len && s.string_table.arr[offset] != 0 {
        // First remove trailing colons
        while offset < st_len && s.string_table.arr[offset] == b':' && s.string_table.arr[offset] != 0 {
            offset += 1;
        }

        // Check if it was only colons
        if offset >= st_len || s.string_table.arr[offset] == 0 {
            return exit_code;
        }

        // Copy the search path until the first \0 or :
        path.clear();
        while offset < st_len && s.string_table.arr[offset] != 0 && s.string_table.arr[offset] != b':' {
            if path.len() < MAX_PATH_LENGTH {
                path.push(s.string_table.arr[offset] as char);
            }
            offset += 1;
        }

        // Path too long... Can't handle.
        if path.len() + 1 >= MAX_PATH_LENGTH {
            continue;
        }

        // Add a separator if necessary
        if !path.ends_with('/') {
            path.push('/');
        }

        // Keep track of the end of the current search path
        let search_path_end = path.len();

        // Try to open it -- if we've found anything, swap it with the back
        let mut i = 0;
        while i < *needed_not_found {
            // Get the soname offset
            let soname_offset = if needed_buf_offsets.n <= SMALL_VEC_SIZE {
                needed_buf_offsets.buf[i] as usize
            } else {
                needed_buf_offsets.heap.as_ref().unwrap()[i] as usize
            };

            // Get the soname from the string table
            let soname = std::str::from_utf8(
                &s.string_table.arr[soname_offset..s.string_table.arr.len()]
            )
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");

            // Path too long, can't handle
            if search_path_end + soname.len() + 1 >= MAX_PATH_LENGTH {
                i += 1;
                continue;
            }

            // Otherwise append
            path.truncate(search_path_end);
            path.push_str(soname);

            s.found_all_needed[depth] = *needed_not_found <= 1;

            // And try to locate the lib
            let code = recurse(&path, depth + 1, s, compat, reason);

            if code == Err(LibtreeError::DependencyNotFound) {
                exit_code = Err(LibtreeError::DependencyNotFound);
            }

            if code.is_ok() || code == Err(LibtreeError::DependencyNotFound) {
                // Found at least the direct dependency, so swap out the current
                // soname to the back and reduce the number of to be found by one
                if needed_buf_offsets.n <= SMALL_VEC_SIZE {
                    let tmp = needed_buf_offsets.buf[i];
                    needed_buf_offsets.buf[i] = needed_buf_offsets.buf[*needed_not_found - 1];
                    needed_buf_offsets.buf[*needed_not_found - 1] = tmp;
                } else {
                    let heap = needed_buf_offsets.heap.as_mut().unwrap();
                    let tmp = heap[i];
                    heap[i] = heap[*needed_not_found - 1];
                    heap[*needed_not_found - 1] = tmp;
                }
                *needed_not_found -= 1;
            } else {
                i += 1;
            }
        }
    }

    exit_code
}

pub fn interpolate_variables(
    s: &mut libtree_state_t,
    src: usize,
    origin: &str,
) -> bool {
    // We do not write to dst if there is no variables to interpolate
    let mut prev_src = src;
    let mut curr_src = src;
    let output_start = s.string_table.n;

    loop {
        // Find the next potential variable
        if curr_src >= s.string_table.arr.len() {
            break;
        }

        let remaining_len = s.string_table.arr.len() - curr_src;
        let remaining_slice = &s.string_table.arr[curr_src..curr_src + remaining_len];

        let dollar_pos = remaining_slice.iter().position(|&b| b == b'$');

        if dollar_pos.is_none() {
            break;
        }

        let dollar_offset = dollar_pos.unwrap();
        curr_src += dollar_offset;

        let bytes_to_dollar = curr_src - prev_src;

        // Go past the dollar
        curr_src += 1;

        // Remember if we have to look for matching curly braces
        let mut curly = false;
        if curr_src < s.string_table.arr.len() && s.string_table.arr[curr_src] == b'{' {
            curly = true;
            curr_src += 1;
        }

        // String to interpolate
        let var_val: Option<&str>;
        if curr_src + 6 <= s.string_table.arr.len()
            && &s.string_table.arr[curr_src..curr_src + 6] == b"ORIGIN" {
            var_val = Some(origin);
            curr_src += 6;
        } else if curr_src + 3 <= s.string_table.arr.len()
            && &s.string_table.arr[curr_src..curr_src + 3] == b"LIB" {
            var_val = Some(&s.LIB);
            curr_src += 3;
        } else if curr_src + 8 <= s.string_table.arr.len()
            && &s.string_table.arr[curr_src..curr_src + 8] == b"PLATFORM" {
            var_val = Some(&s.PLATFORM);
            curr_src += 8;
        } else if curr_src + 6 <= s.string_table.arr.len()
            && &s.string_table.arr[curr_src..curr_src + 6] == b"OSNAME" {
            var_val = Some(&s.OSNAME);
            curr_src += 6;
        } else if curr_src + 5 <= s.string_table.arr.len()
            && &s.string_table.arr[curr_src..curr_src + 5] == b"OSREL" {
            var_val = Some(&s.OSREL);
            curr_src += 5;
        } else {
            continue;
        }

        // Require matching {...}
        if curly {
            if curr_src >= s.string_table.arr.len() || s.string_table.arr[curr_src] != b'}' {
                continue;
            }
            curr_src += 1;
        }

        let var_val_str = var_val.unwrap();
        let var_len = var_val_str.len();

        // Make sure we have enough space to write to
        string_table_maybe_grow(&mut s.string_table, bytes_to_dollar + var_len);

        // First copy over the string until the variable
        for i in 0..bytes_to_dollar {
            s.string_table.arr.push(s.string_table.arr[prev_src + i]);
        }
        s.string_table.n += bytes_to_dollar;

        // Then copy the variable value (without null)
        s.string_table.arr.extend_from_slice(var_val_str.as_bytes());
        s.string_table.n += var_len;

        // Update prev_src to continue from after the variable
        prev_src = curr_src;
    }

    // Did we copy anything? That implies a variable was interpolated
    // Copy the remainder, including the \0
    if s.string_table.n > output_start {
        // Find the length of remaining string including null terminator
        let remainder_start = prev_src;
        let mut remainder_len = 0;
        for i in remainder_start..s.string_table.arr.len() {
            remainder_len += 1;
            if i < s.string_table.arr.len() && s.string_table.arr[i] == 0 {
                break;
            }
        }

        string_table_maybe_grow(&mut s.string_table, remainder_len);

        // Copy the remainder
        for i in 0..remainder_len {
            s.string_table.arr.push(s.string_table.arr[remainder_start + i]);
        }
        s.string_table.n += remainder_len;

        return true;
    }

    false
}

pub fn print_colon_delimited_paths(start: &str, indent: &str) {
    let mut current = start;

    loop {
        // Don't print empty string
        if current.is_empty() || current.starts_with('\0') {
            break;
        }

        // Find the next delimiter after start
        let next = current.find(':');

        // Get the part before the colon (or all of it if no colon)
        let part = match next {
            Some(pos) => {
                if pos == 0 {
                    // Empty part, skip it
                    current = &current[1..];
                    continue;
                }
                &current[..pos]
            }
            None => {
                if current.is_empty() {
                    break;
                }
                current
            }
        };

        print!("{}", indent);
        print!("{}", JUST_INDENT);

        // Print the path
        println!("{}", part);

        // We done yet?
        if next.is_none() {
            break;
        }

        // Otherwise continue from after the colon
        current = &current[next.unwrap() + 1..];
    }
}

pub fn print_line(
    depth: usize,
    name: &str,
    color_bold: &str,
    color_regular: &str,
    highlight: bool,
    reason: found_t,
    s: &libtree_state_t,
) {
    tree_preamble(s, depth);

    // Color the filename different than the path name, if we have a path
    if s.color && highlight {
        if let Some(slash_pos) = name.rfind('/') {
            print!("{}", color_regular);
            print!("{}", &name[..=slash_pos]);
            print!("{}", color_bold);
            print!("{}", &name[slash_pos + 1..]);
        } else {
            print!("{}", color_bold);
            print!("{}", name);
        }
    } else {
        if s.color {
            print!("{}", color_bold);
        }
        print!("{}", name);
    }

    if s.color && highlight {
        print!("{} \x1b[33m", CLEAR);  // BOLD_YELLOW
    } else {
        print!(" ");
    }

    match reason.how {
        how_t::RPATH => {
            if reason.depth + 1 >= depth {
                print!("[rpath]");
            } else {
                print!("[rpath of {}]", reason.depth + 1);
            }
        }
        how_t::LD_LIBRARY_PATH => {
            print!("[LD_LIBRARY_PATH]");
        }
        how_t::RUNPATH => {
            print!("[runpath]");
        }
        how_t::LD_SO_CONF => {
            print!("[");
            let conf_name = s.ld_conf_file.rfind('/').map(|pos| &s.ld_conf_file[pos + 1..])
                .unwrap_or(&s.ld_conf_file);
            print!("{}", conf_name);
            print!("]");
        }
        how_t::DIRECT => {
            print!("[direct]");
        }
        how_t::DEFAULT => {
            print!("[default path]");
        }
        _ => {}
    }

    if s.color {
        println!("{}", CLEAR);
    } else {
        println!();
    }
}

pub fn print_error(
    depth: usize,
    needed_not_found: usize,
    needed_buf_offsets: &small_vec_u64_t,
    runpath: Option<&str>,
    s: &mut libtree_state_t,
    no_def_lib: bool,
) {
    // Print all libraries that were not found
    for i in 0..needed_not_found {
        s.found_all_needed[depth] = i + 1 >= needed_not_found;
        tree_preamble(s, depth + 1);

        if s.color {
            print!("{}", BOLD_RED);
        }

        // Get the library name
        let offset = if needed_buf_offsets.n <= SMALL_VEC_SIZE {
            needed_buf_offsets.buf[i] as usize
        } else {
            needed_buf_offsets.heap.as_ref().unwrap()[i] as usize
        };

        let lib_name = std::str::from_utf8(&s.string_table.arr[offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");

        print!("{} not found\n", lib_name);

        if s.color {
            print!("{}", CLEAR);
        }
    }

    // If anything was not found, we print the search paths in order they are considered
    const BRIGHT_BLACK: &str = "\x1b[0;90m";

    let box_vertical = if s.color {
        format!("{}{}{}", JUST_INDENT, REGULAR_RED, LIGHT_QUADRUPLE_DASH_VERTICAL)
            + CLEAR
    } else {
        format!("{}{}", JUST_INDENT, LIGHT_QUADRUPLE_DASH_VERTICAL)
    };

    let mut indent = String::new();
    for i in 0..depth {
        if s.found_all_needed[i] {
            indent.push_str(JUST_INDENT);
        } else {
            indent.push_str(&format!("{}   ", LIGHT_VERTICAL));
        }
    }
    indent.push_str(&box_vertical);

    print!("{}", indent);
    if s.color {
        print!("{}", BRIGHT_BLACK);
    }
    print!(" Paths considered in this order:\n");
    if s.color {
        print!("{}", CLEAR);
    }

    // 1. rpath
    print!("{}", indent);
    if runpath.is_some() {
        if s.color {
            print!("{}", BRIGHT_BLACK);
        }
        print!(" 1. rpath is skipped because runpath was set\n");
        if s.color {
            print!("{}", CLEAR);
        }
    } else {
        if s.color {
            print!("{}", BRIGHT_BLACK);
        }
        print!(" 1. rpath:\n");
        if s.color {
            print!("{}", CLEAR);
        }
        for j in (0..=depth).rev() {
            if s.rpath_offsets[j] != usize::MAX {
                print!("{}", indent);
                if s.color {
                    print!("{}", BRIGHT_BLACK);
                }
                print!("    depth {}", j + 1);
                if s.color {
                    print!("{}", CLEAR);
                }
                print!("\n");

                let rpath_str = std::str::from_utf8(&s.string_table.arr[s.rpath_offsets[j]..])
                    .unwrap_or("")
                    .split('\0')
                    .next()
                    .unwrap_or("");
                print_colon_delimited_paths(rpath_str, &indent);
            }
        }
    }

    // 2. LD_LIBRARY_PATH
    print!("{}", indent);
    if s.color {
        print!("{}", BRIGHT_BLACK);
    }
    if s.ld_library_path_offset == usize::MAX {
        print!(" 2. LD_LIBRARY_PATH was not set\n");
    } else {
        print!(" 2. LD_LIBRARY_PATH:\n");
    }
    if s.color {
        print!("{}", CLEAR);
    }
    if s.ld_library_path_offset != usize::MAX {
        let ld_lib_path = std::str::from_utf8(&s.string_table.arr[s.ld_library_path_offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");
        print_colon_delimited_paths(ld_lib_path, &indent);
    }

    // 3. runpath
    print!("{}", indent);
    if s.color {
        print!("{}", BRIGHT_BLACK);
    }
    if runpath.is_none() {
        print!(" 3. runpath was not set\n");
    } else {
        print!(" 3. runpath:\n");
    }
    if s.color {
        print!("{}", CLEAR);
    }
    if let Some(rp) = runpath {
        print_colon_delimited_paths(rp, &indent);
    }

    // 4. ld config files
    print!("{}", indent);
    if s.color {
        print!("{}", BRIGHT_BLACK);
    }
    if no_def_lib {
        print!(" 4. ld config files not considered due to NODEFLIB flag\n");
    } else {
        print!(" 4. ld config files:\n");
    }
    if s.color {
        print!("{}", CLEAR);
    }
    if !no_def_lib {
        let ld_conf = std::str::from_utf8(&s.string_table.arr[s.ld_so_conf_offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");
        print_colon_delimited_paths(ld_conf, &indent);
    }

    // 5. Standard paths
    print!("{}", indent);
    if s.color {
        print!("{}", BRIGHT_BLACK);
    }
    if no_def_lib {
        print!(" 5. Standard paths not considered due to NODEFLIB flag\n");
    } else {
        print!(" 5. Standard paths:\n");
    }
    if s.color {
        print!("{}", CLEAR);
    }
    if !no_def_lib {
        let default_paths = std::str::from_utf8(&s.string_table.arr[s.default_paths_offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");
        print_colon_delimited_paths(default_paths, &indent);
    }
}

pub fn visited_files_contains(files: &visited_file_array_t, needle: &visited_file_t) -> bool {
    files.arr.iter().any(|f| f.st_dev == needle.st_dev && f.st_ino == needle.st_ino)
}

pub fn visited_files_append(files: &mut visited_file_array_t, new: visited_file_t) {
    files.arr.push(new);
}

pub fn recurse(
    current_file: &str,
    depth: usize,
    s: &mut libtree_state_t,
    compat: compat_t,
    reason: found_t,
) -> LibtreeResult<()> {
    let mut fptr = match File::open(current_file) {
        Ok(f) => f,
        Err(_) => return Err(LibtreeError::CouldNotOpenFile),
    };

    // When we're done recursing, we should give back the memory we've claimed
    let old_buf_size = s.string_table.n;

    // Parse the header
    let mut e_ident = [0u8; 16];
    if fptr.read_exact(&mut e_ident).is_err() {
        return Err(LibtreeError::InvalidMagic);
    }

    // Find magic elfs
    if e_ident[0] != 0x7f || e_ident[1] != b'E' || e_ident[2] != b'L' || e_ident[3] != b'F' {
        return Err(LibtreeError::InvalidMagic);
    }

    // Do at least *some* header validation
    if e_ident[4] != BITS32 && e_ident[4] != BITS64 {
        return Err(LibtreeError::InvalidClass);
    }

    if e_ident[5] != 0x01 && e_ident[5] != 0x02 {
        return Err(LibtreeError::InvalidData);
    }

    let mut curr_type = compat_t {
        any: false,
        class: e_ident[4],
        machine: 0,
    };
    let is_little_endian = e_ident[5] == 0x01;

    // Make sure that we have matching bits with parent
    if !compat.any && compat.class != curr_type.class {
        return Err(LibtreeError::InvalidBits);
    }

    // Make sure that the elf file has the host's endianness
    if is_little_endian != host_is_little_endian() {
        return Err(LibtreeError::InvalidEndianness);
    }

    // Read the ELF header
    let (e_type, e_machine, e_phoff, e_phnum): (u16, u16, u64, u16);

    if curr_type.class == BITS64 {
        let mut header = [0u8; 48]; // sizeof(header_64_t)
        if fptr.read_exact(&mut header).is_err() {
            return Err(LibtreeError::InvalidHeader);
        }
        e_type = u16::from_le_bytes([header[0], header[1]]);
        e_machine = u16::from_le_bytes([header[2], header[3]]);
        e_phoff = u64::from_le_bytes([
            header[16], header[17], header[18], header[19],
            header[20], header[21], header[22], header[23],
        ]);
        e_phnum = u16::from_le_bytes([header[32], header[33]]);
    } else {
        let mut header = [0u8; 36]; // sizeof(header_32_t)
        if fptr.read_exact(&mut header).is_err() {
            return Err(LibtreeError::InvalidHeader);
        }
        e_type = u16::from_le_bytes([header[0], header[1]]);
        e_machine = u16::from_le_bytes([header[2], header[3]]);
        e_phoff = u32::from_le_bytes([header[12], header[13], header[14], header[15]]) as u64;
        e_phnum = u16::from_le_bytes([header[20], header[21]]);
    }

    if e_type != ET_EXEC && e_type != ET_DYN {
        return Err(LibtreeError::NoExecOrDyn);
    }

    curr_type.machine = e_machine;
    if !compat.any && compat.machine != curr_type.machine {
        return Err(LibtreeError::IncompatibleIsa);
    }

    if fptr.seek(SeekFrom::Start(e_phoff)).is_err() {
        return Err(LibtreeError::InvalidPhoff);
    }

    // Read program headers
    let mut pt_load_offset = small_vec_u64_t::new();
    let mut pt_load_vaddr = small_vec_u64_t::new();
    small_vec_u64_init(&mut pt_load_offset);
    small_vec_u64_init(&mut pt_load_vaddr);

    let mut p_offset = u64::MAX;

    if curr_type.class == BITS64 {
        for _ in 0..e_phnum {
            let mut prog = [0u8; 56]; // sizeof(prog_64_t)
            if fptr.read_exact(&mut prog).is_err() {
                small_vec_u64_free(&mut pt_load_offset);
                small_vec_u64_free(&mut pt_load_vaddr);
                return Err(LibtreeError::InvalidProgHeader);
            }
            let p_type = u32::from_le_bytes([prog[0], prog[1], prog[2], prog[3]]);
            let p_off = u64::from_le_bytes([
                prog[8], prog[9], prog[10], prog[11],
                prog[12], prog[13], prog[14], prog[15],
            ]);
            let p_vaddr = u64::from_le_bytes([
                prog[16], prog[17], prog[18], prog[19],
                prog[20], prog[21], prog[22], prog[23],
            ]);

            if p_type == PT_LOAD {
                small_vec_u64_append(&mut pt_load_offset, p_off);
                small_vec_u64_append(&mut pt_load_vaddr, p_vaddr);
            } else if p_type == PT_DYNAMIC {
                p_offset = p_off;
            }
        }
    } else {
        for _ in 0..e_phnum {
            let mut prog = [0u8; 32]; // sizeof(prog_32_t)
            if fptr.read_exact(&mut prog).is_err() {
                small_vec_u64_free(&mut pt_load_offset);
                small_vec_u64_free(&mut pt_load_vaddr);
                return Err(LibtreeError::InvalidProgHeader);
            }
            let p_type = u32::from_le_bytes([prog[0], prog[1], prog[2], prog[3]]);
            let p_off = u32::from_le_bytes([prog[4], prog[5], prog[6], prog[7]]);
            let p_vaddr = u32::from_le_bytes([prog[8], prog[9], prog[10], prog[11]]);

            if p_type == PT_LOAD {
                small_vec_u64_append(&mut pt_load_offset, p_off as u64);
                small_vec_u64_append(&mut pt_load_vaddr, p_vaddr as u64);
            } else if p_type == PT_DYNAMIC {
                p_offset = p_off as u64;
            }
        }
    }

    // At this point we're going to store the file as "success"
    let metadata = match std::fs::metadata(current_file) {
        Ok(m) => m,
        Err(_) => {
            small_vec_u64_free(&mut pt_load_offset);
            small_vec_u64_free(&mut pt_load_vaddr);
            return Err(LibtreeError::CantStat);
        }
    };

    let finfo = visited_file_t {
        st_dev: metadata.dev(),
        st_ino: metadata.ino(),
    };

    let seen_before = visited_files_contains(&s.visited, &finfo);

    if !seen_before {
        visited_files_append(&mut s.visited, finfo);
    }

    // No dynamic section?
    if p_offset == u64::MAX {
        const BOLD_CYAN: &str = "\x1b[1;36m";
        const REGULAR_CYAN: &str = "\x1b[0;36m";
        print_line(depth, current_file, BOLD_CYAN, REGULAR_CYAN, true, reason, s);
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return Ok(());
    }

    // Check if we have PT_LOAD sections
    if pt_load_offset.n == 0 {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return Err(LibtreeError::NoPtLoad);
    }

    // Go to the dynamic section
    if fptr.seek(SeekFrom::Start(p_offset)).is_err() {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return Err(LibtreeError::InvalidDynamicSection);
    }

    let mut no_def_lib = false;
    let mut strtab = u64::MAX;
    let mut rpath = u64::MAX;
    let mut runpath = u64::MAX;
    let mut soname = u64::MAX;
    let mut needed = small_vec_u64_t::new();
    small_vec_u64_init(&mut needed);

    const DT_FLAGS_1: i64 = 0x6ffffffb;
    const DT_1_NODEFLIB: u64 = 0x800;

    loop {
        let (d_tag, d_val): (i64, u64);

        if curr_type.class == BITS64 {
            let mut dyn_entry = [0u8; 16];
            if fptr.read_exact(&mut dyn_entry).is_err() {
                small_vec_u64_free(&mut pt_load_offset);
                small_vec_u64_free(&mut pt_load_vaddr);
                small_vec_u64_free(&mut needed);
                return Err(LibtreeError::InvalidDynamicArrayEntry);
            }
            d_tag = i64::from_le_bytes([
                dyn_entry[0], dyn_entry[1], dyn_entry[2], dyn_entry[3],
                dyn_entry[4], dyn_entry[5], dyn_entry[6], dyn_entry[7],
            ]);
            d_val = u64::from_le_bytes([
                dyn_entry[8], dyn_entry[9], dyn_entry[10], dyn_entry[11],
                dyn_entry[12], dyn_entry[13], dyn_entry[14], dyn_entry[15],
            ]);
        } else {
            let mut dyn_entry = [0u8; 8];
            if fptr.read_exact(&mut dyn_entry).is_err() {
                small_vec_u64_free(&mut pt_load_offset);
                small_vec_u64_free(&mut pt_load_vaddr);
                small_vec_u64_free(&mut needed);
                return Err(LibtreeError::InvalidDynamicArrayEntry);
            }
            d_tag = i32::from_le_bytes([
                dyn_entry[0], dyn_entry[1], dyn_entry[2], dyn_entry[3],
            ]) as i64;
            d_val = u32::from_le_bytes([
                dyn_entry[4], dyn_entry[5], dyn_entry[6], dyn_entry[7],
            ]) as u64;
        }

        match d_tag {
            DT_NULL => break,
            DT_STRTAB => strtab = d_val,
            DT_RPATH => rpath = d_val,
            DT_RUNPATH => runpath = d_val,
            DT_NEEDED => small_vec_u64_append(&mut needed, d_val),
            DT_SONAME => soname = d_val,
            DT_FLAGS_1 => no_def_lib |= (d_val & DT_1_NODEFLIB) == DT_1_NODEFLIB,
            _ => {}
        }
    }

    if strtab == u64::MAX {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut needed);
        return Err(LibtreeError::NoStrtab);
    }

    // Verify that offsets are ordered
    let vaddrs_slice = if pt_load_vaddr.n <= SMALL_VEC_SIZE {
        &pt_load_vaddr.buf[..pt_load_vaddr.n]
    } else {
        pt_load_vaddr.heap.as_ref().unwrap().as_slice()
    };
    if !is_ascending_order(vaddrs_slice) {
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut needed);
        return Err(LibtreeError::VaddrsNotOrdered);
    }

    // Find the file offset corresponding to the strtab virtual address
    let mut vaddr_idx = 0;
    while vaddr_idx + 1 != pt_load_vaddr.n {
        let next_vaddr = if pt_load_vaddr.n <= SMALL_VEC_SIZE {
            pt_load_vaddr.buf[vaddr_idx + 1]
        } else {
            pt_load_vaddr.heap.as_ref().unwrap()[vaddr_idx + 1]
        };
        if strtab >= next_vaddr {
            vaddr_idx += 1;
        } else {
            break;
        }
    }

    let vaddr_at_idx = if pt_load_vaddr.n <= SMALL_VEC_SIZE {
        pt_load_vaddr.buf[vaddr_idx]
    } else {
        pt_load_vaddr.heap.as_ref().unwrap()[vaddr_idx]
    };
    let offset_at_idx = if pt_load_offset.n <= SMALL_VEC_SIZE {
        pt_load_offset.buf[vaddr_idx]
    } else {
        pt_load_offset.heap.as_ref().unwrap()[vaddr_idx]
    };

    let strtab_offset = offset_at_idx + strtab - vaddr_at_idx;

    small_vec_u64_free(&mut pt_load_vaddr);
    small_vec_u64_free(&mut pt_load_offset);

    // Copy the current soname
    let soname_buf_offset = s.string_table.n;
    if soname != u64::MAX {
        if fptr.seek(SeekFrom::Start(strtab_offset + soname)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return Err(LibtreeError::InvalidSoname);
        }
        let _ = string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    let in_exclude_list = soname != u64::MAX && {
        let soname_str = std::str::from_utf8(&s.string_table.arr[soname_buf_offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("");
        is_in_exclude_list(soname_str)
    };

    // No need to recurse deeper when we aren't in very verbose mode
    let should_recurse = depth < s.max_depth
        && ((!seen_before && !in_exclude_list)
            || (!seen_before && in_exclude_list && s.verbosity >= 2)
            || s.verbosity >= 3);

    // Just print the library and return
    if !should_recurse {
        const BOLD_CYAN: &str = "\x1b[1;36m";
        const REGULAR_CYAN: &str = "\x1b[0;36m";
        const REGULAR_MAGENTA: &str = "\x1b[0;35m";
        const REGULAR_BLUE: &str = "\x1b[0;34m";

        let print_name = if soname == u64::MAX || s.path {
            current_file
        } else {
            std::str::from_utf8(&s.string_table.arr[soname_buf_offset..])
                .unwrap_or("")
                .split('\0')
                .next()
                .unwrap_or("")
        };

        let bold_color = if in_exclude_list {
            REGULAR_MAGENTA
        } else if seen_before {
            REGULAR_BLUE
        } else {
            BOLD_CYAN
        };

        let regular_color = if in_exclude_list {
            REGULAR_MAGENTA
        } else if seen_before {
            REGULAR_BLUE
        } else {
            REGULAR_CYAN
        };

        let highlight = !seen_before && !in_exclude_list;
        print_line(depth, print_name, bold_color, regular_color, highlight, reason, s);

        s.string_table.n = old_buf_size;
        small_vec_u64_free(&mut needed);
        return Ok(());
    }

    // Store the ORIGIN string
    let origin = if let Some(slash_pos) = current_file.rfind('/') {
        &current_file[..slash_pos]
    } else {
        "./"
    };

    // Copy DT_RPATH
    if rpath == u64::MAX {
        s.rpath_offsets[depth] = usize::MAX;
    } else {
        s.rpath_offsets[depth] = s.string_table.n;
        if fptr.seek(SeekFrom::Start(strtab_offset + rpath)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return Err(LibtreeError::InvalidRpath);
        }
        let _ = string_table_copy_from_file(&mut s.string_table, &mut fptr);

        // We store the interpolated string right after the literal copy
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, s.rpath_offsets[depth], origin) {
            s.rpath_offsets[depth] = curr_buf_size;
        }
    }

    // Copy DT_RUNPATH
    let mut runpath_buf_offset = s.string_table.n;
    if runpath != u64::MAX {
        if fptr.seek(SeekFrom::Start(strtab_offset + runpath)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return Err(LibtreeError::InvalidRunpath);
        }
        let _ = string_table_copy_from_file(&mut s.string_table, &mut fptr);

        // We store the interpolated string right after the literal copy
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, runpath_buf_offset, origin) {
            runpath_buf_offset = curr_buf_size;
        }
    }

    // Copy needed libraries
    let mut needed_buf_offsets = small_vec_u64_t::new();
    small_vec_u64_init(&mut needed_buf_offsets);

    for i in 0..needed.n {
        let needed_val = if needed.n <= SMALL_VEC_SIZE {
            needed.buf[i]
        } else {
            needed.heap.as_ref().unwrap()[i]
        };

        small_vec_u64_append(&mut needed_buf_offsets, s.string_table.n as u64);
        if fptr.seek(SeekFrom::Start(strtab_offset + needed_val)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed_buf_offsets);
            small_vec_u64_free(&mut needed);
            return Err(LibtreeError::InvalidNeeded);
        }
        let _ = string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    drop(fptr);

    const BOLD_CYAN: &str = "\x1b[1;36m";
    const REGULAR_CYAN: &str = "\x1b[0;36m";
    const REGULAR_MAGENTA: &str = "\x1b[0;35m";
    const REGULAR_BLUE: &str = "\x1b[0;34m";

    let print_name = if soname == u64::MAX || s.path {
        current_file
    } else {
        std::str::from_utf8(&s.string_table.arr[soname_buf_offset..])
            .unwrap_or("")
            .split('\0')
            .next()
            .unwrap_or("")
    };

    let bold_color = if in_exclude_list {
        REGULAR_MAGENTA
    } else if seen_before {
        REGULAR_BLUE
    } else {
        BOLD_CYAN
    };

    let regular_color = if in_exclude_list {
        REGULAR_MAGENTA
    } else if seen_before {
        REGULAR_BLUE
    } else {
        REGULAR_CYAN
    };

    let highlight = !seen_before && !in_exclude_list;
    print_line(depth, print_name, bold_color, regular_color, highlight, reason, s);

    // Finally start searching
    let mut exit_code = Ok(());
    let mut needed_not_found = needed_buf_offsets.n;

    // Skip common libraries if not verbose
    if needed_not_found > 0 && s.verbosity == 0 {
        apply_exclude_list(&mut needed_not_found, &mut needed_buf_offsets, s);
    }

    if needed_not_found > 0 {
        let result = check_absolute_paths(&mut needed_not_found, &mut needed_buf_offsets, depth, s, curr_type);
        if result.is_err() {
            exit_code = result;
        }
    }

    // Consider rpaths only when runpath is empty
    if runpath == u64::MAX {
        for j in (0..=depth).rev() {
            if needed_not_found == 0 {
                break;
            }
            if s.rpath_offsets[j] == usize::MAX {
                continue;
            }

            let result = check_search_paths(
                found_t { how: how_t::RPATH, depth: j },
                s.rpath_offsets[j],
                &mut needed_not_found,
                &mut needed_buf_offsets,
                depth,
                s,
                curr_type,
            );
            if result.is_err() {
                exit_code = result;
            }
        }
    }

    // Then try LD_LIBRARY_PATH, if we have it
    if needed_not_found > 0 && s.ld_library_path_offset != usize::MAX {
        let result = check_search_paths(
            found_t { how: how_t::LD_LIBRARY_PATH, depth: 0 },
            s.ld_library_path_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type,
        );
        if result.is_err() {
            exit_code = result;
        }
    }

    // Then consider runpaths
    if needed_not_found > 0 && runpath != u64::MAX {
        let result = check_search_paths(
            found_t { how: how_t::RUNPATH, depth: 0 },
            runpath_buf_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type,
        );
        if result.is_err() {
            exit_code = result;
        }
    }

    // Check ld.so.conf paths
    if needed_not_found > 0 && !no_def_lib {
        let result = check_search_paths(
            found_t { how: how_t::LD_SO_CONF, depth: 0 },
            s.ld_so_conf_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type,
        );
        if result.is_err() {
            exit_code = result;
        }
    }

    // Then consider standard paths
    if needed_not_found > 0 && !no_def_lib {
        let result = check_search_paths(
            found_t { how: how_t::DEFAULT, depth: 0 },
            s.default_paths_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type,
        );
        if result.is_err() {
            exit_code = result;
        }
    }

    // Finally summarize those that could not be found
    if needed_not_found > 0 {
        let runpath_str: Option<String> = if runpath == u64::MAX {
            None
        } else {
            Some(
                std::str::from_utf8(&s.string_table.arr[runpath_buf_offset..])
                    .unwrap_or("")
                    .split('\0')
                    .next()
                    .unwrap_or("")
                    .to_string()
            )
        };

        let runpath_ref = runpath_str.as_ref().map(|s| s.as_str());
        print_error(depth, needed_not_found, &needed_buf_offsets, runpath_ref, s, no_def_lib);
        s.string_table.n = old_buf_size;
        small_vec_u64_free(&mut needed_buf_offsets);
        small_vec_u64_free(&mut needed);
        return Err(LibtreeError::DependencyNotFound);
    }

    // Free memory in our string table
    s.string_table.n = old_buf_size;
    small_vec_u64_free(&mut needed_buf_offsets);
    small_vec_u64_free(&mut needed);
    exit_code
}

pub fn ld_conf_globbing(st: &mut string_table_t, pattern: &str) -> LibtreeResult<()> {
    use glob::glob;

    match glob(pattern) {
        Ok(paths) => {
            for entry in paths {
                if let Ok(path) = entry {
                    let _ = parse_ld_config_file(st, path.to_str().unwrap_or(""));
                }
            }
            Ok(())
        }
        Err(_) => Ok(()), // GLOB_NOMATCH is not an error
    }
}

pub fn parse_ld_config_file(st: &mut string_table_t, path: &str) -> LibtreeResult<()> {
    use std::io::BufRead;

    let file = match std::fs::File::open(path) {
        Ok(f) => f,
        Err(_) => return Err(LibtreeError::CouldNotOpenFile),
    };

    let reader = std::io::BufReader::new(file);

    for line_result in reader.lines() {
        let line = match line_result {
            Ok(l) => l,
            Err(_) => continue,
        };

        // Remove leading/trailing whitespace
        let trimmed = line.trim();

        // Remove comments
        let without_comment = if let Some(pos) = trimmed.find('#') {
            &trimmed[..pos]
        } else {
            trimmed
        };

        let cleaned = without_comment.trim();

        // Skip empty lines
        if cleaned.is_empty() {
            continue;
        }

        // Handle 'include ' directive
        if cleaned.starts_with("include ") {
            let pattern = cleaned[8..].trim();

            // Handle relative paths
            let full_pattern = if !pattern.starts_with('/') {
                if let Some(dir_pos) = path.rfind('/') {
                    format!("{}/{}", &path[..dir_pos], pattern)
                } else {
                    pattern.to_string()
                }
            } else {
                pattern.to_string()
            };

            let _ = ld_conf_globbing(st, &full_pattern);
        } else {
            // Regular path entry
            string_table_store(st, cleaned);
            // Replace trailing \0 with :
            if let Some(last) = st.arr.last_mut() {
                if *last == 0 {
                    *last = b':';
                }
            }
        }
    }

    Ok(())
}

pub fn parse_ld_so_conf(s: &mut libtree_state_t) {
    s.ld_so_conf_offset = s.string_table.arr.len();

    // Parse the ld.so.conf file
    let _ = parse_ld_config_file(&mut s.string_table, &s.ld_conf_file.clone());

    // Replace the last ':' with '\0' if we have paths
    if s.string_table.arr.len() > s.ld_so_conf_offset {
        if let Some(last) = s.string_table.arr.last_mut() {
            if *last == b':' {
                *last = 0;
            }
        }
    } else {
        string_table_store(&mut s.string_table, "");
    }
}

pub fn parse_ld_library_path(s: &mut libtree_state_t) {
    s.ld_library_path_offset = usize::MAX;

    if let Ok(val) = std::env::var("LD_LIBRARY_PATH") {
        s.ld_library_path_offset = s.string_table.arr.len();
        string_table_store(&mut s.string_table, &val);

        // Replace ; with :
        let start = s.ld_library_path_offset;
        for i in start..s.string_table.arr.len() {
            if s.string_table.arr[i] == b';' {
                s.string_table.arr[i] = b':';
            }
        }
    }
}

pub fn set_default_paths(s: &mut libtree_state_t) {
    s.default_paths_offset = s.string_table.arr.len();
    string_table_store(&mut s.string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}

pub fn libtree_state_init() -> libtree_state_t {
    use std::io::IsTerminal;

    libtree_state_t {
        verbosity: 0,
        path: false,
        color: std::env::var("NO_COLOR").is_err() && std::io::stdout().is_terminal(),
        ld_conf_file: "/etc/ld.so.conf".to_string(),
        max_depth: MAX_RECURSION_DEPTH,
        string_table: string_table_t {
            arr: Vec::with_capacity(1024),
            n: 0,
            capacity: 1024,
        },
        visited: visited_file_array_t { arr: Vec::with_capacity(256) },
        PLATFORM: String::new(),
        LIB: "lib".to_string(),
        OSNAME: String::new(),
        OSREL: String::new(),
        rpath_offsets: [usize::MAX; MAX_RECURSION_DEPTH],
        ld_library_path_offset: usize::MAX,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: [false; MAX_RECURSION_DEPTH],
    }
}

pub fn libtree_state_free(s: &mut libtree_state_t) {
    // In Rust, cleanup is automatic via Drop trait.
    // This function is kept for API compatibility but is a no-op.
    // The Vec fields will be automatically freed when the struct is dropped.
    s.string_table.arr.clear();
    s.string_table.n = 0;
    s.visited.arr.clear();
}

pub fn print_tree(paths: &[String]) -> LibtreeResult<()> {
    // First collect standard paths
    let mut s = libtree_state_init();

    parse_ld_so_conf(&mut s);
    parse_ld_library_path(&mut s);
    set_default_paths(&mut s);

    let mut exit_code = Ok(());

    for path in paths {
        let code = recurse(
            path,
            0,
            &mut s,
            compat_t { any: true, class: 0, machine: 0 },
            found_t { how: how_t::INPUT, depth: 0 },
        );

        use std::io::Write;
        let _ = std::io::stdout().flush();

        if let Err(e) = code {
            exit_code = Err(e);
            eprint!("Error [{}]: ", path);

            let msg = match e {
                LibtreeError::InvalidMagic => "Invalid ELF magic bytes\n",
                LibtreeError::InvalidClass => "Invalid ELF class\n",
                LibtreeError::InvalidData => "Invalid ELF data\n",
                LibtreeError::InvalidHeader => "Invalid ELF header\n",
                LibtreeError::InvalidBits => "Invalid bits\n",
                LibtreeError::InvalidEndianness => "Invalid endianness\n",
                LibtreeError::NoExecOrDyn => "Not an ET_EXEC or ET_DYN ELF file\n",
                LibtreeError::InvalidPhoff => "Invalid ELF program header offset\n",
                LibtreeError::InvalidProgHeader => "Invalid ELF program header\n",
                LibtreeError::CantStat => "Can't stat file\n",
                LibtreeError::InvalidDynamicSection => "Invalid ELF dynamic section\n",
                LibtreeError::InvalidDynamicArrayEntry => "Invalid ELF dynamic array entry\n",
                LibtreeError::NoStrtab => "No ELF string table found\n",
                LibtreeError::InvalidSoname => "Can't read DT_SONAME\n",
                LibtreeError::InvalidRpath => "Can't read DT_RPATH\n",
                LibtreeError::InvalidRunpath => "Can't read DT_RUNPATH\n",
                LibtreeError::InvalidNeeded => "Can't read DT_NEEDED\n",
                LibtreeError::DependencyNotFound => "Not all dependencies were found\n",
                LibtreeError::NoPtLoad => "No PT_LOAD found in ELF file\n",
                LibtreeError::VaddrsNotOrdered => "Virtual addresses are not ordered\n",
                LibtreeError::CouldNotOpenFile => "Could not open file\n",
                LibtreeError::IncompatibleIsa => "Incompatible ISA\n",
            };

            eprint!("{}", msg);
            let _ = std::io::stderr().flush();
        }
    }

    libtree_state_free(&mut s);
    exit_code
}
