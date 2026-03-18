// Module: zstr
// Convert BigInt to decimal string

use crate::z_t;

/// Convert BigInt to decimal string representation
///
/// # Arguments
/// * `a` - The BigInt to convert to string
///
/// # Returns
/// String representation of the BigInt in decimal format
///
/// # Example
/// ```
/// use num_bigint::BigInt;
/// use libzahl::zstr::zstr;
///
/// let num = BigInt::from(12345);
/// let s = zstr(&num);
/// assert_eq!(s, "12345");
///
/// let neg = BigInt::from(-9876);
/// let s = zstr(&neg);
/// assert_eq!(s, "-9876");
///
/// let zero = BigInt::from(0);
/// let s = zstr(&zero);
/// assert_eq!(s, "0");
/// ```
pub fn zstr(a: &z_t) -> String {
    // BigInt's to_string() already handles conversion to decimal string
    // including proper handling of negative numbers and zero
    a.to_string()
}
