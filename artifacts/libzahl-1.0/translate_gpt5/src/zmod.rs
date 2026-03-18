// Module: zmod
// Implements modulo operation for BigInt

use crate::z_t;
use crate::Result;
use crate::zdivmod::zdivmod;

/// Compute modulo: a = b % c
///
/// This function computes the remainder of b divided by c and stores it in a.
/// It discards the quotient. Returns an error if the divisor is zero.
///
/// # Arguments
/// * `a` - The destination BigInt for the remainder (b % c)
/// * `b` - The dividend BigInt
/// * `c` - The divisor BigInt
///
/// # Returns
/// * `Ok(())` if the operation succeeds
/// * `Err(ZahlError::DivisionByZero)` if c is zero
///
/// # Examples
/// ```
/// use libzahl::{z_t, zmod::zmod};
/// let mut result = z_t::from(0);
/// let dividend = z_t::from(17);
/// let divisor = z_t::from(5);
/// zmod(&mut result, &dividend, &divisor).unwrap();
/// assert_eq!(result, z_t::from(2));
/// ```
pub fn zmod(a: &mut z_t, b: &z_t, c: &z_t) -> Result<()> {
    // Use a temporary variable for the quotient that we discard
    let mut temp_quotient = z_t::from(0);
    zdivmod(&mut temp_quotient, a, b, c)
}
