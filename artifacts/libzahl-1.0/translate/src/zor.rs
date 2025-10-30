use crate::*;

pub fn zor(a: &mut Z, b: &Z, c: &Z) {
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
        if let (Some(a_chars), Some(c_chars)) = (a.chars.as_mut(), c.chars.as_ref()) {
            for i in 0..n {
                a_chars[i] |= c_chars[i];
            }
        }
    } else if a as *const _ == c as *const _ {
        if c.used < b.used {
            if let (Some(a_chars), Some(b_chars)) = (a.chars.as_mut(), b.chars.as_ref()) {
                a_chars[n..m].copy_from_slice(&b_chars[n..m]);
            }
        }
        if let (Some(a_chars), Some(b_chars)) = (a.chars.as_mut(), b.chars.as_ref()) {
            for i in 0..n {
                a_chars[i] |= b_chars[i];
            }
        }
    } else if m == b.used {
        if let (Some(a_chars), Some(b_chars)) = (a.chars.as_mut(), b.chars.as_ref()) {
            a_chars[..m].copy_from_slice(&b_chars[..m]);
            for i in 0..n {
                a_chars[i] |= c.chars.as_ref().map_or(0, |c_chars| c_chars[i]);
            }
        }
    } else {
        if let (Some(a_chars), Some(c_chars)) = (a.chars.as_mut(), c.chars.as_ref()) {
            a_chars[..m].copy_from_slice(&c_chars[..m]);
            for i in 0..n {
                a_chars[i] |= b.chars.as_ref().map_or(0, |b_chars| b_chars[i]);
            }
        }
    }
    
    a.used = m;
    a.sign = (((zsignum(b) > 0) && (zsignum(c) > 0)) as i32) * 2 - 1;
}
