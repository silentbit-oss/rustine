use crate::*;
use std::ptr;


pub fn zadd_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut i: usize;
    let size: usize;
    let mut n: usize;
    let mut carry = [0u32, 0u32];
    let addend: &[zahl_char_t];
    
    if zzero(b) {
        zabs(a, c);
        return;
    } else if zzero(c) {
        zabs(a, b);
        return;
    }
    
    size = std::cmp::max(b[0].used, c[0].used);
    n = (b[0].used + c[0].used) - size;
    
    // Ensure a has enough allocated memory
    if a[0].alloced < (size + 1) {
        libzahl_realloc(a, size + 1);
    }
    
    // Ensure the chars vector exists and has enough capacity
    if a[0].chars.is_none() {
        a[0].chars = Some(vec![0; size + 1].into_boxed_slice());
    } else if let Some(ref chars) = a[0].chars {
        if chars.len() <= size {
            let mut new_chars = vec![0; size + 1].into_boxed_slice();
            new_chars[..chars.len()].copy_from_slice(&chars);
            a[0].chars = Some(new_chars);
        }
    }
    
    // Set the last element to 0
    if let Some(ref mut chars) = a[0].chars {
        chars[size] = 0;
    }
    
    // Handle the different cases for a, b, c relationships
    if std::ptr::eq(a, b) {
        if a[0].used < c[0].used {
            n = c[0].used;
            if let Some(ref mut a_chars) = a[0].chars {
                if a_chars.len() < n {
                    let mut new_chars = vec![0; n].into_boxed_slice();
                    new_chars[..a_chars.len()].copy_from_slice(&a_chars);
                    a[0].chars = Some(new_chars);
                }
            }
            // Zero out the extended part
            if let Some(ref mut a_chars) = a[0].chars {
                for j in a[0].used..n {
                    a_chars[j] = 0;
                }
            }
        }
        addend = if let Some(chars) = &c[0].chars {
            &chars[..c[0].used]
        } else {
            &[]
        };
    } else if std::ptr::eq(a, c) {
        if a[0].used < b[0].used {
            n = b[0].used;
            if let Some(ref mut a_chars) = a[0].chars {
                if a_chars.len() < n {
                    let mut new_chars = vec![0; n].into_boxed_slice();
                    new_chars[..a_chars.len()].copy_from_slice(&a_chars);
                    a[0].chars = Some(new_chars);
                }
            }
            // Zero out the extended part
            if let Some(ref mut a_chars) = a[0].chars {
                for j in a[0].used..n {
                    a_chars[j] = 0;
                }
            }
        }
        addend = if let Some(chars) = &b[0].chars {
            &chars[..b[0].used]
        } else {
            &[]
        };
    } else if b[0].used > c[0].used {
        if let (Some(a_chars), Some(b_chars)) = (a[0].chars.as_mut(), b[0].chars.as_ref()) {
            a_chars[..b[0].used].copy_from_slice(&b_chars[..b[0].used]);
        }
        a[0].used = b[0].used;
        addend = if let Some(chars) = &c[0].chars {
            &chars[..c[0].used]
        } else {
            &[]
        };
    } else {
        if let (Some(a_chars), Some(c_chars)) = (a[0].chars.as_mut(), c[0].chars.as_ref()) {
            a_chars[..c[0].used].copy_from_slice(&c_chars[..c[0].used]);
        }
        a[0].used = c[0].used;
        addend = if let Some(chars) = &b[0].chars {
            &chars[..b[0].used]
        } else {
            &[]
        };
    }
    
    // Perform the addition with carry
    if let Some(a_chars) = a[0].chars.as_mut() {
        for i in 0..n {
            if carry[i & 1] != 0 {
                carry[(!i) & 1] = if (u32::MAX - a_chars[i]) <= addend[i] { 1 } else { 0 };
            } else {
                carry[(!i) & 1] = if (u32::MAX - a_chars[i]) < addend[i] { 1 } else { 0 };
            }
            a_chars[i] = a_chars[i].wrapping_add(addend[i]).wrapping_add(carry[i & 1]);
        }
        
        let mut i = n;
        while carry[i & 1] != 0 {
            carry[(!i) & 1] = if a_chars[i] == u32::MAX { 1 } else { 0 };
            a_chars[i] = a_chars[i].wrapping_add(1);
            i += 1;
        }
        
        if a[0].used < i {
            a[0].used = i;
        }
    }
    
    a[0].sign = 1;
}
pub fn zadd(a: &mut z_t, b: &z_t, c: &z_t) {
    if zzero(b) {
        if a.as_ptr() != c.as_ptr() {
            zset(a, c);
        }
    } else if zzero(c) {
        if a.as_ptr() != b.as_ptr() {
            zset(a, b);
        }
    } else if b.as_ptr() == c.as_ptr() {
        zlsh(a, b, 1);
    } else if (zsignum(b) | zsignum(c)) < 0 {
        if zsignum(b) < 0 {
            if zsignum(c) < 0 {
                zadd_unsigned(a, b, c);
                a[0].sign = -zsignum(a);
            } else {
                zsub_unsigned(a, c, b);
            }
        } else {
            zsub_unsigned(a, b, c);
        }
    } else {
        zadd_unsigned(a, b, c);
    }
}
