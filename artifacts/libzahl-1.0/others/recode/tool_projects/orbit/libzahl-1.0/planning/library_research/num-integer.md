# Rust Library Research: num-integer

## Overview

**Crate:** `num-integer`
**Purpose:** Integer-specific traits and number-theoretic functions
**License:** MIT or Apache-2.0
**Minimum Rust Version:** 1.31+
**Documentation:** https://docs.rs/num-integer/

The num-integer crate provides mathematical operations and traits specifically designed for integer types, complementing num-bigint with essential number theory functions.

## Key Traits

### Integer Trait

**Core trait for integer operations:**
- Extends `Num` trait with integer-specific operations
- Implemented for all standard integer types and BigInt
- Provides division variants (floor, ceil, modulo)

**Key methods:**
```rust
pub trait Integer: Sized + Num + PartialOrd + Ord {
    fn div_floor(&self, other: &Self) -> Self;
    fn mod_floor(&self, other: &Self) -> Self;
    fn gcd(&self, other: &Self) -> Self;
    fn lcm(&self, other: &Self) -> Self;
    fn divides(&self, other: &Self) -> bool;
    fn is_multiple_of(&self, other: &Self) -> bool;
    fn is_even(&self) -> bool;
    fn is_odd(&self) -> bool;
    fn div_rem(&self, other: &Self) -> (Self, Self);
    fn div_mod_floor(&self, other: &Self) -> (Self, Self);
    // ... more methods
}
```

### Average Trait

**Compute averages without overflow:**
```rust
pub trait Average: Integer {
    fn average_floor(&self, other: &Self) -> Self;
    fn average_ceil(&self, other: &Self) -> Self;
}
```

Uses clever algorithm to avoid overflow in intermediate calculations.

### Roots Trait

**Integer root calculations:**
```rust
pub trait Roots: Integer {
    fn sqrt(&self) -> Self;      // Square root (truncated)
    fn cbrt(&self) -> Self;      // Cube root (truncated)
    fn nth_root(&self, n: u32) -> Self;  // Nth root (truncated)
}
```

Returns truncated principal (floor) of the root.

## Essential Functions

### Greatest Common Divisor (GCD)

```rust
use num_integer::gcd;
use num_bigint::BigInt;

let a = BigInt::from(2 * 3 * 3 * 7);  // 126
let b = BigInt::from(3 * 7 * 11);      // 231
let result = gcd(a, b);
assert_eq!(result, BigInt::from(21));  // 3 * 7
```

**Properties:**
- Always returns non-negative result
- `gcd(0, 0) = 0`
- `gcd(a, 0) = |a|`
- Commutative: `gcd(a, b) = gcd(b, a)`

### Lowest Common Multiple (LCM)

```rust
use num_integer::lcm;
use num_bigint::BigInt;

let a = BigInt::from(12);
let b = BigInt::from(18);
let result = lcm(a, b);
assert_eq!(result, BigInt::from(36));
```

### Combined GCD and LCM

**More efficient than computing separately:**
```rust
use num_integer::gcd_lcm;
use num_bigint::BigInt;

let a = BigInt::from(12);
let b = BigInt::from(18);
let (g, l) = gcd_lcm(a, b);
assert_eq!(g, BigInt::from(6));
assert_eq!(l, BigInt::from(36));
```

### Extended GCD

**Computes GCD with Bézout coefficients:**
```rust
use num_integer::ExtendedGcd;
use num_bigint::BigInt;

let a = BigInt::from(240);
let b = BigInt::from(46);
let ExtendedGcd { gcd, x, y } = a.extended_gcd(&b);

// Verifies: a*x + b*y = gcd
assert_eq!(gcd, BigInt::from(2));
assert_eq!(&a * &x + &b * &y, gcd);
```

**Use cases:**
- Modular multiplicative inverse
- Solving linear Diophantine equations
- Cryptographic operations

## Division Variants

### Floor Division

```rust
use num_integer::div_floor;

// Standard division rounds toward zero
assert_eq!(7 / 3, 2);
assert_eq!(-7 / 3, -2);

// Floor division rounds toward negative infinity
assert_eq!(div_floor(7, 3), 2);
assert_eq!(div_floor(-7, 3), -3);  // Note: -3, not -2
```

### Ceiling Division

```rust
use num_integer::div_ceil;

assert_eq!(div_ceil(7, 3), 3);   // Rounds up
assert_eq!(div_ceil(6, 3), 2);   // Exact division
assert_eq!(div_ceil(-7, 3), -2); // Toward positive infinity
```

### Modulo (Floor)

```rust
use num_integer::mod_floor;

// Standard mod follows truncation
assert_eq!(7 % 3, 1);
assert_eq!(-7 % 3, -1);

// Floor mod always non-negative (for positive divisor)
assert_eq!(mod_floor(7, 3), 1);
assert_eq!(mod_floor(-7, 3), 2);  // Note: 2, not -1
```

### Combined Division and Remainder

