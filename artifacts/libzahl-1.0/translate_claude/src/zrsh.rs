// Module: zrsh
// Implements right shift operation for BigInt

use crate::z_t;
use num_traits::Zero;

/// Right shift a BigInt by a specified number of bits.
/// Equivalent to C function: void zrsh(z_t a, z_t b, size_t bits)
///
/// This function computes a = b >> bits, performing a right shift operation.
/// Right shifting by n bits is equivalent to dividing by 2^n (floored for positive,
/// ceiling for negative in two's complement, but this implementation uses
/// magnitude-based shifting like the C version).
///
/// # Arguments
/// * `a` - The destination BigInt to store the shifted result
/// * `b` - The source BigInt to be shifted
/// * `bits` - The number of bits to shift right
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zrsh::zrsh;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(20);
/// zrsh(&mut a, &b, 2);  // 20 >> 2 = 5
/// assert_eq!(a, BigInt::from(5));
/// ```
pub fn zrsh(a: &mut z_t, b: &z_t, bits: usize) {
    // If bits is zero, just copy b to a
    if bits == 0 {
        *a = b.clone();
        return;
    }

    // If b is zero, result is zero
    if b.is_zero() {
        *a = z_t::zero();
        return;
    }

    // Check if shifting would result in zero
    // This happens when the number of bits in b is less than or equal to bits
    let b_bits = b.bits() as usize;
    if b_bits <= bits {
        *a = z_t::zero();
        return;
    }

    // Perform right shift using BigInt's shift operators
    // BigInt handles the sign correctly
    *a = b >> bits;
}
