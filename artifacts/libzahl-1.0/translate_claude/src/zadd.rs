// Module: zadd
// Implements addition operations for BigInt

use crate::z_t;
use num_traits::Zero;
use num_traits::Signed;

/// Add absolute values of two BigInts and store the result.
/// This is a helper function that performs unsigned addition: a = |b| + |c|
/// Equivalent to C function: void zadd_unsigned(z_t a, z_t b, z_t c)
///
/// # Arguments
/// * `a` - The destination BigInt to store the sum of absolute values
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zadd::zadd_unsigned;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(-10);
/// let c = BigInt::from(5);
/// zadd_unsigned(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(15));  // |-10| + |5| = 15
/// ```
pub fn zadd_unsigned(a: &mut z_t, b: &z_t, c: &z_t) {
    // Handle zero cases
    if b.is_zero() {
        *a = c.abs();
        return;
    }
    if c.is_zero() {
        *a = b.abs();
        return;
    }

    // Add the absolute values
    *a = b.abs() + c.abs();
}

/// Add two BigInts and store the result.
/// Equivalent to C function: void zadd(z_t a, z_t b, z_t c)
///
/// This function computes a = b + c, handling all sign combinations correctly:
/// - If either operand is zero, copies the other operand
/// - If b == c, efficiently computes 2*b
/// - Handles mixed signs using zadd_unsigned and zsub_unsigned helpers
///
/// # Arguments
/// * `a` - The destination BigInt to store the sum
/// * `b` - The first source BigInt
/// * `c` - The second source BigInt
///
/// # Examples
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zadd::zadd;
///
/// let mut a = BigInt::from(0);
/// let b = BigInt::from(10);
/// let c = BigInt::from(5);
/// zadd(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(15));
///
/// // Handles negative numbers
/// let b = BigInt::from(-10);
/// let c = BigInt::from(5);
/// zadd(&mut a, &b, &c);
/// assert_eq!(a, BigInt::from(-5));
/// ```
pub fn zadd(a: &mut z_t, b: &z_t, c: &z_t) {
    use crate::zset::zset;
    use crate::zsub::zsub_unsigned;

    // Handle zero cases
    if b.is_zero() {
        zset(a, c);
        return;
    }
    if c.is_zero() {
        zset(a, b);
        return;
    }

    // If b == c, compute 2*b
    if std::ptr::eq(b, c) || b == c {
        *a = b * 2;
        return;
    }

    // Handle different sign combinations
    let b_negative = b.is_negative();
    let c_negative = c.is_negative();

    if b_negative || c_negative {
        if b_negative {
            if c_negative {
                // Both negative: add absolute values and negate
                zadd_unsigned(a, b, c);
                *a = -&*a;
            } else {
                // b negative, c positive: c - |b|
                zsub_unsigned(a, c, b);
            }
        } else {
            // b positive, c negative: b - |c|
            zsub_unsigned(a, b, c);
        }
    } else {
        // Both positive: add absolute values
        zadd_unsigned(a, b, c);
    }
}

