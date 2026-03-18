// Module: zmodpow
// Modular exponentiation: a = (b ^ c) % d

use crate::z_t;
use crate::Result;
use crate::ZahlError;
use crate::zmodmul::zmodmul;
use crate::zmodsqr::zmodsqr;
use crate::zmod::zmod;
use crate::zsetu::zsetu;
use num_bigint::BigInt;
use num_traits::{Zero, Signed};

/// Compute modular exponentiation: a = (b ^ c) % d
///
/// This function computes b raised to the power c, reduced modulo d,
/// using efficient modular exponentiation algorithm (square-and-multiply).
///
/// # Arguments
/// * `a` - Output: the result (b ^ c) % d
/// * `b` - The base
/// * `c` - The exponent
/// * `d` - The modulus
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::InvalidDomain)` for:
///   - 0^0 (indeterminate form)
///   - Division by zero (d == 0)
///   - Negative exponent with zero base (0^(-n))
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmodpow::zmodpow};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(2);
/// let c = BigInt::from(10);
/// let d = BigInt::from(1000);
/// let mut a = BigInt::from(0);
/// zmodpow(&mut a, &b, &c, &d).unwrap();
/// assert_eq!(a, BigInt::from(24)); // 2^10 % 1000 = 1024 % 1000 = 24
/// ```
pub fn zmodpow(a: &mut z_t, b: &z_t, c: &z_t, d: &z_t) -> Result<()> {
    // Handle c <= 0
    if c.is_zero() {
        if b.is_zero() {
            // 0^0 is indeterminate
            return Err(ZahlError::InvalidDomain);
        } else if d.is_zero() {
            // Division by zero
            return Err(ZahlError::InvalidDomain);
        }
        // anything^0 = 1
        zsetu(a, 1);
        return Ok(());
    } else if c.is_negative() {
        if b.is_zero() || d.is_zero() {
            // Division by zero
            return Err(ZahlError::InvalidDomain);
        }
        // For negative exponents, the result would be fractional
        // In integer arithmetic, this becomes 0
        *a = BigInt::zero();
        return Ok(());
    } else if d.is_zero() {
        // Division by zero
        return Err(ZahlError::InvalidDomain);
    } else if b.is_zero() {
        // 0^c = 0 for c > 0
        *a = BigInt::zero();
        return Ok(());
    }

    // At this point: c > 0, d != 0, b != 0

    // Clone inputs to avoid aliasing issues
    let mut tb = b.clone();
    let tc = c.clone();
    let td = d.clone();

    // Reduce base modulo d
    let tb_clone = tb.clone();
    zmod(&mut tb, &tb_clone, &td)?;

    // Initialize result to 1
    let mut result = BigInt::from(1);

    // Get number of bits in exponent
    let bits = tc.bits() as usize;

    // Process each bit of the exponent using square-and-multiply
    for i in 0..bits {
        // Check if bit i is set
        if tc.bit(i as u64) {
            // Multiply result by current base: result = (result * tb) % td
            let result_clone = result.clone();
            zmodmul(&mut result, &result_clone, &tb, &td)?;
        }
        // Square the base for next bit: tb = (tb * tb) % td
        // Only square if we're not at the last bit
        if i + 1 < bits {
            let tb_clone = tb.clone();
            zmodsqr(&mut tb, &tb_clone, &td)?;
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
    fn test_zmodpow_basic() {
        let b = BigInt::from(2);
        let c = BigInt::from(10);
        let d = BigInt::from(1000);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // 2^10 % 1000 = 1024 % 1000 = 24
        assert_eq!(a, BigInt::from(24));
    }

    #[test]
    fn test_zmodpow_zero_exponent() {
        let b = BigInt::from(123);
        let c = BigInt::from(0);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        assert_eq!(a, BigInt::from(1));
    }

    #[test]
    fn test_zmodpow_zero_base() {
        let b = BigInt::from(0);
        let c = BigInt::from(5);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmodpow_zero_zero() {
        let b = BigInt::from(0);
        let c = BigInt::from(0);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        let result = zmodpow(&mut a, &b, &c, &d);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zmodpow_zero_modulus() {
        let b = BigInt::from(2);
        let c = BigInt::from(3);
        let d = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zmodpow(&mut a, &b, &c, &d);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zmodpow_one_exponent() {
        let b = BigInt::from(123);
        let c = BigInt::from(1);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // 123^1 % 100 = 23
        assert_eq!(a, BigInt::from(23));
    }

    #[test]
    fn test_zmodpow_negative_base() {
        let b = BigInt::from(-3);
        let c = BigInt::from(3);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // (-3)^3 % 10 = -27 % 10 = 7 (libzahl uses mathematical modulo, always returns positive)
        // C result: 7, not -3
        assert_eq!(a, BigInt::from(7));
    }

    #[test]
    fn test_zmodpow_negative_exponent() {
        let b = BigInt::from(2);
        let c = BigInt::from(-3);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // Negative exponent in integer arithmetic returns 0
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmodpow_negative_exponent_zero_base() {
        let b = BigInt::from(0);
        let c = BigInt::from(-3);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        let result = zmodpow(&mut a, &b, &c, &d);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zmodpow_large() {
        let b = BigInt::from(3);
        let c = BigInt::from(100);
        let d = BigInt::from(1000);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // 3^100 % 1000 - use BigInt's modpow to verify
        use num_traits::Pow;
        let expected = b.modpow(&c, &d);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodpow_very_large() {
        let b = BigInt::from(2);
        let c = BigInt::from(256);
        let d = BigInt::from(100000);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // 2^256 % 100000
        let expected = b.modpow(&c, &d);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodpow_small_modulus() {
        let b = BigInt::from(7);
        let c = BigInt::from(13);
        let d = BigInt::from(5);
        let mut a = BigInt::from(0);
        zmodpow(&mut a, &b, &c, &d).unwrap();
        // 7^13 % 5
        let expected = b.modpow(&c, &d);
        assert_eq!(a, expected);
    }
}
