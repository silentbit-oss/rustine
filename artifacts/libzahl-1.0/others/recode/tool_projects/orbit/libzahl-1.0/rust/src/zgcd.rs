// Module: zgcd
// Implements greatest common divisor operation for BigInt

use crate::z_t;
use num_integer::Integer;

/// Computes the greatest common divisor (GCD) of b and c, storing the result in a.
/// Equivalent to C function: void zgcd(z_t a, z_t b, z_t c)
///
/// The GCD is always non-negative, except when both b and c are negative,
/// in which case the result is negative (matching the C implementation behavior).
///
/// # Arguments
/// * `a` - The destination BigInt to store the GCD result
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zgcd::zgcd;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(48);
/// let c = BigInt::from(18);
/// zgcd(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(6));
/// ```
pub fn zgcd(a: &mut z_t, b: &z_t, c: &z_t) {
    use num_traits::Zero;
    use num_bigint::Sign;

    // Match C implementation's special cases
    // If b == c, return b
    if b == c {
        *a = b.clone();
        return;
    }

    // If b is zero, return c (preserving sign)
    if b.is_zero() {
        *a = c.clone();
        return;
    }

    // If c is zero, return b (preserving sign)
    if c.is_zero() {
        *a = b.clone();
        return;
    }

    // Use the num_integer::Integer trait's gcd() method
    // BigInt already implements this trait
    let gcd_result = b.gcd(c);

    // The C implementation preserves negative sign when both inputs are negative
    // The Integer::gcd() method returns the absolute value, so we need to adjust
    if b.sign() == Sign::Minus && c.sign() == Sign::Minus {
        *a = -gcd_result;
    } else {
        *a = gcd_result;
    }
}

