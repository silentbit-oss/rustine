# Implementation Plan for libopenaptx Rust Translation

## Overview

This plan details the step-by-step implementation of the libopenaptx C to Rust translation. The translation follows a "bottom-up" approach, implementing lower-level utility functions first, then building up to higher-level codec functionality. The plan is divided into two parts:
- **PART A**: Source code translation (for Translator Agent)
- **PART B**: Test translation and verification (for Validator Agent)

## Implementation Progress Checklist

### PART A: Source Code Translation
- [x] A.1: Verify skeleton project structure and name mapping
- [x] A.2: Translate constants and lookup tables
- [x] A.3: Translate basic utility functions
- [x] A.4: Translate filter and signal processing functions
- [x] A.5: Translate QMF analysis and synthesis functions
- [x] A.6: Translate quantization functions
- [x] A.7: Translate prediction and inversion functions
- [x] A.8: Translate encoding and decoding functions
- [x] A.9: Translate packing and synchronization functions
- [x] A.10: Translate public API functions
- [x] A.11: Translate encoder utility (openaptxenc)
- [x] A.12: Translate decoder utility (openaptxdec)

### PART B: Test Translation & Verification
- [x] B.1: Translate and execute basic tests (test.rs)
- [x] B.2: Translate and execute padding tests (test_padding.rs)
- [x] B.3: Translate and execute roundtrip tests (test_roundtrip.rs)

---

## PART A: Source Code Translation

### Step A.1: Verify skeleton project structure and name mapping

**Description:** Verify that the file structure of the RUST translation exists under data/tool_projects/orbit/libopenaptx/rust and matches the design. Verify that skeleton files (with stubs) exist for all classes/modules. Verify that name-mapping.json exists and contains all required mappings. Verify that the skeleton validation report exists at data/tool_projects/orbit/libopenaptx/planning/skeleton-validation-report.md to confirm the environment is set up correctly.

**Functions to translate:** None (verification only)

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Expected Outcome:** Confirmation that all skeleton files exist, Cargo.toml is configured correctly, and the project structure matches the design document.

---

### Step A.2: Translate constants and lookup tables

**Description:** Translate all constants and static lookup tables from openaptx.c to src/openaptx.rs. This includes version constants, codec constants (NB_CHANNELS, NB_SUBBANDS, etc.), and all quantization/dither lookup tables. These are foundational data structures with no dependencies.

**Functions to translate:**
- Static constants: OPENAPTX_MAJOR, OPENAPTX_MINOR, OPENAPTX_PATCH
- Public version globals: aptx_major, aptx_minor, aptx_patch
- Codec constants: NB_CHANNELS, NB_SUBBANDS, NB_FILTERS, FILTER_TAPS, LATENCY_SAMPLES
- Lookup tables:
  - quantize_intervals_LF, quantize_intervals_MLF, quantize_intervals_MHF, quantize_intervals_HF
  - invert_quantize_dither_factors_LF/MLF/MHF/HF
  - quantize_dither_factors_LF/MLF/MHF/HF
  - quantize_factor_select_offset_LF/MLF/MHF/HF
  - QMF filter coefficient tables (if present in C source)

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Implementation Notes:**
- Use `const` for compile-time constants
- Use `static` for lookup tables
- Ensure array sizes match C exactly
- Preserve exact numeric values from C

**Expected Outcome:** All constants and tables are defined, project compiles (with unimplemented functions), cargo check passes.

---

### Step A.3: Translate basic utility functions

**Description:** Translate the foundational utility functions that have no dependencies. These are pure functions used throughout the codec.

**Functions to translate:**
- openaptx.c:clip_intp2
- openaptx.c:clip
- openaptx.c:sign_extend

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Implementation Notes:**
- Use Rust's type system for safety
- Use wrapping arithmetic where needed to match C overflow behavior
- Add `#[inline]` annotations for performance
- Preserve exact C semantics for bit manipulation

**Expected Outcome:** All three utility functions are implemented and pass basic unit tests. Project compiles successfully.

---

### Step A.4: Translate filter and signal processing functions

**Description:** Translate the QMF filter signal management functions. These functions manipulate the aptx_filter_signal structure.

**Functions to translate:**
- openaptx.c:aptx_qmf_filter_signal_push
- openaptx.c:aptx_qmf_convolution

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- aptx_filter_signal struct (already defined in skeleton)

**Implementation Notes:**
- Use Rust slices for array access with bounds checking
- Ensure circular buffer logic is correct
- Use wrapping arithmetic for integer operations

**Expected Outcome:** Filter signal functions are implemented. Project compiles successfully.

---

### Step A.5: Translate QMF analysis and synthesis functions

**Description:** Translate the QMF (Quadrature Mirror Filter) tree analysis and synthesis functions. These are the core DSP functions for frequency decomposition and reconstruction.

