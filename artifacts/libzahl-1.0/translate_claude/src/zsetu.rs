// Module: zsetu
// Implements conversion from unsigned 64-bit integer to BigInt

use crate::z_t;

/// Sets a to the value of an unsigned 64-bit integer
///
/// # Arguments
/// * `a` - The destination BigInt (mutable reference)
/// * `b` - The source u64 value
///
/// # Examples
/// ```
/// use libzahl::{z_t, zsetu::zsetu};
/// let mut a = z_t::from(0);
/// zsetu(&mut a, 42);
/// assert_eq!(a, z_t::from(42));
/// ```
pub fn zsetu(a: &mut z_t, b: u64) {
    *a = z_t::from(b);
}

