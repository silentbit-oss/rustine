# RUST Overall Translation Design for libzahl-1.0

## Overview

This document describes the high-level design for translating libzahl-1.0 from C to Rust. The translation aims for a 1:1 functional mapping while adapting to idiomatic Rust patterns for error handling, memory management, and type safety.

**Translation Approach:** Direct functional translation with Rust idioms
- Preserve all libzahl functionality
- Maintain API compatibility where possible
- Replace C patterns with Rust equivalents
- Leverage Rust's type system and ownership model

## Translation Requirements

**Core Requirements:**
1. Complete 1:1 translation of all libzahl functions
2. Preserve exact directory structure and file names (change .c to .rs)
3. Maintain all identifier names (functions, types, constants)
4. Replace longjmp error handling with Result<T, E>
5. Use num-bigint as core BigInt implementation
6. Implement all arithmetic, bitwise, and number theory operations
7. Support string conversion and serialization
8. Provide random number generation
9. Include comprehensive test suite

**Non-Requirements:**
- Thread-safety (matches libzahl's single-threaded design)
- Cryptographic hardening (libzahl explicitly not for crypto)
- Performance optimization beyond Rust best practices

## C Source Files to Translate

**Public header:** `zahl.h` → `src/lib.rs` (module exports)

**Internal header:** `src/internals.h` → `src/internals.rs` (internal utilities)

**Implementation files** (51 files in src/ directory):
- allocator.c → allocator.rs
- zabs.c → zabs.rs
- zadd.c → zadd.rs
- zand.c → zand.rs
- zbits.c → zbits.rs
- zbset.c → zbset.rs
- zbtest.c → zbtest.rs
- zcmp.c → zcmp.rs
- zcmpi.c → zcmpi.rs
- zcmpmag.c → zcmpmag.rs
- zcmpu.c → zcmpu.rs
- zdiv.c → zdiv.rs
- zdivmod.c → zdivmod.rs
- zerror.c → zerror.rs
- zfree.c → zfree.rs
- zgcd.c → zgcd.rs
- zload.c → zload.rs
- zlsb.c → zlsb.rs
- zlsh.c → zlsh.rs
- zmod.c → zmod.rs
- zmodmul.c → zmodmul.rs
- zmodpow.c → zmodpow.rs
- zmodpowu.c → zmodpowu.rs
- zmodsqr.c → zmodsqr.rs
- zmul.c → zmul.rs
- zneg.c → zneg.rs
- znot.c → znot.rs
- zor.c → zor.rs
- zperror.c → zperror.rs
- zpow.c → zpow.rs
- zpowu.c → zpowu.rs
- zptest.c → zptest.rs
- zrand.c → zrand.rs
- zrsh.c → zrsh.rs
- zsave.c → zsave.rs
- zset.c → zset.rs
- zseti.c → zseti.rs
- zsets.c → zsets.rs
- zsetu.c → zsetu.rs
- zsetup.c → zsetup.rs (may be eliminated)
- zsplit.c → zsplit.rs
- zsqr.c → zsqr.rs
- zstr.c → zstr.rs
- zstr_length.c → zstr_length.rs
- zsub.c → zsub.rs
- zswap.c → zswap.rs
- ztrunc.c → ztrunc.rs
- zunsetup.c → zunsetup.rs (may be eliminated)
- zxor.c → zxor.rs

**Test file:** `test.c` → `tests/test.rs`

**Build system:** `Makefile` → `Cargo.toml`

## RUST Module Structure

### Directory Layout (Preserving C Structure)

```
rust/
├── Cargo.toml          (replaces Makefile)
├── LICENSE             (same as C)
├── README.md           (adapted from C README)
├── src/
│   ├── lib.rs          (main library entry, replaces zahl.h)
│   ├── internals.rs    (internal utilities, replaces internals.h)
│   ├── allocator.rs    (memory management - may be simplified)
│   ├── zabs.rs
│   ├── zadd.rs
│   ├── zand.rs
│   ├── zbits.rs
│   ├── zbset.rs
│   ├── zbtest.rs
│   ├── zcmp.rs
│   ├── zcmpi.rs
│   ├── zcmpmag.rs
│   ├── zcmpu.rs
│   ├── zdiv.rs
│   ├── zdivmod.rs
│   ├── zerror.rs       (error type definitions)
│   ├── zfree.rs        (may be eliminated - RAII handles cleanup)
│   ├── zgcd.rs
│   ├── zload.rs
│   ├── zlsb.rs
│   ├── zlsh.rs
│   ├── zmod.rs
│   ├── zmodmul.rs
│   ├── zmodpow.rs
│   ├── zmodpowu.rs
│   ├── zmodsqr.rs
│   ├── zmul.rs
│   ├── zneg.rs
│   ├── znot.rs
│   ├── zor.rs
│   ├── zperror.rs
│   ├── zpow.rs
│   ├── zpowu.rs
│   ├── zptest.rs
│   ├── zrand.rs
│   ├── zrsh.rs
│   ├── zsave.rs
│   ├── zset.rs
│   ├── zseti.rs
│   ├── zsets.rs
│   ├── zsetu.rs
│   ├── zsetup.rs       (may be eliminated - no setup needed)
│   ├── zsplit.rs
│   ├── zsqr.rs
│   ├── zstr.rs
│   ├── zstr_length.rs
│   ├── zsub.rs
│   ├── zswap.rs
│   ├── ztrunc.rs
│   ├── zunsetup.rs     (may be eliminated - RAII handles cleanup)
│   └── zxor.rs
├── tests/
│   └── test.rs         (port of test.c)
└── man/                (documentation - optional)
```

**CRITICAL:** File and directory names MUST remain identical to C version (only extension changes from .c to .rs).

### Module Organization in lib.rs

```rust
// src/lib.rs

// Error types
mod zerror;
pub use zerror::{ZahlError, Result};

// Core type (re-export from num-bigint)
pub use num_bigint::BigInt as z_t;

// Enumerations
pub use zptest::Primality;
pub use zrand::{RandDevice, RandDist};

// Internal utilities (private)
mod internals;

// Function modules (each in separate file)
mod allocator;  // May be simplified or eliminated
mod zabs;
mod zadd;
mod zand;
// ... (all other modules)

// Public API exports
pub use zabs::zabs;
pub use zadd::zadd;
pub use zand::zand;
// ... (all other public functions)

// Constants (replacing C constants)
pub mod constants {
    use super::z_t;
    use once_cell::sync::Lazy;

    pub static CONST_0: Lazy<z_t> = Lazy::new(|| z_t::from(0));
    pub static CONST_1: Lazy<z_t> = Lazy::new(|| z_t::from(1));
    pub static CONST_2: Lazy<z_t> = Lazy::new(|| z_t::from(2));
    pub static CONST_4: Lazy<z_t> = Lazy::new(|| z_t::from(4));
    pub static CONST_1E9: Lazy<z_t> = Lazy::new(|| z_t::from(1_000_000_000u64));
    pub static CONST_1E19: Lazy<z_t> = Lazy::new(|| z_t::from(10_000_000_000_000_000_000u64));
}
```

## RUST Structs & Traits

### Core Type: z_t

**C definition:**
```c
typedef struct {
    int sign;           // -1, 0, 1
    size_t used;
    size_t alloced;
    zahl_char_t *chars;
} z_t[1];
```

**Rust translation:**
```rust
// Use num-bigint's BigInt directly
pub use num_bigint::BigInt as z_t;
```

**Rationale:**
- `BigInt` provides equivalent functionality
- Handles sign, magnitude, and dynamic allocation internally
- No need for manual memory management
- All arithmetic operations already implemented

### Enumerations

**Primality (zprimality in C):**
```rust
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Primality {
    Nonprime = 0,
    ProbablyPrime = 1,
    Prime = 2,
}
```

**Random Device (zranddev in C):**
```rust
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RandDevice {
    FastRandom = 0,    // ThreadRng (fast PRNG)
    SecureRandom = 1,  // OsRng (cryptographically secure)
}
```

**Random Distribution (zranddist in C):**
```rust
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RandDist {
    Quasiuniform = 0,  // Faster, approximately uniform
    Uniform = 1,       // Slower, exactly uniform (rejection sampling)
}
```

### Helper Traits (Optional)

**For ergonomic conversions:**
```rust
pub trait ToZT {
    fn to_zt(&self) -> z_t;
}

impl ToZT for i64 {
    fn to_zt(&self) -> z_t {
        z_t::from(*self)
    }
}

impl ToZT for u64 {
    fn to_zt(&self) -> z_t {
        z_t::from(*self)
    }
}
```

## RUST Error Handling

### Error Type Definition

**Using thiserror crate:**
```rust
// src/zerror.rs

use thiserror::Error;

#[derive(Error, Debug)]
pub enum ZahlError {
    #[error("Division by zero")]
    DivisionByZero,

    #[error("Invalid domain: {0}")]
    InvalidDomain(String),

    #[error("Memory allocation failed")]
    AllocationFailed,

    #[error("Invalid exponent for operation: {0}")]
    InvalidExponent(String),

    #[error("I/O error: {0}")]
    Io(#[from] std::io::Error),

    #[error("Parse error: {0}")]
    ParseError(String),

    #[error("Invalid radix: {0}")]
    InvalidRadix(u32),

    #[error("Overflow in operation")]
    Overflow,

    #[error("Underflow in operation")]
    Underflow,
}

pub type Result<T> = std::result::Result<T, ZahlError>;
```

### Error Handling Pattern

**Replaces C's longjmp pattern:**

**C pattern:**
```c
jmp_buf env;
if (setjmp(env)) {
    zperror(0);
    return -1;
}
zsetup(env);
zadd(result, a, b);  // May longjmp on error
```

**Rust pattern:**
```rust
fn calculation() -> Result<z_t> {
    let result = zadd(&a, &b)?;  // Propagate error
    let result2 = zmul(&result, &c)?;
    Ok(result2)
}

match calculation() {
    Ok(value) => println!("Result: {}", value),
    Err(e) => eprintln!("Error: {}", e),
}
```

### No Setup/Teardown Required

**C requires:**
- `zsetup(env)` before use
- `zunsetup()` for cleanup

**Rust eliminates:**
- No setup function needed
- RAII handles all cleanup automatically
- Drop trait cleans up BigInt allocations

## RUST 3rd Party Libraries

### Core Dependencies

**Cargo.toml:**
```toml
[package]
name = "zahl"
version = "1.0.0"
edition = "2021"
rust-version = "1.60"

[dependencies]
# Arbitrary-precision integers
num-bigint = { version = "0.4", features = ["rand"] }
num-traits = "0.2"
num-integer = "0.1"

# Random number generation
rand = "0.8"

# Error handling
thiserror = "1.0"

# Lazy static initialization
once_cell = "1.19"

[dev-dependencies]
# For testing
rand = "0.8"
```

### Library Purposes

1. **num-bigint (0.4+)**
   - Primary BigInt implementation
   - Replaces libzahl's z_t type
   - Handles arithmetic operations
   - Enable `rand` feature for random number generation

2. **num-traits (0.2+)**
   - Generic numeric traits (Zero, One, etc.)
   - Shared abstractions across numeric types
   - Used by num-bigint

3. **num-integer (0.1+)**
   - Integer-specific operations
   - GCD, LCM functions
   - Division variants (floor, ceil, modulo)
   - Even/odd checks

4. **rand (0.8+)**
   - Random number generation
   - ThreadRng for FAST_RANDOM
   - OsRng for SECURE_RANDOM
   - Integration with num-bigint via `rand` feature

5. **thiserror (1.0+)**
   - Ergonomic error type definitions
   - Automatic Error trait implementation
   - Better error messages

6. **once_cell (1.19+)**
   - Lazy static initialization
   - For constant BigInt values
   - Thread-safe, efficient initialization

## RUST Translated Libraries

### Memory Management Translation

**C approach:**
- Manual memory management with `malloc`/`free`
- Memory pooling for performance
- Power-of-2 allocation sizes
- Global pool arrays

**Rust approach:**
- Let BigInt handle allocations internally
- Trust Rust's allocator efficiency
- No manual pooling needed
- RAII ensures proper cleanup

**allocator.rs:**
```rust
// Most allocator functionality eliminated
// BigInt handles memory management internally
// Keep only if specific optimizations needed
```

### Arithmetic Operations Translation

**Pattern for binary operations:**
```rust
// src/zadd.rs

use crate::{z_t, Result};

pub fn zadd(b: &z_t, c: &z_t) -> z_t {
    b + c
}
```

**Pattern for operations that can fail:**
```rust
// src/zdiv.rs

use crate::{z_t, Result, ZahlError};
use num_traits::Zero;

pub fn zdiv(b: &z_t, c: &z_t) -> Result<z_t> {
    if c.is_zero() {
        return Err(ZahlError::DivisionByZero);
    }
    Ok(b / c)
}
```

### Comparison Operations Translation

**Pattern:**
```rust
// src/zcmp.rs

use crate::z_t;
use std::cmp::Ordering;

pub fn zcmp(a: &z_t, b: &z_t) -> i32 {
    match a.cmp(b) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}
```

### Bitwise Operations Translation

**Pattern:**
```rust
// src/zand.rs

use crate::z_t;

pub fn zand(b: &z_t, c: &z_t) -> z_t {
    b & c
}
```

### String Conversion Translation

**Pattern:**
```rust
// src/zstr.rs

use crate::{z_t, Result};

pub fn zstr(a: &z_t) -> String {
    a.to_string()  // Decimal representation
}

// src/zsets.rs

use crate::{z_t, Result, ZahlError};
use std::str::FromStr;

pub fn zsets(s: &str) -> Result<z_t> {
    z_t::from_str(s)
        .map_err(|e| ZahlError::ParseError(format!("{}", e)))
}
```

### Random Number Generation Translation

**Pattern:**
```rust
// src/zrand.rs

use crate::{z_t, Result, ZahlError, RandDevice, RandDist};
use num_bigint::{BigInt, RandBigInt};
use rand::{thread_rng, rngs::OsRng};
use num_traits::Zero;

pub fn zrand(dev: RandDevice, dist: RandDist, n: &z_t) -> Result<z_t> {
    if n.is_zero() {
        return Ok(z_t::zero());
    }

    match dev {
        RandDevice::FastRandom => {
            let mut rng = thread_rng();
            generate_random(&mut rng, dist, n)
        }
        RandDevice::SecureRandom => {
            let mut rng = OsRng;
            generate_random(&mut rng, dist, n)
        }
    }
}

fn generate_random<R: rand::Rng>(
    rng: &mut R,
    dist: RandDist,
    n: &z_t,
) -> Result<z_t> {
    let bits = n.bits() as u64;

    match dist {
        RandDist::Quasiuniform => {
            // Faster: generate random bits, scale to range
            let r = rng.gen_biguint(bits);
            let result = (BigInt::from(r) + 1) * n >> bits;
            Ok(result)
        }
        RandDist::Uniform => {
            // Exact: rejection sampling
            loop {
                let r = rng.gen_bigint(bits);
                if &r.abs() <= n {
                    return Ok(r);
                }
            }
        }
    }
}
```

### GCD Translation

**Using num-integer:**
```rust
// src/zgcd.rs

use crate::z_t;
use num_integer::Integer;

pub fn zgcd(b: &z_t, c: &z_t) -> z_t {
    b.gcd(c)
}
```

### Primality Testing Translation

**Miller-Rabin implementation:**
```rust
// src/zptest.rs

use crate::{z_t, Result, Primality};
use num_bigint::BigInt;
use num_traits::{Zero, One};
use rand::{thread_rng, Rng};

pub fn zptest(
    witness: Option<&mut z_t>,
    n: &z_t,
    iterations: i32,
) -> Result<Primality> {
    // Small cases
    if n <= &BigInt::from(1) {
        if let Some(w) = witness {
            *w = n.clone();
        }
        return Ok(Primality::Nonprime);
    }

    if n <= &BigInt::from(3) {
        return Ok(Primality::Prime);
    }

    if n.is_even() {
        if let Some(w) = witness {
            *w = n.clone();
        }
        return Ok(Primality::Nonprime);
    }

    // Miller-Rabin test
    // ... (full implementation following C version)

    Ok(Primality::ProbablyPrime)
}
```

## Translation Strategy Summary

### 1. Type Mapping
- `z_t[1]` → `BigInt`
- `size_t` → `usize`
- `int` → `i32`
- `char *` → `&str` or `String`
- Enums preserve exact names and values

### 2. Function Signatures
- **C:** `void zfunc(z_t out, z_t in1, z_t in2)`
- **Rust:** `fn zfunc(in1: &z_t, in2: &z_t) -> z_t`
- Return values instead of output parameters
- Use references for borrowing

### 3. Error Handling
- Replace `longjmp` with `Result<T, E>`
- Use `?` operator for error propagation
- Define custom error type with thiserror

### 4. Memory Management
- Eliminate manual allocation (BigInt handles it)
- Remove zfree, zsetup, zunsetup
- RAII handles all cleanup

### 5. Constants
- Use `once_cell::Lazy` for lazy initialization
- Define module for shared constants

### 6. Testing
- Port all test cases from test.c
- Use Rust's built-in test framework
- Add property-based tests with quickcheck

## Implementation Order

1. **Phase 1: Foundation**
   - Error types (zerror.rs)
   - Core type aliases (lib.rs)
   - Constants (internals.rs)

2. **Phase 2: Basic Operations**
   - Assignment (zset, zseti, zsetu)
   - Comparison (zcmp, zcmpi, zcmpu, zcmpmag)
   - Simple properties (zinit, zeven, zodd, zzero, zsignum)

3. **Phase 3: Arithmetic**
   - Addition/subtraction (zadd, zsub)
   - Multiplication/division (zmul, zdiv, zmod, zdivmod)
   - Unary operations (zneg, zabs, zsqr)
   - Power operations (zpow, zpowu, zmodpow, zmodpowu, zmodsqr, zmodmul)

4. **Phase 4: Bitwise**
   - Logic operations (zand, zor, zxor, znot)
   - Shift operations (zlsh, zrsh)
   - Bit manipulation (zbits, zlsb, zbtest, zbset, ztrunc, zsplit)

5. **Phase 5: Number Theory**
   - GCD (zgcd)
   - Primality testing (zptest)

6. **Phase 6: I/O**
   - String conversion (zstr, zsets, zstr_length)
   - Serialization (zsave, zload)
   - Memory operations (zswap)

7. **Phase 7: Random**
   - Random generation (zrand)

8. **Phase 8: Testing**
   - Port all test cases
   - Add additional Rust-specific tests

## Key Design Decisions

### Decision 1: Use BigInt Directly
**Rationale:** No need for custom wrapper. BigInt provides all required functionality with better performance and safety guarantees.

### Decision 2: Result<T, E> for Errors
**Rationale:** Idiomatic Rust error handling. Type-safe, composable, no global state.

### Decision 3: Eliminate Setup/Teardown
**Rationale:** RAII handles lifecycle. No manual initialization needed.

### Decision 4: Keep Same Function Names
**Rationale:** Maintains API familiarity for users migrating from C version.

### Decision 5: Remove Memory Pooling
**Rationale:** Modern allocators are efficient. Premature optimization. Let BigInt handle it.

### Decision 6: Preserve File Structure
**Rationale:** Maintains organizational clarity. One function per file matches C structure.

## Conclusion

This design provides a complete roadmap for translating libzahl from C to Rust while leveraging Rust's type system, error handling, and memory safety guarantees. The translation preserves all functionality while adapting to idiomatic Rust patterns.
