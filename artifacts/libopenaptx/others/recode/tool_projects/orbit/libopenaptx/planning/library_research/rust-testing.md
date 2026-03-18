# Rust Testing Framework Research

## Overview

The C project includes test files (test.c and tests/*.c) with custom test macros. Rust has a built-in testing framework that is more ergonomic and feature-rich.

## Test Structure

### C Approach
```c
// test_common.h
#define ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "❌ ASSERT FAILED: %s\n", msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define PASS(msg) printf("✅ %s passed\n", msg)

// test.c
void test_aptx_encode_decode() {
    // setup
    assert_true(result == expected, "test_name");
    PASS("test_name");
}

int main() {
    test_aptx_encode_decode();
    return 0;
}
```

### Rust Approach

**Recommendation: Use built-in test framework with `#[test]` attribute**

```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_aptx_encode_decode() {
        // Setup
        let ctx = aptx_init(false);

        // Test logic
        let result = encode_something(&ctx);

        // Assertions
        assert_eq!(result, expected);
        assert!(result > 0);
        assert_ne!(result, wrong_value);
    }

    #[test]
    #[should_panic]
    fn test_invalid_input_panics() {
        // This test passes if it panics
        process_invalid_data();
    }

    #[test]
    #[ignore]
    fn expensive_test() {
        // Run with: cargo test -- --ignored
    }
}
```

**Running tests:**
```bash
cargo test              # Run all tests
cargo test test_name    # Run specific test
cargo test -- --nocapture  # Show println! output
cargo test -- --test-threads=1  # Run tests serially
```

## Assertion Macros

### Standard Assertions

```rust
assert!(condition);                    // Panics if false
assert!(condition, "message");         // Custom panic message
assert!(condition, "value: {}", val);  // Formatted message

assert_eq!(left, right);               // Panics if not equal
assert_eq!(left, right, "msg");        // With custom message

assert_ne!(left, right);               // Panics if equal

debug_assert!(condition);              // Only in debug builds
debug_assert_eq!(left, right);         // Only in debug builds
```

### Custom Assertions (if needed)

```rust
macro_rules! assert_approx_eq {
    ($left:expr, $right:expr, $epsilon:expr) => {
        let diff = ($left - $right).abs();
        assert!(
            diff < $epsilon,
            "assertion failed: `(left ≈ right)`\n  left: `{:?}`,\n right: `{:?}`,\n  diff: `{:?}`,\n epsilon: `{:?}`",
            $left, $right, diff, $epsilon
        );
    };
}
```

## Test Organization

### C Approach
```
test.c                  # Main test file
tests/test_common.h     # Test macros
tests/test_dither.c     # Individual test suites
tests/test_padding.c
tests/test_roundtrip.c
tests/test_sync.c
```

### Rust Approach

**Option 1: Inline tests (recommended for unit tests)**
```rust
// src/lib.rs or src/openaptx.rs
pub fn encode_samples(...) -> Result<(), Error> {
    // Implementation
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_encode_samples() {
        // Test implementation
    }
}
```

**Option 2: Separate test files (recommended for integration tests)**
```
src/
  lib.rs
  openaptx.rs
tests/
  test_roundtrip.rs
  test_padding.rs
  test_dither.rs
  test_sync.rs
  common/
    mod.rs         # Shared test utilities
```

```rust
// tests/common/mod.rs
pub fn setup_test_context() -> AptxContext {
    // Shared setup code
}

// tests/test_roundtrip.rs
mod common;

#[test]
fn test_roundtrip_classic() {
    let ctx = common::setup_test_context();
    // Test logic
}
```

**Trade-offs:**
- Inline tests: Close to code, good for unit tests
- Separate files: Better organization for integration tests
- **Recommendation**: Both - inline for unit tests, `tests/` for integration tests

## Test Fixtures and Setup

### C Approach
```c
void test_function() {
    struct aptx_context *ctx = aptx_init(0);
    // Test logic
    aptx_finish(ctx);
}
```

### Rust Approach

**Option 1: Manual setup/teardown**
```rust
#[test]
fn test_encode() {
    // Setup
    let mut ctx = aptx_init(false);

    // Test logic
    let result = ctx.encode(&data);
    assert!(result.is_ok());

    // Teardown (automatic via Drop)
}
```

**Option 2: Helper functions**
```rust
fn setup() -> AptxContext {
    aptx_init(false)
}

#[test]
fn test_encode() {
    let mut ctx = setup();
    // Test logic
}
```

**Option 3: Test fixtures (for complex setup)**
```rust
struct TestFixture {
    ctx: AptxContext,
    input: Vec<u8>,
    expected: Vec<u8>,
}

impl TestFixture {
    fn new() -> Self {
        Self {
            ctx: aptx_init(false),
            input: vec![0; 24],
            expected: vec![0; 4],
        }
    }
}

#[test]
fn test_with_fixture() {
    let fixture = TestFixture::new();
    // Use fixture
}
```

## Test Data and Constants

### C Approach
```c
#define NB_SAMPLES 8
const int16_t test_data[16] = {0, 256, 512, ...};
```

### Rust Approach

```rust
#[cfg(test)]
mod tests {
    const NB_SAMPLES: usize = 8;
    const TEST_DATA: [i16; 16] = [0, 256, 512, /* ... */];

    #[test]
    fn test_with_data() {
        for sample in TEST_DATA.iter() {
            // Test each sample
        }
    }
}
```

## Benchmarking

### Built-in Benchmarking (unstable, requires nightly)

```rust
#![feature(test)]
extern crate test;

