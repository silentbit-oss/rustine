// Module: zerror
// Error handling types and functions

use std::fmt;
use std::io;
use thiserror::Error;

/// Error types for libzahl operations
/// Matches the C enum zerror structure
#[derive(Debug, Error, Clone, Copy, PartialEq, Eq)]
pub enum zerror {
    #[error("errno set")]
    ZERROR_ERRNO_SET = 0,
}

/// Extended error information for Rust
/// This provides more detailed error types while maintaining C compatibility
#[derive(Debug, Error, Clone)]
pub enum ZahlError {
    #[error("Division by zero")]
    DivisionByZero,

    #[error("Invalid domain")]
    InvalidDomain,

    #[error("Memory allocation failed")]
    AllocationFailed,

    #[error("Invalid exponent")]
    InvalidExponent,

    #[error("I/O error: {0}")]
    Io(String),

    #[error("Parse error: {0}")]
    ParseError(String),

    #[error("Invalid radix: {0}")]
    InvalidRadix(u32),

    #[error("Overflow")]
    Overflow,

    #[error("Underflow")]
    Underflow,
}

impl From<io::Error> for ZahlError {
    fn from(err: io::Error) -> Self {
        ZahlError::Io(err.to_string())
    }
}

impl From<std::num::ParseIntError> for ZahlError {
    fn from(err: std::num::ParseIntError) -> Self {
        ZahlError::ParseError(err.to_string())
    }
}

/// Result type alias for libzahl operations
pub type Result<T> = std::result::Result<T, ZahlError>;

/// Thread-local error state for C-compatible error handling
use std::cell::RefCell;
thread_local! {
    static LAST_ERROR: RefCell<Option<ZahlError>> = RefCell::new(None);
}

/// Set the last error for the current thread
pub fn set_error(error: ZahlError) {
    LAST_ERROR.with(|e| {
        *e.borrow_mut() = Some(error);
    });
}

/// Clear the last error for the current thread
pub fn clear_error() {
    LAST_ERROR.with(|e| {
        *e.borrow_mut() = None;
    });
}

/// Return the current error code and description
///
/// This function returns the last error that occurred and optionally
/// provides a description string. Returns (error_code, description).
/// Returns 0 if no error occurred.
pub fn zerror() -> (i32, Option<String>) {
    LAST_ERROR.with(|e| {
        let error_ref = e.borrow();
        match &*error_ref {
            None => (0, None),
            Some(err) => {
                let code = match err {
                    ZahlError::DivisionByZero => 1,
                    ZahlError::InvalidDomain => 2,
                    ZahlError::AllocationFailed => 3,
                    ZahlError::InvalidExponent => 4,
                    ZahlError::Io(_) => 5,
                    ZahlError::ParseError(_) => 6,
                    ZahlError::InvalidRadix(_) => 7,
                    ZahlError::Overflow => 8,
                    ZahlError::Underflow => 9,
                };
                (code, Some(err.to_string()))
            }
        }
    })
}
