use crate::*;
use std::ffi::CStr;
use std::ffi::CString;
use std::ffi::c_void;
use std::os::raw::c_char;
use std::ptr;

pub fn _mi_toupper(c: char) -> char {
    if c >= 'a' && c <= 'z' {
        ((c as u8) - b'a' + b'A') as char
    } else {
        c
    }
}
pub fn _mi_strlcpy(dest: &mut [u8], src: &[u8]) {
    if dest.is_empty() || src.is_empty() {
        return;
    }
    
    let mut src_idx = 0;
    let mut dest_idx = 0;
    let mut remaining = dest.len();
    
    while src_idx < src.len() && src[src_idx] != 0 && remaining > 1 {
        dest[dest_idx] = src[src_idx];
        src_idx += 1;
        dest_idx += 1;
        remaining -= 1;
    }
    
    if dest_idx < dest.len() {
        dest[dest_idx] = 0;
    }
}
pub fn _mi_strlen(s: Option<&str>) -> usize {
    match s {
        Some(str_ref) => str_ref.len(),
        None => 0,
    }
}
pub fn _mi_strnlen(s: Option<&str>, max_len: usize) -> usize {
    if s.is_none() {
        return 0;
    }
    
    let s = s.unwrap();
    let mut len = 0;
    
    for c in s.chars().take(max_len) {
        len += 1;
    }
    
    len
}
pub fn mi_outc(c: char, out: &mut Option<&mut [u8]>, end: usize) {
    if let Some(buffer) = out {
        if buffer.len() > end {
            let p = &mut buffer[end];
            *p = c as u8;
        }
    }
}

