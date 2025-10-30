use crate::*;
use rand::Rng;

pub fn znot(a: &mut z_t, b: &mut z_t) {
    let mut bits;
    
    if zzero(b) {
        a[0].sign = 0;
        return;
    }
    
    bits = zbits(b);
    
    {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    }
    
    a[0].sign = -zsignum(a);
    
    if let Some(ref mut chars) = a[0].chars {
        for n in (0..a[0].used).rev() {
            chars[n] = !chars[n];
        }
    }
    
    bits = bits & (32 - 1);
    if bits != 0 {
        if let Some(ref mut chars) = a[0].chars {
            let last_idx = a[0].used - 1;
            chars[last_idx] &= ((1 as zahl_char_t) << bits) - 1;
        }
    }
    
    while a[0].used > 0 && {
        if let Some(ref chars) = a[0].chars {
            chars[a[0].used - 1] == 0
        } else {
            true
        }
    } {
        a[0].used -= 1;
    }
    
    if a[0].used == 0 {
        a[0].sign = 0;
    }
}
