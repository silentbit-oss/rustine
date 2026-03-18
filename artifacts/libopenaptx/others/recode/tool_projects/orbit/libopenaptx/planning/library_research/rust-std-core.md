# Rust Standard Library Core Features Research

## Overview

For the libopenaptx translation from C to Rust, the primary dependencies will be from Rust's standard library. The C implementation has no external dependencies, so the Rust translation should similarly rely only on `std` and core language features.

## Memory Management

### C Approach
```c
struct aptx_context *ctx = malloc(sizeof(*ctx));
free(ctx);
```

### Rust Approach

**Recommendation: Use `Box<T>` for heap allocation**

```rust
pub struct aptx_context {
    // fields...
}

// Initialization
let ctx = Box::new(aptx_context::default());

// Automatic deallocation via Drop trait
// No explicit free() needed
```

**Key Differences:**
- Rust's `Box<T>` provides automatic memory management via RAII
- Drop trait automatically called when Box goes out of scope
- No manual free() required
- Memory safety guaranteed at compile time

**Alternative Approaches:**
1. **`Box::new()`** - Heap allocation (recommended for large structs)
2. **Stack allocation** - For smaller structs, can return directly
3. **`Arc<Mutex<T>>`** - For shared ownership (not needed here)

**Trade-offs:**
- `Box<T>`: Simple, no overhead, single ownership
- Stack: Fastest but size limitations
- `Arc`: Thread-safe but unnecessary overhead for single-threaded codec

## Integer Types

### C Approach
```c
#include <stdint.h>
int32_t, uint32_t, int16_t, uint8_t, size_t
```

### Rust Approach

**Built-in primitive types:**
```rust
i8, u8      // 8-bit signed/unsigned
i16, u16    // 16-bit signed/unsigned
i32, u32    // 32-bit signed/unsigned
i64, u64    // 64-bit signed/unsigned
isize, usize // Pointer-sized signed/unsigned
```

**Recommendation:**
- Use Rust's built-in types directly: `i32`, `u32`, `i16`, `u8`, `usize`
- These are guaranteed sizes, same as C's `stdint.h`
- No need for type aliases unless desired for clarity

**Key Operations:**
```rust
// Wrapping arithmetic (matches C overflow behavior)
a.wrapping_add(b)
a.wrapping_sub(b)
a.wrapping_mul(b)

// Checked arithmetic (returns Option)
a.checked_add(b)

// Saturating arithmetic
a.saturating_add(b)

// Bit operations
a & b, a | b, a ^ b
a << shift, a >> shift
```

**Trade-offs:**
- Default Rust arithmetic panics on overflow in debug mode
- C has undefined overflow for signed integers
- Use `wrapping_*` methods to match C behavior exactly
- Consider using checked operations for safety where appropriate

## Constants and Static Data

### C Approach
```c
static const int32_t quantize_intervals_LF[65] = { ... };
```

### Rust Approach

**Recommendation: Use `const` or `static` arrays**

```rust
// Const (inlined at compile time)
const QUANTIZE_INTERVALS_LF: [i32; 65] = [ ... ];

// Static (has fixed address in memory)
static QUANTIZE_INTERVALS_LF: [i32; 65] = [ ... ];
```

**Key Differences:**
- `const`: Inlined wherever used, no memory address
- `static`: Single instance with fixed address
- Both are immutable by default

**Recommendation for this project:**
- Use `const` for small lookup tables (< 100 elements)
- Use `static` for large tables or when address matters
- Use `const` for compile-time constants like `NB_SUBBANDS`

**Trade-offs:**
- `const`: Potentially duplicated in binary but optimizer usually handles this
- `static`: Single copy, can take more space in stack frames if referenced
- Both have zero runtime cost

## Structs and Field Initialization

### C Approach
```c
struct aptx_filter_signal {
    int32_t buffer[32];
    uint8_t pos;
};
```

### Rust Approach

**Recommendation: Use standard structs with derive macros**

```rust
#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_filter_signal {
    pub buffer: [i32; 32],
    pub pos: u8,
}
```

**Common derives:**
- `Debug`: Enables `{:?}` formatting for debugging
- `Clone`: Enables `.clone()` for deep copy
- `Copy`: Enables implicit copy for small types
- `Default`: Enables `::default()` for zero-initialization

**Initialization patterns:**
```rust
// Default initialization (zeros)
let signal = aptx_filter_signal::default();

// Explicit initialization
let signal = aptx_filter_signal {
    buffer: [0; 32],
    pos: 0,
};

// Partial initialization (rest default)
let signal = aptx_filter_signal {
    pos: 5,
    ..Default::default()
};
```

