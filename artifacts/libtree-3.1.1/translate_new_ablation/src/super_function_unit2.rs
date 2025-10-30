use crate::*;
use crate::HowT::DIRECT;
use std::ffi::CStr;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::mem::ManuallyDrop;
use std::os::raw::c_char;
use std::os::unix::fs::MetadataExt;
use std::path::Path;
use std::ptr;

pub fn helper_helper_check_search_paths_1_1(
    depth_ref: &mut usize,
    exit_code_ref: &mut i32,
    i_ref: &mut usize,
    reason: FoundT,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    s: &mut LibtreeStateT,
    compat: CompatT,
    path: &mut [c_char; 4096],
    path_end: *const c_char,
    search_path_end: *mut c_char,
) {
    let depth = *depth_ref;
    let mut exit_code = *exit_code_ref;
    let mut i = *i_ref;

    // Get soname_len safely
    let soname_offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
    let soname_slice = &s.string_table.arr.as_ref().unwrap()[soname_offset..];
    let soname_cstr = unsafe { CStr::from_ptr(soname_slice.as_ptr() as *const c_char) };
    let soname_len = soname_cstr.to_bytes().len();

    // Check buffer bounds
    unsafe {
        if search_path_end.add(soname_len + 1) >= path_end as *mut c_char {
            return;
        }

        // Copy the string safely
        ptr::copy_nonoverlapping(
            soname_slice.as_ptr() as *const c_char,
            search_path_end,
            soname_len + 1,
        );
    }

    s.found_all_needed[depth] = if *needed_not_found <= 1 { '1' } else { '0' };

    let code = match recurse(unsafe { CStr::from_ptr(path.as_ptr()).to_str().unwrap() }, depth + 1, s, compat, reason) {
        Ok(c) => c,
        Err(_) => return,
    };

    if code == 28 {
        exit_code = 28;
    }

    if code == 0 || code == 28 {
        let tmp = needed_buf_offsets.p.as_mut().unwrap()[i];
        let last_index = *needed_not_found - 1;
        needed_buf_offsets.p.as_mut().unwrap()[i] = needed_buf_offsets.p.as_mut().unwrap()[last_index];
        *needed_not_found -= 1;
        needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found] = tmp;
    } else {
        i += 1;
    }

    *depth_ref = depth;
    *exit_code_ref = exit_code;
    *i_ref = i;
}

