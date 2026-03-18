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
use std::ptr::null_mut;
use std::ptr;

pub fn csv_write2(dest: Option<&mut [u8]>, src: Option<&[u8]>, quote: u8) -> usize {
    let Some(src) = src else {
        return 0;
    };
    
    let mut chars = 0;
    let dest_size = dest.as_ref().map(|d| d.len()).unwrap_or(0);
    let mut dest_iter = dest.map(|d| d.iter_mut());

    // Write opening quote
    if dest_size > chars {
        if let Some(dest_byte) = dest_iter.as_mut().and_then(|iter| iter.next()) {
            *dest_byte = quote;
        }
    }
    chars += 1;

    // Process each source byte
    for &src_byte in src {
        if src_byte == quote {
            // Double the quote
            if dest_size > chars {
                if let Some(dest_byte) = dest_iter.as_mut().and_then(|iter| iter.next()) {
                    *dest_byte = quote;
                }
            }
            chars = chars.saturating_add(1);
        }

        // Write the source byte
        if dest_size > chars {
            if let Some(dest_byte) = dest_iter.as_mut().and_then(|iter| iter.next()) {
                *dest_byte = src_byte;
            }
        }
        chars = chars.saturating_add(1);
    }

    // Write closing quote
    if dest_size > chars {
        if let Some(dest_byte) = dest_iter.as_mut().and_then(|iter| iter.next()) {
            *dest_byte = quote;
        }
    }
    chars = chars.saturating_add(1);

    chars
}

pub fn csv_fwrite2(
    file: &mut std::fs::File,
    src: Option<&[u8]>,
    src_size: usize,
    quote: u8,
) -> std::io::Result<()> {
    if let Some(src) = src {
        // Write opening quote
        file.write_all(&[quote])?;

        for &byte in src.iter().take(src_size) {
            if byte == quote {
                // Write escaped quote
                file.write_all(&[quote])?;
            }
            file.write_all(&[byte])?;
        }

        // Write closing quote
        file.write_all(&[quote])?;
        Ok(())
    } else {
        // If src is None, treat it as an error
        Err(std::io::Error::new(std::io::ErrorKind::InvalidInput, "src is None"))
    }
}
pub fn csv_init(p: &mut CsvParser, options: u8) -> i32 {
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
    if p.entry_buf.is_some() && p.free_func != CsvParser::default().free_func {
        if let Some(buf) = p.entry_buf.take() {
            let ptr = Box::into_raw(buf.into_boxed_slice()) as *mut u8;
            (p.free_func)(ptr);
        }
    }
    p.entry_size = 0;
}
pub fn csv_error(p: &CsvParser) -> i32 {
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
    if status >= 4 || status < 0 {
        &CSV_ERRORS[4]
    } else {
        &CSV_ERRORS[status as usize]
    }
}
pub fn csv_write(dest: Option<&mut [u8]>, src: Option<&[u8]>) -> usize {
    csv_write2(dest, src, 0x22)
}

pub fn csv_fwrite(fp: &mut File, src: Option<&[u8]>, src_size: usize) -> std::io::Result<()> {
    csv_fwrite2(fp, src, src_size, 0x22)
}
pub fn csv_get_opts(p: Option<&CsvParser>) -> i32 {
    // Check if the reference is None (equivalent to NULL check in C)
    if p.is_none() {
        return -1;
    }
    
    // Safe to unwrap since we checked for None
    p.unwrap().options as i32
}
pub fn csv_set_opts(p: Option<&mut CsvParser>, options: u8) -> i32 {
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
    if let Some(parser) = p {
        parser.delim_char = c;
    }
}
pub fn csv_set_quote(p: Option<&mut CsvParser>, c: u8) {
    if let Some(parser) = p {
        parser.quote_char = c;
    }
}
pub fn csv_get_delim(p: Option<&CsvParser>) -> Option<u8> {
    // Use Option<&CsvParser> to handle NULL pointer case
    let p = p?; // Early return if p is None (equivalent to assert in C)
    Some(p.delim_char)
}

pub fn csv_get_quote(p: Option<&CsvParser>) -> Option<u8> {
    assert!(p.is_some(), "received null csv_parser");
    Some(p.unwrap().quote_char)
}
pub fn csv_set_space_func(p: Option<&mut CsvParser>, f: Option<fn(u8) -> i32>) {
    if let Some(p) = p {
        p.is_space = f;
    }
}
pub fn csv_set_term_func(p: Option<&mut CsvParser>, f: Option<fn(u8) -> i32>) {
    if let Some(p) = p {
        p.is_term = f;
    }
}
pub fn csv_set_realloc_func(p: Option<&mut CsvParser>, f: Option<fn(*mut u8, usize) -> *mut u8>) {
    if let (Some(p), Some(f)) = (p, f) {
        p.realloc_func = f;
    }
}
pub fn csv_set_free_func(p: Option<&mut CsvParser>, f: Option<fn(*mut u8)>) {
    if let (Some(p), Some(f)) = (p, f) {
        p.free_func = f;
    }
}
pub fn csv_set_blk_size(p: Option<&mut CsvParser>, size: usize) {
    if let Some(p) = p {
        p.blk_size = size;
    }
}
pub fn csv_get_buffer_size(p: Option<&CsvParser>) -> usize {
    // Use pattern matching to handle the Option
    match p {
        Some(parser) => parser.entry_size,
        None => 0,
    }
}


pub fn csv_increase_buffer(p: &mut CsvParser) -> i32 {
    if p.realloc_func as usize == 0 {
        return 0;
    }
    
    let mut to_add = p.blk_size;
    
    if p.entry_size >= (usize::MAX - to_add) {
        to_add = usize::MAX - p.entry_size;
    }
    
    if to_add == 0 {
        p.status = 3;
        return -1;
    }
    
    let mut vp = null_mut();
    let mut current_to_add = to_add;
    
    while {
        let entry_buf_ptr = match &p.entry_buf {
            Some(buf) => buf.as_ptr() as *mut u8,
            None => null_mut(),
        };
        
        vp = (p.realloc_func)(entry_buf_ptr, p.entry_size + current_to_add);
        vp.is_null()
    } {
        current_to_add /= 2;
        if current_to_add == 0 {
            p.status = 2;
            return -1;
        }
    }
    
    unsafe {
        let new_size = p.entry_size + current_to_add;
        let new_vec = Vec::from_raw_parts(vp, new_size, new_size);
        p.entry_buf = Some(new_vec);
    }
    
    p.entry_size += current_to_add;
    0
}
pub fn csv_fini(
    p: &mut CsvParser,
    cb1: Option<unsafe fn(Option<&[u8]>, usize, Option<&str>)>,
    cb2: Option<unsafe fn(i32, *mut c_void)>,
    data: Option<&str>,
) -> i32 {
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
                            cb2.unwrap()(c as i32, ptr::null_mut());
                        }
                        pstate = 0;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    } else if (p.options & 2) != 0 {
                        if cb2.is_some() {
                            cb2.unwrap()(c as i32, ptr::null_mut());
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
                            cb2.unwrap()(c as i32, ptr::null_mut());
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
                        cb2.unwrap()(c as i32, ptr::null_mut());
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
