# Rust Overall Translation Design

## Overview

This document outlines the design for a 1:1 translation of the libtree C project to Rust. The goal is to maintain the same functionality, architecture, and user-facing behavior while leveraging Rust's safety guarantees and modern language features.

**Design Principles**:
1. **1:1 Translation**: Preserve the exact directory structure, file names, and identifier names from the C version
2. **Idiomatic Rust**: Use Rust patterns (Result, Option, iterators) while maintaining C algorithm structure
3. **Zero Unsafe Code**: Leverage Rust's safety guarantees; avoid unsafe blocks
4. **Minimal Dependencies**: Use only well-established, necessary crates
5. **Drop-in Compatibility**: Maintain identical command-line interface and output format

## Translation Requirements

No additional requirements specified. This is a straightforward 1:1 translation of the C codebase to Rust.

## C Source Files to Translate

Based on the C project structure, the following source files must be translated:

### Primary Source Files
1. **`libtree.h`** → `libtree.rs` (module declarations moved to `lib.rs`)
2. **`libtree.c`** → `libtree.rs` (implementation)

### Test Files
1. **`tests/test.c`** → `tests/test.rs`
2. **`tests/06_symbol_versions/main.c`** → `tests/06_symbol_versions/main.rs`
3. **`tests/06_symbol_versions/v1.c`** → `tests/06_symbol_versions/v1.rs`
4. **`tests/06_symbol_versions/v2.c`** → `tests/06_symbol_versions/v2.rs`

### Build Files
1. **`Makefile`** → `Cargo.toml` (Rust package manifest)
2. Test `Makefile` files → Integrated into `Cargo.toml` test configuration

### Documentation (preserved as-is)
1. `README.md` - Updated with Rust build instructions
2. `CHANGELOG.md` - Preserved
3. `LICENSE` - Preserved
4. `doc/libtree.1` - Man page (preserved)
5. `doc/screenshot.png` - Screenshot (preserved)

## RUST Module Structure

**CRITICAL: The Rust translation MUST preserve the exact directory structure and file names from the C skeleton, changing only the file extension from `.c` to `.rs` and `.h` to `.rs`.**

### Root Directory Structure

```
rust/
├── Cargo.toml                  # Rust package manifest (replaces Makefile)
├── Cargo.lock                  # Dependency lock file (generated)
├── README.md                   # Updated with Rust instructions
├── CHANGELOG.md                # Preserved from C
├── LICENSE                     # Preserved from C
├── doc/
│   ├── libtree.1              # Man page (preserved)
│   └── screenshot.png         # Screenshot (preserved)
├── src/
│   ├── lib.rs                 # Library crate root (new)
│   ├── main.rs                # Binary crate entry point (new)
│   └── libtree.rs             # Core implementation (from libtree.c)
└── tests/
    ├── test.rs                # Main test suite (from tests/test.c)
    ├── 01_origin/
    │   └── Makefile           # Preserved or adapted
    ├── 02_rpath_of_parents_parent/
    │   └── Makefile           # Preserved or adapted
    ├── 03_direct_and_absolute_rpath/
    │   └── Makefile           # Preserved or adapted
    ├── 04_rpath_over_env_over_runpath/
    │   └── Makefile           # Preserved or adapted
    ├── 05_32_bits/
    │   └── Makefile           # Preserved or adapted
    ├── 06_symbol_versions/
    │   ├── Makefile           # Preserved or adapted
    │   ├── main.rs            # From main.c
    │   ├── v1.rs              # From v1.c
    │   ├── v1.map             # Preserved
    │   ├── v2.rs              # From v2.c
    │   └── v2.map             # Preserved
    ├── 07_origin_is_relative_to_symlink_location_not_realpath/
    │   └── Makefile           # Preserved or adapted
    ├── 08_nodeflib/
    │   └── Makefile           # Preserved or adapted
    └── 10_rpath_order/
        └── Makefile           # Preserved or adapted
```

### Module Organization

**`src/lib.rs`** (Library crate root):
- Exports public API for programmatic use
- Declares module structure
- Re-exports key types and functions

**`src/main.rs`** (Binary crate):
- Command-line parsing (from commented-out main() in libtree.c)
- Calls library functions
- Exit code handling

