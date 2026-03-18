use crate::*;
use std::ptr;

pub fn zlsh(a: &mut z_t, b: &z_t, bits: usize) {
    let mut chars: usize;
    let mut cbits: usize;
    let mut carry = [0, 0];
    
    if zzero(b) {
        a[0].sign = 0;
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
    
    if a[0].alloced < (b[0].used + chars) {
        libzahl_realloc(a, b[0].used + chars);
    }
    
    // Handle the chars array manipulation
    {
        let a_ptr = a as *const _;
        let b_ptr = b as *const _;
        let same_ptr = a_ptr == b_ptr;
        
        let a_chars = &mut a[0].chars;
        let b_chars = &b[0].chars;
        
        if let (Some(a_chars), Some(b_chars)) = (a_chars, b_chars) {
            // Ensure we have enough capacity
            if a_chars.len() < b[0].used + chars {
                libzahl_realloc(a, b[0].used + chars);
                // After realloc, we need to get a_chars again
                if let Some(a_chars) = &mut a[0].chars {
                    if same_ptr {
                        // Use memmove for overlapping regions
                        unsafe {
                            ptr::copy(
                                b_chars.as_ptr(),
                                a_chars.as_mut_ptr().add(chars),
                                b[0].used,
                            );
                        }
                    } else {
                        // Use memcpy for non-overlapping regions
                        unsafe {
                            ptr::copy_nonoverlapping(
                                b_chars.as_ptr(),
                                a_chars.as_mut_ptr().add(chars),
                                b[0].used,
                            );
                        }
                    }
                    
                    // Zero out the first chars elements
                    for i in 0..chars {
                        a_chars[i] = 0;
                    }
                    
                    a[0].used = b[0].used + chars;
                    
                    if bits != 0 {
                        for i in chars..a[0].used {
                            carry[(!i) & 1] = a_chars[i] >> cbits;
                            a_chars[i] <<= bits;
                            a_chars[i] |= carry[i & 1];
                        }
                        
                        let last_i = a[0].used - 1;
                        if carry[last_i & 1] != 0 {
                            if a[0].alloced < a[0].used + 1 {
                                libzahl_realloc(a, a[0].used + 1);
                                // After realloc, we need to get a_chars again
                                if let Some(a_chars) = &mut a[0].chars {
                                    // Create a new array with the additional element
                                    let mut new_chars = vec![0; a[0].used + 1];
                                    new_chars[..a[0].used].copy_from_slice(&a_chars[..a[0].used]);
                                    new_chars[a[0].used] = carry[last_i & 1];
                                    a[0].chars = Some(new_chars.into_boxed_slice());
                                    a[0].used += 1;
                                }
                            } else {
                                // Create a new array with the additional element
                                let mut new_chars = vec![0; a[0].used + 1];
                                new_chars[..a[0].used].copy_from_slice(&a_chars[..a[0].used]);
                                new_chars[a[0].used] = carry[last_i & 1];
                                a[0].chars = Some(new_chars.into_boxed_slice());
                                a[0].used += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    a[0].sign = zsignum(b);
}