#[cfg(test)]
mod benches {
    use super::*;
    use test::Bencher;

    #[bench]
    fn bench_encode(b: &mut Bencher) {
        let mut ctx = aptx_init(false);
        let input = [0u8; 24];
        let mut output = [0u8; 4];

        b.iter(|| {
            aptx_encode(&mut ctx, &input, &mut output)
        });
    }
}
```

**Alternative: Criterion crate (stable Rust)**
```rust
// benches/encoding.rs
use criterion::{black_box, criterion_group, criterion_main, Criterion};

fn benchmark_encode(c: &mut Criterion) {
    c.bench_function("encode_frame", |b| {
        let mut ctx = aptx_init(false);
        let input = [0u8; 24];
        let mut output = [0u8; 4];

        b.iter(|| {
            aptx_encode(black_box(&mut ctx), black_box(&input), black_box(&mut output))
        });
    });
}

criterion_group!(benches, benchmark_encode);
criterion_main!(benches);
```

**Trade-offs:**
- Built-in: Simple, requires nightly
- Criterion: More features, works on stable, external dependency
- **Recommendation**: Criterion for this project (stable Rust)

## Property-Based Testing

### Using proptest or quickcheck

```rust
#[cfg(test)]
mod tests {
    use proptest::prelude::*;

    proptest! {
        #[test]
        fn test_encode_decode_roundtrip(samples in prop::collection::vec(any::<i16>(), 4..1024)) {
            let mut ctx_enc = aptx_init(false);
            let mut ctx_dec = aptx_init(false);

            let mut encoded = vec![0u8; samples.len() / 4];
            let mut decoded = vec![0i16; samples.len()];

            // Encode then decode
            aptx_encode(&mut ctx_enc, &samples, &mut encoded);
            aptx_decode(&mut ctx_dec, &encoded, &mut decoded);

            // Check properties (not exact match due to lossy compression)
            prop_assert!(samples.len() == decoded.len());
        }
    }
}
```

**Trade-offs:**
- Finds edge cases automatically
- Slower than unit tests
- Requires external crate
- **Recommendation**: Optional - useful for codec validation

## Test Coverage

### Using tarpaulin or llvm-cov

```bash
# Install tarpaulin
cargo install cargo-tarpaulin

# Run coverage
cargo tarpaulin --out Html --output-dir coverage

# Or using llvm-cov (newer)
cargo install cargo-llvm-cov
cargo llvm-cov --html
```

**Integration with CI:**
```yaml
# .github/workflows/test.yml
- name: Run tests with coverage
  run: cargo llvm-cov --lcov --output-path lcov.info
