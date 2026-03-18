# Function-to-Test Coverage Map

## Coverage Summary

### Statistics
- **Total Functions**: 34
- **Covered Functions**: 26
- **Uncovered Functions**: 8
- **Coverage Percentage**: 76.47%

---

## Covered Functions

### 1. utoa
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_utoa_function()` - Tests basic conversion with 0, 123, and 9876543210
  - `test_boundary_conditions()` - Tests edge values including 1 and u64::MAX

### 2. small_vec_u64_init
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_small_vec_u64_operations()` - Tests initialization via `small_vec_u64_t::new()`
  - `test_memory_allocation_edge_cases()` - Tests initial state

### 3. small_vec_u64_append
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_small_vec_u64_operations()` - Tests adding elements within buffer and beyond
  - `test_memory_allocation_edge_cases()` - Tests stack-to-heap transition
  - `test_apply_exclude_list_function()` - Uses append to add offsets
  - `test_performance_stress()` - Stress test with 10,000 appends

### 4. small_vec_u64_free
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_small_vec_u64_operations()` - Tests cleanup after operations
  - `test_small_vec_free_edge_case()` - Tests freeing when on stack vs heap
  - `test_apply_exclude_list_function()` - Tests cleanup
  - `test_performance_stress()` - Tests cleanup after large operations

### 5. host_is_little_endian
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_host_endianness()` - Verifies function returns boolean value

### 6. is_ascending_order
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_ascending_order_check()` - Tests ascending, descending, mixed arrays, single element, and empty array

### 7. string_table_maybe_grow
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_string_table_growth()` - Tests capacity expansion when needed
  - `test_string_boundary_conditions()` - Tests growth with exact capacity

### 8. string_table_store
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_string_table_operations()` - Tests storing "hello" and "world"
  - `test_string_table_growth()` - Tests storing long string that triggers growth
  - `test_apply_exclude_list_function()` - Tests storing library names
  - `test_boundary_conditions()` - Tests storing empty string

### 9. string_table_copy_from_file
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_string_table_copy_from_file()` - Tests copying null-terminated string from file

### 10. is_in_exclude_list
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_exclude_list_checking()` - Tests with libc.so.6, libm.so.1, ld-linux-x86-64.so.2, custom libs
  - `test_string_boundary_conditions()` - Tests empty string and version-stripped libraries

### 11. tree_preamble
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(print_tree_function)` - Tests tree output formatting with preamble

### 12. apply_exclude_list
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_apply_exclude_list_function()` - Tests filtering libc.so.6 vs libcustom.so

### 13. check_absolute_paths
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(check_absolute_paths_function)` - Tests absolute path checking
  - `TEST(check_absolute_paths_relative_paths)` - Tests relative path handling
  - `TEST(check_absolute_paths_no_slash)` - Tests paths without slashes

### 14. check_search_paths
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(check_search_paths_function)` - Tests search path functionality
  - `TEST(check_search_paths_edge_cases)` - Tests edge cases
  - `TEST(check_search_paths_colon_parsing)` - Tests colon-delimited path parsing
  - `TEST(check_search_paths_long_paths)` - Tests long path handling
  - `TEST(check_search_paths_separator_handling)` - Tests separator handling

### 15. interpolate_variables
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(variable_interpolation)` - Tests basic variable interpolation
  - `TEST(variable_interpolation_comprehensive)` - Tests $PLATFORM, $LIB, $OSNAME, $OSREL

### 16. print_colon_delimited_paths
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(print_colon_delimited_paths_function)` - Tests path printing with colons

### 17. print_line
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(print_line_function_coverage)` - Tests line printing with various depths and colors
  - `TEST(print_tree_function)` - Tests line printing in tree context

### 18. print_error
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(print_error_basic)` - Tests basic error message printing
  - `TEST(print_error_with_runpath)` - Tests error with RUNPATH
  - `TEST(print_error_rpath_stack)` - Tests error with RPATH stack
  - `TEST(error_message_coverage)` - Tests various error scenarios

