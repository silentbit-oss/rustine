# Rust Standard Library I/O Research

## Overview

The C command-line utilities (openaptxenc.c and openaptxdec.c) use stdio for reading and writing binary audio data. This document covers Rust's I/O capabilities for equivalent functionality.

## File I/O

### C Approach
```c
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

// Windows binary mode
_setmode(_fileno(stdin), _O_BINARY);
_setmode(_fileno(stdout), _O_BINARY);

// Reading
fread(buffer, 1, size, stdin);

// Writing
fwrite(buffer, 1, size, stdout);
```

### Rust Approach

**Recommendation: Use `std::io` traits and stdin/stdout**

```rust
use std::io::{self, Read, Write};

fn main() -> io::Result<()> {
    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    let mut buffer = vec![0u8; 1024];

    // Reading
    let n = stdin.read(&mut buffer)?;

    // Writing
    stdout.write_all(&buffer[..n])?;
    stdout.flush()?;

    Ok(())
}
```

**Key Traits:**
- `Read` - Provides `read()`, `read_exact()`, `read_to_end()` etc
- `Write` - Provides `write()`, `write_all()`, `flush()` etc
- `BufRead` - Provides buffered reading with `read_line()`, `lines()` etc

**Binary Mode:**
- On Unix: stdin/stdout are already binary
- On Windows: Rust handles binary mode automatically
- No need for `_setmode()` equivalent

**Buffered I/O:**
```rust
use std::io::{BufReader, BufWriter};

let stdin = BufReader::new(io::stdin());
let stdout = BufWriter::new(io::stdout());
```

**Trade-offs:**
- Unbuffered: Lower latency, more syscalls
- Buffered: Better throughput, slight latency
- **Recommendation**: Use BufReader/BufWriter for command-line tools

## Error Handling

### C Approach
```c
if (fread(buffer, 1, size, stdin) != size) {
    fprintf(stderr, "Error reading\n");
    return 1;
}
```

### Rust Approach

**Recommendation: Use `Result<T, E>` and `?` operator**

```rust
use std::io::{self, Read};

fn process() -> io::Result<()> {
    let mut stdin = io::stdin();
    let mut buffer = vec![0u8; 1024];

    // ? operator propagates errors
    stdin.read_exact(&mut buffer)?;

    Ok(())
}

fn main() {
    if let Err(e) = process() {
        eprintln!("Error: {}", e);
        std::process::exit(1);
    }
}
```

**Key Methods:**
- `read()` - Reads up to buffer size, returns bytes read
- `read_exact()` - Reads exact buffer size or returns error
- `read_to_end()` - Reads until EOF

**Error Types:**
```rust
io::Error // Standard I/O errors
io::ErrorKind::UnexpectedEof
io::ErrorKind::InvalidData
// etc.
```

**Trade-offs:**
- `?` operator: Clean code but propagates errors up
- `unwrap()`: Panics on error (avoid in libraries)
- `expect("msg")`: Panics with message (better for debugging)
- **Recommendation**: Use `?` with `Result` return type

## Command-Line Arguments

### C Approach
```c
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--hd") == 0) {
        hd = 1;
    }
}
```

### Rust Approach

**Option 1: Manual parsing with `std::env::args()`**
```rust
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let hd = args.contains(&"--hd".to_string());
}
```

**Option 2: Use `clap` crate (recommended for complex CLIs)**
```rust
use clap::Parser;

#[derive(Parser)]
struct Args {
    /// Enable aptX HD mode
    #[arg(long)]
    hd: bool,
}

fn main() {
    let args = Args::parse();
    if args.hd {
        // ...
    }
}
```

**Trade-offs:**
- Manual: Zero dependencies, full control
- `clap`: Rich features (help text, validation, etc.), external dependency
- **Recommendation**: Manual for simple flags (like this project), `clap` for complex CLIs

## Binary Data Conversion

### C Approach
```c
// Convert 3 bytes to 24-bit signed int
int32_t sample = (int32_t)(((uint32_t)input[0] << 0) |
                           ((uint32_t)input[1] << 8) |
                           ((uint32_t)(int8_t)input[2] << 16));
```

### Rust Approach

**Recommendation: Use byte order methods**

```rust
// Little-endian 24-bit to i32
let sample = i32::from_le_bytes([
    input[0],
    input[1],
    input[2],
    if input[2] & 0x80 != 0 { 0xFF } else { 0x00 }, // Sign extend
]);

// Or using bit operations (more explicit)
let sample = (input[0] as u32) |
             ((input[1] as u32) << 8) |
             ((input[2] as i8 as i32) << 16);
```

