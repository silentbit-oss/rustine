use crate::*;

pub fn zbset(a: &mut Z, b: &Z, bit: usize, action: i32) {
    let mut mask: u32 = 1;
    let chars = bit >> 5;
    let bit = bit & (32 - 1);
    mask <<= bit;

    // Equivalent to the do-while(0) block
    if a as *const _ != b as *const _ {
        zset(a, b);
    }

    if action != 0 {
        if zzero(a) {
            a.used = 0;
            a.sign = 1;
        }
        if a.used <= chars {
            // Equivalent to the do-while(0) block
            if a.alloced < (chars + 1) {
                libzahl_realloc(a, chars + 1);
            }

            // Equivalent to memset
            if let Some(a_chars) = &mut a.chars {
                for i in a.used..(chars + 1) {
                    a_chars[i] = 0;
                }
            }
            a.used = chars + 1;
        }
    }

    if action > 0 {
        if let Some(a_chars) = &mut a.chars {
            a_chars[chars] |= mask;
        }
        return;
    } else if action < 0 {
        if let Some(a_chars) = &mut a.chars {
            a_chars[chars] ^= mask;
        }
    } else if chars < a.used {
        if let Some(a_chars) = &mut a.chars {
            a_chars[chars] &= !mask;
        }
    }

    while a.used > 0 && a.chars.as_ref().map_or(false, |c| c[a.used - 1] == 0) {
        a.used -= 1;
    }

    if a.used == 0 {
        a.sign = 0;
    }
}
