// Module: zmodpowu
// Modular exponentiation with u64 exponent: a = (b ^ c) % d

use crate::z_t;
use crate::Result;
use crate::ZahlError;
use crate::zmodmul::zmodmul;
use crate::zmodsqr::zmodsqr;
use crate::zmod::zmod;
use crate::zsetu::zsetu;
use num_bigint::BigInt;
use num_traits::Zero;

/// Compute modular exponentiation with u64 exponent: a = (b ^ c) % d
///
/// This function computes b raised to the power c, reduced modulo d,
/// using efficient modular exponentiation algorithm (square-and-multiply).
/// The exponent is a u64 for efficiency.
///
/// # Arguments
/// * `a` - Output: the result (b ^ c) % d
/// * `b` - The base
/// * `c` - The exponent (u64)
/// * `d` - The modulus
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::InvalidDomain)` for:
///   - 0^0 (indeterminate form)
///   - Division by zero (d == 0)
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmodpowu::zmodpowu};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(2);
/// let d = BigInt::from(1000);
/// let mut a = BigInt::from(0);
/// zmodpowu(&mut a, &b, 10, &d).unwrap();
/// assert_eq!(a, BigInt::from(24)); // 2^10 % 1000 = 1024 % 1000 = 24
/// ```
pub fn zmodpowu(a: &mut z_t, b: &z_t, c: u64, d: &z_t) -> Result<()> {
    // Handle c == 0
    if c == 0 {
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
    let td = d.clone();

    // Reduce base modulo d
    let tb_clone = tb.clone();
    zmod(&mut tb, &tb_clone, &td)?;

    // Initialize result to 1
    let mut result = BigInt::from(1);

    // Exponentiation by squaring
    let mut exp = c;

    while exp > 0 {
        if exp & 1 == 1 {
            // If bit is set, multiply result by current base
            let result_clone = result.clone();
            zmodmul(&mut result, &result_clone, &tb, &td)?;
        }
        // Square the base for next iteration
        exp >>= 1;
        if exp > 0 {
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
    fn test_zmodpowu_basic() {
        let b = BigInt::from(2);
        let d = BigInt::from(1000);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 10, &d).unwrap();
        // 2^10 % 1000 = 1024 % 1000 = 24
        assert_eq!(a, BigInt::from(24));
    }

    #[test]
    fn test_zmodpowu_zero_exponent() {
        let b = BigInt::from(123);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 0, &d).unwrap();
        assert_eq!(a, BigInt::from(1));
    }

    #[test]
    fn test_zmodpowu_zero_base() {
        let b = BigInt::from(0);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 5, &d).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmodpowu_zero_zero() {
        let b = BigInt::from(0);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        let result = zmodpowu(&mut a, &b, 0, &d);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zmodpowu_zero_modulus() {
        let b = BigInt::from(2);
        let d = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zmodpowu(&mut a, &b, 3, &d);
        assert!(result.is_err());
        assert!(matches!(result.unwrap_err(), ZahlError::InvalidDomain));
    }

    #[test]
    fn test_zmodpowu_one_exponent() {
        let b = BigInt::from(123);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 1, &d).unwrap();
        // 123^1 % 100 = 23
        assert_eq!(a, BigInt::from(23));
    }

    #[test]
    fn test_zmodpowu_negative_base() {
        let b = BigInt::from(-3);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 3, &d).unwrap();
        // (-3)^3 % 10 = -27 % 10 = 7 (libzahl uses mathematical modulo, always returns positive)
        // C result: 7, not -3
        assert_eq!(a, BigInt::from(7));
    }

    #[test]
    fn test_zmodpowu_large() {
        let b = BigInt::from(3);
        let d = BigInt::from(1000);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 100, &d).unwrap();
        // 3^100 % 1000 - use BigInt's modpow to verify
        let expected = b.modpow(&BigInt::from(100), &d);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodpowu_very_large() {
        let b = BigInt::from(2);
        let d = BigInt::from(100000);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 256, &d).unwrap();
        // 2^256 % 100000
        let expected = b.modpow(&BigInt::from(256), &d);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodpowu_small_modulus() {
        let b = BigInt::from(7);
        let d = BigInt::from(5);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 13, &d).unwrap();
        // 7^13 % 5
        let expected = b.modpow(&BigInt::from(13), &d);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodpowu_two() {
        let b = BigInt::from(5);
        let d = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodpowu(&mut a, &b, 2, &d).unwrap();
        // 5^2 % 10 = 25 % 10 = 5
        assert_eq!(a, BigInt::from(5));
    }
}
