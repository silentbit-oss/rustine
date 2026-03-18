use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;

pub fn zsets(a: &mut z_t, str: Option<&str>) -> Result<(), i32> {
    let str = match str {
        Some(s) => s,
        None => {
            return Err(-1);
        }
    };

    let mut str_idx = 0;
    let mut temp: u64 = 0;
    let neg = str.chars().nth(str_idx) == Some('-');
    
    // Skip optional sign
    str_idx += if neg || str.chars().nth(str_idx) == Some('+') { 1 } else { 0 };

    // Check if string is empty after sign
    if str_idx >= str.len() {
        return Err(-1);
    }

    // Validate all remaining characters are digits
    if !str[str_idx..].chars().all(|c| c.is_ascii_digit()) {
        return Err(-1);
    }

    a[0].sign = 0;
    zset(a, &libzahl_const_1e19.lock().unwrap());

    let chunk_size = (str.len() - str_idx) % 19;
    let mut chars = str[str_idx..].chars();

    loop {
        let tmp_const = libzahl_const_1e19.lock().unwrap();
        let mut local_const = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
        zset(&mut local_const, &tmp_const);
        let mut local_a = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
        zset(&mut local_a, a);
        zmul(a, &mut local_a, &mut local_const);

        temp = 0;

        // Process digits in chunks of up to 19 characters
        for _ in 0..chunk_size {
            if let Some(c) = chars.next() {
                temp = temp * 10 + (c.to_digit(10).unwrap() as u64);
            } else {
                break;
            }
        }

        if temp == 0 {
            if chars.clone().count() == 0 {
                break;
            }
            continue;
        }

        {
            let mut tmp_num = libzahl_tmp_str_num.lock().unwrap();
            tmp_num[0].chars = Some(Box::new([(temp & 0xFFFFFFFF) as zahl_char_t, (temp >> 32) as zahl_char_t]));
            tmp_num[0].used = 1 + if (temp >> 32) != 0 { 1 } else { 0 };
        }

        let tmp_num_guard = libzahl_tmp_str_num.lock().unwrap();
        let mut local_a2 = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
        zset(&mut local_a2, a);
        zadd(a, &local_a2, &tmp_num_guard);

        if chars.clone().count() == 0 {
            break;
        }
    }

    if neg {
        a[0].sign = -zsignum(a);
    }

    Ok(())
}
