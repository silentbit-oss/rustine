// Module: zcmpi
// Implements comparison of BigInt with i64

use crate::z_t;
use std::cmp::Ordering;

/// Compare a BigInt with a signed 64-bit integer
///
/// Returns:
/// * -1 if a < b
/// * 0 if a == b
/// * 1 if a > b
///
/// # Arguments
/// * `a` - BigInt to compare
/// * `b` - i64 value to compare with
///
/// # Examples
/// ```
/// use libzahl::{z_t, zcmpi::zcmpi};
/// let a = z_t::from(10);
/// assert_eq!(zcmpi(&a, 20), -1);
/// assert_eq!(zcmpi(&a, 10), 0);
/// assert_eq!(zcmpi(&a, 5), 1);
///
/// let b = z_t::from(-5);
/// assert_eq!(zcmpi(&b, 0), -1);
/// ```
pub fn zcmpi(a: &z_t, b: i64) -> i32 {
    let b_bigint = z_t::from(b);
    match a.cmp(&b_bigint) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}
