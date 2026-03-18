// Module: zand
// Implements bitwise AND operation for BigInt

use crate::z_t;
use num_traits::Zero;
use num_traits::Signed;

/// Bitwise AND of two BigInts.
/// Equivalent to C function: void zand(z_t a, z_t b, z_t c)
///
/// This function computes a = b & c, performing bitwise AND operation.
/// The result follows the semantics of the original C implementation:
/// - If either operand is zero, the result is zero
/// - Only ANDs bits up to the minimum length of the two operands
/// - The sign of the result is positive if either b or c is positive
///
/// # Arguments
/// * `a` - The destination BigInt to store the AND result
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zand::zand;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(0b1010);  // 10
/// let c = BigInt::from(0b1100);  // 12
/// zand(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(0b1000));  // 8
/// ```
pub fn zand(a: &mut z_t, b: &z_t, c: &z_t) {
    // Handle zero cases
    if b.is_zero() || c.is_zero() {
        *a = z_t::zero();
        return;
    }

    // For BigInt with two's complement representation, we need to handle
    // the sign-magnitude representation used by the original C code.
    // The C code performs AND on magnitudes and determines sign separately.

    // Get absolute values for magnitude-based AND
    let b_abs = b.abs();
    let c_abs = c.abs();

    // Perform bitwise AND on absolute values
    let result_abs = &b_abs & &c_abs;

    // If result is zero, return zero
    if result_abs.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Sign handling: positive if either operand is positive
    // This matches the C logic: (zsignum(b) > 0 || zsignum(c) > 0) * 2 - 1
    // which gives +1 if either is positive, -1 if both are negative
    let both_negative = b < &z_t::zero() && c < &z_t::zero();

    *a = if both_negative {
        -result_abs
    } else {
        result_abs
    };
}
