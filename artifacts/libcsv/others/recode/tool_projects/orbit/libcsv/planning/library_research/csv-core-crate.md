# Rust Library Research: csv-core Crate

## Overview

**Crate**: csv-core (version 0.1.11+)
**Author**: BurntSushi (Andrew Gallant)
**License**: Unlicense/MIT
**Repository**: https://github.com/BurntSushi/rust-csv
**Documentation**: https://docs.rs/csv-core/

The `csv-core` crate is a minimal, low-level CSV parsing and writing library designed for `no_std` environments. It provides the foundation for the higher-level `csv` crate.

## Key Characteristics

- **`no_std` compatible**: Works without the Rust standard library
- **Zero allocation**: No heap allocations required
- **Zero-copy**: Minimal data copying
- **Streaming**: Pull-based API for incremental processing
- **Low-level**: Requires manual state management

## Core Types

### Reader

```rust
pub struct Reader {
    // Internal state (opaque)
}

impl Reader {
    pub fn new() -> Reader;

    pub fn read_field(
        &mut self,
        input: &[u8],
        output: &mut [u8]
    ) -> (ReadFieldResult, usize, usize);

    pub fn read_record(
        &mut self,
        input: &[u8],
        output: &mut [u8]
    ) -> (ReadRecordResult, usize, usize);

    pub fn finish(&mut self, output: &mut [u8]) -> (ReadFieldResult, usize);
}

pub enum ReadFieldResult {
    InputEmpty,      // Need more input data
    OutputFull,      // Output buffer full
    Field { record_end: bool },  // Field complete
    End,             // End of CSV data
}

pub enum ReadRecordResult {
    InputEmpty,
    OutputFull,
    Record,          // Complete record read
    End,
}
```

### ReaderBuilder

```rust
pub struct ReaderBuilder {
    // Configuration fields
}

impl ReaderBuilder {
    pub fn new() -> ReaderBuilder;
    pub fn delimiter(&mut self, delimiter: u8) -> &mut Self;
    pub fn quote(&mut self, quote: u8) -> &mut Self;
    pub fn terminator(&mut self, term: Terminator) -> &mut Self;
    pub fn quoting(&mut self, yes: bool) -> &mut Self;
    pub fn double_quote(&mut self, yes: bool) -> &mut Self;
    pub fn escape(&mut self, escape: Option<u8>) -> &mut Self;
    pub fn build(&self) -> Reader;
}
```

### Writer

```rust
pub struct Writer {
    // Internal state
}

impl Writer {
    pub fn new() -> Writer;

    pub fn field(&mut self, input: &[u8], output: &mut [u8]) -> (WriteResult, usize, usize);
    pub fn delimiter(&mut self, output: &mut [u8]) -> (WriteResult, usize);
    pub fn terminator(&mut self, output: &mut [u8]) -> (WriteResult, usize);
    pub fn finish(&mut self, output: &mut [u8]) -> (WriteResult, usize);
}

pub enum WriteResult {
    InputEmpty,      // All input consumed
    OutputFull,      // Output buffer full
}
```

### WriterBuilder

```rust
pub struct WriterBuilder {
    // Configuration fields
}

impl WriterBuilder {
    pub fn new() -> WriterBuilder;
    pub fn delimiter(&mut self, delimiter: u8) -> &mut Self;
    pub fn quote(&mut self, quote: u8) -> &mut Self;
    pub fn terminator(&mut self, term: Terminator) -> &mut Self;
    pub fn quote_style(&mut self, style: QuoteStyle) -> &mut Self;
    pub fn double_quote(&mut self, yes: bool) -> &mut Self;
    pub fn escape(&mut self, escape: u8) -> &mut Self;
    pub fn build(&self) -> Writer;
}
```

### Terminator

```rust
pub enum Terminator {
    CRLF,            // \r\n
    Any(u8),         // Any single byte

    // Platform-specific
    #[cfg(unix)]
    pub const fn unix() -> Terminator { Terminator::Any(b'\n') }

    #[cfg(windows)]
    pub const fn windows() -> Terminator { Terminator::CRLF }
}
```

### QuoteStyle

```rust
pub enum QuoteStyle {
    Always,          // Always quote fields
    Necessary,       // Quote only when necessary
    NonNumeric,      // Quote non-numeric fields
    Never,           // Never quote
}
```

## API Design Philosophy

### Pull-Based Streaming

Unlike callback-based APIs, `csv-core` uses a pull model:

1. Call `read_field()` or `read_record()`
2. Inspect result enum
3. Handle cases: need more input, output full, data ready, or end
4. Manually manage input/output buffer positions

This design gives maximum control but requires careful state management.

### Buffer Management

The caller provides both input and output buffers:

```rust
let mut reader = Reader::new();
let input = b"a,b,c\n";
let mut output = [0u8; 1024];

let (result, input_read, output_written) = reader.read_field(input, &mut output);
```

Returns:
- `result`: What happened (field complete, need more input, etc.)
- `input_read`: How many input bytes consumed
- `output_written`: How many output bytes written

### Zero-Copy Design

