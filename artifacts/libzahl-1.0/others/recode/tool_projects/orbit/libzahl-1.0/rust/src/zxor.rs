// Module: zxor
// Implements bitwise XOR operation for BigInt

use crate::z_t;
use crate::zset::zset;
use num_traits::Zero;
use num_traits::Signed;

/// Bitwise XOR of two BigInts.
/// Equivalent to C function: void zxor(z_t a, z_t b, z_t c)
///
/// This function computes a = b ^ c, performing bitwise XOR operation.
/// The result follows the semantics of the original C implementation:
/// - If both operands are zero, the result is zero
/// - If one operand is zero, the result is a copy of the other
/// - XORs all bits up to the maximum length of the two operands
/// - The sign of the result depends on whether the signs of b and c differ
///
/// # Arguments
/// * `a` - The destination BigInt to store the XOR result
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zxor::zxor;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(0b1010);  // 10
/// let c = BigInt::from(0b1100);  // 12
/// zxor(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(0b0110));  // 6
/// ```
pub fn zxor(a: &mut z_t, b: &z_t, c: &z_t) {
    // Handle zero cases
    if b.is_zero() {
        if c.is_zero() {
            *a = z_t::zero();
        } else {
            zset(a, c);
        }
        return;
    } else if c.is_zero() {
        zset(a, b);
        return;
    }

    // For BigInt with two's complement representation, we need to handle
    // the sign-magnitude representation used by the original C code.
    // The C code performs XOR on magnitudes and determines sign separately.

    // Get absolute values for magnitude-based XOR
    let b_abs = b.abs();
    let c_abs = c.abs();

    // Perform bitwise XOR on absolute values
    let result_abs = &b_abs ^ &c_abs;

    // If result is zero, return zero
    if result_abs.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Sign handling: positive if signs are the same, negative if different
    // This matches the C logic: 1 - 2 * ((zsignum(b) ^ zsignum(c)) < 0)
    // When signs differ, (zsignum(b) ^ zsignum(c)) is negative, so result is negative
    // When signs are same, (zsignum(b) ^ zsignum(c)) is non-negative, so result is positive
    let b_negative = b < &z_t::zero();
    let c_negative = c < &z_t::zero();
    let signs_differ = b_negative != c_negative;

    *a = if signs_differ {
        -result_abs
    } else {
        result_abs
    };
}