**`src/libtree.rs`** (Core implementation):
- All core logic from libtree.c
- Function names MUST remain identical to C version
- Struct names MUST remain identical to C version
- Module-level constants and types

### Cargo.toml Structure

```toml
[package]
name = "libtree"
version = "3.1.1"
edition = "2021"
authors = ["Original C Author", "Rust Translation Team"]
license = "MIT"
description = "Display the dependency tree of ELF binaries"
repository = "https://github.com/haampie/libtree"
readme = "README.md"

[dependencies]
goblin = "0.8"      # ELF parsing
glob = "0.3"        # Wildcard pattern matching
uname = "0.1"       # System information (uname)

[dev-dependencies]
tempfile = "3"      # Temporary files for tests

[[bin]]
name = "libtree"
path = "src/main.rs"

[lib]
name = "libtree"
path = "src/lib.rs"

[profile.release]
opt-level = 3
lto = true
codegen-units = 1
```

## RUST Structs & Traits

### Core Data Structures (libtree.rs)

All struct names MUST remain identical to the C version. Fields may be adapted to idiomatic Rust types while preserving semantics.

**`compat_t`**:
```rust
#[derive(Clone, Copy, Debug)]
pub struct compat_t {
    pub any: bool,           // bool instead of char
    pub class: u8,           // BITS32 or BITS64
    pub machine: u16,        // ISA/machine type
}
```

**`found_t`**:
```rust
#[derive(Clone, Copy, Debug)]
pub struct found_t {
    pub how: how_t,          // Enum type
    pub depth: usize,        // Depth in dependency tree
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum how_t {
    INPUT,
    DIRECT,
    RPATH,
    LD_LIBRARY_PATH,
    RUNPATH,
    LD_SO_CONF,
    DEFAULT,
}
```

**`string_table_t`**:
```rust
pub struct string_table_t {
    pub arr: Vec<u8>,        // Vec<u8> instead of char* (handles binary data)
    // n and capacity are implicit in Vec
}

impl string_table_t {
    pub fn new() -> Self {
        Self { arr: Vec::new() }
    }

    pub fn n(&self) -> usize {
        self.arr.len()
    }

    pub fn capacity(&self) -> usize {
        self.arr.capacity()
    }

    // Methods: string_table_store, string_table_maybe_grow, string_table_copy_from_file
}
```

**`visited_file_t`**:
```rust
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct visited_file_t {
    pub st_dev: u64,         // Device ID (from std::fs::Metadata)
    pub st_ino: u64,         // Inode number
}
```

**`visited_file_array_t`**:
```rust
pub struct visited_file_array_t {
    pub arr: Vec<visited_file_t>,  // Vec instead of manual array + size + capacity
}

impl visited_file_array_t {
    pub fn new() -> Self {
        Self { arr: Vec::new() }
    }

    // Methods: visited_files_contains, visited_files_append
}
```

**`libtree_state_t`**:
```rust
pub struct libtree_state_t {
    // Configuration
    pub verbosity: i32,
    pub path: bool,
    pub color: bool,
    pub ld_conf_file: String,
    pub max_depth: usize,

    // String storage
    pub string_table: string_table_t,
    pub visited: visited_file_array_t,

    // rpath substitution values
    pub PLATFORM: String,
    pub LIB: String,
    pub OSNAME: String,
    pub OSREL: String,

    // Search path offsets
    pub rpath_offsets: [usize; MAX_RECURSION_DEPTH],
    pub ld_library_path_offset: usize,
    pub default_paths_offset: usize,
    pub ld_so_conf_offset: usize,

    // Tree rendering state
    pub found_all_needed: [bool; MAX_RECURSION_DEPTH],  // bool instead of char
}

impl libtree_state_t {
    // Methods: libtree_state_init, libtree_state_free (becomes Drop impl)
}

impl Drop for libtree_state_t {
    fn drop(&mut self) {
        // Automatic cleanup (replaces libtree_state_free)
    }
}
```

