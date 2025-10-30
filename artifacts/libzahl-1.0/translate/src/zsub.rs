use crate::*;

pub fn helper_zsub_unsigned_1(
    a_ref: &mut Z,
    s_idx_ref: &mut u32,
    n_ref: &mut usize,
    b: &Z,
    c: &Z,
    magcmp: i32,
) {
    if magcmp == 0 {
        a_ref.sign = 0;
        return;
    }

    *n_ref = if b.used < c.used { b.used } else { c.used };

    let s_idx = if std::ptr::eq(a_ref, b) {
        let mut tmp = libzahl_tmp_sub.lock().unwrap();
        zset(&mut tmp, b);
        tmp.chars.as_ref().map_or(0, |chars| chars.len() as u32)
    } else {
        b.chars.as_ref().map_or(0, |chars| chars.len() as u32)
    };

    if !std::ptr::eq(a_ref, c) {
        zset(a_ref, c);
    }

    *s_idx_ref = s_idx;
}
pub fn zsub_unsigned(a: &mut Z, b: &Z, c: &Z) {
    let mut carry = [0, 0];
    let mut s_idx = 0;
    let mut n = 0; // Initialize n to avoid uninitialized use
    let magcmp;

    if zzero(b) {
        let mut tmp = Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        };
        zabs(&mut tmp, c);
        zneg(a, &tmp);
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }

    magcmp = zcmpmag(b, c);
    if magcmp <= 0 {
        helper_zsub_unsigned_1(a, &mut s_idx, &mut n, b, c, magcmp);
    } else {
        n = if b.used < c.used { b.used } else { c.used };
        if std::ptr::eq(a, c) {
            let mut tmp = libzahl_tmp_sub.lock().unwrap();
            zset(&mut tmp, c);
            s_idx = tmp.chars.as_ref().map_or(0, |chars| chars.len() as u32);
        } else {
            s_idx = c.chars.as_ref().map_or(0, |chars| chars.len() as u32);
        }
        
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    }

    let tmp_guard = if std::ptr::eq(a, c) {
        Some(libzahl_tmp_sub.lock().unwrap())
    } else {
        Option::None
    };
    let s = if std::ptr::eq(a, c) {
        tmp_guard.as_ref().unwrap().chars.as_ref()
    } else {
        c.chars.as_ref()
    };

    if let Some(a_chars) = &mut a.chars {
        if let Some(s_chars) = s {
            for i in 0..n {
                carry[(i ^ 1) & 1] = if carry[i & 1] != 0 {
                    a_chars[i] <= s_chars[i + s_idx as usize]
                } else {
                    a_chars[i] < s_chars[i + s_idx as usize]
                } as u32;
                a_chars[i] = a_chars[i].wrapping_sub(s_chars[i + s_idx as usize]);
                a_chars[i] = a_chars[i].wrapping_sub(carry[i & 1]);
            }

            if carry[n & 1] != 0 {
                let mut i = n;
                while i < a_chars.len() && a_chars[i] == 0 {
                    a_chars[i] = u32::MAX;
                    i += 1;
                }
                if i < a_chars.len() {
                    a_chars[i] = a_chars[i].wrapping_sub(1);
                }
            }
        }
    }

    a.sign = magcmp;
}
pub fn zsub(a: &mut Z, b: &Z, c: &Z) {
    if std::ptr::eq(b, c) {
        a.sign = 0;
    } else if zzero(b) {
        zneg(a, c);
    } else if zzero(c) {
        // Equivalent to the do-while(0) block in C
        if !std::ptr::eq(a, b) {
            zset(a, b);
        }
    } else if (zsignum(b) | zsignum(c)) < 0 {
        if zsignum(b) < 0 {
            if zsignum(c) < 0 {
                zsub_unsigned(a, c, b);
            } else {
                zadd_unsigned(a, b, c);
                a.sign = -zsignum(a);
            }
        } else {
            zadd_unsigned(a, b, c);
        }
    } else {
        zsub_unsigned(a, b, c);
    }
}
