use crate::*;
use std::usize;


pub fn zlsb(a: &z_t) -> usize {
    let mut i = 0;
    let mut x: zahl_char_t;
    
    if zzero(a) {
        return usize::MAX;
    }
    
    loop {
        // Safe access since we know a is not zero and chars exists
        x = a[0].chars.as_ref().unwrap()[i];
        if x != 0 {
            x = !x;
            i *= 32;
            while x & 1 != 0 {
                x >>= 1;
                i += 1;
            }
            return i;
        }
        i += 1;
    }
}
