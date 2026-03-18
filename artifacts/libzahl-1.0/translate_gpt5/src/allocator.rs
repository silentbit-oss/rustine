// Module: allocator
// Translation of allocator.c from libzahl C library
//
// In the C version, libzahl_realloc reallocates a z_t's internal buffer
// to ensure it has enough space for a given number of characters.
// It uses a memory pool system for efficiency.
//
// In Rust, this is unnecessary because:
// - BigInt automatically manages its internal buffer size
// - Memory grows automatically as needed
// - Rust's allocator handles reallocation efficiently
//
// This function is kept as a no-op stub for API compatibility.

use crate::z_t;

/// Reallocate a big integer's internal buffer (no-op in Rust)
///
/// In the C version, this function ensures a z_t has enough allocated space
/// for a specified number of characters, using a custom memory pool system.
/// In Rust, this is handled automatically:
/// - BigInt manages its own internal buffer size
/// - Memory automatically grows as needed for operations
/// - Rust's allocator handles all reallocation efficiently
///
/// This function accepts parameters to maintain API compatibility but does nothing.
/// BigInt will automatically allocate the necessary memory during operations.
///
/// # Arguments
/// * `_a` - The big integer to reallocate (unused, kept for API compatibility)
/// * `_need` - The number of characters needed (unused, kept for API compatibility)
pub fn libzahl_realloc(_a: &mut z_t, _need: usize) {
    // No-op: Rust handles memory allocation automatically
    // BigInt grows its internal buffer as needed
    // No manual memory management required
}
