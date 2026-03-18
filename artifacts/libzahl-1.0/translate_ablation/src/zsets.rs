use crate::*;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::sync::Mutex;

pub fn zsets(a: &mut z_t, str: Option<&str>) -> Result<(), ()> {
    let c_str = match str {
        Some(s) => s,
        None => {
            unsafe { *libc::__errno_location() = libc::EINVAL };
            return Err(());
        }
    };
    
    let mut temp: u64 = 0;
    let mut neg = false;
    let mut chars = c_str.chars().peekable();
    
    // Check for sign
    if let Some(&first_char) = chars.peek() {
        neg = first_char == '-';
        if first_char == '-' || first_char == '+' {
            chars.next();
        }
    }
    
    // Convert remaining characters to a string
    let remaining_str: String = chars.collect();
    
    // Check if string is empty after sign
    if remaining_str.is_empty() {
        unsafe { *libc::__errno_location() = libc::EINVAL };
        return Err(());
    }
    
    // Validate all characters are digits
    if !remaining_str.chars().all(|c| c.is_ascii_digit()) {
        unsafe { *libc::__errno_location() = libc::EINVAL };
        return Err(());
    }
    
    // Initialize result to zero
    a[0].sign = 0;
    a[0].used = 0;
    if a[0].chars.is_none() {
        a[0].chars = Some(Box::new([0; 1]));
        a[0].alloced = 1;
    }
    
    let len = remaining_str.len();
    let remainder = len % 19;
    let mut idx = 0;
    let digits: Vec<char> = remaining_str.chars().collect();
    
    // Process digits in chunks of up to 19 digits
    while idx < len {
        // Multiply current result by 10^19
        {
            let mut libzahl_const_1e19_guard = libzahl_const_1e19.lock().unwrap();
            let mut temp_b = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zset(&mut temp_b, &*a);
            zmul(a, &mut temp_b, &mut *libzahl_const_1e19_guard);
        }
        
        temp = 0;
        
        // Process next chunk of digits (up to 19 digits)
        let chunk_size = if idx == 0 && remainder != 0 {
            remainder
        } else {
            19
        };
        
        for _ in 0..chunk_size {
            if idx < len {
                let digit_char = digits[idx];
                temp = temp * 10 + (digit_char as u64 - '0' as u64);
                idx += 1;
            }
        }
        
        if temp == 0 {
            continue;
        }
        
        // Store the temporary number
        {
            let mut libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
            let tmp_num = &mut *libzahl_tmp_str_num_guard;
            
            if tmp_num[0].chars.is_none() || tmp_num[0].alloced < 2 {
                tmp_num[0].chars = Some(Box::new([0; 2]));
                tmp_num[0].alloced = 2;
            }
            
            if let Some(ref mut chars) = tmp_num[0].chars {
                chars[0] = (temp & 0xFFFFFFFF) as zahl_char_t;
                chars[1] = (temp >> 32) as zahl_char_t;
            }
            
            tmp_num[0].used = if (temp >> 32) != 0 { 2 } else { 1 };
            tmp_num[0].sign = 0;
            
            // Create temporary copies to avoid borrow conflicts
            let mut temp_a = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zset(&mut temp_a, a);
            zadd(a, &temp_a, &*tmp_num);
        }
    }
    
    if neg {
        a[0].sign = -zsignum(a);
    }
    
    Ok(())
}