```rust
use num_integer::Integer;
use num_bigint::BigInt;

let a = BigInt::from(17);
let b = BigInt::from(5);

// div_rem (truncated)
let (quot, rem) = a.div_rem(&b);
assert_eq!(quot, BigInt::from(3));
assert_eq!(rem, BigInt::from(2));

// div_mod_floor (floored)
let (quot, rem) = a.div_mod_floor(&b);
assert_eq!(quot, BigInt::from(3));
assert_eq!(rem, BigInt::from(2));
```

## Root Operations

### Square Root

```rust
use num_integer::Roots;
use num_bigint::BigInt;

let n = BigInt::from(100);
assert_eq!(n.sqrt(), BigInt::from(10));

let n = BigInt::from(101);
assert_eq!(n.sqrt(), BigInt::from(10));  // Truncated
```

### Nth Root

```rust
use num_integer::Roots;
use num_bigint::BigInt;

let n = BigInt::from(1000);
assert_eq!(n.cbrt(), BigInt::from(10));   // Cube root

let n = BigInt::from(1024);
assert_eq!(n.nth_root(10), BigInt::from(2));  // 10th root
```

## Combinatorial Functions

### Binomial Coefficients

```rust
use num_integer::binomial;
use num_bigint::BigUint;

// Compute C(n, k) = n! / (k! * (n-k)!)
let result = binomial(BigUint::from(10u32), 3);
assert_eq!(result, BigUint::from(120u32));
```

### Binomial Iterator

```rust
use num_integer::IterBinomial;

// Iterate over binomial coefficients
let iter = IterBinomial::new(5);
let coefficients: Vec<_> = iter.collect();
// [1, 5, 10, 10, 5, 1] - Pascal's triangle row 5
```

### Multinomial Coefficients

```rust
use num_integer::multinomial;
use num_bigint::BigUint;

// For distributing n items into k groups
let n = BigUint::from(10u32);
let groups = vec![3, 3, 4];
let result = multinomial(&groups);
```

## Usage Patterns for libzahl Translation

### Pattern 1: GCD Implementation

**libzahl's zgcd:**
```c
void zgcd(z_t a, z_t b, z_t c);
```

**Rust translation:**
```rust
use num_bigint::BigInt;
use num_integer::Integer;

pub fn zgcd(b: &BigInt, c: &BigInt) -> BigInt {
    b.gcd(c)
}
```

**Even simpler with function:**
```rust
use num_integer::gcd;

pub fn zgcd(b: &BigInt, c: &BigInt) -> BigInt {
    gcd(b.clone(), c.clone())
}
```

### Pattern 2: Division with Remainder

**libzahl's zdivmod:**
```c
void zdivmod(z_t a, z_t b, z_t c, z_t d);  // a = c/d, b = c%d
```

**Rust translation:**
```rust
use num_bigint::BigInt;
use num_integer::Integer;

pub fn zdivmod(c: &BigInt, d: &BigInt) -> Result<(BigInt, BigInt)> {
    if d == &BigInt::ZERO {
        return Err(ZahlError::DivisionByZero);
    }
    Ok(c.div_rem(d))
}
```

### Pattern 3: Integer Properties

**libzahl's inline functions:**
```c
static inline int zeven(z_t a) { return !a->sign || !(a->chars[0] & 1); }
static inline int zodd(z_t a) { return a->sign && (a->chars[0] & 1); }
```

**Rust translation:**
```rust
use num_integer::Integer;

pub fn zeven(a: &BigInt) -> bool {
    a.is_even()
}

pub fn zodd(a: &BigInt) -> bool {
    a.is_odd()
}
```

## Integration with num-bigint

**Seamless integration:**
```rust
use num_bigint::BigInt;
use num_integer::Integer;

let a = BigInt::from(126);
let b = BigInt::from(231);

// Integer trait methods work directly on BigInt
let gcd = a.gcd(&b);
let lcm = a.lcm(&b);
let (quot, rem) = a.div_rem(&b);
let is_even = a.is_even();
```

## Performance Considerations

**GCD algorithms:**
- Uses efficient binary GCD (similar to libzahl)
- Optimized for different integer sizes
- No unnecessary allocations

**Root calculations:**
- Newton's method for approximation
- Binary search refinement
- Efficient for large integers

**Division operations:**
- Leverage underlying BigInt division
- Minimal overhead for variant operations

## Trade-offs

**Advantages:**
- Comprehensive number theory operations
- Well-tested implementations
- Idiomatic Rust APIs
- Works seamlessly with num-bigint
- Zero-cost abstractions

**Disadvantages:**
- Additional dependency
- Some operations not needed for basic libzahl port
- Documentation could be more detailed

## Recommended Usage for libzahl Translation

1. **Use for GCD operations** - direct replacement for zgcd
2. **Use Integer trait** - for even/odd checks, divisibility
3. **Use div_rem** - for combined division and modulo
4. **Consider extended_gcd** - if future functionality needed
5. **Leverage root operations** - if adding sqrt/cbrt functions
6. **Avoid binomial functions** - not in libzahl scope

## Dependencies

Works best with:
- `num-bigint`: Primary integer type
- `num-traits`: Shared trait definitions
- `num-iter`: For iteration support

## Summary

The num-integer crate provides essential number-theoretic operations that perfectly complement num-bigint for translating libzahl. The GCD, LCM, and division operations map directly to libzahl's functionality with cleaner, more type-safe APIs.
