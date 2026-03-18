// Module: zperror
// Error printing function

use crate::zerror::zerror;

/// Print error message to stderr (similar to perror in C)
///
/// Prints the provided prefix followed by the error description
/// to standard error. Similar to the C perror function.
pub fn zperror(prefix: &str) {
    let (code, desc) = zerror();

    if code != 0 {
        if let Some(error_desc) = desc {
            eprintln!("{}: {}", prefix, error_desc);
        } else {
            eprintln!("{}: Unknown error (code: {})", prefix, code);
        }
    } else {
        eprintln!("{}: No error", prefix);
    }
}
