// Module: zcmpmag
// Implements comparison of absolute values of two BigInts

use crate::z_t;
use std::cmp::Ordering;
use num_traits::Signed;

/// Compare the absolute values of two BigInts
///
/// Returns:
/// * -1 if |a| < |b|
/// * 0 if |a| == |b|
/// * 1 if |a| > |b|
///
/// # Arguments
/// * `a` - First BigInt to compare (using absolute value)
/// * `b` - Second BigInt to compare (using absolute value)
///
/// # Examples
/// ```
/// use libzahl::{z_t, zcmpmag::zcmpmag};
/// let a = z_t::from(-10);
/// let b = z_t::from(20);
/// assert_eq!(zcmpmag(&a, &b), -1);  // |-10| < |20|
///
/// let c = z_t::from(-15);
/// let d = z_t::from(15);
/// assert_eq!(zcmpmag(&c, &d), 0);   // |-15| == |15|
///
/// let e = z_t::from(-30);
/// let f = z_t::from(10);
/// assert_eq!(zcmpmag(&e, &f), 1);   // |-30| > |10|
/// ```
pub fn zcmpmag(a: &z_t, b: &z_t) -> i32 {
    let abs_a = a.abs();
    let abs_b = b.abs();

    match abs_a.cmp(&abs_b) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}
