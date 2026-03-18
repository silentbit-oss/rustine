// Module: zbtest
// Implements bit testing for BigInt

use crate::z_t;
use num_traits::Zero;

/// Test if a specific bit is set in a BigInt.
/// Equivalent to C function: int zbtest(z_t a, size_t bit)
///
/// This function returns 1 if the bit at the specified position is set,
/// and 0 otherwise. Bit positions are zero-indexed from the least significant bit.
///
/// # Arguments
/// * `a` - The BigInt to test
/// * `bit` - The bit position to test (0-indexed)
///
/// # Returns
/// * `i32` - 1 if the bit is set, 0 otherwise
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zbtest::zbtest;
///
/// let a = BigInt::from(5);  // 0b101
/// assert_eq!(zbtest(&a, 0), 1);  // bit 0 is set
/// assert_eq!(zbtest(&a, 1), 0);  // bit 1 is not set
/// assert_eq!(zbtest(&a, 2), 1);  // bit 2 is set
/// assert_eq!(zbtest(&a, 3), 0);  // bit 3 is not set
/// ```
pub fn zbtest(a: &z_t, bit: usize) -> i32 {
    // If a is zero, all bits are zero
    if a.is_zero() {
        return 0;
    }

    // Get the number of bits in the magnitude of a
    let num_bits = a.bits() as usize;

    // If the bit position is beyond the number of bits in a, return 0
    if bit >= num_bits {
        return 0;
    }

    // Use BigInt's bit() method to test the bit
    // bit() returns true if the bit is set, false otherwise
    // We only care about the magnitude, not the sign
    if a.magnitude().bit(bit as u64) {
        1
    } else {
        0
    }
}
