use crate::*;
use std::ptr;

pub fn zrsh(a: &mut z_t, b: &z_t, bits: usize) {
    if bits == 0 {
        if !ptr::eq(a, b) {
            zset(a, b);
        }
        return;
    }

    let chars = bits >> 5;
    if zzero(b) || chars >= b[0].used || {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        temp[0] = Z {
            sign: b[0].sign,
            used: b[0].used,
            alloced: b[0].alloced,
            chars: b[0].chars.clone(),
        };
        zbits(&mut temp) <= bits
    } {
        a[0].sign = 0;
        return;
    }

    let bits = bits & (32 - 1);
    let cbits = 32 - bits;

    if chars > 0 && ptr::eq(a, b) {
        a[0].used -= chars;
        if let Some(ref mut a_chars) = a[0].chars {
            let (dst, src) = a_chars.split_at_mut(chars);
            dst[..a[0].used].copy_from_slice(&src[..a[0].used]);
        }
    } else if !ptr::eq(a, b) {
        a[0].used = b[0].used - chars;
        if a[0].alloced < a[0].used {
            libzahl_realloc(a, a[0].used);
        }
        if let (Some(ref mut a_chars), Some(ref b_chars)) = (&mut a[0].chars, &b[0].chars) {
            a_chars[..a[0].used].copy_from_slice(&b_chars[chars..chars + a[0].used]);
        }
    }

    if bits > 0 {
        if let Some(ref mut a_chars) = a[0].chars {
            a_chars[0] >>= bits;
            for i in 1..a[0].used {
                a_chars[i - 1] |= a_chars[i] << cbits;
                a_chars[i] >>= bits;
            }

            while a_chars[a[0].used - 1] == 0 {
                a[0].used -= 1;
            }
        }
    }

    a[0].sign = zsignum(b);
}