**Trade-offs:**
- Derive macros: Zero cost, code generation at compile time
- Manual implementation: More control but more boilerplate
- `Copy` trait: Only for small types (< 1KB typically)

## Arrays and Buffers

### C Approach
```c
int32_t buffer[32];
uint8_t decode_sync_buffer[6];
```

### Rust Approach

**Recommendation: Use fixed-size arrays**

```rust
buffer: [i32; 32]
decode_sync_buffer: [u8; 6]
```

**Key Operations:**
```rust
// Iteration
for item in buffer.iter() { }
for item in buffer.iter_mut() { }

// Slicing
let slice = &buffer[0..16];
let slice = &mut buffer[16..32];

// Zero initialization
let buffer = [0i32; 32];
```

**Alternative: Vec for dynamic sizing (not needed here):**
```rust
let buffer = vec![0i32; 32]; // Heap-allocated, growable
```

**Trade-offs:**
- Fixed arrays: Stack-allocated, compile-time size, no overhead
- Vec: Heap-allocated, dynamic sizing, small overhead (capacity tracking)
- For this codec, fixed arrays are recommended (matches C exactly)

## Enums

### C Approach
```c
enum channels {
    LEFT,
    RIGHT,
    NB_CHANNELS
};
```

### Rust Approach

**Recommendation: Use proper enums without count variant**

```rust
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Channel {
    Left = 0,
    Right = 1,
}

pub const NB_CHANNELS: usize = 2;
```

**Or use constants if indexing is primary use:**
```rust
pub const LEFT: usize = 0;
pub const RIGHT: usize = 1;
pub const NB_CHANNELS: usize = 2;
```

**Trade-offs:**
- Enum: Type-safe, matches exhaustively in match statements
- Constants: Simpler for array indexing, matches C more directly
- **Recommendation**: Use constants for this project (simpler array indexing)

## Inline Functions

### C Approach
```c
static inline int32_t clip_intp2(int32_t a, unsigned p) {
    // ...
}
```

### Rust Approach

**Recommendation: Use `#[inline]` attribute**

```rust
#[inline]
fn clip_intp2(a: i32, p: u32) -> i32 {
    // ...
}

// Or for aggressive inlining
#[inline(always)]
fn clip_intp2(a: i32, p: u32) -> i32 {
    // ...
}
```

**Key Differences:**
- Rust's optimizer is very good at inlining automatically
- `#[inline]` is a hint, not a requirement
- `#[inline(always)]` forces inlining (like `__attribute__((always_inline))`)

**Recommendation:**
- Use `#[inline]` for small hot functions
- Let compiler decide for most cases
- Use `#[inline(always)]` sparingly (only for tiny functions)

## Opaque Types (API Design)

### C Approach
```c
// Header file
struct aptx_context;  // Forward declaration

// Implementation file
struct aptx_context {
    // actual fields
};
```

### Rust Approach

**Recommendation: Use module privacy**

```rust
// In lib.rs or public module
pub struct AptxContext {
    // Private fields (not pub)
    channels: [AptxChannel; NB_CHANNELS],
    hd: bool,
    // ...
}

impl AptxContext {
    pub fn new(hd: bool) -> Box<Self> {
        // ...
    }

    pub fn reset(&mut self) {
        // ...
    }
}
```

**Alternative: Newtype pattern for full opacity:**
```rust
pub struct AptxContext(Box<AptxContextInner>);

struct AptxContextInner {
    // fields
}
```

**Trade-offs:**
- Private fields: Simple, allows direct field access internally
- Newtype: Full opacity, more indirection
- **Recommendation**: Private fields (simpler and more idiomatic)

## Summary of Recommendations

| C Feature | Rust Equivalent | Recommendation |
|-----------|----------------|----------------|
| `malloc/free` | `Box::new()` + Drop | Use Box for heap allocation |
| `int32_t` etc | `i32`, `u32` etc | Direct primitive types |
| `static const` | `const` or `static` | Use `const` for tables |
| `struct` | `struct` | Add derive macros |
| Fixed arrays | `[T; N]` | Use fixed-size arrays |
| `enum` | `enum` or `const` | Use `const` for indices |
| `inline` | `#[inline]` | Use for hot functions |
| Opaque pointer | Private fields | Module privacy |
| Overflow | `.wrapping_*()` | Match C behavior |

## Documentation

Rust has excellent built-in documentation support:

```rust
/// Initialize context for aptX codec and reset it.
///
/// # Arguments
/// * `hd` - false for aptX codec, true for aptX HD codec
///
/// # Returns
/// A new AptxContext in a Box
pub fn aptx_init(hd: bool) -> Box<AptxContext> {
    // ...
}
```

Documentation is generated with `cargo doc` and appears in IDE hover tooltips.
