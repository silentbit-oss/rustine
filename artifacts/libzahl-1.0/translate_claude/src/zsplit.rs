// Module: zsplit
// Implements splitting a BigInt at a bit position

use crate::z_t;
use crate::ztrunc::ztrunc;
use crate::zrsh::zrsh;
use num_traits::Zero;

/// Split a BigInt at a bit position into high and low parts.
/// Equivalent to C function: void zsplit(z_t high, z_t low, z_t a, size_t delim)
///
/// This function splits a BigInt at the specified bit position:
/// - low contains the bits from 0 to delim-1 (least significant bits)
/// - high contains the bits from delim onwards (most significant bits)
///
/// The operation is equivalent to:
/// - low = a & ((1 << delim) - 1)
/// - high = a >> delim
///
/// # Arguments
/// * `high` - The destination for the high-order bits (bits >= delim)
/// * `low` - The destination for the low-order bits (bits < delim)
/// * `a` - The source BigInt to split
/// * `delim` - The bit position at which to split (0-indexed)
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zsplit::zsplit;
///
/// let mut high = BigInt::from(0);
/// let mut low = BigInt::from(0);
/// let a = BigInt::from(255);  // 0b11111111
/// zsplit(&mut high, &mut low, &a, 4);
/// assert_eq!(low, BigInt::from(15));   // 0b1111 = 15 (lower 4 bits)
/// assert_eq!(high, BigInt::from(15));  // 0b1111 = 15 (upper 4 bits)
///
/// let a = BigInt::from(123);  // 0b1111011
/// zsplit(&mut high, &mut low, &a, 3);
/// assert_eq!(low, BigInt::from(3));    // 0b011 = 3 (lower 3 bits)
/// assert_eq!(high, BigInt::from(15));  // 0b1111 = 15 (upper bits)
/// ```
pub fn zsplit(high: &mut z_t, low: &mut z_t, a: &z_t, delim: usize) {
    // If a is zero, both parts are zero
    if a.is_zero() {
        *high = z_t::zero();
        *low = z_t::zero();
        return;
    }

    // Handle the case where high and a are the same reference
    // We need to compute in a specific order to avoid overwriting data
    if std::ptr::eq(high as *const z_t, a as *const z_t) {
        // Compute low first, then high (since high == a)
        ztrunc(low, a, delim);
        zrsh(high, a, delim);
    } else {
        // Normal case: compute high first, then low
        zrsh(high, a, delim);
        ztrunc(low, a, delim);
    }
}
