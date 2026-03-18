# Rust Library Research: rand

## Overview

**Crate:** `rand`
**Version:** 0.10.1+
**Purpose:** Comprehensive random number generation utilities for Rust
**License:** MIT or Apache-2.0
**Repository:** github.com/rust-random/rand
**Documentation:** https://docs.rs/rand/

The rand crate is the foundational Rust library for random number generation, providing utilities to generate random numbers, convert them to useful types and distributions, and implement randomness-related algorithms.

## Core Traits and Types

### Primary Traits

**Rng Trait:**
- Primary interface for infallible random number generators
- Core methods for generating random values
- Most commonly used trait

**TryRng:**
- Base trait for RNGs that may fail
- Useful for hardware RNGs or external sources
- Returns Result<T, Error>

**SeedableRng:**
- Enables explicit seeding of generators
- Deterministic behavior from seed
- Essential for reproducible testing

**CryptoRng & TryCryptoRng:**
- Marker traits indicating cryptographically secure RNGs
- No methods, just type-level guarantees
- Critical for security-sensitive applications

### Key Generator Types

**ThreadRng:**
- Thread-local random number generator
- Automatically seeded
- Fast and convenient for most uses
- Accessed via `thread_rng()` or `rng()`

**OsRng:**
- Operating system random number generator
- Cryptographically secure
- Uses `/dev/urandom` on Unix-like systems
- Slower but higher quality entropy

**StdRng:**
- Standard PRNG (Pseudo-Random Number Generator)
- Balance of speed and quality
- Seedable for reproducibility

## Random Number Generation Patterns

### Convenience Functions (Prelude)

```rust
use rand::prelude::*;

// Access thread-local generator
let mut rng = rng();

// Generate random value of any type
let x: u32 = random();
let y: f64 = random();

// Generate value in range
let n = random_range(0..100);

// Generate boolean with probability
let coin_flip = random_bool(0.5);
```

### Direct RNG Usage

```rust
use rand::{thread_rng, Rng};

let mut rng = thread_rng();

// Generate random values
let x: u8 = rng.gen();
let y = rng.gen_range(0..100);
let z = rng.gen_bool(0.7);

// Fill array with random bytes
let mut bytes = [0u8; 32];
rng.fill(&mut bytes);
```

### Sequence Operations

```rust
use rand::prelude::*;

let mut items = vec![1, 2, 3, 4, 5];

// Shuffle in place
items.shuffle(&mut thread_rng());

// Choose random element
let choice = items.choose(&mut thread_rng());

// Choose multiple elements
let choices: Vec<_> = items.choose_multiple(&mut thread_rng(), 3).collect();
```

## Cryptographically Secure RNG (OsRng)

**For security-sensitive applications:**

```rust
use rand::rngs::OsRng;
use rand::RngCore;

let mut rng = OsRng;

// Generate cryptographically secure random bytes
let mut key = [0u8; 32];
rng.fill_bytes(&mut key);

// Use with distributions
use rand::distributions::Uniform;
let range = Uniform::new(0, 100);
let secure_random = range.sample(&mut rng);
```

**Characteristics:**
- Non-deterministic (cannot be seeded)
- Cryptographically secure
- Slower than PRNGs
- Uses OS entropy source
- On Unix: reads from `/dev/urandom`
- On Windows: uses BCryptGenRandom

## Distribution Support

The `distributions` module provides various probability distributions:

### Common Distributions

```rust
use rand::distributions::{Alphanumeric, Standard, Uniform};
use rand::{thread_rng, Rng};

let mut rng = thread_rng();

// Uniform distribution
let uniform = Uniform::new(0, 100);
let value = rng.sample(uniform);

// Alphanumeric characters (example from docs)
let s: String = rng
    .sample_iter(&Alphanumeric)
    .take(10)
    .map(char::from)
    .collect();

// Standard distribution (default for type)
let x: f64 = rng.sample(Standard);
```

### Distribution Types
- **Standard:** Default distribution for a type
- **Uniform:** Evenly distributed values in range
- **Alphanumeric:** Random ASCII alphanumeric characters
- **Bernoulli:** Boolean with specified probability
- **WeightedIndex:** Choose from weighted options

## Integration with num-bigint

**RandBigInt trait** (from num-bigint crate with rand feature):

