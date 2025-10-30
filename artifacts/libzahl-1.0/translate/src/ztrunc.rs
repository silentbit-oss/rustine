use crate::*;

pub fn ztrunc(a: &mut Z, b: &Z, bits: usize) {
    let mut mask: ZahlCharT = 1;
    let chars: usize;
    let mut i: usize;

    if zzero(b) {
        a.sign = 0;
        return;
    }

    chars = (bits + (32 - 1)) >> 5;
    a.sign = b.sign;
    a.used = if chars < b.used { chars } else { b.used };
    
    let mut bits = if a.used < chars { 0 } else { bits };
    
    if a as *const _ != b as *const _ {
        if a.alloced < a.used {
            libzahl_realloc(a, a.used);
        }
        
        if let Some(a_chars) = &mut a.chars {
            if let Some(b_chars) = &b.chars {
                a_chars[..a.used].copy_from_slice(&b_chars[..a.used]);
            }
        }
    }

    bits = bits & (32 - 1);
    if bits != 0 {
        mask <<= bits;
        mask -= 1;
        if let Some(a_chars) = &mut a.chars {
            if a.used > 0 {
                a_chars[a.used - 1] &= mask;
            }
        }
    }

    i = a.used;
    while i > 0 {
        i -= 1;
        if let Some(a_chars) = &a.chars {
            if a_chars[i] != 0 {
                return;
            }
        }
    }

    a.sign = 0;
}
