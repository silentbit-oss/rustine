# C Project Research Document

## Overview

The libopenaptx project is an open-source implementation of the Audio Processing Technology codec (aptX), which is primarily used in Bluetooth A2DP audio streaming. The library provides encoding and decoding functionality for both aptX (classic) and aptX HD variants.

**Key Characteristics:**
- **License**: GPLv3+
- **Primary Function**: Audio codec for compressing stereo audio samples
- **Variants**:
  - aptX Classic: 6:1 fixed compression ratio (4 bytes output per 4 samples)
  - aptX HD: 4:1 fixed compression ratio (6 bytes output per 4 samples)
- **Audio Format**: Operates on 24-bit signed stereo PCM samples at 44.1kHz
- **Latency**: 90 samples of latency in the codec pipeline

The codec uses a QMF (Quadrature Mirror Filter) tree analysis for frequency decomposition, followed by quantization and prediction filtering for compression.

## Directory Structure

```
c/
├── COPYING
├── Makefile
├── README
├── compile_commands.json
├── cov_html
│   ├── coverage
│   │   └── mnt
│   │       └── d
│   │           └── C2RustTranslation
│   │               └── subjects
│   │                   └── libopenaptx
│   │                       ├── openaptx.c.html
│   │                       └── test.c.html
│   ├── index.html
│   └── style.css
├── default.profraw
├── openaptx.c
├── openaptx.h
├── openaptxdec.c
├── openaptxenc.c
├── test.c
├── test.profdata
├── test.profraw
├── test_aptx
└── tests
    ├── test_common.h
    ├── test_dither.c
    ├── test_padding.c
    ├── test_roundtrip.c
    └── test_sync.c
```

**Core Source Files:**
- `openaptx.h` - Public API header file
- `openaptx.c` - Main codec implementation (1329 lines)
- `openaptxenc.c` - Command-line encoder utility
- `openaptxdec.c` - Command-line decoder utility
- `test.c` - Basic test suite
- `tests/` - Additional unit tests

**Build Artifacts:**
- Coverage reports in `cov_html/`
- Profiling data files (`.profraw`, `.profdata`)
- Compiled test binary `test_aptx`

## Structs & Interfaces

### Public API (openaptx.h)

**Version Constants:**
```c
#define OPENAPTX_MAJOR 0
#define OPENAPTX_MINOR 2
#define OPENAPTX_PATCH 1
extern const int aptx_major, aptx_minor, aptx_patch;
```

**Main Context:**
```c
struct aptx_context; // Opaque context structure
```

**API Functions:**
1. `aptx_init(int hd)` - Initialize codec context (hd=0 for classic, hd=1 for HD)
2. `aptx_reset(struct aptx_context *ctx)` - Reset internal state, predictor, and parity sync
3. `aptx_finish(struct aptx_context *ctx)` - Free codec context
4. `aptx_encode(...)` - Encode 4 stereo samples (24 bytes) to aptX format
5. `aptx_encode_finish(...)` - Finish encoding stream with padding (92 samples for latency)
6. `aptx_decode(...)` - Decode aptX samples to PCM
7. `aptx_decode_sync(...)` - Auto-synchronizing decoder for corrupted streams
8. `aptx_decode_sync_finish(...)` - Finish sync decoding and return dropped byte count

### Internal Structures (openaptx.c)

**Core Data Structures:**

1. **`aptx_filter_signal`** - Filter signal buffer
   - `int32_t buffer[2*FILTER_TAPS]` (32 elements)
   - `uint8_t pos` - Current position in circular buffer

2. **`aptx_QMF_analysis`** - Quadrature Mirror Filter analysis state
   - `aptx_filter_signal outer_filter_signal[NB_FILTERS]` (2 filters)
   - `aptx_filter_signal inner_filter_signal[NB_FILTERS][NB_FILTERS]` (2x2 filters)

3. **`aptx_quantize`** - Quantization state
   - `int32_t quantized_sample`
   - `int32_t quantized_sample_parity_change`
   - `int32_t error`

