// Module: zbset
// Implements bit setting, clearing, and flipping for BigInt

use crate::z_t;
use crate::zset::zset;
use num_traits::{Zero, One, Signed};
use num_bigint::{BigInt, Sign};

/// Set, clear, or flip a bit in a BigInt.
/// Equivalent to C function: void zbset(z_t a, z_t b, size_t bit, int action)
///
/// This function modifies a by setting, clearing, or flipping the bit at the
/// specified position based on the action parameter:
/// - action > 0: Set the bit (make it 1)
/// - action == 0: Clear the bit (make it 0)
/// - action < 0: Flip the bit (toggle between 0 and 1)
///
/// # Arguments
/// * `a` - The destination BigInt (will be modified)
/// * `b` - The source BigInt (copied to a, then the bit is modified)
/// * `bit` - The bit position to modify (0-indexed)
/// * `action` - The action to perform: >0 for set, ==0 for clear, <0 for flip
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zbset::zbset;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(5);  // 0b101
/// zbset(&mut a, &b, 1, 1);  // Set bit 1: 0b101 -> 0b111 = 7
/// assert_eq!(a, BigInt::from(7));
///
/// zbset(&mut a, &b, 2, 0);  // Clear bit 2: 0b101 -> 0b001 = 1
/// assert_eq!(a, BigInt::from(1));
///
/// zbset(&mut a, &b, 0, -1);  // Flip bit 0: 0b101 -> 0b100 = 4
/// assert_eq!(a, BigInt::from(4));
/// ```
pub fn zbset(a: &mut z_t, b: &z_t, bit: usize, action: i32) {
    // Copy b to a first
    zset(a, b);

    // The C implementation operates on the magnitude (absolute value) and preserves the sign.
    // We need to do the same in Rust to match the behavior.

    // Get the sign and magnitude
    let sign = a.sign();
    let mut magnitude = a.abs();

    // Create a mask for the bit position
    let mask = BigInt::one() << bit;

    if action > 0 {
        // Set the bit (OR with mask)
        magnitude |= &mask;
    } else if action < 0 {
        // Flip the bit (XOR with mask)
        magnitude ^= &mask;
    } else {
        // Clear the bit (AND with NOT mask)
        magnitude &= !&mask;
    }

    // Restore the sign
    *a = match sign {
        num_bigint::Sign::Minus => -magnitude,
        num_bigint::Sign::Plus => magnitude,
        num_bigint::Sign::NoSign => magnitude, // This handles zero
    };
}
