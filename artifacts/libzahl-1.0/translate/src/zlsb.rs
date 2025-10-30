use crate::*;
use std::usize;

pub fn zlsb(a: &Z) -> usize {
    let mut i = 0;
    let mut x: ZahlCharT;
    
    if zzero(a) {
        return usize::MAX;
    }
    
    loop {
        // Safe access to chars array - we know it's Some because zzero would have returned otherwise
        x = a.chars.as_ref().unwrap()[i];
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