**`small_vec_u64_t`**:
```rust
pub struct small_vec_u64_t {
    buf: [u64; SMALL_VEC_SIZE],  // Stack-allocated buffer
    heap: Option<Vec<u64>>,      // Heap allocation when needed
    n: usize,                    // Current size
}

impl small_vec_u64_t {
    pub fn new() -> Self {
        Self {
            buf: [0; SMALL_VEC_SIZE],
            heap: None,
            n: 0,
        }
    }

    pub fn push(&mut self, val: u64) {
        // Implementation of small_vec_u64_append
    }

    pub fn get(&self, index: usize) -> Option<u64> {
        // Safe indexing (replaces direct pointer arithmetic)
    }

    pub fn len(&self) -> usize {
        self.n
    }

    // Automatic cleanup via Drop trait (replaces small_vec_u64_free)
}

impl Drop for small_vec_u64_t {
    fn drop(&mut self) {
        // Automatic cleanup
    }
}
```

### ELF Structures (via goblin)

Instead of defining custom structs for ELF data (header_64_t, header_32_t, etc.), we use goblin's built-in types:

- `goblin::elf::Elf` - Parsed ELF file
- `goblin::elf::Header` - ELF header (unified 32/64-bit)
- `goblin::elf::ProgramHeader` - Program headers
- `goblin::elf::Dynamic` - Dynamic section entries

## RUST Error Handling

### Error Type Definition

```rust
use std::fmt;
use std::error::Error;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LibtreeError {
    InvalidMagic = 11,
    InvalidClass = 12,
    InvalidData = 13,
    InvalidHeader = 14,
    InvalidBits = 15,
    InvalidEndianness = 16,
    NoExecOrDyn = 17,
    InvalidPhoff = 18,
    InvalidProgHeader = 19,
    CantStat = 20,
    InvalidDynamicSection = 21,
    InvalidDynamicArrayEntry = 22,
    NoStrtab = 23,
    InvalidSoname = 24,
    InvalidRpath = 25,
    InvalidRunpath = 26,
    InvalidNeeded = 27,
    DependencyNotFound = 28,
    NoPtLoad = 29,
    VaddrsNotOrdered = 30,
    CouldNotOpenFile = 31,
    IncompatibleIsa = 32,
}

impl fmt::Display for LibtreeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let msg = match self {
            LibtreeError::InvalidMagic => "Invalid ELF magic bytes",
            LibtreeError::InvalidClass => "Invalid ELF class",
            // ... all other error messages
        };
        write!(f, "{}", msg)
    }
}

impl Error for LibtreeError {}

pub type LibtreeResult<T> = Result<T, LibtreeError>;
```

### Error Handling Patterns

**Function signatures**:
```rust
// C: int recurse(...)
// Rust:
pub fn recurse(
    current_file: &str,
    depth: usize,
    state: &mut libtree_state_t,
    compat: compat_t,
    reason: found_t,
) -> LibtreeResult<()> {
    // Use ? operator for error propagation
    let file = File::open(current_file)
        .map_err(|_| LibtreeError::CouldNotOpenFile)?;

    // Early returns with ?
    let elf = parse_elf(&file)?;

    Ok(())
}
```

**Error conversion**:
```rust
impl From<std::io::Error> for LibtreeError {
    fn from(err: std::io::Error) -> Self {
        match err.kind() {
            std::io::ErrorKind::NotFound => LibtreeError::CouldNotOpenFile,
            std::io::ErrorKind::PermissionDenied => LibtreeError::CouldNotOpenFile,
            _ => LibtreeError::CouldNotOpenFile,
        }
    }
}

impl From<goblin::error::Error> for LibtreeError {
    fn from(err: goblin::error::Error) -> Self {
        // Map goblin errors to LibtreeError variants
        LibtreeError::InvalidHeader
    }
}
```

## RUST 3rd Party Libraries

### Primary Dependencies

**1. goblin (version 0.8+)**
- **Purpose**: ELF parsing
- **Usage**: Parse ELF headers, program headers, dynamic section
- **Why chosen**: Battle-tested, zero-copy, handles 32/64-bit transparently
- **Alternative considered**: `elf` crate (lighter but less mature)

**2. glob (version 0.3+)**
- **Purpose**: Wildcard pattern matching for ld.so.conf include directives
- **Usage**: Direct replacement for libc `glob()` function
- **Why chosen**: Drop-in replacement, cross-platform, idiomatic Rust API
- **Alternative considered**: Manual pattern matching (complex, error-prone)

**3. uname (version 0.1+)**
- **Purpose**: System information (machine, OS name, OS release)
- **Usage**: Variable interpolation in rpath/runpath ($PLATFORM, $OSNAME, $OSREL)
- **Why chosen**: Thin wrapper around libc `uname()`, minimal overhead
- **Alternative considered**: Direct libc binding (requires unsafe code)

