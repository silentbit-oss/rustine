# Implementation Plan for libcsv C to Rust Translation

## Progress Checklist

### PART A: Source Code Translation (For Translator Agent)
- [x] A.1: Verify skeleton project structure and name mapping
- [x] A.2: Implement error handling and utility functions
- [x] A.3: Implement parser initialization and configuration
- [x] A.4: Implement buffer management
- [x] A.5: Implement core parsing logic
- [x] A.6: Implement finalization logic
- [x] A.7: Implement CSV writing functions
- [x] A.8: Verify compilation of core library

### PART B: Test Translation & Verification (For Validator Agent)
- [x] B.1: Implement test infrastructure
- [x] B.2: Run all parser tests
- [x] B.3: Run all writer tests
- [x] B.4: Implement and test example programs
- [x] B.5: Final validation

---

## PART A: Source Code Translation

### Step A.1: Verify skeleton project structure and name mapping

**Description:** Verify that the file structure of the RUST translation exists under data/tool_projects/orbit/libcsv/rust and matches the design. Verify that skeleton files (with stubs) exist for all classes/modules. Verify that name-mapping.json exists and contains all required mappings. Verify that the skeleton validation report exists at data/tool_projects/orbit/libcsv/planning/skeleton-validation-report.md to confirm the environment is set up correctly.

**Functions and methods to verify:**
- All 42 functions listed in c-functions.md should have mappings in name-mapping.json
- All skeleton files should exist with unimplemented!() stubs

---

### Step A.2: Implement error handling and utility functions

**Description:** Implement the foundational error handling and utility functions that have no dependencies. These functions are simple getters and setters that don't depend on other functions. All function names must use the exact names from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_error
- libcsv.c:csv_strerror (note: csv_errors array is already defined in C as a constant array)
- libcsv.c:csv_get_opts
- libcsv.c:csv_set_opts
- libcsv.c:csv_set_delim
- libcsv.c:csv_set_quote
- libcsv.c:csv_get_delim
- libcsv.c:csv_get_quote
- libcsv.c:csv_set_space_func
- libcsv.c:csv_set_term_func
- libcsv.c:csv_set_realloc_func
- libcsv.c:csv_set_free_func
- libcsv.c:csv_set_blk_size
- libcsv.c:csv_get_buffer_size

**Dependencies:** None (these are simple getters/setters)

**Notes:**
- Use name-mapping.json to ensure correct function names
- csv_strerror uses a const array csv_errors defined at the top of libcsv.c
- All functions should preserve C semantics exactly

---

### Step A.3: Implement parser initialization and configuration

**Description:** Implement csv_init and csv_free which set up and tear down the parser state. These functions initialize the csv_parser struct fields and manage the entry buffer. Use exact function names from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_init
- libcsv.c:csv_free

