// Module: zfree
// Translation of zfree.c from libzahl C library
//
// In the C version, zfree returns a z_t's memory to a memory pool
// for later reuse, implementing a custom memory management strategy.
//
// In Rust, this is unnecessary because:
// - BigInt automatically frees its memory when dropped (RAII)
// - Rust's allocator efficiently manages memory without custom pools
// - Memory is freed automatically when values go out of scope
//
// This function is kept as a no-op stub for API compatibility.

use crate::z_t;

/// Free a big integer's memory (no-op in Rust)
///
/// In the C version, this function returns the integer's memory to a memory pool
/// for later reuse. In Rust, this is handled automatically:
/// - BigInt manages its own memory through RAII
/// - Memory is automatically freed when the value is dropped
/// - Rust's allocator efficiently manages memory without custom pools
///
/// This function accepts a reference to maintain API compatibility but does nothing.
/// The actual memory will be freed when the value goes out of scope.
///
/// # Arguments
/// * `_a` - The big integer to free (unused, kept for API compatibility)
pub fn zfree(_a: &z_t) {
    // No-op: Rust handles memory deallocation automatically
    // BigInt's Drop trait frees memory when the value goes out of scope
    // No custom memory pools needed
}