4. **`aptx_invert_quantize`** - Inverse quantization state
   - `int32_t quantization_factor`
   - `int32_t factor_select`
   - `int32_t reconstructed_difference`

5. **`aptx_prediction`** - Prediction filter state
   - `int32_t prev_sign[2]`
   - `int32_t s_weight[2]`
   - `int32_t d_weight[24]`
   - `int32_t pos`
   - `int32_t reconstructed_differences[48]`
   - `int32_t previous_reconstructed_sample`
   - `int32_t predicted_difference`
   - `int32_t predicted_sample`

6. **`aptx_channel`** - Per-channel codec state
   - `int32_t codeword_history` - For parity checking
   - `int32_t dither_parity`
   - `int32_t dither[NB_SUBBANDS]` (4 subbands)
   - `aptx_QMF_analysis qmf`
   - `aptx_quantize quantize[NB_SUBBANDS]`
   - `aptx_invert_quantize invert_quantize[NB_SUBBANDS]`
   - `aptx_prediction prediction[NB_SUBBANDS]`

7. **`aptx_context`** - Main codec context (complete definition)
   - `size_t decode_sync_packets`
   - `size_t decode_dropped`
   - `aptx_channel channels[NB_CHANNELS]` (2 channels: LEFT, RIGHT)
   - `uint8_t hd` - HD mode flag
   - `uint8_t sync_idx` - Synchronization index
   - `uint8_t encode_remaining` - Remaining samples to encode in finish
   - `uint8_t decode_skip_leading` - Samples to skip due to latency
   - `uint8_t decode_sync_buffer_len`
   - `unsigned char decode_sync_buffer[6]`

8. **`aptx_tables`** - Quantization lookup tables
   - `const int32_t *quantize_intervals`
   - `const int32_t *invert_quantize_dither_factors`
   - `const int32_t *quantize_dither_factors`
   - `const int16_t *quantize_factor_select_offset`
   - `int tables_size`
   - `int32_t factor_max`
   - `int prediction_order`

**Constants:**
- `NB_CHANNELS = 2` (LEFT, RIGHT)
- `NB_SUBBANDS = 4` (LF, MLF, MHF, HF frequency bands)
- `NB_FILTERS = 2`
- `FILTER_TAPS = 16`
- `LATENCY_SAMPLES = 90`

## Data Models

### External Data Models

**Input PCM Data (Encoding):**
- Format: 24-bit signed integers per sample
- Layout: LLLRRRLLLRRRLLLRRRLLLRRR (L=left 3 bytes, R=right 3 bytes)
- Size: 24 bytes per 4 stereo samples
- Byte order: Little-endian (LSB first)
- Sample range: -2^23 to 2^23-1

**Output Encoded Data (Encoding):**
- aptX Classic: 4 bytes (LLRR) per 4 stereo samples
  - L = 16 bits for left channel codeword
  - R = 16 bits for right channel codeword
  - Each codeword contains 4 quantized subband values (7,4,2,2 bits or 7,4,2,3 bits)
- aptX HD: 6 bytes (LLLRRR) per 4 stereo samples
  - L = 24 bits for left channel codeword
  - R = 24 bits for right channel codeword
  - Each codeword contains 4 quantized subband values with more precision

**Codeword Packing:**
- Classic aptX packing (16-bit): `[LF:7][MLF:4][MHF:2][HF:2/3]`
- HD aptX packing (24-bit): `[LF:9/10][MLF:6][MHF:5][HF:4]`
- Parity bit: Last bit alternates for error detection

**Synchronization:**
- Parity check every 4 frames (4 × 4 samples = 16 samples)
- Sync detection in `aptx_decode_sync` for corrupted streams

### Internal Data Models

