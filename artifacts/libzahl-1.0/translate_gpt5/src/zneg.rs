// Module: zneg
// Implements negation operation for BigInt

use crate::z_t;

/// Sets a to the negation of b.
/// Equivalent to C function: void zneg(z_t a, z_t b)
///
/// # Arguments
/// * `a` - The destination BigInt to store the negated value
/// * `b` - The source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zneg::zneg;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(42);
/// zneg(&mut a, &b);
/// assert_eq!(a, BigInt::from(-42));
/// ```
pub fn zneg(a: &mut z_t, b: &z_t) {
    *a = -b;
}