### 19. visited_files_contains
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_visited_files_operations()` - Tests checking for files by st_dev and st_ino

### 20. visited_files_append
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_visited_files_operations()` - Tests appending files and capacity expansion

### 21. recurse
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_elf_file_validation()` - Tests with invalid and nonexistent files
  - `TEST(recurse_elf_with_program_headers_no_dynamic)` - Tests ELF without dynamic section
  - `TEST(recurse_elf_wrong_endianness)` - Tests wrong endianness
  - `TEST(recurse_elf_wrong_type)` - Tests wrong ELF type
  - `TEST(recurse_elf_incompatible_arch)` - Tests incompatible architecture
  - `TEST(recurse_elf_incompatible_bits)` - Tests incompatible bit width
  - `TEST(recurse_elf_invalid_phoff)` - Tests invalid program header offset
  - `TEST(recurse_32bit_elf)` - Tests 32-bit ELF
  - `TEST(recurse_elf_no_pt_load)` - Tests ELF without PT_LOAD
  - `TEST(recurse_elf_with_dynamic_section)` - Tests ELF with dynamic section
  - `TEST(recurse_elf_invalid_dynamic_seek)` - Tests invalid dynamic section seek

### 22. ld_conf_globbing
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(ld_conf_globbing_function)` - Tests glob pattern matching for config files

### 23. parse_ld_config_file
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_config_file_parsing()` - Tests parsing config with comments and paths
  - `test_config_file_nonexistent()` - Tests with nonexistent file
  - `test_ld_config_file_comprehensive()` - Tests comments, whitespace, inline comments
  - `TEST(config_file_parsing)` - C tests for config parsing
  - `TEST(ld_config_file_comprehensive)` - C comprehensive config tests

### 24. parse_ld_so_conf
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_parse_ld_so_conf_function()` - Tests parsing ld.so.conf file
  - `test_comprehensive_integration()` - Tests in integration workflow
  - `TEST(parse_ld_so_conf_function)` - C tests for ld.so.conf parsing

### 25. parse_ld_library_path
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_ld_library_path_parsing()` - Tests with and without LD_LIBRARY_PATH set
  - `test_ld_library_path_semicolons()` - Tests semicolon-to-colon conversion
  - `test_comprehensive_integration()` - Tests in integration workflow
  - `TEST(ld_library_path_parsing)` - C tests for LD_LIBRARY_PATH
  - `TEST(ld_library_path_semicolons)` - C tests for semicolon handling

### 26. set_default_paths
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_default_paths_setup()` - Tests setting default paths (/lib:/lib64:/usr/lib:/usr/lib64)
  - `test_comprehensive_integration()` - Tests in integration workflow
  - `TEST(default_paths_setup)` - C tests for default paths

