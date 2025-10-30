use crate::*;

pub fn zcmpmag(a: &Z, b: &Z) -> i32 {
    if zzero(a) {
        return -(!zzero(b) as i32);
    }
    if zzero(b) {
        return 1;
    }

    let mut i = a.used - 1;
    let mut j = b.used - 1;

    // First loop: compare when i > j
    while i > j {
        if let Some(chars) = &a.chars {
            if chars[i] != 0 {
                return 1;
            }
        }
        i -= 1;
    }

    // Second loop: compare when j > i
    while j > i {
        if let Some(chars) = &b.chars {
            if chars[j] != 0 {
                return -1;
            }
        }
        j -= 1;
    }

    // Third loop: compare when i == j
    while i > 0 {
        let a_char = a.chars.as_ref().map_or(0, |chars| chars[i]);
        let b_char = b.chars.as_ref().map_or(0, |chars| chars[i]);
        
        if a_char != b_char {
            return ((a_char > b_char) as i32 * 2) - 1;
        }
        i -= 1;
    }

    // Final comparison of the first character
    let a_char = a.chars.as_ref().map_or(0, |chars| chars[0]);
    let b_char = b.chars.as_ref().map_or(0, |chars| chars[0]);
    
    if a_char < b_char {
        -1
    } else if a_char > b_char {
        1
    } else {
        0
    }
}
