# Rust Library Research: csv Crate

## Overview

**Crate**: csv (version 1.4.0+)
**Author**: BurntSushi (Andrew Gallant)
**License**: Unlicense/MIT
**Repository**: https://github.com/BurntSushi/rust-csv
**Documentation**: https://docs.rs/csv/

The `csv` crate is the most widely used CSV library in the Rust ecosystem, providing a fast and flexible CSV reader and writer with Serde integration.

## Core Types

### Reader Types

1. **`Reader<R>`**: Main CSV reader type
   - Generic over any `io::Read` implementation
   - Provides iterator interface over records
   - Supports both `StringRecord` (UTF-8) and `ByteRecord` (raw bytes)

2. **`ReaderBuilder`**: Builder for configuring readers
   - Set delimiters, quotes, terminators
   - Configure header behavior
   - Set buffer capacity
   - Enable/disable flexible parsing

3. **`StringRecord`**: UTF-8 validated record
   - Implements `Index<usize>` for field access
   - Provides iterators over fields
   - Clone-on-write semantics

4. **`ByteRecord`**: Raw byte record
   - No UTF-8 validation
   - Better performance for binary data
   - Can be converted to `StringRecord`

### Writer Types

1. **`Writer<W>`**: Main CSV writer type
   - Generic over any `io::Write` implementation
   - Automatic quote escaping
   - Serde serialization support

2. **`WriterBuilder`**: Builder for configuring writers
   - Set delimiters, quotes, terminators
   - Configure quote style
   - Set buffer capacity

## Configuration Options

### ReaderBuilder Options

```rust
let reader = csv::ReaderBuilder::new()
    .delimiter(b',')           // Field delimiter (default: comma)
    .quote(b'"')               // Quote character (default: double quote)
    .double_quote(true)        // Enable quote escaping via doubling
    .escape(None)              // Optional escape character
    .has_headers(true)         // First row is header
    .flexible(false)           // Allow variable field count
    .trim(Trim::None)          // Whitespace trimming
    .terminator(Terminator::CRLF)  // Line ending
    .comment(None)             // Comment character
    .from_reader(reader);
```

### Trim Options

```rust
pub enum Trim {
    None,       // No trimming
    Headers,    // Trim header fields only
    Fields,     // Trim all fields
    All,        // Trim headers and fields
}
```

### Terminator Options

```rust
pub enum Terminator {
    CRLF,       // \r\n (default)
    Any(u8),    // Custom single-byte terminator
}
```

### Quote Style (Writer)

```rust
pub enum QuoteStyle {
    Always,         // Quote all fields
    Necessary,      // Quote only when needed (default)
    NonNumeric,     // Quote non-numeric fields
    Never,          // Never quote (may produce invalid CSV)
}
```

## Error Handling

### Error Type

The crate provides a single `Error` type with various kinds:

```rust
pub enum ErrorKind {
    Io(io::Error),              // I/O error
    Utf8 { pos, err },          // UTF-8 validation error
    UnequalLengths { pos, expected, actual },  // Record length mismatch
    Seek,                       // Seek error
    Serialize(String),          // Serde serialization error
    Deserialize { pos, err },   // Serde deserialization error
}
```

Errors are returned as `Result<T, csv::Error>`.

## Typical Usage Patterns

### Reading CSV Records

```rust
// Iterate over string records
let mut reader = csv::Reader::from_reader(io::stdin());
for result in reader.records() {
    let record = result?;
    // Process record
}

// With headers
let mut reader = csv::Reader::from_reader(file);
let headers = reader.headers()?;
for result in reader.records() {
    let record = result?;
    let field = &record[0];  // Access by index
}
```

### Reading with Serde

```rust
#[derive(Debug, Deserialize)]
struct Row {
    name: String,
    age: u32,
    city: String,
}

let mut reader = csv::Reader::from_reader(file);
for result in reader.deserialize() {
    let row: Row = result?;
    // Process typed row
}
```

### Writing CSV

