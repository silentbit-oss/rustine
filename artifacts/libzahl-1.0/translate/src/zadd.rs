use crate::*;

pub fn zadd_unsigned(a: &mut Z, b: &Z, c: &Z) {
    let mut carry = [0u32, 0u32];
    let mut addend_idx = 0usize;
    
    if zzero(b) {
        zabs(a, c);
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }

    let size = if b.used > c.used { b.used } else { c.used };
    let mut n = (b.used + c.used) - size;

    // Ensure allocation is sufficient
    if a.alloced < (size + 1) {
        libzahl_realloc(a, size + 1);
    }

    // Initialize the extra character
    if let Some(chars) = &mut a.chars {
        if chars.len() > size {
            chars[size] = 0;
        }
    }

    // Determine which operand to use as addend and copy data accordingly
    if std::ptr::eq(a, b) {
        if a.used < c.used {
            n = c.used;
            if let Some(chars) = &mut a.chars {
                let start = a.used;
                let end = n;
                chars[start..end].fill(0);
            }
        }
        addend_idx = 0; // Will use c.chars as addend
    } else if std::ptr::eq(a, c) {
        if a.used < b.used {
            n = b.used;
            if let Some(chars) = &mut a.chars {
                let start = a.used;
                let end = n;
                chars[start..end].fill(0);
            }
        }
        addend_idx = 0; // Will use b.chars as addend
    } else if b.used > c.used {
        if let (Some(a_chars), Some(b_chars)) = (&mut a.chars, &b.chars) {
            a_chars[..b.used].copy_from_slice(&b_chars[..b.used]);
        }
        a.used = b.used;
        addend_idx = 0; // Will use c.chars as addend
    } else {
        if let (Some(a_chars), Some(c_chars)) = (&mut a.chars, &c.chars) {
            a_chars[..c.used].copy_from_slice(&c_chars[..c.used]);
        }
        a.used = c.used;
        addend_idx = 0; // Will use b.chars as addend
    }

    // Perform the addition
    let mut i = 0;
    while i < n {
        if let (Some(a_chars), Some(addend_chars)) = (&mut a.chars, &if addend_idx == 0 { c.chars.as_ref() } else { b.chars.as_ref() }) {
            let addend = addend_chars[i + addend_idx];
            if carry[i & 1] != 0 {
                carry[(i ^ 1) & 1] = ((u32::MAX - a_chars[i]) <= addend) as u32;
            } else {
                carry[(i ^ 1) & 1] = ((u32::MAX - a_chars[i]) < addend) as u32;
            }
            a_chars[i] += addend + carry[i & 1];
        }
        i += 1;
    }

    // Handle remaining carry
    while carry[i & 1] != 0 {
        if let Some(chars) = &mut a.chars {
            carry[(i ^ 1) & 1] = (chars[i] == u32::MAX) as u32;
            chars[i] += 1;
        }
        i += 1;
    }

    // Update used count if necessary
    if a.used < i {
        a.used = i;
    }
    a.sign = 1;
}
pub fn zadd(a: &mut Z, b: &Z, c: &Z) {
    if zzero(b) {
        if a as *const _ != c as *const _ {
            zset(a, c);
        }
    } else if zzero(c) {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    } else if b as *const _ == c as *const _ {
        zlsh(a, b, 1);
    } else {
        let b_sign = zsignum(b);
        let c_sign = zsignum(c);
        
        if (b_sign | c_sign) < 0 {
            if b_sign < 0 {
                if c_sign < 0 {
                    zadd_unsigned(a, b, c);
                    a.sign = -zsignum(a);
                } else {
                    zsub_unsigned(a, c, b);
                }
            } else {
                zsub_unsigned(a, b, c);
            }
        } else {
            zadd_unsigned(a, b, c);
        }
    }
}
