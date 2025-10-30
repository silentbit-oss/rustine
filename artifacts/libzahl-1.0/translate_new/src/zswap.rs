use crate::*;

pub fn zswap(a: &mut z_t, b: &mut z_t) {
    // Create a temporary Z to hold the value
    let mut t = Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    };
    
    // Swap the values using safe Rust operations
    std::mem::swap(&mut a[0], &mut t);
    std::mem::swap(&mut b[0], &mut a[0]);
    std::mem::swap(&mut t, &mut b[0]);
}
