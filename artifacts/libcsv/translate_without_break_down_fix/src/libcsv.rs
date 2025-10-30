use crate::*;
use lazy_static::lazy_static;
use std::alloc::Layout;
use std::alloc::dealloc;
use std::alloc::realloc;
use std::assert;
use std::cmp;
use std::ffi::c_void;
use std::fs::File;
use std::io::Write;
use std::io;
use std::ptr;

pub fn csv_write2(mut dest: Option<&mut [u8]>, src: Option<&[u8]>, quote: u8) -> usize {
	println!("* csv_write2");
    let mut chars = 0;

    // Early return if src is None (equivalent to NULL check in C)
    let src = match src {
        Some(s) => s,
        None => return 0,
    };

    // Handle dest being None by setting effective size to 0
    let dest_size = dest.as_ref().map_or(0, |d| d.len());
    let mut cdest_idx = 0;

    // Write opening quote if there's space
    if dest_size > chars {
        if let Some(d) = dest.as_mut() {
            d[cdest_idx] = quote;
            cdest_idx += 1;
        }
    }
    chars = chars.saturating_add(1);

    // Process each byte in src
    for &byte in src {
        // Double quotes if needed
        if byte == quote {
            if dest_size > chars {
                if let Some(d) = dest.as_mut() {
                    d[cdest_idx] = quote;
                    cdest_idx += 1;
                }
            }
            chars = chars.saturating_add(1);
        }

        // Copy the byte
        if dest_size > chars {
            if let Some(d) = dest.as_mut() {
                d[cdest_idx] = byte;
                cdest_idx += 1;
            }
        }
        chars = chars.saturating_add(1);
    }

    // Write closing quote if there's space
    if dest_size > chars {
        if let Some(d) = dest.as_mut() {
            d[cdest_idx] = quote;
        }
    }
    chars = chars.saturating_add(1);

    chars
}

pub fn csv_fwrite2(fp: &mut dyn Write, src: Option<&[u8]>, src_size: usize, quote: u8) -> io::Result<()> {
	println!("* csv_fwrite2");
    // Check for NULL-equivalent conditions (None for src)
    let csrc = match src {
        Some(s) => s,
        None => return Ok(()),
    };

    // Write opening quote
    fp.write_all(&[quote])?;

    let mut csrc_idx = 0;
    let mut remaining_size = src_size;

    while remaining_size > 0 {
        let current_byte = csrc[csrc_idx];
        
        // Double the quote if encountered
        if current_byte == quote {
            fp.write_all(&[quote])?;
        }

        // Write the current byte
        fp.write_all(&[current_byte])?;

        remaining_size -= 1;
        csrc_idx += 1;
    }

    // Write closing quote
    fp.write_all(&[quote])?;

    Ok(())
}
pub fn csv_init(p: &mut CsvParser, options: u8) -> i32 {
	println!("* csv_init");
    if p as *const _ == std::ptr::null() {
        return -1;
    }

    p.entry_buf = None;
    p.pstate = 0;
    p.quoted = 0;
    p.spaces = 0;
    p.entry_pos = 0;
    p.entry_size = 0;
    p.status = 0;
    p.options = options;
    p.quote_char = 0x22;
    p.delim_char = 0x2c;
    p.is_space = None;
    p.is_term = None;
    p.blk_size = 128;
    p.malloc_func = |size| unsafe { std::alloc::alloc(std::alloc::Layout::from_size_align(size, 1).unwrap()) };
    p.realloc_func = |ptr, size| unsafe { std::alloc::realloc(ptr, std::alloc::Layout::from_size_align(size, 1).unwrap(), size) };
    p.free_func = |ptr| unsafe { std::alloc::dealloc(ptr, std::alloc::Layout::from_size_align(1, 1).unwrap()) };

    0
}
pub fn csv_free(p: &mut CsvParser) {
	println!("* csv_free");
    if p.entry_buf.is_some() && p.free_func != CsvParser::default().free_func {
        if let Some(buf) = p.entry_buf.take() {
            let ptr = Box::into_raw(buf.into_boxed_slice()) as *mut u8;
            (p.free_func)(ptr);
        }
    }
    p.entry_size = 0;
}
pub fn csv_error(p: &CsvParser) -> i32 {
	println!("* csv_error");
    assert!(p.status != 0, "received null csv_parser");
    p.status
}

lazy_static! {
    pub static ref CSV_ERRORS: [&'static str; 5] = [
        "success",
        "error parsing data while strict checking enabled",
        "memory exhausted while increasing buffer size",
        "data size too large",
        "invalid status code"
    ];
}

pub fn csv_strerror(status: i32) -> &'static str {
	println!("* csv_strerror");
    if status >= 4 || status < 0 {
        &CSV_ERRORS[4]
    } else {
        &CSV_ERRORS[status as usize]
    }
}
pub fn csv_write(dest: Option<&mut [u8]>, src: Option<&[u8]>) -> usize {
	println!("* csv_write");
    csv_write2(dest, src, 0x22)
}