### Development Dependencies

**4. tempfile (version 3+)**
- **Purpose**: Creating temporary files and directories for tests
- **Usage**: Test ELF file creation and parsing
- **Why chosen**: Standard Rust testing tool, automatic cleanup

### Standard Library Usage

**std::fs**: File operations
- `File::open()`, `File::read()`, `File::seek()`

**std::io**: I/O traits and buffering
- `Read`, `Seek`, `BufReader`, `BufRead`

**std::path**: Path manipulation
- `Path`, `PathBuf`, path component extraction

**std::env**: Environment variables
- `env::var("LD_LIBRARY_PATH")`, `env::var("NO_COLOR")`

**std::collections**: Hash-based visited file tracking (optional optimization)
- `HashSet<visited_file_t>` (alternative to Vec-based linear search)

**std::io::IsTerminal**: Terminal detection for color support
- `stdout().is_terminal()` (replaces `isatty()`)

## RUST Translated Libraries

### Function Name Mapping (C → Rust)

**All function names MUST remain identical to the C version.** Only the signature and implementation change to use Rust types.

#### Utility Functions

```rust
// C: void utoa(char *str, size_t v);
pub fn utoa(v: usize) -> String {
    v.to_string()  // Rust standard library provides this
}

// C: int host_is_little_endian(void);
pub fn host_is_little_endian() -> bool {
    cfg!(target_endian = "little")  // Compile-time constant in Rust
}

// C: int is_ascending_order(uint64_t *v, size_t n);
pub fn is_ascending_order(v: &[u64]) -> bool {
    v.windows(2).all(|w| w[0] < w[1])
}
```

#### String Table Functions

```rust
// C: void string_table_maybe_grow(struct string_table_t *t, size_t n);
impl string_table_t {
    pub fn string_table_maybe_grow(&mut self, n: usize) {
        self.arr.reserve(n);  // Vec handles this automatically
    }
}

// C: void string_table_store(struct string_table_t *t, const char *str);
impl string_table_t {
    pub fn string_table_store(&mut self, s: &str) {
        self.arr.extend_from_slice(s.as_bytes());
        self.arr.push(0);  // Null terminator
    }
}

// C: void string_table_copy_from_file(struct string_table_t *t, FILE *fptr);
impl string_table_t {
    pub fn string_table_copy_from_file<R: Read>(&mut self, reader: &mut R) -> std::io::Result<()> {
        let mut byte = [0u8; 1];
        loop {
            reader.read_exact(&mut byte)?;
            if byte[0] == 0 {
                self.arr.push(0);
                break;
            }
            self.arr.push(byte[0]);
        }
        Ok(())
    }
}
```

#### Exclude List Functions

```rust
// C: int is_in_exclude_list(const char *soname);
pub fn is_in_exclude_list(soname: &str) -> bool {
    const EXCLUDE_LIST: &[&str] = &[
        "ld-linux-aarch64.so",
        "ld-linux-armhf.so",
        // ... all entries from C version
    ];

    // Strip version numbers from the right
    let trimmed = soname.trim_end_matches(|c: char| c.is_ascii_digit() || c == '.');

    EXCLUDE_LIST.iter().any(|&excluded| trimmed.starts_with(excluded))
}
```

#### Visited Files Functions

```rust
// C: int visited_files_contains(struct visited_file_array_t *files, struct stat *needle);
impl visited_file_array_t {
    pub fn visited_files_contains(&self, needle: &visited_file_t) -> bool {
        self.arr.contains(needle)
    }
}

// C: void visited_files_append(struct visited_file_array_t *files, struct stat *new);
impl visited_file_array_t {
    pub fn visited_files_append(&mut self, new: visited_file_t) {
        self.arr.push(new);
    }
}
```

#### State Management Functions

