// Module: zsub
// Implements subtraction operations for BigInt

use crate::z_t;
use crate::zcmpmag::zcmpmag;
use num_traits::Zero;
use num_traits::Signed;

/// Subtract absolute values of two BigInts and store the result.
/// This is a helper function that performs unsigned subtraction: a = |b| - |c|
/// Equivalent to C function: void zsub_unsigned(z_t a, z_t b, z_t c)
///
/// The result's sign is determined by the magnitude comparison:
/// - If |b| > |c|, result is positive
/// - If |b| < |c|, result is negative
/// - If |b| == |c|, result is zero
///
/// # Arguments
/// * `a` - The destination BigInt to store the difference
/// * `b` - The first source BigInt (minuend)
/// * `c` - The second source BigInt (subtrahend)
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zsub::zsub_unsigned;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(-20);
/// let c = BigInt::from(10);
/// zsub_unsigned(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(10));  // |-20| - |10| = 10
/// ```
pub fn zsub_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    // Handle zero cases
    if b.is_zero() {
        *a = -c.abs();
        return;
    }
    if c.is_zero() {
        *a = b.abs();
        return;
    }

    // Compare magnitudes
    let magcmp = zcmpmag(b, c);

    if magcmp == 0 {
        // |b| == |c|, result is zero
        *a = z_t::zero();
    } else if magcmp > 0 {
        // |b| > |c|, result is positive
        *a = b.abs() - c.abs();
    } else {
        // |b| < |c|, result is negative
        *a = -(c.abs() - b.abs());
    }
}

/// Subtract two BigInts and store the result.
/// Equivalent to C function: void zsub(z_t a, z_t b, z_t c)
///
/// This function computes a = b - c, handling all sign combinations correctly:
/// - If b == c, result is zero
/// - If b is zero, result is -c
/// - If c is zero, result is b
/// - Handles mixed signs using zadd_unsigned and zsub_unsigned helpers
///
/// # Arguments
/// * `a` - The destination BigInt to store the difference
/// * `b` - The first source BigInt (minuend)
/// * `c` - The second source BigInt (subtrahend)
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zsub::zsub;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(10);
/// let c = BigInt::from(5);
/// zsub(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(5));
///
/// // Handles negative numbers
/// let b = BigInt::from(-10);
/// let c = BigInt::from(5);
/// zsub(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(-15));
/// ```
pub fn zsub(a: &mut z_t, b: &z_t, c: &z_t) {
    use crate::zset::zset;
    use crate::zneg::zneg;
    use crate::zadd::zadd_unsigned;

    // If b == c, result is zero
    if std::ptr::eq(b, c) || b == c {
        *a = z_t::zero();
        return;
    }

    // Handle zero cases
    if b.is_zero() {
        zneg(a, c);
        return;
    }
    if c.is_zero() {
        zset(a, b);
        return;
    }

    // Handle different sign combinations
    let b_negative = b.is_negative();
    let c_negative = c.is_negative();

    if b_negative || c_negative {
        if b_negative {
            if c_negative {
                // Both negative: -(|b| - |c|) = |c| - |b|
                zsub_unsigned(a, c, b);
            } else {
                // b negative, c positive: -(|b| + |c|)
                zadd_unsigned(a, b, c);
                *a = -&*a;
            }
        } else {
            // b positive, c negative: |b| + |c|
            zadd_unsigned(a, b, c);
        }
    } else {
        // Both positive: |b| - |c|
        zsub_unsigned(a, b, c);
    }
}

