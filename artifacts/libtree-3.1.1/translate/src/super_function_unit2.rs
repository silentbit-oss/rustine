use crate::*;
use crate::HowT;
use std::ptr::copy_nonoverlapping;
use std::ffi::CStr;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::io::stdout;
use std::fs::File;
use std::path::Path;
use std::os::linux::fs::MetadataExt;
use std::ptr;
use std::mem::ManuallyDrop;
use std::os::raw;
use std::os::linux::raw::stat;

#[repr(C)]
union ProgUnion {
    p64: ManuallyDrop<Prog64T>,
    p32: ManuallyDrop<Prog32T>,
}

pub fn helper_helper_check_search_paths_1_1(
    depth_ref: &mut usize,
    exit_code_ref: &mut i32,
    i_ref: &mut usize,
    reason: FoundT,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    s: &mut LibtreeStateT,
    compat: CompatT,
    path: &mut [u8; 4096],
    path_end: *const u8,
    st: &StringTableT,
    search_path_end: &mut u8,
) {
    let depth = *depth_ref;
    let mut exit_code = *exit_code_ref;
    let mut i = *i_ref;

    // Get soname length (equivalent to strlen)
    let soname_slice = st.arr.as_ref().unwrap();
    let soname_start = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
    let soname_cstr = unsafe { 
        let ptr = soname_slice.as_ptr() as *const u8;
        CStr::from_ptr(ptr.add(soname_start)) 
    };
    let soname_len = soname_cstr.to_bytes().len();

    // Check buffer bounds
    let search_path_end_ptr = search_path_end as *mut u8;
    let path_end_ptr = path_end as *const u8;
    if (search_path_end_ptr as usize + soname_len + 1) >= path_end_ptr as usize {
        return; // Rust doesn't have 'continue' outside loops
    }

    // Copy soname (equivalent to memcpy)
    unsafe {
        ptr::copy_nonoverlapping(
            soname_slice.as_ptr() as *const u8,
            search_path_end_ptr,
            soname_len + 1,
        );
    }

    s.found_all_needed[depth] = if *needed_not_found <= 1 { '1' } else { '0' };

    let code = recurse(unsafe { CStr::from_ptr(path.as_ptr()).to_str().unwrap() }, depth + 1, s, compat, reason);

    if code == 28 {
        exit_code = 28;
    }

    if code == 0 || code == 28 {
        let tmp = needed_buf_offsets.p.as_mut().unwrap()[i];
        needed_buf_offsets.p.as_mut().unwrap()[i] = needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found - 1];
        *needed_not_found -= 1;
        needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found] = tmp;
    } else {
        i += 1;
    }

    *depth_ref = depth;
    *exit_code_ref = exit_code;
    *i_ref = i;
}

pub fn helper_check_search_paths_1(
    offset_ref: &mut usize,
    depth_ref: &mut usize,
    exit_code_ref: &mut i32,
    reason: FoundT,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    s: &mut LibtreeStateT,
    compat: CompatT,
    path: &mut [u8; 4096],
    path_end: *const u8,
    st: &StringTableT,
) -> i32 {
    let mut offset = *offset_ref;
    let mut depth = *depth_ref;
    let mut exit_code = *exit_code_ref;

    // Skip colons
    while st.arr.as_ref().map_or(false, |arr| offset < arr.len() && arr[offset] == ':') {
        offset += 1;
    }

    // Check for end of string
    if st.arr.as_ref().map_or(true, |arr| offset >= arr.len() || arr[offset] == '\0') {
        return exit_code;
    }

    let dest = path.as_mut_ptr();
    let mut dest_idx = 0;

    // Copy path segment
    while st.arr.as_ref().map_or(false, |arr| 
        offset < arr.len() && 
        arr[offset] != '\0' && 
        arr[offset] != ':' &&
        dest_idx < 4096
    ) {
        unsafe {
            *dest.add(dest_idx) = st.arr.as_ref().unwrap()[offset] as u8;
        }
        offset += 1;
        dest_idx += 1;
    }

    // Check path bounds
    if dest_idx >= 4096 - 1 {
        *offset_ref = offset;
        *depth_ref = depth;
        *exit_code_ref = exit_code;
        return exit_code;
    }

    // Add trailing slash if needed
    if dest_idx > 0 && unsafe { *dest.add(dest_idx - 1) } != b'/' {
        unsafe {
            *dest.add(dest_idx) = b'/';
        }
        dest_idx += 1;
    }

    let search_path_end = unsafe { dest.add(dest_idx) };

    // Process needed items
    let mut i = 0;
    while i < *needed_not_found {
        let st_ptr = &s.string_table as *const StringTableT;
        helper_helper_check_search_paths_1_1(
            &mut depth,
            &mut exit_code,
            &mut i,
            reason.clone(),
            needed_not_found,
            needed_buf_offsets,
            s,
            compat.clone(),
            path,
            path_end,
            unsafe { &*st_ptr },
            unsafe { &mut *search_path_end },
        );
    }

    *offset_ref = offset;
    *depth_ref = depth;
    *exit_code_ref = exit_code;
    exit_code
}

