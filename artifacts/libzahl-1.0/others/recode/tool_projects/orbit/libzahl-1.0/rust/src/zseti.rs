// Module: zseti
// Implements conversion from signed 64-bit integer to BigInt

use crate::z_t;

/// Sets a to the value of a signed 64-bit integer
///
/// # Arguments
/// * `a` - The destination BigInt (mutable reference)
/// * `b` - The source i64 value
///
/// # Examples
/// ```
/// use libzahl::{z_t, zseti::zseti};
/// let mut a = z_t::from(0);
/// zseti(&mut a, -42);
/// assert_eq!(a, z_t::from(-42));
/// ```
pub fn zseti(a: &mut z_t, b: i64) {
    *a = z_t::from(b);
}

