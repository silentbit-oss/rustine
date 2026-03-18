# Rust Translation Design for libcsv

## Overview

This document describes the design for translating the C libcsv library (version 3.0.3) to Rust. The translation aims to provide a **1:1 functional equivalent** while leveraging Rust's safety guarantees, type system, and modern idioms.

The translation will maintain API compatibility at the structural level (same file names, same function names, same types) while adapting the implementation to use Rust's ownership model, error handling (`Result`), and memory safety features.

## Translation Requirements

### Primary Requirements

1. **1:1 Translation**: Preserve the exact directory structure, file names, and identifier names from the C codebase
2. **API Preservation**: Maintain the same public API surface (function signatures adapted to Rust types)
3. **Behavioral Equivalence**: Produce identical parsing and writing results for all valid inputs
4. **Test Compatibility**: All existing C test cases must pass with equivalent Rust implementations

### Rust Adaptations

While maintaining structural equivalence, the translation will adapt:

1. **Memory Safety**: Replace manual memory management with Rust ownership
2. **Error Handling**: Replace C error codes with `Result<T, E>` types
3. **Type Safety**: Use Rust's strong type system (no void pointers, proper enums)
4. **Null Handling**: Replace null pointers with `Option<T>`
5. **Buffer Management**: Use `Vec<u8>` instead of manual realloc
6. **Function Pointers**: Use Rust function pointers or trait objects where appropriate

### Non-Goals

