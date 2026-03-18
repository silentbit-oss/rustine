use std::fs::File;
use crate::*;
use std::env;
use std::io;
use std::process;
use std::ptr;
use lazy_static::lazy_static;
use std::alloc::Layout;
use std::alloc::handle_alloc_error;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
use std::os::linux::raw::stat;
use std::io::Read;
use std::io::Result as IoResult;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::os::raw::c_char;
use std::os::raw::c_longlong;
use std::os::raw::c_ulonglong;
use std::ffi::CStr;
use std::clone::Clone;
pub fn utoa(str: &mut [u8], mut v: usize) {
    if v == 0 {
        str[0] = b'0';
        if str.len() > 1 {
            str[1] = b'\0';
        }
        return;
    }

    let mut p_idx = 0;
    let p = str.as_mut_ptr();

    // Convert each digit to ASCII and store in reverse order
    unsafe {
        while v > 0 {
            *p.add(p_idx) = b'0' + (v % 10) as u8;
            p_idx += 1;
            v /= 10;
        }
    }

    let len = p_idx;
    
    // Reverse the string to get the correct order
    for i in 0..len / 2 {
        let tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }

    // Null-terminate the string if there's space
    if len < str.len() {
        str[len] = b'\0';
    }
}
pub fn host_is_little_endian() -> bool {
	println!("\n* host_is_little_endian");
    let test: i32 = 1;
    let bytes: &[u8] = unsafe { std::slice::from_raw_parts(&test as *const _ as *const u8, std::mem::size_of::<i32>()) };
    bytes[0] == 1
}
pub fn is_ascending_order(v: &[u64], n: usize) -> bool {
	println!("\n* is_ascending_order");
    for j in 1..n {
        if v[j - 1] >= v[j] {
            return false;
        }
    }
    true
}

