# Implementation Plan for libtree C to Rust Translation

## Progress Checklist

### PART A: Source Code Translation (29/29 functions)
- [x] Step A.1: Verify skeleton project structure and name mapping
- [x] Step A.2: Implement utility functions (5 functions)
- [x] Step A.3: Implement small_vec_u64 functions (3 functions)
- [x] Step A.4: Implement string_table functions (3 functions)
- [x] Step A.5: Implement visited_files functions (2 functions)
- [x] Step A.6: Implement state management functions (2 functions)
- [x] Step A.7: Implement exclude list function (1 function)
- [x] Step A.8: Implement tree rendering function (1 function)
- [x] Step A.9: Implement path search functions (2 functions)
- [x] Step A.10: Implement print functions (3 functions)
- [x] Step A.11: Implement variable interpolation (1 function)
- [x] Step A.12: Implement config parsing functions (5 functions)
- [x] Step A.13: Implement main recursion function (1 function)
- [x] Step A.14: Implement top-level print_tree function (1 function)
- [x] Step A.15: Implement main binary entry point (1 function in main.rs)

### PART B: Test Translation & Verification (8/8 test functions)
- [x] Step B.1: Translate and execute test helper functions (3 functions)
- [x] Step B.2: Translate and execute main test function (1 function)
- [x] Step B.3: Translate and execute symbol version tests (4 functions)

---

## PART A: Source Code Translation

### Step A.1: Verify skeleton project structure and name mapping

**Description:** Verify that the file structure of the RUST translation exists under data/tool_projects/orbit/libtree-3.1.1/rust and matches the design. Verify that skeleton files (with stubs) exist for all classes/modules. Verify that name-mapping.json exists and contains all required mappings. Verify that the skeleton validation report exists at data/tool_projects/orbit/libtree-3.1.1/planning/skeleton-validation-report.md to confirm the environment is set up correctly.

**Verification Steps:**
1. Confirm rust/ directory structure exists
2. Verify Cargo.toml is present and has correct dependencies
3. Check that name-mapping.json exists with 37 function mappings
4. Read skeleton-validation-report.md to confirm validation passed
5. Run `cargo check` to ensure skeleton compiles (with unimplemented! stubs)

**Expected Result:** All skeleton files present, name mapping complete, project structure validated, cargo check succeeds with warnings about unimplemented functions.

---

### Step A.2: Implement utility functions (5 functions)

**Description:** Implement basic utility functions that have no dependencies on other libtree functions. These are pure functions that can be implemented and tested independently. Use the name-mapping.json file to ensure correct function names are used.

**Functions to translate:**
- c/libtree.c:utoa
- c/libtree.c:host_is_little_endian
- c/libtree.c:is_ascending_order

**Additional implementation notes:**
- `utoa`: Convert to using Rust's `usize::to_string()` standard library method
- `host_is_little_endian`: Use Rust's compile-time `cfg!(target_endian = "little")` macro
- `is_ascending_order`: Implement using Rust iterators and the `windows()` method

**Dependencies:** None (pure utility functions)

**Expected Result:** These functions compile successfully. Add unit tests in `#[cfg(test)]` modules to verify correctness.

---

### Step A.3: Implement small_vec_u64 functions (3 functions)

**Description:** Implement the small vector type that uses stack allocation with heap fallback. This is a self-contained data structure used throughout the codebase. Reference name-mapping.json for function names.

**Functions to translate:**
- c/libtree.c:small_vec_u64_init
- c/libtree.c:small_vec_u64_append
- c/libtree.c:small_vec_u64_free

**Implementation notes:**
- `small_vec_u64_init`: Initialize the struct with stack buffer
- `small_vec_u64_append`: Add elements, switching to heap when stack buffer is full
- `small_vec_u64_free`: Implement as `Drop` trait instead of explicit function (automatic cleanup)
- Add methods: `get()`, `len()`, `push()` for ergonomic API

**Dependencies:** None (self-contained data structure)

**Expected Result:** `small_vec_u64_t` struct is fully functional and automatically manages memory. Compiles without errors.

---

### Step A.4: Implement string_table functions (3 functions)

**Description:** Implement the dynamic string table that stores concatenated null-terminated strings. Use name-mapping.json for consistent naming.

**Functions to translate:**
- c/libtree.c:string_table_maybe_grow
- c/libtree.c:string_table_store
- c/libtree.c:string_table_copy_from_file

