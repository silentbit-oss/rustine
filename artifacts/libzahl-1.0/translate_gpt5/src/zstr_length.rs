// Module: zstr_length
// Calculate string length for BigInt in given radix

use crate::{z_t, Result, ZahlError};
use num_bigint::BigInt;
use num_traits::{Zero, Signed};

/// Calculate the number of characters needed to represent a BigInt in a given radix
///
/// # Arguments
/// * `a` - The BigInt to calculate string length for
/// * `radix` - The radix (base) to use (must be between 2 and 36)
///
/// # Returns
/// * `Ok(usize)` - The number of characters needed (including sign if negative)
/// * `Err(ZahlError::InvalidRadix)` - If radix is not between 2 and 36
///
/// # Notes
/// - For zero, returns 1 (the character '0')
/// - For negative numbers, includes the '-' sign in the count
/// - The radix must be between 2 and 36 inclusive
///
/// # Example
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zstr_length::zstr_length;
///
/// let num = BigInt::from(123);
/// assert_eq!(zstr_length(&num, 10).unwrap(), 3); // "123"
///
/// let num = BigInt::from(-123);
/// assert_eq!(zstr_length(&num, 10).unwrap(), 4); // "-123"
///
/// let num = BigInt::from(0);
/// assert_eq!(zstr_length(&num, 10).unwrap(), 1); // "0"
///
/// let num = BigInt::from(255);
/// assert_eq!(zstr_length(&num, 16).unwrap(), 2); // "ff"
///
/// let num = BigInt::from(255);
/// assert_eq!(zstr_length(&num, 2).unwrap(), 8); // "11111111"
/// ```
pub fn zstr_length(a: &z_t, radix: u64) -> Result<usize> {
    // Validate radix range (2-36 is standard for string representations)
    if radix < 2 || radix > 36 {
        return Err(ZahlError::InvalidRadix(radix as u32));
    }

    // Handle zero case
    if a.is_zero() {
        return Ok(1);
    }

    // Get absolute value for counting digits
    let mut num = a.abs();
    let is_negative = a < &BigInt::zero();

    // Count digits using repeated division by powers of radix
    // This algorithm uses squaring to find the largest power of radix
    // that fits in num, then counts down efficiently
    let radix_bigint = BigInt::from(radix);
    let mut total_digits = 1;

    while !num.is_zero() {
        // Start with radix and repeatedly square to find largest power that fits
        let mut mag = radix_bigint.clone();
        let mut div = mag.clone();
        let mut size_temp = 1usize;

        // Square mag until it exceeds num, keeping track of div (the previous value)
        while mag <= num {
            div = mag.clone();
            mag = &mag * &mag;
            size_temp = size_temp.checked_shl(1).unwrap_or(usize::MAX);
        }

        // Back up one step (we went one too far)
        size_temp = size_temp >> 1;
        total_digits += size_temp;

        // Divide num by the largest power we found
        num = num / div;
    }

    // Add 1 for the minus sign if negative
    if is_negative {
        Ok(total_digits + 1)
    } else {
        Ok(total_digits)
    }
}
