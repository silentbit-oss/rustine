// Module: zdivmod
// Implements simultaneous division and modulo operations for BigInt

use crate::z_t;
use crate::{ZahlError, Result};
use num_traits::Zero;

/// Compute both division and modulo: a = c / d, b = c % d
///
/// This function computes both the quotient and remainder simultaneously.
/// It returns an error if the divisor is zero.
///
/// # Arguments
/// * `a` - The destination BigInt for the quotient (c / d)
/// * `b` - The destination BigInt for the remainder (c % d)
/// * `c` - The dividend BigInt
/// * `d` - The divisor BigInt
///
/// # Returns
/// * `Ok(())` if the operation succeeds
/// * `Err(ZahlError::DivisionByZero)` if d is zero
///
/// # Examples
/// ```
/// use libzahl::{z_t, zdivmod::zdivmod};
/// let mut quotient = z_t::from(0);
/// let mut remainder = z_t::from(0);
/// let dividend = z_t::from(17);
/// let divisor = z_t::from(5);
/// zdivmod(&mut quotient, &mut remainder, &dividend, &divisor).unwrap();
/// assert_eq!(quotient, z_t::from(3));
/// assert_eq!(remainder, z_t::from(2));
/// ```
pub fn zdivmod(a: &mut z_t, b: &mut z_t, c: &z_t, d: &z_t) -> Result<()> {
    use num_traits::Signed;

    // Check for zero divisor (undefined form)
    if d.is_zero() {
        return Err(ZahlError::DivisionByZero);
    }

    // If dividend is zero, both quotient and remainder are zero
    if c.is_zero() {
        *a = z_t::zero();
        *b = z_t::zero();
        return Ok(());
    }

    // libzahl uses a specific division algorithm where:
    // - The quotient sign is determined by the sign of dividend * divisor
    // - The remainder is always the absolute value mod absolute value (always positive or zero)
    // This is based on the C implementation at lines 16 and 38 of zdivmod.c

    let sign_c = if c.is_negative() { -1 } else { 1 };
    let sign_d = if d.is_negative() { -1 } else { 1 };
    let sign = sign_c * sign_d;

    // Compute absolute values
    let abs_c = c.abs();
    let abs_d = d.abs();

    // Perform unsigned division
    let quotient = &abs_c / &abs_d;
    let remainder = &abs_c % &abs_d;

    // Set quotient with correct sign
    *a = if sign < 0 { -quotient } else { quotient };

    // Set remainder (always positive/zero in libzahl)
    *b = remainder;

    Ok(())
}
