// Module: zabs
// Implements absolute value operation for BigInt

use crate::z_t;
use num_traits::Signed;

/// Sets a to the absolute value of b.
/// Equivalent to C function: void zabs(z_t a, z_t b)
///
/// # Arguments
/// * `a` - The destination BigInt to store the absolute value
/// * `b` - The source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zabs::zabs;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(-42);
/// zabs(&mut a, &b);
/// assert_eq!(a, BigInt::from(42));
/// ```
pub fn zabs(a: &mut z_t, b: &z_t) {
    *a = b.abs();
}

