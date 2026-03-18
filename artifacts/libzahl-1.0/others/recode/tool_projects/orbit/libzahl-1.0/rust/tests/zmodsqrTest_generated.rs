// Test file for zmodsqr function - Generated test
use zahl::zmodsqr::zmodsqr;
use num_bigint::BigInt;

#[test]
fn test_zmodsqr_basic() {
    println!("Test: zmodsqr_basic - (17 * 17) % 10 = 9");
    let b = BigInt::from(17);
    let c = BigInt::from(10);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // (17 * 17) % 10 = 289 % 10 = 9
    assert_eq!(a, BigInt::from(9));
    println!("PASS");
}

#[test]
fn test_zmodsqr_zero() {
    println!("Test: zmodsqr_zero - (0 * 0) % 10 = 0");
    let b = BigInt::from(0);
    let c = BigInt::from(10);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    assert_eq!(a, BigInt::from(0));
    println!("PASS");
}

#[test]
fn test_zmodsqr_negative() {
    println!("Test: zmodsqr_negative - (-7 * -7) % 10 = 9");
    let b = BigInt::from(-7);
    let c = BigInt::from(10);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // (-7 * -7) % 10 = 49 % 10 = 9
    assert_eq!(a, BigInt::from(9));
    println!("PASS");
}

#[test]
#[should_panic(expected = "DivisionByZero")]
fn test_zmodsqr_zero_modulus() {
    println!("Test: zmodsqr_zero_modulus - Should trigger error for modulus = 0");
    let b = BigInt::from(5);
    let c = BigInt::from(0);
    let mut a = BigInt::from(0);

    // This should return an error
    let result = zmodsqr(&mut a, &b, &c);
    assert!(result.is_err());

    // Panic to satisfy should_panic
    panic!("DivisionByZero");
}

#[test]
fn test_zmodsqr_zero_modulus_error() {
    println!("Test: zmodsqr_zero_modulus_error - Verify error for modulus = 0");
    let b = BigInt::from(5);
    let c = BigInt::from(0);
    let mut a = BigInt::from(0);

    let result = zmodsqr(&mut a, &b, &c);
    assert!(result.is_err());
    println!("PASS: Error correctly triggered for zero modulus");
}

#[test]
fn test_zmodsqr_large() {
    println!("Test: zmodsqr_large - (12345 * 12345) % 1000 = 25");
    let b = BigInt::from(12345);
    let c = BigInt::from(1000);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // (12345 * 12345) % 1000 = 152399025 % 1000 = 25
    assert_eq!(a, BigInt::from(25));
    println!("PASS");
}

#[test]
fn test_zmodsqr_one() {
    println!("Test: zmodsqr_one - (1 * 1) % 10 = 1");
    let b = BigInt::from(1);
    let c = BigInt::from(10);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    assert_eq!(a, BigInt::from(1));
    println!("PASS");
}

#[test]
fn test_zmodsqr_modulus_larger_than_square() {
    println!("Test: zmodsqr_modulus_larger - (5 * 5) % 100 = 25");
    let b = BigInt::from(5);
    let c = BigInt::from(100);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // (5 * 5) % 100 = 25
    assert_eq!(a, BigInt::from(25));
    println!("PASS");
}

#[test]
fn test_zmodsqr_aliasing() {
    println!("Test: zmodsqr_aliasing - Test when a and c have the same value initially");
    let b = BigInt::from(7);
    let c = BigInt::from(10);
    let mut a = c.clone();  // a starts with same value as c

    zmodsqr(&mut a, &b, &c).unwrap();

    // (7 * 7) % 10 = 49 % 10 = 9
    assert_eq!(a, BigInt::from(9));
    println!("PASS");
}

#[test]
fn test_zmodsqr_very_large() {
    println!("Test: zmodsqr_very_large - Test with very large numbers");
    // b = 123456789123456789
    let b: BigInt = "123456789123456789".parse().unwrap();
    // c = 1000000007 (large prime)
    let c: BigInt = "1000000007".parse().unwrap();
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // (123456789123456789^2) % 1000000007 = 165980939
    let expected: BigInt = "165980939".parse().unwrap();
    assert_eq!(a, expected);
    println!("PASS");
}

#[test]
fn test_zmodsqr_negative_modulus() {
    println!("Test: zmodsqr_negative_modulus - (7 * 7) % -10");
    let b = BigInt::from(7);
    let c = BigInt::from(-10);
    let mut a = BigInt::from(0);

    zmodsqr(&mut a, &b, &c).unwrap();

    // Both C and Rust implementations return 9 (positive result)
    assert_eq!(a, BigInt::from(9));
    println!("PASS");
}
