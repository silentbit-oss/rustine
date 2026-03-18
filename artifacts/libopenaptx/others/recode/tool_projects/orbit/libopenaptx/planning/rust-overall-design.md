# Rust Overall Translation Design

## Overview

This document provides the high-level design for translating the libopenaptx C library to Rust. The translation aims to be a 1:1 mapping that preserves the C project's structure, naming conventions, and behavior while leveraging Rust's safety guarantees and modern language features.

**Translation Goals:**
- Maintain identical API surface and behavior
- Preserve all identifier names (functions, structs, fields, variables)
- Keep the same directory structure and file organization
- Ensure memory safety without garbage collection
- Achieve equivalent or better performance
- Maintain compatibility with existing usage patterns

**Translation Approach:**
- Direct struct-to-struct translation
- Function-by-function conversion
- Preserve integer overflow behavior using wrapping arithmetic
- Use Rust's type system for safety without changing semantics
- Replace manual memory management with RAII (Drop trait)

## Translation Requirements

The translation requirements parameter was empty, indicating a **strict 1:1 translation** with no additional features or modifications beyond language translation.

**Key Constraints:**
1. Preserve exact file and directory names (only `.c` → `.rs` extension change)
2. Preserve all identifier names exactly as-is
3. Maintain identical API function signatures (modulo Rust idioms)
4. Keep the same public interface
5. No feature additions or removals
6. Match C behavior for edge cases (overflow, signed arithmetic, etc.)

## C Source Files to Translate

### Core Library Files
1. **openaptx.h** → **openaptx.rs** (or lib.rs with pub items)
   - Public API declarations
   - Constants and version information
   - Opaque struct forward declaration

2. **openaptx.c** → **openaptx.rs**
   - Main codec implementation (1329 lines)
   - All internal data structures
   - QMF analysis and synthesis
   - Quantization and prediction algorithms
   - Encoding and decoding functions

### Command-Line Utilities
3. **openaptxenc.c** → **openaptxenc.rs**
   - Encoder command-line tool
   - stdin/stdout binary I/O
   - Converts to src/bin/openaptxenc.rs

4. **openaptxdec.c** → **openaptxdec.rs**
   - Decoder command-line tool
   - stdin/stdout binary I/O
   - Converts to src/bin/openaptxdec.rs

### Test Files
5. **test.c** → **test.rs**
   - Basic test suite
   - Converts to tests/test.rs

6. **tests/test_common.h** → **tests/common/mod.rs**
   - Shared test utilities
   - Assert macros → Rust assertions

7. **tests/test_dither.c** → **tests/test_dither.rs**
   - Dither generation tests

8. **tests/test_padding.c** → **tests/test_padding.rs**
   - Encoding padding tests

9. **tests/test_roundtrip.c** → **tests/test_roundtrip.rs**
   - Encode/decode roundtrip tests

10. **tests/test_sync.c** → **tests/test_sync.rs**
    - Synchronization tests

### Non-Translated Files
- **Makefile** → **Cargo.toml** (build system configuration)
- **README** → **README.md** (documentation)
- **COPYING** → **LICENSE** or **COPYING** (license file)
- **compile_commands.json** → Not needed (Cargo handles this)

## RUST Module Structure

The Rust translation will preserve the exact directory structure and file names from the C project, with only the file extensions changed.

### Directory Tree

```
rust/
├── Cargo.toml              (replaces Makefile)
├── README.md               (translates README)
├── COPYING                 (unchanged)
├── src/
│   ├── lib.rs              (main library entry point)
│   ├── openaptx.rs         (translates openaptx.c)
│   └── bin/
│       ├── openaptxenc.rs  (translates openaptxenc.c)
│       └── openaptxdec.rs  (translates openaptxdec.c)
├── tests/
│   ├── common/
│   │   └── mod.rs          (translates tests/test_common.h)
│   ├── test.rs             (translates test.c)
│   ├── test_dither.rs      (translates tests/test_dither.c)
│   ├── test_padding.rs     (translates tests/test_padding.c)
│   ├── test_roundtrip.rs   (translates tests/test_roundtrip.c)
│   └── test_sync.rs        (translates tests/test_sync.c)
└── benches/
    └── encoding.rs         (optional: benchmarking)
```

