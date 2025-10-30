use crate::*;

pub fn zxor(a: &mut Z, b: &Z, c: &Z) {
    let n;
    let m;
    
    if zzero(b) {
        if zzero(c) {
            a.sign = 0;
        } else {
            if a as *const _ != c as *const _ {
                zset(a, c);
            }
        }
        return;
    } else if zzero(c) {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
        return;
    }
    
    m = if b.used > c.used { b.used } else { c.used };
    n = (b.used + c.used) - m;
    
    {
        if a.alloced < m {
            libzahl_realloc(a, m);
        }
    }
    
    if a as *const _ == b as *const _ {
        if b.used < c.used {
            if let (Some(a_chars), Some(c_chars)) = (a.chars.as_mut(), c.chars.as_ref()) {
                a_chars[n..m].copy_from_slice(&c_chars[n..m]);
            }
        }
        for i in 0..n {
            if let Some(a_chars) = a.chars.as_mut() {
                if let Some(c_chars) = c.chars.as_ref() {
                    a_chars[i] ^= c_chars[i];
                }
            }
        }
    } else if a as *const _ == c as *const _ {
        if c.used < b.used {
            if let (Some(a_chars), Some(b_chars)) = (a.chars.as_mut(), b.chars.as_ref()) {
                a_chars[n..m].copy_from_slice(&b_chars[n..m]);
            }
        }
        for i in 0..n {
            if let Some(a_chars) = a.chars.as_mut() {
                if let Some(b_chars) = b.chars.as_ref() {
                    a_chars[i] ^= b_chars[i];
                }
            }
        }
    } else if m == b.used {
        if let (Some(a_chars), Some(b_chars)) = (a.chars.as_mut(), b.chars.as_ref()) {
            a_chars[..m].copy_from_slice(&b_chars[..m]);
        }
        for i in 0..n {
            if let Some(a_chars) = a.chars.as_mut() {
                if let Some(c_chars) = c.chars.as_ref() {
                    a_chars[i] ^= c_chars[i];
                }
            }
        }
    } else {
        if let (Some(a_chars), Some(c_chars)) = (a.chars.as_mut(), c.chars.as_ref()) {
            a_chars[..m].copy_from_slice(&c_chars[..m]);
        }
        for i in 0..n {
            if let Some(a_chars) = a.chars.as_mut() {
                if let Some(b_chars) = b.chars.as_ref() {
                    a_chars[i] ^= b_chars[i];
                }
            }
        }
    }
    
    a.used = m;
    while a.used > 0 && a.chars.as_ref().map_or(false, |chars| chars[a.used - 1] == 0) {
        a.used -= 1;
    }
    
    if a.used > 0 {
        a.sign = 1 - (2 * ((zsignum(b) ^ zsignum(c)) < 0) as i32);
    } else {
        a.sign = 0;
    }
}
