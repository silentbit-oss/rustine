// Module: zunsetup
// Translation of zunsetup.c from libzahl C library
//
// In the C version, zunsetup cleans up global state including:
// - Freeing temporary variables
// - Freeing constants
// - Freeing memory pools
//
// In Rust, this is unnecessary because:
// - BigInt automatically frees its memory when dropped (RAII)
// - No global state needs cleanup
// - Memory pools are not needed (Rust allocator handles this)
//
// This function is kept as a no-op stub for API compatibility.

/// Clean up the libzahl library (no-op in Rust)
///
/// In the C version, this function frees global state, temporary variables,
/// and memory pools. In Rust, all of this is handled automatically:
/// - BigInt values are automatically freed when they go out of scope (RAII)
/// - The Drop trait ensures proper cleanup
/// - No global state needs manual cleanup
///
/// This function exists only for API compatibility and does nothing.
pub fn zunsetup() {
    // No-op: Rust handles cleanup automatically through RAII
    // BigInt's Drop trait handles memory deallocation
    // No global state needs manual cleanup
}
