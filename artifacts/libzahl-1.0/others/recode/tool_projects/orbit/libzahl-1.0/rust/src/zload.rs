// Module: zload - Binary deserialization of BigInt

use crate::z_t;
use num_bigint::{BigInt, Sign};

/// Deserialize a BigInt from a byte buffer.
///
/// # Parameters
/// - `a`: Mutable reference to the BigInt to populate
/// - `buffer`: Byte slice containing serialized data
///
/// # Returns
/// The number of bytes read from the buffer
///
/// # Format
/// The deserialization format matches zsave:
/// - 4 bytes: sign (as i32: 0 = zero, 1 = positive, -1 = negative)
/// - 8 bytes: data length in bytes (as u64)
/// - N bytes: little-endian byte representation of the magnitude
pub fn zload(a: &mut z_t, buffer: &[u8]) -> usize {
    let mut offset = 0;

    // Read sign (4 bytes, little-endian)
    let sign_size = std::mem::size_of::<i32>();
    let sign_bytes: [u8; 4] = buffer[offset..offset + sign_size].try_into().unwrap();
    let sign_value = i32::from_le_bytes(sign_bytes);
    offset += sign_size;

    // Read data length (8 bytes, little-endian)
    let length_size = std::mem::size_of::<u64>();
    let length_bytes: [u8; 8] = buffer[offset..offset + length_size].try_into().unwrap();
    let data_len = u64::from_le_bytes(length_bytes) as usize;
    offset += length_size;

    // Convert sign value to Sign enum
    let sign = match sign_value {
        -1 => Sign::Minus,
        0 => Sign::NoSign,
        1 => Sign::Plus,
        _ => Sign::NoSign, // Default to zero for invalid values
    };

    // Read magnitude bytes
    if sign == Sign::NoSign || data_len == 0 {
        // Zero value
        *a = BigInt::from(0);
    } else {
        let magnitude_bytes = &buffer[offset..offset + data_len];
        *a = BigInt::from_bytes_le(sign, magnitude_bytes);
        offset += data_len;
    }

    offset
}
