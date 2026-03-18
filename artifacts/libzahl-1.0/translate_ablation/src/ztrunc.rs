use crate::*;
use std::ptr;

pub fn ztrunc(a: &mut z_t, b: &z_t, mut bits: usize) {
    let mut mask: zahl_char_t = 1;
    let mut chars: usize;
    let mut i: usize;

    if zzero(b) {
        a[0].sign = 0;
        return;
    }

    chars = (bits + (32 - 1)) >> 5;
    a[0].sign = b[0].sign;
    a[0].used = if chars < b[0].used { chars } else { b[0].used };
    if a[0].used < chars {
        bits = 0;
    }

    if !ptr::eq(a, b) {
        if a[0].alloced < a[0].used {
            libzahl_realloc(a, a[0].used);
        }
        
        if let Some(ref b_chars) = b[0].chars {
            if let Some(ref mut a_chars) = a[0].chars {
                a_chars[..a[0].used].copy_from_slice(&b_chars[..a[0].used]);
            } else {
                a[0].chars = Some(b_chars[..a[0].used].to_vec().into_boxed_slice());
            }
        }
    }

    let bits = bits & (32 - 1);
    if bits != 0 {
        mask <<= bits;
        mask -= 1;
        if let Some(ref mut a_chars) = a[0].chars {
            a_chars[a[0].used - 1] &= mask;
        }
    }

    for i in (0..a[0].used).rev() {
        if let Some(ref a_chars) = a[0].chars {
            if a_chars[i] != 0 {
                return;
            }
        }
    }

    a[0].sign = 0;
}
