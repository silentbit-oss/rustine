// Module: zswap
// Implements swapping of two BigInt values

use crate::z_t;
use std::mem::swap;

/// Swaps the values of two BigInts
///
/// # Arguments
/// * `a` - The first BigInt (mutable reference)
/// * `b` - The second BigInt (mutable reference)
///
/// # Examples
/// ```
/// use libzahl::{z_t, zswap::zswap, zseti::zseti};
/// let mut a = z_t::from(0);
/// let mut b = z_t::from(0);
/// zseti(&mut a, 42);
/// zseti(&mut b, 100);
/// zswap(&mut a, &mut b);
/// assert_eq!(a, z_t::from(100));
/// assert_eq!(b, z_t::from(42));
/// ```
pub fn zswap(a: &mut z_t, b: &mut z_t) {
    swap(a, b);
}