pub fn check_absolute_paths(
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    depth: &mut usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
) -> i32 {
    let mut exit_code = 0;
    let mut i = 0;
    
    while i < *needed_not_found {
        helper_check_absolute_paths_1(
            depth,
            &mut exit_code,
            &mut i,
            needed_not_found,
            needed_buf_offsets,
            s,
            compat.clone(),
        );
    }

    exit_code
}

pub fn helper_check_absolute_paths_1(
    depth_ref: &mut usize,
    exit_code_ref: &mut i32,
    i_ref: &mut usize,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    s: &mut LibtreeStateT,
    compat: CompatT,
) {
    let depth = *depth_ref;
    let mut exit_code = *exit_code_ref;
    let mut i = *i_ref;
    let st = &s.string_table;

    // Check if path contains '/'
    if let Some(arr) = &st.arr {
        let offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
        let path_str = &arr[offset..];
        if !path_str.iter().any(|&c| c == '/') {
            i += 1;
            *i_ref = i;
            return;
        }
    } else {
        return;
    }

    let mut path = [0u8; 4096];
    let st_arr = s.string_table.arr.as_ref().unwrap();
    let offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
    let path_slice = &st_arr[offset..];
    let len = path_slice.iter().take_while(|&&c| c != '\0').count();

    if len >= 4096 {
        return;
    }

    for (i, &c) in path_slice.iter().take(len).enumerate() {
        path[i] = c as u8;
    }

    s.found_all_needed[depth] = if *needed_not_found <= 1 { '1' } else { '0' };

    let mut err_idx = 0;
    if path[0] != b'/' {
        err_idx = 1; // " is not absolute"
        exit_code = 28;
    } else {
        let code = recurse(
            unsafe { CStr::from_bytes_with_nul_unchecked(&path[..=len]) }.to_str().unwrap(),
            depth + 1,
            s,
            compat,
            FoundT { how: HowT::DIRECT, depth: 0 },
        );
        if code == 28 {
            exit_code = 28;
        }
        if code != 0 && code != 28 {
            err_idx = 2; // " not found"
        }
    }

    if err_idx != 0 {
        tree_preamble(s, depth + 1);
        if s.color != 0 {
            stdout().write_all(b"\x1b[1;31m").unwrap();
        }
        stdout().write_all(&path[..len]).unwrap();
        stdout().write_all(match err_idx {
            1 => b" is not absolute",
            2 => b" not found",
            _ => unreachable!(),
        }).unwrap();
        stdout().write_all(if s.color != 0 { b"\x1b[0m\n" } else { b"\n" }).unwrap();
    }

    let tmp = needed_buf_offsets.p.as_mut().unwrap()[i];
    needed_buf_offsets.p.as_mut().unwrap()[i] = needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found - 1];
    *needed_not_found -= 1;
    needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found] = tmp;

    *depth_ref = depth;
    *exit_code_ref = exit_code;
    *i_ref = i;
}

