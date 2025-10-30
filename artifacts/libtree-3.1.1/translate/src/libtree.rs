use libc::FILE;
use std::fs::File;
use crate::*;
use std::env;
use std::io;
use std::process;
use std::ptr;
use std::ffi::CStr;
use lazy_static::lazy_static;
use std::alloc::Layout;
use std::alloc::alloc;
use std::str::FromStr;
use std::io::Read;
use std::io::Result as IoResult;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
use std::os::raw::c_char;
use std::os::raw::c_longlong;
use std::os::raw::c_ulonglong;
use std::mem::ManuallyDrop;
pub fn utoa(str: &mut [u8], mut v: usize) {
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
    let str_slice = &mut str[..len];

    // Reverse the string to get correct order
    for i in 0..len / 2 {
        let tmp = str_slice[i];
        str_slice[i] = str_slice[len - i - 1];
        str_slice[len - i - 1] = tmp;
    }

    // Add null terminator if there's space
    if len < str.len() {
        str[len] = b'\0';
    }
}
pub fn host_is_little_endian() -> bool {
    let test = 1;
    let bytes = &test as *const _ as *const u8;
    unsafe { *bytes == 1 }
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
    // Convert Option<&str> to &str with default values if None
    let start = match start {
        Some(s) => s,
        None => return,
    };
    let indent = match indent {
        Some(s) => s,
        None => "",
    };

    let mut start_idx = 0;
    let bytes = start.as_bytes();
    
    loop {
        if start_idx >= bytes.len() {
            break;
        }

        let remaining = &bytes[start_idx..];
        let next = remaining.iter().position(|&b| b == b':');

        if let Some(relative_pos) = next {
            let absolute_pos = start_idx + relative_pos;
            if start_idx == absolute_pos {
                start_idx += 1;
                continue;
            }

            // Print indent and additional spaces
            io::stdout().write_all(indent.as_bytes()).unwrap();
            io::stdout().write_all(b"    ").unwrap();

            // Print the path segment
            let segment = &start[start_idx..absolute_pos];
            io::stdout().write_all(segment.as_bytes()).unwrap();
            io::stdout().write_all(b"\n").unwrap();

            start_idx = absolute_pos + 1;
        } else {
            // Print indent and additional spaces
            io::stdout().write_all(indent.as_bytes()).unwrap();
            io::stdout().write_all(b"    ").unwrap();

            // Print the remaining path
            let segment = &start[start_idx..];
            println!("{}", segment);
            break;
        }
    }
}
pub fn small_vec_u64_init(v: &mut SmallVecU64T) {
    *v = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 16,
    };
}