### File Structure Details

#### src/lib.rs
```rust
//! libopenaptx - Open Source implementation of aptX codec
//!
//! This crate provides encoding and decoding for aptX and aptX HD audio codecs.

pub mod openaptx;

// Re-export public API
pub use openaptx::{
    aptx_context,
    aptx_init,
    aptx_reset,
    aptx_finish,
    aptx_encode,
    aptx_encode_finish,
    aptx_decode,
    aptx_decode_sync,
    aptx_decode_sync_finish,
    aptx_major,
    aptx_minor,
    aptx_patch,
};
```

#### src/openaptx.rs
Contains all translated code from openaptx.c and openaptx.h:
- Constants (OPENAPTX_MAJOR, etc.)
- Version globals
- Internal structs (aptx_filter_signal, aptx_QMF_analysis, etc.)
- Main context struct (aptx_context)
- Lookup tables (quantize_intervals_*, etc.)
- All functions (clip_intp2, aptx_encode, aptx_decode, etc.)

#### src/bin/openaptxenc.rs
```rust
//! aptX encoder command-line utility
use std::io::{self, Read, Write};
use libopenaptx::*;

fn main() -> io::Result<()> {
    // Translation of openaptxenc.c main()
}
```

#### src/bin/openaptxdec.rs
```rust
//! aptX decoder command-line utility
use std::io::{self, Read, Write};
use libopenaptx::*;

fn main() -> io::Result<()> {
    // Translation of openaptxdec.c main()
}
```

#### tests/common/mod.rs
```rust
//! Shared test utilities

#[macro_export]
macro_rules! ASSERT {
    ($cond:expr, $msg:expr) => {
        assert!($cond, $msg);
    };
}

#[macro_export]
macro_rules! PASS {
    ($msg:expr) => {
        println!("✅ {} passed", $msg);
    };
}
```

#### tests/test_*.rs
Each test file contains `#[test]` functions corresponding to the C test functions.

### Cargo.toml Structure

```toml
[package]
name = "libopenaptx"
version = "0.2.1"
authors = ["Original C authors", "Rust translation team"]
edition = "2021"
license = "GPL-3.0-or-later"
description = "Open Source implementation of aptX and aptX HD audio codecs"
repository = "https://github.com/..."
readme = "README.md"
keywords = ["audio", "codec", "aptx", "bluetooth"]
categories = ["multimedia::audio"]

[lib]
name = "libopenaptx"
path = "src/lib.rs"
crate-type = ["lib", "cdylib", "staticlib"]  # For C FFI compatibility

[[bin]]
name = "openaptxenc"
path = "src/bin/openaptxenc.rs"

[[bin]]
name = "openaptxdec"
path = "src/bin/openaptxdec.rs"

[dependencies]
# No external dependencies for core library

[dev-dependencies]
# Optional: for testing enhancements
# proptest = "1.0"

[profile.release]
opt-level = 3
lto = true
codegen-units = 1

[profile.bench]
inherits = "release"
```

## RUST Structs & Traits

All struct names are preserved exactly from the C code. No new traits are introduced beyond standard derives.

### Core Data Structures

#### aptx_filter_signal
```rust
#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_filter_signal {
    pub buffer: [i32; 2 * FILTER_TAPS],  // 32 elements
    pub pos: u8,
}
```

#### aptx_QMF_analysis
```rust
#[derive(Debug, Clone, Default)]
pub struct aptx_QMF_analysis {
    pub outer_filter_signal: [aptx_filter_signal; NB_FILTERS],
    pub inner_filter_signal: [[aptx_filter_signal; NB_FILTERS]; NB_FILTERS],
}
```

#### aptx_quantize
```rust
#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_quantize {
    pub quantized_sample: i32,
    pub quantized_sample_parity_change: i32,
    pub error: i32,
}
```

#### aptx_invert_quantize
```rust
#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_invert_quantize {
    pub quantization_factor: i32,
    pub factor_select: i32,
    pub reconstructed_difference: i32,
}
```

