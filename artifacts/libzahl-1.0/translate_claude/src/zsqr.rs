// Module: zsqr
// Square a BigInt

use crate::z_t;

/// Square a BigInt: a = b^2
///
/// This function computes the square of an arbitrary precision integer.
/// The result is stored in `a`.
///
/// # Arguments
/// * `a` - Output: the square of b
/// * `b` - The value to square
///
/// # Examples
/// ```
/// use libzahl::{z_t, zsqr::zsqr};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(123);
/// let a = zsqr(&b);
/// assert_eq!(a, BigInt::from(15129));
/// ```
pub fn zsqr(a: &mut z_t, b: &z_t) {
    *a = b * b;
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zsqr_basic() {
        let b = BigInt::from(123);
        let mut a = BigInt::from(0);
        zsqr(&mut a, &b);
        assert_eq!(a, BigInt::from(15129));
    }

    #[test]
    fn test_zsqr_negative() {
        let b = BigInt::from(-123);
        let mut a = BigInt::from(0);
        zsqr(&mut a, &b);
        assert_eq!(a, BigInt::from(15129));
    }

    #[test]
    fn test_zsqr_zero() {
        let b = BigInt::from(0);
        let mut a = BigInt::from(0);
        zsqr(&mut a, &b);
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zsqr_large() {
        let b = BigInt::from(999999);
        let mut a = BigInt::from(0);
        zsqr(&mut a, &b);
        assert_eq!(a, BigInt::from(999998000001i64));
    }
}