pub fn small_vec_u64_append(v: &mut SmallVecU64T, val: u64) {
    if v.n < 16 {
        v.buf[v.n] = val;
        v.n += 1;
        return;
    }

    if v.n == 16 {
        v.capacity = 2 * 16;
        let mut new_vec = Vec::with_capacity(v.capacity);
        new_vec.extend_from_slice(&v.buf);
        v.p = Some(new_vec.into_boxed_slice());
    } else if v.n == v.capacity {
        v.capacity *= 2;
        if let Some(boxed_slice) = &mut v.p {
            let mut vec = boxed_slice.to_vec();
            vec.reserve(v.capacity - vec.capacity());
            *boxed_slice = vec.into_boxed_slice();
        } else {
            process::exit(1);
        }
    }

    if let Some(boxed_slice) = &mut v.p {
        boxed_slice[v.n] = val;
    } else {
        process::exit(1);
    }
    v.n += 1;
}
pub fn small_vec_u64_free(v: &mut SmallVecU64T) {
    if v.n <= 16 {
        return;
    }
    v.p = None; // Equivalent to freeing the memory and setting pointer to 0
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
    
    if t.arr.is_none() {
        process::exit(1);
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

pub fn is_in_exclude_list(soname: &str) -> i32 {
    let start = soname;
    let end = start.rfind('\0').unwrap_or(start.len());
    
    if start.is_empty() || end == 0 {
        return 0;
    }

    let mut end_idx = end - 1;
    let bytes = start.as_bytes();
    
    while end_idx > 0 && (bytes[end_idx].is_ascii_digit() || bytes[end_idx] == b'.') {
        end_idx -= 1;
    }

    let prefix = &start[..=end_idx];
    
    for excluded in EXCLUDE_LIST.iter() {
        if prefix.starts_with(excluded) {
            return 1;
        }
    }

    0
}
pub fn tree_preamble(s: &LibtreeStateT, depth: usize) {
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
pub fn visited_files_append(files: &mut VisitedFileArrayT, new: &std::os::linux::raw::stat) {
    if files.n == files.capacity {
        files.capacity *= 2;
        match &mut files.arr {
            Some(arr) => {
                arr.reserve(files.capacity - arr.len());
            },
            None => {
                files.arr = Some(Vec::with_capacity(files.capacity));
            }
        }
        
        if files.arr.is_none() {
            process::exit(1);
        }
    }
    
    if let Some(arr) = &mut files.arr {
        arr.push(VisitedFileT {
            st_dev: new.st_dev,
            st_ino: new.st_ino,
        });
        files.n += 1;
    }
}
pub fn libtree_state_init(s: &mut LibtreeStateT) {
    // Initialize string_table
    s.string_table.n = 0;
    s.string_table.capacity = 1024;
    s.string_table.arr = Some(vec!['\0'; s.string_table.capacity]);

    // Initialize visited
    s.visited.n = 0;
    s.visited.capacity = 256;
    s.visited.arr = Some(vec![VisitedFileT {
        st_dev: 0,
        st_ino: 0,
    }; s.visited.capacity]);
}
pub fn libtree_state_free(s: &mut LibtreeStateT) {
    // In Rust, memory management is automatic for owned types like Vec and String.
    // The fields `string_table.arr` and `visited.arr` would typically be Vec or similar,
    // which automatically free their memory when dropped. However, if these fields
    // are raw pointers (which would require unsafe code to free), we assume they've been
    // properly wrapped in Rust types that handle their own memory.
    
    // Since the original C code frees these arrays, we'll clear them to release any resources.
    // This assumes `string_table.arr` and `visited.arr` are Option<Vec> collections.
    if let Some(arr) = &mut s.string_table.arr {
        arr.clear();
    }
    if let Some(arr) = &mut s.visited.arr {
        arr.clear();
    }
    
    // If these fields were actually raw pointers (unlikely in idiomatic Rust), we'd need:
    // unsafe {
    //     libc::free(s.string_table.arr as *mut libc::c_void);
    //     libc::free(s.visited.arr as *mut libc::c_void);
    // }
    // But we avoid unsafe and assume proper Rust types are used.
}

pub fn helper_helper_main_2_1(
    s_ref: &mut LibtreeStateT,
    opt_help_ref: &mut i32,
    arg: &str,
    arg_idx: usize,
) -> io::Result<()> {
    let mut s = s_ref.clone();
    let mut opt_help = *opt_help_ref;

    match arg.chars().nth(arg_idx) {
        Some('h') => {
            opt_help = 1;
        }
        Some('p') => {
            s.path = 1;
        }
        Some('v') => {
            s.verbosity += 1;
        }
        _ => {
            let stderr = io::stderr();
            let mut handle = stderr.lock();
            handle.write_all(b"Unrecognized flag `-")?;
            handle.write_all(arg.as_bytes())?;
            handle.write_all(b"`\n")?;
            return Err(io::Error::new(
                io::ErrorKind::InvalidInput,
                "Unrecognized flag",
            ));
        }
    }

    *s_ref = s;
    *opt_help_ref = opt_help;
    Ok(())
}

pub fn helper_helper_main_2_2(
    s_ref: &mut LibtreeStateT,
    opt_help_ref: &mut i32,
    opt_version_ref: &mut i32,
    opt_raw_ref: &mut i32,
    i_ref: &mut i32,
    arg_idx_ref: &mut u32,
    argc: i32,
    argv: &[*const c_char],
    argv_idx: u32,
    arg: &CStr,
) -> Result<(), i32> {
    let mut s = s_ref.clone();
    let mut opt_help = *opt_help_ref;
    let mut opt_version = *opt_version_ref;
    let mut opt_raw = *opt_raw_ref;
    let mut i = *i_ref;
    let mut arg_idx = *arg_idx_ref;

    arg_idx += 1;
    let arg_bytes = arg.to_bytes();
    if arg_idx as usize >= arg_bytes.len() {
        opt_raw = 1;
    } else {
        let arg_str = arg.to_str().map_err(|_| {
            eprintln!("Invalid UTF-8 in argument");
            1
        })?;

        match arg_str {
            "version" => opt_version = 1,
            "path" => s.path = 1,
            "verbose" => s.verbosity += 1,
            "help" => opt_help = 1,
            "ldconf" => {
                if (i + 1) == argc {
                    eprintln!("Expected value after `--ldconf`");
                    return Err(1);
                }
                i += 1;
                unsafe {
                    s.ld_conf_file = Some(
                        CStr::from_ptr(argv[(i + argv_idx as i32) as usize])
                            .to_string_lossy()
                            .into_owned(),
                    );
                }
            }
            "max-depth" => {
                if (i + 1) == argc {
                    eprintln!("Expected value after `--max-depth`");
                    return Err(1);
                }
                i += 1;
                unsafe {
                    let depth_str = CStr::from_ptr(argv[(i + argv_idx as i32) as usize])
                        .to_string_lossy();
                    s.max_depth = u64::from_str(&depth_str).unwrap_or(0);
                }
                if s.max_depth > 32 {
                    s.max_depth = 32;
                }
            }
            _ => {
                eprint!("Unrecognized flag `--");
                eprint!("{}", arg_str);
                eprintln!("`");
                return Err(1);
            }
        }
    }

    *s_ref = s;
    *opt_help_ref = opt_help;
    *opt_version_ref = opt_version;
    *opt_raw_ref = opt_raw;
    *i_ref = i;
    *arg_idx_ref = arg_idx;

    Ok(())
}
pub fn string_table_store(t: &mut StringTableT, str: &str) {
    let n = str.len() + 1; // +1 for null terminator equivalent
    string_table_maybe_grow(t, n);
    
    // Convert the string to bytes and copy into the array
    if let Some(arr) = &mut t.arr {
        // Extend the vector with the string bytes plus null terminator
        let bytes = str.as_bytes();
        arr.extend(bytes.iter().map(|&b| b as char));
        arr.push('\0'); // Add null terminator equivalent
        
        t.n += n;
    }
}

pub fn string_table_copy_from_file(t: &mut StringTableT, fptr: &mut impl Read) {
    let mut buf = [0u8; 1];
    
    loop {
        match fptr.read(&mut buf) {
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
            },
            Ok(_) => break, // EOF or other read issues
            Err(_) => break, // Error handling
        }
    }

    string_table_maybe_grow(t, 1);
    if let Some(ref mut arr) = t.arr {
        arr.push('\0');
        t.n += 1;
    }
}

pub fn visited_files_contains(files: &VisitedFileArrayT, needle: &libc::stat) -> bool {
    if let Some(arr) = &files.arr {
        for i in 0..files.n {
            let f = &arr[i];
            if (f.st_dev == needle.st_dev) && (f.st_ino == needle.st_ino) {
                return true;
            }
        }
    }
    false
}
pub fn parse_ld_library_path(s: &mut LibtreeStateT) {
    s.ld_library_path_offset = usize::MAX;
    
    // Use std::env::var_os to safely get environment variable
    let val = std::env::var_os("LD_LIBRARY_PATH");
    if val.is_none() {
        return;
    }
    
    // Store the OsString in a binding to extend its lifetime
    let os_str = val.unwrap();
    // Convert to &str safely
    let val = os_str.to_str().unwrap();
    
    s.ld_library_path_offset = s.string_table.n;
    string_table_store(&mut s.string_table, val);
    
    // Get mutable reference to the string table array
    if let Some(string_table_arr) = &mut s.string_table.arr {
        let search_start = s.ld_library_path_offset;
        let search_end = string_table_arr.len();
        
        // Ensure we don't go out of bounds
        if search_start >= search_end {
            return;
        }
        
        // Work with the slice of the string table
        let search_slice = &mut string_table_arr[search_start..search_end];
        
        // Iterate through the string replacing ';' with ':'
        for c in search_slice.iter_mut() {
            if *c == ';' {
                *c = ':';
            }
        }
    }
}
pub fn set_default_paths(s: &mut LibtreeStateT) {
    s.default_paths_offset = s.string_table.n;
    string_table_store(&mut s.string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}
pub fn helper_recurse_3(
    no_def_lib_ref: &mut i32,
    strtab_ref: &mut u64,
    rpath_ref: &mut u64,
    runpath_ref: &mut u64,
    soname_ref: &mut u64,
    cont_ref: &mut i32,
    fptr: &mut impl Read,
    curr_type: CompatT,
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
    let d_tag: u64;
    let d_val: u64;

    if curr_type.class == 2 {
        let mut dyn64 = Dyn64T {
            d_tag: 0,
            d_val: 0,
        };
        fptr.read_exact(unsafe {
            std::slice::from_raw_parts_mut(
                &mut dyn64 as *mut _ as *mut u8,
                std::mem::size_of::<Dyn64T>(),
            )
        })?;
        d_tag = dyn64.d_tag as u64;
        d_val = dyn64.d_val as u64;
    } else {
        let mut dyn32 = Dyn32T {
            d_tag: 0,
            d_val: 0,
        };
        fptr.read_exact(unsafe {
            std::slice::from_raw_parts_mut(
                &mut dyn32 as *mut _ as *mut u8,
                std::mem::size_of::<Dyn32T>(),
            )
        })?;
        d_tag = dyn32.d_tag as u32 as u64;
        d_val = dyn32.d_val as u64;
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

#[derive(Clone)]
struct Dyn32T {
    d_tag: i32,
    d_val: u32,
}
pub fn helper_interpolate_variables_1(
    prev_src_ref: &mut usize,
    curr_src_ref: &mut usize,
    s: &mut LibtreeStateT,
    ORIGIN: &str,
    st: &mut StringTableT,
) {
    let mut prev_src = *prev_src_ref;
    let mut curr_src = *curr_src_ref;

    // Find '$' character
    let arr = st.arr.as_ref().unwrap();
    let dollar_pos = arr[curr_src..].iter().position(|&c| c == '$');
    if dollar_pos.is_none() {
        return;
    }
    let dollar_pos = curr_src + dollar_pos.unwrap();

    curr_src = dollar_pos;
    let bytes_to_dollar = curr_src - prev_src;
    curr_src += 1;

    let mut curly = false;
    if arr[curr_src] == '{' {
        curly = true;
        curr_src += 1;
    }

    let var_val = if curr_src + 6 <= arr.len() && &arr[curr_src..curr_src+6].iter().collect::<String>() == "ORIGIN" {
        curr_src += 6;
        ORIGIN
    } else if curr_src + 3 <= arr.len() && &arr[curr_src..curr_src+3].iter().collect::<String>() == "LIB" {
        curr_src += 3;
        s.LIB.as_deref().unwrap_or("")
    } else if curr_src + 8 <= arr.len() && &arr[curr_src..curr_src+8].iter().collect::<String>() == "PLATFORM" {
        curr_src += 8;
        s.PLATFORM.as_deref().unwrap_or("")
    } else if curr_src + 6 <= arr.len() && &arr[curr_src..curr_src+6].iter().collect::<String>() == "OSNAME" {
        curr_src += 6;
        s.OSNAME.as_deref().unwrap_or("")
    } else if curr_src + 5 <= arr.len() && &arr[curr_src..curr_src+5].iter().collect::<String>() == "OSREL" {
        curr_src += 5;
        s.OSREL.as_deref().unwrap_or("")
    } else {
        return;
    };

    if curly {
        if arr[curr_src] != '}' {
            return;
        }
        curr_src += 1;
    }

    let var_len = var_val.len();
    string_table_maybe_grow(st, bytes_to_dollar + var_len);

    let arr = st.arr.as_mut().unwrap();
    let (dest, src) = arr.split_at_mut(s.string_table.n);
    dest[s.string_table.n..s.string_table.n + bytes_to_dollar]
        .copy_from_slice(&src[prev_src..prev_src + bytes_to_dollar]);
    s.string_table.n += bytes_to_dollar;

    prev_src = curr_src;

    let var_val_chars: Vec<char> = var_val.chars().collect();
    arr[s.string_table.n..s.string_table.n + var_len]
        .copy_from_slice(&var_val_chars[..var_len]);
    s.string_table.n += var_len;

    *prev_src_ref = prev_src;
    *curr_src_ref = curr_src;
}
pub fn interpolate_variables(s: &mut LibtreeStateT, src: usize, ORIGIN: &str) -> i32 {
    let mut prev_src = src;
    let mut curr_src = src;
    
    loop {
        let prev_src_before = prev_src;
        let curr_src_before = curr_src;
        let st_ptr = &mut s.string_table as *mut StringTableT;
        helper_interpolate_variables_1(
            &mut prev_src, 
            &mut curr_src, 
            s, 
            ORIGIN, 
            unsafe { &mut *st_ptr }
        );
        
        if prev_src == curr_src {
            break;
        }
    }

    if prev_src != src {
        let st = &mut s.string_table;
        let arr_slice = st.arr.as_ref().unwrap();
        let string_start = &arr_slice[prev_src..];
        let len = string_start.iter().position(|&c| c == '\0').unwrap_or(string_start.len());
        let n = len + 1;
        
        string_table_maybe_grow(st, n);
        
        if let Some(arr) = &mut st.arr {
            let dest_start = st.n;
            let (left, right) = arr.split_at_mut(dest_start);
            let src_slice = &left[prev_src..prev_src + n];
            right[..n].copy_from_slice(src_slice);
        }
        
        st.n += n;
        return 1;
    }
    0
}
pub fn helper_recurse_2(
    curr_type_ref: &mut CompatT,
    compat: CompatT,
    fptr: &mut File,
    mut header: HeaderUnion,
) -> Result<(), i32> {
    let mut curr_type = curr_type_ref.clone();

    // Read header.h32 from file
    if fptr.read_exact(unsafe { &mut *(&mut *header.h32 as *mut Header32T as *mut u8 as *mut [u8; std::mem::size_of::<Header32T>()]) }).is_err() {
        fptr.seek(SeekFrom::Start(0)).ok(); // Reset position before closing
        return Err(14);
    }

    // Check e_type
    if unsafe { header.h32.e_type } != 2 && unsafe { header.h32.e_type } != 3 {
        fptr.seek(SeekFrom::Start(0)).ok(); // Reset position before closing
        return Err(17);
    }

    curr_type.machine = unsafe { header.h32.e_machine };

    // Check machine compatibility
    if compat.any == '\0' && compat.machine != curr_type.machine {
        fptr.seek(SeekFrom::Start(0)).ok(); // Reset position before closing
        return Err(32);
    }

    // Seek to e_phoff
    if fptr.seek(SeekFrom::Start(unsafe { header.h32.e_phoff as u64 })).is_err() {
        fptr.seek(SeekFrom::Start(0)).ok(); // Reset position before closing
        return Err(18);
    }

    *curr_type_ref = curr_type;
    Ok(())
}

// Helper trait to convert struct to mutable bytes
trait AsMutBytes {
    fn as_mut_bytes(&mut self) -> &mut [u8];
}

impl AsMutBytes for Header32T {
    fn as_mut_bytes(&mut self) -> &mut [u8] {
        unsafe {
            std::slice::from_raw_parts_mut(
                self as *mut _ as *mut u8,
                std::mem::size_of::<Header32T>(),
            )
        }
    }
}

// Union equivalent in Rust
pub union HeaderUnion {
    pub h64: std::mem::ManuallyDrop<Header64T>,
    pub h32: std::mem::ManuallyDrop<Header32T>,
}
pub fn print_line(
    depth: usize,
    name: &str,
    color_bold: &str,
    color_regular: &str,
    highlight: bool,
    reason: FoundT,
    s: &LibtreeStateT,
) {
    tree_preamble(s, depth);
    
    if s.color != 0 && highlight {
        if let Some(slash_idx) = name.rfind('/') {
            let (prefix, suffix) = name.split_at(slash_idx + 1);
            io::stdout()
                .write_all(color_regular.as_bytes())
                .unwrap();
            io::stdout().write_all(prefix.as_bytes()).unwrap();
            io::stdout()
                .write_all(color_bold.as_bytes())
                .unwrap();
            io::stdout().write_all(suffix.as_bytes()).unwrap();
        } else {
            if s.color != 0 {
                io::stdout()
                    .write_all(color_bold.as_bytes())
                    .unwrap();
            }
            io::stdout().write_all(name.as_bytes()).unwrap();
        }
    } else {
        if s.color != 0 {
            io::stdout()
                .write_all(color_bold.as_bytes())
                .unwrap();
        }
        io::stdout().write_all(name.as_bytes()).unwrap();
    }

    if s.color != 0 && highlight {
        io::stdout().write_all(b"\x1B[0m \x1B[33m").unwrap();
    } else {
        print!(" ");
    }

    match reason.how {
        HowT::RPATH => {
            if (reason.depth + 1) >= depth {
                print!("[rpath]");
            } else {
                let mut num = [0u8; 8];
                utoa(&mut num, reason.depth + 1);
                print!("[rpath of {}]", std::str::from_utf8(&num).unwrap());
            }
        }
        HowT::LD_LIBRARY_PATH => print!("[LD_LIBRARY_PATH]"),
        HowT::RUNPATH => print!("[runpath]"),
        HowT::LD_SO_CONF => {
            print!("[");
            let conf_name = s.ld_conf_file.as_ref().and_then(|f| f.rfind('/').map(|i| &f[i+1..]));
            if let Some(name) = conf_name {
                print!("{}", name);
            }
            print!("]");
        }
        HowT::DIRECT => print!("[direct]"),
        HowT::DEFAULT => print!("[default path]"),
        _ => {}
    }

    if s.color != 0 {
        io::stdout().write_all(b"\x1B[0m\n").unwrap();
    } else {
        println!();
    }
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
            write!(io::stdout(), "{}", std::str::from_utf8(&num).unwrap()).unwrap();
            if s.color != 0 {
                write!(io::stdout(), "\x1B[0m").unwrap();
            }
            writeln!(io::stdout()).unwrap();

            let path = if let Some(arr) = &s.string_table.arr {
                if s.rpath_offsets[j] < arr.len() {
                    let char_slice = &arr[s.rpath_offsets[j]..];
                    let null_pos = char_slice.iter().position(|&c| c == '\0').unwrap_or(char_slice.len());
                    let valid_slice = &char_slice[..null_pos];
                    if valid_slice.is_empty() {
                        Option::None
                    } else {
                        // Convert the valid slice directly to a string
                        Some(valid_slice.iter().collect::<String>())
                    }
                } else {
                    Option::None
                }
            } else {
                Option::None
            };
            print_colon_delimited_paths(path.as_deref(), Some(indent));
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
        s.found_all_needed[depth] = if (i + 1) >= needed_not_found { '1' } else { '0' };
        tree_preamble(s, depth + 1);
        
        if s.color != 0 {
            print!("\x1B[1;31m");
        }
        if let Some(arr) = &s.string_table.arr {
            let chars = &arr[needed_buf_offsets.p.as_ref().unwrap()[i] as usize..];
            let s: String = chars.iter().collect();
            print!("{}", s);
        }
        println!(" not found");
        if s.color != 0 {
            print!("\x1B[0m");
        }
    }

    let box_vertical = if s.color != 0 {
        "    \x1B[0;31m│\x1B[0m"
    } else {
        "    │"
    };

    let mut indent = String::new();
    for i in 0..depth {
        if s.found_all_needed[i] != '0' {
            indent.push_str("    ");
        } else {
            indent.push_str("│   ");
        }
    }
    indent.push_str(box_vertical);

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    println!(" Paths considered in this order:");
    if s.color != 0 {
        print!("\x1B[0m");
    }

    print!("{}", indent);
    if runpath.is_some() {
        if s.color != 0 {
            print!("\x1B[0;90m");
        }
        println!(" 1. rpath is skipped because runpath was set");
        if s.color != 0 {
            print!("\x1B[0m");
        }
    } else {
        helper_print_error_1(depth, s, &indent);
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    println!(
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
            let chars = &arr[s.ld_library_path_offset..];
            let s: String = chars.iter().collect();
            print_colon_delimited_paths(
                Some(&s),
                Some(&indent),
            );
        }
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    println!(
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
    println!(
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
        let chars = &arr[s.ld_so_conf_offset..];
        let s: String = chars.iter().collect();
        print_colon_delimited_paths(
            Some(&s),
            Some(&indent),
        );
    }

    print!("{}", indent);
    if s.color != 0 {
        print!("\x1B[0;90m");
    }
    println!(
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
        let chars = &arr[s.default_paths_offset..];
        let s: String = chars.iter().collect();
        print_colon_delimited_paths(
            Some(&s),
            Some(&indent),
        );
    }
}
pub fn apply_exclude_list(
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    s: &LibtreeStateT,
) {
    let mut i = 0;
    while i < *needed_not_found {
        let offset = needed_buf_offsets.p.as_ref().unwrap()[i];
        let c_str_ptr = s.string_table.arr.as_ref().unwrap().as_ptr().wrapping_add(offset as usize);
        let c_str = unsafe { CStr::from_ptr(c_str_ptr as *const u8) };
        let str_slice = c_str.to_str().unwrap();
        
        if is_in_exclude_list(str_slice) != 0 {
            let tmp = needed_buf_offsets.p.as_ref().unwrap()[i];
            let last = *needed_not_found - 1;
            needed_buf_offsets.p.as_mut().unwrap()[i] = needed_buf_offsets.p.as_ref().unwrap()[last];
            needed_buf_offsets.p.as_mut().unwrap()[last] = tmp;
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

    // Read header.h64 from file
    unsafe {
        let bytes = std::slice::from_raw_parts_mut(&mut header.h64 as *mut _ as *mut u8, Header64T::size());
        fptr.read_exact(bytes).map_err(|_| 14)?;
    }

    // Check e_type
    if unsafe { header.h64.e_type } != 2 && unsafe { header.h64.e_type } != 3 {
        fptr.flush().ok();
        return Err(17);
    }

    curr_type.machine = unsafe { header.h64.e_machine };

    // Check machine compatibility
    if compat.any == '\0' && compat.machine != curr_type.machine {
        fptr.flush().ok();
        return Err(32);
    }

    // Seek to e_phoff
    fptr.seek(SeekFrom::Start(unsafe { header.h64.e_phoff })).map_err(|_| 18)?;

    *curr_type_ref = curr_type;
    Ok(())
}

impl HeaderUnion {
    // Helper method to get mutable bytes for h64
    pub unsafe fn as_mut_bytes(&mut self) -> &mut [u8] {
        std::slice::from_raw_parts_mut(&mut self.h64 as *mut _ as *mut u8, Header64T::size())
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
        CompatT {
            any: 1 as char,
            class: 0,
            machine: 0,
        },
        FoundT {
            how: HowT::INPUT,
            depth: 0,
        },
    );

    io::stdout().flush().unwrap(); // Equivalent to fflush(stdout)

    if code != 0 {
        exit_code = code;
        let stderr = io::stderr();
        let mut stderr_lock = stderr.lock();
        write!(stderr_lock, "Error [{}]: ", pathv[i]).unwrap();
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
        let mut stderr_lock = stderr.lock();
        stderr_lock.write_all(msg.as_bytes()).unwrap();
    }

    io::stderr().flush().unwrap(); // Equivalent to fflush(stderr)
    *exit_code_ref = exit_code;
}

pub fn helper_main_1(s: LibtreeStateT, opt_help: i32) -> i32 {
    let stdout = io::stdout();
    let mut handle = stdout.lock();

    handle.write_all(b"Show the dynamic dependency tree of ELF files\nUsage: libtree [OPTION]... [--] FILE [FILES]...\n\n  -h, --help     Print help info\n      --version  Print version info\n\nFile names starting with '-', for example '-.so', can be specified as follows:\n  libtree -- -.so\n\nLocating libs options:\n  -p, --path       Show the path of libraries instead of the soname\n  -v               Show libraries skipped by default*\n  -vv              Show dependencies of libraries skipped by default*\n  -vvv             Show dependencies of already encountered libraries\n  --ldconf <path>  Config file for extra search paths [").unwrap();
    
    if let Some(ld_conf_file) = &s.ld_conf_file {
        handle.write_all(ld_conf_file.as_bytes()).unwrap();
    }
    
    handle.write_all(b"]\n  --max-depth <n>  Limit library traversal to at most n levels of depth\n\n* For brevity, the following libraries are not shown by default:\n  ").unwrap();
    
    let num_excluded = EXCLUDE_LIST.len();
    let mut cursor_x = 3;
    
    for (j, lib) in EXCLUDE_LIST.iter().enumerate() {
        cursor_x += lib.len();
        if cursor_x > 60 {
            cursor_x = 3;
            handle.write_all(b"\n  ").unwrap();
        }
        handle.write_all(lib.as_bytes()).unwrap();
        if j + 1 != num_excluded {
            handle.write_all(b", ").unwrap();
        }
    }
    
    handle.write_all(b".\n\nThe following rpath/runpath substitutions are used:\n  PLATFORM       ").unwrap();
    if let Some(platform) = &s.PLATFORM {
        handle.write_all(platform.as_bytes()).unwrap();
    }
    
    handle.write_all(b"\n  LIB            ").unwrap();
    if let Some(lib) = &s.LIB {
        handle.write_all(lib.as_bytes()).unwrap();
    }
    
    handle.write_all(b"\n  OSNAME         ").unwrap();
    if let Some(osname) = &s.OSNAME {
        handle.write_all(osname.as_bytes()).unwrap();
    }
    
    handle.write_all(b"\n  OSREL          ").unwrap();
    if let Some(osrel) = &s.OSREL {
        handle.write_all(osrel.as_bytes()).unwrap();
    }
    
    handle.write_all(b"\n").unwrap();
    
    !opt_help
}
pub fn helper_main_2(
    argv_idx_ref: &mut u32,
    s_ref: &mut LibtreeStateT,
    positional_ref: &mut i32,
    opt_help_ref: &mut i32,
    opt_version_ref: &mut i32,
    opt_raw_ref: &mut i32,
    i_ref: &mut i32,
    argc: i32,
    argv: &[*const c_char],
) {
    let argv_idx = *argv_idx_ref;
    let mut s = s_ref.clone();
    let mut positional = *positional_ref;
    let mut opt_help = *opt_help_ref;
    let mut opt_version = *opt_version_ref;
    let mut opt_raw = *opt_raw_ref;
    let mut i = *i_ref;

    let arg = unsafe { CStr::from_ptr(argv[(i as usize + argv_idx as usize)]) };
    let arg_bytes = arg.to_bytes();
    let mut arg_idx = 0;

    if opt_raw != 0 || arg_bytes[arg_idx as usize] != b'-' || arg_bytes.get((1 + arg_idx as usize)).map_or(true, |&c| c == 0) {
        positional += 1;
    } else {
        arg_idx += 1;
        if arg_bytes[arg_idx as usize] == b'-' {
            helper_helper_main_2_2(
                &mut s,
                &mut opt_help,
                &mut opt_version,
                &mut opt_raw,
                &mut i,
                &mut arg_idx,
                argc,
                argv,
                argv_idx,
                arg,
            ).unwrap();
        }

        while (arg_idx as usize) < arg_bytes.len() && arg_bytes[arg_idx as usize] != 0 {
            let arg_str = arg.to_str().unwrap_or_default();
            helper_helper_main_2_1(&mut s, &mut opt_help, arg_str, arg_idx as usize);
            arg_idx += 1;
        }
    }

    *argv_idx_ref = argv_idx;
    *s_ref = s;
    *positional_ref = positional;
    *opt_help_ref = opt_help;
    *opt_version_ref = opt_version;
    *opt_raw_ref = opt_raw;
    *i_ref = i;
}
pub fn parse_ld_so_conf(s: &mut LibtreeStateT) {
    let st = &mut s.string_table;
    s.ld_so_conf_offset = st.n;
    
    if let Some(ld_conf_file) = &s.ld_conf_file {
        // Parse the config file if it exists
        if let Err(e) = parse_ld_config_file(st, ld_conf_file) {
            eprintln!("Error parsing ld config file: {}", e);
        }
    }

    if st.n > s.ld_so_conf_offset {
        // If we added any characters, ensure null termination
        if let Some(arr) = &mut st.arr {
            if !arr.is_empty() {
                arr[st.n - 1] = '\0';
            }
        }
    } else {
        // Otherwise store an empty string
        string_table_store(st, "");
    }
}
pub fn print_tree(pathc: usize, pathv: &[&str], s: &mut LibtreeStateT) -> i32 {
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
