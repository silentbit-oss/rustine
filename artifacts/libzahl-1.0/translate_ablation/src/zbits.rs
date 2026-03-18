use crate::*;
use rand::Rng;

pub fn zbits(a: &mut z_t) -> usize {
    if zzero(a) {
        return 1;
    }

    let mut i = a[0].used - 1;
    loop {
        let x = match &a[0].chars {
            Some(chars) => chars[i],
            None => 0,
        };

        if x != 0 {
            // Safe because we're working with a mutable reference
            // and we know the chars exist at this point
            a[0].used = i + 1;
            
            let mut i = i * 32;
            let mut x = x;
            while x != 0 {
                x >>= 1;
                i += 1;
            }
            
            return i;
        }
        
        if i == 0 {
            break;
        }
        i -= 1;
    }

    // This line is theoretically unreachable because:
    // 1. If zzero(a) is true, we return early
    // 2. Otherwise, we'll eventually find a non-zero x or reach i=0
    // But Rust requires all paths to return, so we return a default value
    0
}