```rust
// C: void libtree_state_init(struct libtree_state_t *s);
impl libtree_state_t {
    pub fn libtree_state_init() -> Self {
        Self {
            verbosity: 0,
            path: false,
            color: std::env::var("NO_COLOR").is_err() && std::io::stdout().is_terminal(),
            ld_conf_file: "/etc/ld.so.conf".to_string(),
            max_depth: MAX_RECURSION_DEPTH,
            string_table: string_table_t::new(),
            visited: visited_file_array_t::new(),
            PLATFORM: String::new(),
            LIB: "lib".to_string(),
            OSNAME: String::new(),
            OSREL: String::new(),
            rpath_offsets: [usize::MAX; MAX_RECURSION_DEPTH],
            ld_library_path_offset: usize::MAX,
            default_paths_offset: 0,
            ld_so_conf_offset: 0,
            found_all_needed: [false; MAX_RECURSION_DEPTH],
        }
    }
}

// C: void libtree_state_free(struct libtree_state_t *s);
// Rust: Automatic via Drop trait - no explicit function needed
impl Drop for libtree_state_t {
    fn drop(&mut self) {
        // Automatic cleanup of all owned data
    }
}
```

#### Config Parsing Functions

```rust
// C: int parse_ld_config_file(struct string_table_t *t, const char *path);
pub fn parse_ld_config_file(t: &mut string_table_t, path: &str) -> LibtreeResult<()> {
    // Implementation using BufReader, glob crate
    Ok(())
}

// C: void parse_ld_library_path(struct libtree_state_t *s);
pub fn parse_ld_library_path(s: &mut libtree_state_t) {
    if let Ok(path) = std::env::var("LD_LIBRARY_PATH") {
        s.ld_library_path_offset = s.string_table.n();
        s.string_table.string_table_store(&path);
    } else {
        s.ld_library_path_offset = usize::MAX;
    }
}

// C: void set_default_paths(struct libtree_state_t *s);
pub fn set_default_paths(s: &mut libtree_state_t) {
    s.default_paths_offset = s.string_table.n();
    s.string_table.string_table_store("/lib:/usr/lib");
}
```

#### Recursion and Printing Functions

```rust
// C: void tree_preamble(const struct libtree_state_t *s, size_t depth);
pub fn tree_preamble(s: &libtree_state_t, depth: usize) {
    // Implementation using print! macro
}

// C: int recurse(char *current_file, size_t depth, struct libtree_state_t *s,
//               struct compat_t compat, struct found_t reason);
pub fn recurse(
    current_file: &str,
    depth: usize,
    s: &mut libtree_state_t,
    compat: compat_t,
    reason: found_t,
) -> LibtreeResult<()> {
    // Implementation using goblin for ELF parsing
    // Returns Result instead of int
    Ok(())
}

// C: int interpolate_variables(struct libtree_state_t *s, size_t src, const char *ORIGIN);
pub fn interpolate_variables(
    s: &mut libtree_state_t,
    src: usize,
    origin: &str,
) -> bool {
    // Implementation using string operations
    false
}

// C: void print_line(size_t depth, char *name, char *color_bold, char *color_regular,
//                   int highlight, struct found_t reason, struct libtree_state_t *s);
pub fn print_line(
    depth: usize,
    name: &str,
    color_bold: &str,
    color_regular: &str,
    highlight: bool,
    reason: found_t,
    s: &libtree_state_t,
) {
    // Implementation using print! macro
}

// C: void print_error(size_t depth, size_t needed_not_found,
//                    struct small_vec_u64_t *needed_buf_offsets,
//                    char *runpath, struct libtree_state_t *s, int no_def_lib);
pub fn print_error(
    depth: usize,
    needed_not_found: usize,
    needed_buf_offsets: &small_vec_u64_t,
    runpath: Option<&str>,
    s: &libtree_state_t,
    no_def_lib: bool,
) {
    // Implementation using print! macro
}

// C: int print_tree(int pathc, char **pathv, struct libtree_state_t *s);
pub fn print_tree(paths: &[String]) -> LibtreeResult<()> {
    let mut s = libtree_state_t::libtree_state_init();

    // Initialize system info using uname crate
    let info = uname::uname().map_err(|_| LibtreeError::CantStat)?;
    s.PLATFORM = info.machine;
    s.OSNAME = info.sysname;
    s.OSREL = info.release;

    parse_ld_so_conf(&mut s)?;
    parse_ld_library_path(&mut s);
    set_default_paths(&mut s);

    for path in paths {
        recurse(path, 0, &mut s, compat_t { any: true, class: 0, machine: 0 },
                found_t { how: how_t::INPUT, depth: 0 })?;
    }

    Ok(())
}
```

