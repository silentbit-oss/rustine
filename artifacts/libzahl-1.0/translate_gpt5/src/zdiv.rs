// Module: zdiv
// Implements integer division for BigInt

use crate::z_t;
use crate::Result;
use crate::zdivmod::zdivmod;

/// Compute integer division: a = b / c
///
/// This function computes the quotient of b divided by c and stores it in a.
/// It discards the remainder. Returns an error if the divisor is zero.
///
/// # Arguments
/// * `a` - The destination BigInt for the quotient (b / c)
/// * `b` - The dividend BigInt
/// * `c` - The divisor BigInt
///
/// # Returns
/// * `Ok(())` if the operation succeeds
/// * `Err(ZahlError::DivisionByZero)` if c is zero
///
/// # Examples
/// ```
/// use libzahl::{z_t, zdiv::zdiv};
/// let mut result = z_t::from(0);
/// let dividend = z_t::from(17);
/// let divisor = z_t::from(5);
/// zdiv(&mut result, &dividend, &divisor).unwrap();
/// assert_eq!(result, z_t::from(3));
/// ```
pub fn zdiv(a: &mut z_t, b: &z_t, c: &z_t) -> Result<()> {
    // Use a temporary variable for the remainder that we discard
    let mut temp_remainder = z_t::from(0);
    zdivmod(a, &mut temp_remainder, b, c)
}