**Functions to translate:**
- openaptx.c:aptx_qmf_polyphase_analysis
- openaptx.c:aptx_qmf_tree_analysis
- openaptx.c:aptx_qmf_polyphase_synthesis
- openaptx.c:aptx_qmf_tree_synthesis

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- clip_intp2 (from A.3)
- aptx_qmf_filter_signal_push (from A.4)
- aptx_qmf_convolution (from A.4)
- QMF coefficient tables (from A.2)

**Implementation Notes:**
- These are computationally intensive functions
- Use wrapping arithmetic for fixed-point operations
- Ensure filter bank structure is correctly implemented

**Expected Outcome:** QMF analysis and synthesis functions are implemented. Project compiles successfully.

---

### Step A.6: Translate quantization functions

**Description:** Translate the quantization and binary search functions used in encoding.

**Functions to translate:**
- openaptx.c:aptx_bin_search
- openaptx.c:aptx_quantize_difference

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- clip (from A.3)
- clip_intp2 (from A.3)
- Quantization lookup tables (from A.2)

**Implementation Notes:**
- Binary search must handle edge cases correctly
- Quantization uses lookup tables from A.2
- Use wrapping arithmetic for dither calculations

**Expected Outcome:** Quantization functions are implemented. Project compiles successfully.

---

### Step A.7: Translate prediction and inversion functions

**Description:** Translate the inverse quantization and prediction filtering functions used in decoding.

**Functions to translate:**
- openaptx.c:aptx_invert_quantization
- openaptx.c:aptx_prediction_filtering
- openaptx.c:aptx_process_subband

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- clip (from A.3)
- sign_extend (from A.3)
- Inversion lookup tables (from A.2)

**Implementation Notes:**
- Prediction uses adaptive filtering
- Carefully implement weight updates
- Use wrapping arithmetic for accumulation

**Expected Outcome:** Prediction and inversion functions are implemented. Project compiles successfully.

---

### Step A.8: Translate encoding and decoding functions

**Description:** Translate the mid-level encoding and decoding functions that process subbands and channels.

**Functions to translate:**
- openaptx.c:aptx_update_codeword_history
- openaptx.c:aptx_generate_dither
- openaptx.c:aptx_encode_channel
- openaptx.c:aptx_decode_channel
- openaptx.c:aptx_invert_quantize_and_prediction

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- aptx_qmf_tree_analysis (from A.5)
- aptx_qmf_tree_synthesis (from A.5)
- aptx_quantize_difference (from A.6)
- aptx_invert_quantization (from A.7)
- aptx_prediction_filtering (from A.7)
- aptx_process_subband (from A.7)

**Implementation Notes:**
- Dither generation uses PRNG-like algorithm
- Channel encoding processes all subbands
- Channel decoding reconstructs samples

**Expected Outcome:** Channel encoding and decoding functions are implemented. Project compiles successfully.

---

### Step A.9: Translate packing and synchronization functions

**Description:** Translate functions that pack/unpack codewords and handle synchronization.

**Functions to translate:**
- openaptx.c:aptx_quantized_parity
- openaptx.c:aptx_check_parity
- openaptx.c:aptx_insert_sync
- openaptx.c:aptx_pack_codeword
- openaptx.c:aptxhd_pack_codeword
- openaptx.c:aptx_unpack_codeword
- openaptx.c:aptxhd_unpack_codeword

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- None (bit manipulation only)

**Implementation Notes:**
- Careful bit packing for aptX (16-bit) vs aptX HD (24-bit)
- Parity checks for error detection
- Sync insertion for stream synchronization

**Expected Outcome:** Packing and synchronization functions are implemented. Project compiles successfully.

---

### Step A.10: Translate public API functions

**Description:** Translate the main public API functions and sample processing functions.

**Functions to translate:**
- openaptx.c:aptx_encode_samples
- openaptx.c:aptx_decode_samples
- openaptx.c:aptx_reset_decode_sync
- openaptx.c:aptx_reset
- openaptx.c:aptx_finish
- openaptx.c:aptx_encode
- openaptx.c:aptx_encode_finish
- openaptx.c:aptx_decode
- openaptx.c:aptx_decode_sync
- openaptx.c:aptx_decode_sync_finish

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- aptx_encode_channel (from A.8)
- aptx_decode_channel (from A.8)
- aptx_pack_codeword (from A.9)
- aptxhd_pack_codeword (from A.9)
- aptx_unpack_codeword (from A.9)
- aptxhd_unpack_codeword (from A.9)
- aptx_check_parity (from A.9)
- aptx_insert_sync (from A.9)

**Implementation Notes:**
- aptx_init allocates and initializes context (use Box::new)
- aptx_finish deallocates context (handled by Drop)
- aptx_reset clears internal state
- Encode/decode functions handle buffering and frame alignment
- aptx_decode_sync handles corrupted streams with auto-synchronization