**Standard conversions:**
```rust
u16::from_le_bytes([byte0, byte1])
u16::from_be_bytes([byte0, byte1])
i32::to_le_bytes()
i32::to_be_bytes()
```

**Trade-offs:**
- `from_*_bytes()`: Type-safe, clear endianness
- Bit operations: More flexible, matches C directly
- **Recommendation**: Use bit operations to match C behavior exactly

## Memory Buffers and Slices

### C Approach
```c
unsigned char buffer[1024];
fread(buffer, 1, 1024, stdin);
process_data(buffer, 1024);
```

### Rust Approach

**Recommendation: Use slices (`&[u8]` and `&mut [u8]`)**

```rust
let mut buffer = [0u8; 1024];
stdin.read_exact(&mut buffer)?;
process_data(&buffer);

// Or with Vec for dynamic sizing
let mut buffer = vec![0u8; 1024];
let n = stdin.read(&mut buffer)?;
process_data(&buffer[..n]);
```

**Key Slice Operations:**
```rust
// Subslicing
let first_half = &buffer[..512];
let second_half = &buffer[512..];

// Chunking
for chunk in buffer.chunks(4) {
    // Process 4-byte chunks
}

// Iteration
for byte in buffer.iter() { }
for byte in buffer.iter_mut() { }
```

**Trade-offs:**
- Fixed arrays: Stack-allocated, compile-time size
- Vec: Heap-allocated, dynamic sizing
- **Recommendation**: Use fixed arrays for known sizes, Vec for variable

## Stdout Locking

### Performance Consideration

```rust
use std::io::{self, Write};

fn main() -> io::Result<()> {
    let stdout = io::stdout();
    let mut handle = stdout.lock(); // Lock for duration of scope

    // Multiple writes without re-locking overhead
    for chunk in data.chunks(1024) {
        handle.write_all(chunk)?;
    }

    Ok(())
}
```

**When to use:**
- Many small writes in a loop
- Prevents repeated lock/unlock overhead
- Lock is released when handle goes out of scope

## Platform-Specific Considerations

### Windows vs Unix

**C Approach:**
```c
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
#endif
```

**Rust Approach:**
```rust
// Not needed! Rust handles this automatically
// stdin/stdout are binary-safe on all platforms
```

**Platform-specific compilation (if needed):**
```rust
#[cfg(windows)]
fn platform_specific() {
    // Windows-only code
}

#[cfg(unix)]
fn platform_specific() {
    // Unix-only code
}
```

## Example: Complete Translation Pattern

### C Code (openaptxenc.c main loop)
```c
while (1) {
    size_t r = fread(input, 1, sizeof(input), stdin);
    if (r == 0)
        break;

    size_t processed = aptx_encode(ctx, input, r, output, sizeof(output), &written);
    fwrite(output, 1, written, stdout);
}
```

### Rust Translation
```rust
use std::io::{self, Read, Write};

fn main() -> io::Result<()> {
    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    let mut input = [0u8; 1024];
    let mut output = [0u8; 512];

    loop {
        let r = stdin.read(&mut input)?;
        if r == 0 {
            break; // EOF
        }

        let mut written = 0;
        let processed = aptx_encode(&mut ctx, &input[..r], &mut output, &mut written);
        stdout.write_all(&output[..written])?;
    }

    stdout.flush()?;
    Ok(())
}
```

## Summary

| C Feature | Rust Equivalent | Notes |
|-----------|----------------|-------|
| `fread/fwrite` | `read()/write_all()` | Use Read/Write traits |
| `stdin/stdout` | `io::stdin()/io::stdout()` | Already binary-safe |
| `fprintf(stderr)` | `eprintln!()` | Formatted error output |
| Binary mode | N/A | Automatic in Rust |
| Buffer | `[u8; N]` or `Vec<u8>` | Slices for passing |
| `argc/argv` | `env::args()` | Iterator over arguments |
| Error checking | `Result<T>` + `?` | Idiomatic error handling |

## Recommendations for This Project

1. **Use `std::io::Read` and `std::io::Write` traits** for I/O operations
2. **Use `BufReader` and `BufWriter`** for better performance
3. **Use `?` operator** for clean error propagation
4. **Use `eprintln!`** for error messages (writes to stderr)
5. **Return `io::Result<()>`** from main for error handling
6. **Use fixed-size arrays** when buffer size is known
7. **No need for platform-specific binary mode handling** - Rust does this automatically
