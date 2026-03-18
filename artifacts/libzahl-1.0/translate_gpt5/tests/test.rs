// Test translation from C to Rust
// Original file: test.c

use zahl::{z_t, Result};
use zahl::zsetu::zsetu;
use zahl::zswap::zswap;
use zahl::zneg::zneg;
use zahl::zcmp::zcmp;
use zahl::zbset::zbset;
use zahl::zsave::zsave;
use zahl::zload::zload;
use zahl::zbits::zbits;
use zahl::zlsb::zlsb;
use zahl::zabs::zabs;
use zahl::zadd::zadd;
use zahl::zseti::zseti;
use zahl::zadd::zadd_unsigned;
use zahl::zsub::zsub_unsigned;
use zahl::zand::zand;
use zahl::zcmpi::zcmpi;
use zahl::zcmpmag::zcmpmag;
use zahl::zcmpu::zcmpu;
use zahl::zdiv::zdiv;
use zahl::zdivmod::zdivmod;
use zahl::zgcd::zgcd;
use zahl::zlsh::zlsh;
use zahl::zmod::zmod;
use zahl::zmodmul::zmodmul;
use zahl::zmodpow::zmodpow;
use zahl::zmodpowu::zmodpowu;
use zahl::zmul::zmul;
use zahl::znot::znot;
use zahl::zor::zor;
use zahl::zpow::zpow;
use zahl::zpowu::zpowu;
use zahl::zrsh::zrsh;
use zahl::zset::zset;
use zahl::zsets::zsets;
use zahl::zsplit::zsplit;
use zahl::zsqr::zsqr;
use zahl::zstr::zstr;
use zahl::zstr_length::zstr_length;
use zahl::zsub::zsub;
use zahl::ztrunc::ztrunc;
use zahl::zxor::zxor;
use zahl::zbtest::zbtest;
use zahl::zmodsqr::zmodsqr;
use zahl::zptest::zptest;
use zahl::zptest::zprimality;
use zahl::zrand::zrand;
use zahl::zrand::zranddev;
use zahl::zrand::zranddist;
use num_traits::{Zero, One};
use num_bigint::BigInt;

// Helper functions that were inline in C header
fn zeven(a: &z_t) -> i32 {
    // Even if zero or even non-zero
    if a.is_zero() || (a & BigInt::one()).is_zero() { 1 } else { 0 }
}

fn zodd(a: &z_t) -> i32 {
    // Odd if non-zero and bit 0 is set
    if !a.is_zero() && !(a & BigInt::one()).is_zero() { 1 } else { 0 }
}

fn zzero(a: &z_t) -> i32 {
    if a.is_zero() { 1 } else { 0 }
}

fn zsignum(a: &z_t) -> i32 {
    // Return -1, 0, or 1
    if a.is_zero() {
        0
    } else if *a > BigInt::zero() {
        1
    } else {
        -1
    }
}

#[test]
fn test_1() {
    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);
    let mut buf = vec![0u8; 2000];

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Test basic properties
    assert_eq!(zeven(&_0), 1);
    assert_eq!(zodd(&_0), 0);
    assert_eq!(zzero(&_0), 1);
    assert_eq!(zsignum(&_0), 0);
    assert_eq!(zeven(&_1), 0);
    assert_eq!(zodd(&_1), 1);
    assert_eq!(zzero(&_1), 0);
    assert_eq!(zsignum(&_1), 1);
    assert_eq!(zeven(&_2), 1);
    assert_eq!(zodd(&_2), 0);
    assert_eq!(zzero(&_2), 0);
    assert_eq!(zsignum(&_2), 1);

    // Test swap operations
    zswap(&mut _1, &mut _2);
    assert_eq!(zeven(&_2), 0);
    assert_eq!(zodd(&_2), 1);
    assert_eq!(zzero(&_2), 0);
    assert_eq!(zsignum(&_2), 1);
    assert_eq!(zeven(&_1), 1);
    assert_eq!(zodd(&_1), 0);
    assert_eq!(zzero(&_1), 0);
    assert_eq!(zsignum(&_1), 1);
    zswap(&mut _2, &mut _1);
    assert_eq!(zeven(&_1), 0);
    assert_eq!(zodd(&_1), 1);
    assert_eq!(zzero(&_1), 0);
    assert_eq!(zsignum(&_1), 1);
    assert_eq!(zeven(&_2), 1);
    assert_eq!(zodd(&_2), 0);
    assert_eq!(zzero(&_2), 0);
    assert_eq!(zsignum(&_2), 1);

    // Test negation
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert_eq!(zsignum(&_2), -1);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert_eq!(zsignum(&_2), 1);

    // Test comparison operations
    assert_eq!(zcmp(&_0, &_0), 0);
    assert_eq!(zcmp(&_1, &_1), 0);
    assert!(zcmp(&_0, &_1) < 0);
    assert!(zcmp(&_1, &_0) > 0);
    assert!(zcmp(&_1, &_2) < 0);
    assert!(zcmp(&_2, &_1) > 0);
    assert!(zcmp(&_0, &_2) < 0);
    assert!(zcmp(&_2, &_0) > 0);

    // Test bit set operations
    zbset(&mut a, &_0, 0, 1);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zbset(&mut a, &temp_a, 1, 1);
    assert_eq!(zcmp(&a, &_3), 0);
    let temp_a = a.clone();
    zbset(&mut a, &temp_a, 0, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_a = a.clone();
    zbset(&mut a, &temp_a, 0, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_a = a.clone();
    zbset(&mut a, &temp_a, 0, -1);
    assert_eq!(zcmp(&a, &_3), 0);
    let temp_a = a.clone();
    zbset(&mut a, &temp_a, 0, -1);
    assert_eq!(zcmp(&a, &_2), 0);

    // Test save/load operations
    zsetu(&mut a, 1000);
    zsetu(&mut b, 0);
    assert!(zcmp(&a, &b) != 0);
    let n = zsave(&a, Some(&mut buf));
    assert!(n > 0);
    let loaded = zload(&mut b, &buf);
    assert_eq!(loaded, n);
    assert_eq!(zcmp(&a, &b), 0);

    // Test bit operations
    assert_eq!(zbits(&_0), 1);
    assert_eq!(zbits(&_1), 1);
    assert_eq!(zbits(&_2), 2);
    assert_eq!(zbits(&_3), 2);

    assert_eq!(zlsb(&_0), usize::MAX);
    assert_eq!(zlsb(&_1), 0);
    assert_eq!(zlsb(&_2), 1);
    assert_eq!(zlsb(&_3), 0);
}

#[test]
fn test_2() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Test basic addition operations
    zadd(&mut a, &_0, &_1);
    assert_eq!(zsignum(&a), 1);
    assert_eq!(zcmp(&a, &_1), 0);
    assert_eq!(zcmpi(&a, 1), 0);
    assert_eq!(zcmpu(&a, 1), 0);
    let temp_a = a.clone();
    zneg(&mut a, &temp_a);
    assert_eq!(zsignum(&a), -1);
    assert!(zcmp(&a, &_1) < 0);
    assert!(zcmpi(&a, 1) < 0);
    assert!(zcmpu(&a, 1) < 0);
    zadd(&mut a, &_2, &_0);
    assert_eq!(zsignum(&a), 1);
    assert_eq!(zcmp(&a, &_2), 0);
    assert_eq!(zcmpi(&a, 2), 0);
    assert_eq!(zcmpu(&a, 2), 0);
    let temp_a = a.clone();
    zneg(&mut a, &temp_a);
    assert_eq!(zsignum(&a), -1);
    assert!(zcmp(&a, &_2) < 0);
    assert!(zcmpi(&a, 2) < 0);
    assert!(zcmpu(&a, 2) < 0);

    // Test addition with same values
    assert_eq!(zsignum(&_1), 1);
    zadd(&mut a, &_1, &_1);
    assert_eq!(zsignum(&a), 1);
    assert_eq!(zcmp(&a, &_2), 0);
    assert_eq!(zcmpi(&a, 2), 0);
    assert_eq!(zcmpu(&a, 2), 0);
    zset(&mut b, &_1);
    zadd(&mut a, &b, &_1);
    assert_eq!(zsignum(&a), 1);
    assert_eq!(zcmp(&a, &_2), 0);
    assert_eq!(zcmpi(&a, 2), 0);
    assert_eq!(zcmpu(&a, 2), 0);

    // Test addition with negative results
    let temp_a = a.clone();
    zneg(&mut a, &temp_a);
    zset(&mut b, &_2);
    let temp_b = b.clone();
    zneg(&mut b, &temp_b);
    assert_eq!(zsignum(&a), -1);
    assert_eq!(zcmp(&a, &b), 0);
    assert!(zcmp(&a, &_2) < 0);
    assert_eq!(zcmpmag(&a, &b), 0);
    assert_eq!(zcmpmag(&a, &_2), 0);
    assert!(zcmpi(&a, 2) < 0);
    assert!(zcmpu(&a, 2) < 0);
    assert_eq!(zcmpi(&a, -2), 0);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);

    // Test addition with larger results
    zadd(&mut a, &_1, &_2);
    assert_eq!(zsignum(&a), 1);
    assert!(zcmp(&a, &_2) > 0);
    assert!(zcmpi(&a, 2) > 0);
    assert!(zcmpu(&a, 2) > 0);
    let temp_a = a.clone();
    zneg(&mut a, &temp_a);
    zset(&mut b, &_2);
    let temp_b = b.clone();
    zneg(&mut b, &temp_b);
    assert_eq!(zsignum(&a), -1);
    assert!(zcmpmag(&a, &_2) > 0);
    assert!(zcmpmag(&a, &b) > 0);
    assert!(zcmp(&a, &b) < 0);
    assert!(zcmp(&a, &_2) < 0);
    assert!(zcmpi(&a, 2) < 0);
    assert!(zcmpu(&a, 2) < 0);
    assert!(zcmpi(&a, -2) < 0);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert!(zcmp(&a, &_2) < 0);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    let temp_3 = _3.clone();
    zneg(&mut b, &temp_3);
    assert_eq!(zcmp(&a, &b), 0);
}

