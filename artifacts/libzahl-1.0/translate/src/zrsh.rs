use crate::*;

pub fn zrsh(a: &mut Z, b: &Z, bits: usize) {
    if bits == 0 {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
        return;
    }

    let chars = bits >> 5;
    let mut b_clone = Z {
        sign: b.sign,
        used: b.used,
        alloced: b.alloced,
        chars: b.chars.as_ref().map(|c| {
            let vec = c.to_vec();
            vec.into_boxed_slice()
        }),
    };
    if zzero(b) || chars >= b.used || zbits(&mut b_clone) <= bits {
        a.sign = 0;
        a.used = 0;
        a.chars = Option::None;
        return;
    }

    let bits = bits & (32 - 1);
    let cbits = 32 - bits;

    if chars > 0 && a as *const _ == b as *const _ {
        a.used -= chars;
        if let Some(chars_ref) = &mut a.chars {
            let (dest, src) = chars_ref.split_at_mut(chars);
            dest[..a.used].copy_from_slice(&src[..a.used]);
        }
    } else if a as *const _ != b as *const _ {
        a.used = b.used - chars;
        if a.alloced < a.used {
            libzahl_realloc(a, a.used);
        }
        if let Some(b_chars) = &b.chars {
            if let Some(a_chars) = &mut a.chars {
                a_chars[..a.used].copy_from_slice(&b_chars[chars..chars + a.used]);
            } else {
                let mut new_chars = vec![0; a.used].into_boxed_slice();
                new_chars.copy_from_slice(&b_chars[chars..chars + a.used]);
                a.chars = Some(new_chars);
            }
        }
    }

    if bits > 0 {
        if let Some(a_chars) = &mut a.chars {
            a_chars[0] >>= bits;
            for i in 1..a.used {
                a_chars[i - 1] |= a_chars[i] << cbits;
                a_chars[i] >>= bits;
            }

            while a_chars[a.used - 1] == 0 {
                a.used -= 1;
            }
        }
    }

    a.sign = zsignum(b);
}