```rust
let mut writer = csv::Writer::from_writer(io::stdout());
writer.write_record(&["a", "b", "c"])?;
writer.write_record(&["1", "2", "3"])?;
writer.flush()?;

// With Serde
#[derive(Serialize)]
struct Row { name: String, age: u32 }

let mut writer = csv::Writer::from_writer(file);
writer.serialize(Row { name: "Alice".to_string(), age: 30 })?;
writer.flush()?;
```

## Performance Characteristics

- **Fast**: Uses `csv-core` for low-level parsing (zero-copy when possible)
- **Memory efficient**: Streaming API, doesn't load entire file
- **Buffer control**: Configurable buffer capacity
- **Optimized serialization**: Uses `itoa` and `ryu` for fast number formatting

## Dependencies

- `csv-core`: Low-level parsing engine
- `serde`: Optional, for serialization/deserialization
- `itoa`: Fast integer to string conversion
- `ryu`: Fast float to string conversion

## Serde Integration

The crate provides seamless Serde integration:

- **Deserialization**: Automatically maps CSV fields to struct fields by header name
- **`invalid_option`**: Special deserializer for handling empty strings as `None`
- **Custom deserializers**: Support for complex field types

## Idiomatic Usage Recommendations

### When to Use `StringRecord` vs `ByteRecord`

- **`StringRecord`**: Default choice for UTF-8 data (most CSV files)
- **`ByteRecord`**: Use when data may contain invalid UTF-8 or when working with raw bytes

### Error Handling Best Practices

```rust
// Explicit error handling
for result in reader.records() {
    match result {
        Ok(record) => process_record(&record),
        Err(e) => {
            eprintln!("Error reading record: {}", e);
            // Decide: continue, skip, or abort
        }
    }
}

// With `?` operator
fn process_csv(path: &str) -> Result<(), csv::Error> {
    let mut reader = csv::Reader::from_path(path)?;
    for result in reader.records() {
        let record = result?;
        process_record(&record);
    }
    Ok(())
}
```

### Builder Pattern Usage

Always use builders for non-default configuration:

```rust
let reader = csv::ReaderBuilder::new()
    .delimiter(b';')
    .has_headers(false)
    .flexible(true)
    .from_path("data.csv")?;
```

## Trade-offs

### Advantages

- Mature, well-tested library
- Excellent performance
- Strong Serde integration
- Comprehensive configuration options
- Good documentation and examples

### Disadvantages

- High-level API (less control than `csv-core`)
- Requires `std` (not suitable for `no_std` environments)
- Callback-based parsing not supported (iterator only)

## Mapping to libcsv Concepts

| libcsv Feature | csv Crate Equivalent |
|----------------|---------------------|
| `csv_parser` struct | `Reader<R>` / `ReaderBuilder` |
| `csv_parse()` | `reader.records()` iterator |
| Field callback `cb1` | Access via `StringRecord` index |
| Row callback `cb2` | Implicit in iterator (each `next()`) |
| `csv_init()` | `ReaderBuilder::new()` |
| `csv_free()` | Automatic via Drop trait |
| `csv_fini()` | Automatic at end of iteration |
| `csv_write()` | `writer.write_record()` |
| Custom delimiters | `.delimiter()` builder method |
| Custom quotes | `.quote()` builder method |
| Strict mode | No direct equivalent (flexible mode opposite) |
| Buffer management | Automatic with configurable capacity |

## Recommendation for Translation

The `csv` crate is **highly recommended** for the Rust translation:

1. **Idiomatic Rust**: Uses iterators, `Result`, and Serde
2. **Performance**: Comparable or better than C libcsv
3. **Safety**: Memory-safe, no buffer overflows
4. **Maintainability**: Well-documented, widely used
5. **Feature parity**: Covers all libcsv capabilities

However, direct 1:1 translation will require adapting:
- Callback-based API → Iterator-based API
- Manual buffer management → Automatic buffer management
- State machine → Hidden internal state
- C-style error codes → Rust `Result` type