pub fn csv_fwrite(fp: &mut File, src: Option<&[u8]>, src_size: usize) -> std::io::Result<()> {
	println!("* csv_fwrite");
    csv_fwrite2(fp, src, src_size, 0x22)
}
pub fn csv_get_opts(p: Option<&CsvParser>) -> i32 {
	println!("* csv_get_opts");
    // Check if the reference is None (equivalent to NULL check in C)
    if p.is_none() {
        return -1;
    }
    
    // Safe to unwrap since we checked for None
    p.unwrap().options as i32
}
pub fn csv_set_opts(p: Option<&mut CsvParser>, options: u8) -> i32 {
	println!("* csv_set_opts");
    // Check if p is None (equivalent to NULL check in C)
    if p.is_none() {
        return -1;
    }

    // Unwrap safely and set options
    let p = p.unwrap();
    p.options = options;
    
    0
}
pub fn csv_set_delim(p: Option<&mut CsvParser>, c: u8) {
	println!("* csv_set_delim");
    if let Some(parser) = p {
        parser.delim_char = c;
    }
}
pub fn csv_set_quote(p: Option<&mut CsvParser>, c: u8) {
	println!("* csv_set_quote");
    if let Some(parser) = p {
        parser.quote_char = c;
    }
}
pub fn csv_get_delim(p: Option<&CsvParser>) -> Option<u8> {
	println!("* csv_get_delim");
    // Use Option<&CsvParser> to handle NULL pointer case
    let p = p?; // Early return if p is None (equivalent to assert in C)
    Some(p.delim_char)
}

pub fn csv_get_quote(p: Option<&CsvParser>) -> Option<u8> {
	println!("* csv_get_quote");
    assert!(p.is_some(), "received null csv_parser");
    Some(p.unwrap().quote_char)
}
pub fn csv_set_space_func(p: Option<&mut CsvParser>, f: Option<fn(u8) -> i32>) {
	println!("* csv_set_space_func");
    if let Some(p) = p {
        p.is_space = f;
    }
}
pub fn csv_set_term_func(p: Option<&mut CsvParser>, f: Option<fn(u8) -> i32>) {
	println!("* csv_set_term_func");
    if let Some(p) = p {
        p.is_term = f;
    }
}
pub fn csv_set_realloc_func(p: Option<&mut CsvParser>, f: Option<fn(*mut u8, usize) -> *mut u8>) {
	println!("* csv_set_realloc_func");
    if let (Some(p), Some(f)) = (p, f) {
        p.realloc_func = f;
    }
}
pub fn csv_set_free_func(p: Option<&mut CsvParser>, f: Option<fn(*mut u8)>) {
	println!("* csv_set_free_func");
    if let (Some(p), Some(f)) = (p, f) {
        p.free_func = f;
    }
}
pub fn csv_set_blk_size(p: Option<&mut CsvParser>, size: usize) {
	println!("* csv_set_blk_size");
    if let Some(p) = p {
        p.blk_size = size;
    }
}
pub fn csv_get_buffer_size(p: Option<&CsvParser>) -> usize {
	println!("* csv_get_buffer_size");
    // Use pattern matching to handle the Option
    match p {
        Some(parser) => parser.entry_size,
        None => 0,
    }
}

