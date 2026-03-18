// Module: zlsh
// Implements left shift operation for BigInt

use crate::z_t;
use num_traits::Zero;

/// Left shift a BigInt by a specified number of bits.
/// Equivalent to C function: void zlsh(z_t a, z_t b, size_t bits)
///
/// This function computes a = b << bits, performing a left shift operation.
/// Left shifting by n bits is equivalent to multiplying by 2^n.
///
/// # Arguments
/// * `a` - The destination BigInt to store the shifted result
/// * `b` - The source BigInt to be shifted
/// * `bits` - The number of bits to shift left
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zlsh::zlsh;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(5);
/// zlsh(&mut a, &b, 2);  // 5 << 2 = 20
/// assert_eq!(a, BigInt::from(20));
/// ```
pub fn zlsh(a: &mut z_t, b: &z_t, bits: usize) {
    // If b is zero, result is zero
    if b.is_zero() {
        *a = z_t::zero();
        return;
    }

    // If bits is zero, just copy b to a
    if bits == 0 {
        *a = b.clone();
        return;
    }

    // Perform left shift using BigInt's shift operators
    // BigInt handles the sign correctly
    *a = b << bits;
}