**Implementation notes:**
- `string_table_maybe_grow`: Use `Vec::reserve()` for automatic growth
- `string_table_store`: Append string bytes with null terminator
- `string_table_copy_from_file`: Read bytes until null terminator, use generic `Read` trait

**Dependencies:** None (uses only std library)

**Expected Result:** String table operations work correctly, automatic memory management via Vec. Compiles without errors.

---

### Step A.5: Implement visited_files functions (2 functions)

**Description:** Implement functions for tracking visited files to prevent infinite recursion on circular dependencies. Reference name-mapping.json.

**Functions to translate:**
- c/libtree.c:visited_files_contains
- c/libtree.c:visited_files_append

**Implementation notes:**
- `visited_files_contains`: Use `Vec::contains()` or consider `HashSet` for better performance
- `visited_files_append`: Use `Vec::push()`
- Extract `st_dev` and `st_ino` from `std::fs::Metadata` using `std::os::unix::fs::MetadataExt` trait

**Dependencies:** Uses `visited_file_array_t` struct (already defined)

**Expected Result:** Visited file tracking works correctly. Compiles without errors.

---

### Step A.6: Implement state management functions (2 functions)

**Description:** Implement initialization and cleanup for the main state structure. Use name-mapping.json for naming.

**Functions to translate:**
- c/libtree.c:libtree_state_init
- c/libtree.c:libtree_state_free

**Implementation notes:**
- `libtree_state_init`: Return initialized `libtree_state_t` with default values
- Use `std::io::stdout().is_terminal()` for color detection
- Check `NO_COLOR` environment variable
- `libtree_state_free`: Can be removed or implemented as `Drop` trait (automatic cleanup in Rust)

**Dependencies:**
- `string_table_t` (Step A.4)
- `visited_file_array_t` (Step A.5)

**Expected Result:** State initialization works correctly with proper defaults. Compiles without errors.

---

### Step A.7: Implement exclude list function (1 function)

**Description:** Implement the function that checks if a library name is in the exclude list (common system libraries). Use name-mapping.json.

**Functions to translate:**
- c/libtree.c:is_in_exclude_list

**Implementation notes:**
- Define `EXCLUDE_LIST` as a const array of string slices
- Strip version numbers from the soname (trim trailing digits and dots)
- Check if soname starts with any excluded prefix
- Use Rust string methods: `trim_end_matches()`, `starts_with()`

**Dependencies:** None (pure function with const data)

**Expected Result:** Exclude list checking works correctly. Compiles without errors.

---

### Step A.8: Implement tree rendering function (1 function)

**Description:** Implement the function that prints the tree structure preamble (indentation and tree characters). Reference name-mapping.json.

**Functions to translate:**
- c/libtree.c:tree_preamble

**Implementation notes:**
- Use `print!()` macro instead of printf
- Access `found_all_needed` array from state
- Print tree characters: `LIGHT_VERTICAL`, `JUST_INDENT`, etc.

**Dependencies:**
- `libtree_state_t` (Step A.6)
- Tree character constants (already defined)

**Expected Result:** Tree rendering produces correct indentation. Compiles without errors.

---

### Step A.9: Implement path search functions (2 functions)

**Description:** Implement functions that search for libraries in absolute paths and search paths. Use name-mapping.json for naming.

**Functions to translate:**
- c/libtree.c:check_absolute_paths
- c/libtree.c:check_search_paths

**Implementation notes:**
- Use `std::fs::metadata()` to check file existence
- Use `std::path::Path` for path manipulation
- Call `recurse()` recursively when dependencies are found
- Return `LibtreeResult<()>` for error handling
- Parse colon-delimited search paths

**Dependencies:**
- `recurse()` function (Step A.13 - will be called, implement as stub returning Ok(()) initially)
- `small_vec_u64_t` (Step A.3)
- `string_table_t` (Step A.4)
- `visited_files_*` functions (Step A.5)
- `apply_exclude_list()` (implemented in this step)

**Special note:** These functions call `recurse()` which won't be fully implemented until Step A.13. For now, have them compile by calling the `recurse()` stub.

**Expected Result:** Path search logic compiles. Full functionality will be verified once `recurse()` is implemented.

---

### Step A.10: Implement print functions (3 functions)

**Description:** Implement output formatting functions for displaying dependency information and errors. Reference name-mapping.json.

**Functions to translate:**
- c/libtree.c:print_line
- c/libtree.c:print_error
- c/libtree.c:print_colon_delimited_paths

