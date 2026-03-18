// Test for libzahl_realloc function
// Rust translation of allocatorTest_generated.c

use zahl::{z_t, allocator::libzahl_realloc};
use num_bigint::BigInt;
use num_traits::Zero;

fn zsignum(a: &z_t) -> i32 {
    if a.is_zero() {
        0
    } else if *a > BigInt::zero() {
        1
    } else {
        -1
    }
}

fn test_libzahl_realloc() -> Result<(), String> {
    println!("Test 1: Reallocating with small size (power of 2)");
    let mut a = BigInt::from(42);
    println!("  Original value: {}", a);

    // Request reallocation to 8 elements (in Rust, this is a no-op)
    libzahl_realloc(&mut a, 8);
    println!("  After realloc(8)");

    // Value should be preserved (the primary functional behavior)
    assert_eq!(zsignum(&a), 1, "Signum should be 1");
    assert_eq!(a, BigInt::from(42), "Value should be 42");
    println!("  PASS: Value preserved");

    println!("\nTest 2: Reallocating with non-power-of-2 size");
    let mut b = BigInt::from(1234567890u64);
    println!("  Original value: {}", b);

    // Request reallocation to 15 elements
    libzahl_realloc(&mut b, 15);
    println!("  After realloc(15)");

    // Value should be preserved
    assert_eq!(zsignum(&b), 1, "Signum should be 1");
    assert_eq!(b, BigInt::from(1234567890u64), "Value should be 1234567890");
    println!("  PASS: Value preserved");

    println!("\nTest 3: Reallocating with larger size");
    let mut c = BigInt::from(999999999u64);
    println!("  Original value: {}", c);

    // Request reallocation to 64 elements
    libzahl_realloc(&mut c, 64);
    println!("  After realloc(64)");

    // Value should be preserved
    assert_eq!(zsignum(&c), 1, "Signum should be 1");
    assert_eq!(c, BigInt::from(999999999u64), "Value should be 999999999");
    println!("  PASS: Value preserved");

    println!("\nTest 4: Reallocating with size 1 (edge case)");
    let mut a = BigInt::from(7);
    libzahl_realloc(&mut a, 1);
    println!("  After realloc(1)");
    assert_eq!(a, BigInt::from(7), "Value should be 7");
    println!("  PASS: Value preserved with size 1");

    println!("\nTest 5: Reallocating with size 2 (already power of 2)");
    let mut b = BigInt::from(100);
    libzahl_realloc(&mut b, 2);
    println!("  After realloc(2)");
    assert_eq!(b, BigInt::from(100), "Value should be 100");
    println!("  PASS: Value preserved");

    println!("\nTest 6: Multiple reallocations");
    let mut c = BigInt::from(12345);
    libzahl_realloc(&mut c, 4);
    println!("  After realloc(4)");
    assert_eq!(c, BigInt::from(12345), "Value should be 12345 after realloc(4)");

    libzahl_realloc(&mut c, 32);
    println!("  After realloc(32)");
    assert_eq!(c, BigInt::from(12345), "Value should be 12345 after realloc(32)");

    libzahl_realloc(&mut c, 8);
    println!("  After realloc(8)");
    assert_eq!(c, BigInt::from(12345), "Value should be 12345 after realloc(8)");
    println!("  PASS: Multiple reallocations succeeded");

    println!("\nTest 7: Large allocation");
    let mut a = BigInt::from(0);
    libzahl_realloc(&mut a, 1024);
    println!("  After realloc(1024)");
    assert_eq!(a, BigInt::from(0), "Value should be 0");
    println!("  PASS: Large allocation succeeded");

    println!("\n========================================");
    println!("All libzahl_realloc tests PASSED!");
    println!("========================================");
    Ok(())
}

fn main() {
    match test_libzahl_realloc() {
        Ok(()) => {
            println!("\nTEST RESULT: SUCCESS");
            std::process::exit(0);
        }
        Err(e) => {
            eprintln!("\nTEST RESULT: FAILURE");
            eprintln!("Error: {}", e);
            std::process::exit(1);
        }
    }
}
