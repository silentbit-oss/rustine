use crate::*;
use std::ptr;

pub fn zor(a: &mut z_t, b: &z_t, c: &z_t) {
    let n: usize;
    let m: usize;
    
    if zzero(b) {
        if zzero(c) {
            a[0].sign = 0;
        } else {
            if !ptr::eq(a, c) {
                zset(a, c);
            }
        }
        return;
    } else if zzero(c) {
        if !ptr::eq(a, b) {
            zset(a, b);
        }
        return;
    }
    
    m = if b[0].used > c[0].used { b[0].used } else { c[0].used };
    n = (b[0].used + c[0].used) - m;
    
    if a[0].alloced < m {
        libzahl_realloc(a, m);
    }
    
    if ptr::eq(a, b) {
        if b[0].used < c[0].used {
            let src = &c[0].chars.as_ref().unwrap()[n..m];
            let dst = &mut a[0].chars.as_mut().unwrap()[n..m];
            dst.copy_from_slice(src);
        }
        for i in 0..n {
            a[0].chars.as_mut().unwrap()[i] |= c[0].chars.as_ref().unwrap()[i];
        }
    } else if ptr::eq(a, c) {
        if c[0].used < b[0].used {
            let src = &b[0].chars.as_ref().unwrap()[n..m];
            let dst = &mut a[0].chars.as_mut().unwrap()[n..m];
            dst.copy_from_slice(src);
        }
        for i in 0..n {
            a[0].chars.as_mut().unwrap()[i] |= b[0].chars.as_ref().unwrap()[i];
        }
    } else if m == b[0].used {
        let src = &b[0].chars.as_ref().unwrap()[..m];
        let dst = &mut a[0].chars.as_mut().unwrap()[..m];
        dst.copy_from_slice(src);
        for i in 0..n {
            a[0].chars.as_mut().unwrap()[i] |= c[0].chars.as_ref().unwrap()[i];
        }
    } else {
        let src = &c[0].chars.as_ref().unwrap()[..m];
        let dst = &mut a[0].chars.as_mut().unwrap()[..m];
        dst.copy_from_slice(src);
        for i in 0..n {
            a[0].chars.as_mut().unwrap()[i] |= b[0].chars.as_ref().unwrap()[i];
        }
    }
    
    a[0].used = m;
    a[0].sign = (((zsignum(b) > 0) as i32 & (zsignum(c) > 0) as i32) * 2 - 1);
}