### Constants

All constant names MUST remain identical:

```rust
// ELF constants
pub const ET_EXEC: u16 = 2;
pub const ET_DYN: u16 = 3;
pub const PT_NULL: u32 = 0;
pub const PT_LOAD: u32 = 1;
pub const PT_DYNAMIC: u32 = 2;
pub const DT_NULL: i64 = 0;
pub const DT_NEEDED: i64 = 1;
pub const DT_STRTAB: i64 = 5;
pub const DT_SONAME: i64 = 14;
pub const DT_RPATH: i64 = 15;
pub const DT_RUNPATH: i64 = 29;

// Architecture constants
pub const BITS32: u8 = 1;
pub const BITS64: u8 = 2;

// Configuration constants
pub const SMALL_VEC_SIZE: usize = 16;
pub const MAX_RECURSION_DEPTH: usize = 32;
pub const MAX_PATH_LENGTH: usize = 4096;

// Color codes (as string constants)
pub const REGULAR_RED: &str = "\x1b[0;31m";
pub const BOLD_RED: &str = "\x1b[1;31m";
pub const CLEAR: &str = "\x1b[0m";
// ... all other color constants

// Tree rendering characters
pub const LIGHT_HORIZONTAL: &str = "─";
pub const LIGHT_QUADRUPLE_DASH_VERTICAL: &str = "┊";
pub const LIGHT_UP_AND_RIGHT: &str = "└";
pub const LIGHT_VERTICAL: &str = "│";
pub const LIGHT_VERTICAL_AND_RIGHT: &str = "├";
pub const JUST_INDENT: &str = "    ";
```

### Key Translation Decisions

1. **Strings**: Use `String` for owned strings, `&str` for borrowed strings (instead of `char*`)
2. **Arrays**: Use `Vec<T>` for dynamic arrays (instead of manual malloc/realloc)
3. **Fixed Arrays**: Use `[T; N]` for fixed-size arrays (same as C)
4. **Option Types**: Use `Option<T>` instead of sentinel values (e.g., `usize::MAX` → `None`)
5. **Boolean Values**: Use `bool` instead of `char` or `int`
6. **Error Handling**: Use `Result<T, E>` instead of integer error codes
7. **Memory Management**: Automatic via ownership (no manual free)
8. **File I/O**: Use `std::fs::File` and `std::io` traits instead of `FILE*`
9. **ELF Parsing**: Use `goblin` instead of manual struct parsing
10. **Glob Matching**: Use `glob` crate instead of libc `glob()`

### Testing Strategy

1. **Unit Tests**: Test individual functions with `#[cfg(test)]` modules
2. **Integration Tests**: Port C test suite to Rust in `tests/` directory
3. **Test Binary Compatibility**: Ensure Rust version produces identical output to C version
4. **Fuzz Testing**: Use cargo-fuzz to test ELF parsing robustness
5. **Cross-Platform Testing**: Test on Linux, FreeBSD (if applicable)

### Build and Distribution

**Cargo Commands**:
- `cargo build` - Debug build
- `cargo build --release` - Optimized build
- `cargo test` - Run all tests
- `cargo run -- <args>` - Run with arguments
- `cargo install --path .` - Install locally

**Release Build Optimizations** (in Cargo.toml):
```toml
[profile.release]
opt-level = 3        # Maximum optimization
lto = true           # Link-time optimization
codegen-units = 1    # Better optimization, slower compile
strip = true         # Strip symbols for smaller binary
```

**Static Linking** (for portable binary):
```toml
[profile.release]
target = "x86_64-unknown-linux-musl"  # Static linking on Linux
```

---

## Summary

This design document provides a comprehensive roadmap for translating the libtree C project to Rust while maintaining:
1. **Exact directory and file structure** (only extensions change)
2. **Identical function and struct names** (only types adapt to Rust idioms)
3. **Same functionality and behavior** (1:1 translation)
4. **Improved safety** (no unsafe code, automatic memory management)
5. **Idiomatic Rust** (Result, Option, iterators, ownership)
6. **Minimal dependencies** (goblin, glob, uname)
7. **Cross-platform compatibility** (Linux, FreeBSD)

The translation leverages Rust's strengths (safety, zero-cost abstractions, modern tooling) while preserving the C version's design and user experience.
