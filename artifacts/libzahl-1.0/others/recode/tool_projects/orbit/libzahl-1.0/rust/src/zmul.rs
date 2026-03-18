// Module: zmul
// Multiplication of two BigInts

use crate::z_t;

/// Multiply two BigInts: a = b * c
///
/// This function multiplies two arbitrary precision integers.
/// The result is stored in `a`.
///
/// # Arguments
/// * `a` - Output: the product b * c
/// * `b` - First multiplicand
/// * `c` - Second multiplicand
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmul::zmul};
/// use num_bigint::BigInt;
///
/// let b = BigInt::from(123);
/// let c = BigInt::from(456);
/// let a = zmul(&b, &c);
/// assert_eq!(a, BigInt::from(56088));
/// ```
pub fn zmul(a: &mut z_t, b: &z_t, c: &z_t) {
    *a = b * c;
}

#[cfg(test)]
mod tests {
    use super::*;
    use num_bigint::BigInt;

    #[test]
    fn test_zmul_basic() {
        let b = BigInt::from(123);
        let c = BigInt::from(456);
        let mut a = BigInt::from(0);
        zmul(&mut a, &b, &c);
        assert_eq!(a, BigInt::from(56088));
    }

    #[test]
    fn test_zmul_negative() {
        let b = BigInt::from(-123);
        let c = BigInt::from(456);
        let mut a = BigInt::from(0);
        zmul(&mut a, &b, &c);
        assert_eq!(a, BigInt::from(-56088));
    }

    #[test]
    fn test_zmul_zero() {
        let b = BigInt::from(0);
        let c = BigInt::from(456);
        let mut a = BigInt::from(0);
        zmul(&mut a, &b, &c);
        assert_eq!(a, BigInt::from(0));
    }

    #[test]
    fn test_zmul_large() {
        let b = BigInt::from(999999i64);
        let c = BigInt::from(888888i64);
        let mut a = BigInt::from(0);
        zmul(&mut a, &b, &c);
        assert_eq!(a, BigInt::from(888887111112i64));
    }
}
