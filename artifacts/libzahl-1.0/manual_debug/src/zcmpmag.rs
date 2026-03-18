use crate::*;
use rand::Rng;


pub fn zcmpmag(a: &mut z_t, b: &mut z_t) -> i32 {
    if zzero(a) {
        return -(!zzero(b) as i32);
    }
    if zzero(b) {
        return 1;
    }
    
    if a[0].used == 0 || b[0].used == 0 {
        return 0;
    }
    let mut i = a[0].used - 1;
    let mut j = b[0].used - 1;

    while i > j {
        if let Some(chars) = &a[0].chars {
            if chars[i] != 0 {
                return 1;
            }
        }
        // In Rust, we can't modify a.used directly since we have an immutable borrow
        // This is a limitation of the safe translation - we'll need to skip this line
        a[0].used -= 1;
        i -= 1;
    }

    while j > i {
        if let Some(chars) = &b[0].chars {
            if chars[j] != 0 {
                return -1;
            }
        }
        // Similarly, can't modify b.used here
        b[0].used -= 1;
        j -= 1;
    }

    while i > 0 {
        let a_char = a[0].chars.as_ref().map_or(0, |chars| chars[i]);
        let b_char = b[0].chars.as_ref().map_or(0, |chars| chars[i]);
        
        if a_char != b_char {
            return ((a_char > b_char) as i32 * 2) - 1;
        }
        i -= 1;
    }

    let a_char = a[0].chars.as_ref().map_or(0, |chars| chars[0]);
    let b_char = b[0].chars.as_ref().map_or(0, |chars| chars[0]);

    if a_char < b_char {
        -1
    } else if a_char > b_char {
        1
    } else {
        0
    }
}