- Not creating an idiomatic high-level Rust CSV library (use BurntSushi's `csv` crate for that)
- Not using Serde or other high-level abstractions
- Not changing the API design or adding new features
- Not using external crates for core functionality (only std library)

## C Source Files to Translate

### Core Library Files

1. **csv.h** → **csv.rs** (or module structure)
   - Public API definitions
   - Constants and error codes
   - `csv_parser` struct
   - Function declarations

2. **libcsv.c** → **libcsv.rs**
   - Implementation of all parsing and writing functions
   - Internal helper functions
   - State machine logic

3. **test_csv.c** → **test_csv.rs**
   - Test suite with all test cases
   - Test infrastructure

### Example Programs

4. **examples/csvfix.c** → **examples/csvfix.rs**
5. **examples/csvinfo.c** → **examples/csvinfo.rs**
6. **examples/csvtest.c** → **examples/csvtest.rs**
7. **examples/csvvalid.c** → **examples/csvvalid.rs**

### Supporting Files

8. **Cargo.toml**: Rust package manifest
9. **README.md**: Rust-specific documentation
10. **LICENSE**: Maintain LGPL 2.1 license

### Build System

- Replace GNU Autotools with Cargo (Rust's build system)
- Maintain compatibility with test files in `tests/` directory

## RUST Module Structure

The translation will preserve the exact C project structure:

```
rust/
├── Cargo.toml                  # Rust package manifest
├── README.md                   # Documentation
├── LICENSE                     # LGPL 2.1 license
├── csv.h                       # Preserved for reference (not used in build)
├── libcsv.c                    # Preserved for reference (not used in build)
├── test_csv.c                  # Preserved for reference (not used in build)
├── src/
│   ├── lib.rs                  # Main library file (combines csv.h + libcsv.c)
│   └── bin/
│       └── test_csv.rs         # Test binary (translation of test_csv.c)
├── examples/
│   ├── csvfix.rs               # Translation of csvfix.c
│   ├── csvinfo.rs              # Translation of csvinfo.c
│   ├── csvtest.rs              # Translation of csvtest.c
│   └── csvvalid.rs             # Translation of csvvalid.c
└── tests/
    ├── test_01.csv             # Test data files (copied from C)
    ├── test_02.csv
    ├── test_03.csv
    ├── test_04.csv
    ├── test_05.csv
    ├── test_06.csv
    ├── test_07.csv
    ├── test_08.csv
    ├── test_10.csv
    ├── test_11.csv
    ├── test_12.csv
    └── test_13.csv
```

### Module Organization

**`src/lib.rs`** will contain:

```rust
// Constants (from csv.h)
pub const CSV_MAJOR: u32 = 3;
pub const CSV_MINOR: u32 = 0;
pub const CSV_RELEASE: u32 = 3;

// Error codes (from csv.h)
pub const CSV_SUCCESS: i32 = 0;
pub const CSV_EPARSE: i32 = 1;
pub const CSV_ENOMEM: i32 = 2;
pub const CSV_ETOOBIG: i32 = 3;
pub const CSV_EINVALID: i32 = 4;

// Parser options (from csv.h)
pub const CSV_STRICT: u8 = 1;
pub const CSV_REPALL_NL: u8 = 2;
pub const CSV_STRICT_FINI: u8 = 4;
pub const CSV_APPEND_NULL: u8 = 8;
pub const CSV_EMPTY_IS_NULL: u8 = 16;

// Character values (from csv.h)
pub const CSV_TAB: u8 = 0x09;
pub const CSV_SPACE: u8 = 0x20;
pub const CSV_CR: u8 = 0x0d;
pub const CSV_LF: u8 = 0x0a;
pub const CSV_COMMA: u8 = 0x2c;
pub const CSV_QUOTE: u8 = 0x22;

// Main parser struct (from csv.h)
pub struct csv_parser { /* ... */ }

// Public API functions (from csv.h and libcsv.c)
pub fn csv_init(...) -> i32 { /* ... */ }
pub fn csv_fini(...) -> i32 { /* ... */ }
pub fn csv_free(...) { /* ... */ }
pub fn csv_error(...) -> i32 { /* ... */ }
pub fn csv_strerror(...) -> &'static str { /* ... */ }
pub fn csv_parse(...) -> usize { /* ... */ }
pub fn csv_write(...) -> usize { /* ... */ }
pub fn csv_fwrite(...) -> i32 { /* ... */ }
pub fn csv_write2(...) -> usize { /* ... */ }
pub fn csv_fwrite2(...) -> i32 { /* ... */ }
pub fn csv_get_opts(...) -> i32 { /* ... */ }
pub fn csv_set_opts(...) -> i32 { /* ... */ }
pub fn csv_set_delim(...) { /* ... */ }
pub fn csv_set_quote(...) { /* ... */ }
pub fn csv_get_delim(...) -> u8 { /* ... */ }
pub fn csv_get_quote(...) -> u8 { /* ... */ }
pub fn csv_set_space_func(...) { /* ... */ }
pub fn csv_set_term_func(...) { /* ... */ }
pub fn csv_set_realloc_func(...) { /* ... */ }
pub fn csv_set_free_func(...) { /* ... */ }
pub fn csv_set_blk_size(...) { /* ... */ }
pub fn csv_get_buffer_size(...) -> usize { /* ... */ }

// Internal functions (from libcsv.c)
fn csv_increase_buffer(...) -> i32 { /* ... */ }
```

### File Name Preservation

As per requirements, all file names remain identical except for the `.rs` extension replacing `.c` or `.h`.

## RUST Structs & Traits

### Core Parser Structure

Translation of `struct csv_parser`:

```rust
pub struct csv_parser {
    pub pstate: i32,                    // Parser state
    pub quoted: i32,                    // Is current field quoted (using i32 for C bool compat)
    pub spaces: usize,                  // Number of continuous spaces
    pub entry_buf: Vec<u8>,             // Entry buffer (replaces unsigned char*)
    pub entry_pos: usize,               // Current position in entry_buf
    pub entry_size: usize,              // Size of entry buffer (will equal entry_buf.len())
    pub status: i32,                    // Operation status
    pub options: u8,                    // Parser options
    pub quote_char: u8,                 // Quote character
    pub delim_char: u8,                 // Delimiter character
    pub is_space: Option<fn(u8) -> i32>,    // Space detection function
    pub is_term: Option<fn(u8) -> i32>,     // Terminator detection function
    pub blk_size: usize,                // Block size for buffer growth
    pub malloc_func: Option<fn(usize) -> *mut u8>,  // Not used (kept for compatibility)
    pub realloc_func: Option<fn(*mut u8, usize) -> *mut u8>,  // Not used in Rust impl
    pub free_func: Option<fn(*mut u8)>,     // Not used in Rust impl
}
```

**Design Notes:**
- `entry_buf` becomes `Vec<u8>` instead of raw pointer
- `entry_size` always equals `entry_buf.len()` (kept for API compatibility)
- Memory function pointers kept but not used (Rust manages memory automatically)
- `quoted` uses `i32` instead of `bool` to maintain C-compatible representation
- Function pointers use `Option<fn>` to represent nullable function pointers

### No Additional Traits Required

Since this is a 1:1 translation, we will NOT implement Rust traits like:
- `Iterator` (would change API semantics)
- `Read` / `Write` (not part of original design)
- `Serialize` / `Deserialize` (adds external dependency)

The translation maintains the C-style procedural API.

## RUST Error Handling

### Error Representation

The C library uses integer error codes. The Rust translation will maintain these for API compatibility but also provide Rust-friendly error handling.

#### Error Codes (Preserved)

```rust
pub const CSV_SUCCESS: i32 = 0;
pub const CSV_EPARSE: i32 = 1;
pub const CSV_ENOMEM: i32 = 2;
pub const CSV_ETOOBIG: i32 = 3;
pub const CSV_EINVALID: i32 = 4;
```

#### Error String Mapping

```rust
pub fn csv_strerror(error: i32) -> &'static str {
    match error {
        CSV_SUCCESS => "success",
        CSV_EPARSE => "error parsing data while strict checking enabled",
        CSV_ENOMEM => "memory exhausted while increasing buffer size",
        CSV_ETOOBIG => "data size too large",
        CSV_EINVALID => "invalid status code",
        _ => "invalid status code",
    }
}
```

### Error Handling Strategy

1. **Functions return error codes**: Maintain C API contract (`i32` return values for status)
2. **Parser stores error state**: `csv_parser.status` holds the last error
3. **`csv_error()` retrieves status**: Same as C API
4. **No panics**: All errors returned as codes, never panic

### Rust Safety Guarantees

Even though we're maintaining C-style error codes:

- **No undefined behavior**: Rust prevents buffer overflows, use-after-free, null dereferences
- **Memory safety**: Vec automatically manages allocation/deallocation
- **No manual null checks**: Use `Option<T>` for nullable values

## RUST 3rd Party Libraries

### Standard Library Only

The translation will use **only Rust's standard library**:

- `std::vec::Vec` - Dynamic arrays (replace malloc/realloc)
- `std::option::Option` - Nullable values (replace NULL)
- `std::fs::File` - File I/O (for examples and tests)
- `std::io::{Read, Write}` - I/O traits (for file operations)

### No External Crates

To maintain simplicity and match the C library's zero-dependency philosophy:

- **No `csv` crate**: We're translating libcsv itself
- **No `serde`**: Not part of original design
- **No `thiserror`/`anyhow`**: Using integer error codes
- **No `libc`**: Pure Rust implementation

### Development Dependencies

Only for testing and examples:

```toml
[dev-dependencies]
# None required - using std::fs for file I/O in tests
```

## RUST Translated Libraries

### Cargo.toml Configuration

```toml
[package]
name = "libcsv"
version = "3.0.3"
edition = "2021"
authors = ["Robert Gamble (original C)", "Translated to Rust"]
license = "LGPL-2.1"
description = "A 1:1 Rust translation of libcsv - parse and write CSV data"
repository = "https://github.com/..."

[lib]
name = "csv"
path = "src/lib.rs"

[[bin]]
name = "test_csv"
path = "src/bin/test_csv.rs"

[[example]]
name = "csvfix"
path = "examples/csvfix.rs"

[[example]]
name = "csvinfo"
path = "examples/csvinfo.rs"

[[example]]
name = "csvtest"
path = "examples/csvtest.rs"

[[example]]
name = "csvvalid"
path = "examples/csvvalid.rs"

[dependencies]
# No external dependencies

[dev-dependencies]
# No external dev dependencies
```

### Build Instructions

Replace C build system:

```bash
# Build library
cargo build --release

# Run tests
cargo run --bin test_csv

# Run examples
cargo run --example csvinfo -- tests/test_01.csv
cargo run --example csvtest
cargo run --example csvfix -- tests/test_01.csv
cargo run --example csvvalid -- tests/test_01.csv
```

### Library API

The public API will be exported from `src/lib.rs`:

```rust
// Re-export everything as pub
pub use crate::csv_parser;
pub use crate::csv_init;
pub use crate::csv_free;
pub use crate::csv_fini;
pub use crate::csv_parse;
// ... etc for all public functions
```

Users can import as:

```rust
use csv::*;

let mut parser = csv_parser::default();
csv_init(&mut parser, 0);
// ... use parser
csv_free(&mut parser);
```

## Translation Strategy

### Key Translation Decisions

#### 1. Memory Management

| C Approach | Rust Approach |
|------------|---------------|
| `malloc` / `realloc` | `Vec::new()` / `Vec::resize()` |
| `free` | Automatic (Drop trait) |
| Manual buffer growth | `Vec::reserve()` / `Vec::push()` |
| NULL pointers | `Option<T>` |

#### 2. Function Signatures

C callbacks:
```c
void (*cb1)(void *data, size_t len, void *user_data);
void (*cb2)(int c, void *user_data);
```

Rust translation:
```rust
type FieldCallback = fn(data: Option<&[u8]>, len: usize, user_data: *mut std::ffi::c_void);
type RowCallback = fn(c: i32, user_data: *mut std::ffi::c_void);
```

**Note**: Using raw pointers for `user_data` maintains C API compatibility. Rust code calling this should use `&mut T` cast to `*mut c_void`.

#### 3. State Machine

The state machine logic remains identical:
- Same states (ROW_NOT_BEGUN, FIELD_NOT_BEGUN, etc.)
- Same transitions
- Same macro logic (translated to Rust macros or inline functions)

#### 4. Buffer Operations

C:
```c
if (entry_pos == p->entry_size) {
    csv_increase_buffer(p);
}
p->entry_buf[entry_pos++] = c;
```

Rust:
```rust
if entry_pos == p.entry_buf.len() {
    csv_increase_buffer(p);
}
p.entry_buf[entry_pos] = c;
entry_pos += 1;
```

Or more idiomatically:
```rust
if entry_pos >= p.entry_buf.len() {
    p.entry_buf.reserve(p.blk_size);
    p.entry_buf.resize(p.entry_buf.len() + p.blk_size, 0);
}
p.entry_buf[entry_pos] = c;
entry_pos += 1;
```

#### 5. Macros

C macros:
```c
#define SUBMIT_FIELD(p) \
  do { \
   if (!quoted) entry_pos -= spaces; \
   /* ... */ \
  } while (0)
```

Rust translation options:

**Option A - Macro:**
```rust
macro_rules! submit_field {
    ($p:expr, $quoted:expr, $entry_pos:expr, $spaces:expr, $cb1:expr, $data:expr) => {
        {
            if !$quoted { $entry_pos -= $spaces; }
            // ... rest of logic
        }
    };
}
```

**Option B - Inline function:**
```rust
#[inline]
fn submit_field(p: &mut csv_parser, quoted: &mut bool, entry_pos: &mut usize,
                spaces: &mut usize, cb1: FieldCallback, data: *mut c_void) {
    if !*quoted { *entry_pos -= *spaces; }
    // ... rest of logic
}
```

**Recommendation**: Use inline functions for better type checking and debugging.

#### 6. Assertions

C:
```c
assert(p && "received null csv_parser");
```

Rust:
```rust
assert!(!p.is_null(), "received null csv_parser");
```

Or better, use references to eliminate nullability:
```rust
pub fn csv_error(p: &csv_parser) -> i32 {
    // No null check needed - references can't be null
    p.status
}
```

## Identifier Naming Preservation

As per requirements, **ALL identifiers remain EXACTLY the same**:

### Structures
- `csv_parser` (NOT `CsvParser` or `Parser`)

### Functions
- `csv_init` (NOT `init` or `csv_initialize`)
- `csv_parse` (NOT `parse`)
- `csv_free` (NOT `free` or `drop`)

### Constants
- `CSV_STRICT` (NOT `CsvStrict` or `STRICT`)
- `CSV_COMMA` (NOT `COMMA`)

### Variables
In function implementations, maintain C variable names:
- `pstate` (NOT `parser_state`)
- `entry_pos` (NOT `entry_position`)
- `quoted` (NOT `is_quoted`)

This ensures maximum compatibility and recognizability for users familiar with the C API.

## Testing Strategy

### Test Translation

`test_csv.c` → `test_csv.rs`:

1. **Preserve all test cases**: All 40+ test cases translated exactly
2. **Same test data**: Use the same CSV test files in `tests/` directory
3. **Same test structure**: Maintain the event-driven test framework
4. **Verify equivalence**: Ensure Rust version produces identical results

### Test Infrastructure

```rust
struct Event {
    event_type: i32,
    retval: i32,
    size: usize,
    data: Option<Vec<u8>>,
}

const CSV_END: i32 = 0;
const CSV_COL: i32 = 1;
const CSV_ROW: i32 = 2;
const CSV_ERR: i32 = 3;

fn test_parser(
    test_name: &str,
    options: u8,
    input: &[u8],
    expected: &[Event],
    delimiter: u8,
    quote: u8,
    space_func: Option<fn(u8) -> i32>,
    term_func: Option<fn(u8) -> i32>,
) {
    // Implement test logic identical to C version
}
```

### Example Test Cases

Must pass all these tests (sample):

1. **test01**: Basic parsing `"1,2 ,  3         ,4,5\r\n"`
2. **test02**: Empty fields `",,,,,\n"`
3. **test03**: Quoted commas `"\",\",\",\",\"\""`
4. **test04**: Multiline quoted field
5. **test05**: Escaped quotes
6. **test07b**: Strict mode error detection
7. **test12b**: CSV_REPALL_NL option
8. **test16b**: CSV_STRICT_FINI option
9. **test19**: CSV_EMPTY_IS_NULL option

## Implementation Phases

### Phase 1: Core Library Structure
1. Create Cargo project structure
2. Translate `csv_parser` struct
3. Translate constants and error codes
4. Implement `csv_strerror`

### Phase 2: Initialization & Configuration
1. Implement `csv_init`
2. Implement `csv_free`
3. Implement getter/setter functions
4. Implement `csv_get_opts`, `csv_set_opts`

### Phase 3: Core Parsing
1. Implement `csv_increase_buffer`
2. Translate state machine macros
3. Implement `csv_parse` (main parsing loop)
4. Implement `csv_fini`

### Phase 4: Writing Functions
1. Implement `csv_write` / `csv_write2`
2. Implement `csv_fwrite` / `csv_fwrite2`

### Phase 5: Testing
1. Translate test infrastructure
2. Translate all test cases
3. Run and verify all tests pass
4. Debug any discrepancies

### Phase 6: Examples
1. Translate `csvinfo.rs`
2. Translate `csvtest.rs`
3. Translate `csvfix.rs`
4. Translate `csvvalid.rs`
5. Verify examples work with test CSV files

## Validation Criteria

The translation is complete and correct when:

1. ✅ All source files translated (lib, tests, examples)
2. ✅ All test cases pass with identical results
3. ✅ All examples compile and run successfully
4. ✅ `cargo build --release` succeeds with no warnings
5. ✅ `cargo clippy` passes with no warnings
6. ✅ File structure exactly matches C project (with .rs extensions)
7. ✅ All identifier names preserved exactly
8. ✅ API signatures maintain compatibility (adapted to Rust types)
9. ✅ Documentation comments added for public API
10. ✅ No unsafe code except where necessary for C API compatibility

## Open Questions and Decisions

### 1. Handling void* user_data

**Decision**: Use `*mut std::ffi::c_void` for direct compatibility. Users should cast `&mut T` to this type.

### 2. Function pointers vs trait objects

**Decision**: Use raw function pointers `fn(...)` to match C API exactly. Do NOT use `Box<dyn Fn(...)>`.

### 3. Integer types for boolean flags

**Decision**: Use `i32` for `quoted` and other boolean-like fields to maintain C representation. Use `bool` internally where appropriate.

### 4. Library name

**Decision**: Crate name is `libcsv`, library name is `csv` (matching C library name).

### 5. Edition

**Decision**: Use Rust 2021 edition (latest stable) for modern features while maintaining compatibility.

## Conclusion

This design provides a comprehensive blueprint for translating libcsv from C to Rust while:

- Maintaining exact API compatibility (names, structure)
- Preserving behavioral equivalence
- Leveraging Rust's safety guarantees
- Keeping the translation simple and recognizable
- Ensuring all tests pass

The translation will serve as a reference implementation demonstrating how to translate C libraries to Rust while preserving their original design philosophy and API surface.