```rust
use num_bigint::{BigInt, BigUint, RandBigInt};
use rand::thread_rng;

let mut rng = thread_rng();

// Generate random BigInt with specified bit size
let big_random: BigInt = rng.gen_bigint(1024);

// Generate random BigUint
let big_unsigned: BigUint = rng.gen_biguint(1024);

// Generate in specific range
let big_in_range = rng.gen_bigint_range(&lower_bound, &upper_bound);
```

## Recommended Usage Patterns

### Pattern 1: Quick Random Values
```rust
use rand::random;

// Simplest way for one-off random values
let x: u32 = random();
let flag: bool = random();
```

### Pattern 2: Multiple Random Operations
```rust
use rand::{thread_rng, Rng};

let mut rng = thread_rng();
// Reuse the same RNG for efficiency
for _ in 0..100 {
    let value = rng.gen_range(0..10);
    // process value...
}
```

### Pattern 3: Reproducible Random (Testing)
```rust
use rand::{SeedableRng, Rng};
use rand::rngs::StdRng;

// Create RNG with specific seed
let mut rng = StdRng::seed_from_u64(42);

// Now generates same sequence every time
let value1 = rng.gen::<u32>();
let value2 = rng.gen::<u32>();
```

### Pattern 4: Secure Random (Cryptography)
```rust
use rand::rngs::OsRng;
use rand::RngCore;

let mut rng = OsRng;
let mut secure_bytes = [0u8; 32];
rng.fill_bytes(&mut secure_bytes);
```

## Performance Considerations

**ThreadRng:**
- Fast for general-purpose use
- Thread-local, no synchronization overhead
- Good for non-security-critical applications

**OsRng:**
- Slower due to OS syscalls
- Cryptographically secure
- Use only when security matters

**StdRng:**
- Balance of speed and quality
- Deterministic when seeded
- Good for simulations and testing

**Optimization tips:**
- Reuse RNG instances rather than creating new ones
- Use `fill()` for bulk generation
- Consider thread-local for parallel code

## Mapping to libzahl Random Functions

**libzahl's `zrand()` function:**
```c
void zrand(z_t r, enum zranddev dev, enum zranddist dist, z_t n);
```

**Rust equivalents:**

1. **Device selection (FAST_RANDOM vs SECURE_RANDOM):**
   - FAST_RANDOM → `ThreadRng` or `StdRng`
   - SECURE_RANDOM → `OsRng`

2. **Distribution (QUASIUNIFORM vs UNIFORM):**
   - Both can use `Uniform` distribution
   - QUASIUNIFORM optimization may use bit shifting
   - UNIFORM requires rejection sampling for exact uniformity

3. **Implementation approach:**
```rust
use num_bigint::{BigInt, RandBigInt};
use rand::rngs::{ThreadRng, OsRng};
use rand::{thread_rng, Rng};

fn zrand(dev: RandDevice, dist: RandDist, max: &BigInt) -> Result<BigInt> {
    match dev {
        RandDevice::Fast => {
            let mut rng = thread_rng();
            generate_in_range(&mut rng, dist, max)
        }
        RandDevice::Secure => {
            let mut rng = OsRng;
            generate_in_range(&mut rng, dist, max)
        }
    }
}
```

## Dependencies

**Core dependencies:**
- `rand_core` (0.10.0): Fundamental RNG traits
- Optional: `chacha20`, `getrandom`, `serde`

**For bigint integration:**
- `num-bigint` with `rand` feature enabled

## Trade-offs

**Advantages:**
- Comprehensive and mature ecosystem
- Clear separation of concerns (traits, generators, distributions)
- Excellent performance
- Strong cryptographic options
- Good documentation

**Disadvantages:**
- API can be complex for simple use cases
- Multiple crates to understand (rand, rand_core, rand_chacha, etc.)
- Version compatibility can be tricky across ecosystem

## Integration Recommendations for libzahl Translation

1. **Use ThreadRng for FAST_RANDOM** - matches libzahl's `/dev/urandom`
2. **Use OsRng for SECURE_RANDOM** - matches libzahl's `/dev/random`
3. **Enable rand feature in num-bigint** - provides RandBigInt trait
4. **Implement both distribution modes** - UNIFORM and QUASIUNIFORM
5. **Return Result<T, Error>** instead of longjmp
6. **Consider caching RNG instances** for performance
7. **Use type system to enforce security** - CryptoRng marker trait
