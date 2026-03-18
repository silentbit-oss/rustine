// Test file for zrand_get_random_bits function

use num_bigint::BigInt;

// Import the function we're testing
use zahl::zrand::zrand_get_random_bits;
use zahl::zranddev;
use zahl::zbits::zbits;
use zahl::zcmp::zcmp;
use zahl::zcmpmag::zcmpmag;
use zahl::zlsh::zlsh;

#[test]
fn test_zero_bits() {
    let result = zrand_get_random_bits(0, zranddev::FAST_RANDOM);
    assert_eq!(result, BigInt::from(0), "Zero bits should produce zero");
    println!("PASS: test_zero_bits");
}

#[test]
fn test_small_bits_fast() {
    let bits = 8;
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be < 2^8 = 256
    let upper_bound = BigInt::from(256);
    assert!(zcmpmag(&result, &upper_bound) < 0,
            "Result should be less than 256, got: {}", result);
    println!("PASS: test_small_bits_fast");
}

#[test]
fn test_medium_bits_fast() {
    let bits = 16;
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be < 2^16 = 65536
    let upper_bound = BigInt::from(65536);
    assert!(zcmpmag(&result, &upper_bound) < 0,
            "Result should be less than 65536, got: {}", result);
    println!("PASS: test_medium_bits_fast");
}

#[test]
fn test_exact_char_boundary() {
    let bits = 32; // Exactly one 32-bit word
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be < 2^32
    let one = BigInt::from(1);
    let mut upper_bound = BigInt::from(0);
    zlsh(&mut upper_bound, &one, 32);
    assert!(zcmpmag(&result, &upper_bound) < 0,
            "Result should be less than 2^32, got: {}", result);
    println!("PASS: test_exact_char_boundary");
}

#[test]
fn test_large_bits_fast() {
    let bits = 128;
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be < 2^128
    // We verify by checking zbits(result) <= 128
    assert!(zbits(&result) <= bits,
            "Result should have at most {} bits, got: {}", bits, zbits(&result));
    println!("PASS: test_large_bits_fast");
}

#[test]
fn test_secure_random_device() {
    let bits = 64;
    let result = zrand_get_random_bits(bits, zranddev::SECURE_RANDOM);

    // Result should be < 2^64
    assert!(zbits(&result) <= bits,
            "Result should have at most {} bits, got: {}", bits, zbits(&result));
    println!("PASS: test_secure_random_device");
}

#[test]
fn test_non_aligned_bits() {
    let bits = 37; // Not aligned to 32-bit boundary
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be < 2^37
    // We verify by checking zbits(result) <= 37
    assert!(zbits(&result) <= bits,
            "Result should have at most {} bits, got: {}", bits, zbits(&result));
    println!("PASS: test_non_aligned_bits");
}

#[test]
fn test_multiple_calls_different_results() {
    let bits = 64;
    let iterations = 10;
    let mut same_count = 0;

    // Generate multiple random numbers and verify they're not all the same
    for _ in 0..iterations {
        let result1 = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);
        let result2 = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

        if zcmp(&result1, &result2) == 0 {
            same_count += 1;
        }
    }

    // It's astronomically unlikely that all 10 pairs are identical
    assert!(same_count < iterations,
            "Too many identical pairs: {}/{}", same_count, iterations);
    println!("PASS: test_multiple_calls_different_results");
}

#[test]
fn test_single_bit() {
    let bits = 1;
    let result = zrand_get_random_bits(bits, zranddev::FAST_RANDOM);

    // Result should be 0 or 1
    let upper_bound = BigInt::from(2);
    assert!(zcmpmag(&result, &upper_bound) < 0,
            "Result should be 0 or 1, got: {}", result);
    println!("PASS: test_single_bit");
}

// Integration test that runs all tests
#[test]
fn run_all_tests() {
    println!("Starting zrand_get_random_bits tests...\n");

    test_zero_bits();
    test_small_bits_fast();
    test_medium_bits_fast();
    test_exact_char_boundary();
    test_large_bits_fast();
    test_secure_random_device();
    test_non_aligned_bits();
    test_multiple_calls_different_results();
    test_single_bit();

    println!("\nAll tests passed!");
}