pub fn print_colon_delimited_paths(start: Option<&str>, indent: Option<&str>) {
	println!("\n* print_colon_delimited_paths");
    // Handle NULL cases by providing defaults
    let start = match start {
        Some(s) => s,
        None => return,
    };
    let indent = match indent {
        Some(i) => i,
        None => "",
    };

    let mut start_idx = 0;
    let bytes = start.as_bytes();
    
    loop {
        if start_idx >= bytes.len() {
            break;
        }

        let remaining = &start[start_idx..];
        let next = remaining.find(':');

        if next == Some(0) {
            start_idx += 1;
            continue;
        }

        // Print indent and additional spacing
        print!("{}    ", indent);
        io::stdout().flush().unwrap();

        match next {
            None => {
                println!("{}", remaining);
                break;
            }
            Some(pos) => {
                let segment = &remaining[..pos];
                println!("{}", segment);
                start_idx += pos + 1;
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
	println!("\n* is_in_exclude_list");
    // Check for NULL input (None in Rust)
    let soname = match soname {
        Some(s) => s,
        None => return 0,
    };

    // Convert to bytes for easier manipulation
    let bytes = soname.as_bytes();
    let len = bytes.len();

    // Handle empty string case
    if len == 0 {
        return 0;
    }

    // Find the last non-digit/non-dot character from the end
    let mut end_idx = len - 1;
    loop {
        let current_char = bytes[end_idx];
        if !(current_char.is_ascii_digit() || current_char == b'.') {
            break;
        }
        if end_idx == 0 {
            break;
        }
        end_idx -= 1;
    }

    // Get the base name (without trailing numbers/dots)
    let base_name = &soname[..=end_idx];

    // Check against exclude list
    for excluded in EXCLUDE_LIST.iter() {
        if base_name == *excluded {
            return 1;
        }
    }

    0
}
pub fn small_vec_u64_init(v: &mut SmallVecU64T) {
	println!("\n* small_vec_u64_init");
    // Initialize all fields to default values
    v.buf = [0; 16];
    v.p = None;
    v.n = 0;
    v.capacity = 16;
}

pub fn small_vec_u64_append(v: &mut SmallVecU64T, val: u64) {
	println!("\n* small_vec_u64_append");
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
	println!("\n* small_vec_u64_free");
    if v.n <= 16 {
        return;
    }
    v.p = None; // Equivalent to free(v->p) and setting v->p = 0
}
pub fn string_table_maybe_grow(t: &mut StringTableT, n: usize) {
	println!("\n* string_table_maybe_grow");
    if (t.n + n) <= t.capacity {
        return;
    }
    
    t.capacity = 2 * (t.n + n);
    
    match &mut t.arr {
        Some(arr) => {
            let current_capacity = arr.capacity();
            if t.capacity > current_capacity {
                arr.reserve(t.capacity - current_capacity);
            }
        },
        None => {
            t.arr = Some(Vec::with_capacity(t.capacity));
        }
    }
}
pub fn tree_preamble(s: &mut LibtreeStateT, depth: usize) {
	println!("\n* tree_preamble");
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
	println!("\n* visited_files_append");
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
	println!("\n* libtree_state_init");
    s.string_table.n = 0;
    s.string_table.capacity = 1024;
    s.string_table.arr = Some(vec!['\0'; s.string_table.capacity]);
    
    s.visited.n = 0;
    s.visited.capacity = 256;
    s.visited.arr = Some(Vec::with_capacity(s.visited.capacity));
}
pub fn libtree_state_free(s: &mut LibtreeStateT) {
	println!("\n* libtree_state_free");
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
	println!("\n* string_table_store");
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
	println!("\n* string_table_copy_from_file");
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
	println!("\n* visited_files_contains");
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
    let n = val.chars().count();
    string_table_maybe_grow(&mut s.string_table, n);
    
    if let Some(arr) = &mut s.string_table.arr {
        arr.extend(val.chars());
    } else {
        let chars: Vec<char> = val.chars().collect();
        s.string_table.arr = Some(chars);
    }
    s.string_table.n += n;
    
    let search_start = s.ld_library_path_offset;
    let search_str = unsafe {
        std::slice::from_raw_parts_mut(
            s.string_table.arr.as_mut().expect("string_table.arr should be Some").as_mut_ptr().add(search_start),
            n
        )
    };
    
    let mut search_idx = 0;
    while let Some(pos) = search_str[search_idx..].iter().position(|&c| c == ';') {
        let absolute_pos = search_idx + pos;
        search_str[absolute_pos] = ':';
        search_idx = absolute_pos + 1;
    }
}
pub fn set_default_paths(s: &mut LibtreeStateT) {
	println!("\n* set_default_paths");
    s.default_paths_offset = s.string_table.n;
    string_table_store(&mut s.string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}
pub fn apply_exclude_list(needed_not_found: &mut usize, needed_buf_offsets: &mut SmallVecU64T, s: &LibtreeStateT) {
	println!("\n* apply_exclude_list");
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
	println!("\n* helper_recurse_1");
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
	println!("\n* h64_as_mut_bytes");
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
	println!("\n* helper_recurse_3");
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
	println!("\n* helper_interpolate_variables_1");
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
	println!("\n* interpolate_variables");
    let mut prev_src = src;
    let mut curr_src = src;
    
    // First, perform all the interpolation operations
    loop {
        let st_ptr = &mut s.string_table as *mut StringTableT;
        if helper_interpolate_variables_1(
            &mut prev_src,
            &mut curr_src,
            s,
            ORIGIN,
            unsafe { &mut *st_ptr },
        ).is_none() {
            break;
        }
    }

    // Then handle the string table manipulation
    if prev_src != src {
        let st = &mut s.string_table;
        let arr_slice = st.arr.as_ref().unwrap();
        let substr = &arr_slice[prev_src..];
        let n = substr.iter().position(|&c| c == '\0').unwrap_or(substr.len()) + 1;
        
        string_table_maybe_grow(st, n);
        
        if let Some(arr) = &mut st.arr {
            let dest_start = st.n;
            let src_start = prev_src;
            let (left, right) = arr.split_at_mut(dest_start);
            right[..n].copy_from_slice(&left[src_start..src_start + n]);
        }
        
        st.n += n;
        return 1;
    }
    
    0
}
pub fn helper_print_error_1(depth: usize, s: &LibtreeStateT, indent: &str) {
	println!("\n* helper_print_error_1");
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
	println!("\n* print_error");
    // First part: Print not found messages
    for i in 0..needed_not_found {
        s.found_all_needed[depth] = if (i + 1) >= needed_not_found { '1' } else { '0' };
        tree_preamble(s, depth + 1);
        
        if s.color != 0 {
            print!("\x1B[1;31m");
        }
        if let Some(arr) = &s.string_table.arr {
            let slice = &arr[needed_buf_offsets.p.as_ref().unwrap()[i] as usize..];
            let s: String = slice.iter().collect();
            print!("{}", s);
        }
        print!(" not found\n");
        if s.color != 0 {
            print!("\x1B[0m");
        }
    }

    // Prepare indent string
    let box_vertical = if s.color != 0 {
        "    \x1B[0;31m\u{e2}\u{94}\u{8a}\x1B[0m"
    } else {
        "    \u{e2}\u{94}\u{8a}"
    };

    let mut indent = String::new();
    for i in 0..depth {
        if s.found_all_needed[i] != '0' {
            indent.push_str("    ");
        } else {
            indent.push_str("\u{e2}\u{94}\u{82}   ");
        }
    }
    indent.push_str(box_vertical);

    // Print paths considered section
    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    print!(" Paths considered in this order:\n");
    if s.color != 0 {
        print!("\x1B[0m");
    }

    print!("{}", indent);
    match runpath {
        Some(_) => {
            if s.color != 0 {
                print!("\x1B[0;90m");
            }
            print!(" 1. rpath is skipped because runpath was set\n");
            if s.color != 0 {
                print!("\x1B[0m");
            }
        }
        None => {
            helper_print_error_1(depth, s, &indent);
        }
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    print!(
        "{}",
        if s.ld_library_path_offset == usize::MAX {
            " 2. LD_LIBRARY_PATH was not set\n"
        } else {
            " 2. LD_LIBRARY_PATH:\n"
        }
    );
    if s.color != 0 {
        print!("\x1B[0m");
    }
    if s.ld_library_path_offset != usize::MAX {
        if let Some(arr) = &s.string_table.arr {
            let slice = &arr[s.ld_library_path_offset..];
            let s: String = slice.iter().collect();
            print_colon_delimited_paths(Some(&s), Some(&indent));
        }
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    print!(
        "{}",
        if runpath.is_none() {
            " 3. runpath was not set\n"
        } else {
            " 3. runpath:\n"
        }
    );
    if s.color != 0 {
        print!("\x1B[0m");
    }
    if let Some(runpath) = runpath {
        print_colon_delimited_paths(Some(runpath), Some(&indent));
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    print!(
        "{}",
        if no_def_lib {
            " 4. ld config files not considered due to NODEFLIB flag\n"
        } else {
            " 4. ld config files:\n"
        }
    );
    if s.color != 0 {
        print!("\x1B[0m");
    }
    if let Some(arr) = &s.string_table.arr {
        let slice = &arr[s.ld_so_conf_offset..];
        let s: String = slice.iter().collect();
        print_colon_delimited_paths(Some(&s), Some(&indent));
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    print!(
        "{}",
        if no_def_lib {
            " 5. Standard paths not considered due to NODEFLIB flag\n"
        } else {
            " 5. Standard paths:\n"
        }
    );
    if s.color != 0 {
        print!("\x1B[0m");
    }
    if let Some(arr) = &s.string_table.arr {
        let slice = &arr[s.default_paths_offset..];
        let s: String = slice.iter().collect();
        print_colon_delimited_paths(Some(&s), Some(&indent));
    }
}
pub fn helper_recurse_2(
    curr_type_ref: &mut CompatT,
    compat: CompatT,
    fptr: &mut (impl Read + Seek),
    mut header: HeaderUnion,
) -> Result<(), i32> {
	println!("\n* helper_recurse_2");
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
	println!("\n* print_line");
    tree_preamble(s, depth);
    
    let stdout = io::stdout();
    let mut handle = stdout.lock();

    if s.color != 0 && highlight {
        if let Some(slash_pos) = name.rfind('/') {
            let (dir, file) = name.split_at(slash_pos + 1);
            write!(handle, "{}{}", color_regular, dir).unwrap();
            write!(handle, "{}{}", color_bold, file).unwrap();
        } else {
            write!(handle, "{}{}", color_bold, name).unwrap();
        }
    } else {
        if s.color != 0 {
            write!(handle, "{}", color_bold).unwrap();
        }
        write!(handle, "{}", name).unwrap();
    }

    if s.color != 0 && highlight {
        write!(handle, "\x1B[0m \x1B[33m").unwrap();
    } else {
        write!(handle, " ").unwrap();
    }

    match reason.how {
        HowT::RPATH => {
            if (reason.depth + 1) >= depth {
                write!(handle, "[rpath]").unwrap();
            } else {
                let mut num = [0u8; 8];
                utoa(&mut num, reason.depth + 1);
                write!(handle, "[rpath of {}]", std::str::from_utf8(&num).unwrap()).unwrap();
            }
        }
        HowT::LD_LIBRARY_PATH => {
            write!(handle, "[LD_LIBRARY_PATH]").unwrap();
        }
        HowT::RUNPATH => {
            write!(handle, "[runpath]").unwrap();
        }
        HowT::LD_SO_CONF => {
            let conf_name = match &s.ld_conf_file {
                Some(path) => {
                    if let Some(pos) = path.rfind('/') {
                        &path[pos + 1..]
                    } else {
                        path.as_str()
                    }
                }
                None => "",
            };
            write!(handle, "[{}]", conf_name).unwrap();
        }
        HowT::DIRECT => {
            write!(handle, "[direct]").unwrap();
        }
        HowT::DEFAULT => {
            write!(handle, "[default path]").unwrap();
        }
        _ => {}
    }

    if s.color != 0 {
        writeln!(handle, "\x1B[0m").unwrap();
    } else {
        writeln!(handle).unwrap();
    }
}
pub fn helper_print_tree_1(
    exit_code_ref: &mut i32,
    pathv: &[&str],
    s: &mut LibtreeStateT,
    i: usize,
) {
	println!("\n* helper_print_tree_1");
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
	println!("\n* parse_ld_so_conf");
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
pub fn print_tree(pathc: usize, pathv: &[&str], s: &mut LibtreeStateT) -> i32 {
	println!("\n* print_tree");
    libtree_state_init(s);
    parse_ld_so_conf(s);
    parse_ld_library_path(s);
    set_default_paths(s);
    
    let mut exit_code = 0;
    for i in 0..pathc {
        helper_print_tree_1(&mut exit_code, pathv, s, i);
    }
    
    libtree_state_free(s);
    exit_code
}
