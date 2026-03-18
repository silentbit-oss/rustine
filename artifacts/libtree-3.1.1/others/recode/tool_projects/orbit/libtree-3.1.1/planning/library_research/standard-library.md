# Rust Standard Library Research

## Overview

The Rust standard library (`std`) provides most of the functionality needed to replace C standard library dependencies. No external crates are needed for these capabilities.

## File I/O - `std::fs` and `std::io`

### Replacement for `<stdio.h>` file operations

**`std::fs::File`**: File handle
- `File::open(path)` - Opens file for reading (replaces `fopen(path, "rb")`)
- `File::create(path)` - Creates/truncates file for writing
- Implements `Read`, `Write`, `Seek` traits

**`std::io::Read`**: Reading from files/streams
- `read(&mut self, buf: &mut [u8]) -> Result<usize>` - Read bytes (replaces `fread()`)
- `read_to_end(&mut self, buf: &mut Vec<u8>)` - Read entire file
- `read_exact(&mut self, buf: &mut [u8])` - Read exact amount or error

**`std::io::Seek`**: File positioning
- `seek(&mut self, pos: SeekFrom) -> Result<u64>` - Replaces `fseek()`
- `SeekFrom::Start(offset)` - Replaces `SEEK_SET`
- `SeekFrom::Current(offset)` - Replaces `SEEK_CUR`
- `SeekFrom::End(offset)` - Replaces `SEEK_END`

**`std::io::BufReader`**: Buffered reading (for config file parsing)
- `BufRead::read_line()` - Read line-by-line
- `BufRead::lines()` - Iterator over lines

**`std::fs::metadata()` and `std::fs::Metadata`**: File information
- Replaces `stat()` and `struct stat`
- Methods: `dev()`, `ino()`, `len()`, `is_file()`, `is_dir()`

### Migration from C

| C Function | Rust Equivalent |
|------------|----------------|
| `fopen(path, "rb")` | `File::open(path)?` |
| `fclose(fptr)` | Automatic via Drop trait |
| `fread(buf, size, count, fptr)` | `file.read(buf)?` |
| `fseek(fptr, offset, SEEK_SET)` | `file.seek(SeekFrom::Start(offset))?` |
| `stat(path, &statbuf)` | `std::fs::metadata(path)?` |

## String Operations - `std::string` and `str`

### Replacement for `<string.h>`

**`String`**: Owned, growable UTF-8 string
- `String::new()` - Empty string
- `String::from(s)` - From string literal
- `String::push_str(&str)` - Append string (replaces `strcat()`)
- `String::push(char)` - Append character

**`&str`**: String slice (borrowed string)
- `len()` - String length (replaces `strlen()`)
- `is_empty()` - Check if empty
- `starts_with(pattern)` - Prefix check
- `ends_with(pattern)` - Suffix check
- `contains(pattern)` - Substring search
- `split(delimiter)` - String splitting (for colon-delimited paths)
- `trim()`, `trim_start()`, `trim_end()` - Whitespace removal

**String searching**:
- `find(pattern) -> Option<usize>` - Replaces `strchr()`, `strstr()`
- `rfind(pattern) -> Option<usize>` - Replaces `strrchr()`

**String comparison**:
- `==`, `!=` operators - Replaces `strcmp()`
- `starts_with(prefix)` - Replaces `strncmp()` for prefix matching

### Migration from C

| C Function | Rust Equivalent |
|------------|----------------|
| `strlen(s)` | `s.len()` |
| `strcmp(a, b)` | `a == b` |
| `strncmp(a, b, n)` | `a.starts_with(&b[..n])` or `a[..n] == b[..n]` |
| `strchr(s, c)` | `s.find(c)` |
| `strrchr(s, c)` | `s.rfind(c)` |
| `strstr(haystack, needle)` | `haystack.find(needle)` |

## Memory Management - Automatic via Ownership

### Replacement for `<stdlib.h>` memory functions

**No manual memory management needed**:
- `malloc()` - Replaced by `Vec::new()`, `Box::new()`, etc.
- `realloc()` - Automatic via `Vec::reserve()`, `Vec::push()`
- `free()` - Automatic via Drop trait when value goes out of scope