**Dependencies:**
- Depends on csv_parser struct being defined (already in skeleton)
- csv_free uses free_func if set (already handled by Rust's Drop trait for Vec)

**Notes:**
- csv_init sets default values for all parser fields
- csv_free deallocates the entry_buf (in Rust, Vec handles this automatically)
- Must preserve exact field initialization order and values from C

---

### Step A.4: Implement buffer management

**Description:** Implement the internal buffer management function csv_increase_buffer. This function grows the entry_buf when more space is needed during parsing. This is critical for csv_parse to work. Use exact function name from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_increase_buffer

**Dependencies:**
- Depends on csv_parser struct having entry_buf (Vec<u8>)
- No other function dependencies

**Notes:**
- Original C uses realloc with exponential growth strategy
- Rust translation should use Vec::reserve() and Vec::resize()
- Must handle CSV_ENOMEM and CSV_ETOOBIG errors
- Growth strategy: try full blk_size, if fails, halve size repeatedly

---

### Step A.5: Implement core parsing logic

**Description:** Implement the main csv_parse function which processes CSV data incrementally using a state machine. This is the most complex function in the library. It uses macros SUBMIT_FIELD, SUBMIT_ROW, and SUBMIT_CHAR which should be translated to inline functions or kept as macros. Use exact function name from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_parse

**Dependencies:**
- Depends on csv_increase_buffer (Step A.4)
- Uses SUBMIT_FIELD, SUBMIT_ROW, SUBMIT_CHAR macros (translate to Rust equivalents)
- Uses parser state constants (ROW_NOT_BEGUN, FIELD_NOT_BEGUN, etc.)

**Notes:**
- State machine with 4 states: ROW_NOT_BEGUN, FIELD_NOT_BEGUN, FIELD_BEGUN, FIELD_MIGHT_HAVE_ENDED
- Handles quoted fields, delimiters, spaces, terminators
- Invokes callbacks cb1 (field) and cb2 (row)
- Local variable optimization: copy frequently accessed struct fields to local variables
- Must preserve exact parsing behavior including edge cases

---

### Step A.6: Implement finalization logic

**Description:** Implement csv_fini which finalizes parsing when input ends. This handles the case where the CSV data doesn't end with a newline. Use exact function name from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_fini

**Dependencies:**
- Depends on SUBMIT_FIELD and SUBMIT_ROW macros/functions (used in csv_parse, Step A.5)
- Must be implemented after csv_parse since they share macro logic

**Notes:**
- Handles unterminated quoted fields
- Submits final field and row if needed
- Resets parser state
- Respects CSV_STRICT_FINI option

---

### Step A.7: Implement CSV writing functions

**Description:** Implement the CSV writing functions which take raw data and output properly quoted and escaped CSV format. These functions have no dependencies on parsing logic. Use exact function names from name-mapping.json.

**Functions and methods to translate:**
- libcsv.c:csv_write
- libcsv.c:csv_fwrite
- libcsv.c:csv_write2
- libcsv.c:csv_fwrite2

**Dependencies:**
- No dependencies on other functions
- csv_write calls csv_write2 internally
- csv_fwrite calls csv_fwrite2 internally

**Notes:**
- csv_write and csv_fwrite use default quote character (CSV_QUOTE)
- csv_write2 and csv_fwrite2 allow custom quote character
- Must properly escape quotes by doubling them
- Buffer size checking for csv_write/csv_write2
- File I/O for csv_fwrite/csv_fwrite2

---

### Step A.8: Verify compilation of core library

**Description:** Verify that the core library (src/lib.rs) compiles successfully without errors or warnings. Run cargo build and cargo clippy to ensure code quality.

**Verification steps:**
1. Run `cargo build --lib` to compile the library
2. Run `cargo clippy -- -D warnings` to check for warnings
3. Verify no compilation errors or warnings
4. Fix any issues found

**Notes:**
- This step does not run tests yet (tests are in PART B)
- Ensures all source code is syntactically correct and type-safe
- All function implementations should be complete at this point

---

## PART B: Test Translation & Verification

### Step B.1: Implement test infrastructure

**Description:** Translate the test infrastructure from test_csv.c to test_csv.rs. This includes the event structure, test helper functions, and callback functions used by the test framework. Use exact function names from name-mapping.json.

**Tests to translate and execute:**
- test_csv.c:event struct
- test_csv.c:fail_parser
- test_csv.c:fail_writer
- test_csv.c:cb1 (field callback for tests)
- test_csv.c:cb2 (row callback for tests)
- test_csv.c:test_parser
- test_csv.c:test_writer
- test_csv.c:test_writer2

**Dependencies:**
- Depends on core library (all of PART A)

**Verification:**
1. Compile test_csv binary: `cargo build --bin test_csv`
2. Verify test infrastructure compiles

**Notes:**
- Event structure tracks expected vs actual parsing results
- Callbacks accumulate events for comparison
- Test helper functions compare actual vs expected events

---

### Step B.2: Run all parser tests

**Description:** Translate all parser test cases from test_csv.c main function and execute them. Each test case verifies specific parsing behavior (quoted fields, empty fields, strict mode, options, etc.). Use exact function names from name-mapping.json.

**Tests to implement in test_csv.c:main:**
- test01: Basic parsing "1,2 ,  3         ,4,5\r\n"
- test02: Empty fields ",,,,,\n"
- test03: Quoted commas "\",\",\",\",\"\""
- test04: Multiline quoted field
- test05: Escaped quotes
- test06: Quoted field with spaces
- test07a: Non-quoted field with double quote (non-strict)
- test07b: Non-quoted field with double quote (strict mode - should error)
- test08: Empty input ""
- test09: Newline in quoted field
- test10: CR LF handling
- test11a: Space after quote (non-strict)
- test11b: Space after quote (strict)
- test12a: CSV_REPALL_NL option disabled
- test12b: CSV_REPALL_NL option enabled
- test13: Delimiter edge cases
- test14: Custom delimiter (tab)
- test15: Custom quote character
- test16a: CSV_STRICT_FINI disabled
- test16b: CSV_STRICT_FINI enabled
- test17: CSV_APPEND_NULL option
- test18: Custom space function
- test19: CSV_EMPTY_IS_NULL option
- test20+: Any additional test cases in test_csv.c

**Verification:**
1. Run `cargo run --bin test_csv`
2. All tests should pass (output "All tests passed!")
3. If any test fails, debug and fix the issue

**Dependencies:**
- Depends on test infrastructure (Step B.1)
- Depends on csv_parse and all parsing functions (PART A)

**Notes:**
- Tests use test data files in tests/ directory
- Each test verifies specific CSV parsing edge cases
- Must match exact behavior of C implementation

---

### Step B.3: Run all writer tests

**Description:** Translate and execute all writer test cases which verify CSV writing functionality (proper quoting and escaping).

**Writer tests to implement:**
- writer_test01: Basic writing with quotes
- writer_test02: Writing with embedded quotes (escaping)
- writer_test03: Writing empty strings
- writer_test04: Writing with custom quote character
- writer_test05+: Any additional writer tests

**Verification:**
1. Run `cargo run --bin test_csv` (includes writer tests)
2. All writer tests should pass
3. Verify output matches expected format

**Dependencies:**
- Depends on test infrastructure (Step B.1)
- Depends on csv_write* functions (Step A.7)

---

### Step B.4: Implement and test example programs

**Description:** Translate the example programs (csvfix, csvinfo, csvtest, csvvalid) and verify they work correctly with test CSV files. Use exact function names from name-mapping.json.

**Examples to translate and test:**

**csvfix.rs:**
- examples/csvfix.c:cb1
- examples/csvfix.c:cb2
- examples/csvfix.c:main

**csvinfo.rs:**
- examples/csvinfo.c:cb1
- examples/csvinfo.c:cb2
- examples/csvinfo.c:is_space
- examples/csvinfo.c:is_term
- examples/csvinfo.c:main

**csvtest.rs:**
- examples/csvtest.c:cb1
- examples/csvtest.c:cb2
- examples/csvtest.c:main

**csvvalid.rs:**
- examples/csvvalid.c:main

**Verification:**
1. Build examples: `cargo build --examples`
2. Run csvinfo: `cargo run --example csvinfo -- tests/test_01.csv`
3. Run csvtest: `cargo run --example csvtest`
4. Run csvfix: `cargo run --example csvfix -- tests/test_01.csv > output.csv`
5. Run csvvalid: `cargo run --example csvvalid -- tests/test_01.csv`
6. Verify output matches expected behavior

**Dependencies:**
- Depends on all core library functions (PART A)
- Uses test CSV files in tests/ directory

**Notes:**
- Examples demonstrate library usage
- Verify output format matches C version
- csvinfo counts fields and rows
- csvtest tests basic parsing
- csvfix reads and writes CSV (fixing format)
- csvvalid validates CSV format

---

### Step B.5: Final validation

**Description:** Perform final comprehensive validation of the complete translation.

**Validation steps:**
1. Run `cargo build --release` - verify clean build with no warnings
2. Run `cargo clippy -- -D warnings` - verify no clippy warnings
3. Run `cargo test` - verify any unit tests pass
4. Run `cargo run --bin test_csv` - verify all tests pass
5. Run all examples with test data files
6. Compare behavior with original C implementation
7. Verify all 42 functions are implemented (no unimplemented!() remaining)

**Success criteria:**
- All 42 functions fully implemented
- Zero compilation warnings or errors
- All test cases pass
- All examples work correctly
- Behavior matches C implementation exactly

---

## Notes

### Name Mapping
- **CRITICAL**: All function implementations MUST use the exact names specified in name-mapping.json
- Verify function names match before implementing each step
- No renaming or case conversions allowed

### Implementation Order
- PART A must be completed sequentially (steps A.1 through A.8)
- Each step in PART A builds on previous steps
- PART B can only start after PART A is complete
- Steps within PART B should be done in order

### Testing Strategy
- PART A focuses on implementation and compilation only
- PART B focuses on testing and verification
- No tests should be run until all of PART A is complete

### Error Handling
- Preserve exact C error handling behavior
- Use integer error codes (CSV_SUCCESS, CSV_EPARSE, etc.)
- Store errors in parser status field
- No panics - all errors returned as codes

### Memory Management
- Replace malloc/realloc/free with Vec operations
- Vec automatically handles deallocation
- Preserve buffer growth strategy from C
- No manual memory management needed in Rust

### Compilation Verification
- After each step, verify code compiles: `cargo build --lib`
- Fix any errors before proceeding to next step
- Use `cargo clippy` to catch potential issues early
