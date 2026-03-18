// Symbol version v2
// Translation from C tests/06_symbol_versions/v2.c to Rust

// In C, this uses assembly directives to create versioned symbols:
// __asm__(".symver xyz_old,xyz@VER_1");
// __asm__(".symver xyz_new,xyz@@VER_2");
//
// Rust doesn't have direct equivalent for symbol versioning in the same way,
// but we can create the functions with different names for testing purposes

#[no_mangle]
pub extern "C" fn xyz_old() -> i32 {
    3
}

#[no_mangle]
pub extern "C" fn xyz_new() -> i32 {
    4
}

// In a real scenario with symbol versioning, you would use:
// - Custom build scripts to create version scripts
// - Link with specific linker flags
// - Use global_asm! for inline assembly (nightly Rust)

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_xyz_old_returns_3() {
        assert_eq!(xyz_old(), 3);
    }

    #[test]
    fn test_xyz_new_returns_4() {
        assert_eq!(xyz_new(), 4);
    }
}
