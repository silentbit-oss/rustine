// Module: zmodmul
// Modular multiplication: a = (b * c) % d

use crate::z_t;
use crate::Result;
use crate::zmul::zmul;
use crate::zmod::zmod;

/// Compute modular multiplication: a = (b * c) % d
///
/// This function computes the product of b and c, then reduces it modulo d.
/// The result is stored in `a`.
///
/// # Arguments
/// * `a` - Output: the result (b * c) % d
/// * `b` - First multiplicand
/// * `c` - Second multiplicand
/// * `d` - The modulus
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::DivisionByZero)` if d is zero
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmodmul::zmodmul};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(123);
/// let c = BigInt::from(456);
/// let d = BigInt::from(100);
/// let mut a = BigInt::from(0);
/// zmodmul(&mut a, &b, &c, &d).unwrap();
/// assert_eq!(a, BigInt::from(88)); // (123 * 456) % 100 = 56088 % 100 = 88
/// ```
pub fn zmodmul(a: &mut z_t, b: &z_t, c: &z_t, d: &z_t) -> Result<()> {
    // Handle aliasing: if a and d are the same reference, we need to clone d
    // In the C version, they used a temporary variable libzahl_tmp_modmul
    // In Rust, we simply clone when necessary

    let d_clone = d.clone();

    // Multiply b * c
    let mut product = z_t::from(0);
    zmul(&mut product, b, c);

    // Take modulo
    zmod(a, &product, &d_clone)
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zmodmul_basic() {
        let b = BigInt::from(123);
        let c = BigInt::from(456);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodmul(&mut a, &b, &c, &d).unwrap();
        // (123 * 456) % 100 = 56088 % 100 = 88
        assert_eq!(a, BigInt::from(88));
    }

    #[test]
    fn test_zmodmul_zero_multiplier() {
        let b = BigInt::from(0);
        let c = BigInt::from(456);
        let d = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodmul(&mut a, &b, &c, &d).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmodmul_negative() {
        let b = BigInt::from(-10);
        let c = BigInt::from(7);
        let d = BigInt::from(13);
        let mut a = BigInt::from(0);
        zmodmul(&mut a, &b, &c, &d).unwrap();
        // (-10 * 7) % 13 = -70 % 13 = 5 (libzahl uses mathematical modulo, always returns positive)
        // C result: 5, not -5
        assert_eq!(a, BigInt::from(5));
    }

    #[test]
    fn test_zmodmul_zero_modulus() {
        let b = BigInt::from(123);
        let c = BigInt::from(456);
        let d = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zmodmul(&mut a, &b, &c, &d);
        assert!(result.is_err());
    }

    #[test]
    fn test_zmodmul_large() {
        let b = BigInt::from(999999);
        let c = BigInt::from(888888);
        let d = BigInt::from(12345);
        let mut a = BigInt::from(0);
        zmodmul(&mut a, &b, &c, &d).unwrap();
        // (999999 * 888888) % 12345
        let expected = (BigInt::from(999999) * BigInt::from(888888)) % BigInt::from(12345);
        assert_eq!(a, expected);
    }

    #[test]
    fn test_zmodmul_aliasing() {
        // Test when a and d might be the same (although in Rust they can't be due to borrowing)
        // This tests the correctness of the implementation
        let b = BigInt::from(7);
        let c = BigInt::from(8);
        let d = BigInt::from(10);
        let mut a = d.clone();
        zmodmul(&mut a, &b, &c, &d).unwrap();
        // (7 * 8) % 10 = 56 % 10 = 6
        assert_eq!(a, BigInt::from(6));
    }
}