pub fn csv_increase_buffer(p: &mut CsvParser) -> i32 {
    if p.realloc_func == CsvParser::default().realloc_func {
        return 0;
    }

    let mut to_add = p.blk_size;
    if p.entry_size >= usize::MAX - to_add {
        to_add = usize::MAX - p.entry_size;
    }

    if to_add == 0 {
        p.status = 3;
        return -1;
    }

    let mut vp_idx = ptr::null_mut();
    loop {
        let current_size = p.entry_size + to_add;
        vp_idx = (p.realloc_func)(p.entry_buf.as_mut().map_or(ptr::null_mut(), |v| v.as_mut_ptr()), current_size);

        if !vp_idx.is_null() {
            break;
        }

        to_add /= 2;
        if to_add == 0 {
            p.status = 2;
            return -1;
        }
    }

    unsafe {
        if let Some(ref mut buf) = p.entry_buf {
            buf.set_len(p.entry_size + to_add);
        } else {
            let new_capacity = p.entry_size + to_add;
            let vec = Vec::from_raw_parts(vp_idx, new_capacity, new_capacity);
            p.entry_buf = Some(vec);
        }
    }
    p.entry_size += to_add;
    0
}
pub fn csv_fini(
    p: &mut CsvParser,
    cb1: Option<unsafe fn(Option<&[u8]>, usize, Option<&str>)>,
    cb2: Option<unsafe fn(i32, *mut c_void)>,
    data: Option<&str>,
) -> i32 {
	println!("* csv_fini");
    if p as *const _ == std::ptr::null() {
        return -1;
    }

    let mut quoted = p.quoted;
    let mut pstate = p.pstate;
    let mut spaces = p.spaces;
    let mut entry_pos = p.entry_pos;

    if pstate == 2 && p.quoted != 0 && (p.options & 1) != 0 && (p.options & 4) != 0 {
        p.status = 1;
        return -1;
    }

    match pstate {
        3 => {
            p.entry_pos -= p.spaces + 1;
            entry_pos = p.entry_pos;
        }
        1 | 2 => {
            {
                if quoted == 0 {
                    entry_pos -= spaces;
                }
                if (p.options & 8) != 0 {
                    if let Some(buf) = &mut p.entry_buf {
                        if entry_pos < buf.len() {
                            buf[entry_pos] = b'\0';
                        }
                    }
                }
                if cb1.is_some()
                    && (p.options & 16) != 0
                    && quoted == 0
                    && entry_pos == 0
                {
                    unsafe { cb1.unwrap()(None, entry_pos, data) };
                } else if cb1.is_some() {
                    unsafe {
                        cb1.unwrap()(
                            p.entry_buf.as_deref(),
                            entry_pos,
                            data,
                        )
                    };
                }
                pstate = 1;
                entry_pos = 0;
                quoted = 0;
                spaces = 0;
            }
            {
                if let Some(cb) = cb2 {
                    unsafe { cb(-1, data.map(|s| s as *const _ as *mut c_void).unwrap_or(std::ptr::null_mut())) };
                }
                pstate = 0;
                entry_pos = 0;
                quoted = 0;
                spaces = 0;
            }
        }
        0 => {}
        _ => {}
    }

    p.spaces = 0;
    p.quoted = 0;
    p.entry_pos = 0;
    p.status = 0;
    p.pstate = 0;

    0
}
pub fn csv_parse(
    p: &mut CsvParser,
    s: Option<&[u8]>,
    len: usize,
    cb1: Option<fn(Option<&[u8]>, usize, Option<&str>)>,
    cb2: Option<fn(i32, *mut std::ffi::c_void)>,
    data: Option<&str>,
) -> usize {
    use std::ffi::c_void;
    use std::ptr;

    let data_ptr = if let Some(s) = data {
        s.as_ptr() as *mut c_void
    } else {
        ptr::null_mut()
    };

    assert!(ptr::eq(p, p), "received null csv_parser");
    if s.is_none() {
        return 0;
    }
    let us = s.unwrap();
    let mut pos = 0;
    let delim = p.delim_char;
    let quote = p.quote_char;
    let is_space = p.is_space;
    let is_term = p.is_term;
    let mut quoted = p.quoted;
    let mut pstate = p.pstate;
    let mut spaces = p.spaces;
    let mut entry_pos = p.entry_pos;

    if p.entry_buf.is_none() && pos < len {
        if csv_increase_buffer(p) != 0 {
            p.quoted = quoted;
            p.pstate = pstate;
            p.spaces = spaces;
            p.entry_pos = entry_pos;
            return pos;
        }
    }

    while pos < len {
        if entry_pos == if (p.options & 8) != 0 {
            p.entry_size - 1
        } else {
            p.entry_size
        } {
            if csv_increase_buffer(p) != 0 {
                p.quoted = quoted;
                p.pstate = pstate;
                p.spaces = spaces;
                p.entry_pos = entry_pos;
                return pos;
            }
        }

        let c = us[pos];
        pos += 1;

        match pstate {
            0 | 1 => {
                if (is_space.map_or(c == 0x20 || c == 0x09, |f| f(c) != 0)) && c != delim {
                    continue;
                } else if is_term.map_or(c == 0x0d || c == 0x0a, |f| f(c) != 0) {
                    if pstate == 1 {
                        if quoted == 0 {
                            entry_pos -= spaces;
                        }
                        if (p.options & 8) != 0 {
                            p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                        }
                        if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1.unwrap()(None, entry_pos, data);
                        } else if cb1.is_some() {
                            cb1.unwrap()(
                                Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                                entry_pos,
                                data,
                            );
                        }
                        pstate = 1;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;

                        if cb2.is_some() {
                            cb2.unwrap()(c as i32, data_ptr);
                        }
                        pstate = 0;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    } else if (p.options & 2) != 0 {
                        if cb2.is_some() {
                            cb2.unwrap()(c as i32, data_ptr);
                        }
                        pstate = 0;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    }
                    continue;
                } else if c == delim {
                    if quoted == 0 {
                        entry_pos -= spaces;
                    }
                    if (p.options & 8) != 0 {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                    }
                    if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                        cb1.unwrap()(None, entry_pos, data);
                    } else if cb1.is_some() {
                        cb1.unwrap()(
                            Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                            entry_pos,
                            data,
                        );
                    }
                    pstate = 1;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;
                } else if c == quote {
                    pstate = 2;
                    quoted = 1;
                } else {
                    pstate = 2;
                    quoted = 0;
                    p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                    entry_pos += 1;
                }
            }
            2 => {
                if c == quote {
                    if quoted != 0 {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                        entry_pos += 1;
                        pstate = 3;
                    } else {
                        if (p.options & 1) != 0 {
                            p.status = 1;
                            p.quoted = quoted;
                            p.pstate = pstate;
                            p.spaces = spaces;
                            p.entry_pos = entry_pos;
                            return pos - 1;
                        }
                        p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                        entry_pos += 1;
                        spaces = 0;
                    }
                } else if c == delim {
                    if quoted != 0 {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                        entry_pos += 1;
                    } else {
                        if quoted == 0 {
                            entry_pos -= spaces;
                        }
                        if (p.options & 8) != 0 {
                            p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                        }
                        if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1.unwrap()(None, entry_pos, data);
                        } else if cb1.is_some() {
                            cb1.unwrap()(
                                Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                                entry_pos,
                                data,
                            );
                        }
                        pstate = 1;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    }
                } else if is_term.map_or(c == 0x0d || c == 0x0a, |f| f(c) != 0) {
                    if quoted == 0 {
                        if quoted == 0 {
                            entry_pos -= spaces;
                        }
                        if (p.options & 8) != 0 {
                            p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                        }
                        if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1.unwrap()(None, entry_pos, data);
                        } else if cb1.is_some() {
                            cb1.unwrap()(
                                Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                                entry_pos,
                                data,
                            );
                        }
                        pstate = 1;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;

                        if cb2.is_some() {
                            cb2.unwrap()(c as i32, data_ptr);
                        }
                        pstate = 0;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    } else {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                        entry_pos += 1;
                    }
                } else if quoted == 0 && is_space.map_or(c == 0x20 || c == 0x09, |f| f(c) != 0) {
                    p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                    entry_pos += 1;
                    spaces += 1;
                } else {
                    p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                    entry_pos += 1;
                    spaces = 0;
                }
            }
            3 => {
                if c == delim {
                    entry_pos -= spaces + 1;
                    if quoted == 0 {
                        entry_pos -= spaces;
                    }
                    if (p.options & 8) != 0 {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                    }
                    if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                        cb1.unwrap()(None, entry_pos, data);
                    } else if cb1.is_some() {
                        cb1.unwrap()(
                            Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                            entry_pos,
                            data,
                        );
                    }
                    pstate = 1;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;
                } else if is_term.map_or(c == 0x0d || c == 0x0a, |f| f(c) != 0) {
                    entry_pos -= spaces + 1;
                    if quoted == 0 {
                        entry_pos -= spaces;
                    }
                    if (p.options & 8) != 0 {
                        p.entry_buf.as_mut().unwrap()[entry_pos] = b'\0';
                    }
                    if cb1.is_some() && (p.options & 16) != 0 && quoted == 0 && entry_pos == 0 {
                        cb1.unwrap()(None, entry_pos, data);
                    } else if cb1.is_some() {
                        cb1.unwrap()(
                            Some(&p.entry_buf.as_ref().unwrap()[..entry_pos]),
                            entry_pos,
                            data,
                        );
                    }
                    pstate = 1;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;

                    if cb2.is_some() {
                        cb2.unwrap()(c as i32, data_ptr);
                    }
                    pstate = 0;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;
                } else if is_space.map_or(c == 0x20 || c == 0x09, |f| f(c) != 0) {
                    p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                    entry_pos += 1;
                    spaces += 1;
                } else if c == quote {
                    if spaces != 0 {
                        if (p.options & 1) != 0 {
                            p.status = 1;
                            p.quoted = quoted;
                            p.pstate = pstate;
                            p.spaces = spaces;
                            p.entry_pos = entry_pos;
                            return pos - 1;
                        }
                        spaces = 0;
                        p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                        entry_pos += 1;
                    } else {
                        pstate = 2;
                    }
                } else {
                    if (p.options & 1) != 0 {
                        p.status = 1;
                        p.quoted = quoted;
                        p.pstate = pstate;
                        p.spaces = spaces;
                        p.entry_pos = entry_pos;
                        return pos - 1;
                    }
                    pstate = 2;
                    spaces = 0;
                    p.entry_buf.as_mut().unwrap()[entry_pos] = c;
                    entry_pos += 1;
                }
            }
            _ => {}
        }
    }

    p.quoted = quoted;
    p.pstate = pstate;
    p.spaces = spaces;
    p.entry_pos = entry_pos;
    pos
}