pub fn recurse(
    current_file: &str,
    depth: usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
    reason: FoundT,
) -> Result<i32, Box<dyn std::error::Error>> {
    let mut fptr = File::open(current_file)?;
    let old_buf_size = s.string_table.n;

    // Read ELF identification
    let mut e_ident = [0u8; 16];
    fptr.read_exact(&mut e_ident)?;

    // Check ELF magic number
    if e_ident[0] != 0x7f || e_ident[1] != b'E' || e_ident[2] != b'L' || e_ident[3] != b'F' {
        return Ok(11);
    }

    // Check ELF class (32-bit or 64-bit)
    if e_ident[4] != 1 && e_ident[4] != 2 {
        return Ok(12);
    }

    // Check endianness
    if e_ident[5] != 1 && e_ident[5] != 2 {
        return Ok(13);
    }

    let curr_type = CompatT {
        any: '\0',
        class: e_ident[4],
        machine: 0,
    };
    let is_little_endian = e_ident[5] == 1;

    if compat.any != '\0' && compat.class != curr_type.class {
        return Ok(15);
    }

    if is_little_endian != host_is_little_endian() {
        return Ok(16);
    }

    let mut curr_type_clone = curr_type.clone();
    let e_phnum = if curr_type.class == 2 {
        let mut temp_header = HeaderUnion { h64: ManuallyDrop::new(Header64T {
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
        })};
        let header_clone = unsafe { HeaderUnion { h64: ManuallyDrop::new((*temp_header.h64).clone()) } };
        helper_recurse_1(&mut curr_type_clone, compat.clone(), &mut fptr, header_clone)
            .map_err(|e| Box::new(std::io::Error::new(std::io::ErrorKind::Other, e.to_string())))?;
        unsafe { temp_header.h64.e_phnum }
    } else {
        let mut temp_header = HeaderUnion { h32: ManuallyDrop::new(Header32T {
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
        })};
        let header_clone = unsafe { HeaderUnion { h32: ManuallyDrop::new((*temp_header.h32).clone()) } };
        helper_recurse_2(&mut curr_type_clone, compat.clone(), &mut fptr, header_clone)
            .map_err(|e| Box::new(std::io::Error::new(std::io::ErrorKind::Other, e.to_string())))?;
        unsafe { temp_header.h32.e_phnum }
    };

    let mut prog: ManuallyDrop<Box<dyn std::any::Any>> = if curr_type.class == 2 {
        ManuallyDrop::new(Box::new(Prog64T {
            p_type: 0,
            p_flags: 0,
            p_offset: 0,
            p_vaddr: 0,
            p_paddr: 0,
            p_filesz: 0,
            p_memsz: 0,
            p_align: 0,
        }))
    } else {
        ManuallyDrop::new(Box::new(Prog32T {
            p_type: 0,
            p_offset: 0,
            p_vaddr: 0,
            p_paddr: 0,
            p_filesz: 0,
            p_memsz: 0,
            p_flags: 0,
            p_align: 0,
        }))
    };

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
            let mut value = ManuallyDrop::into_inner(prog);
            for _ in 0..e_phnum {
                let mut buf = [0u8; std::mem::size_of::<Prog64T>()];
                fptr.read_exact(&mut buf)?;
                let prog64: Prog64T = unsafe { std::mem::transmute(buf) };
                *value.downcast_mut::<Prog64T>().unwrap() = prog64.clone();

                if prog64.p_type == 1 {
                    small_vec_u64_append(&mut pt_load_offset, prog64.p_offset);
                    small_vec_u64_append(&mut pt_load_vaddr, prog64.p_vaddr);
                } else if prog64.p_type == 2 {
                    p_offset = prog64.p_offset;
                }
            }
            prog = ManuallyDrop::new(value);
        }
    } else {
        unsafe {
            let mut value = ManuallyDrop::into_inner(prog);
            for _ in 0..e_phnum {
                let mut buf = [0u8; std::mem::size_of::<Prog32T>()];
                fptr.read_exact(&mut buf)?;
                let prog32: Prog32T = unsafe { std::mem::transmute(buf) };
                *value.downcast_mut::<Prog32T>().unwrap() = prog32.clone();

                if prog32.p_type == 1 {
                    small_vec_u64_append(&mut pt_load_offset, prog32.p_offset as u64);
                    small_vec_u64_append(&mut pt_load_vaddr, prog32.p_vaddr as u64);
                } else if prog32.p_type == 2 {
                    p_offset = prog32.p_offset as u64;
                }
            }
            prog = ManuallyDrop::new(value);
        }
    }

    let mut stat = std::mem::MaybeUninit::<libc::stat>::uninit();
    let r = unsafe {
        libc::stat(
            current_file.as_ptr() as *const libc::c_char,
            stat.as_mut_ptr(),
        )
    };
    if r != 0 {
        return Err(Box::new(std::io::Error::last_os_error()));
    }
    let stat = unsafe { stat.assume_init() };

    let seen_before = visited_files_contains(&s.visited, &stat) != 0;
    if !seen_before {
        let raw_stat = std::os::linux::raw::stat {
            st_dev: stat.st_dev,
            st_ino: stat.st_ino,
            st_mode: stat.st_mode,
            st_nlink: stat.st_nlink,
            st_uid: stat.st_uid,
            st_gid: stat.st_gid,
            st_rdev: stat.st_rdev,
            st_size: stat.st_size,
            st_blksize: stat.st_blksize,
            st_blocks: stat.st_blocks,
            st_atime: stat.st_atime,
            st_atime_nsec: stat.st_atime_nsec,
            st_mtime: stat.st_mtime,
            st_mtime_nsec: stat.st_mtime_nsec,
            st_ctime: stat.st_ctime,
            st_ctime_nsec: stat.st_ctime_nsec,
            __pad0: 0,
            __unused: [0; 3],
        };
        visited_files_append(&mut s.visited, &raw_stat);
    }

    if p_offset == u64::MAX {
        print_line(
            depth,
            current_file,
            "\x1b[1;36m",
            "\x1b[0;36m",
            true,
            reason,
            s,
        );
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return Ok(0);
    }

    if pt_load_offset.n == 0 {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        return Ok(29);
    }

    fptr.seek(SeekFrom::Start(p_offset))?;

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

    loop {
        let mut cont = 1;
        helper_recurse_3(
            &mut no_def_lib,
            &mut strtab,
            &mut rpath,
            &mut runpath,
            &mut soname,
            &mut cont,
            &mut fptr,
            &curr_type,
            &mut pt_load_offset,
            &mut pt_load_vaddr,
            &mut needed,
        )?;
        if cont == 0 {
            break;
        }
    }

    if strtab == u64::MAX {
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut needed);
        return Ok(23);
    }

    if !is_ascending_order(&pt_load_vaddr.buf, pt_load_vaddr.n) {
        small_vec_u64_free(&mut pt_load_vaddr);
        small_vec_u64_free(&mut pt_load_offset);
        small_vec_u64_free(&mut needed);
        return Ok(30);
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
        fptr.seek(SeekFrom::Start(strtab_offset + soname))?;
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    let in_exclude_list = soname != u64::MAX && {
        let soname_str = unsafe {
            CStr::from_ptr(s.string_table.arr.as_ref().unwrap().as_ptr().add(soname_buf_offset) as *const i8)
        };
        is_in_exclude_list(Some(soname_str.to_str().unwrap())) != 0
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
                CStr::from_ptr(s.string_table.arr.as_ref().unwrap().as_ptr().add(soname_buf_offset) as *const i8)
                    .to_str().unwrap()
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
        return Ok(0);
    }

    let mut origin = [0u8; 4096];
    let path = Path::new(current_file);
    if let Some(parent) = path.parent() {
        let parent_str = parent.to_str().ok_or("Invalid path")?;
        origin[..parent_str.len()].copy_from_slice(parent_str.as_bytes());
        origin[parent_str.len()] = b'\0';
    } else {
        origin[..2].copy_from_slice(b"./");
        origin[2] = b'\0';
    }

    if rpath == u64::MAX {
        s.rpath_offsets[depth] = usize::MAX;
    } else {
        s.rpath_offsets[depth] = s.string_table.n;
        fptr.seek(SeekFrom::Start(strtab_offset + rpath))?;
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, s.rpath_offsets[depth], unsafe {
            CStr::from_ptr(origin.as_ptr() as *const i8).to_str().unwrap()
        }) != 0
        {
            s.rpath_offsets[depth] = curr_buf_size;
        }
    }

    let mut runpath_buf_offset = s.string_table.n;
    if runpath != u64::MAX {
        fptr.seek(SeekFrom::Start(strtab_offset + runpath))?;
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
        let curr_buf_size = s.string_table.n;
        if interpolate_variables(s, runpath_buf_offset, unsafe {
            CStr::from_ptr(origin.as_ptr() as *const i8).to_str().unwrap()
        }) != 0
        {
            runpath_buf_offset = curr_buf_size;
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
        fptr.seek(SeekFrom::Start(strtab_offset + needed.buf[i]))?;
        string_table_copy_from_file(&mut s.string_table, &mut fptr);
    }

    let print_name = if soname == u64::MAX || s.path != 0 {
        current_file
    } else {
        unsafe {
            CStr::from_ptr(s.string_table.arr.as_ref().unwrap().as_ptr().add(soname_buf_offset) as *const i8)
                .to_str().unwrap()
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
            depth,
            s,
            curr_type.clone(),
        )?;
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
            )?;
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
        )?;
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
        )?;
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
        )?;
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
        )?;
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
                    CStr::from_ptr(s.string_table.arr.as_ref().unwrap().as_ptr().add(runpath_buf_offset) as *const i8)
                        .to_str().unwrap()
                })
            },
            s,
            no_def_lib != 0,
        );
        s.string_table.n = old_buf_size;
        small_vec_u64_free(&mut needed_buf_offsets);
        small_vec_u64_free(&mut needed);
        return Ok(28);
    }

    s.string_table.n = old_buf_size;
    small_vec_u64_free(&mut needed_buf_offsets);
    small_vec_u64_free(&mut needed);
    Ok(exit_code)
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
    path: &mut [c_char; 4096],
    path_end: *const c_char,
) -> i32 {
    let mut offset = *offset_ref;
    let mut depth = *depth_ref;
    let mut exit_code = *exit_code_ref;

    // Skip colons
    while s.string_table.arr.as_ref().map_or(false, |arr| offset < arr.len() && arr[offset] == ':') {
        offset += 1;
    }

    // Check for end of string
    if s.string_table.arr.as_ref().map_or(true, |arr| offset >= arr.len() || arr[offset] == '\0') {
        return exit_code;
    }

    // Copy path segment
    let mut dest_idx = 0;
    while s.string_table.arr.as_ref().map_or(false, |arr| 
        offset < arr.len() && 
        arr[offset] != '\0' && 
        arr[offset] != ':' && 
        dest_idx < path.len() && 
        unsafe { path.as_ptr().add(dest_idx) } != path_end
    ) {
        path[dest_idx] = s.string_table.arr.as_ref().unwrap()[offset] as c_char;
        offset += 1;
        dest_idx += 1;
    }

    // Check path bounds
    if dest_idx + 1 >= path.len() || unsafe { path.as_ptr().add(dest_idx + 1) } >= path_end {
        *offset_ref = offset;
        *depth_ref = depth;
        *exit_code_ref = exit_code;
        return exit_code;
    }

    // Add trailing slash if needed
    if dest_idx > 0 && path[dest_idx - 1] != b'/' as c_char {
        path[dest_idx] = b'/' as c_char;
        dest_idx += 1;
    }

    let search_path_end = unsafe { path.as_mut_ptr().add(dest_idx) };

    // Process needed items
    let mut i = 0;
    while i < *needed_not_found {
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
            search_path_end,
        );
    }

    *offset_ref = offset;
    *depth_ref = depth;
    *exit_code_ref = exit_code;
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

    // Check if path contains '/'
    if let Some(arr) = &s.string_table.arr {
        let offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
        let path_str = &arr[offset..];
        if !path_str.contains(&'/') {
            i += 1;
            *i_ref = i;
            return;
        }
    }

    let mut path = [0 as c_char; 4096];
    if let Some(arr) = &s.string_table.arr {
        let offset = needed_buf_offsets.p.as_ref().unwrap()[i] as usize;
        let path_slice = &arr[offset..];
        let len = path_slice.len();
        
        if len >= 4096 {
            return;
        }

        for (i, &c) in path_slice.iter().take(len).enumerate() {
            path[i] = c as c_char;
        }
        path[len] = 0;
    }

    s.found_all_needed[depth] = if *needed_not_found <= 1 { '1' } else { '0' };
    let mut err_idx = 0;

    if path[0] != b'/' as c_char {
        err_idx = 1; // " is not absolute"
        exit_code = 28;
    } else {
        let code = match recurse(
            unsafe { CStr::from_ptr(&path[0]).to_str().unwrap() },
            depth + 1,
            s,
            compat,
            FoundT { how: HowT::DIRECT, depth: 0 },
        ) {
            Ok(c) => c,
            Err(_) => -1,
        };
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
            print!("\x1B[1;31m");
        }
        unsafe {
            print!("{}", CStr::from_ptr(&path[0]).to_string_lossy());
        }
        match err_idx {
            1 => print!(" is not absolute"),
            2 => print!(" not found"),
            _ => (),
        }
        if s.color != 0 {
            println!("\x1B[0m");
        } else {
            println!();
        }
    }

    let tmp = needed_buf_offsets.p.as_mut().unwrap()[i];
    needed_buf_offsets.p.as_mut().unwrap()[i] = needed_buf_offsets.p.as_mut().unwrap()[(*needed_not_found) - 1];
    *needed_not_found -= 1;
    needed_buf_offsets.p.as_mut().unwrap()[*needed_not_found] = tmp;

    *depth_ref = depth;
    *exit_code_ref = exit_code;
    *i_ref = i;
}