**Sample Processing Pipeline:**
1. **Input samples** → 32-bit signed integers (int32_t)
2. **QMF Analysis** → 4 frequency subbands per channel
   - LF: Low Frequency (0-5.5 kHz)
   - MLF: Medium-Low Frequency (5.5-11 kHz)
   - MHF: Medium-High Frequency (11-16.5 kHz)
   - HF: High Frequency (16.5-22 kHz)
3. **Quantization** → Variable bit quantized values
4. **Packing** → Compact codewords

**Quantization Tables:**
- Separate tables for each subband and codec variant (classic vs HD)
- Tables contain:
  - Quantization intervals for binary search
  - Dither factors for noise shaping
  - Invert quantization factors for reconstruction
  - Factor select offsets for adaptive quantization

**Filter Coefficients:**
- Polyphase QMF filter coefficients (multiple sets)
- Used for frequency domain decomposition and reconstruction

**State Management:**
- Filter histories stored in circular buffers
- Prediction state maintained across frames
- Dither sequences generated pseudo-randomly

## Error Handling

The C implementation uses **minimal explicit error handling**:

1. **Memory Allocation:**
   - `aptx_init()` returns NULL on malloc failure
   - Caller must check for NULL pointer

2. **Buffer Management:**
   - Functions process as much data as fits in buffers
   - Return values indicate bytes processed
   - No explicit bounds checking - relies on caller providing correct sizes

3. **Parity Check Failures:**
   - `aptx_decode()`: Stops processing and returns partial result
   - `aptx_decode_sync()`: Continues processing, searches for valid sync
   - Synced flag indicates decoder state (1=synced, 0=unsynchronized)

4. **Invalid Input:**
   - No validation of input parameters
   - Undefined behavior on invalid inputs (e.g., NULL pointers with non-zero sizes)

5. **Encoding/Decoding State:**
   - Latency management via `decode_skip_leading` and `encode_remaining`
   - `aptx_reset()` clears state for new stream
   - `aptx_encode_finish()` returns 0 if more buffer needed, 1 when complete

**Error Handling Philosophy:**
- Follows C convention of minimal overhead
- Caller responsible for validity checking
- Return codes indicate success/partial completion
- No exceptions or error enums

## Dependencies

### Standard C Library Dependencies

1. **`<stdlib.h>`**
   - `malloc()` - Dynamic memory allocation for context
   - `free()` - Memory deallocation

2. **`<stdint.h>`**
   - `int8_t`, `uint8_t` - 8-bit integers
   - `int16_t` - 16-bit integers
   - `int32_t`, `uint32_t` - 32-bit integers for sample processing

3. **`<stddef.h>`**
   - `size_t` - Size type for buffer lengths

4. **`<string.h>`**
   - `memset()` - Used in `aptx_reset()` for zeroing context (via manual loop)

### Command-Line Utilities Additional Dependencies

**openaptxenc.c and openaptxdec.c:**
- `<stdio.h>` - File I/O, fprintf, fread, fwrite
- `<fcntl.h>` - File control options
- `<io.h>` - Low-level I/O (Windows-specific for binary mode)
- Platform-specific: Uses `_setmode()`, `_O_BINARY` on Windows

### Test Suite Dependencies

**test.c and tests/*.c:**
- `<stdio.h>` - printf for test output
- `<stdlib.h>` - exit, EXIT_FAILURE

### Build System Dependencies

**From Makefile:**
- Standard POSIX make
- C compiler (cc/gcc/clang)
- Standard utilities: rm, cp, ln, mkdir, printf, ar

### External Library Dependencies

**None** - The core library is completely self-contained with no external dependencies beyond the standard C library.

### Optional Dependencies

**For building/testing:**
- `sox` - Recommended for audio format conversion in examples
- Code coverage tools (gcov/llvm-cov) - For generating coverage reports
- Profiling tools - For .profraw/.profdata generation

### Platform Considerations

- Core library is portable C with no platform-specific code
- Utilities have conditional Windows support (_setmode for binary I/O)
- Suggested compiler flags: `-O3` for optimization, `-mavx2` for SIMD acceleration
- No threading dependencies - single-threaded design
