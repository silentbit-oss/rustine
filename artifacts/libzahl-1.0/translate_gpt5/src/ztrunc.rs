// Module: ztrunc
// Implements bit truncation for BigInt

use crate::z_t;
use num_traits::{Zero, One, Signed};
use num_bigint::{BigInt, BigUint};

/// Truncate a BigInt to n bits.
/// Equivalent to C function: void ztrunc(z_t a, z_t b, size_t bits)
///
/// This function truncates b to the specified number of bits and stores
/// the result in a. Only the least significant 'bits' bits are retained.
/// The sign of the number is preserved.
///
/// # Arguments
/// * `a` - The destination BigInt (will store the truncated result)
/// * `b` - The source BigInt to truncate
/// * `bits` - The number of bits to retain (0-indexed)
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::ztrunc::ztrunc;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(255);  // 0b11111111
/// ztrunc(&mut a, &b, 4);      // Keep only 4 bits: 0b1111 = 15
/// assert_eq!(a, BigInt::from(15));
///
/// let b = BigInt::from(123);  // 0b1111011
/// ztrunc(&mut a, &b, 3);      // Keep only 3 bits: 0b011 = 3
/// assert_eq!(a, BigInt::from(3));
///
/// let b = BigInt::from(-255);  // Negative number
/// ztrunc(&mut a, &b, 4);       // Truncate but preserve sign
/// assert_eq!(a, BigInt::from(-15));
/// ```
pub fn ztrunc(a: &mut z_t, b: &z_t, bits: usize) {
    // If b is zero, result is zero
    if b.is_zero() {
        *a = z_t::zero();
        return;
    }

    // If bits is 0, result is zero
    if bits == 0 {
        *a = z_t::zero();
        return;
    }

    // Save the sign of b
    let is_negative = b.is_negative();

    // Work with the absolute value
    let mag = b.magnitude().clone();

    // Create a mask with 'bits' bits set to 1
    // mask = (1 << bits) - 1
    let mask = (BigUint::one() << bits) - BigUint::one();

    // Apply the mask to truncate to the specified number of bits
    let result = mag & mask;

    // If the result is zero, set a to zero
    if result.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Restore the sign
    if is_negative {
        *a = -BigInt::from(result);
    } else {
        *a = BigInt::from(result);
    }
}
