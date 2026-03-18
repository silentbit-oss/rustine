// Module: zpow
// Raise BigInt to BigInt power

use crate::z_t;
use crate::Result;
use crate::ZahlError;
use crate::zmul::zmul;
use crate::zsqr::zsqr;
use crate::zset::zset;
use crate::zsetu::zsetu;
use num_bigint::BigInt;
use num_traits::{Zero, One, Signed};

/// Raise a BigInt to a BigInt power: a = b^c
///
/// This function computes b raised to the power c using the
/// exponentiation by squaring algorithm for efficiency.
///
/// # Arguments
/// * `a` - Output: the result b^c
/// * `b` - The base
/// * `c` - The exponent (BigInt)
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::InvalidDomain)` for:
///   - 0^0 (indeterminate form)
///   - non-zero base to negative exponent (would be fractional)
///
/// # Notes
/// * For negative exponents with non-zero base, returns 0 (integer division result)
/// * For zero exponent, returns 1 (except for 0^0 which is an error)
/// * For zero base with positive exponent, returns 0
///
/// # Examples
/// ```
/// use libzahl::{z_t, zpow::zpow};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(2);
/// let c = BigInt::from(10);
/// let mut a = BigInt::from(0);
/// zpow(&mut a, &b, &c).unwrap();
/// assert_eq!(a, BigInt::from(1024));
/// ```
pub fn zpow(a: &mut z_t, b: &z_t, c: &z_t) -> Result<()> {
    // Handle c <= 0
    if c.is_zero() {
        if b.is_zero() {
            // 0^0 is indeterminate
            return Err(ZahlError::InvalidDomain);
        }
        // anything^0 = 1
        zsetu(a, 1);
        return Ok(());
    } else if c.is_negative() {
        if b.is_zero() {
            // 0^(-n) would be division by zero
            return Err(ZahlError::InvalidDomain);
        }
        // For negative exponents with non-zero base, result would be fractional.
        // In integer arithmetic, this becomes 0 (like 1/large_number)
        *a = BigInt::zero();
        return Ok(());
    }

    // Handle b == 0 (and c > 0 from above)
    if b.is_zero() {
        *a = BigInt::zero();
        return Ok(());
    }

    // At this point, c > 0 and b != 0
    // Exponentiation by squaring, processing bits of exponent

    // Clone inputs to avoid aliasing issues
    let mut tb = b.clone();
    let tc = c.clone();
    let mut result = BigInt::one();

    // Get the bits of the exponent
    // We'll iterate through the bytes/bits of the BigInt
    let bits = tc.bits();

    // Process each bit of the exponent
    for i in 0..bits {
        // Check if bit i is set
        if tc.bit(i) {
            let temp_result = result.clone();
            zmul(&mut result, &temp_result, &tb);
        }
        // Square the base for next bit position
        // Only square if we're not at the last bit
        if i + 1 < bits {
            let temp_tb = tb.clone();
            zsqr(&mut tb, &temp_tb);
        }
    }

    *a = result;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zpow_basic() {
        let b = BigInt::from(2);
        let c = BigInt::from(10);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(1024));
    }

    #[test]
    fn test_zpow_zero_exponent() {
        let b = BigInt::from(123);
        let c = BigInt::from(0);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(1));
    }

    #[test]
    fn test_zpow_zero_base() {
        let b = BigInt::from(0);
        let c = BigInt::from(5);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zpow_zero_zero() {
        let b = BigInt::from(0);
        let c = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zpow(&mut a, &b, &c);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zpow_one() {
        let b = BigInt::from(123);
        let c = BigInt::from(1);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(123));
    }

    #[test]
    fn test_zpow_negative_base() {
        let b = BigInt::from(-2);
        let c = BigInt::from(3);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(-8));
    }

    #[test]
    fn test_zpow_negative_base_even() {
        let b = BigInt::from(-2);
        let c = BigInt::from(4);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(16));
    }

    #[test]
    fn test_zpow_negative_exponent() {
        let b = BigInt::from(2);
        let c = BigInt::from(-3);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        // 2^(-3) = 1/8, which in integer arithmetic is 0
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zpow_negative_exponent_zero_base() {
        let b = BigInt::from(0);
        let c = BigInt::from(-3);
        let mut a = BigInt::from(0);
        let result = zpow(&mut a, &b, &c);
        // 0^(-3) would be division by zero
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zpow_large() {
        let b = BigInt::from(10);
        let c = BigInt::from(20);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        // 10^20 = 100000000000000000000
        let expected = BigInt::parse_bytes(b"100000000000000000000", 10).unwrap();
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zpow_very_large_exponent() {
        let b = BigInt::from(2);
        let c = BigInt::from(100);
        let mut a = BigInt::from(0);
        zpow(&mut a, &b, &c).unwrap();
        // 2^100 = 1267650600228229401496703205376
        let expected = BigInt::parse_bytes(b"1267650600228229401496703205376", 10).unwrap();
        assert_eq!(a, expected);
    }
}
