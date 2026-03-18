use crate::*;
use lazy_static::lazy_static;
use std::alloc::Layout;
use std::alloc::handle_alloc_error;
use std::clone::Clone;
use std::env;
use std::ffi::CStr;
use std::fs::File;
use std::io::Read;
use std::io::Result as IoResult;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::io;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
use std::os::linux::raw::stat;
use std::os::raw::c_char;
use std::os::raw::c_longlong;
use std::os::raw::c_ulonglong;
use std::process;
use std::ptr;
pub fn utoa(str: &mut [u8], v: usize) {
    let mut p = 0;
    let mut value = v;
    
    // Convert digits to characters in reverse order
    while value > 0 {
        str[p] = b'0' + (value % 10) as u8;
        p += 1;
        value /= 10;
    }
    
    let len = p;
    
    // Reverse the string to get the correct order
    for i in 0..(len / 2) {
        let tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
    
    // Add null terminator if there's space
    if len < str.len() {
        str[len] = b'\0';
    }
}
pub fn host_is_little_endian() -> bool {
    let test: i32 = 1;
    let bytes: &[u8] = unsafe { std::slice::from_raw_parts(&test as *const _ as *const u8, std::mem::size_of::<i32>()) };
    bytes[0] == 1
}
pub fn is_ascending_order(v: &[u64], n: usize) -> bool {
    for j in 1..n {
        if v[j - 1] >= v[j] {
            return false;
        }
    }
    true
}

pub fn print_colon_delimited_paths(start: Option<&str>, indent: Option<&str>) {
    // Convert Option<&str> to &str or return early if None
    let start = match start {
        Some(s) => s,
        None => return,
    };
    let indent = match indent {
        Some(i) => i,
        None => return,
    };

    // Convert to bytes for processing
    let mut bytes = start.as_bytes();
    
    while !bytes.is_empty() {
        if bytes[0] == b'\0' {
            break;
        }
        
        // Find the next colon (':') or end of string
        let next_pos = bytes.iter().position(|&b| b == b':');
        
        if next_pos == Some(0) {
            // Skip empty path (colon at start)
            bytes = &bytes[1..];
            continue;
        }
        
        // Write indent and additional spaces
        let _ = io::stdout().write_all(indent.as_bytes());
        let _ = io::stdout().write_all(b"    ");
        
        match next_pos {
            None => {
                // No colon found, print remaining bytes as string
                let _ = io::stdout().write_all(bytes);
                let _ = io::stdout().write_all(b"\n");
            }
            Some(pos) => {
                // Print the segment before the colon
                let _ = io::stdout().write_all(&bytes[..pos]);
                let _ = io::stdout().write_all(b"\n");
            }
        }
        
        match next_pos {
            None => break,
            Some(pos) => {
                // Move to next segment after colon
                bytes = &bytes[pos + 1..];
            }
        }
    }
}

lazy_static! {
    pub static ref EXCLUDE_LIST: [&'static str; 14] = [
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
        "libstdc++.so"
    ];
}

pub fn is_in_exclude_list(soname: Option<&str>) -> i32 {
    let soname_str = match soname {
        Some(s) => s,
        None => return 0,
    };
    
    if soname_str.is_empty() {
        return 0;
    }
    
    let bytes = soname_str.as_bytes();
    let mut current_index = bytes.len() - 1;
    
    while current_index > 0 {
        let c = bytes[current_index];
        if (c >= b'0' && c <= b'9') || c == b'.' {
            current_index -= 1;
        } else {
            break;
        }
    }
    
    let prefix = &soname_str[..=current_index];
    
    for &excluded in EXCLUDE_LIST.iter() {
        if prefix == excluded {
            return 1;
        }
    }
    
    0
}
pub fn small_vec_u64_init(v: &mut SmallVecU64T) {
    // Initialize all fields to default values
    v.buf = [0; 16];
    v.p = None;
    v.n = 0;
    v.capacity = 16;
}

pub fn small_vec_u64_append(v: &mut SmallVecU64T, val: u64) {
    if v.n < 16 {
        v.buf[v.n] = val;
        v.n += 1;
        return;
    }

    if v.n == 16 {
        v.capacity = 2 * 16;
        let layout = Layout::array::<u64>(v.capacity).unwrap();
        let ptr = unsafe { std::alloc::alloc(layout) as *mut u64 };
        if ptr.is_null() {
            handle_alloc_error(layout);
        }

        unsafe {
            std::ptr::copy_nonoverlapping(v.buf.as_ptr(), ptr, 16);
        }

        v.p = Some(unsafe { Box::from_raw(std::slice::from_raw_parts_mut(ptr, v.capacity)) });
    } else if v.n == v.capacity {
        v.capacity *= 2;
        let layout = Layout::array::<u64>(v.capacity).unwrap();
        let old_ptr = match &v.p {
            Some(boxed) => Box::into_raw(boxed.clone()) as *mut u64,
            None => unreachable!(),
        };
        let ptr = unsafe { std::alloc::realloc(old_ptr as *mut u8, layout, v.capacity * std::mem::size_of::<u64>()) as *mut u64 };
        if ptr.is_null() {
            handle_alloc_error(layout);
        }
        v.p = Some(unsafe { Box::from_raw(std::slice::from_raw_parts_mut(ptr, v.capacity)) });
    }

    match &mut v.p {
        Some(p) => p[v.n] = val,
        None => unreachable!(),
    }
    v.n += 1;
}
pub fn small_vec_u64_free(v: &mut SmallVecU64T) {
    if v.n <= 16 {
        return;
    }
    v.p = None; // Equivalent to free(v->p) and setting v->p = 0
}
pub fn string_table_maybe_grow(t: &mut StringTableT, n: usize) {
    if (t.n + n) <= t.capacity {
        return;
    }
    
    t.capacity = 2 * (t.n + n);
    
    match &mut t.arr {
        Some(arr) => {
            arr.resize(t.capacity, '\0');
        },
        None => {
            t.arr = Some(vec!['\0'; t.capacity]);
        }
    }
}
pub fn tree_preamble(s: &mut LibtreeStateT, depth: usize) {
    if depth == 0 {
        return;
    }
    
    for i in 0..(depth - 1) {
        let output = if s.found_all_needed[i] != '\0' {
            "    "
        } else {
            "\u{2502}   "
        };
        io::stdout().write_all(output.as_bytes()).unwrap();
    }

    let output = if s.found_all_needed[depth - 1] != '\0' {
        "\u{2514}\u{2500}\u{2500} "
    } else {
        "\u{251C}\u{2500}\u{2500} "
    };
    io::stdout().write_all(output.as_bytes()).unwrap();
}
#[derive(Clone)]
pub struct VisitedFileT {
    pub st_dev: dev_t,
    pub st_ino: ino_t,
}

pub fn visited_files_append(files: &mut VisitedFileArrayT, new: &stat) {
    if files.n == files.capacity {
        files.capacity *= 2;
        if let Some(ref mut arr) = files.arr {
            arr.reserve(files.capacity - arr.len());
        } else {
            files.arr = Some(Vec::with_capacity(files.capacity));
        }
        
        // In Rust, Vec will automatically handle allocation failure by panicking,
        // which is the idiomatic way to handle OOM (Out Of Memory) situations.
        // If you want to handle it differently, you could use `try_reserve` and handle the error.
    }

    if let Some(ref mut arr) = files.arr {
        arr.push(visited_file_t::VisitedFileT {
            st_dev: new.st_dev,
            st_ino: new.st_ino,
        });
        files.n += 1;
    } else {
        // This should never happen since we initialize the Vec above if it's None
        process::exit(1);
    }
}
pub fn libtree_state_init(s: &mut LibtreeStateT) {
    s.string_table.n = 0;
    s.string_table.capacity = 1024;
    s.string_table.arr = Some(vec!['\0'; s.string_table.capacity]);
    
    s.visited.n = 0;
    s.visited.capacity = 256;
    s.visited.arr = Some(Vec::with_capacity(s.visited.capacity));
}
pub fn libtree_state_free(s: &mut LibtreeStateT) {
    // In Rust, memory is automatically managed by the ownership system.
    // The StringTableT and VisitedFileArrayT fields will be dropped when the struct is dropped.
    // For Option-wrapped Vecs, we can clear them if they contain a value
    if let Some(arr) = &mut s.string_table.arr {
        arr.clear();
    }
    if let Some(arr) = &mut s.visited.arr {
        arr.clear();
    }
}
pub fn string_table_store(t: &mut StringTableT, str: &str) {
    let n = str.len() + 1; // +1 for null terminator equivalent
    string_table_maybe_grow(t, n);
    
    // Convert the string to chars and extend the array
    if let Some(arr) = &mut t.arr {
        arr.extend(str.chars());
        arr.push('\0'); // Add null terminator equivalent
    } else {
        let mut chars: Vec<char> = str.chars().collect();
        chars.push('\0');
        t.arr = Some(chars);
    }
    
    t.n += n;
}

pub fn string_table_copy_from_file(t: &mut StringTableT, fptr: &mut impl Read) {
    let mut buf = [0u8; 1]; // Buffer to read one byte at a time
    
    loop {
        match fptr.read(&mut buf) {
            Ok(0) => break, // EOF
            Ok(1) => {
                let c = buf[0] as char;
                if c == '\0' {
                    break;
                }
                string_table_maybe_grow(t, 1);
                if let Some(ref mut arr) = t.arr {
                    arr.push(c);
                    t.n += 1;
                }
            }
            Err(_) => break, // Error reading, treat as EOF
            _ => unreachable!(), // Shouldn't happen with 1-byte reads
        }
    }

    string_table_maybe_grow(t, 1);
    if let Some(ref mut arr) = t.arr {
        arr.push('\0');
        t.n += 1;
    }
}

pub fn visited_files_contains(files: &VisitedFileArrayT, needle: &libc::stat) -> i32 {
    if let Some(arr) = &files.arr {
        for f in arr.iter() {
            if f.st_dev == needle.st_dev && f.st_ino == needle.st_ino {
                return 1;
            }
        }
    }
    0
}
pub fn parse_ld_library_path(s: &mut LibtreeStateT) {
    s.ld_library_path_offset = usize::MAX;
    
    let val = env::var("LD_LIBRARY_PATH").ok();
    if val.is_none() {
        return;
    }
    
    let val = val.unwrap();
    s.ld_library_path_offset = s.string_table.n;
    string_table_store(&mut s.string_table, &val);
    
    // Safely unwrap the Option<Vec<char>> to get a mutable reference to the vector
    if let Some(arr) = s.string_table.arr.as_mut() {
        unsafe {
            let search_start = arr.as_mut_ptr().add(s.ld_library_path_offset) as *mut c_char;
            let mut search = search_start;
            
            while !search.is_null() {
                search = libc::strchr(search, b';' as i32);
                if search.is_null() {
                    break;
                }
                *search = b':' as c_char;
                search = search.add(1);
            }
        }
    }
}
pub fn set_default_paths(s: &mut LibtreeStateT) {
    s.default_paths_offset = s.string_table.n;
    string_table_store(&mut s.string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}
pub fn apply_exclude_list(needed_not_found: &mut usize, needed_buf_offsets: &mut SmallVecU64T, s: &LibtreeStateT) {
    let mut i = 0;
    while i < *needed_not_found {
        // Get the offset safely
        let offset = {
            let p = needed_buf_offsets.p.as_ref().expect("p should be initialized");
            p[i] as usize
        };

        // Get the string reference safely
        let string_ptr = s.string_table.arr.as_ref().expect("string_table.arr should be initialized").as_ptr().wrapping_add(offset);
        let c_str = unsafe { std::ffi::CStr::from_ptr(string_ptr as *const i8) };

        let str_option = c_str.to_str().ok();
        if is_in_exclude_list(str_option) != 0 {
            // Perform the swap
            let last = *needed_not_found - 1;
            {
                let p = needed_buf_offsets.p.as_mut().expect("p should be initialized");
                let tmp = p[i];
                p[i] = p[last];
                p[last] = tmp;
            }
            *needed_not_found -= 1;
        } else {
            i += 1;
        }
    }
}
pub fn helper_recurse_1(
    curr_type_ref: &mut CompatT,
    compat: CompatT,
    fptr: &mut File,
    mut header: HeaderUnion,
) -> Result<(), i32> {
    let mut curr_type = curr_type_ref.clone();

    // Read header.h64
    if fptr.read_exact(unsafe { header.h64_as_mut_bytes() }).is_err() {
        return Err(14);
    }

    // Check e_type
    unsafe {
        if header.h64.e_type != 2 && header.h64.e_type != 3 {
            return Err(17);
        }

        curr_type.machine = header.h64.e_machine;
    }

    // Check machine compatibility
    if compat.any == '\0' && compat.machine != curr_type.machine {
        return Err(32);
    }

    // Seek to e_phoff
    unsafe {
        if fptr.seek(SeekFrom::Start(header.h64.e_phoff)).is_err() {
            return Err(18);
        }
    }

    *curr_type_ref = curr_type;
    Ok(())
}

// Helper union for header (similar to C union)
pub union HeaderUnion {
    pub h64: std::mem::ManuallyDrop<Header64T>,
    pub h32: std::mem::ManuallyDrop<Header32T>,
}

impl HeaderUnion {
    // Helper method to get mutable bytes for h64
    pub unsafe fn h64_as_mut_bytes(&mut self) -> &mut [u8] {
        std::slice::from_raw_parts_mut(
            &mut *self.h64 as *mut Header64T as *mut u8,
            std::mem::size_of::<Header64T>(),
        )
    }
}
pub fn helper_recurse_3(
    no_def_lib_ref: &mut i32,
    strtab_ref: &mut u64,
    rpath_ref: &mut u64,
    runpath_ref: &mut u64,
    soname_ref: &mut u64,
    cont_ref: &mut i32,
    fptr: &mut impl Read,
    curr_type: &CompatT,
    pt_load_offset: &mut SmallVecU64T,
    pt_load_vaddr: &mut SmallVecU64T,
    needed: &mut SmallVecU64T,
) -> IoResult<()> {
    let mut no_def_lib = *no_def_lib_ref;
    let mut strtab = *strtab_ref;
    let mut rpath = *rpath_ref;
    let mut runpath = *runpath_ref;
    let mut soname = *soname_ref;
    let mut cont = *cont_ref;
    let (mut d_tag, mut d_val);

    if curr_type.class == 2 {
        let mut dyn_64 = Dyn_64_t {
            d_tag: 0,
            d_val: 0,
        };
        fptr.read_exact(unsafe {
            std::slice::from_raw_parts_mut(
                &mut dyn_64 as *mut _ as *mut u8,
                std::mem::size_of::<Dyn_64_t>(),
            )
        })?;
        d_tag = dyn_64.d_tag as u64;
        d_val = dyn_64.d_val;
    } else {
        let mut dyn_32 = Dyn_32_t {
            d_tag: 0,
            d_val: 0,
        };
        fptr.read_exact(unsafe {
            std::slice::from_raw_parts_mut(
                &mut dyn_32 as *mut _ as *mut u8,
                std::mem::size_of::<Dyn_32_t>(),
            )
        })?;
        d_tag = dyn_32.d_tag as u64;
        d_val = dyn_32.d_val as u64;
    }

    match d_tag {
        0 => {
            cont = 0;
        }
        5 => {
            strtab = d_val;
        }
        15 => {
            rpath = d_val;
        }
        29 => {
            runpath = d_val;
        }
        1 => {
            small_vec_u64_append(needed, d_val);
        }
        14 => {
            soname = d_val;
        }
        0x6ffffffb => {
            no_def_lib |= if (0x800 & d_val) == 0x800 { 1 } else { 0 };
        }
        _ => {}
    }

    *no_def_lib_ref = no_def_lib;
    *strtab_ref = strtab;
    *rpath_ref = rpath;
    *runpath_ref = runpath;
    *soname_ref = soname;
    *cont_ref = cont;

    Ok(())
}

// Helper struct for 32-bit case (not provided in original dependencies)
#[derive(Clone)]
struct Dyn_32_t {
    d_tag: i32,
    d_val: u32,
}
pub fn helper_interpolate_variables_1(
    prev_src_ref: &mut usize,
    curr_src_ref: &mut usize,
    s: &mut LibtreeStateT,
    ORIGIN: &str,
    st: &mut StringTableT,
) -> Option<()> {
    let mut prev_src = *prev_src_ref;
    let mut curr_src = *curr_src_ref;

    // Find '$' character (equivalent to strchr)
    let arr = st.arr.as_ref()?;
    let dollar_pos = arr[curr_src..].iter().position(|&c| c == '$')?;
    let dollar = curr_src + dollar_pos;
    
    curr_src = dollar;
    let bytes_to_dollar = curr_src - prev_src;
    curr_src += 1;

    let mut curly = false;
    if arr.get(curr_src)? == &'{' {
        curly = true;
        curr_src += 1;
    }

    let var_val = if curr_src + 6 <= arr.len() && &arr[curr_src..curr_src+6] == ['O', 'R', 'I', 'G', 'I', 'N'] {
        curr_src += 6;
        ORIGIN
    } else if curr_src + 3 <= arr.len() && &arr[curr_src..curr_src+3] == ['L', 'I', 'B'] {
        curr_src += 3;
        s.LIB.as_deref()?
    } else if curr_src + 8 <= arr.len() && &arr[curr_src..curr_src+8] == ['P', 'L', 'A', 'T', 'F', 'O', 'R', 'M'] {
        curr_src += 8;
        s.PLATFORM.as_deref()?
    } else if curr_src + 6 <= arr.len() && &arr[curr_src..curr_src+6] == ['O', 'S', 'N', 'A', 'M', 'E'] {
        curr_src += 6;
        s.OSNAME.as_deref()?
    } else if curr_src + 5 <= arr.len() && &arr[curr_src..curr_src+5] == ['O', 'S', 'R', 'E', 'L'] {
        curr_src += 5;
        s.OSREL.as_deref()?
    } else {
        return None;
    };

    if curly {
        if arr.get(curr_src)? != &'}' {
            return None;
        }
        curr_src += 1;
    }

    let var_len = var_val.len();
    string_table_maybe_grow(st, bytes_to_dollar + var_len);

    // Safe because we've checked bounds and grown the table if needed
    let arr = st.arr.as_mut()?;
    let (dest, src) = arr.split_at_mut(s.string_table.n);
    dest[s.string_table.n..s.string_table.n + bytes_to_dollar]
        .copy_from_slice(&src[prev_src - s.string_table.n..prev_src - s.string_table.n + bytes_to_dollar]);
    s.string_table.n += bytes_to_dollar;

    prev_src = curr_src;

    let var_val_chars: Vec<char> = var_val.chars().collect();
    arr[s.string_table.n..s.string_table.n + var_len]
        .copy_from_slice(&var_val_chars[..var_len]);
    s.string_table.n += var_len;

    *prev_src_ref = prev_src;
    *curr_src_ref = curr_src;

    Some(())
}
pub fn interpolate_variables(s: &mut LibtreeStateT, src: usize, ORIGIN: &str) -> i32 {
    let mut prev_src = src;
    let mut curr_src = src;
    
    loop {
        let st_ptr = &mut s.string_table as *mut _;
        if helper_interpolate_variables_1(&mut prev_src, &mut curr_src, s, ORIGIN, unsafe { &mut *st_ptr }).is_none() {
            break;
        }
    }
    
    if prev_src != src {
        let st = &mut s.string_table;
        let arr_ptr = st.arr.as_mut().expect("string table array should be initialized").as_mut_ptr();
        let c_str = unsafe { std::ffi::CStr::from_ptr(arr_ptr.add(prev_src) as *const i8) };
        let n = c_str.to_bytes().len() + 1;
        
        string_table_maybe_grow(st, n);
        
        unsafe {
            std::ptr::copy_nonoverlapping(
                arr_ptr.add(prev_src),
                arr_ptr.add(st.n),
                n
            );
        }
        
        st.n += n;
        return 1;
    }
    
    0
}
pub fn helper_print_error_1(depth: usize, s: &LibtreeStateT, indent: &str) {
    if s.color != 0 {
        write!(io::stdout(), "\x1B[0;90m").unwrap();
    }
    write!(io::stdout(), " 1. rpath:\n").unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1B[0m").unwrap();
    }

    for j in (0..=depth).rev() {
        if s.rpath_offsets[j] != usize::MAX {
            let mut num = [0u8; 8];
            utoa(&mut num, j + 1);
            
            write!(io::stdout(), "{}", indent).unwrap();
            if s.color != 0 {
                write!(io::stdout(), "\x1B[0;90m").unwrap();
            }
            write!(io::stdout(), "    depth ").unwrap();
            write!(io::stdout(), "{}", std::str::from_utf8(&num).unwrap().trim_matches('\0')).unwrap();
            if s.color != 0 {
                write!(io::stdout(), "\x1B[0m").unwrap();
            }
            writeln!(io::stdout()).unwrap();
            
            let offset = s.rpath_offsets[j];
            if let Some(arr) = &s.string_table.arr {
                if offset < arr.len() {
                    let mut end = offset;
                    while end < arr.len() && arr[end] != '\0' {
                        end += 1;
                    }
                    let substring: String = arr[offset..end].iter().collect();
                    print_colon_delimited_paths(Some(&substring), Some(indent));
                }
            }
        }
    }
}
pub fn print_error(
    depth: usize,
    needed_not_found: usize,
    needed_buf_offsets: &SmallVecU64T,
    runpath: Option<&str>,
    s: &mut LibtreeStateT,
    no_def_lib: bool,
) {
    for i in 0..needed_not_found {
        s.found_all_needed[depth] = if (i + 1) >= needed_not_found { '\x01' } else { '\x00' };
        tree_preamble(s, depth + 1);
        if s.color != 0 {
            write!(io::stdout(), "\x1b[1;31m").unwrap();
        }
        let offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
        let string_start = &s.string_table.arr.as_ref().unwrap()[offset..];
        // Find the null terminator to get the actual string
        if let Some(null_pos) = string_start.iter().position(|&c| c == '\0') {
            let char_slice = &string_start[..null_pos];
            let string: String = char_slice.iter().collect();
            write!(io::stdout(), "{}", string).unwrap();
        } else {
            let string: String = string_start.iter().collect();
            write!(io::stdout(), "{}", string).unwrap();
        }
        write!(io::stdout(), " not found\n").unwrap();
        if s.color != 0 {
            write!(io::stdout(), "\x1b[0m").unwrap();
        }
    }

    let box_vertical = if s.color != 0 {
        "    \x1b[0;31m\u{250a}\x1b[0m"
    } else {
        "    \u{250a}"
    };

    let indent_len = ("\u{2502}   ".len() * depth) + box_vertical.len() + 1;
    let mut indent = String::with_capacity(indent_len);
    
    for i in 0..depth {
        if s.found_all_needed[i] != '\0' {
            indent.push_str("    ");
        } else {
            indent.push_str("\u{2502}   ");
        }
    }
    
    indent.push_str(box_vertical);
    
    write!(io::stdout(), "{}", indent).unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0;90m").unwrap();
    }
    write!(io::stdout(), " Paths considered in this order:\n").unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0m").unwrap();
    }
    
    write!(io::stdout(), "{}", indent).unwrap();
    if runpath.is_some() {
        if s.color != 0 {
            write!(io::stdout(), "\x1b[0;90m").unwrap();
        }
        write!(io::stdout(), " 1. rpath is skipped because runpath was set\n").unwrap();
        if s.color != 0 {
            write!(io::stdout(), "\x1b[0m").unwrap();
        }
    } else {
        helper_print_error_1(depth, s, &indent);
    }
    
    write!(io::stdout(), "{}", indent).unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0;90m").unwrap();
    }
    write!(
        io::stdout(),
        "{}",
        if s.ld_library_path_offset == usize::MAX {
            " 2. LD_LIBRARY_PATH was not set\n"
        } else {
            " 2. LD_LIBRARY_PATH:\n"
        }
    )
    .unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0m").unwrap();
    }
    
    if s.ld_library_path_offset != usize::MAX {
        let path_start = &s.string_table.arr.as_ref().unwrap()[s.ld_library_path_offset..];
        // Convert char array to string slice
        if let Some(null_pos) = path_start.iter().position(|&c| c == '\0') {
            let path_str = &path_start[..null_pos];
            let path_str: String = path_str.iter().collect();
            print_colon_delimited_paths(Some(&path_str), Some(&indent));
        }
    }
    
    write!(io::stdout(), "{}", indent).unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0;90m").unwrap();
    }
    write!(
        io::stdout(),
        "{}",
        if runpath.is_none() {
            " 3. runpath was not set\n"
        } else {
            " 3. runpath:\n"
        }
    )
    .unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0m").unwrap();
    }
    
    if let Some(runpath_str) = runpath {
        print_colon_delimited_paths(Some(runpath_str), Some(&indent));
    }
    
    write!(io::stdout(), "{}", indent).unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0;90m").unwrap();
    }
    write!(
        io::stdout(),
        "{}",
        if no_def_lib {
            " 4. ld config files not considered due to NODEFLIB flag\n"
        } else {
            " 4. ld config files:\n"
        }
    )
    .unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0m").unwrap();
    }
    
    let ld_so_conf_start = &s.string_table.arr.as_ref().unwrap()[s.ld_so_conf_offset..];
    if let Some(null_pos) = ld_so_conf_start.iter().position(|&c| c == '\0') {
        let ld_so_conf_str = &ld_so_conf_start[..null_pos];
        let ld_so_conf_str: String = ld_so_conf_str.iter().collect();
        print_colon_delimited_paths(Some(&ld_so_conf_str), Some(&indent));
    }
    
    write!(io::stdout(), "{}", indent).unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0;90m").unwrap();
    }
    write!(
        io::stdout(),
        "{}",
        if no_def_lib {
            " 5. Standard paths not considered due to NODEFLIB flag\n"
        } else {
            " 5. Standard paths:\n"
        }
    )
    .unwrap();
    if s.color != 0 {
        write!(io::stdout(), "\x1b[0m").unwrap();
    }
    
    let default_paths_start = &s.string_table.arr.as_ref().unwrap()[s.default_paths_offset..];
    if let Some(null_pos) = default_paths_start.iter().position(|&c| c == '\0') {
        let default_paths_str = &default_paths_start[..null_pos];
        let default_paths_str: String = default_paths_str.iter().collect();
        print_colon_delimited_paths(Some(&default_paths_str), Some(&indent));
    }
}
pub fn helper_recurse_2(
    curr_type_ref: &mut CompatT,
    compat: CompatT,
    fptr: &mut (impl Read + Seek),
    mut header: HeaderUnion,
) -> Result<(), i32> {
    let mut curr_type = curr_type_ref.clone();

    // Read header.h32 from file
    unsafe {
        fptr.read_exact(std::slice::from_raw_parts_mut(
            (&mut header.h32 as *mut std::mem::ManuallyDrop<Header32T>).cast::<u8>(),
            Header32T::size(),
        )).map_err(|_| 14)?;
    }

    // Check e_type
    if unsafe { header.h32.e_type } != 2 && unsafe { header.h32.e_type } != 3 {
        return Err(17);
    }

    curr_type.machine = unsafe { header.h32.e_machine };

    // Check machine compatibility
    if compat.any == '\0' && compat.machine != curr_type.machine {
        return Err(32);
    }

    // Seek to e_phoff position
    fptr.seek(SeekFrom::Start(unsafe { header.h32.e_phoff as u64 })).map_err(|_| 18)?;

    *curr_type_ref = curr_type;
    Ok(())
}
pub fn print_line(
    depth: usize,
    name: &str,
    color_bold: &str,
    color_regular: &str,
    highlight: bool,
    reason: FoundT,
    s: &mut LibtreeStateT,
) {
    tree_preamble(s, depth);
    
    let slash = if s.color != 0 && highlight {
        name.rfind('/')
    } else {
        Option::None
    };

    if let Some(slash_pos) = slash {
        let _ = io::stdout().write_all(color_regular.as_bytes());
        let _ = io::stdout().write_all(&name.as_bytes()[..=slash_pos]);
        let _ = io::stdout().write_all(color_bold.as_bytes());
        let _ = io::stdout().write_all(&name.as_bytes()[slash_pos + 1..]);
    } else {
        if s.color != 0 {
            let _ = io::stdout().write_all(color_bold.as_bytes());
        }
        let _ = io::stdout().write_all(name.as_bytes());
    }

    if s.color != 0 && highlight {
        let _ = io::stdout().write_all(b"\x1B[0m \x1B[33m");
    } else {
        let _ = io::stdout().write_all(b" ");
    }

    match reason.how {
        how_t::HowT::RPATH => {
            if (reason.depth + 1) >= depth {
                let _ = io::stdout().write_all(b"[rpath]");
            } else {
                let mut num = [0u8; 8];
                utoa(&mut num, reason.depth + 1);
                let _ = io::stdout().write_all(b"[rpath of ");
                let _ = io::stdout().write_all(&num);
                let _ = io::stdout().write_all(b"]");
            }
        }
        how_t::HowT::LD_LIBRARY_PATH => {
            let _ = io::stdout().write_all(b"[LD_LIBRARY_PATH]");
        }
        how_t::HowT::RUNPATH => {
            let _ = io::stdout().write_all(b"[runpath]");
        }
        how_t::HowT::LD_SO_CONF => {
            let _ = io::stdout().write_all(b"[");
            let conf_name = match s.ld_conf_file.as_ref() {
                Some(file) => match file.rfind('/') {
                    Some(pos) => &file[pos + 1..],
                    None => &file,
                },
                None => "",
            };
            let _ = io::stdout().write_all(conf_name.as_bytes());
            let _ = io::stdout().write_all(b"]");
        }
        how_t::HowT::DIRECT => {
            let _ = io::stdout().write_all(b"[direct]");
        }
        how_t::HowT::DEFAULT => {
            let _ = io::stdout().write_all(b"[default path]");
        }
        _ => {}
    }

    if s.color != 0 {
        let _ = io::stdout().write_all(b"\x1B[0m\n");
    } else {
        let _ = io::stdout().write_all(b"\n");
    }
}
pub fn helper_print_tree_1(
    exit_code_ref: &mut i32,
    pathv: &[&str],
    s: &mut LibtreeStateT,
    i: usize,
) {
    let mut exit_code = *exit_code_ref;
    let code = recurse(
        pathv[i],
        0,
        s,
        CompatT { any: 1 as char, class: 0, machine: 0 },
        FoundT { how: HowT::INPUT, depth: 0 },
    ).expect("recurse failed");
    
    io::stdout().flush().unwrap();
    
    if code != 0 {
        exit_code = code;
        let stderr = io::stderr();
        let mut stderr = stderr.lock();
        write!(stderr, "Error [{}]: ", pathv[i]).unwrap();
    }

    let msg = match code {
        11 => "Invalid ELF magic bytes\n",
        12 => "Invalid ELF class\n",
        13 => "Invalid ELF data\n",
        14 => "Invalid ELF header\n",
        15 => "Invalid bits\n",
        16 => "Invalid endianness\n",
        17 => "Not an ET_EXEC or ET_DYN ELF file\n",
        18 => "Invalid ELF program header offset\n",
        19 => "Invalid ELF program header\n",
        20 => "Can't stat file\n",
        21 => "Invalid ELF dynamic section\n",
        22 => "Invalid ELF dynamic array entry\n",
        23 => "No ELF string table found\n",
        24 => "Can't read DT_SONAME\n",
        25 => "Can't read DT_RPATH\n",
        26 => "Can't read DT_RUNPATH\n",
        27 => "Can't read DT_NEEDED\n",
        28 => "Not all dependencies were found\n",
        29 => "No PT_LOAD found in ELF file\n",
        30 => "Virtual addresses are not ordered\n",
        31 => "Could not open file\n",
        32 => "Incompatible ISA\n",
        _ => "",
    };

    if !msg.is_empty() {
        let stderr = io::stderr();
        let mut stderr = stderr.lock();
        stderr.write_all(msg.as_bytes()).unwrap();
    }
    
    io::stderr().flush().unwrap();
    *exit_code_ref = exit_code;
}
pub fn parse_ld_so_conf(s: &mut LibtreeStateT) {
    let st = &mut s.string_table;
    s.ld_so_conf_offset = st.n;
    
    if let Some(conf_file) = &s.ld_conf_file {
        parse_ld_config_file(st, conf_file);
    }
    
    if st.n > s.ld_so_conf_offset {
        if let Some(arr) = &mut st.arr {
            if !arr.is_empty() {
                arr[st.n - 1] = '\0';
            }
        }
    } else {
        string_table_store(st, "");
    }
}
pub fn print_tree(pathc: i32, pathv: &[&str], s: &mut LibtreeStateT) -> i32 {
    libtree_state_init(s);
    parse_ld_so_conf(s);
    parse_ld_library_path(s);
    set_default_paths(s);
    let mut exit_code = 0;
    
    for i in 0..pathc as usize {
        if i < pathv.len() {
            helper_print_tree_1(&mut exit_code, pathv, s, i);
        }
    }
    
    libtree_state_free(s);
    exit_code
}
