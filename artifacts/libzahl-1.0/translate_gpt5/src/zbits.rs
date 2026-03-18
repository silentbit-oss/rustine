// Module: zbits
// Implements bit counting for BigInt

use crate::z_t;
use num_traits::Zero;

/// Count the number of bits in a BigInt.
/// Equivalent to C function: size_t zbits(z_t a)
///
/// This function returns the number of bits needed to represent the absolute
/// value of a, which is floor(log2(|a|)) + 1. For zero, it returns 1.
///
/// # Arguments
/// * `a` - The BigInt to count bits for
///
/// # Returns
/// * `usize` - The number of bits needed to represent |a|, or 1 if a is zero
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zbits::zbits;
///
/// let a = BigInt::from(0);
/// assert_eq!(zbits(&a), 1);  // Zero returns 1
///
/// let a = BigInt::from(1);
/// assert_eq!(zbits(&a), 1);  // 0b1 needs 1 bit
///
/// let a = BigInt::from(5);
/// assert_eq!(zbits(&a), 3);  // 0b101 needs 3 bits
///
/// let a = BigInt::from(255);
/// assert_eq!(zbits(&a), 8);  // 0b11111111 needs 8 bits
///
/// let a = BigInt::from(-5);
/// assert_eq!(zbits(&a), 3);  // |-5| = 5 = 0b101 needs 3 bits
/// ```
pub fn zbits(a: &z_t) -> usize {
    // Special case: zero returns 1 (as per the C implementation comment)
    if a.is_zero() {
        return 1;
    }

    // Use BigInt's bits() method which returns the number of bits
    // in the magnitude of the number
    a.bits() as usize
}
