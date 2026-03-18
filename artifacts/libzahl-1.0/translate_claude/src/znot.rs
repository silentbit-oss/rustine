// Module: znot
// Implements bitwise NOT operation for BigInt

use crate::z_t;
use crate::zset::zset;
use num_traits::Zero;
use num_traits::Signed;

/// Bitwise NOT of a BigInt.
/// Equivalent to C function: void znot(z_t a, z_t b)
///
/// This function computes a = ~b, performing bitwise NOT operation.
/// The result follows the semantics of the original C implementation:
/// - If b is zero, the result is zero
/// - Flips all bits up to the bit length of b
/// - Negates the sign of the result
/// - Masks off any bits beyond the original bit length
///
/// # Arguments
/// * `a` - The destination BigInt to store the NOT result
/// * `b` - The source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::znot::znot;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(0b1010);  // 10 (4 bits)
/// znot(&mut a, &b);
/// assert_eq!(a, BigInt::from(0b0101));  // 5 (NOT of 10 within 4 bits)
/// ```
pub fn znot(a: &mut z_t, b: &z_t) {
    // Handle zero case
    if b.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Get the number of bits in b
    let bits = b.bits() as u64;

    // Copy b to a
    zset(a, b);

    // Negate the sign
    *a = -&*a;

    // Get absolute value for bit manipulation
    let abs_a = a.abs();

    // Flip all bits by XORing with a mask of all 1s up to 'bits' bits
    // Mask = 2^bits - 1
    let mask = (z_t::from(1) << bits) - 1;
    let result_abs = &abs_a ^ &mask;

    // If result is zero after flipping, return zero
    if result_abs.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Apply the sign (which was negated earlier)
    // If original was positive, result should be negative (and vice versa)
    let b_negative = b < &z_t::zero();

    *a = if b_negative {
        result_abs  // Original was negative, result is positive
    } else {
        -result_abs  // Original was positive, result is negative
    };
}
