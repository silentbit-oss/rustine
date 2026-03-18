// Generated test file for zerror function
// Tests the zerror module for functional equivalence with C implementation

use zahl::{z_t, ZahlError};
use zahl::{set_error, clear_error};
use zahl::zerror::zerror;

/// Test 1: Check that zerror returns (0, None) when no error
#[test]
fn test_zerror_no_error() {
    // Clear any previous errors
    clear_error();

    // Check zerror with no error
    let (err_code, desc) = zerror();
    assert_eq!(err_code, 0, "Expected error code 0 when no error");
    assert_eq!(desc, None, "Expected None description when no error");

    println!("Test 1 passed: No error returns (0, None)");
}

/// Test 2: Check that zerror returns error info after setting division by zero
#[test]
fn test_zerror_division_by_zero() {
    clear_error();

    // Set a division by zero error
    set_error(ZahlError::DivisionByZero);

    // The error should be set
    let (err_code, desc) = zerror();
    assert_ne!(err_code, 0, "Expected non-zero error code after error");
    assert!(desc.is_some(), "Expected Some description after error");

    let desc_str = desc.unwrap();
    assert!(desc_str.len() > 0, "Expected non-empty error description");
    assert!(desc_str.contains("Division by zero"), "Expected division by zero message");

    println!("Test 2 passed: Error returns code {} with description: {}", err_code, desc_str);
}

/// Test 3: Check that zerror works for invalid domain errors
#[test]
fn test_zerror_invalid_domain() {
    clear_error();

    // Set an invalid domain error
    set_error(ZahlError::InvalidDomain);

    // Check the error
    let (err_code, desc) = zerror();
    assert_ne!(err_code, 0, "Expected non-zero error code after error");
    assert!(desc.is_some(), "Expected Some description after error");

    let desc_str = desc.unwrap();
    assert!(desc_str.contains("Invalid domain"), "Expected invalid domain message");

    println!("Test 3 passed: Invalid domain error returns code {} with description: {}",
             err_code, desc_str);
}

/// Test 4: Check that clearing errors works
#[test]
fn test_zerror_clear() {
    // Set an error first
    set_error(ZahlError::DivisionByZero);

    // Verify error is set
    let (err_code, desc) = zerror();
    assert_ne!(err_code, 0, "Expected non-zero error code");
    assert!(desc.is_some(), "Expected Some description");

    // Clear the error
    clear_error();

    // Verify error is cleared
    let (err_code, desc) = zerror();
    assert_eq!(err_code, 0, "Expected error code 0 after clear");
    assert_eq!(desc, None, "Expected None description after clear");

    println!("Test 4 passed: Error clearing works correctly");
}

/// Test 5: Check that errors can be set and retrieved manually
#[test]
fn test_zerror_manual_set() {
    clear_error();

    // Manually set different error types and verify they're retrievable
    let error_types = vec![
        (ZahlError::DivisionByZero, 1, "Division by zero"),
        (ZahlError::InvalidDomain, 2, "Invalid domain"),
        (ZahlError::AllocationFailed, 3, "Memory allocation failed"),
        (ZahlError::InvalidExponent, 4, "Invalid exponent"),
        (ZahlError::Overflow, 8, "Overflow"),
        (ZahlError::Underflow, 9, "Underflow"),
    ];

    for (error, expected_code, expected_msg_part) in error_types {
        clear_error();
        set_error(error.clone());

        let (err_code, desc) = zerror();
        assert_eq!(err_code, expected_code, "Expected error code {} for {:?}", expected_code, error);
        assert!(desc.is_some(), "Expected Some description for {:?}", error);

        let desc_str = desc.unwrap();
        assert!(desc_str.contains(expected_msg_part),
                "Expected description to contain '{}', got '{}'", expected_msg_part, desc_str);

        println!("Error type {:?} -> code {}, desc: {}",
                 error, err_code, desc_str);
    }

    println!("Test 5 passed: Manual error setting works correctly");
}

/// Test 6: Check that error codes are consistent with expected values
#[test]
fn test_zerror_codes() {
    let test_cases = vec![
        (ZahlError::DivisionByZero, 1),
        (ZahlError::InvalidDomain, 2),
        (ZahlError::AllocationFailed, 3),
        (ZahlError::InvalidExponent, 4),
        (ZahlError::Io("test".to_string()), 5),
        (ZahlError::ParseError("test".to_string()), 6),
        (ZahlError::InvalidRadix(10), 7),
        (ZahlError::Overflow, 8),
        (ZahlError::Underflow, 9),
    ];

    for (error, expected_code) in test_cases {
        clear_error();
        set_error(error.clone());

        let (err_code, _) = zerror();
        assert_eq!(err_code, expected_code, "Error {:?} should map to code {}", error, expected_code);
    }

    println!("Test 6 passed: All error codes are consistent");
}

/// Run all tests together (for manual execution)
#[cfg(test)]
mod integration_tests {
    use super::*;

    #[test]
    fn run_all_zerror_tests() {
        println!("Running all zerror tests...");

        test_zerror_no_error();
        test_zerror_division_by_zero();
        test_zerror_invalid_domain();
        test_zerror_clear();
        test_zerror_manual_set();
        test_zerror_codes();

        println!("All zerror tests passed!");
    }
}
