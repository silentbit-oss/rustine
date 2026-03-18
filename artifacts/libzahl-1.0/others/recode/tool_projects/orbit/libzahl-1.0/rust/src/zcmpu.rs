// Module: zcmpu
// Implements comparison of BigInt with u64

use crate::z_t;
use std::cmp::Ordering;

/// Compare a BigInt with an unsigned 64-bit integer
///
/// Returns:
/// * -1 if a < b
/// * 0 if a == b
/// * 1 if a > b
///
/// # Arguments
/// * `a` - BigInt to compare
/// * `b` - u64 value to compare with
///
/// # Examples
/// ```
/// use libzahl::{z_t, zcmpu::zcmpu};
/// let a = z_t::from(10);
/// assert_eq!(zcmpu(&a, 20), -1);
/// assert_eq!(zcmpu(&a, 10), 0);
/// assert_eq!(zcmpu(&a, 5), 1);
///
/// // Negative BigInt is always less than unsigned integer
/// let b = z_t::from(-5);
/// assert_eq!(zcmpu(&b, 10), -1);
/// ```
pub fn zcmpu(a: &z_t, b: u64) -> i32 {
    let b_bigint = z_t::from(b);
    match a.cmp(&b_bigint) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}