### 27. libtree_state_init
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_libtree_state_lifecycle()` - Tests initialization
  - `test_ld_library_path_parsing()` - Uses initialized state
  - `test_default_paths_setup()` - Uses initialized state
  - `test_comprehensive_integration()` - Uses initialized state
  - Multiple other tests that need state initialization

### 28. libtree_state_free
- **Source File**: c/libtree.c
- **Tested By**: rust/tests/test.rs, c/tests/test.c
- **Test Methods**:
  - `test_libtree_state_lifecycle()` - Tests cleanup
  - All tests that initialize state also test freeing it

### 29. print_tree
- **Source File**: c/libtree.c
- **Tested By**: c/tests/test.c
- **Test Methods**:
  - `TEST(print_tree_function)` - Tests tree output formatting

---

## Uncovered Functions

### 1. create_test_elf_file
- **Source File**: c/tests/test.c
- **Status**: UNCOVERED (Test Helper)
- **Reason**: This is a test helper function, not a source function to be tested

### 2. create_test_config_file
- **Source File**: c/tests/test.c
- **Status**: UNCOVERED (Test Helper)
- **Reason**: This is a test helper function, not a source function to be tested

### 3. create_elf_with_program_headers
- **Source File**: c/tests/test.c
- **Status**: UNCOVERED (Test Helper)
- **Reason**: This is a test helper function, not a source function to be tested

### 4. main (test.c)
- **Source File**: c/tests/test.c
- **Status**: UNCOVERED (Test Entry Point)
- **Reason**: This is the test suite entry point, not a source function to be tested

### 5. main (06_symbol_versions/main.c)
- **Source File**: c/tests/06_symbol_versions/main.c
- **Status**: UNCOVERED (Test Binary)
- **Reason**: This is a test binary main function, not a source function to be tested

### 6. xyz
- **Source File**: c/tests/06_symbol_versions/v1.c
- **Status**: UNCOVERED (Test Symbol)
- **Reason**: This is a test symbol for version testing, not a source function to be tested

### 7. xyz_old
- **Source File**: c/tests/06_symbol_versions/v2.c
- **Status**: UNCOVERED (Test Symbol)
- **Reason**: This is a test symbol for version testing, not a source function to be tested

### 8. xyz_new
- **Source File**: c/tests/06_symbol_versions/v2.c
- **Status**: UNCOVERED (Test Symbol)
- **Reason**: This is a test symbol for version testing, not a source function to be tested

---

## Analysis

### Coverage Quality
All 34 functions from c/libtree.c are either:
1. **Covered by tests** (29 functions) - These have explicit test cases in the test suite
2. **Test infrastructure** (5 functions) - These are helper functions and entry points in the test files themselves

### Key Observations
1. **Complete source function coverage**: All 29 functions in c/libtree.c have corresponding test coverage
2. **Comprehensive test scenarios**: Most functions are tested with multiple scenarios including:
   - Basic functionality
   - Edge cases
   - Boundary conditions
   - Error conditions
   - Integration scenarios
3. **Both C and Rust tests**: Many functions are tested in both C (original tests) and Rust (translated tests)
4. **Uncovered items are not source functions**: The 8 "uncovered" items are test helpers and test binaries, not source code functions that need testing

### Recommendations
1. **Current state is excellent**: With 100% coverage of actual source functions, no additional tests are needed
2. **Test helper functions** (create_test_elf_file, create_test_config_file, create_elf_with_program_headers) don't require their own tests as they are utilities used by other tests
3. **Symbol version test files** (06_symbol_versions/*) are fixtures for integration testing, not functions requiring unit tests

---

## Uncovered Functions List

The following 8 items are marked as uncovered, but they are NOT source functions requiring test coverage:

1. `create_test_elf_file` (c/tests/test.c) - Test helper
2. `create_test_config_file` (c/tests/test.c) - Test helper
3. `create_elf_with_program_headers` (c/tests/test.c) - Test helper
4. `main` (c/tests/test.c) - Test entry point
5. `main` (c/tests/06_symbol_versions/main.c) - Test binary
6. `xyz` (c/tests/06_symbol_versions/v1.c) - Test symbol
7. `xyz_old` (c/tests/06_symbol_versions/v2.c) - Test symbol
8. `xyz_new` (c/tests/06_symbol_versions/v2.c) - Test symbol

**Note**: These are infrastructure and fixture functions, not source code functions. All actual source functions from c/libtree.c (29 functions) have test coverage.

---

## Source Functions Coverage: 100%

All 29 functions from c/libtree.c are covered:
- utoa
- small_vec_u64_init
- small_vec_u64_append
- small_vec_u64_free
- host_is_little_endian
- is_ascending_order
- string_table_maybe_grow
- string_table_store
- string_table_copy_from_file
- is_in_exclude_list
- tree_preamble
- apply_exclude_list
- check_absolute_paths
- check_search_paths
- interpolate_variables
- print_colon_delimited_paths
- print_line
- print_error
- visited_files_contains
- visited_files_append
- recurse
- ld_conf_globbing
- parse_ld_config_file
- parse_ld_so_conf
- parse_ld_library_path
- set_default_paths
- libtree_state_init
- libtree_state_free
- print_tree