**Implementation notes:**
- Use `print!()` and `println!()` macros
- Use color codes for highlighting when `s.color` is true
- `print_error()` shows all search paths that were attempted
- `print_colon_delimited_paths()` splits on ':' and prints each path

**Dependencies:**
- `tree_preamble()` (Step A.8)
- `found_t`, `how_t` enums (already defined)
- `libtree_state_t` (Step A.6)

**Expected Result:** Output formatting works correctly with colors and tree structure. Compiles without errors.

---

### Step A.11: Implement variable interpolation (1 function)

**Description:** Implement rpath/runpath variable interpolation for $ORIGIN, $LIB, $PLATFORM, etc. Use name-mapping.json.

**Functions to translate:**
- c/libtree.c:interpolate_variables

**Implementation notes:**
- Replace variables in search paths: $ORIGIN, $LIB, $PLATFORM, $OSNAME, $OSREL
- Handle both `$VAR` and `${VAR}` syntax
- Use string replacement operations
- Return `bool` indicating if variables were found/replaced

**Dependencies:**
- `string_table_t` (Step A.4)
- `libtree_state_t` (Step A.6)

**Expected Result:** Variable interpolation works correctly. Compiles without errors.

---

### Step A.12: Implement config parsing functions (3 functions)

**Description:** Implement functions to parse ld.so.conf files and environment variables. Reference name-mapping.json.

**Functions to translate:**
- c/libtree.c:ld_conf_globbing
- c/libtree.c:parse_ld_config_file
- c/libtree.c:parse_ld_library_path
- c/libtree.c:parse_ld_so_conf
- c/libtree.c:set_default_paths

**Implementation notes:**
- `ld_conf_globbing()`: Use `glob` crate for pattern matching
- `parse_ld_config_file()`: Read config file, handle `include` directives, parse paths
- Use `std::io::BufReader` for line-by-line reading
- `parse_ld_library_path()`: Read `LD_LIBRARY_PATH` environment variable
- Use `std::env::var()` for environment access
- `set_default_paths()`: Store default system paths ("/lib:/usr/lib")

**Dependencies:**
- `string_table_t` (Step A.4)
- `libtree_state_t` (Step A.6)
- `glob` crate (already in Cargo.toml)

**Expected Result:** Configuration parsing works correctly. Compiles without errors.

---

### Step A.13: Implement main recursion function (1 function)

**Description:** Implement the core recursive function that parses ELF files and resolves dependencies. This is the most complex function. Use name-mapping.json for naming.

**Functions to translate:**
- c/libtree.c:recurse

**Implementation notes:**
- Use `goblin` crate to parse ELF files instead of manual parsing
- Open file with `std::fs::File::open()`
- Parse ELF with `goblin::elf::Elf::parse()`
- Extract: e_machine, e_type, program headers, dynamic section
- Find PT_DYNAMIC segment and extract DT_NEEDED, DT_RPATH, DT_RUNPATH, DT_SONAME
- Check visited files to prevent cycles
- Call path search functions to resolve dependencies
- Return `LibtreeResult<()>` for error handling

**Dependencies:**
- All previous steps (A.2 through A.12)
- `goblin` crate (already in Cargo.toml)
- `check_absolute_paths()` (Step A.9)
- `check_search_paths()` (Step A.9)
- `print_line()` (Step A.10)
- `print_error()` (Step A.10)
- `interpolate_variables()` (Step A.11)
- `visited_files_*()` (Step A.5)

**Expected Result:** ELF parsing and dependency resolution works. Full recursive traversal is functional. Compiles without errors.

---

### Step A.14: Implement top-level print_tree function (1 function)

**Description:** Implement the main entry point function that initializes state and starts the recursion. Reference name-mapping.json.

**Functions to translate:**
- c/libtree.c:print_tree

**Implementation notes:**
- Call `libtree_state_init()` to create state
- Use `uname` crate to get system information (PLATFORM, OSNAME, OSREL)
- Call config parsing functions: `parse_ld_so_conf()`, `parse_ld_library_path()`, `set_default_paths()`
- Iterate over input paths and call `recurse()` for each
- Return `LibtreeResult<()>`

**Dependencies:**
- `libtree_state_init()` (Step A.6)
- `parse_ld_so_conf()`, `parse_ld_library_path()`, `set_default_paths()` (Step A.12)
- `recurse()` (Step A.13)
- `uname` crate (already in Cargo.toml)

