// Module: zsetup
// Translation of zsetup.c from libzahl C library
//
// In the C version, zsetup initializes global state including:
// - Setting up jump buffer for error handling
// - Initializing temporary variables
// - Initializing constants
// - Initializing memory pools
//
// In Rust, this is unnecessary because:
// - Rust uses Result types instead of setjmp/longjmp for error handling
// - BigInt manages its own memory through RAII (no manual allocation needed)
// - No global state needs initialization
// - Memory pools are not needed (Rust allocator handles this)
//
// This function is kept as a no-op stub for API compatibility.

/// Initialize the libzahl library (no-op in Rust)
///
/// In the C version, this function sets up global state, error handling via setjmp/longjmp,
/// and memory pools. In Rust, all of this is handled automatically:
/// - Error handling uses Result types
/// - Memory management uses RAII via BigInt's Drop implementation
/// - No global state needs initialization
///
/// This function exists only for API compatibility and does nothing.
pub fn zsetup() {
    // No-op: Rust handles initialization automatically through RAII
    // BigInt manages its own memory
    // Error handling uses Result types instead of setjmp/longjmp
}
