use crate::*;
use std::ptr;

pub fn zand(a: &mut z_t, b: &z_t, c: &z_t) {
    let a_ptr = a as *const _ as *const ();
    let b_ptr = b as *const _ as *const ();
    let c_ptr = c as *const _ as *const ();
    
    let mut a_inner = &mut a[0];
    let b_inner = &b[0];
    let c_inner = &c[0];

    if zzero(b) || zzero(c) {
        a_inner.sign = 0;
        return;
    }

    let mut n = if b_inner.used < c_inner.used {
        b_inner.used
    } else {
        c_inner.used
    };

    // Find the highest bit where both b and c have a set bit
    while n > 0 {
        n -= 1;
        if let (Some(b_chars), Some(c_chars)) = (&b_inner.chars, &c_inner.chars) {
            if (b_chars[n] & c_chars[n]) != 0 {
                n += 1; // Adjust back to the correct position
                a_inner.used = n;

                // Handle the three cases (a == b, a == c, or neither)
                if a_ptr == b_ptr {
                    if let Some(a_chars) = &mut a_inner.chars {
                        let c_chars = c_inner.chars.as_ref().unwrap();
                        for i in 0..n {
                            a_chars[i] &= c_chars[i];
                        }
                    }
                } else if a_ptr == c_ptr {
                    if let Some(a_chars) = &mut a_inner.chars {
                        let b_chars = b_inner.chars.as_ref().unwrap();
                        for i in 0..n {
                            a_chars[i] &= b_chars[i];
                        }
                    }
                } else {
                    if a_inner.alloced < a_inner.used {
                        // Temporarily drop the mutable borrow to call libzahl_realloc
                        let need = a_inner.used;
                        drop(a_inner);
                        libzahl_realloc(a, need);
                        a_inner = &mut a[0];
                    }

                    if let (Some(a_chars), Some(c_chars)) = (&mut a_inner.chars, &c_inner.chars) {
                        a_chars[..n].copy_from_slice(&c_chars[..n]);
                        let b_chars = b_inner.chars.as_ref().unwrap();
                        for i in 0..n {
                            a_chars[i] &= b_chars[i];
                        }
                    }
                }

                a_inner.sign = 2 * (((zsignum(b) > 0) || (zsignum(c) > 0)) as i32) - 1;
                return;
            }
        }
    }

    a_inner.sign = 0;
}
