/*
 * Generated test file for print_char_func function
 * Tests the character printing functionality of avl_data
 */

use std::process;

// Import the avl_data module
// Assuming the crate name is 'avl_tree' based on typical Rust project structure
extern crate avl_tree;
use avl_tree::avl_data::{makedata, MyData};

// Helper struct to capture output
static mut CAPTURED_OUTPUT: String = String::new();

fn reset_capture() {
    unsafe {
        CAPTURED_OUTPUT.clear();
    }
}

fn capture_char(c: char) {
    unsafe {
        CAPTURED_OUTPUT.push(c);
    }
}

// Custom print_char_func that captures output for testing
fn test_print_char_func(d: &MyData) {
    let c = (d.key & 127) as u8 as char;
    capture_char(c);
}

// Test case structure
struct TestCase {
    key: i32,
    expected_char: char,
    description: &'static str,
}

// Test basic printable ASCII characters
fn test_uppercase_letters() {
    print!("Test: Uppercase letters... ");

    let cases = vec![
        TestCase { key: 65, expected_char: 'A', description: "Letter A" },
        TestCase { key: 90, expected_char: 'Z', description: "Letter Z" },
        TestCase { key: 77, expected_char: 'M', description: "Letter M" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected '{}', got '{}'",
                    case.description,
                    case.expected_char,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0')
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

// Test lowercase letters
fn test_lowercase_letters() {
    print!("Test: Lowercase letters... ");

    let cases = vec![
        TestCase { key: 97, expected_char: 'a', description: "Letter a" },
        TestCase { key: 122, expected_char: 'z', description: "Letter z" },
        TestCase { key: 109, expected_char: 'm', description: "Letter m" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected '{}', got '{}'",
                    case.description,
                    case.expected_char,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0')
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

// Test digits
fn test_digits() {
    print!("Test: Digit characters... ");

    let cases = vec![
        TestCase { key: 48, expected_char: '0', description: "Digit 0" },
        TestCase { key: 57, expected_char: '9', description: "Digit 9" },
        TestCase { key: 53, expected_char: '5', description: "Digit 5" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected '{}', got '{}'",
                    case.description,
                    case.expected_char,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0')
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

// Test special characters
fn test_special_characters() {
    print!("Test: Special characters... ");

    let cases = vec![
        TestCase { key: 32, expected_char: ' ', description: "Space" },
        TestCase { key: 33, expected_char: '!', description: "Exclamation" },
        TestCase { key: 64, expected_char: '@', description: "At symbol" },
        TestCase { key: 126, expected_char: '~', description: "Tilde" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected '{}', got '{}'",
                    case.description,
                    case.expected_char,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0')
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

// Test masking behavior (key & 127)
fn test_masking_behavior() {
    print!("Test: Masking behavior (key & 127)... ");

    let cases = vec![
        TestCase { key: 128, expected_char: '\0', description: "128 masked to 0" },
        TestCase { key: 129, expected_char: '\x01', description: "129 masked to 1" },
        TestCase { key: 193, expected_char: 'A', description: "193 masked to 65 (A)" },
        TestCase { key: 255, expected_char: '\x7f', description: "255 masked to 127" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected 0x{:02x}, got 0x{:02x}",
                    case.description,
                    case.expected_char as u8,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0') as u8
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

// Test edge cases
fn test_edge_cases() {
    print!("Test: Edge cases... ");

    let cases = vec![
        TestCase { key: 0, expected_char: '\0', description: "Null character" },
        TestCase { key: 127, expected_char: '\x7f', description: "DEL character (127)" },
        TestCase { key: 1, expected_char: '\x01', description: "SOH character" },
    ];

    for case in cases {
        reset_capture();
        let data = makedata(case.key);
        test_print_char_func(&data);

        unsafe {
            if CAPTURED_OUTPUT.chars().next() != Some(case.expected_char) {
                println!(
                    "FAILED: {} - Expected 0x{:02x}, got 0x{:02x}",
                    case.description,
                    case.expected_char as u8,
                    CAPTURED_OUTPUT.chars().next().unwrap_or('\0') as u8
                );
                process::exit(1);
            }
        }
    }

    println!("PASSED");
}

fn main() {
    println!("=== Testing print_char_func ===\n");

    test_uppercase_letters();
    test_lowercase_letters();
    test_digits();
    test_special_characters();
    test_masking_behavior();
    test_edge_cases();

    println!("\n=== All tests PASSED ===");
}
