# Glob Crate Research

## Overview

**Crate Name**: `glob`
**Purpose**: Unix shell-style pattern matching for file paths
**Primary Use Case**: Finding files matching wildcard patterns (replacement for libc `glob()`)

## Key Features

1. **Unix shell-style patterns**: Supports `*`, `?`, `[...]`, and `**` (recursive) wildcards
2. **Cross-platform**: Pure Rust implementation works consistently on Windows, Linux, macOS
3. **Two modes**: Filesystem querying (like `glob()`) and direct path matching (like `fnmatch()`)
4. **Customizable**: `MatchOptions` for fine-grained control
5. **Iterator-based**: Lazy evaluation of matching paths

## Main Types

**`Pattern`**: Compiled shell-style pattern for matching
- Created via `Pattern::new(pattern_str)?`
- Can be reused for multiple matches
- Method: `matches(&self, path: &str) -> bool`

**`Paths`**: Iterator over matching filesystem paths
- Returned by `glob()` and `glob_with()`
- Yields `Result<PathBuf, GlobError>` items

**`MatchOptions`**: Configuration for pattern matching
- Fields:
  - `case_sensitive: bool` - Whether to match case
  - `require_literal_separator: bool` - Whether `*` matches path separators
  - `require_literal_leading_dot: bool` - Whether `*` matches leading dots

**`GlobError`**: Error during iteration (I/O errors, permission issues)

**`PatternError`**: Error parsing pattern (invalid syntax)

## Main Functions

**`glob(pattern: &str) -> Result<Paths, PatternError>`**
- Returns iterator over paths matching pattern with default options
- Example: `glob("/etc/*.conf")?`

**`glob_with(pattern: &str, options: MatchOptions) -> Result<Paths, PatternError>`**
- Same as `glob()` but with custom options
- Example: `glob_with("*.TXT", MatchOptions { case_sensitive: false, .. })?`

## Recommended Usage Patterns

**Basic filesystem search**:
```rust
use glob::glob;

for entry in glob("/etc/*.conf")? {
    match entry {
        Ok(path) => println!("Found: {}", path.display()),
        Err(e) => println!("Error: {}", e),
    }
}
```

**Pattern matching without filesystem access**:
```rust
use glob::Pattern;

let pattern = Pattern::new("*.conf")?;
if pattern.matches("nginx.conf") {
    println!("Match!");
}
```

**Custom options**:
```rust
use glob::{glob_with, MatchOptions};

let options = MatchOptions {
    case_sensitive: false,
    require_literal_separator: true,
    require_literal_leading_dot: false,
};

for entry in glob_with("/path/**/*.conf", options)? {
    // Process entries
}
```

## Trade-offs

**Advantages**:
- Drop-in replacement for libc `glob()` functionality
- Cross-platform consistency (important for Rust portability)
- Iterator-based API is idiomatic Rust
- Lightweight with minimal dependencies
- Well-established, part of Rust community libraries

**Disadvantages**:
- Slightly different semantics from POSIX glob in edge cases
- No direct equivalent to `GLOB_TILDE` expansion (need to handle `~` separately)
- Pattern parsing happens at runtime (not compile-time)

## Suitability for libtree Translation

**Rating**: ⭐⭐⭐⭐⭐ (5/5)

The glob crate is perfect for the libtree translation because:
1. **Direct replacement**: The C code uses `glob()` from `<glob.h>`, and this provides nearly identical functionality
2. **Usage in libtree**: The C version uses glob for expanding wildcard patterns in ld.so.conf `include` directives
3. **Error handling**: GlobError provides the same error cases as POSIX glob (NOSPACE, ABORTED, NOMATCH)
4. **Iterator-based**: More idiomatic Rust than the C callback-based approach
5. **Cross-platform**: Ensures consistent behavior across systems

## Migration Strategy from C glob()

**C Code**:
```c
glob_t result;
memset(&result, 0, sizeof(result));
int status = glob(pattern, 0, NULL, &result);

switch (status) {
case GLOB_NOSPACE:
case GLOB_ABORTED:
    return -1;
case GLOB_NOMATCH:
case 0:
    break;
}

for (size_t i = 0; i < result.gl_pathc; i++) {
    // Process result.gl_pathv[i]
}

globfree(&result);
```

**Rust Translation**:
```rust
match glob(pattern) {
    Ok(paths) => {
        for entry in paths {
            match entry {
                Ok(path) => {
                    // Process path
                }
                Err(e) => {
                    // Handle GlobError (I/O error, permission denied, etc.)
                    return Err(e);
                }
            }
        }
    }
    Err(e) => {
        // Handle PatternError (invalid pattern syntax)
        return Err(e);
    }
}
```

**Key Differences**:
- Rust version doesn't need explicit memory cleanup (`globfree()` - handled by Drop)
- Errors are handled via Result types instead of return codes
- No need for `memset()` initialization
- Iterator-based iteration instead of array access
