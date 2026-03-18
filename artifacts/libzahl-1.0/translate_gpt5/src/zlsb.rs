// Module: zlsb
// Implements least significant bit finding for BigInt

use crate::z_t;
use num_traits::Zero;

/// Find the index of the least significant set bit in a BigInt.
/// Equivalent to C function: size_t zlsb(z_t a)
///
/// This function returns the position (0-indexed) of the least significant
/// bit that is set to 1. If a is zero, it returns usize::MAX.
///
/// # Arguments
/// * `a` - The BigInt to search
///
/// # Returns
/// * `usize` - The position of the least significant set bit, or usize::MAX if a is zero
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zlsb::zlsb;
///
/// let a = BigInt::from(0);
/// assert_eq!(zlsb(&a), usize::MAX);  // Zero returns MAX
///
/// let a = BigInt::from(1);
/// assert_eq!(zlsb(&a), 0);  // 0b1, LSB is at position 0
///
/// let a = BigInt::from(4);
/// assert_eq!(zlsb(&a), 2);  // 0b100, LSB is at position 2
///
/// let a = BigInt::from(6);
/// assert_eq!(zlsb(&a), 1);  // 0b110, LSB is at position 1
///
/// let a = BigInt::from(-8);
/// assert_eq!(zlsb(&a), 3);  // |-8| = 8 = 0b1000, LSB is at position 3
/// ```
pub fn zlsb(a: &z_t) -> usize {
    // If a is zero, return MAX value
    if a.is_zero() {
        return usize::MAX;
    }

    // Find the least significant set bit by checking each bit from position 0
    // This is equivalent to counting trailing zeros
    let mut position = 0;

    // Work with the magnitude to handle negative numbers correctly
    let mag = a.magnitude();

    // Check each bit until we find one that is set
    loop {
        if mag.bit(position as u64) {
            return position;
        }
        position += 1;
    }
}
