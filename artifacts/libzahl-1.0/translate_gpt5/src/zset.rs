// Module: zset
// Implements assignment (copy/clone) of one BigInt to another

use crate::z_t;

/// Sets a to the value of b (clones b into a)
///
/// # Arguments
/// * `a` - The destination BigInt (mutable reference)
/// * `b` - The source BigInt (reference)
///
/// # Examples
/// ```
/// use libzahl::{z_t, zset::zset, zseti::zseti};
/// let mut a = z_t::from(0);
/// let mut b = z_t::from(0);
/// zseti(&mut b, 42);
/// zset(&mut a, &b);
/// assert_eq!(a, z_t::from(42));
/// ```
pub fn zset(a: &mut z_t, b: &z_t) {
    *a = b.clone();
}