pub fn mi_outs(s: Option<&str>, out: &mut Option<&mut [u8]>, end: *const u8) {
    let s = match s {
        Some(s) => s,
        None => return,
    };
    
    let out_slice = match out.take() {
        Some(slice) => slice,
        None => return,
    };
    
    let mut s_bytes = s.as_bytes();
    let mut p_bytes = out_slice;
    
    // Calculate how many bytes we can safely copy
    let p_start = p_bytes.as_ptr();
    let bytes_available = unsafe { end.offset_from(p_start) } as usize;
    let bytes_to_copy = s_bytes.len().min(bytes_available).min(p_bytes.len());
    
    if bytes_to_copy > 0 {
        p_bytes[..bytes_to_copy].copy_from_slice(&s_bytes[..bytes_to_copy]);
        
        // Update the output slice to point after the copied data
        let remaining_slice = &mut p_bytes[bytes_to_copy..];
        *out = Some(remaining_slice);
    } else {
        *out = Some(p_bytes);
    }
}
pub fn mi_out_fill(fill: char, len: usize, out: &mut &mut [u8], end: *mut u8) {
    let out_ptr = *out as *mut [u8] as *mut u8;
    let mut p_idx = 0;
    
    for i in 0..len {
        let current_ptr = unsafe { out_ptr.add(p_idx) };
        if current_ptr >= end {
            break;
        }
        
        unsafe {
            *current_ptr = fill as u8;
        }
        p_idx += 1;
    }
    
    unsafe {
        *out = std::slice::from_raw_parts_mut(out_ptr.add(p_idx), (*out).len() - p_idx);
    }
}
pub fn mi_out_alignright(fill: char, start: &mut [u8], len: usize, extra: usize, end: usize) {
    if len == 0 || extra == 0 {
        return;
    }
    if (len + extra) >= end {
        return;
    }
    
    for i in 1..=len {
        let src_idx = len - i;
        let dst_idx = (len + extra) - i;
        start[dst_idx] = start[src_idx];
    }
    
    for i in 0..extra {
        start[i] = fill as u8;
    }
}
pub fn mi_byte_sum64(x: u64) -> usize {
    let mut x = x;
    x += x << 8;
    x += x << 16;
    x += x << 32;
    (x >> 56) as usize
}
pub fn helper_helper_helper__mi_vsnprintf_1_1_1(
    in_idx_ref: &mut u32,
    c_ref: &mut char,
    numtype_ref: &mut char,
    in_str: &str,
) {
    let mut in_idx = *in_idx_ref;
    let mut c = *c_ref;
    let mut numtype = *numtype_ref;
    
    numtype = c;
    
    if let Some(ch) = in_str.chars().nth(in_idx as usize) {
        c = ch;
    } else {
        return;
    }
    
    if c == '\0' {
        return;
    }
    
    in_idx += 1;
    
    if c == 'l' {
        numtype = 'L';
        
        if let Some(ch) = in_str.chars().nth(in_idx as usize) {
            c = ch;
        } else {
            *in_idx_ref = in_idx;
            *c_ref = c;
            *numtype_ref = numtype;
            return;
        }
        
        if c == '\0' {
            *in_idx_ref = in_idx;
            *c_ref = c;
            *numtype_ref = numtype;
            return;
        }
        
        in_idx += 1;
    }
    
    *in_idx_ref = in_idx;
    *c_ref = c;
    *numtype_ref = numtype;
}
pub fn helper_helper_helper__mi_vsnprintf_1_1_3(
    in_idx_ref: &mut u32,
    c_ref: &mut char,
    width_ref: &mut usize,
    in_str: &str,
) {
    let mut in_idx = *in_idx_ref;
    let mut c = *c_ref;
    let mut width = *width_ref;
    
    width = (c as u8 - b'0') as usize;
    
    if let Some(next_char) = in_str.chars().nth(in_idx as usize) {
        c = next_char;
    } else {
        return;
    }
    
    if c == '\0' {
        return;
    }
    
    in_idx += 1;
    
    while c >= '0' && c <= '9' {
        width = (10 * width) + (c as u8 - b'0') as usize;
        
        if let Some(next_char) = in_str.chars().nth(in_idx as usize) {
            c = next_char;
        } else {
            break;
        }
        
        if c == '\0' {
            break;
        }
        
        in_idx += 1;
    }
    
    if c == '\0' {
        return;
    }
    
    *in_idx_ref = in_idx;
    *c_ref = c;
    *width_ref = width;
}
pub fn mi_out_num(x: u64, base: usize, prefix: char, out: &mut Option<&mut [u8]>, end: usize) {
    if x == 0 || base == 0 || base > 16 {
        if prefix != '\0' {
            mi_outc(prefix, out, end);
        }
        mi_outc('0', out, end);
    } else {
        let start_index = match out {
            Some(slice) => slice.len(),
            None => return,
        };
        
        let mut x_temp = x;
        while x_temp > 0 {
            let digit = (x_temp % base as u64) as u8;
            let c = if digit <= 9 {
                (b'0' + digit) as char
            } else {
                (b'A' + digit - 10) as char
            };
            mi_outc(c, out, end);
            x_temp /= base as u64;
        }

        if prefix != '\0' {
            mi_outc(prefix, out, end);
        }

        if let Some(slice) = out {
            let current_len = slice.len();
            let len = current_len - start_index;
            for i in 0..len / 2 {
                let left_idx = start_index + i;
                let right_idx = start_index + (len - i - 1);
                slice.swap(left_idx, right_idx);
            }
        }
    }
}
pub fn helper_helper_helper__mi_vsnprintf_1_1_4(
    fill_ref: &mut char,
    width_ref: &mut usize,
    start_idx_ref: &mut usize,
    x_val: u64,  // Changed from VaList to direct value
    end: usize,
    out: &mut Option<&mut [u8]>,
    c: char,
    numtype: char,
    numplus: char,
) {
    let mut fill = *fill_ref;
    let mut width = *width_ref;
    let mut start_idx = *start_idx_ref;
    let mut x: u64 = x_val;  // Use the passed value
    
    if c == 'p' {
        mi_outs(Some("0x"), out, end as *const u8);
        // In the original C: start_idx = out; 
        // This means we need to track the current position in the output buffer
        // Since we can't directly get the pointer from Option<&mut [u8]>, 
        // we'll simulate the position advancement
        start_idx += 2; // "0x" is 2 characters
        width = if width >= 2 { width - 2 } else { 0 };
    }
    
    if width == 0 && (c == 'x' || c == 'p') {
        if c == 'p' {
            width = if x <= u32::MAX as u64 {
                8  // 2 * 4 (for 32-bit pointers)
            } else if (x >> 16) <= u32::MAX as u64 {
                12 // 2 * 6 (for 48-bit pointers)
            } else {
                std::mem::size_of::<*const ()>() * 2  // Full pointer size
            };
        }
        if width == 0 {
            width = 2;
        }
        fill = '0';
    }
    
    mi_out_num(x, if c == 'x' || c == 'p' { 16 } else { 10 }, numplus, out, end);
    
    *fill_ref = fill;
    *width_ref = width;
    *start_idx_ref = start_idx;
}
pub fn helper_helper_helper__mi_vsnprintf_1_1_2(
    mut args: *mut std::ffi::c_void,
    end: usize,
    out: &mut Option<&mut [u8]>,
    numtype: char,
    numplus: char,
) {
    let mut x: i64 = 0;
    
    // Extract the appropriate type based on numtype
    unsafe {
        match numtype {
            'z' => {
                // size_t - typically usize
                let arg_ptr = args as *mut usize;
                x = *arg_ptr as i64;
                args = arg_ptr.add(1) as *mut std::ffi::c_void;
            }
            't' => {
                // ptrdiff_t - typically isize  
                let arg_ptr = args as *mut isize;
                x = *arg_ptr as i64;
                args = arg_ptr.add(1) as *mut std::ffi::c_void;
            }
            'L' => {
                // long long - use i64
                let arg_ptr = args as *mut i64;
                x = *arg_ptr;
                args = arg_ptr.add(1) as *mut std::ffi::c_void;
            }
            'l' => {
                // long - use i32 or i64 depending on platform, but i64 is safer
                let arg_ptr = args as *mut i64;
                x = *arg_ptr;
                args = arg_ptr.add(1) as *mut std::ffi::c_void;
            }
            _ => {
                // Default to i32 for other types (int)
                let arg_ptr = args as *mut i32;
                x = *arg_ptr as i64;
                args = arg_ptr.add(1) as *mut std::ffi::c_void;
            }
        }
    }
    
    let mut pre: char = '\0';
    if x < 0 {
        pre = '-';
        // Check for the most negative value to avoid overflow
        // Original C code: if (x > INTMAX_MIN) - but we need to handle i64::MIN
        if x != i64::MIN {
            x = -x;
        }
    } else if numplus != '\0' {
        pre = numplus;
    }
    
    mi_out_num(x as u64, 10, pre, out, end);
}
pub unsafe extern "C" fn _mi_snprintf(buf: *mut u8, buflen: usize, fmt: *const u8, mut args: *mut std::ffi::c_void) -> i32 {
    let written = _mi_vsnprintf(
        if buf.is_null() {
            Option::None
        } else {
            Some(std::slice::from_raw_parts_mut(buf, buflen))
        },
        buflen,
        if fmt.is_null() {
            Option::None
        } else {
            Some(std::slice::from_raw_parts(fmt, std::ffi::CStr::from_ptr(fmt as *const i8).to_bytes().len()))
        },
        &mut args
    );
    written
}
pub fn _mi_strnicmp(s: &str, t: &str, n: usize) -> i32 {
    if n == 0 {
        return 0;
    }
    
    let s_chars: Vec<char> = s.chars().collect();
    let t_chars: Vec<char> = t.chars().collect();
    
    let mut t_idx = 0;
    let mut s_idx = 0;
    let mut remaining = n;
    
    while s_idx < s_chars.len() && t_idx < t_chars.len() && remaining > 0 {
        let s_char = s_chars[s_idx];
        let t_char = t_chars[t_idx];
        
        if _mi_toupper(s_char) != _mi_toupper(t_char) {
            break;
        }
        
        s_idx += 1;
        t_idx += 1;
        remaining -= 1;
    }
    
    if remaining == 0 {
        0
    } else if s_idx >= s_chars.len() && t_idx >= t_chars.len() {
        0
    } else if s_idx >= s_chars.len() {
        -1
    } else if t_idx >= t_chars.len() {
        1
    } else {
        let s_char = s_chars[s_idx] as i32;
        let t_char = t_chars[t_idx] as i32;
        s_char - t_char
    }
}
pub fn _mi_getenv(name: Option<&str>, result: &mut [u8], result_size: usize) -> bool {
    if name.is_none() || result.is_empty() || result_size < 64 {
        return false;
    }
    _mi_prim_getenv(name, result, result_size)
}
pub fn _mi_strlcat(dest: &mut [u8], src: &[u8], dest_size: usize) {
    if dest.is_empty() || src.is_empty() || dest_size == 0 {
        return;
    }
    
    let mut dest_idx = 0;
    let mut remaining_size = dest_size;
    
    while dest_idx < dest.len() && dest[dest_idx] != 0 && remaining_size > 1 {
        dest_idx += 1;
        remaining_size -= 1;
    }
    
    _mi_strlcpy(&mut dest[dest_idx..], src);
}
pub fn mi_popcount_generic64(x: u64) -> usize {
    let mut x = x;
    x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
    mi_byte_sum64(x)
}
pub fn _mi_popcount_generic(x: u64) -> usize {
    mi_popcount_generic64(x)
}
