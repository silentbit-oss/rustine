// Module: zcmp
// Implements comparison of two BigInts

use crate::z_t;
use std::cmp::Ordering;

/// Compare two BigInts
///
/// Returns:
/// * -1 if a < b
/// * 0 if a == b
/// * 1 if a > b
///
/// # Arguments
/// * `a` - First BigInt to compare
/// * `b` - Second BigInt to compare
///
/// # Examples
/// ```
/// use libzahl::{z_t, zcmp::zcmp};
/// let a = z_t::from(10);
/// let b = z_t::from(20);
/// assert_eq!(zcmp(&a, &b), -1);
/// assert_eq!(zcmp(&b, &a), 1);
/// assert_eq!(zcmp(&a, &a), 0);
/// ```
pub fn zcmp(a: &z_t, b: &z_t) -> i32 {
    match a.cmp(b) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}
