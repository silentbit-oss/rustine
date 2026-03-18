// Module: zsets
// Parse decimal string to BigInt

use crate::{z_t, Result, ZahlError};
use std::str::FromStr;

/// Parse a decimal string and set the BigInt to that value
///
/// # Arguments
/// * `s` - The decimal string to parse (may have leading '+' or '-' sign)
///
/// # Returns
/// * `Ok(BigInt)` - Successfully parsed BigInt
/// * `Err(ZahlError::ParseError)` - Invalid string format
///
/// # Errors
/// Returns `ZahlError::ParseError` if:
/// - The string is empty after removing the optional sign
/// - The string contains non-digit characters
/// - The string format is invalid
///
/// # Example
/// ```
/// use libzahl::zsets::zsets;
/// use num_bigint::BigInt;
///
/// let result = zsets("12345");
/// assert!(result.is_ok());
/// assert_eq!(result.unwrap(), BigInt::from(12345));
///
/// let result = zsets("-9876");
/// assert!(result.is_ok());
/// assert_eq!(result.unwrap(), BigInt::from(-9876));
///
/// let result = zsets("+100");
/// assert!(result.is_ok());
/// assert_eq!(result.unwrap(), BigInt::from(100));
///
/// let result = zsets("");
/// assert!(result.is_err());
///
/// let result = zsets("abc");
/// assert!(result.is_err());
///
/// let result = zsets("12.34");
/// assert!(result.is_err());
/// ```
pub fn zsets(s: &str) -> Result<z_t> {
    // Handle empty string
    if s.is_empty() {
        return Err(ZahlError::ParseError("Empty string".to_string()));
    }

    // Check if starts with sign
    let has_sign = s.starts_with('-') || s.starts_with('+');
    let digit_part = if has_sign { &s[1..] } else { s };

    // Empty string after sign
    if digit_part.is_empty() {
        return Err(ZahlError::ParseError("No digits after sign".to_string()));
    }

    // Check all characters are digits
    for ch in digit_part.chars() {
        if !ch.is_ascii_digit() {
            return Err(ZahlError::ParseError(
                format!("Invalid character '{}' in numeric string", ch)
            ));
        }
    }

    // Parse using BigInt's from_str
    // This handles the actual conversion including the sign
    z_t::from_str(s).map_err(|e| ZahlError::ParseError(e.to_string()))
}