#[test]
fn test_3() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Test basic subtraction operations
    zsub(&mut a, &_2, &_1);
    assert!(zcmpmag(&_2, &_1) > 0);
    assert!(zcmpmag(&_2, &_0) > 0);
    assert!(zcmpmag(&_1, &_0) > 0);
    zsub(&mut b, &_1, &_2);
    assert!(zcmpmag(&_2, &_0) > 0);
    assert!(zcmpmag(&_1, &_0) > 0);
    assert!(zcmpmag(&_2, &_1) > 0);
    assert_eq!(zcmpmag(&a, &b), 0);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &b) > 0);
    assert_eq!(zcmp(&a, &_1), 0);
    assert!(zcmp(&b, &_1) < 0);

    // Test subtraction resulting in zero
    zsub(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_0), 0);
    zseti(&mut b, 0);
    zsetu(&mut c, 0);
    zsub(&mut a, &b, &c);
    assert_eq!(zcmp(&a, &_0), 0);

    // Test more subtraction cases
    assert!(zcmpmag(&_2, &_1) > 0);
    assert!(zcmp(&_2, &_1) > 0);
    zsub(&mut a, &_2, &_1);
    assert_eq!(zsignum(&a), 1);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zsub(&mut a, &temp_a, &_1);
    assert_eq!(zcmp(&a, &_0), 0);
    let temp_a = a.clone();
    zsub(&mut a, &temp_a, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    zsub(&mut a, &_1, &_2);
    assert!(zcmp(&a, &_1) < 0);
    assert_eq!(zcmpmag(&a, &_1), 0);

    // Test absolute value operations
    let temp_a = a.clone();
    zabs(&mut a, &temp_a);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zabs(&mut a, &temp_a);
    assert_eq!(zcmp(&a, &_1), 0);
    zabs(&mut a, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zabs(&mut a, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
}

#[test]
fn test_4() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Test operations with negative numbers
    zseti(&mut b, -1);
    zseti(&mut c, -2);
    zadd(&mut a, &_0, &b);
    assert!(zcmp(&a, &_0) < 0);
    assert_eq!(zcmpi(&a, -1), 0);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &_1) < 0);
    zadd(&mut a, &b, &_0);
    assert!(zcmp(&a, &_0) < 0);
    assert_eq!(zcmpi(&a, -1), 0);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &_1) < 0);
    zadd(&mut a, &b, &c);
    assert!(zcmp(&a, &c) < 0);
    assert!(zcmpmag(&a, &_2) > 0);
    zadd(&mut a, &c, &b);
    assert!(zcmp(&a, &c) < 0);
    assert!(zcmpmag(&a, &_2) > 0);
    zadd(&mut a, &b, &_1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zcmpmag(&a, &_0), 0);
    zadd(&mut a, &_1, &b);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zcmpmag(&a, &_0), 0);

    // Test subtraction with negative numbers
    let temp_1 = _1.clone();
    zneg(&mut b, &temp_1);
    let temp_2 = _2.clone();
    zneg(&mut c, &temp_2);
    zsub(&mut a, &_0, &b);
    assert_eq!(zcmp(&a, &_1), 0);
    zsub(&mut a, &b, &_0);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &_1) < 0);
    zsub(&mut a, &b, &c);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert_eq!(zcmp(&a, &_1), 0);
    zsub(&mut a, &c, &b);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &_1) < 0);
    zsub(&mut a, &b, &_1);
    assert_eq!(zcmpmag(&a, &_2), 0);
    assert!(zcmp(&a, &_2) < 0);
    assert_eq!(zcmp(&a, &c), 0);
    zsub(&mut a, &_1, &b);
    assert!(zcmp(&b, &_1) < 0);
    assert_eq!(zcmpmag(&b, &_1), 0);
    assert_eq!(zcmp(&a, &_2), 0);

    // Test unsigned operations
    let temp_1 = _1.clone();
    zneg(&mut b, &temp_1);
    let temp_2 = _2.clone();
    zneg(&mut c, &temp_2);

    zadd_unsigned(&mut a, &b, &c);
    assert_eq!(zcmp(&a, &_3), 0);
    zadd_unsigned(&mut a, &b, &c);
    assert_eq!(zcmp(&a, &_3), 0);
    zadd_unsigned(&mut a, &b, &_2);
    assert_eq!(zcmp(&a, &_3), 0);
    zadd_unsigned(&mut a, &_1, &c);
    assert_eq!(zcmp(&a, &_3), 0);

    zadd_unsigned(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    zadd_unsigned(&mut a, &_0, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zadd_unsigned(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_2), 0);
    zadd_unsigned(&mut a, &_1, &_0);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zadd_unsigned(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    zadd_unsigned(&mut a, &_0, &_1);
    assert!(zcmp(&a, &_1) != 0);
    zadd_unsigned(&mut a, &_0, &_1);
    assert_eq!(zcmpmag(&a, &_1), 0);
    zadd_unsigned(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_2), 0);
    zadd_unsigned(&mut a, &_1, &_0);
    assert!(zcmp(&a, &_1) != 0);
    zadd_unsigned(&mut a, &_1, &_0);
    assert_eq!(zcmpmag(&a, &_1), 0);
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);

    zsub_unsigned(&mut a, &_2, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zsub_unsigned(&mut a, &_2, &b);
    assert_eq!(zcmp(&a, &_1), 0);
    zsub_unsigned(&mut a, &c, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zsub_unsigned(&mut a, &c, &b);
    assert_eq!(zcmp(&a, &_1), 0);

    zsub_unsigned(&mut a, &_1, &_2);
    assert_eq!(zcmp(&a, &b), 0);
    zsub_unsigned(&mut a, &b, &_2);
    assert_eq!(zcmp(&a, &b), 0);
    zsub_unsigned(&mut a, &_1, &c);
    assert_eq!(zcmp(&a, &b), 0);
    zsub_unsigned(&mut a, &b, &c);
    assert_eq!(zcmp(&a, &b), 0);
}

#[test]
fn test_5() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // AND operations
    zand(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zand(&mut a, &_0, &_1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zand(&mut a, &_0, &_2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zand(&mut a, &_0, &_3);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zand(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zand(&mut a, &_1, &_2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zand(&mut a, &_1, &_3);
    assert_eq!(zcmp(&a, &_1), 0);
    zand(&mut a, &_2, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zand(&mut a, &_2, &_3);
    assert_eq!(zcmp(&a, &_2), 0);
    zand(&mut a, &_3, &_3);
    assert_eq!(zcmp(&a, &_3), 0);

    // OR operations
    zor(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zor(&mut a, &_0, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zor(&mut a, &_0, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zor(&mut a, &_0, &_3);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zor(&mut a, &_1, &_2);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_1, &_3);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_2, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zor(&mut a, &_2, &_3);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_3, &_3);
    assert_eq!(zcmp(&a, &_3), 0);

    // XOR operations
    zxor(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zxor(&mut a, &_0, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zxor(&mut a, &_0, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zxor(&mut a, &_0, &_3);
    assert_eq!(zcmp(&a, &_3), 0);
    zxor(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zxor(&mut a, &_1, &_2);
    assert_eq!(zcmp(&a, &_3), 0);
    zxor(&mut a, &_1, &_3);
    assert_eq!(zcmp(&a, &_2), 0);
    zxor(&mut a, &_2, &_2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zxor(&mut a, &_2, &_3);
    assert_eq!(zcmp(&a, &_1), 0);
    zxor(&mut a, &_3, &_3);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);

    // Negative number bitwise operations
    let temp_1 = _1.clone();
    zneg(&mut b, &temp_1);
    let temp_3 = _3.clone();
    zneg(&mut c, &temp_3);
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zand(&mut a, &b, &c);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zand(&mut a, &b, &_3);
    assert_eq!(zcmp(&a, &_1), 0);
    zand(&mut a, &_1, &c);
    assert_eq!(zcmp(&a, &_1), 0);
    zand(&mut a, &_0, &c);
    assert_eq!(zcmp(&a, &_0), 0);
    zand(&mut a, &b, &_0);
    assert_eq!(zcmp(&a, &_0), 0);

    let temp_1 = _1.clone();
    zneg(&mut b, &temp_1);
    let temp_2 = _2.clone();
    zneg(&mut c, &temp_2);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    zor(&mut a, &b, &c);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &b, &_2);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_1, &c);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    zor(&mut a, &_0, &c);
    assert_eq!(zcmp(&a, &c), 0);
    zor(&mut a, &b, &_0);
    assert_eq!(zcmp(&a, &b), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);

    let temp_1 = _1.clone();
    zneg(&mut b, &temp_1);
    let temp_2 = _2.clone();
    zneg(&mut c, &temp_2);
    zxor(&mut a, &b, &c);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    zxor(&mut a, &b, &_2);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    zxor(&mut a, &_1, &c);
    assert_eq!(zcmpmag(&a, &_3), 0);
    assert_eq!(zcmp(&a, &_3), 0);
    zxor(&mut a, &b, &_0);
    assert_eq!(zcmpmag(&a, &b), 0);
    assert_eq!(zcmp(&a, &b), 0);
    zxor(&mut a, &_0, &c);
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
}

#[test]
fn test_6() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Left shift operations
    zlsh(&mut a, &_0, 0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zlsh(&mut a, &_0, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zlsh(&mut a, &_1, 0);
    assert_eq!(zcmp(&a, &_1), 0);
    zlsh(&mut a, &_1, 1);
    assert_eq!(zcmp(&a, &_2), 0);
    zlsh(&mut a, &_1, 2);
    assert!(zcmp(&a, &_2) > 0);
    zlsh(&mut a, &_2, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    zlsh(&mut a, &_2, 1);
    assert!(zcmp(&a, &_2) > 0);

    zset(&mut a, &_0);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zset(&mut a, &_1);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 1);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 2);
    assert!(zcmp(&a, &_2) > 0);
    zset(&mut a, &_2);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_a = a.clone();
    zlsh(&mut a, &temp_a, 1);
    assert!(zcmp(&a, &_2) > 0);

    // Right shift operations
    zrsh(&mut a, &_0, 0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zrsh(&mut a, &_0, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zrsh(&mut a, &_1, 0);
    assert_eq!(zcmp(&a, &_1), 0);
    zrsh(&mut a, &_1, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zrsh(&mut a, &_1, 2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zrsh(&mut a, &_2, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    zrsh(&mut a, &_2, 1);
    assert_eq!(zcmp(&a, &_1), 0);
    zrsh(&mut a, &_2, 2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);

    zset(&mut a, &_0);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zset(&mut a, &_1);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 1);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);
    zset(&mut a, &_2);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 0);
    assert_eq!(zcmp(&a, &_2), 0);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 1);
    assert_eq!(zcmp(&a, &_1), 0);
    let temp_a = a.clone();
    zrsh(&mut a, &temp_a, 2);
    assert_eq!(zcmp(&a, &_0), 0);
    assert_eq!(zzero(&a), 1);

    // Bit test operations
    assert_eq!(zbtest(&_0, 0), 0);
    assert_eq!(zbtest(&_1, 0), 1);
    assert_eq!(zbtest(&_2, 0), 0);
    assert_eq!(zbtest(&_3, 0), 1);
    assert_eq!(zbtest(&_0, 1), 0);
    assert_eq!(zbtest(&_1, 1), 0);
    assert_eq!(zbtest(&_2, 1), 1);
    assert_eq!(zbtest(&_3, 1), 1);
    assert_eq!(zbtest(&_0, 2), 0);
    assert_eq!(zbtest(&_1, 2), 0);
    assert_eq!(zbtest(&_2, 2), 0);
    assert_eq!(zbtest(&_3, 2), 0);

    // NOT operation
    znot(&mut a, &_2);
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert!(zcmp(&a, &_1) != 0);
    let temp_a = a.clone();
    znot(&mut a, &temp_a);
    assert_eq!(zcmp(&a, &_0), 0);

    // Truncate operation
    zsetu(&mut a, 0x1234);
    zsetu(&mut c, 0x234);
    let temp_a = a.clone();
    ztrunc(&mut a, &temp_a, 12);
    assert_eq!(zcmp(&a, &c), 0);

    // Split operation
    zsetu(&mut a, 0xEEFF);
    zsetu(&mut c, 0xEE);
    zsetu(&mut d, 0xFF);
    let temp_a = a.clone();
    zsplit(&mut a, &mut b, &temp_a, 8);
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmpmag(&b, &d), 0);
    zsetu(&mut a, 0xEEFF);
    let temp_a = a.clone();
    zsplit(&mut b, &mut a, &temp_a, 8);
    assert_eq!(zcmpmag(&b, &c), 0);
    assert_eq!(zcmpmag(&a, &d), 0);
}

#[test]
fn test_7() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Multiplication
    zmul(&mut a, &_2, &_3);
    assert_eq!(zcmpi(&a, 6), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    zmul(&mut a, &_2, &_3);
    assert_eq!(zcmpi(&a, -6), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    zmul(&mut a, &_2, &_3);
    assert_eq!(zcmpi(&a, -6), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    zmul(&mut a, &_2, &_3);
    assert_eq!(zcmpi(&a, 6), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);

    // Square
    zmul(&mut a, &_3, &_3);
    assert_eq!(zcmpi(&a, 9), 0);
    zsqr(&mut a, &_3);
    assert_eq!(zcmpi(&a, 9), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);
    zmul(&mut a, &_3, &_3);
    assert_eq!(zcmpi(&a, 9), 0);
    zsqr(&mut a, &_3);
    assert_eq!(zcmpi(&a, 9), 0);
    let temp_3 = _3.clone();
    zneg(&mut _3, &temp_3);

    // Division
    zseti(&mut a, 8);
    zseti(&mut b, 2);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 4), 0);
    zseti(&mut b, -2);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, -4), 0);
    zseti(&mut a, -8);
    zseti(&mut b, 2);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, -4), 0);
    zseti(&mut b, -2);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 4), 0);

    zseti(&mut a, 1000);
    zseti(&mut b, 10);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 100), 0);
    zseti(&mut b, -10);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, -100), 0);
    zseti(&mut a, -1000);
    zseti(&mut b, 10);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, -100), 0);
    zseti(&mut b, -10);
    zdiv(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 100), 0);

    // Modulo
    zseti(&mut a, 7);
    zseti(&mut b, 3);
    zmod(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut b, -3);
    zmod(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut a, -7);
    zseti(&mut b, 3);
    zmod(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut b, -3);
    zmod(&mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&c, 1), 0);

    // Division with modulo
    zseti(&mut a, 7);
    zseti(&mut b, 3);
    zdivmod(&mut d, &mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&d, 2), 0);
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut b, -3);
    zdivmod(&mut d, &mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&d, -2), 0);
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut a, -7);
    zseti(&mut b, 3);
    zdivmod(&mut d, &mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&d, -2), 0);
    assert_eq!(zcmpi(&c, 1), 0);
    zseti(&mut b, -3);
    zdivmod(&mut d, &mut c, &a, &b).unwrap();
    assert_eq!(zcmpi(&d, 2), 0);
    assert_eq!(zcmpi(&c, 1), 0);

    // Modular multiplication
    zseti(&mut a, 102);
    zseti(&mut b, 501);
    zseti(&mut c, 5);
    let temp_a = a.clone();
    zmodmul(&mut a, &temp_a, &b, &c).unwrap();
    assert_eq!(zcmp(&a, &_2), 0);

    // GCD
    zseti(&mut b, 2 * 3 * 3 * 7);
    zseti(&mut c, 3 * 7 * 11);
    zseti(&mut d, 3 * 7);
    zgcd(&mut a, &_0, &_0);
    assert_eq!(zcmp(&a, &_0), 0);
    zgcd(&mut a, &b, &_0);
    assert_eq!(zcmp(&a, &b), 0);
    zgcd(&mut a, &_0, &c);
    assert_eq!(zcmp(&a, &c), 0);
    zgcd(&mut a, &b, &b);
    assert_eq!(zcmp(&a, &b), 0);
    zgcd(&mut a, &b, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zgcd(&mut a, &_2, &b);
    assert_eq!(zcmp(&a, &_2), 0);
    zgcd(&mut a, &_2, &_2);
    assert_eq!(zcmp(&a, &_2), 0);
    zgcd(&mut a, &c, &_2);
    assert_eq!(zcmp(&a, &_1), 0);
    zgcd(&mut a, &_2, &c);
    assert_eq!(zcmp(&a, &_1), 0);
    zgcd(&mut a, &b, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zgcd(&mut a, &_1, &c);
    assert_eq!(zcmp(&a, &_1), 0);
    zgcd(&mut a, &_1, &_1);
    assert_eq!(zcmp(&a, &_1), 0);
    zgcd(&mut a, &b, &c);
    assert_eq!(zcmp(&a, &d), 0);
    zgcd(&mut a, &c, &b);
    assert_eq!(zcmp(&a, &d), 0);
}

#[test]
fn test_8() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Power with negative exponent
    zseti(&mut a, 10);
    zseti(&mut b, -1);
    let temp_a = a.clone();
    zpow(&mut a, &temp_a, &b).unwrap();
    assert_eq!(zcmp(&a, &_0), 0);

    zseti(&mut a, 10);
    zseti(&mut b, -1);
    zseti(&mut c, 3); // Initialize c before using in modpow
    zseti(&mut a, 20);
    let temp_a = a.clone();
    zmodpow(&mut a, &temp_a, &b, &c).unwrap();
    assert_eq!(zcmp(&a, &_0), 0);

    // Power with unsigned exponent
    zseti(&mut a, 10);
    zseti(&mut c, 100000);
    let temp_a = a.clone();
    zpowu(&mut a, &temp_a, 5).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    zseti(&mut a, -10);
    zseti(&mut c, -100000);
    let temp_a = a.clone();
    zpowu(&mut a, &temp_a, 5).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    zseti(&mut a, -10);
    zseti(&mut c, 10000);
    let temp_a = a.clone();
    zpowu(&mut a, &temp_a, 4).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    // Modular power with unsigned exponent
    zseti(&mut a, 10);
    zseti(&mut c, 3);
    let temp_a = a.clone();
    zmodpowu(&mut a, &temp_a, 5, &c).unwrap();
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert_eq!(zcmp(&a, &_1), 0);

    // Power with signed exponent
    zseti(&mut a, 10);
    zseti(&mut b, 5);
    zseti(&mut c, 100000);
    let temp_a = a.clone();
    zpow(&mut a, &temp_a, &b).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    zseti(&mut a, -10);
    zseti(&mut b, 5);
    zseti(&mut c, -100000);
    let temp_a = a.clone();
    zpow(&mut a, &temp_a, &b).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    zseti(&mut a, -10);
    zseti(&mut b, 4);
    zseti(&mut c, 10000);
    let temp_a = a.clone();
    zpow(&mut a, &temp_a, &b).unwrap();
    assert_eq!(zcmpmag(&a, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    // Modular power with signed exponent
    zseti(&mut a, 10);
    zseti(&mut b, 5);
    zseti(&mut c, 3);
    let temp_a = a.clone();
    zmodpow(&mut a, &temp_a, &b, &c).unwrap();
    assert_eq!(zcmpmag(&a, &_1), 0);
    assert_eq!(zcmp(&a, &_1), 0);
}

#[test]
fn test_9() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);
    let mut buf: String;

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // String parsing and conversion
    a = zsets("1234").unwrap();
    assert_eq!(zcmpi(&a, 1234), 0);
    b = zsets("+1234").unwrap();
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr_length(&_0, 10).unwrap(), 1);
    assert_eq!(zstr_length(&_1, 10).unwrap(), 1);
    assert_eq!(zstr_length(&_2, 10).unwrap(), 1);
    assert_eq!(zstr_length(&_3, 10).unwrap(), 1);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert_eq!(zstr_length(&_2, 10).unwrap(), 2);
    let temp_2 = _2.clone();
    zneg(&mut _2, &temp_2);
    assert_eq!(zstr_length(&a, 10).unwrap(), 4);
    buf = zstr(&a);
    assert_eq!(buf, "1234");
    a = zsets("-1234").unwrap();
    zseti(&mut b, -1234);
    zseti(&mut c, 1234);
    assert!(zcmp(&a, &_0) < 0);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zcmpmag(&a, &c), 0);
    assert!(zcmp(&a, &c) < 0);
    buf = zstr(&a);
    assert_eq!(buf, "-1234");
    buf = zstr(&a);
    assert_eq!(buf, "-1234");

    // Random number generation
    zsetu(&mut d, 100000);
    a = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &d).unwrap();
    assert!(zcmp(&a, &_0) >= 0);
    assert!(zcmp(&a, &d) <= 0);
    b = zrand(zranddev::SECURE_RANDOM, zranddist::UNIFORM, &d).unwrap();
    assert!(zcmp(&b, &_0) >= 0);
    assert!(zcmp(&b, &d) <= 0);
    c = zrand(zranddev::FAST_RANDOM, zranddist::UNIFORM, &d).unwrap();
    assert!(zcmp(&c, &_0) >= 0);
    assert!(zcmp(&c, &d) <= 0);
    assert!(zcmp(&a, &b) != 0);
    assert!(zcmp(&a, &c) != 0);
    assert!(zcmp(&b, &c) != 0);

    // PRIME testing
    zseti(&mut a, -5);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, -4);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, -3);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, -2);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, -1);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 0);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 1);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 2);
    assert_eq!(zptest(None, &a, 100), zprimality::PRIME);
    zseti(&mut a, 3);
    assert_eq!(zptest(None, &a, 100), zprimality::PRIME);
    zseti(&mut a, 4);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 5);
    assert!(zptest(None, &a, 100) != zprimality::NONPRIME);
    zseti(&mut a, 6);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 7);
    assert!(zptest(None, &a, 100) != zprimality::NONPRIME);
    zseti(&mut a, 8);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 9);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 10);
    assert_eq!(zptest(None, &a, 100), zprimality::NONPRIME);
    zseti(&mut a, 11);
    assert!(zptest(None, &a, 100) != zprimality::NONPRIME);
    zseti(&mut a, 101);
    assert!(zptest(None, &a, 100) != zprimality::NONPRIME);
}

