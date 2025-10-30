use crate::*;

pub fn zswap(a: &mut Z, b: &mut Z) {
    // In Rust, we can simply swap the values directly without temporary variables
    std::mem::swap(a, b);
}
