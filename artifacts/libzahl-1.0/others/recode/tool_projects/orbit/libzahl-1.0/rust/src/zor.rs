// Module: zor
// Implements bitwise OR operation for BigInt

use crate::z_t;
use crate::zset::zset;
use num_traits::Zero;
use num_traits::Signed;

/// Bitwise OR of two BigInts.
/// Equivalent to C function: void zor(z_t a, z_t b, z_t c)
///
/// This function computes a = b | c, performing bitwise OR operation.
/// The result follows the semantics of the original C implementation:
/// - If both operands are zero, the result is zero
/// - If one operand is zero, the result is a copy of the other
/// - ORs all bits up to the maximum length of the two operands
/// - The sign of the result is positive only if both b and c are positive
///
/// # Arguments
/// * `a` - The destination BigInt to store the OR result
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zor::zor;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(0b1010);  // 10
/// let c = BigInt::from(0b1100);  // 12
/// zor(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(0b1110));  // 14
/// ```
pub fn zor(a: &mut z_t, b: &z_t, c: &z_t) {
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
    // The C code performs OR on magnitudes and determines sign separately.

    // Get absolute values for magnitude-based OR
    let b_abs = b.abs();
    let c_abs = c.abs();

    // Perform bitwise OR on absolute values
    let result_abs = &b_abs | &c_abs;

    // Sign handling: positive only if both operands are positive
    // This matches the C logic: (zsignum(b) > 0 && zsignum(c) > 0) * 2 - 1
    // which gives +1 if both are positive, -1 if either is negative
    let both_positive = b > &z_t::zero() && c > &z_t::zero();

    *a = if both_positive {
        result_abs
    } else {
        -result_abs
    };
}
