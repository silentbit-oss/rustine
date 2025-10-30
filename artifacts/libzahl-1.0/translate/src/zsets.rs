use crate::*;

pub fn zsets(a: &mut Z, str: Option<&str>) -> Result<(), std::io::Error> {
    let str = str.ok_or_else(|| std::io::Error::new(std::io::ErrorKind::InvalidInput, "NULL pointer"))?;
    let mut str_idx = 0;
    let mut temp: u64 = 0;
    let neg = str.chars().next() == Some('-');
    
    // Skip sign if present
    if neg || str.chars().next() == Some('+') {
        str_idx += 1;
    }
    
    // Check if string is empty after sign
    if str_idx >= str.len() {
        return Err(std::io::Error::new(std::io::ErrorKind::InvalidInput, "empty string"));
    }
    
    // Validate all remaining characters are digits
    if !str[str_idx..].chars().all(|c| c.is_ascii_digit()) {
        return Err(std::io::Error::new(std::io::ErrorKind::InvalidInput, "non-digit characters"));
    }
    
    a.sign = 0;
    {
        let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
        let libzahl_const_1e19 = LIBZAHL_CONST_1E19.lock().unwrap();
        zset(&mut *libzahl_tmp_str_num, &*libzahl_const_1e19);
    }
    
    let chunk_size = 19;
    let mut chars = str[str_idx..].chars();
    
    while let Some(c) = chars.next() {
        {
            let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
            let mut tmp = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp, a);
            zmul(a, &mut tmp, &mut *libzahl_tmp_str_num);
        }
        
        temp = 0;
        let mut count = 0;
        
        // Process up to 19 digits at a time
        temp = temp * 10 + (c as u64 - b'0' as u64);
        count += 1;
        
        for _ in 1..chunk_size {
            if let Some(c) = chars.next() {
                temp = temp * 10 + (c as u64 - b'0' as u64);
                count += 1;
            } else {
                break;
            }
        }
        
        if temp == 0 {
            continue;
        }
        
        {
            let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
            libzahl_tmp_str_num.chars = Some(vec![(temp & 0xFFFFFFFF) as u32, (temp >> 32) as u32].into_boxed_slice());
            libzahl_tmp_str_num.used = 1 + (temp >> 32 != 0) as usize;
            let tmp_num = Z {
                sign: libzahl_tmp_str_num.sign,
                used: libzahl_tmp_str_num.used,
                alloced: libzahl_tmp_str_num.alloced,
                chars: libzahl_tmp_str_num.chars.clone(),
            };
            zadd(a, &tmp_num, &*libzahl_tmp_str_num);
        }
    }
    
    if neg {
        a.sign = -zsignum(a);
    }
    
    Ok(())
}
