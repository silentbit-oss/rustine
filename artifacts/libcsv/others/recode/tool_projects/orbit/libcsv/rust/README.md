# libcsv-rust

A Rust translation of the libcsv library for parsing and writing CSV data.

## Original Library

This is a Rust translation of libcsv version 3.0.3, a C library for parsing and writing CSV (Comma-Separated Values) data.

Original library: https://sourceforge.net/projects/libcsv/

## Installation

This Rust crate requires Rust 1.56 or later.

Add this to your `Cargo.toml`:

```toml
[dependencies]
libcsv = { path = "." }
```

Or build and run tests:

```bash
cargo build
cargo test
```

## Features

- Parse CSV data with configurable options
- Write CSV data with proper quoting and escaping
- Support for custom delimiters and quote characters
- Strict parsing mode for validating CSV format
- Configurable handling of spaces, line endings, and empty fields
- Custom space and term functions for specialized parsing

## Usage

See the `examples/` directory for usage examples:

- `csvtest.rs` - Basic CSV parsing example
- `csvfix.rs` - CSV reformatting tool
- `csvvalid.rs` - CSV validation tool
- `csvinfo.rs` - CSV file information and statistics

## License

The libcsv library is licensed under the LGPL, see the COPYING file for details.
The example programs are not covered under a license and can be used without restriction.

## Documentation

Run `cargo doc --open` to generate and view the documentation.

## Testing

Run the test suite:

```bash
cargo test
```

## Translation Notes

This Rust translation maintains functional equivalence with the original C library while using safe Rust constructs throughout. All functionality has been translated to use Rust's memory-safe features without any `unsafe` code blocks.

## Reference Files

The original C source files are included in this directory for reference:
- `csv.h` - C header file with API definitions
- `libcsv.c` - C implementation
- `test_csv.c` - C test suite
