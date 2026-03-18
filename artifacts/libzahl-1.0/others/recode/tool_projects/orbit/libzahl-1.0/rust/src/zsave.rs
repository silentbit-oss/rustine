// Module: zsave - Binary serialization of BigInt

use crate::z_t;
use num_bigint::Sign;

/// Serialize a BigInt to a byte buffer.
///
/// # Parameters
/// - `a`: The BigInt to serialize
/// - `buffer`: Optional mutable slice to write bytes to. If None, only calculates size.
///
/// # Returns
/// The number of bytes written (or required if buffer is None)
///
/// # Format
/// The serialization format is:
/// - 4 bytes: sign (as i32: 0 = zero, 1 = positive, -1 = negative)
/// - 8 bytes: data length in bytes (as u64)
/// - N bytes: little-endian byte representation of the magnitude
pub fn zsave(a: &z_t, buffer: Option<&mut [u8]>) -> usize {
    // Get the sign and magnitude bytes
    let (sign, magnitude_bytes) = a.to_bytes_le();

    // Convert Sign enum to i32
    let sign_value: i32 = match sign {
        Sign::Minus => -1,
        Sign::NoSign => 0,
        Sign::Plus => 1,
    };

    // Calculate total size needed
    let sign_size = std::mem::size_of::<i32>();       // 4 bytes
    let length_size = std::mem::size_of::<u64>();     // 8 bytes
    let data_size = magnitude_bytes.len();
    let total_size = sign_size + length_size + data_size;

    // If buffer is provided, write to it
    if let Some(buf) = buffer {
        let mut offset = 0;

        // Write sign (4 bytes, little-endian)
        buf[offset..offset + sign_size].copy_from_slice(&sign_value.to_le_bytes());
        offset += sign_size;

        // Write data length (8 bytes, little-endian)
        let data_len = data_size as u64;
        buf[offset..offset + length_size].copy_from_slice(&data_len.to_le_bytes());
        offset += length_size;

        // Write magnitude bytes
        if data_size > 0 {
            buf[offset..offset + data_size].copy_from_slice(&magnitude_bytes);
        }
    }

    total_size
}