#### aptx_prediction
```rust
#[derive(Debug, Clone, Default)]
pub struct aptx_prediction {
    pub prev_sign: [i32; 2],
    pub s_weight: [i32; 2],
    pub d_weight: [i32; 24],
    pub pos: i32,
    pub reconstructed_differences: [i32; 48],
    pub previous_reconstructed_sample: i32,
    pub predicted_difference: i32,
    pub predicted_sample: i32,
}
```

#### aptx_channel
```rust
#[derive(Debug, Clone, Default)]
pub struct aptx_channel {
    pub codeword_history: i32,
    pub dither_parity: i32,
    pub dither: [i32; NB_SUBBANDS],
    pub qmf: aptx_QMF_analysis,
    pub quantize: [aptx_quantize; NB_SUBBANDS],
    pub invert_quantize: [aptx_invert_quantize; NB_SUBBANDS],
    pub prediction: [aptx_prediction; NB_SUBBANDS],
}
```

#### aptx_context
```rust
#[derive(Debug, Clone, Default)]
pub struct aptx_context {
    pub decode_sync_packets: usize,
    pub decode_dropped: usize,
    pub channels: [aptx_channel; NB_CHANNELS],
    pub hd: u8,
    pub sync_idx: u8,
    pub encode_remaining: u8,
    pub decode_skip_leading: u8,
    pub decode_sync_buffer_len: u8,
    pub decode_sync_buffer: [u8; 6],
}
```

#### aptx_tables
```rust
#[derive(Debug, Clone, Copy)]
pub struct aptx_tables {
    pub quantize_intervals: &'static [i32],
    pub invert_quantize_dither_factors: &'static [i32],
    pub quantize_dither_factors: &'static [i32],
    pub quantize_factor_select_offset: &'static [i16],
    pub tables_size: usize,
    pub factor_max: i32,
    pub prediction_order: usize,
}
```

### Derived Traits

