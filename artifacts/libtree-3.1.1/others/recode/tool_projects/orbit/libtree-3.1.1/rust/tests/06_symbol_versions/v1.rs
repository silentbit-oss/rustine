// Symbol version v1
// Translation from C tests/06_symbol_versions/v1.c to Rust

// In C: int xyz() { return 3; }
// This is a simple function that returns 3

#[no_mangle]
pub extern "C" fn xyz() -> i32 {
    3
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_xyz_returns_3() {
        assert_eq!(xyz(), 3);
    }
}