**Dynamic arrays**: `Vec<T>`
- `Vec::new()` - Empty vector
- `Vec::with_capacity(n)` - Pre-allocated capacity
- `vec.push(item)` - Add element (auto-grows)
- `vec.reserve(additional)` - Ensure capacity
- `vec.len()` - Current size
- `vec.capacity()` - Allocated capacity

### Migration from C

| C Pattern | Rust Equivalent |
|-----------|----------------|
| `char *buf = malloc(size)` | `let mut buf = Vec::with_capacity(size)` |
| `buf = realloc(buf, new_size)` | `buf.reserve(additional)` |
| `free(buf)` | Automatic when `buf` goes out of scope |

## System Information - `std::env` and `std::os::unix`

### Replacement for `<sys/utsname.h>`

**`std::env`**: Environment variables
- `env::var("VAR_NAME")` - Get environment variable (replaces `getenv()`)
- `env::vars()` - Iterator over all environment variables

**Platform information** (requires `uname` crate or libc):
For `uname()` functionality, use the `uname` crate (thin wrapper around libc):
```rust
use uname::uname;
let info = uname().unwrap();
println!("OS: {}", info.sysname);
println!("Release: {}", info.release);
println!("Machine: {}", info.machine);
```

### Migration from C

| C Function | Rust Equivalent |
|------------|----------------|
| `getenv("VAR")` | `std::env::var("VAR").ok()` |
| `uname(&utsname)` | `uname::uname()?` (requires `uname` crate) |

## Process and Terminal - `std::io` and `std::os::unix::io`

### Replacement for `<unistd.h>`

**`std::io::IsTerminal`** (Rust 1.70+): Terminal detection
- `std::io::stdout().is_terminal()` - Replaces `isatty(STDOUT_FILENO)`

**Standard streams**:
- `std::io::stdout()` - Standard output
- `std::io::stderr()` - Standard error
- `std::io::stdin()` - Standard input

### Migration from C

| C Function | Rust Equivalent |
|------------|----------------|
| `isatty(STDOUT_FILENO)` | `std::io::stdout().is_terminal()` |

## Parsing and Conversion

### Replacement for `<stdlib.h>` parsing functions

**Integer parsing**:
- `str::parse::<u64>()` - Replaces `strtoul()`
- `str::parse::<i64>()` - Replaces `strtol()`
- Returns `Result<T, ParseIntError>`

**Example**:
```rust
let num: u64 = "12345".parse()?; // Replaces strtoul(s, NULL, 10)
```

## Error Handling - `Result<T, E>`

### Replacement for C error codes

Rust uses `Result<T, E>` enum for error handling:
```rust
enum Result<T, E> {
    Ok(T),     // Success case
    Err(E),    // Error case
}
```

**Usage pattern**:
```rust
match operation() {
    Ok(value) => {
        // Handle success
    }
    Err(error) => {
        // Handle error
    }
}

// Or use ? operator for early return
let value = operation()?;
```

### Migration from C

| C Pattern | Rust Equivalent |
|-----------|----------------|
| `if (func() != 0) { return -1; }` | `func()?;` |
| `int status = func(); if (status == ERROR) { ... }` | `match func() { Ok(_) => ..., Err(e) => ... }` |

## Key Differences from C

1. **Memory Safety**: No manual `malloc`/`free` - ownership system prevents leaks and use-after-free
2. **No NULL**: Use `Option<T>` instead of null pointers
3. **UTF-8 Strings**: Rust strings are always valid UTF-8 (use `Vec<u8>` for byte arrays)
4. **Automatic Cleanup**: Resources cleaned up via Drop trait when going out of scope
5. **Error Handling**: Use `Result` and `Option` instead of error codes and null
6. **Iterator-based**: Prefer iterators over manual loops with indices

## Suitability for libtree Translation

**Rating**: ⭐⭐⭐⭐⭐ (5/5)

The Rust standard library provides all necessary functionality to replace C standard library dependencies:
1. File I/O operations are more ergonomic and safer
2. String handling is UTF-8-aware and bounds-checked
3. Automatic memory management prevents leaks
4. Error handling via Result is more explicit and safer
5. No additional dependencies needed for basic operations
