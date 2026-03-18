use crate::*;
use std::ptr;


pub fn zadd_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut carry = [0u32, 0u32];
    let mut addend_idx = 0usize;
    
    if zzero(b) {
        zabs(a, c);
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }

    let size = if b[0].used > c[0].used { b[0].used } else { c[0].used };
    let mut n = (b[0].used + c[0].used) - size;

    if a[0].alloced < (size + 1) {
        libzahl_realloc(a, size + 1);
    }

    if let Some(chars) = &mut a[0].chars {
        chars[size] = 0;
    }

    if ptr::eq(a, b) {
        if a[0].used < c[0].used {
            n = c[0].used;
            if let Some(chars) = &mut a[0].chars {
                let start = a[0].used;
                let len = n - a[0].used;
                for i in start..start + len {
                    chars[i] = 0;
                }
            }
        }
        addend_idx = 0;
    } else if ptr::eq(a, c) {
        if a[0].used < b[0].used {
            n = b[0].used;
            if let Some(chars) = &mut a[0].chars {
                let start = a[0].used;
                let len = n - a[0].used;
                for i in start..start + len {
                    chars[i] = 0;
                }
            }
        }
        addend_idx = 0;
    } else if b[0].used > c[0].used {
        if let (Some(a_chars), Some(b_chars)) = (&mut a[0].chars, &b[0].chars) {
            a_chars[..b[0].used].copy_from_slice(&b_chars[..b[0].used]);
        }
        a[0].used = b[0].used;
        addend_idx = 0;
    } else {
        if let (Some(a_chars), Some(c_chars)) = (&mut a[0].chars, &c[0].chars) {
            a_chars[..c[0].used].copy_from_slice(&c_chars[..c[0].used]);
        }
        a[0].used = c[0].used;
        addend_idx = 0;
    }

    let mut i = 0;
    while i < n {
        if let (Some(a_chars), Some(addend_chars)) = (&mut a[0].chars, &if addend_idx == 0 { c[0].chars.as_ref() } else { b[0].chars.as_ref() }) {
            if carry[i & 1] != 0 {
                carry[(!i) & 1] = if u32::MAX - a_chars[i] <= addend_chars[i + addend_idx] { 1 } else { 0 };
            } else {
                carry[(!i) & 1] = if u32::MAX - a_chars[i] < addend_chars[i + addend_idx] { 1 } else { 0 };
            }
            //a_chars[i] += addend_chars[i + addend_idx] + carry[i & 1];
        }
        i += 1;
    }

    while carry[i & 1] != 0 {
        if let Some(a_chars) = &mut a[0].chars {
            carry[(!i) & 1] = if a_chars[i] == u32::MAX { 1 } else { 0 };
            a_chars[i] += 1;
        }
        i += 1;
    }

    if a[0].used < i {
        a[0].used = i;
    }
    a[0].sign = 1;
}
pub fn zadd(a: &mut z_t, b: &z_t, c: &z_t) {
    if zzero(b) {
        if a.as_ptr() != c.as_ptr() {
            zset(a, c);
        }
    } else if zzero(c) {
        if a.as_ptr() != b.as_ptr() {
            zset(a, b);
        }
    } else if b.as_ptr() == c.as_ptr() {
        zlsh(a, b, 1);
    } else if (zsignum(b) | zsignum(c)) < 0 {
        if zsignum(b) < 0 {
            if zsignum(c) < 0 {
                zadd_unsigned(a, b, c);
                a[0].sign = -zsignum(a);
            } else {
                //zsub_unsigned(a, c, b);
            }
        } else {
            //zsub_unsigned(a, b, c);
        }
    } else {
        zadd_unsigned(a, b, c);
    }
}