**Expected Result:** Complete library tree can be printed for input binaries. Compiles and runs successfully.

---

### Step A.15: Implement main binary entry point (1 function in main.rs)

**Description:** Implement command-line argument parsing and call print_tree. This completes the binary executable.

**Implementation notes:**
- Parse command-line arguments (consider using `clap` crate or manual parsing)
- Handle flags: `-v` (verbosity), `-p` (show paths), `-a` (show all), `-d` (max depth), `-l` (ld.conf file)
- Call `print_tree()` with the list of input files
- Handle errors and exit codes
- Print usage/help message

**Dependencies:**
- `print_tree()` (Step A.14)

**Expected Result:** Complete libtree binary is functional with all command-line options. Can be run with `cargo run -- <binary>`. Produces output identical to the C version.

---

## PART B: Test Translation & Verification

**Note:** This part focuses on translating and executing tests to verify the Rust implementation matches the C behavior.

### Step B.1: Translate and execute test helper functions (3 functions)

**Description:** Translate the test helper functions that create test ELF files and configuration files. Use name-mapping.json for naming.

**Functions to translate:**
- c/tests/test.c:create_test_elf_file
- c/tests/test.c:create_test_config_file
- c/tests/test.c:create_elf_with_program_headers

**Implementation notes:**
- Use `tempfile` crate for temporary file creation (already in dev-dependencies)
- Write binary ELF data using `std::fs::File::write_all()`
- Create test config files with specific content
- Generate ELF files with valid headers and program headers for testing

**Dependencies:**
- Source implementation (PART A complete)
- `tempfile` crate

**Verification:**
- Run with `cargo test` to ensure helper functions work
- Verify test ELF files are created correctly

**Expected Result:** Test infrastructure compiles and helper functions create valid test files.

---

### Step B.2: Translate and execute main test function (1 function)

**Description:** Translate the main test function that contains all unit tests. Reference name-mapping.json.

**Functions to translate:**
- c/tests/test.c:main

**Implementation notes:**
- Convert C test cases to Rust `#[test]` functions
- Test each libtree function individually:
  - `utoa()` conversion
  - `is_ascending_order()` with various inputs
  - `string_table` operations
  - `small_vec_u64` operations
  - `visited_files` tracking
  - `is_in_exclude_list()` matching
  - ELF parsing with various valid/invalid files
  - Config file parsing
  - Variable interpolation
- Use `assert!()` and `assert_eq!()` macros
- Each C test case becomes a separate Rust test function

**Dependencies:**
- All source functions (PART A)
- Test helpers (Step B.1)

**Verification:**
- Run with `cargo test`
- All tests should pass
- Compare output with C test results

**Expected Result:** All unit tests pass, verifying correct behavior of individual functions.

---

### Step B.3: Translate and execute symbol version tests (4 functions)

**Description:** Translate the symbol versioning test files. Use name-mapping.json for naming.

**Functions to translate:**
- c/tests/06_symbol_versions/main.c:main
- c/tests/06_symbol_versions/v1.c:xyz
- c/tests/06_symbol_versions/v2.c:xyz_old
- c/tests/06_symbol_versions/v2.c:xyz_new

**Implementation notes:**
- These tests verify that libtree correctly handles symbol versioning in shared libraries
- Create test shared libraries with versioned symbols
- Run libtree on test binaries that depend on these libraries
- Verify correct dependency resolution with symbol versions

**Dependencies:**
- All source functions (PART A)
- Test infrastructure (Steps B.1-B.2)

**Verification:**
- Build test shared libraries with `rustc --crate-type=dylib`
- Run libtree on test binaries
- Compare output with expected results
- Verify symbol versions are correctly displayed

**Expected Result:** Symbol versioning tests pass, demonstrating correct handling of versioned dependencies.

---

## Summary

This implementation plan provides a systematic, bottom-up approach to translating the libtree C project to Rust:

- **Part A** translates all 29 source functions in 15 steps, building from simple utilities to complex ELF parsing
- **Part B** translates all 8 test functions in 3 steps, ensuring correctness through comprehensive testing
- Each step results in compilable code
- Dependencies are satisfied before dependent code is implemented
- The name-mapping.json file is referenced throughout to ensure consistent naming
- Rust idioms (Result, Option, iterators, Drop trait) are used appropriately
- The final implementation maintains 1:1 functional equivalence with the C version

The translation can proceed incrementally, with each step validated before moving to the next.
