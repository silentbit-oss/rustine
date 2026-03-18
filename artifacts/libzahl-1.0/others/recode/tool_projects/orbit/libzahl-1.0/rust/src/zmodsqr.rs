// Module: zmodsqr
// Modular square: a = (b * b) % c

use crate::z_t;
use crate::Result;
use crate::zsqr::zsqr;
use crate::zmod::zmod;

/// Compute modular square: a = (b * b) % c
///
/// This function computes the square of b, then reduces it modulo c.
/// The result is stored in `a`.
///
/// # Arguments
/// * `a` - Output: the result (b * b) % c
/// * `b` - The value to square
/// * `c` - The modulus
///
/// # Returns
/// * `Ok(())` on success
/// * `Err(ZahlError::DivisionByZero)` if c is zero
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmodsqr::zmodsqr};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(17);
/// let c = BigInt::from(10);
/// let mut a = BigInt::from(0);
/// zmodsqr(&mut a, &b, &c).unwrap();
/// assert_eq!(a, BigInt::from(9)); // (17 * 17) % 10 = 289 % 10 = 9
/// ```
pub fn zmodsqr(a: &mut z_t, b: &z_t, c: &z_t) -> Result<()> {
    // Handle aliasing: if a and c are the same reference, we need to clone c
    // In the C version, they used a temporary variable libzahl_tmp_modsqr
    // In Rust, we simply clone when necessary

    let c_clone = c.clone();

    // Square b
    let mut square = z_t::from(0);
    zsqr(&mut square, b);

    // Take modulo
    zmod(a, &square, &c_clone)
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zmodsqr_basic() {
        let b = BigInt::from(17);
        let c = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        // (17 * 17) % 10 = 289 % 10 = 9
        assert_eq!(a, BigInt::from(9));
    }

    #[test]
    fn test_zmodsqr_zero() {
        let b = BigInt::from(0);
        let c = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmodsqr_negative() {
        let b = BigInt::from(-7);
        let c = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        // (-7 * -7) % 10 = 49 % 10 = 9
        assert_eq!(a, BigInt::from(9));
    }

    #[test]
    fn test_zmodsqr_zero_modulus() {
        let b = BigInt::from(5);
        let c = BigInt::from(0);
        let mut a = BigInt::from(0);
        let result = zmodsqr(&mut a, &b, &c);
        assert!(result.is_err());
    }

    #[test]
    fn test_zmodsqr_large() {
        let b = BigInt::from(12345);
        let c = BigInt::from(1000);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        // (12345 * 12345) % 1000 = 152399025 % 1000 = 25
        assert_eq!(a, BigInt::from(25));
    }

    #[test]
    fn test_zmodsqr_one() {
        let b = BigInt::from(1);
        let c = BigInt::from(10);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        assert_eq!(a, BigInt::from(1));
    }

    #[test]
    fn test_zmodsqr_modulus_larger_than_square() {
        let b = BigInt::from(5);
        let c = BigInt::from(100);
        let mut a = BigInt::from(0);
        zmodsqr(&mut a, &b, &c).unwrap();
        // (5 * 5) % 100 = 25
        assert_eq!(a, BigInt::from(25));
    }

    #[test]
    fn test_zmodsqr_aliasing() {
        // Test when a and c might be the same (although in Rust they can't be due to borrowing)
        // This tests the correctness of the implementation
        let b = BigInt::from(7);
        let c = BigInt::from(10);
        let mut a = c.clone();
        zmodsqr(&mut a, &b, &c).unwrap();
        // (7 * 7) % 10 = 49 % 10 = 9
        assert_eq!(a, BigInt::from(9));
    }
}
