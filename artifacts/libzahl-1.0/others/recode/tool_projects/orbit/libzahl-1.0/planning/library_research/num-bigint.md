# Rust Library Research: num-bigint

## Overview

**Crate:** `num-bigint`
**Purpose:** Arbitrary-precision integer arithmetic for Rust
**License:** MIT or Apache-2.0
**Minimum Rust Version:** 1.60+
**Documentation:** https://docs.rs/num-bigint/

The num-bigint crate provides "Big Integer Types for Rust" enabling work with unlimited-size integers. This is essential for cryptography, number theory, and mathematical computations beyond fixed-size integer limits.

## Main Types

### BigUint
- Represents **unsigned** arbitrary-precision integers
- Internal representation: vector of digits
- Zero allocation overhead for values that fit in inline storage
- Provides `BigUint::ZERO` constant

### BigInt
- Represents **signed** arbitrary-precision integers
- Internally: `BigUint` magnitude + `Sign` enum
- Supports negative values
- More feature-complete than BigUint for general arithmetic

### Sign Enum
```rust
pub enum Sign {
    Minus,
    NoSign,  // Zero
    Plus,
}
```

## Common Operations

### Arithmetic Operations
All standard operators work through operator overloading:
- Addition: `+`, `+=`
- Subtraction: `-`, `-=`
- Multiplication: `*`, `*=`
- Division: `/`, `/=`
- Modulo: `%`, `%=`
- Bitwise: `&`, `|`, `^`, `<<`, `>>`
- Negation: unary `-`

**Example:**
```rust
use num_bigint::BigUint;
use num_traits::One;

fn fib(n: usize) -> BigUint {
    let mut f0 = BigUint::ZERO;
    let mut f1 = BigUint::one();
    for _ in 0..n {
        let f2 = f0 + &f1;  // Note: borrowing to avoid moves
        f0 = f1;
        f1 = f2;
    }
    f0
}
```

### Comparison Operations
- All standard comparison operators: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Ordering semantics match mathematical expectations

### Conversion Methods
- **ToBigInt trait:** Convert to signed BigInt
- **ToBigUint trait:** Convert to unsigned BigUint
- **From<T> implementations:** For primitive integer types
- **TryFrom<T>:** For fallible conversions
- **to_string():** Decimal string representation
- **from_str():** Parse from decimal string

### Digit Access
- **U32Digits:** Iterator over 32-bit digits (little-endian)
- **U64Digits:** Iterator over 64-bit digits (little-endian)

## Memory Management

**Heap allocation:** Always uses the `alloc` crate for heap-allocated digit vectors
- Memory grows dynamically with number magnitude
- No stack-only option
- Requires careful consideration in resource-constrained environments

**Optimization strategies:**
- Use references (`&`) in operations to avoid unnecessary clones
- Consider `std::mem::swap()` for efficient value exchange
- Reuse allocations where possible by mutating in place

## Performance Characteristics

**Algorithmic complexity:**
- Addition/Subtraction: O(n) where n = number of digits
- Multiplication: O(n²) for small numbers, Karatsuba for large
- Division: O(n²)
- Comparison: O(n)

**Performance considerations:**
- Vector-based storage benefits from CPU cache locality
- Rust's zero-cost abstractions minimize overhead
- No garbage collection pauses
- Inherent overhead of arbitrary-precision vs. native integers

**Benchmarking recommended** for performance-critical code.

## Recommended Usage Patterns

### 1. Random Number Generation
Requires `rand` feature:
```rust
use num_bigint::{BigInt, RandBigInt};
use rand::thread_rng;

let mut rng = thread_rng();
let a = rng.gen_bigint(1000);  // Random 1000-bit BigInt
let b = rng.gen_biguint(1000); // Random 1000-bit BigUint
```

### 2. Serialization
Requires `serde` feature for cross-platform data exchange:
```rust
use num_bigint::BigInt;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
struct Data {
    value: BigInt,
}
```

### 3. Borrowing to Avoid Clones
```rust
let a = BigInt::from(100);
let b = BigInt::from(200);

// Good: borrows to avoid unnecessary clones
let sum = &a + &b;

// Less efficient: would clone 'a'
let sum = a + &b;
```

### 4. String Conversion
```rust
use num_bigint::BigInt;
use std::str::FromStr;

// Parse from string
let a = BigInt::from_str("123456789012345678901234567890")?;

// Convert to string (decimal)
let s = a.to_string();
```

### 5. Testing Support
Requires `arbitrary` and/or `quickcheck` features:
- Property-based testing
- Fuzzing support
- Useful for validating arithmetic implementations

## Trade-offs

**Advantages:**
- Mature, well-tested library
- Rich operator overloading feels native
- Good performance for Rust ecosystem
- Extensive trait implementations (Debug, Display, Hash, etc.)
- Optional features for serialization, random generation

**Disadvantages:**
- Always heap-allocated (no small-value optimization)
- Not optimized for cryptographic constant-time operations
- Limited to decimal string conversion (no binary, hex, octal built-in)
- No built-in primality testing or GCD (requires num-integer)

## Integration Recommendations for libzahl Translation

1. **Use BigInt as primary type** (matches libzahl's signed integers)
2. **Leverage operator overloading** for natural syntax
3. **Use num-traits** crate for generic numeric operations
4. **Enable rand feature** for random number generation
5. **Consider num-integer** crate for GCD and extended operations
6. **Implement custom error types** instead of libzahl's longjmp pattern
7. **Use Result<T, E>** for error handling (idiomatic Rust)

## Additional Dependencies Likely Needed

- **num-traits**: Generic numeric trait abstractions (Zero, One, etc.)
- **num-integer**: Integer-specific operations (GCD, LCM, etc.)
- **rand**: Random number generation
- **thiserror** or **anyhow**: Ergonomic error handling
