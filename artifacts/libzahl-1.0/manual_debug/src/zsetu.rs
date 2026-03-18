use crate::*;
use rand::Rng;

pub fn zsetu(a: &mut z_t, b: u64) {
    if b == 0 {
        a[0].sign = 0;
        return;
    }

    // Calculate required allocation size
    let needed = ((std::mem::size_of_val(&b) + std::mem::size_of::<zahl_char_t>() - 1) / 
                 std::mem::size_of::<zahl_char_t>());

    // Check and reallocate if necessary
    if a[0].alloced < needed {
        libzahl_realloc(a, needed);
    }

    a[0].sign = 1;
    a[0].used = 0;
    
    let mut b = b; // Make mutable copy
    while b != 0 {
        // Safe because we've ensured sufficient allocation
        if let Some(ref mut chars) = a[0].chars {
            //chars[a[0].used] = b as zahl_char_t;
        }
        a[0].used += 1;
        b >>= 32;
    }
}