- **Debug**: For debugging output (derives automatically)
- **Clone**: For deep copying structures
- **Copy**: For small structures that can be copied implicitly
- **Default**: For zero-initialization (matches C's zero-init behavior)

**No custom traits** are required for this translation.

## RUST Error Handling

The C API uses minimal error handling (NULL returns, partial processing). The Rust translation will preserve this behavior for API compatibility but use Rust idioms internally.

### Public API Error Handling

**C Pattern:**
```c
struct aptx_context *ctx = aptx_init(hd);
if (!ctx) {
    // Handle allocation failure
}
```

**Rust Translation:**
```rust
pub fn aptx_init(hd: bool) -> Option<Box<aptx_context>> {
    Some(Box::new(aptx_context::default_with_hd(hd)))
}
```

**Alternative (for better ergonomics):**
```rust
// Internal implementation might use Result
fn aptx_init_internal(hd: bool) -> Result<Box<aptx_context>, AllocationError> {
    Ok(Box::new(aptx_context::default_with_hd(hd)))
}

// Public API maintains compatibility
pub fn aptx_init(hd: bool) -> Option<Box<aptx_context>> {
    aptx_init_internal(hd).ok()
}
```

### Function Return Values

Maintain C semantics:
- **Processed byte counts**: Return `usize` (was `size_t`)
- **Success flags**: Return `bool` (was `int` as 0/1)
- **Written values**: Use mutable reference `&mut usize` (was pointer)
- **NULL checks**: Use `Option<T>` for nullable returns

### Command-Line Utility Error Handling

**C Pattern:**
```c
if (fread(buffer, 1, size, stdin) != size) {
    fprintf(stderr, "Error reading\n");
    return 1;
}
```

**Rust Translation:**
```rust
fn main() -> io::Result<()> {
    let mut stdin = io::stdin();
    let mut buffer = [0u8; 1024];

    stdin.read_exact(&mut buffer)?;  // ? propagates errors

    Ok(())
}
```

**Error Reporting:**
```rust
if let Err(e) = process() {
    eprintln!("Error: {}", e);
    std::process::exit(1);
}
```

## RUST 3rd Party Libraries

The Rust translation will use **no external dependencies** for the core library, matching the C implementation.

### Core Library
- **Dependencies**: None (only `std`)
- **Rationale**: Maintains simplicity and portability

### Optional Development Dependencies
- **proptest** (optional): Property-based testing for codec validation
- **criterion** (optional): Benchmarking framework
- **cargo-llvm-cov** (optional): Code coverage tool

### Build Dependencies
- None required

## RUST Translated Libraries

Since the C library has no external dependencies, there are no 3rd-party libraries to translate. All functionality is implemented using:
- Rust standard library (`std`)
- Core language features
- Built-in types and traits

### Standard Library Usage

**From `std`:**
- `std::boxed::Box` - Heap allocation (replaces malloc/free)
- `std::mem` - Memory operations (size_of, etc.)
- `std::io` - I/O traits for command-line utilities
- `std::env` - Command-line argument parsing
- `std::process` - Exit codes for utilities

**Core Types:**
- `i8`, `u8`, `i16`, `u16`, `i32`, `u32`, `i64`, `u64` - Integer types
- `usize` - Size type (replaces `size_t`)
- `bool` - Boolean type
- `[T; N]` - Fixed-size arrays
- `&[T]` - Slices

### API Compatibility Layer (Optional)

For FFI compatibility with C, optionally provide a C-compatible interface:

```rust
// src/ffi.rs (optional)
use std::os::raw::{c_int, c_uchar};

#[no_mangle]
pub extern "C" fn aptx_init(hd: c_int) -> *mut aptx_context {
    match super::aptx_init(hd != 0) {
        Some(ctx) => Box::into_raw(ctx),
        None => std::ptr::null_mut(),
    }
}

#[no_mangle]
pub extern "C" fn aptx_finish(ctx: *mut aptx_context) {
    if !ctx.is_null() {
        unsafe { Box::from_raw(ctx); }
    }
}

// ... additional FFI wrappers
```

**Trade-offs:**
- Enables C interoperability
- Adds minimal overhead
- Requires `unsafe` blocks
- **Recommendation**: Implement only if C FFI is required

## Implementation Notes

### Integer Arithmetic
Use `.wrapping_*()` methods to match C overflow behavior:
```rust
// C: a + b (with wraparound on overflow)
// Rust: a.wrapping_add(b)
```

### Inline Functions
Annotate hot functions with `#[inline]`:
```rust
#[inline]
fn clip_intp2(a: i32, p: u32) -> i32 {
    // ...
}
```

### Constants
Define as `const` for compile-time evaluation:
```rust
pub const NB_CHANNELS: usize = 2;
pub const NB_SUBBANDS: usize = 4;
pub const FILTER_TAPS: usize = 16;
pub const LATENCY_SAMPLES: usize = 90;
```

### Static Tables
Define as `static` arrays:
```rust
static QUANTIZE_INTERVALS_LF: [i32; 65] = [
    -9948, 9948, 29860, /* ... */
];
```

### Memory Safety
- No manual memory management
- Drop trait handles cleanup
- Bounds checking on array access (optimizer removes when provable)
- No null pointers (use `Option<Box<T>>`)

### Performance Considerations
- Use release mode: `cargo build --release`
- Enable LTO: `lto = true` in Cargo.toml
- Consider SIMD optimizations (future work)
- Profile with `cargo bench` using Criterion

## Testing Strategy

1. **Unit Tests**: Inline `#[test]` functions in src/openaptx.rs
2. **Integration Tests**: Separate test files in tests/
3. **Roundtrip Tests**: Encode then decode, verify data
4. **Edge Case Tests**: Boundary conditions, error cases
5. **Compatibility Tests**: Compare output with C implementation
6. **Property-Based Tests** (optional): Random input validation with proptest
7. **Benchmarks** (optional): Performance comparison with Criterion

## Build and Installation

```bash
# Build library and binaries
cargo build --release

# Run tests
cargo test

# Run benchmarks (if implemented)
cargo bench

# Install binaries
cargo install --path .

# Generate documentation
cargo doc --open

# Check code
cargo clippy
cargo fmt
```

## Future Enhancements (Post-Translation)

After completing the 1:1 translation, consider:
1. Add SIMD optimizations using `std::simd` or `packed_simd`
2. Implement parallel processing for multi-channel audio
3. Add async I/O support for streaming use cases
4. Create high-level wrapper API with builder pattern
5. Add comprehensive error types with `thiserror`
6. Implement `no_std` support for embedded systems
7. Add WASM target support for browser use

**Note**: These are deferred until after translation validation.