pub fn recurse(
    current_file: &str,
    mut depth: usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
    reason: FoundT,
) -> i32 {
    // Open the file
    let mut fptr = match File::open(current_file) {
        Ok(f) => f,
        Err(_) => return 31,
    };

    let old_buf_size = s.string_table.n;
    let mut e_ident = [0u8; 16];

    // Read ELF identification
    if fptr.read_exact(&mut e_ident).is_err() {
        return 11;
    }

    // Check ELF magic
    if e_ident[0] != 0x7f || e_ident[1] != b'E' || e_ident[2] != b'L' || e_ident[3] != b'F' {
        return 11;
    }

    // Check ELF class
    if e_ident[4] != 1 && e_ident[4] != 2 {
        return 12;
    }

    // Check data encoding
    if e_ident[5] != 1 && e_ident[5] != 2 {
        return 13;
    }

    let curr_type = CompatT {
        any: if e_ident[4] == 1 { '\0' } else { '\x01' },
        class: e_ident[4],
        machine: 0,
    };
    let is_little_endian = e_ident[5] == 1;

    if compat.any == '\0' && compat.class != curr_type.class {
        return 15;
    }

    if is_little_endian != host_is_little_endian() {
        return 16;
    }

    let mut header = HeaderUnion { h64: ManuallyDrop::new(Header64T {
        e_type: 0,
        e_machine: 0,
        e_version: 0,
        e_entry: 0,
        e_phoff: 0,
        e_shoff: 0,
        e_flags: 0,
        e_ehsize: 0,
        e_phentsize: 0,
        e_phnum: 0,
        e_shentsize: 0,
        e_shnum: 0,
        e_shstrndx: 0,
    }) };

    let mut header_clone = unsafe { std::mem::transmute_copy(&header) };
    if curr_type.class == 2 {
        if helper_recurse_1(&mut curr_type.clone(), compat.clone(), &mut fptr, header_clone).is_err() {
            return 19;
        }
    } else {
        if helper_recurse_2(&mut curr_type.clone(), compat.clone(), &mut fptr, header_clone).is_err() {
            return 19;
        }
    }

    let mut prog = ProgUnion { p64: ManuallyDrop::new(Prog64T {
        p_type: 0,
        p_flags: 0,
        p_offset: 0,
        p_vaddr: 0,
        p_paddr: 0,
        p_filesz: 0,
        p_memsz: 0,
        p_align: 0,
    }) };
    let mut pt_load_offset = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    let mut pt_load_vaddr = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut pt_load_offset);
    small_vec_u64_init(&mut pt_load_vaddr);
    let mut p_offset = u64::MAX;

    if curr_type.class == 2 {
        unsafe {
            for _ in 0..header.h64.e_phnum {
                let mut buf = [0u8; std::mem::size_of::<Prog64T>()];
                if fptr.read_exact(&mut buf).is_err() {
                    small_vec_u64_free(&mut pt_load_offset);
                    small_vec_u64_free(&mut pt_load_vaddr);
                    return 19;
                }
                prog.p64 = ManuallyDrop::new(std::mem::transmute(buf));

                if prog.p64.p_type == 1 {
                    small_vec_u64_append(&mut pt_load_offset, prog.p64.p_offset);
                    small_vec_u64_append(&mut pt_load_vaddr, prog.p64.p_vaddr);
                } else if prog.p64.p_type == 2 {
                    p_offset = prog.p64.p_offset;
                }
            }
        }
    } else {
        unsafe {
            for _ in 0..header.h32.e_phnum {
                let mut buf = [0u8; std::mem::size_of::<Prog32T>()];
                if fptr.read_exact(&mut buf).is_err() {
                    small_vec_u64_free(&mut pt_load_offset);
                    small_vec_u64_free(&mut pt_load_vaddr);
                    return 19;
                }
                prog.p32 = ManuallyDrop::new(std::mem::transmute(buf));

                if prog.p32.p_type == 1 {
                    small_vec_u64_append(&mut pt_load_offset, prog.p32.p_offset as u64);
                    small_vec_u64_append(&mut pt_load_vaddr, prog.p32.p_vaddr as u64);
                } else if prog.p32.p_type == 2 {
                    p_offset = prog.p32.p_offset as u64;
                }
            }
        }
    }

    let finfo = match std::fs::metadata(current_file) {
        Ok(m) => m,
        Err(_) => {
            small_vec_u64_free(&mut pt_load_offset);
            small_vec_u64_free(&mut pt_load_vaddr);
            return 20;
        }
    };

    // FIX: Correctly handle stat types and references
    let stat_ref = finfo.as_raw_stat();
    let stat_libc: &libc::stat = unsafe { &*(stat_ref as *const std::os::linux::raw::stat as *const libc::stat) };
    let seen_before = visited_files_contains(&s.visited, stat_libc);

    if !seen_before {
        visited_files_append(&mut s.visited, stat_ref);
    }

    if p_offset == u64::MAX {
        print_line(
            depth,
            current_file,
            "\x1b[1;36m",
            "\x1b[0;36m",
            true,
            reason.clone(),
            s,
        );
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return 0;
    }

    if pt_load_offset.n == 0 {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return 29;
    }

    if fptr.seek(SeekFrom::Start(p_offset)).is_err() {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return 21;
    }

    let mut no_def_lib = 0;
    let mut strtab = u64::MAX;
    let mut rpath = u64::MAX;
    let mut runpath = u64::MAX;
    let mut soname = u64::MAX;
    let mut needed = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed);

    let mut cont = 1;
    while cont != 0 {
        if helper_recurse_3(
            &mut no_def_lib,
            &mut strtab,
            &mut rpath,
            &mut runpath,
            &mut soname,
            &mut cont,
            &mut fptr,
            curr_type.clone(),
            &mut pt_load_offset,
            &mut pt_load_vaddr,
            &mut needed,
        ).is_err() {
            small_vec_u64_free(&mut pt_load_offset);
            small_vec_u64_free(&mut pt_load_vaddr);
            small_vec_u64_free(&mut needed);
            return 23;
        }
    }

    if strtab == u64::MAX {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut needed);
        return 23;
    }

    if !is_ascending_order(&pt_load_vaddr.buf, pt_load_vaddr.n) {
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut needed);
        return 30;
    }

    let mut vaddr_idx = 0;
    while (vaddr_idx + 1) != pt_load_vaddr.n && strtab >= pt_load_vaddr.buf[vaddr_idx + 1] {
        vaddr_idx += 1;
    }

    let strtab_offset = (pt_load_offset.buf[vaddr_idx] + strtab) - pt_load_vaddr.buf[vaddr_idx];
    small_vec_u64_free(&mut pt_load_vaddr);
    small_vec_u64_free(&mut pt_load_offset);

    let soname_buf_offset = s.string_table.n;
    if soname != u64::MAX {
        if fptr.seek(SeekFrom::Start(strtab_offset + soname)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return 24;
        }
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    let in_exclude_list = soname != u64::MAX && {
        let soname_str = unsafe { 
            let ptr = s.string_table.arr.as_ref().unwrap().as_ptr() as *const u8;
            CStr::from_ptr(ptr.add(soname_buf_offset)) 
        };
        is_in_exclude_list(soname_str.to_str().unwrap_or("")) != 0
    };

    let should_recurse = depth < s.max_depth as usize
        && ((!seen_before && !in_exclude_list)
            || ((!seen_before && in_exclude_list) && s.verbosity >= 2)
            || s.verbosity >= 3);

    if !should_recurse {
        let print_name = if soname == u64::MAX || s.path != 0 {
            current_file
        } else {
            unsafe { 
                let ptr = s.string_table.arr.as_ref().unwrap().as_ptr() as *const u8;
                CStr::from_ptr(ptr.add(soname_buf_offset))
                    .to_str()
                    .unwrap_or("")
            }
        };

        let bold_color = if in_exclude_list {
            "\x1b[0;35m"
        } else if seen_before {
            "\x1b[0;34m"
        } else {
            "\x1b[1;36m"
        };

        let regular_color = if in_exclude_list {
            "\x1b[0;35m"
        } else if seen_before {
            "\x1b[0;34m"
        } else {
            "\x1b[0;36m"
        };

        let highlight = !seen_before && !in_exclude_list;
        print_line(
            depth,
            print_name,
            bold_color,
            regular_color,
            highlight,
            reason,
            s,
        );
        s.string_table.n = old_buf_size;
        small_vec_u64_free(&mut needed);
        return 0;
    }

    let mut origin = [0u8; 4096];
    let path_bytes = current_file.as_bytes();
    if let Some(last_slash) = current_file.rfind('/') {
        origin[..last_slash].copy_from_slice(&path_bytes[..last_slash]);
        origin[last_slash] = 0;
    } else {
        origin[..2].copy_from_slice(b"./");
        origin[2] = 0;
    }

    if rpath == u64::MAX {
        s.rpath_offsets[depth] = usize::MAX;
    } else {
        s.rpath_offsets[depth] = s.string_table.n;
        if fptr.seek(SeekFrom::Start(strtab_offset + rpath)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return 25;
        }
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, s.rpath_offsets[depth], unsafe {
            CStr::from_ptr(origin.as_ptr()).to_str().unwrap_or("")
        }) != 0 {
            s.rpath_offsets[depth] = curr_buf_size;
        }
    }

    let runpath_buf_offset = s.string_table.n;
    if runpath != u64::MAX {
        if fptr.seek(SeekFrom::Start(strtab_offset + runpath)).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed);
            return 26;
        }
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, runpath_buf_offset, unsafe {
            CStr::from_ptr(origin.as_ptr()).to_str().unwrap_or("")
        }) != 0 {
            s.string_table.n = curr_buf_size;
        }
    }

    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);

    for i in 0..needed.n {
        small_vec_u64_append(&mut needed_buf_offsets, s.string_table.n as u64);
        if fptr.seek(SeekFrom::Start(strtab_offset + needed.buf[i])).is_err() {
            s.string_table.n = old_buf_size;
            small_vec_u64_free(&mut needed_buf_offsets);
            small_vec_u64_free(&mut needed);
            return 27;
        }
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    let print_name = if soname == u64::MAX || s.path != 0 {
        current_file
    } else {
        unsafe { 
            let ptr = s.string_table.arr.as_ref().unwrap().as_ptr() as *const u8;
            CStr::from_ptr(ptr.add(soname_buf_offset))
                .to_str()
                .unwrap_or("")
        }
    };

    let bold_color = if in_exclude_list {
        "\x1b[0;35m"
    } else if seen_before {
        "\x1b[0;34m"
    } else {
        "\x1b[1;36m"
    };

    let regular_color = if in_exclude_list {
        "\x1b[0;35m"
    } else if seen_before {
        "\x1b[0;34m"
    } else {
        "\x1b[0;36m"
    };

    let highlight = !seen_before && !in_exclude_list;
    print_line(
        depth,
        print_name,
        bold_color,
        regular_color,
        highlight,
        reason,
        s,
    );

    let mut exit_code = 0;
    let mut needed_not_found = needed_buf_offsets.n;

    if needed_not_found != 0 && s.verbosity == 0 {
        apply_exclude_list(&mut needed_not_found, &mut needed_buf_offsets, s);
    }

    if needed_not_found != 0 {
        exit_code |= check_absolute_paths(
            &mut needed_not_found,
            &mut needed_buf_offsets,
            &mut depth,
            s,
            curr_type.clone(),
        );
    }

    if runpath == u64::MAX {
        for j in (0..=depth).rev() {
            if needed_not_found == 0 {
                break;
            }
            if s.rpath_offsets[j] == usize::MAX {
                continue;
            }
            exit_code |= check_search_paths(
                FoundT {
                    how: HowT::RPATH,
                    depth: j,
                },
                s.rpath_offsets[j],
                &mut needed_not_found,
                &mut needed_buf_offsets,
                depth,
                s,
                curr_type.clone(),
            );
        }
    }

    if needed_not_found != 0 && s.ld_library_path_offset != usize::MAX {
        exit_code |= check_search_paths(
            FoundT {
                how: HowT::LD_LIBRARY_PATH,
                depth: 0,
            },
            s.ld_library_path_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type.clone(),
        );
    }

    if needed_not_found != 0 && runpath != u64::MAX {
        exit_code |= check_search_paths(
            FoundT {
                how: HowT::RUNPATH,
                depth: 0,
            },
            runpath_buf_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type.clone(),
        );
    }

    if needed_not_found != 0 && no_def_lib == 0 {
        exit_code |= check_search_paths(
            FoundT {
                how: HowT::LD_SO_CONF,
                depth: 0,
            },
            s.ld_so_conf_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type.clone(),
        );
    }

    if needed_not_found != 0 && no_def_lib == 0 {
        exit_code |= check_search_paths(
            FoundT {
                how: HowT::DEFAULT,
                depth: 0,
            },
            s.default_paths_offset,
            &mut needed_not_found,
            &mut needed_buf_offsets,
            depth,
            s,
            curr_type.clone(),
        );
    }

    if needed_not_found != 0 {
        print_error(
            depth,
            needed_not_found,
            &needed_buf_offsets,
            if runpath == u64::MAX {
                None
            } else {
                Some(unsafe {
                    let ptr = s.string_table.arr.as_ref().unwrap().as_ptr() as *const u8;
                    CStr::from_ptr(ptr.add(runpath_buf_offset))
                        .to_str()
                        .unwrap_or("")
                })
            },
            s,
            no_def_lib != 0,
        );
        s.string_table.n = old_buf_size;
        small_vec_u64_free(&mut needed_buf_offsets);
        small_vec_u64_free(&mut needed);
        return 28;
    }

    s.string_table.n = old_buf_size;
    small_vec_u64_free(&mut needed_buf_offsets);
    small_vec_u64_free(&mut needed);
    exit_code
}

pub fn check_search_paths(
    reason: FoundT,
    offset: usize,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    mut depth: usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
) -> i32 {
    let mut exit_code = 0;
    let mut path = [0u8; 4096];
    let path_end = unsafe { path.as_ptr().add(4096) };
    let st_ptr = &s.string_table as *const StringTableT;

    let mut current_offset = offset;
    while unsafe { &*st_ptr }.arr.as_ref().map_or(false, |arr| arr[current_offset] != '\0') {
        helper_check_search_paths_1(
            &mut current_offset,
            &mut depth,
            &mut exit_code,
            reason.clone(),
            needed_not_found,
            needed_buf_offsets,
            s,
            compat.clone(),
            &mut path,
            path_end,
            unsafe { &*st_ptr },
        );
    }

    exit_code
}