```

## Documentation Tests

### Rust Feature: Tests in Doc Comments

```rust
/// Encodes 4 stereo samples to aptX format.
///
/// # Example
/// ```
/// use libopenaptx::aptx_init;
///
/// let mut ctx = aptx_init(false);
/// let input = [0u8; 24];
/// let mut output = [0u8; 4];
/// let mut written = 0;
///
/// let processed = aptx_encode(&mut ctx, &input, &mut output, &mut written);
/// assert!(processed <= 24);
/// ```
pub fn aptx_encode(...) { }
```

**Running doc tests:**
```bash
cargo test --doc
```

**Trade-offs:**
- Examples are tested automatically
- Ensures documentation stays up to date
- No equivalent in C
- **Recommendation**: Use for public API documentation

## Translation Mapping

| C Pattern | Rust Equivalent | Notes |
|-----------|----------------|-------|
| `ASSERT(cond, msg)` | `assert!(cond, "msg")` | Built-in macro |
| `assert_true(x, msg)` | `assert!(x, "msg")` | Same as above |
| `PASS("test")` | Test passes silently | Rust prints on failure only |
| `exit(EXIT_FAILURE)` | `panic!("msg")` | In tests, caught by framework |
| Manual test runner | `#[test]` attribute | Automatic discovery |
| `fprintf(stderr)` | `eprintln!()` in test | Or use `assert!` |
| Test count | `cargo test` output | Automatic counting |

## Example: Complete Test Translation

### C Code
```c
// test_roundtrip.c
void test_roundtrip(int hd) {
    struct aptx_context *enc = aptx_init(hd);
    struct aptx_context *dec = aptx_init(hd);

    int16_t pcm_in[16] = {0};
    for (int i = 0; i < 16; ++i)
        pcm_in[i] = i * 256;

    uint8_t encoded[64] = {0};
    size_t written = 0;
    aptx_encode(enc, pcm_in, sizeof(pcm_in), encoded, sizeof(encoded), &written);

    ASSERT(written > 0, "Should encode data");
    PASS("Roundtrip test");

    aptx_finish(enc);
    aptx_finish(dec);
}
```

### Rust Translation
```rust
// tests/test_roundtrip.rs
use libopenaptx::aptx_init;

#[test]
fn test_roundtrip_classic() {
    test_roundtrip(false);
}

#[test]
fn test_roundtrip_hd() {
    test_roundtrip(true);
}

fn test_roundtrip(hd: bool) {
    let mut enc = aptx_init(hd);
    let mut dec = aptx_init(hd);

    let mut pcm_in = [0i16; 16];
    for (i, sample) in pcm_in.iter_mut().enumerate() {
        *sample = (i * 256) as i16;
    }

    let mut encoded = [0u8; 64];
    let mut written = 0;
    aptx_encode(&mut enc, &pcm_in, &mut encoded, &mut written);

    assert!(written > 0, "Should encode data");
    // No PASS macro needed - test passes silently
}
```

## Recommendations for This Project

1. **Use `#[test]` attribute** for all tests
2. **Organize tests in `tests/` directory** for integration tests
3. **Use inline tests** for unit tests in src files
4. **Use `assert!`, `assert_eq!`, `assert_ne!`** instead of custom macros
5. **Create `tests/common/mod.rs`** for shared test utilities
6. **Run tests with `cargo test`** instead of custom test runner
7. **Consider property-based testing** for codec validation (optional)
8. **Use doc tests** for public API examples
9. **Generate coverage reports** with `cargo-llvm-cov` or `tarpaulin`
10. **No need for PASS macro** - Rust shows only failures by default

## Running Tests

```bash
# Run all tests
cargo test

# Run specific test
cargo test test_roundtrip

# Run tests with output
cargo test -- --nocapture

# Run ignored tests
cargo test -- --ignored

# Run tests single-threaded
cargo test -- --test-threads=1

# Run only unit tests
cargo test --lib

# Run only integration tests
cargo test --test test_roundtrip

# Run benchmarks (with criterion)
cargo bench
```
