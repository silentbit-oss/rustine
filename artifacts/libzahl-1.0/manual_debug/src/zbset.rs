use crate::*;
use std::ptr;

pub fn zbset(a: &mut z_t, b: &z_t, bit: usize, action: i32) {
    let mut mask: zahl_char_t = 1;
    let mut chars = bit >> 5;
    let bit = bit & (32 - 1);
    mask <<= bit;

    if a.as_ptr() != b.as_ptr() {
        zset(a, b);
    }

    if action != 0 {
        if zzero(a) {
            a[0].used = 0;
            a[0].sign = 1;
        }
        if a[0].used <= chars {
            if a[0].alloced < (chars + 1) {
                libzahl_realloc(a, chars + 1);
            }
            if let Some(ref mut chars_ptr) = a[0].chars {
                let slice = &mut chars_ptr[chars..];
                for byte in slice.iter_mut() {
                    *byte = 0;
                }
            }
            a[0].used = chars + 1;
        }
    }

    match action {
        1 => {
            if let Some(ref mut chars_ptr) = a[0].chars {
                chars_ptr[chars] |= mask;
            }
            return;
        },
        -1 => {
            if let Some(ref mut chars_ptr) = a[0].chars {
                chars_ptr[chars] ^= mask;
            }
        },
        0 => {
            if chars < a[0].used {
                if let Some(ref mut chars_ptr) = a[0].chars {
                    chars_ptr[chars] &= !mask;
                }
            }
        },
        _ => (),
    }

    while a[0].used > 0 && a[0].chars.as_ref().map_or(false, |c| c[a[0].used - 1] == 0) {
        a[0].used -= 1;
    }

    if a[0].used == 0 {
        a[0].sign = 0;
    }
}