#[test]
fn test_10() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Error condition tests - assert_nr means the operation should return an error
    // zdivmod errors
    assert!(zdivmod(&mut a, &mut b, &_0, &_0).is_err());
    assert!(zdivmod(&mut a, &mut b, &_1, &_0).is_err());
    zdivmod(&mut a, &mut b, &_0, &_1).unwrap();
    zdivmod(&mut a, &mut b, &_1, &_1).unwrap();

    // zdiv errors
    assert!(zdiv(&mut a, &_0, &_0).is_err());
    assert!(zdiv(&mut a, &_1, &_0).is_err());
    zdiv(&mut a, &_0, &_1).unwrap();
    zdiv(&mut a, &_1, &_1).unwrap();

    // zmod errors
    assert!(zmod(&mut a, &_0, &_0).is_err());
    assert!(zmod(&mut a, &_1, &_0).is_err());
    zmod(&mut a, &_0, &_1).unwrap();
    zmod(&mut a, &_1, &_1).unwrap();

    // zpow errors
    assert!(zpow(&mut a, &_0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zpow(&mut a, &_0, &_1).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zpow(&mut a, &_0, &_1).unwrap();
    zpow(&mut a, &_1, &_0).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zpow(&mut a, &_1, &_0).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);

    // zmodmul errors
    assert!(zmodmul(&mut a, &_1, &_1, &_0).is_err());

    // zmodpow errors
    assert!(zmodpow(&mut a, &_0, &_0, &_1).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpow(&mut a, &_0, &_1, &_1).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zmodpow(&mut a, &_0, &_1, &_1).unwrap();
    zmodpow(&mut a, &_1, &_0, &_1).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zmodpow(&mut a, &_1, &_0, &_1).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpow(&mut a, &_0, &_0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpow(&mut a, &_0, &_1, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpow(&mut a, &_0, &_1, &_0).is_err());
    assert!(zmodpow(&mut a, &_1, &_0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpow(&mut a, &_1, &_0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);

    // zpowu errors
    assert!(zpowu(&mut a, &_0, 0).is_err());
    zpowu(&mut a, &_0, 1).unwrap();
    zpowu(&mut a, &_1, 0).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zpowu(&mut a, &_1, 0).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);

    // zmodpowu errors
    assert!(zmodpowu(&mut a, &_0, 0, &_1).is_err());
    zmodpowu(&mut a, &_0, 1, &_1).unwrap();
    zmodpowu(&mut a, &_1, 0, &_1).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    zmodpowu(&mut a, &_1, 0, &_1).unwrap();
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpowu(&mut a, &_0, 0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpowu(&mut a, &_0, 1, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpowu(&mut a, &_0, 1, &_0).is_err());
    assert!(zmodpowu(&mut a, &_1, 0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
    assert!(zmodpowu(&mut a, &_1, 0, &_0).is_err());
    let temp_1 = _1.clone();
    zneg(&mut _1, &temp_1);
}

#[test]
fn test_11() {

    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);
    let mut buf = String::new();

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Large number string conversion tests
    zsetu(&mut a, 1);
    buf = zstr(&a);
    assert_eq!(buf, "1");
    zsetu(&mut a, 10);
    buf = zstr(&a);
    assert_eq!(buf, "10");
    zsetu(&mut a, 100);
    buf = zstr(&a);
    assert_eq!(buf, "100");
    zsetu(&mut a, 1000);
    buf = zstr(&a);
    assert_eq!(buf, "1000");
    zsetu(&mut a, 10000);
    buf = zstr(&a);
    assert_eq!(buf, "10000");
    zsetu(&mut a, 100000);
    buf = zstr(&a);
    assert_eq!(buf, "100000");
    zsetu(&mut a, 1000000);
    buf = zstr(&a);
    assert_eq!(buf, "1000000");
    zsetu(&mut a, 10000000);
    buf = zstr(&a);
    assert_eq!(buf, "10000000");
    zsetu(&mut a, 100000000);
    buf = zstr(&a);
    assert_eq!(buf, "100000000");
    zsetu(&mut a, 999999999);
    buf = zstr(&a);
    assert_eq!(buf, "999999999");
    zsetu(&mut a, 1000000000);
    buf = zstr(&a);
    assert_eq!(buf, "1000000000");
    zsetu(&mut a, 1000000001);
    buf = zstr(&a);
    assert_eq!(buf, "1000000001");
    zsetu(&mut a, 2000000000);
    buf = zstr(&a);
    assert_eq!(buf, "2000000000");
    zsetu(&mut a, 2050000000);
    buf = zstr(&a);
    assert_eq!(buf, "2050000000");
    zsetu(&mut a, 2100000000);
    buf = zstr(&a);
    assert_eq!(buf, "2100000000");
    zsetu(&mut a, 2140000000);
    buf = zstr(&a);
    assert_eq!(buf, "2140000000");
    zsetu(&mut a, 2147000000);
    buf = zstr(&a);
    assert_eq!(buf, "2147000000");
    zsetu(&mut a, 2147483000);
    buf = zstr(&a);
    assert_eq!(buf, "2147483000");
    zsetu(&mut a, 2147483640);
    buf = zstr(&a);
    assert_eq!(buf, "2147483640");
    zsetu(&mut a, 2147483646);
    buf = zstr(&a);
    assert_eq!(buf, "2147483646");

    zseti(&mut a, 2147483647);
    buf = zstr(&a);
    assert_eq!(buf, "2147483647");
    zseti(&mut a, -2147483647);
    buf = zstr(&a);
    assert_eq!(buf, "-2147483647");
    zseti(&mut a, -2147483647 - 1);
    buf = zstr(&a);
    assert_eq!(buf, "-2147483648");

    zsetu(&mut a, 2147483647);
    buf = zstr(&a);
    assert_eq!(buf, "2147483647");
    zsetu(&mut a, 2147483648);
    buf = zstr(&a);
    assert_eq!(buf, "2147483648");
    zsetu(&mut a, 2147483649);
    buf = zstr(&a);
    assert_eq!(buf, "2147483649");

    zsetu(&mut a, 3000000000);
    buf = zstr(&a);
    assert_eq!(buf, "3000000000");
    zsetu(&mut a, 3100000000);
    buf = zstr(&a);
    assert_eq!(buf, "3100000000");
    zsetu(&mut a, 3200000000);
    buf = zstr(&a);
    assert_eq!(buf, "3200000000");
    zsetu(&mut a, 3300000000);
    buf = zstr(&a);
    assert_eq!(buf, "3300000000");
    zsetu(&mut a, 3400000000);
    buf = zstr(&a);
    assert_eq!(buf, "3400000000");
    zsetu(&mut a, 3500000000);
    buf = zstr(&a);
    assert_eq!(buf, "3500000000");
    zsetu(&mut a, 3600000000);
    buf = zstr(&a);
    assert_eq!(buf, "3600000000");
    zsetu(&mut a, 3700000000);
    buf = zstr(&a);
    assert_eq!(buf, "3700000000");
    zsetu(&mut a, 3800000000);
    buf = zstr(&a);
    assert_eq!(buf, "3800000000");
    zsetu(&mut a, 3900000000);
    buf = zstr(&a);
    assert_eq!(buf, "3900000000");
    zsetu(&mut a, 3999999999);
    buf = zstr(&a);
    assert_eq!(buf, "3999999999");
    zsetu(&mut a, 4000000000);
    buf = zstr(&a);
    assert_eq!(buf, "4000000000");
    zsetu(&mut a, 4000000001);
    assert_eq!(zstr_length(&a, 10).unwrap(), 10);
    buf = zstr(&a);
    assert_eq!(buf, "4000000001");

    // Include test-random.c content - comprehensive function tests
    include_test_random_complete(&mut a, &mut b, &mut c, &mut d);
}

// Helper function for zeven_nonzero
fn zeven_nonzero(a: &z_t) -> i32 {
    // Check if even, assumes non-zero
    if (a & BigInt::one()).is_zero() { 1 } else { 0 }
}

// Helper function for zodd_nonzero
fn zodd_nonzero(a: &z_t) -> i32 {
    // Check if odd, assumes non-zero
    if !(a & BigInt::one()).is_zero() { 1 } else { 0 }
}

// This function contains all the test-random.c content
fn include_test_random_complete(mut a: &mut z_t, mut b: &mut z_t, mut c: &mut z_t, mut d: &mut z_t) {
    let mut n: usize;
    let mut buf: Vec<u8> = Vec::new();
    /* zzero */
    *a = zsets("1").unwrap();
    assert_eq!(zzero(&a), 0);

    *a = zsets("0").unwrap();
    assert_eq!(zzero(&a), 1);

    *a = zsets("1").unwrap();
    assert_eq!(zzero(&a), 0);

    *a = zsets("-1").unwrap();
    assert_eq!(zzero(&a), 0);

    *a = zsets("-1").unwrap();
    assert_eq!(zzero(&a), 0);


    /* zsignum */
    *a = zsets("-1").unwrap();
    assert_eq!(zsignum(&a), -1);

    *a = zsets("0").unwrap();
    assert_eq!(zsignum(&a), 0);

    *a = zsets("-3").unwrap();
    assert_eq!(zsignum(&a), -1);

    *a = zsets("1").unwrap();
    assert_eq!(zsignum(&a), 1);

    *a = zsets("2").unwrap();
    assert_eq!(zsignum(&a), 1);


    /* zeven_nonzero */
    *a = zsets("2").unwrap();
    assert_eq!(zeven_nonzero(&a), 1);

    *a = zsets("-8").unwrap();
    assert_eq!(zeven_nonzero(&a), 1);

    *a = zsets("-4").unwrap();
    assert_eq!(zeven_nonzero(&a), 1);

    *a = zsets("2").unwrap();
    assert_eq!(zeven_nonzero(&a), 1);

    *a = zsets("-3").unwrap();
    assert_eq!(zeven_nonzero(&a), 0);


    /* zodd_nonzero */
    *a = zsets("6").unwrap();
    assert_eq!(zodd_nonzero(&a), 0);

    *a = zsets("7").unwrap();
    assert_eq!(zodd_nonzero(&a), 1);

    *a = zsets("-4").unwrap();
    assert_eq!(zodd_nonzero(&a), 0);

    *a = zsets("-5").unwrap();
    assert_eq!(zodd_nonzero(&a), 1);

    *a = zsets("3").unwrap();
    assert_eq!(zodd_nonzero(&a), 1);


    /* zeven */
    *a = zsets("1").unwrap();
    assert_eq!(zeven(&a), 0);

    *a = zsets("-1").unwrap();
    assert_eq!(zeven(&a), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zeven(&a), 0);

    *a = zsets("-1").unwrap();
    assert_eq!(zeven(&a), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zeven(&a), 0);


    /* zcmp */
    *a = zsets("1").unwrap();
    *b = zsets("0").unwrap();
    assert_eq!(zcmp(&a, &b), 1);

    *a = zsets("3").unwrap();
    *b = zsets("4").unwrap();
    assert_eq!(zcmp(&a, &b), -1);

    *a = zsets("0").unwrap();
    *b = zsets("0").unwrap();
    assert_eq!(zcmp(&a, &b), 0);

    *a = zsets("-6").unwrap();
    *b = zsets("1").unwrap();
    assert_eq!(zcmp(&a, &b), -1);

    *a = zsets("1").unwrap();
    *b = zsets("-2").unwrap();
    assert_eq!(zcmp(&a, &b), 1);


    /* zcmpi */
    *a = zsets("-1").unwrap();
    assert_eq!(zcmpi(&a, -631556921459996383i64 - 1i64), 1);

    *a = zsets("-1").unwrap();
    assert_eq!(zcmpi(&a, -860989285280235032i64 - 1i64), 1);

    *a = zsets("3").unwrap();
    assert_eq!(zcmpi(&a, 3843065909583822856i64), -1);

    *a = zsets("-8").unwrap();
    assert_eq!(zcmpi(&a, 6380422529430794010i64), -1);

    *a = zsets("0").unwrap();
    assert_eq!(zcmpi(&a, -4399213862147245037i64 - 1i64), 1);


    /* zcmpu */
    *a = zsets("2").unwrap();
    assert_eq!(zcmpu(&a, 18126255354594005202u64), -1);

    *a = zsets("-1").unwrap();
    assert_eq!(zcmpu(&a, 17479879725101897725u64), -1);

    *a = zsets("0").unwrap();
    assert_eq!(zcmpu(&a, 11017937424768121079u64), -1);

    *a = zsets("-4").unwrap();
    assert_eq!(zcmpu(&a, 13760049040475088813u64), -1);

    *a = zsets("-1").unwrap();
    assert_eq!(zcmpu(&a, 10109002758525979270u64), -1);


    /* zcmpmag */
    *a = zsets("0").unwrap();
    *b = zsets("2").unwrap();
    assert_eq!(zcmpmag(&a, &b), -1);

    *a = zsets("-2").unwrap();
    *b = zsets("2").unwrap();
    assert_eq!(zcmpmag(&a, &b), 0);

    *a = zsets("-6").unwrap();
    *b = zsets("-1").unwrap();
    assert_eq!(zcmpmag(&a, &b), 1);

    *a = zsets("-3").unwrap();
    *b = zsets("-1").unwrap();
    assert_eq!(zcmpmag(&a, &b), 1);

    *a = zsets("3").unwrap();
    *b = zsets("-1").unwrap();
    assert_eq!(zcmpmag(&a, &b), 1);


    /* zodd */
    *a = zsets("6").unwrap();
    assert_eq!(zodd(&a), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zodd(&a), 1);

    *a = zsets("-1").unwrap();
    assert_eq!(zodd(&a), 1);

    *a = zsets("-2").unwrap();
    assert_eq!(zodd(&a), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zodd(&a), 1);


    /* zabs */
    *a = zsets("-2").unwrap();
    zabs(&mut b, &a);
    let a_clone = a.clone(); zabs(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "2");

    *a = zsets("7").unwrap();
    zabs(&mut b, &a);
    let a_clone = a.clone(); zabs(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "7");

    *a = zsets("-1").unwrap();
    zabs(&mut b, &a);
    let a_clone = a.clone(); zabs(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "1");

    *a = zsets("5").unwrap();
    zabs(&mut b, &a);
    let a_clone = a.clone(); zabs(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "5");

    *a = zsets("1").unwrap();
    zabs(&mut b, &a);
    let a_clone = a.clone(); zabs(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "1");


    /* zneg */
    *a = zsets("-7").unwrap();
    zneg(&mut b, &a);
    let a_clone = a.clone(); zneg(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "7");

    *a = zsets("0").unwrap();
    zneg(&mut b, &a);
    let a_clone = a.clone(); zneg(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");

    *a = zsets("2").unwrap();
    zneg(&mut b, &a);
    let a_clone = a.clone(); zneg(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-2");

    *a = zsets("1").unwrap();
    zneg(&mut b, &a);
    let a_clone = a.clone(); zneg(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-1");

    *a = zsets("4").unwrap();
    zneg(&mut b, &a);
    let a_clone = a.clone(); zneg(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-4");


    /* zlsh */
    *a = zsets("4").unwrap();
    zlsh(&mut b, &a, 3);
    let a_clone = a.clone(); zlsh(&mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "32");

    *a = zsets("-1").unwrap();
    zlsh(&mut b, &a, 0);
    let a_clone = a.clone(); zlsh(&mut a, &a_clone, 0);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-1");

    *a = zsets("3").unwrap();
    zlsh(&mut b, &a, 0);
    let a_clone = a.clone(); zlsh(&mut a, &a_clone, 0);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "3");

    *a = zsets("1").unwrap();
    zlsh(&mut b, &a, 3);
    let a_clone = a.clone(); zlsh(&mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "8");

    *a = zsets("2").unwrap();
    zlsh(&mut b, &a, 1);
    let a_clone = a.clone(); zlsh(&mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "4");


    /* zrsh */
    *a = zsets("-2").unwrap();
    zrsh(&mut b, &a, 2);
    let a_clone = a.clone(); zrsh(&mut a, &a_clone, 2);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");

    *a = zsets("2").unwrap();
    zrsh(&mut b, &a, 1);
    let a_clone = a.clone(); zrsh(&mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "1");

    *a = zsets("-2").unwrap();
    zrsh(&mut b, &a, 2);
    let a_clone = a.clone(); zrsh(&mut a, &a_clone, 2);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");

    *a = zsets("-1").unwrap();
    zrsh(&mut b, &a, 1);
    let a_clone = a.clone(); zrsh(&mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");

    *a = zsets("-4").unwrap();
    zrsh(&mut b, &a, 3);
    let a_clone = a.clone(); zrsh(&mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");


    /* ztrunc */
    *a = zsets("-2").unwrap();
    ztrunc(&mut b, &a, 1);
    let a_clone = a.clone(); ztrunc(&mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");

    *a = zsets("2").unwrap();
    ztrunc(&mut b, &a, 5);
    let a_clone = a.clone(); ztrunc(&mut a, &a_clone, 5);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "2");

    *a = zsets("-2").unwrap();
    ztrunc(&mut b, &a, 3);
    let a_clone = a.clone(); ztrunc(&mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-2");

    *a = zsets("-5").unwrap();
    ztrunc(&mut b, &a, 2);
    let a_clone = a.clone(); ztrunc(&mut a, &a_clone, 2);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "-1");

    *a = zsets("0").unwrap();
    ztrunc(&mut b, &a, 1);
    let a_clone = a.clone(); ztrunc(&mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &b), 0);
    assert_eq!(zstr(&a), "0");


    /* zsplit */
    *a = zsets("1").unwrap();
    zset(&mut b, &a);
    let b_clone = b.clone(); zsplit(&mut b, &mut d, &b_clone, 6);
    assert_eq!(zstr(&b), "0");
    assert_eq!(zstr(&d), "1");
    zsplit(&mut c, &mut d, &a, 6);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); zsplit(&mut c, &mut a, &a_clone, 6);
    assert_eq!(zcmp(&a, &d), 0);
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("0").unwrap();
    zset(&mut b, &a);
    let b_clone = b.clone(); zsplit(&mut b, &mut d, &b_clone, 3);
    assert_eq!(zstr(&b), "0");
    assert_eq!(zstr(&d), "0");
    zsplit(&mut c, &mut d, &a, 3);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zsplit(&mut c, &mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &d), 0);
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("0").unwrap();
    zset(&mut b, &a);
    let b_clone = b.clone(); zsplit(&mut b, &mut d, &b_clone, 3);
    assert_eq!(zstr(&b), "0");
    assert_eq!(zstr(&d), "0");
    zsplit(&mut c, &mut d, &a, 3);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zsplit(&mut c, &mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &d), 0);
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("1").unwrap();
    zset(&mut b, &a);
    let b_clone = b.clone(); zsplit(&mut b, &mut d, &b_clone, 1);
    assert_eq!(zstr(&b), "0");
    assert_eq!(zstr(&d), "1");
    zsplit(&mut c, &mut d, &a, 1);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); zsplit(&mut c, &mut a, &a_clone, 1);
    assert_eq!(zcmp(&a, &d), 0);
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("0").unwrap();
    zset(&mut b, &a);
    let b_clone = b.clone(); zsplit(&mut b, &mut d, &b_clone, 3);
    assert_eq!(zstr(&b), "0");
    assert_eq!(zstr(&d), "0");
    zsplit(&mut c, &mut d, &a, 3);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zsplit(&mut c, &mut a, &a_clone, 3);
    assert_eq!(zcmp(&a, &d), 0);
    assert_eq!(zcmp(&b, &c), 0);


    /* zand */
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zand(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zand(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");
    *a = zsets("-1").unwrap();
    zand(&mut d, &a, &a);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");

    *a = zsets("4").unwrap();
    *b = zsets("0").unwrap();
    zand(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zand(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    assert_eq!(zstr(&a), "0");
    *a = zsets("4").unwrap();
    zand(&mut d, &a, &a);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "4");
    assert_eq!(zstr(&a), "4");

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zand(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zand(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");
    *a = zsets("-1").unwrap();
    zand(&mut d, &a, &a);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");

    *a = zsets("2").unwrap();
    *b = zsets("2").unwrap();
    zand(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zand(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "2");
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");
    *a = zsets("2").unwrap();
    zand(&mut d, &a, &a);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");

    *a = zsets("-6").unwrap();
    *b = zsets("-1").unwrap();
    zand(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zand(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    assert_eq!(zstr(&a), "0");
    *a = zsets("-6").unwrap();
    zand(&mut d, &a, &a);
    let a_clone = a.clone(); zand(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "-6");
    assert_eq!(zstr(&a), "-6");


    /* zor */
    *a = zsets("3").unwrap();
    *b = zsets("0").unwrap();
    zor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "3");
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");
    *a = zsets("3").unwrap();
    zor(&mut d, &a, &a);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");

    *a = zsets("-3").unwrap();
    *b = zsets("6").unwrap();
    zor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-7");
    assert_eq!(zstr(&d), "-7");
    assert_eq!(zstr(&a), "-7");
    *a = zsets("-3").unwrap();
    zor(&mut d, &a, &a);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "-3");
    assert_eq!(zstr(&a), "-3");

    *a = zsets("2").unwrap();
    *b = zsets("-2").unwrap();
    zor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-2");
    assert_eq!(zstr(&d), "-2");
    assert_eq!(zstr(&a), "-2");
    *a = zsets("2").unwrap();
    zor(&mut d, &a, &a);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");

    *a = zsets("-3").unwrap();
    *b = zsets("1").unwrap();
    zor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-3");
    assert_eq!(zstr(&d), "-3");
    assert_eq!(zstr(&a), "-3");
    *a = zsets("-3").unwrap();
    zor(&mut d, &a, &a);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "-3");
    assert_eq!(zstr(&a), "-3");

    *a = zsets("2").unwrap();
    *b = zsets("0").unwrap();
    zor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "2");
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");
    *a = zsets("2").unwrap();
    zor(&mut d, &a, &a);
    let a_clone = a.clone(); zor(&mut a, &a_clone, &a_clone);
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");


    /* zxor */
    *a = zsets("0").unwrap();
    *b = zsets("1").unwrap();
    zxor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zxor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");
    *a = zsets("0").unwrap();
    zxor(&mut d, &a, &a);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&d), 1);
    assert_eq!(zzero(&a), 1);

    *a = zsets("3").unwrap();
    *b = zsets("0").unwrap();
    zxor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zxor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "3");
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");
    *a = zsets("3").unwrap();
    zxor(&mut d, &a, &a);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&d), 1);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-2").unwrap();
    *b = zsets("-1").unwrap();
    zxor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zxor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "3");
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");
    *a = zsets("-2").unwrap();
    zxor(&mut d, &a, &a);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&d), 1);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-2").unwrap();
    *b = zsets("-2").unwrap();
    zxor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zxor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    zxor(&mut d, &a, &a);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&d), 1);
    assert_eq!(zzero(&a), 1);

    *a = zsets("2").unwrap();
    *b = zsets("1").unwrap();
    zxor(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zxor(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "3");
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");
    *a = zsets("2").unwrap();
    zxor(&mut d, &a, &a);
    let a_clone = a.clone(); zxor(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&d), 1);
    assert_eq!(zzero(&a), 1);


    /* zbits */
    *a = zsets("1").unwrap();
    assert_eq!(zbits(&a), 1);

    *a = zsets("4").unwrap();
    assert_eq!(zbits(&a), 3);

    *a = zsets("-3").unwrap();
    assert_eq!(zbits(&a), 2);

    *a = zsets("1").unwrap();
    assert_eq!(zbits(&a), 1);

    *a = zsets("-1").unwrap();
    assert_eq!(zbits(&a), 1);


    /* zlsb */
    *a = zsets("1").unwrap();
    assert_eq!(zlsb(&a), 0);

    *a = zsets("-2").unwrap();
    assert_eq!(zlsb(&a), 1);

    *a = zsets("-8").unwrap();
    assert_eq!(zlsb(&a), 3);

    *a = zsets("-1").unwrap();
    assert_eq!(zlsb(&a), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zlsb(&a), 0);


    /* znot */
    *a = zsets("1").unwrap();
    *c = zsets("0").unwrap();
    znot(&mut b, &a);
    let a_clone = a.clone(); znot(&mut a, &a_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    *a = zsets("1").unwrap();
    *c = zsets("0").unwrap();
    znot(&mut b, &a);
    let a_clone = a.clone(); znot(&mut a, &a_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    *a = zsets("0").unwrap();
    *c = zsets("0").unwrap();
    znot(&mut b, &a);
    let a_clone = a.clone(); znot(&mut a, &a_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    *a = zsets("3").unwrap();
    *c = zsets("0").unwrap();
    znot(&mut b, &a);
    let a_clone = a.clone(); znot(&mut a, &a_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);

    *a = zsets("0").unwrap();
    *c = zsets("0").unwrap();
    znot(&mut b, &a);
    let a_clone = a.clone(); znot(&mut a, &a_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &c), 0);


    /* zbtest */
    *a = zsets("1").unwrap();
    assert_eq!(zbtest(&a, 4), 0);

    *a = zsets("1").unwrap();
    assert_eq!(zbtest(&a, 1), 0);

    *a = zsets("2").unwrap();
    assert_eq!(zbtest(&a, 5), 0);

    *a = zsets("-1").unwrap();
    assert_eq!(zbtest(&a, 6), 0);

    *a = zsets("-4").unwrap();
    assert_eq!(zbtest(&a, 0), 0);


    /* zbset */
    *a = zsets("2").unwrap();
    zset(&mut d, &a);
    zbset(&mut b, &a, 2, 1);
    assert_eq!(zstr(&b), "6");
    zbset(&mut b, &a, 2, 0);
    assert_eq!(zstr(&b), "2");
    zbset(&mut b, &a, 2, -1);
    assert_eq!(zstr(&b), "6");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 2, 1);
    assert_eq!(zstr(&a), "6");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 2, 0);
    assert_eq!(zstr(&a), "2");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 2, -1);
    assert_eq!(zstr(&a), "6");

    *a = zsets("-2").unwrap();
    zset(&mut d, &a);
    zbset(&mut b, &a, 5, 1);
    assert_eq!(zstr(&b), "-34");
    zbset(&mut b, &a, 5, 0);
    assert_eq!(zstr(&b), "-2");
    zbset(&mut b, &a, 5, -1);
    assert_eq!(zstr(&b), "-34");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 5, 1);
    assert_eq!(zstr(&a), "-34");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 5, 0);
    assert_eq!(zstr(&a), "-2");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 5, -1);
    assert_eq!(zstr(&a), "-34");

    *a = zsets("0").unwrap();
    zset(&mut d, &a);
    zbset(&mut b, &a, 6, 1);
    assert_eq!(zstr(&b), "64");
    zbset(&mut b, &a, 6, 0);
    assert_eq!(zstr(&b), "0");
    zbset(&mut b, &a, 6, -1);
    assert_eq!(zstr(&b), "64");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 6, 1);
    assert_eq!(zstr(&a), "64");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 6, 0);
    assert_eq!(zstr(&a), "0");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 6, -1);
    assert_eq!(zstr(&a), "64");

    *a = zsets("-1").unwrap();
    zset(&mut d, &a);
    zbset(&mut b, &a, 3, 1);
    assert_eq!(zstr(&b), "-9");
    zbset(&mut b, &a, 3, 0);
    assert_eq!(zstr(&b), "-1");
    zbset(&mut b, &a, 3, -1);
    assert_eq!(zstr(&b), "-9");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 3, 1);
    assert_eq!(zstr(&a), "-9");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 3, 0);
    assert_eq!(zstr(&a), "-1");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 3, -1);
    assert_eq!(zstr(&a), "-9");

    *a = zsets("-1").unwrap();
    zset(&mut d, &a);
    zbset(&mut b, &a, 0, 1);
    assert_eq!(zstr(&b), "-1");
    zbset(&mut b, &a, 0, 0);
    assert_eq!(zstr(&b), "0");
    zbset(&mut b, &a, 0, -1);
    assert_eq!(zstr(&b), "0");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 0, 1);
    assert_eq!(zstr(&a), "-1");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 0, 0);
    assert_eq!(zstr(&a), "0");
    zset(&mut a, &d);
    let a_clone = a.clone(); zbset(&mut a, &a_clone, 0, -1);
    assert_eq!(zstr(&a), "0");


    /* zadd_unsigned */
    *a = zsets("1").unwrap();
    *b = zsets("-6").unwrap();
    zadd_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "7");
    assert_eq!(zstr(&d), "7");
    assert_eq!(zstr(&a), "7");
    zadd_unsigned(&mut c, &b, &b);
    let b_clone = b.clone(); zadd_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zstr(&c), "12");
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("6").unwrap();
    *b = zsets("-3").unwrap();
    zadd_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "9");
    assert_eq!(zstr(&d), "9");
    assert_eq!(zstr(&a), "9");
    zadd_unsigned(&mut c, &b, &b);
    let b_clone = b.clone(); zadd_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zstr(&c), "6");
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("-4").unwrap();
    *b = zsets("2").unwrap();
    zadd_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "6");
    assert_eq!(zstr(&d), "6");
    assert_eq!(zstr(&a), "6");
    zadd_unsigned(&mut c, &b, &b);
    let b_clone = b.clone(); zadd_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zstr(&c), "4");
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("-3").unwrap();
    *b = zsets("1").unwrap();
    zadd_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "4");
    assert_eq!(zstr(&d), "4");
    assert_eq!(zstr(&a), "4");
    zadd_unsigned(&mut c, &b, &b);
    let b_clone = b.clone(); zadd_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zstr(&c), "2");
    assert_eq!(zcmp(&b, &c), 0);

    *a = zsets("1").unwrap();
    *b = zsets("-2").unwrap();
    zadd_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "3");
    assert_eq!(zstr(&d), "3");
    assert_eq!(zstr(&a), "3");
    zadd_unsigned(&mut c, &b, &b);
    let b_clone = b.clone(); zadd_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zstr(&c), "4");
    assert_eq!(zcmp(&b, &c), 0);


    /* zsub_unsigned */
    *a = zsets("-6").unwrap();
    *b = zsets("0").unwrap();
    zsub_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "6");
    assert_eq!(zstr(&d), "6");
    assert_eq!(zstr(&a), "6");
    zsub_unsigned(&mut a, &b, &b);
    assert_eq!(zzero(&a), 1);
    let b_clone = b.clone(); zsub_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zzero(&b), 1);

    *a = zsets("-5").unwrap();
    *b = zsets("6").unwrap();
    zsub_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");
    zsub_unsigned(&mut a, &b, &b);
    assert_eq!(zzero(&a), 1);
    let b_clone = b.clone(); zsub_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zzero(&b), 1);

    *a = zsets("0").unwrap();
    *b = zsets("-1").unwrap();
    zsub_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");
    zsub_unsigned(&mut a, &b, &b);
    assert_eq!(zzero(&a), 1);
    let b_clone = b.clone(); zsub_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zzero(&b), 1);

    *a = zsets("-3").unwrap();
    *b = zsets("-2").unwrap();
    zsub_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");
    zsub_unsigned(&mut a, &b, &b);
    assert_eq!(zzero(&a), 1);
    let b_clone = b.clone(); zsub_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zzero(&b), 1);

    *a = zsets("-1").unwrap();
    *b = zsets("-2").unwrap();
    zsub_unsigned(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub_unsigned(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub_unsigned(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");
    zsub_unsigned(&mut a, &b, &b);
    assert_eq!(zzero(&a), 1);
    let b_clone = b.clone(); zsub_unsigned(&mut b, &b_clone, &b_clone);
    assert_eq!(zzero(&b), 1);


    /* zadd */
    *a = zsets("1").unwrap();
    *b = zsets("0").unwrap();
    zadd(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");

    *a = zsets("0").unwrap();
    *b = zsets("-4").unwrap();
    zadd(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-4");
    assert_eq!(zstr(&d), "-4");
    assert_eq!(zstr(&a), "-4");

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zadd(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    assert_eq!(zstr(&a), "0");

    *a = zsets("-2").unwrap();
    *b = zsets("0").unwrap();
    zadd(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-2");
    assert_eq!(zstr(&d), "-2");
    assert_eq!(zstr(&a), "-2");

    *a = zsets("0").unwrap();
    *b = zsets("1").unwrap();
    zadd(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zadd(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zadd(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");


    /* zsub */
    *a = zsets("-1").unwrap();
    *b = zsets("0").unwrap();
    zsub(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "-1");
    assert_eq!(zstr(&a), "-1");

    *a = zsets("2").unwrap();
    *b = zsets("0").unwrap();
    zsub(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "2");
    assert_eq!(zstr(&d), "2");
    assert_eq!(zstr(&a), "2");

    *a = zsets("-8").unwrap();
    *b = zsets("0").unwrap();
    zsub(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-8");
    assert_eq!(zstr(&d), "-8");
    assert_eq!(zstr(&a), "-8");

    *a = zsets("1").unwrap();
    *b = zsets("0").unwrap();
    zsub(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "1");
    assert_eq!(zstr(&a), "1");

    *a = zsets("1").unwrap();
    *b = zsets("3").unwrap();
    zsub(&mut c, &a, &b);
    zset(&mut d, &b);
    let d_clone = d.clone(); zsub(&mut d, &a, &d_clone);
    let a_clone = a.clone(); zsub(&mut a, &a_clone, &b);
    assert_eq!(zstr(&c), "-2");
    assert_eq!(zstr(&d), "-2");
    assert_eq!(zstr(&a), "-2");


    /* zmul */
    *a = zsets("8").unwrap();
    *b = zsets("-1").unwrap();
    *d = zsets("-8").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zmul(&mut c, &b, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("8").unwrap();
    let b_clone = b.clone(); zmul(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    *d = zsets("64").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    *d = zsets("-1").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zmul(&mut c, &b, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zmul(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    *d = zsets("1").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    *d = zsets("0").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zmul(&mut c, &b, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("0").unwrap();
    let b_clone = b.clone(); zmul(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    *d = zsets("0").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("4").unwrap();
    *b = zsets("-1").unwrap();
    *d = zsets("-4").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zmul(&mut c, &b, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("4").unwrap();
    let b_clone = b.clone(); zmul(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    *d = zsets("16").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("1").unwrap();
    *b = zsets("4").unwrap();
    *d = zsets("4").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zmul(&mut c, &b, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zmul(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    *d = zsets("1").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zmul(&mut a, &a_clone, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);


    /* zsqr */
    *a = zsets("0").unwrap();
    *d = zsets("0").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zsqr(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("1").unwrap();
    *d = zsets("1").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zsqr(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("0").unwrap();
    *d = zsets("0").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zsqr(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("1").unwrap();
    *d = zsets("1").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zsqr(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("1").unwrap();
    *d = zsets("1").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let a_clone = a.clone(); zsqr(&mut a, &a_clone);
    assert_eq!(zcmp(&a, &d), 0);


    /* zdivmod */
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");

    *a = zsets("1").unwrap();
    *b = zsets("4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "1");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "1");
    *a = zsets("4").unwrap();
    *b = zsets("4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("4").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("4").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "1");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "1");
    *a = zsets("4").unwrap();
    *b = zsets("-4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("4").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("4").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "1");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "1");
    *a = zsets("-4").unwrap();
    *b = zsets("4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-4").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-4").unwrap();
    *b = zsets("4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "1");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "1");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "1");
    *a = zsets("-4").unwrap();
    *b = zsets("-4").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-4").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-4").unwrap();
    *b = zsets("-4").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-4").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");

    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");

    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "0");
    *a = zsets("0").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "0");
    *a = zsets("3").unwrap();
    *b = zsets("3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("3").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("3").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "0");
    *a = zsets("0").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "0");
    *a = zsets("3").unwrap();
    *b = zsets("-3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("3").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("3").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("0").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "0");
    *a = zsets("0").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-3").unwrap();
    *b = zsets("3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-3").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-3").unwrap();
    *b = zsets("3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("0").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "0");
    assert_eq!(zstr(&d), "0");
    *a = zsets("0").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "0");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-3").unwrap();
    *b = zsets("-3").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-3").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-3").unwrap();
    *b = zsets("-3").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-3").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");

    *a = zsets("7").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "7");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("7").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("7").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "7");
    assert_eq!(zstr(&d), "0");
    *a = zsets("7").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "7");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("7").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-7");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("7").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("7").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-7");
    assert_eq!(zstr(&d), "0");
    *a = zsets("7").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-7");
    assert_eq!(zstr(&b), "0");
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-7").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-7");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-7").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-7").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-7");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-7").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-7");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "-1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "-1");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-7").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "7");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-7").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-7").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "7");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-7").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "7");
    assert_eq!(zstr(&b), "0");
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    zdivmod(&mut c, &mut d, &a, &b);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut a, &mut b, &a_clone, &b_clone);
    assert_eq!(zcmp(&a, &c), 0);
    assert_eq!(zcmp(&b, &d), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); let b_clone = b.clone(); zdivmod(&mut b, &mut a, &a_clone, &b_clone);
    assert_eq!(zcmp(&b, &c), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut b, &mut a, &b_clone, &b_clone);
    assert_eq!(zcmpu(&b, 1), 0);
    assert_eq!(zcmpu(&a, 0), 0);
    *b = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut a, &mut b, &b_clone, &b_clone);
    assert_eq!(zcmpu(&a, 1), 0);
    assert_eq!(zcmpu(&b, 0), 0);
    *a = zsets("-1").unwrap();
    *b = zsets("-1").unwrap();
    let a_clone = a.clone(); zdivmod(&mut a, &mut d, &a_clone, &b);
    assert_eq!(zstr(&a), "1");
    assert_eq!(zstr(&d), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdivmod(&mut c, &mut b, &a, &b_clone);
    assert_eq!(zstr(&c), "1");
    assert_eq!(zstr(&b), "0");


    /* zdiv */
    *a = zsets("-1").unwrap();
    *b = zsets("-2").unwrap();
    *d = zsets("0").unwrap();
    zdiv(&mut c, &a, &b);
    let a_clone = a.clone(); zdiv(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdiv(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("3").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("3").unwrap();
    zdiv(&mut c, &a, &b);
    let a_clone = a.clone(); zdiv(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("3").unwrap();
    let b_clone = b.clone(); zdiv(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("-1").unwrap();
    zdiv(&mut c, &a, &b);
    let a_clone = a.clone(); zdiv(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zdiv(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("2").unwrap();
    *b = zsets("-1").unwrap();
    *d = zsets("-2").unwrap();
    zdiv(&mut c, &a, &b);
    let a_clone = a.clone(); zdiv(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zdiv(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("2").unwrap();
    *b = zsets("-2").unwrap();
    *d = zsets("-1").unwrap();
    zdiv(&mut c, &a, &b);
    let a_clone = a.clone(); zdiv(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zdiv(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);


    /* zmod */
    *a = zsets("1").unwrap();
    *b = zsets("7").unwrap();
    *d = zsets("1").unwrap();
    zmod(&mut c, &a, &b);
    let a_clone = a.clone(); zmod(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zmod(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("0").unwrap();
    zmod(&mut c, &a, &b);
    let a_clone = a.clone(); zmod(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmod(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("3").unwrap();
    *b = zsets("4").unwrap();
    *d = zsets("3").unwrap();
    zmod(&mut c, &a, &b);
    let a_clone = a.clone(); zmod(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("3").unwrap();
    let b_clone = b.clone(); zmod(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-7").unwrap();
    *b = zsets("-4").unwrap();
    *d = zsets("3").unwrap();
    zmod(&mut c, &a, &b);
    let a_clone = a.clone(); zmod(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-7").unwrap();
    let b_clone = b.clone(); zmod(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-1").unwrap();
    *b = zsets("-2").unwrap();
    *d = zsets("1").unwrap();
    zmod(&mut c, &a, &b);
    let a_clone = a.clone(); zmod(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmod(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);


    /* zmodmul */
    *a = zsets("2").unwrap();
    *b = zsets("0").unwrap();
    *c = zsets("4").unwrap();
    zmodmul(&mut d, &a, &b, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &b, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("4").unwrap();
    zmodmul(&mut d, &b, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &b, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("4").unwrap();
    zmodmul(&mut d, &a, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *d = zsets("0").unwrap();
    zmodmul(&mut c, &a, &b, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &a);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    zmodmul(&mut c, &b, &a, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &a);
    assert_eq!(zstr(&b), "0");
    zmodmul(&mut b, &a, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-1").unwrap();
    *b = zsets("0").unwrap();
    *c = zsets("-1").unwrap();
    zmodmul(&mut d, &a, &b, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &b, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("-1").unwrap();
    zmodmul(&mut d, &b, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &b, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("-1").unwrap();
    zmodmul(&mut d, &a, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-1").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *d = zsets("0").unwrap();
    zmodmul(&mut c, &a, &b, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &a);
    assert_eq!(zstr(&b), "0");
    *b = zsets("0").unwrap();
    zmodmul(&mut c, &b, &a, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &a);
    assert_eq!(zstr(&b), "0");
    zmodmul(&mut b, &a, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-2").unwrap();
    *b = zsets("-1").unwrap();
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &a, &b, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("-1").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &b, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &b, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("-1").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &b, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &a, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *d = zsets("0").unwrap();
    zmodmul(&mut c, &a, &b, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &a);
    assert_eq!(zstr(&b), "0");
    *b = zsets("-1").unwrap();
    zmodmul(&mut c, &b, &a, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &a);
    assert_eq!(zstr(&b), "0");
    zmodmul(&mut b, &a, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("2").unwrap();
    *b = zsets("-1").unwrap();
    *c = zsets("-4").unwrap();
    zmodmul(&mut d, &a, &b, &c);
    assert_eq!(zstr(&d), "2");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&a), "2");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &c);
    assert_eq!(zstr(&b), "2");
    *b = zsets("-1").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &b, &c_clone);
    assert_eq!(zstr(&c), "2");
    *c = zsets("-4").unwrap();
    zmodmul(&mut d, &b, &a, &c);
    assert_eq!(zstr(&d), "2");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &c);
    assert_eq!(zstr(&a), "2");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &c);
    assert_eq!(zstr(&b), "2");
    *b = zsets("-1").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &b, &a, &c_clone);
    assert_eq!(zstr(&c), "2");
    *c = zsets("-4").unwrap();
    zmodmul(&mut d, &a, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *d = zsets("0").unwrap();
    zmodmul(&mut c, &a, &b, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &a);
    assert_eq!(zstr(&b), "0");
    *b = zsets("-1").unwrap();
    zmodmul(&mut c, &b, &a, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &a);
    assert_eq!(zstr(&b), "0");
    zmodmul(&mut b, &a, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-2").unwrap();
    *b = zsets("8").unwrap();
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &a, &b, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("8").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &b, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &b, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &c);
    assert_eq!(zstr(&b), "0");
    *b = zsets("8").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &b, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *c = zsets("1").unwrap();
    zmodmul(&mut d, &a, &a, &c);
    assert_eq!(zstr(&d), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &c);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let c_clone = c.clone(); zmodmul(&mut c, &a, &a, &c_clone);
    assert_eq!(zstr(&c), "0");
    *d = zsets("0").unwrap();
    zmodmul(&mut c, &a, &b, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &b, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &a, &b_clone, &a);
    assert_eq!(zstr(&b), "0");
    *b = zsets("8").unwrap();
    zmodmul(&mut c, &b, &a, &a);
    assert_eq!(zstr(&c), "0");
    let a_clone = a.clone(); zmodmul(&mut a, &b, &a_clone, &a_clone);
    assert_eq!(zstr(&a), "0");
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodmul(&mut b, &b_clone, &a, &a);
    assert_eq!(zstr(&b), "0");
    zmodmul(&mut b, &a, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodmul(&mut a, &a_clone, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);


    /* zmodsqr */
    *a = zsets("0").unwrap();
    *b = zsets("-2").unwrap();
    *d = zsets("0").unwrap();
    zmodsqr(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zset(&mut c, &a);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    zset(&mut a, &c);
    zset(&mut c, &b);
    let b_clone = b.clone(); zmodsqr(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("0").unwrap();
    zmodsqr(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zset(&mut c, &a);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    zset(&mut a, &c);
    zset(&mut c, &b);
    let b_clone = b.clone(); zmodsqr(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    zmodsqr(&mut b, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-4").unwrap();
    *b = zsets("5").unwrap();
    *d = zsets("1").unwrap();
    zmodsqr(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zset(&mut c, &a);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    zset(&mut a, &c);
    zset(&mut c, &b);
    let b_clone = b.clone(); zmodsqr(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    zmodsqr(&mut b, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("-5").unwrap();
    *b = zsets("-1").unwrap();
    *d = zsets("0").unwrap();
    zmodsqr(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zset(&mut c, &a);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    zset(&mut a, &c);
    zset(&mut c, &b);
    let b_clone = b.clone(); zmodsqr(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    zmodsqr(&mut b, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);

    *a = zsets("1").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("0").unwrap();
    zmodsqr(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zset(&mut c, &a);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&a, &d), 0);
    zset(&mut a, &c);
    zset(&mut c, &b);
    let b_clone = b.clone(); zmodsqr(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);
    zmodsqr(&mut b, &a, &a);
    assert_eq!(zzero(&b), 1);
    let a_clone = a.clone(); zmodsqr(&mut a, &a_clone, &a_clone);
    assert_eq!(zzero(&a), 1);


    /* zsave_zload */
    *a = zsets("1").unwrap();
    n = zsave(&a, None);
    buf.resize(n, 0);
    assert_eq!(zsave(&a, Some(&mut buf)), n);
    assert_eq!(zload(&mut b, &buf), n);
    assert_eq!(zcmp(&a, &b), 0);

    *a = zsets("-1").unwrap();
    n = zsave(&a, None);
    buf.resize(n, 0);
    assert_eq!(zsave(&a, Some(&mut buf)), n);
    assert_eq!(zload(&mut b, &buf), n);
    assert_eq!(zcmp(&a, &b), 0);

    *a = zsets("-2").unwrap();
    n = zsave(&a, None);
    buf.resize(n, 0);
    assert_eq!(zsave(&a, Some(&mut buf)), n);
    assert_eq!(zload(&mut b, &buf), n);
    assert_eq!(zcmp(&a, &b), 0);

    *a = zsets("-3").unwrap();
    n = zsave(&a, None);
    buf.resize(n, 0);
    assert_eq!(zsave(&a, Some(&mut buf)), n);
    assert_eq!(zload(&mut b, &buf), n);
    assert_eq!(zcmp(&a, &b), 0);

    *a = zsets("-1").unwrap();
    n = zsave(&a, None);
    buf.resize(n, 0);
    assert_eq!(zsave(&a, Some(&mut buf)), n);
    assert_eq!(zload(&mut b, &buf), n);
    assert_eq!(zcmp(&a, &b), 0);


    /* zgcd */
    *a = zsets("0").unwrap();
    *b = zsets("-2").unwrap();
    *d = zsets("-2").unwrap();
    zgcd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-4").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("1").unwrap();
    zgcd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-4").unwrap();
    *b = zsets("2").unwrap();
    *d = zsets("2").unwrap();
    zgcd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-5").unwrap();
    *b = zsets("0").unwrap();
    *d = zsets("-5").unwrap();
    zgcd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-1").unwrap();
    *b = zsets("1").unwrap();
    *d = zsets("1").unwrap();
    zgcd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);


    /* zpow */
    *a = zsets("-3").unwrap();
    zsetu(&mut b, 4);
    *d = zsets("81").unwrap();
    zpow(&mut c, &a, &b);
    let a_clone = a.clone(); zpow(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-3").unwrap();
    let b_clone = b.clone(); zpow(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-2").unwrap();
    zsetu(&mut b, 10);
    *d = zsets("1024").unwrap();
    zpow(&mut c, &a, &b);
    let a_clone = a.clone(); zpow(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zpow(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-3").unwrap();
    zsetu(&mut b, 7);
    *d = zsets("-2187").unwrap();
    zpow(&mut c, &a, &b);
    let a_clone = a.clone(); zpow(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-3").unwrap();
    let b_clone = b.clone(); zpow(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("1").unwrap();
    zsetu(&mut b, 11);
    *d = zsets("1").unwrap();
    zpow(&mut c, &a, &b);
    let a_clone = a.clone(); zpow(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zpow(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);

    *a = zsets("-3").unwrap();
    zsetu(&mut b, 1);
    *d = zsets("-3").unwrap();
    zpow(&mut c, &a, &b);
    let a_clone = a.clone(); zpow(&mut a, &a_clone, &b);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-3").unwrap();
    let b_clone = b.clone(); zpow(&mut b, &a, &b_clone);
    assert_eq!(zcmp(&b, &d), 0);


    /* zpowu */
    *a = zsets("-1").unwrap();
    *d = zsets("1").unwrap();
    zpowu(&mut c, &a, 8);
    let a_clone = a.clone(); zpowu(&mut a, &a_clone, 8);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("-1").unwrap();
    *d = zsets("1").unwrap();
    zpowu(&mut c, &a, 14);
    let a_clone = a.clone(); zpowu(&mut a, &a_clone, 14);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("2").unwrap();
    *d = zsets("65536").unwrap();
    zpowu(&mut c, &a, 16);
    let a_clone = a.clone(); zpowu(&mut a, &a_clone, 16);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("6").unwrap();
    *d = zsets("78364164096").unwrap();
    zpowu(&mut c, &a, 14);
    let a_clone = a.clone(); zpowu(&mut a, &a_clone, 14);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);

    *a = zsets("0").unwrap();
    *d = zsets("0").unwrap();
    zpowu(&mut c, &a, 6);
    let a_clone = a.clone(); zpowu(&mut a, &a_clone, 6);
    assert_eq!(zcmp(&c, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);


    /* zmodpow */
    *a = zsets("-1").unwrap();
    *b = zsets("13").unwrap();
    *c = zsets("1").unwrap();
    *d = zsets("0").unwrap();
    zmodpow(&mut d, &a, &b, &c);
    let a_clone = a.clone(); zmodpow(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&d), "0");
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-1").unwrap();
    let b_clone = b.clone(); zmodpow(&mut b, &a, &b_clone, &c);
    assert_eq!(zcmp(&b, &d), 0);
    *b = zsets("13").unwrap();
    let c_clone = c.clone(); zmodpow(&mut c, &a, &b, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("4").unwrap();
    *b = zsets("1").unwrap();
    *c = zsets("1").unwrap();
    *d = zsets("0").unwrap();
    zmodpow(&mut d, &a, &b, &c);
    let a_clone = a.clone(); zmodpow(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&d), "0");
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("4").unwrap();
    let b_clone = b.clone(); zmodpow(&mut b, &a, &b_clone, &c);
    assert_eq!(zcmp(&b, &d), 0);
    *b = zsets("1").unwrap();
    let c_clone = c.clone(); zmodpow(&mut c, &a, &b, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-4").unwrap();
    *b = zsets("6").unwrap();
    *c = zsets("-2").unwrap();
    *d = zsets("0").unwrap();
    zmodpow(&mut d, &a, &b, &c);
    let a_clone = a.clone(); zmodpow(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&d), "0");
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-4").unwrap();
    let b_clone = b.clone(); zmodpow(&mut b, &a, &b_clone, &c);
    assert_eq!(zcmp(&b, &d), 0);
    *b = zsets("6").unwrap();
    let c_clone = c.clone(); zmodpow(&mut c, &a, &b, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("1").unwrap();
    *b = zsets("15").unwrap();
    *c = zsets("-2").unwrap();
    *d = zsets("1").unwrap();
    zmodpow(&mut d, &a, &b, &c);
    let a_clone = a.clone(); zmodpow(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&d), "1");
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("1").unwrap();
    let b_clone = b.clone(); zmodpow(&mut b, &a, &b_clone, &c);
    assert_eq!(zcmp(&b, &d), 0);
    *b = zsets("15").unwrap();
    let c_clone = c.clone(); zmodpow(&mut c, &a, &b, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-2").unwrap();
    *b = zsets("4").unwrap();
    *c = zsets("-1").unwrap();
    *d = zsets("0").unwrap();
    zmodpow(&mut d, &a, &b, &c);
    let a_clone = a.clone(); zmodpow(&mut a, &a_clone, &b, &c);
    assert_eq!(zstr(&d), "0");
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-2").unwrap();
    let b_clone = b.clone(); zmodpow(&mut b, &a, &b_clone, &c);
    assert_eq!(zcmp(&b, &d), 0);
    *b = zsets("4").unwrap();
    let c_clone = c.clone(); zmodpow(&mut c, &a, &b, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);


    /* zmodpowu */
    *a = zsets("3").unwrap();
    *c = zsets("4").unwrap();
    *d = zsets("1").unwrap();
    zmodpowu(&mut b, &a, 16, &c);
    let a_clone = a.clone(); zmodpowu(&mut a, &a_clone, 16, &c);
    assert_eq!(zcmp(&b, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("3").unwrap();
    let c_clone = c.clone(); zmodpowu(&mut c, &a, 16, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("2").unwrap();
    *c = zsets("-7").unwrap();
    *d = zsets("2").unwrap();
    zmodpowu(&mut b, &a, 16, &c);
    let a_clone = a.clone(); zmodpowu(&mut a, &a_clone, 16, &c);
    assert_eq!(zcmp(&b, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("2").unwrap();
    let c_clone = c.clone(); zmodpowu(&mut c, &a, 16, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("0").unwrap();
    *c = zsets("-1").unwrap();
    *d = zsets("0").unwrap();
    zmodpowu(&mut b, &a, 5, &c);
    let a_clone = a.clone(); zmodpowu(&mut a, &a_clone, 5, &c);
    assert_eq!(zcmp(&b, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("0").unwrap();
    let c_clone = c.clone(); zmodpowu(&mut c, &a, 5, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("-3").unwrap();
    *c = zsets("-1").unwrap();
    *d = zsets("0").unwrap();
    zmodpowu(&mut b, &a, 5, &c);
    let a_clone = a.clone(); zmodpowu(&mut a, &a_clone, 5, &c);
    assert_eq!(zcmp(&b, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("-3").unwrap();
    let c_clone = c.clone(); zmodpowu(&mut c, &a, 5, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);

    *a = zsets("0").unwrap();
    *c = zsets("-1").unwrap();
    *d = zsets("0").unwrap();
    zmodpowu(&mut b, &a, 10, &c);
    let a_clone = a.clone(); zmodpowu(&mut a, &a_clone, 10, &c);
    assert_eq!(zcmp(&b, &d), 0);
    assert_eq!(zcmp(&a, &d), 0);
    *a = zsets("0").unwrap();
    let c_clone = c.clone(); zmodpowu(&mut c, &a, 10, &c_clone);
    assert_eq!(zcmp(&c, &d), 0);


    /* zstr_length */
    *a = zsets("-2").unwrap();
    assert_eq!(zstr_length(&a, 10).unwrap(), 2);

    *a = zsets("0").unwrap();
    assert_eq!(zstr_length(&a, 10).unwrap(), 1);

    *a = zsets("1").unwrap();
    assert_eq!(zstr_length(&a, 10).unwrap(), 1);

    *a = zsets("1").unwrap();
    assert_eq!(zstr_length(&a, 10).unwrap(), 1);

    *a = zsets("4").unwrap();
    assert_eq!(zstr_length(&a, 10).unwrap(), 1);


    /* zstr */
    *a = zsets("0").unwrap();
    assert_eq!(zstr(&a), "0");

    *a = zsets("3").unwrap();
    assert_eq!(zstr(&a), "3");

    *a = zsets("0").unwrap();
    assert_eq!(zstr(&a), "0");

    *a = zsets("-1").unwrap();
    assert_eq!(zstr(&a), "-1");

    *a = zsets("2").unwrap();
    assert_eq!(zstr(&a), "2");


}

#[test]
fn test_12() {
    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    // Very large number operations
    zsetu(&mut a, 4000000000u64);
    zsetu(&mut b, 4000000000u64);
    zadd(&mut c, &a, &a);
    d = zsets("8000000000").unwrap();
    assert_eq!(zcmp(&c, &d), 0);
    zadd(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    let c_clone = c.clone();
    zadd(&mut c, &c_clone, &a);
    d = zsets("12000000000").unwrap();
    assert_eq!(zcmp(&c, &d), 0);
    let c_clone = c.clone();
    zsub(&mut c, &c_clone, &a);
    d = zsets("8000000000").unwrap();
    assert_eq!(zcmp(&c, &d), 0);
    let c_clone = c.clone();
    zsub(&mut c, &c_clone, &a);
    d = zsets("4000000000").unwrap();
    assert_eq!(zcmp(&c, &d), 0);
    d = zsets("8000000000").unwrap();
    let d_clone = d.clone();
    zrsh(&mut d, &d_clone, 1);
    assert_eq!(zcmp(&c, &d), 0);
    a = zsets("6234216714").unwrap();
    b = zsets("9424614147").unwrap();
    d = zsets("830476546").unwrap();
    zand(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    a = zsets("234216714").unwrap();
    b = zsets("9424614147").unwrap();
    d = zsets("9629466379").unwrap();
    zor(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    a = zsets("6234216714").unwrap();
    b = zsets("9424614147").unwrap();
    d = zsets("13997877769").unwrap();
    zxor(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    a = zsets("34216714").unwrap();
    b = zsets("9424614147").unwrap();
    d = zsets("9458821129").unwrap();
    zxor(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000").unwrap();
    zmul(&mut c, &a, &a);
    assert_eq!(zcmp(&c, &d), 0);
    let c_clone = c.clone();
    zdiv(&mut c, &c_clone, &a);
    assert_eq!(zcmp(&c, &a), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000").unwrap();
    zsqr(&mut c, &a);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    let _ = zmodpowu(&mut c, &a, 5, &_3);
    assert_eq!(zcmpu(&c, 1), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1").unwrap();
    zpowu(&mut c, &a, 0);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000").unwrap();
    zpowu(&mut c, &a, 1);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000").unwrap();
    zpowu(&mut c, &a, 2);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    b = zsets("1000000000000000000").unwrap();
    d = zsets("1000000000000000000000000000").unwrap();
    zmul(&mut c, &a, &b);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000000000000").unwrap();
    zmul(&mut b, &a, &a);
    let b_clone = b.clone();
    zmul(&mut b, &b_clone, &a);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000000000000").unwrap();
    zpowu(&mut c, &a, 3);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000000000000000000000").unwrap();
    zpowu(&mut c, &a, 4);
    assert_eq!(zcmp(&c, &d), 0);
    zsetu(&mut a, 1000000000u64);
    d = zsets("1000000000000000000000000000000000000000000000").unwrap();
    zpowu(&mut c, &a, 5);
    assert_eq!(zcmp(&c, &d), 0);

    // Include test-random.c content - comprehensive function tests
    include_test_random_complete(&mut a, &mut b, &mut c, &mut d);
}

#[test]
fn test_13() {
    let mut a = z_t::from(0);
    let mut b = z_t::from(0);
    let mut c = z_t::from(0);
    let mut d = z_t::from(0);
    let mut _0 = z_t::from(0);
    let mut _1 = z_t::from(0);
    let mut _2 = z_t::from(0);
    let mut _3 = z_t::from(0);
    let mut buf: String;

    zsetu(&mut _0, 0);
    zsetu(&mut _1, 1);
    zsetu(&mut _2, 2);
    zsetu(&mut _3, 3);

    zsetu(&mut a, 4294967294u64);
    buf = zstr(&a);
    assert_eq!(buf, "4294967294");
    zsetu(&mut a, 4294967295u64);
    buf = zstr(&a);
    assert_eq!(buf, "4294967295");
    zsetu(&mut a, 4294967296u64);
    buf = zstr(&a);
    assert_eq!(buf, "4294967296");
    zsetu(&mut a, 4294967297u64);
    buf = zstr(&a);
    assert_eq!(buf, "4294967297");

    zseti(&mut a, 9223372036854775807i64);
    buf = zstr(&a);
    assert_eq!(buf, "9223372036854775807");
    zseti(&mut a, -9223372036854775807i64);
    buf = zstr(&a);
    assert_eq!(buf, "-9223372036854775807");
    zseti(&mut a, -9223372036854775807i64 - 1i64);
    buf = zstr(&a);
    assert_eq!(buf, "-9223372036854775808");

    zsetu(&mut a, 18446744073709551614u64);
    buf = zstr(&a);
    assert_eq!(buf, "18446744073709551614");
    zsetu(&mut a, 18446744073709551615u64);
    buf = zstr(&a);
    assert_eq!(buf, "18446744073709551615");
    let a_clone = a.clone();
    zadd(&mut a, &a_clone, &_1);
    buf = zstr(&a);
    assert_eq!(buf, "18446744073709551616");
    let a_clone = a.clone();
    zadd(&mut a, &a_clone, &_1);
    buf = zstr(&a);
    assert_eq!(buf, "18446744073709551617");

    a = zsets("1000000000000000000000000000000").unwrap();
    buf = zstr(&a);
    assert_eq!(buf, "1000000000000000000000000000000");
    a = zsets("+1000000000000000000000000000000").unwrap();
    buf = zstr(&a);
    assert_eq!(buf, "1000000000000000000000000000000");
    a = zsets("-1000000000000000000000000000000").unwrap();
    buf = zstr(&a);
    assert_eq!(buf, "-1000000000000000000000000000000");

    zsetu(&mut a, 1000000000000000u64);
    let a_clone = a.clone();
    zsqr(&mut a, &a_clone);
    buf = zstr(&a);
    assert_eq!(buf, "1000000000000000000000000000000");

    // Include test-random.c content - comprehensive function tests
    include_test_random_complete(&mut a, &mut b, &mut c, &mut d);
}


// NOTE: In Rust, the test harness is provided by cargo test.
// Unlike the C version which has a main() function that calls each test sequentially,
// Rust's cargo test framework automatically discovers and runs all functions marked with #[test].
//
// To run all tests (equivalent to C's main() function):
//   cargo test --test test
//
// This will run all 13 test functions (test_1 through test_13) and report results.
// The output shows:
//   - Total number of tests run
//   - Number of tests passed/failed
//   - Individual test results
//
// This is functionally equivalent to the C version's main() which runs:
//   test_1(), test_2(), test_3(), test_4(), test_5(), test_6(), test_7(),
//   test_8(), test_9(), test_10(), test_11(), test_12(), test_13()
