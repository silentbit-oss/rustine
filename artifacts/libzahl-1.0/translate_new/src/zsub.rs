use crate::*;
use lazy_static::lazy_static;
use std::ptr;

pub fn zsub_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut carry = [0, 0];
    let s: &[zahl_char_t];
    let mut s_idx = 0;
    let mut i: usize = 0;
    let n: usize;
    let magcmp: i32;

    if zzero(b) {
        zabs(a, c);
        {
            let temp = [Z {
                sign: a[0].sign,
                used: a[0].used,
                alloced: a[0].alloced,
                chars: a[0].chars.clone(),
            }];
            zneg(a, &temp);
        }
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }

    magcmp = zcmpmag(b, c);
    let tmp_sub = libzahl_tmp_sub.lock().unwrap();
    if magcmp <= 0 {
        if magcmp == 0 {
            a[0].sign = 0;
            return;
        }
        n = if b[0].used < c[0].used { b[0].used } else { c[0].used };
        if a as *const _ == b as *const _ {
            zset(&mut *libzahl_tmp_sub.lock().unwrap(), b);
            s_idx = tmp_sub[0].chars.as_ref().unwrap().len();
            s = tmp_sub[0].chars.as_ref().unwrap();
        } else {
            s_idx = b[0].chars.as_ref().unwrap().len();
            s = b[0].chars.as_ref().unwrap();
        }
        {
            if a as *const _ != c as *const _ {
                zset(a, c);
            }
        }
    } else {
        n = if b[0].used < c[0].used { b[0].used } else { c[0].used };
        if a as *const _ == c as *const _ {
            zset(&mut *libzahl_tmp_sub.lock().unwrap(), c);
            s_idx = tmp_sub[0].chars.as_ref().unwrap().len();
            s = tmp_sub[0].chars.as_ref().unwrap();
        } else {
            s_idx = c[0].chars.as_ref().unwrap().len();
            s = c[0].chars.as_ref().unwrap();
        }
        {
            if a as *const _ != b as *const _ {
                zset(a, b);
            }
        }
    }

    let a_chars = a[0].chars.as_mut().unwrap();
    for i in 0..n {
        carry[(i ^ 1) & 1] = if carry[i & 1] != 0 {
            (a_chars[i] <= s[i + s_idx]) as zahl_char_t
        } else {
            (a_chars[i] < s[i + s_idx]) as zahl_char_t
        };
        a_chars[i] -= s[i + s_idx];
        a_chars[i] -= carry[i & 1];
    }

    if carry[i & 1] != 0 {
        while a_chars[i] == 0 {
            a_chars[i] = u32::MAX;
            i += 1;
        }
        a_chars[i] -= 1;
    }
    a[0].sign = magcmp;
}

pub fn zsub(a: &mut z_t, b: &z_t, c: &z_t) {
    if ptr::eq(b, c) {
        a[0].sign = 0;
    } else if zzero(b) {
        zneg(a, c);
    } else if zzero(c) {
        if !ptr::eq(a, b) {
            zset(a, b);
        }
    } else if (zsignum(b) | zsignum(c)) < 0 {
        if zsignum(b) < 0 {
            if zsignum(c) < 0 {
                zsub_unsigned(a, c, b);
            } else {
                zadd_unsigned(a, b, c);
                a[0].sign = -zsignum(a);
            }
        } else {
            zadd_unsigned(a, b, c);
        }
    } else {
        zsub_unsigned(a, b, c);
    }
}