The API minimizes copying:
- Input buffer provided by caller (can be mmap'd file, network buffer, etc.)
- Output buffer provided by caller (can write directly to final destination)
- Reader advances through input incrementally
- No internal allocations

## Typical Usage Patterns

### Reading CSV Fields

```rust
use csv_core::{Reader, ReadFieldResult};

let mut reader = Reader::new();
let input = b"field1,field2,field3\n";
let mut output = [0u8; 1024];
let mut input_pos = 0;
let mut output_pos = 0;

loop {
    let (result, nin, nout) = reader.read_field(
        &input[input_pos..],
        &mut output[output_pos..]
    );
    input_pos += nin;
    output_pos += nout;

    match result {
        ReadFieldResult::Field { record_end } => {
            // Field complete, available in output[0..output_pos]
            let field = &output[0..output_pos];
            process_field(field);
            output_pos = 0;  // Reset for next field

            if record_end {
                // End of record
                break;
            }
        }
        ReadFieldResult::InputEmpty => {
            // Need more input data
            break;
        }
        ReadFieldResult::OutputFull => {
            // Output buffer full, need to flush or enlarge
            break;
        }
        ReadFieldResult::End => {
            // End of CSV data
            break;
        }
    }
}
```

### Writing CSV Fields

```rust
use csv_core::{Writer, WriteResult};

let mut writer = Writer::new();
let input = b"field_value";
let mut output = [0u8; 1024];
let mut output_pos = 0;

// Write field
let (result, nin, nout) = writer.field(input, &mut output[output_pos..]);
output_pos += nout;

// Write delimiter
let (result, nout) = writer.delimiter(&mut output[output_pos..]);
output_pos += nout;

// Write another field...

// Write terminator
let (result, nout) = writer.terminator(&mut output[output_pos..]);
output_pos += nout;
```

## Performance Characteristics

- **Minimal overhead**: Direct state machine implementation
- **No allocations**: All buffers provided by caller
- **Predictable**: No hidden allocations or panics
- **Embeddable**: Suitable for embedded systems
- **Fast**: Core parsing loop highly optimized

## When to Use csv-core vs csv

### Use `csv-core` when:

1. **`no_std` environment**: Embedded systems, bare metal, WASM without std
2. **Maximum control**: Need precise control over buffer management
3. **Zero allocation required**: Strict memory constraints
4. **Custom I/O**: Non-standard input sources (hardware, custom protocols)
5. **Performance critical**: Squeeze out last bit of performance

### Use `csv` crate when:

1. **Standard applications**: Normal Rust programs with std library
2. **Ergonomics**: Want iterator-based, high-level API
3. **Serde integration**: Need automatic struct serialization
4. **Convenience**: Don't need low-level control

## Comparison to libcsv

### Similarities

- Low-level, state machine-based parsing
- Caller manages buffers
- Incremental/streaming processing
- Minimal dependencies
- Configuration via builder pattern

### Differences

| Feature | libcsv | csv-core |
|---------|--------|----------|
| Callbacks | Yes (`cb1`, `cb2`) | No (pull-based) |
| Buffer allocation | Dynamic (realloc) | Caller-provided |
| Error handling | Status codes | Result enums |
| Memory management | Manual free | No allocation |
| State | Opaque struct | Opaque struct |

### API Comparison

| libcsv | csv-core |
|--------|----------|
| `csv_parser` | `Reader` |
| `csv_parse()` | `read_field()` / `read_record()` |
| `csv_init()` | `Reader::new()` / `ReaderBuilder::build()` |
| `csv_free()` | Not needed (no allocation) |
| `csv_fini()` | `finish()` |
| `csv_set_delim()` | `ReaderBuilder::delimiter()` |
| `csv_set_quote()` | `ReaderBuilder::quote()` |
| Callbacks | Manual field processing |
| Buffer growth | Caller manages output buffer |

## Trade-offs

### Advantages

- `no_std` compatible
- Zero allocation
- Maximum control
- Predictable performance
- Small code size

### Disadvantages

- Complex API (manual state management)
- More code required for basic tasks
- No Serde integration
- No automatic buffer management
- No high-level conveniences

## Mapping to libcsv

`csv-core` is actually **more similar** to libcsv's design than the high-level `csv` crate:

1. **Both are low-level**: Direct state machine access
2. **Streaming**: Incremental processing
3. **Caller-managed buffers**: libcsv has dynamic buffers, csv-core requires static buffers
4. **Pull vs Push**: csv-core is pull-based, libcsv is push (callback) based

## Recommendation for Translation

`csv-core` is **suitable for a 1:1 translation** if:

- Goal is to maintain the low-level API style
- Need `no_std` compatibility
- Want to preserve the streaming, incremental design
- Callbacks can be adapted to pull-based API

However, for a more idiomatic Rust translation, combining aspects of both `csv-core` (for low-level implementation) and exposing a higher-level API (like `csv` crate) would be better.

### Hybrid Approach Recommendation

1. Use `csv-core` as **internal implementation** (or inspiration)
2. Expose **both** low-level and high-level APIs:
   - Low-level: Similar to libcsv (for compatibility)
   - High-level: Rust iterators, `Result`, Serde (for idiomatic usage)

This provides:
- **Compatibility**: C users can understand the low-level API
- **Ergonomics**: Rust users get idiomatic API
- **Flexibility**: Users choose based on needs