**Expected Outcome:** All public API functions are implemented. The library is functionally complete. Project compiles and builds successfully. Basic smoke tests can run.

---

### Step A.11: Translate encoder utility (openaptxenc)

**Description:** Translate the command-line encoder utility that reads raw audio from stdin and writes aptX to stdout.

**Functions to translate:**
- openaptxenc.c:main

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- All public API functions from openaptx module (A.10)

**Implementation Notes:**
- Use std::io for stdin/stdout
- Parse command-line arguments (HD mode flag)
- Handle binary I/O correctly
- Use Result<()> for error propagation
- Match C behavior for exit codes

**Expected Outcome:** Encoder binary compiles and runs. Can encode raw audio to aptX format.

---

### Step A.12: Translate decoder utility (openaptxdec)

**Description:** Translate the command-line decoder utility that reads aptX from stdin and writes raw audio to stdout.

**Functions to translate:**
- openaptxdec.c:main

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- All public API functions from openaptx module (A.10)

**Implementation Notes:**
- Use std::io for stdin/stdout
- Parse command-line arguments (HD mode flag, sync mode flag)
- Handle binary I/O correctly
- Use Result<()> for error propagation
- Support both normal and sync decoding modes
- Match C behavior for exit codes

**Expected Outcome:** Decoder binary compiles and runs. Can decode aptX format to raw audio. Source code translation is complete.

---

## PART B: Test Translation & Verification

### Step B.1: Translate and execute basic tests (test.rs)

**Description:** Translate the basic test suite from test.c to tests/test.rs and execute tests to verify core functionality.

**Tests to translate and execute:**
- test.c:assert_true
- test.c:test_aptx_encode_decode_various
- test.c:test_aptx_hd_mode
- test.c:test_aptx_decode_sync
- test.c:test_aptx_invalid_inputs
- test.c:main

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Implementation Notes:**
- Convert C test functions to Rust #[test] functions
- Use Rust assert! and assert_eq! macros
- Main function can be kept for manual test execution
- Each test should verify correctness of the public API

**Expected Outcome:** All basic tests pass. Core codec functionality is verified.

---

### Step B.2: Translate and execute padding tests (test_padding.rs)

**Description:** Translate encoding padding tests from tests/test_padding.c and execute them.

**Tests to translate and execute:**
- tests/test_padding.c:test_encode_padding

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- Public API functions (implemented in A.10)

**Implementation Notes:**
- Verify that encode_finish properly pads the stream
- Ensure latency compensation works correctly

**Expected Outcome:** Padding test passes. Encoding latency is correctly handled.

---

### Step B.3: Translate and execute roundtrip tests (test_roundtrip.rs)

**Description:** Translate roundtrip encode/decode tests from tests/test_roundtrip.c and execute them.

**Tests to translate and execute:**
- tests/test_roundtrip.c:test_roundtrip
- tests/test_roundtrip.c:test_roundtrip_classic
- tests/test_roundtrip.c:test_roundtrip_hd

**Name Mapping Reference:** data/tool_projects/orbit/libopenaptx/planning/name-mapping.json

**Dependencies:**
- Public API functions (implemented in A.10)

**Implementation Notes:**
- Verify that encoding then decoding recovers original samples (within codec precision)
- Test both aptX classic and aptX HD modes
- Compare output with expected results

**Expected Outcome:** All roundtrip tests pass. Translation is verified to be functionally correct. Project is complete.

---

## Implementation Guidelines

### General Principles
1. **Follow name-mapping.json exactly** - All function and type names must match the mapping
2. **Preserve C semantics** - Use wrapping arithmetic, match overflow behavior
3. **1:1 translation** - Do not add features or refactor beyond language requirements
4. **Compile after each step** - Ensure code compiles before moving to next step
5. **Test incrementally** - Verify each component works before building on it

### Rust-Specific Considerations
- Use `wrapping_add()`, `wrapping_sub()`, `wrapping_mul()` for arithmetic
- Add `#[inline]` to hot functions (signal processing, quantization)
- Use slices `&[T]` instead of pointers where safe
- Use `Box<aptx_context>` for heap-allocated context
- Implement `Default` trait for zero-initialization of structs

### Error Handling
- Public API maintains C semantics (Option, return codes)
- Internal functions can use Rust idioms
- No panics in production code paths

### Testing Strategy
- Unit tests for individual functions (inline in modules)
- Integration tests in tests/ directory
- Compare output with C implementation where possible

## Completion Criteria

The translation is complete when:
1. ✅ All functions from PART A are implemented
2. ✅ All functions from PART B are implemented and tests pass
3. ✅ Project compiles without warnings (cargo build --release)
4. ✅ All tests pass (cargo test)
5. ✅ Binaries run successfully (cargo run --bin openaptxenc/openaptxdec)
6. ✅ Output matches C implementation for same inputs
