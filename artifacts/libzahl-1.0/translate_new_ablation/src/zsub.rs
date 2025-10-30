use crate::*;
use crate::types::Z;
use crate::types::z_t;
use crate::types::zahl_char_t;
use crate::zabs;
use crate::zcmpmag;
use crate::zneg;
use crate::zset;
use crate::zzero;
use lazy_static::lazy_static;
use std::ptr;

lazy_static! {
    pub static ref libzahl_tmp_sub: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}

pub fn zsub_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut carry = [0, 0];
    let mut s_slice: Option<Box<[zahl_char_t]>> = None;
    let mut i: usize = 0;
    let n: usize;
    let magcmp: i32;
    
    if zzero(b) {
        zabs(a, c);
        let mut a_copy = Z {
            sign: a[0].sign,
            used: a[0].used,
            alloced: a[0].alloced,
            chars: a[0].chars.clone(),
        };
        let a_copy_arr = [a_copy];
        zneg(a, &a_copy_arr);
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }
    
    magcmp = zcmpmag(b, c);
    
    if magcmp <= 0 {
        if magcmp == 0 {
            a[0].sign = 0;
            return;
        }
        n = if b[0].used < c[0].used { b[0].used } else { c[0].used };
        
        if std::ptr::eq(a, b) {
            let mut tmp_guard = libzahl_tmp_sub.lock().unwrap();
            zset(&mut *tmp_guard, b);
            s_slice = tmp_guard[0].chars.clone();
        } else {
            s_slice = b[0].chars.clone();
        }
        
        if !std::ptr::eq(a, c) {
            zset(a, c);
        }
    } else {
        n = if b[0].used < c[0].used { b[0].used } else { c[0].used };
        
        if std::ptr::eq(a, c) {
            let mut tmp_guard = libzahl_tmp_sub.lock().unwrap();
            zset(&mut *tmp_guard, c);
            s_slice = tmp_guard[0].chars.clone();
        } else {
            s_slice = c[0].chars.clone();
        }
        
        if !std::ptr::eq(a, b) {
            zset(a, b);
        }
    }
    
    let s = s_slice.as_ref().unwrap();
    let a_chars = a[0].chars.as_mut().unwrap();
    for i in 0..n {
        carry[(i.wrapping_neg()) & 1] = if carry[i & 1] != 0 {
            (a_chars[i] <= s[i]) as zahl_char_t
        } else {
            (a_chars[i] < s[i]) as zahl_char_t
        };
        a_chars[i] = a_chars[i].wrapping_sub(s[i]);
        a_chars[i] = a_chars[i].wrapping_sub(carry[i & 1]);
    }
    
    if carry[n & 1] != 0 {
        let mut current_i = n;
        while a_chars[current_i] == 0 {
            a_chars[current_i] = zahl_char_t::MAX;
            current_i += 1;
        }
        a_chars[current_i] -= 1;
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
