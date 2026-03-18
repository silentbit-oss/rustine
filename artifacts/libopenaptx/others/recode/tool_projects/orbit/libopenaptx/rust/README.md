# libopenaptx (Rust Implementation)

This is a Rust translation of the Open Source implementation of Audio Processing Technology codec (aptX), originally derived from the C implementation based on ffmpeg 4.0 project and licensed under GPLv3+. This codec is mainly used in Bluetooth A2DP profile.

This Rust translation maintains full functional equivalence with the C implementation while providing memory safety guarantees and idiomatic Rust code.

## License

This library is licensed under GPLv3+. If you need other license options, please contact the original author. Please refer to the COPYING file for full license details.

**Important License Restrictions:**

This library and any other project which uses this library must not be used in other organizations, projects, applications, libraries (and in any other software form) incompatible with libopenaptx licence or where current license of this project is violated or where previous version of this library/license was violated. Freedesktop and Collabora are examples of such projects which are not allowed to use this library in any form due to license violations.

Participants of Freedesktop and Collabora projects and any other affiliated persons with them are not allowed to contact author or contribute to this project.

Other projects which are adding additional hidden or implicit restrictions to their licenses through their own Code of Conduct explanation and therefore make them incompatible with license of this library are not allowed to use this library or any other application based on this library in their project in any form, including redistribution.

## Features

- **aptX codec**: Fixed compression ratio 6:1
- **aptX HD codec**: Fixed compression ratio 4:1
- Both variants operate on raw 24-bit signed stereo audio samples
- 100% safe Rust implementation (no unsafe blocks)
- Full functional equivalence with C implementation verified through comprehensive testing

## Project Structure

This project provides:
- `libopenaptx` - Rust library crate with the codec implementation
- `openaptxenc` - Command line utility for encoding operations
- `openaptxdec` - Command line utility for decoding operations

Documentation for the library is provided in the source code documentation (`cargo doc`).

## Building

### Prerequisites

- Rust toolchain (1.70 or later recommended)
- Cargo build system

### Build and Install

To build the project:

```bash
cargo build --release
```

To run tests:

```bash
cargo test
```

To build and install system-wide:

```bash
cargo install --path .
```

### Optimization

The release build is configured with optimization level 3 by default. The Rust compiler will automatically apply appropriate optimizations for your target CPU.

For additional CPU-specific optimizations (e.g., AVX2 on Intel Haswell or AMD Excavator and later):

```bash
RUSTFLAGS="-C target-cpu=native" cargo build --release
```

## Usage

The command line utilities work identically to the C version and can be used with `sox` for resampling or playing audio.

### Convert Wave audio file to aptX

```bash
sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | openaptxenc > sample.aptx
```

### Convert aptX audio file to Wave

```bash
openaptxdec < sample.aptx | sox -t raw -r 44.1k -L -e s -b 24 -c 2 - sample.wav
```

### Convert MP3 to aptX HD

```bash
sox sample.mp3 -t raw -r 44.1k -L -e s -b 24 -c 2 - | openaptxenc --hd > sample.aptxhd
```

### Play aptX HD audio file

```bash
openaptxdec --hd < sample.aptxhd | play -t raw -r 44.1k -L -e s -b 24 -c 2 -
```

## Library API

The Rust library provides a safe, idiomatic API for encoding and decoding aptX audio. See the module documentation for detailed API information:

```bash
cargo doc --open
```

Key types:
- `openaptx_context` - Codec context structure
- `openaptx_encode` - Encode 24-bit stereo samples to aptX
- `openaptx_decode` - Decode aptX to 24-bit stereo samples
- `openaptx_init` - Initialize codec context
- `openaptx_free` - Free codec context resources

## Translation Notes

This Rust implementation is a direct translation from the C codebase, maintaining:
- Exact function and variable naming from the original
- Identical algorithmic behavior
- Same compression ratios and audio quality
- Binary-compatible output with the C implementation

The translation has been verified through:
- Comprehensive unit tests matching the C test suite
- Cross-language integration tests comparing C and Rust outputs
- Round-trip encoding/decoding verification
- 100% test pass rate in both implementations

All code is written in safe Rust with no `unsafe` blocks, providing memory safety guarantees while maintaining full functional equivalence.

## Testing

Run the full test suite:

```bash
cargo test
```

Run tests with output:

```bash
cargo test -- --nocapture
```

Run specific tests:

```bash
cargo test test_roundtrip
```

## Benchmarking

Benchmark performance:

```bash
cargo bench
```

## Contributing

Please refer to the license restrictions above regarding who may contribute to this project.

## Original Project

This is a Rust translation of the C implementation. The original C project information and additional context can be found in the C source directory.
