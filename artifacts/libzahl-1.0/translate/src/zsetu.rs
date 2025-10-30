use crate::*;

pub fn zsetu(a: &mut Z, mut b: u64) {
    if b == 0 {
        a.sign = 0;
        return;
    }

    // Calculate required allocation size
    let required_size = ((std::mem::size_of_val(&b) + std::mem::size_of::<u32>() - 1) 
                        / std::mem::size_of::<u32>());

    // Check and potentially reallocate
    if a.alloced < required_size {
        libzahl_realloc(a, required_size);
    }

    a.sign = 1;
    a.used = 0;

    // Process each 32-bit chunk of b
    while b != 0 {
        // Safe because we've ensured sufficient allocation
        if let Some(chars) = &mut a.chars {
            chars[a.used] = b as u32;
            a.used += 1;
            b >>= 32;
        } else {
            // This should never happen since we allocated above
            panic!("Allocation failed but no error was raised");
        }
    }
}