pub fn check_search_paths(
    reason: FoundT,
    offset: usize,
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    mut depth: usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
) -> Result<i32, Box<dyn std::error::Error>> {
    let mut exit_code = 0;
    let mut path = [0 as c_char; 4096];
    let path_end = unsafe { path.as_ptr().add(4096) };

    let mut current_offset = offset;
    loop {
        // Check condition without holding borrow
        let cond = s.string_table.arr.as_ref().map_or(false, |arr| 
            current_offset < arr.len() && 
            arr[current_offset] != '\0'
        );
        if !cond {
            break;
        }

        exit_code = helper_check_search_paths_1(
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
        );
    }

    Ok(exit_code)
}

pub fn check_absolute_paths(
    needed_not_found: &mut usize,
    needed_buf_offsets: &mut SmallVecU64T,
    mut depth: usize,
    s: &mut LibtreeStateT,
    compat: CompatT,
) -> Result<i32, Box<dyn std::error::Error>> {
    let mut exit_code = 0;
    let mut i = 0;
    
    while i < *needed_not_found {
        helper_check_absolute_paths_1(
            &mut depth,
            &mut exit_code,
            &mut i,
            needed_not_found,
            needed_buf_offsets,
            s,
            compat.clone(),
        );
    }

    Ok(exit_code)
}
