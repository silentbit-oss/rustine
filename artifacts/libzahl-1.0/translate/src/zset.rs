use crate::*;

pub fn zset(a: &mut Z, b: &Z) {
    if zzero(b) {
        a.sign = 0;
    } else {
        // Use a block to limit the scope of the mutable borrow
        {
            if a.alloced < b.used {
                libzahl_realloc(a, b.used);
            }
        }
        
        a.sign = b.sign;
        a.used = b.used;
        
        if let Some(b_chars) = &b.chars {
            if let Some(a_chars) = &mut a.chars {
                // Safe equivalent of memcpy using Rust's slice operations
                a_chars[..b.used].copy_from_slice(&b_chars[..b.used]);
            } else {
                // If a.chars is None but b.chars is Some, we need to allocate
                let mut new_chars = vec![0; b.used].into_boxed_slice();
                new_chars.copy_from_slice(&b_chars[..b.used]);
                a.chars = Some(new_chars);
            }
        }
    }
}
