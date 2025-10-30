use crate::*;

pub fn zlsh(a: &mut Z, b: &Z, bits: usize) {
    let mut chars;
    let mut cbits;
    let mut carry = [0, 0];
    
    if zzero(b) {
        a.sign = 0;
        return;
    }
    
    if bits == 0 {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
        return;
    }
    
    chars = bits >> 5;
    let bits = bits & (32 - 1);
    cbits = 32 - bits;
    
    {
        if a.alloced < (b.used + chars) {
            libzahl_realloc(a, b.used + chars);
        }
    }
    
    // Store the pointer comparison result before the mutable borrow
    let same_ptr = a as *const _ == b as *const _;
    
    match (&mut a.chars, &b.chars) {
        (Some(a_chars), Some(b_chars)) => {
            if same_ptr {
                // Equivalent to memmove
                a_chars.copy_within(..b.used, chars);
            } else {
                // Equivalent to memcpy
                a_chars[chars..chars + b.used].copy_from_slice(&b_chars[..b.used]);
            }
            
            // Equivalent to memset
            a_chars[..chars].fill(0);
        }
        (Some(a_chars), None) => {
            // b has no chars but isn't zero - this shouldn't happen if zzero is correct
            a_chars[..chars].fill(0);
        }
        (None, Some(b_chars)) => {
            // Allocate new storage
            let mut new_chars = vec![0; b.used + chars].into_boxed_slice();
            new_chars[chars..chars + b.used].copy_from_slice(&b_chars[..b.used]);
            a.chars = Some(new_chars);
        }
        (None, None) => {
            // Both have no chars - shouldn't happen if zzero is correct
        }
    }
    
    a.used = b.used + chars;
    
    if bits != 0 {
        if let Some(a_chars) = &mut a.chars {
            let mut last_i = 0;
            for i in chars..a.used {
                carry[(!i) & 1] = a_chars[i] >> cbits;
                a_chars[i] <<= bits;
                a_chars[i] |= carry[i & 1];
                last_i = i;
            }
            
            if carry[last_i & 1] != 0 {
                {
                    if a.alloced < (a.used + 1) {
                        libzahl_realloc(a, a.used + 1);
                    }
                }
                
                if let Some(a_chars) = &mut a.chars {
                    a_chars[last_i] = carry[last_i & 1];
                    a.used += 1;
                }
            }
        }
    }
    
    a.sign = zsignum(b);
}
