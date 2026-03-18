// Module: zpowu
// Raise BigInt to u64 power

use crate::z_t;
use crate::Result;
use crate::ZahlError;
use crate::zmul::zmul;
use crate::zsqr::zsqr;
use crate::zset::zset;
use crate::zsetu::zsetu;
use num_bigint::BigInt;
use num_traits::Zero;

/// Raise a BigInt to a u64 power: a = b^c
///
/// This function computes b raised to the power c using the
/// exponentiation by squaring algorithm for efficiency.
///
/// # Arguments
/// * `a` - Output: the result b^c
/// * `b` - The base
/// * `c` - The exponent (u64)
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::InvalidDomain)` for 0^0 (indeterminate form)
///
/// # Examples
/// ```
/// use libzahl::{z_t, zpowu::zpowu};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(2);
/// let mut a = BigInt::from(0);
/// zpowu(&mut a, &b, 10).unwrap();
/// assert_eq!(a, BigInt::from(1024));
/// ```
pub fn zpowu(a: &mut z_t, b: &z_t, c: u64) -> Result<()> {
    // Handle c == 0
    if c == 0 {
        if b.is_zero() {
            // 0^0 is indeterminate
            return Err(ZahlError::InvalidDomain);
        }
        // anything^0 = 1
        zsetu(a, 1);
        return Ok(());
    }

    // Handle b == 0
    if b.is_zero() {
        // 0^c = 0 for c > 0
        *a = BigInt::zero();
        return Ok(());
    }

    // Exponentiation by squaring
    // We need a temporary variable for the base to avoid aliasing issues
    let mut tb = b.clone();
    let mut result = BigInt::from(1u32);
    let mut exp = c;

    while exp > 0 {
        if exp & 1 == 1 {
            // If bit is set, multiply result by current base
            let temp_result = result.clone();
            zmul(&mut result, &temp_result, &tb);
        }
        // Square the base for next iteration
        exp >>= 1;
        if exp > 0 {
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
    fn test_zpowu_basic() {
        let b = BigInt::from(2);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 10).unwrap();
        assert_eq!(a, BigInt::from(1024));
    }

    #[test]
    fn test_zpowu_zero_exponent() {
        let b = BigInt::from(123);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 0).unwrap();
        assert_eq!(a, BigInt::from(1));
    }

    #[test]
    fn test_zpowu_zero_base() {
        let b = BigInt::from(0);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 5).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zpowu_zero_zero() {
        let b = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zpowu(&mut a, &b, 0);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zpowu_one() {
        let b = BigInt::from(123);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 1).unwrap();
        assert_eq!(a, BigInt::from(123));
    }

    #[test]
    fn test_zpowu_negative_base() {
        let b = BigInt::from(-2);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 3).unwrap();
        assert_eq!(a, BigInt::from(-8));
    }

    #[test]
    fn test_zpowu_negative_base_even() {
        let b = BigInt::from(-2);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 4).unwrap();
        assert_eq!(a, BigInt::from(16));
    }

    #[test]
    fn test_zpowu_large() {
        let b = BigInt::from(10);
        let mut a = BigInt::from(0);
        zpowu(&mut a, &b, 20).unwrap();
        // 10^20 = 100000000000000000000
        let expected = BigInt::parse_bytes(b"100000000000000000000", 10).unwrap();
        assert_eq!(a, expected);
    }
}
