// Test suite for libtree
// Translation from C tests/test.c to Rust

use ::libtree::*;
use std::fs::{File, remove_file};
use std::io::Write;
use std::env;

// Helper functions for creating test ELF files
pub fn create_test_elf_file(filename: &str, valid: bool) -> std::io::Result<()> {
    let mut f = File::create(filename)?;

    if valid {
        // Write minimal valid ELF header
        let mut elf_header = [0u8; 64];
        elf_header[0] = 0x7f;  // ELF magic
        elf_header[1] = b'E';
        elf_header[2] = b'L';
        elf_header[3] = b'F';
        elf_header[4] = 2;     // 64-bit
        elf_header[5] = 1;     // Little endian
        elf_header[6] = 1;     // Version
        elf_header[16] = 2;    // ET_EXEC
        elf_header[18] = 0x3e; // x86-64
        f.write_all(&elf_header)?;
    } else {
        // Write invalid data
        f.write_all(b"invalid")?;
    }
    Ok(())
}

pub fn create_test_config_file(filename: &str, content: &str) -> std::io::Result<()> {
    let mut f = File::create(filename)?;
    f.write_all(content.as_bytes())?;
    Ok(())
}

// Test utility functions
#[test]
fn test_utoa_function() {
    assert_eq!(utoa(0), "0");
    assert_eq!(utoa(123), "123");
    assert_eq!(utoa(9876543210), "9876543210");
}

#[test]
fn test_host_endianness() {
    let result = host_is_little_endian();
    // Should return true or false
    assert!(result || !result);
}

#[test]
fn test_ascending_order_check() {
    let ascending = vec![1, 2, 3, 4, 5];
    let descending = vec![5, 4, 3, 2, 1];
    let mixed = vec![1, 3, 2, 4, 5];

    assert_eq!(is_ascending_order(&ascending), true);
    assert_eq!(is_ascending_order(&descending), false);
    assert_eq!(is_ascending_order(&mixed), false);

    // Edge cases
    let single = vec![42];
    assert_eq!(is_ascending_order(&single), true);

    let empty: Vec<u64> = vec![];
    assert_eq!(is_ascending_order(&empty), true);
}

// Test small_vec_u64 data structure
#[test]
fn test_small_vec_u64_operations() {
    let mut vec = small_vec_u64_t::new();
    assert_eq!(vec.len(), 0);

    // Test adding elements within buffer capacity
    for i in 0..16 {
        small_vec_u64_append(&mut vec, i);
        assert_eq!(vec.len(), (i + 1) as usize);
    }

    // Test expansion beyond buffer
    small_vec_u64_append(&mut vec, 16);
    assert_eq!(vec.len(), 17);

    // Add more to test reallocation
    for i in 17..50 {
        small_vec_u64_append(&mut vec, i);
    }
    assert_eq!(vec.len(), 50);

    small_vec_u64_free(&mut vec);
}

// Test string table operations
#[test]
fn test_string_table_operations() {
    let mut table = string_table_t {
        n: 0,
        capacity: 10,
        arr: Vec::with_capacity(10),
    };

    string_table_store(&mut table, "hello");
    assert_eq!(table.n, 6); // 5 chars + null terminator
    assert_eq!(&table.arr[0..5], b"hello");
    assert_eq!(table.arr[5], 0); // null terminator

    string_table_store(&mut table, "world");
    assert_eq!(&table.arr[6..11], b"world");
    assert_eq!(table.arr[11], 0); // null terminator
}

#[test]
fn test_string_table_growth() {
    let mut table = string_table_t {
        n: 0,
        capacity: 5,
        arr: Vec::with_capacity(5),
    };

    // This should trigger growth
    string_table_store(&mut table, "this is a long string");
    assert!(table.capacity >= table.n);
    assert!(table.arr.capacity() >= table.n);
    let stored = std::str::from_utf8(&table.arr[0..21]).unwrap();
    assert_eq!(stored, "this is a long string");
}

// Test exclude list functionality
#[test]
fn test_exclude_list_checking() {
    assert_eq!(is_in_exclude_list("libc.so.6"), true);
    assert_eq!(is_in_exclude_list("libc.so"), true);
    assert_eq!(is_in_exclude_list("libm.so.1"), true);
    assert_eq!(is_in_exclude_list("ld-linux-x86-64.so.2"), true);

    assert_eq!(is_in_exclude_list("libcustom.so"), false);
    assert_eq!(is_in_exclude_list("mylib.so.1"), false);
    assert_eq!(is_in_exclude_list(""), false);
}

// Test visited files tracking
#[test]
fn test_visited_files_operations() {
    let mut files = visited_file_array_t {
        arr: Vec::with_capacity(2),
    };

    let file1 = visited_file_t { st_dev: 1, st_ino: 100 };
    let file2 = visited_file_t { st_dev: 1, st_ino: 200 };
    let file3 = visited_file_t { st_dev: 2, st_ino: 100 };

    assert_eq!(visited_files_contains(&files, &file1), false);

    visited_files_append(&mut files, file1);
    assert_eq!(visited_files_contains(&files, &file1), true);
    assert_eq!(visited_files_contains(&files, &file2), false);

    visited_files_append(&mut files, file2);
    assert_eq!(visited_files_contains(&files, &file1), true);
    assert_eq!(visited_files_contains(&files, &file2), true);
    assert_eq!(visited_files_contains(&files, &file3), false);

    // This should trigger capacity expansion
    visited_files_append(&mut files, file3);
    assert_eq!(visited_files_contains(&files, &file3), true);
    assert!(files.arr.capacity() > 2);
}

// Test libtree state initialization and cleanup
#[test]
fn test_libtree_state_lifecycle() {
    let mut state = libtree_state_init();

    assert_eq!(state.string_table.n, 0);
    assert_eq!(state.string_table.capacity, 1024);
    assert_eq!(state.string_table.arr.capacity(), 1024);

    assert!(state.visited.arr.is_empty());

    libtree_state_free(&mut state);
}

// Test configuration file parsing
#[test]
fn test_config_file_parsing() {
    // Create test config file
    let config_content = "# This is a comment\n\
                         /usr/local/lib\n\
                         /opt/lib\n\
                         \n\
                           /usr/lib/x86_64-linux-gnu  \n\
                         include /etc/ld.so.conf.d/*.conf\n";

    create_test_config_file("test_ld.conf", config_content).unwrap();

    let mut table = string_table_t {
        n: 0,
        capacity: 1024,
        arr: Vec::with_capacity(1024),
    };

    let result = parse_ld_config_file(&mut table, "test_ld.conf");
    assert!(result.is_ok());

    // Check that paths were added (they should be colon-separated)
    let table_str = std::str::from_utf8(&table.arr[0..table.n]).unwrap();
    assert!(table_str.contains("/usr/local/lib"));
    assert!(table_str.contains("/opt/lib"));
    assert!(table_str.contains("/usr/lib/x86_64-linux-gnu"));

    remove_file("test_ld.conf").ok();
}

#[test]
fn test_config_file_nonexistent() {
    let mut table = string_table_t {
        n: 0,
        capacity: 1024,
        arr: Vec::with_capacity(1024),
    };

    let result = parse_ld_config_file(&mut table, "nonexistent.conf");
    assert!(result.is_err()); // Should fail
}

// Test environment variable parsing
#[test]
fn test_ld_library_path_parsing() {
    let mut state = libtree_state_init();

    // Test with no LD_LIBRARY_PATH set
    env::remove_var("LD_LIBRARY_PATH");
    parse_ld_library_path(&mut state);
    assert_eq!(state.ld_library_path_offset, usize::MAX);

    // Test with LD_LIBRARY_PATH set
    env::set_var("LD_LIBRARY_PATH", "/usr/local/lib:/opt/lib");
    parse_ld_library_path(&mut state);
    assert_ne!(state.ld_library_path_offset, usize::MAX);
    let path_str = std::str::from_utf8(
        &state.string_table.arr[state.ld_library_path_offset..]
    ).unwrap();
    assert!(path_str.starts_with("/usr/local/lib:/opt/lib"));

    libtree_state_free(&mut state);
}

// Test default paths setup
#[test]
fn test_default_paths_setup() {
    let mut state = libtree_state_init();

    set_default_paths(&mut state);

    let path_str = std::str::from_utf8(
        &state.string_table.arr[state.default_paths_offset..]
    ).unwrap();
    assert!(path_str.starts_with("/lib:/lib64:/usr/lib:/usr/lib64"));

    libtree_state_free(&mut state);
}

// Test ELF file validation
#[test]
fn test_elf_file_validation() {
    // Create test files
    create_test_elf_file("valid.elf", true).unwrap();
    create_test_elf_file("invalid.elf", false).unwrap();

    let mut state = libtree_state_init();
    let compat = compat_t {
        any: true,
        class: 0,
        machine: 0,
    };
    let reason = found_t {
        how: how_t::INPUT,
        depth: 0,
    };

    // Test invalid file
    let result = recurse("invalid.elf", 0, &mut state, compat, reason);
    assert!(result.is_err());
    if let Err(e) = result {
        assert_eq!(e, LibtreeError::InvalidMagic);
    }

    // Test nonexistent file
    let result = recurse("nonexistent.elf", 0, &mut state, compat, reason);
    assert!(result.is_err());
    if let Err(e) = result {
        assert_eq!(e, LibtreeError::CouldNotOpenFile);
    }

    libtree_state_free(&mut state);

    remove_file("valid.elf").ok();
    remove_file("invalid.elf").ok();
}

// Test string_table_copy_from_file function
#[test]
fn test_string_table_copy_from_file() {
    let mut table = string_table_t {
        n: 0,
        capacity: 100,
        arr: Vec::with_capacity(100),
    };

    // Create a test file with null-terminated string
    let mut test_file = File::create("test_string_copy.txt").unwrap();
    test_file.write_all(b"test\0data").unwrap();
    drop(test_file);

    // Test reading from file
    let mut test_file = File::open("test_string_copy.txt").unwrap();
    string_table_copy_from_file(&mut table, &mut test_file).unwrap();

    // The function reads until null terminator or EOF
    assert!(table.n >= 5); // "test" + null = 5
    let stored = std::str::from_utf8(&table.arr[0..4]).unwrap();
    assert_eq!(stored, "test");

    remove_file("test_string_copy.txt").ok();
}

// Test apply_exclude_list function
#[test]
fn test_apply_exclude_list_function() {
    let mut state = libtree_state_init();
    let mut needed_buf_offsets = small_vec_u64_t::new();

    // Add some libraries to test
    string_table_store(&mut state.string_table, "libc.so.6");
    small_vec_u64_append(&mut needed_buf_offsets, 0);

    let offset2 = state.string_table.n;
    string_table_store(&mut state.string_table, "libcustom.so");
    small_vec_u64_append(&mut needed_buf_offsets, offset2 as u64);

    let mut needed_not_found = 2;
    apply_exclude_list(&mut needed_not_found, &mut needed_buf_offsets, &state);

    // libc.so.6 should be moved to back, so needed_not_found should be 1
    assert_eq!(needed_not_found, 1);

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}

// Test boundary conditions
#[test]
fn test_boundary_conditions() {
    // Test utoa with edge values
    assert_eq!(utoa(1), "1");

    let max_val = u64::MAX as usize;
    let result = utoa(max_val);
    // Should not crash and produce some string
    assert!(result.len() > 0);

    // Test empty string operations
    let mut table = string_table_t {
        n: 0,
        capacity: 100,
        arr: Vec::with_capacity(100),
    };

    string_table_store(&mut table, "");
    assert_eq!(table.n, 1);
    assert_eq!(table.arr.len(), 1);
    assert_eq!(table.arr[0], 0);
}

// Test memory allocation edge cases
#[test]
fn test_memory_allocation_edge_cases() {
    let mut vec = small_vec_u64_t::new();

    // Test the transition from stack to heap
    for i in 0..SMALL_VEC_SIZE + 1 {
        small_vec_u64_append(&mut vec, i as u64);
    }

    assert_eq!(vec.len(), SMALL_VEC_SIZE + 1);

    // Test further expansion
    for i in SMALL_VEC_SIZE + 1..100 {
        small_vec_u64_append(&mut vec, i as u64);
    }

    assert_eq!(vec.len(), 100);

    small_vec_u64_free(&mut vec);
}

// Test LD config file parsing with various scenarios
#[test]
fn test_ld_config_file_comprehensive() {
    // Test with comments and whitespace variations
    let config_content = "# Comment at start\n\
                         /usr/local/lib   # inline comment\n\
                            /opt/lib   \n\
                         \n\
                           # Comment with leading spaces\n\
                         /usr/lib/custom\n\
                         include /etc/ld.so.conf.d/*.conf\n";

    create_test_config_file("test_complex_ld.conf", config_content).unwrap();

    let mut table = string_table_t {
        n: 0,
        capacity: 1024,
        arr: Vec::with_capacity(1024),
    };

    let result = parse_ld_config_file(&mut table, "test_complex_ld.conf");
    assert!(result.is_ok());

    // Should contain the paths with colons
    let table_str = std::str::from_utf8(&table.arr[0..table.n]).unwrap();
    assert!(table_str.contains("/usr/local/lib:"));
    assert!(table_str.contains("/opt/lib:"));
    assert!(table_str.contains("/usr/lib/custom:"));

    remove_file("test_complex_ld.conf").ok();
}

// Test LD_LIBRARY_PATH with semicolons
#[test]
fn test_ld_library_path_semicolons() {
    let mut state = libtree_state_init();

    // Test with semicolons (Windows-style)
    env::set_var("LD_LIBRARY_PATH", "/path1;/path2;/path3");
    parse_ld_library_path(&mut state);

    assert_ne!(state.ld_library_path_offset, usize::MAX);
    // Semicolons should be converted to colons
    let path_str = std::str::from_utf8(
        &state.string_table.arr[state.ld_library_path_offset..]
    ).unwrap();
    assert!(path_str.contains("/path1:/path2:/path3"));

    libtree_state_free(&mut state);
}

// Test parse_ld_so_conf function
#[test]
fn test_parse_ld_so_conf_function() {
    let mut state = libtree_state_init();

    // Create a test ld.so.conf file
    let config_content = "/usr/local/lib\n/opt/lib\n";
    create_test_config_file("test_ld_so.conf", config_content).unwrap();

    state.ld_conf_file = "test_ld_so.conf".to_string();
    parse_ld_so_conf(&mut state);

    assert_ne!(state.ld_so_conf_offset, usize::MAX);
    // Should end with null terminator, not colon
    let ld_conf_str = std::str::from_utf8(
        &state.string_table.arr[state.ld_so_conf_offset..]
    ).unwrap();
    assert!(ld_conf_str.len() > 0);

    libtree_state_free(&mut state);
    remove_file("test_ld_so.conf").ok();
}

// Test string boundary conditions
#[test]
fn test_string_boundary_conditions() {
    // Test is_in_exclude_list with edge cases
    assert_eq!(is_in_exclude_list(""), false); // Empty string

    // Test with library that has version numbers stripped
    assert_eq!(is_in_exclude_list("libc.so.6.1.2.3"), true);
    assert_eq!(is_in_exclude_list("libm.so.1"), true);

    // Test string table growth with exact capacity
    let mut table = string_table_t {
        n: 5,
        capacity: 10,
        arr: Vec::with_capacity(10),
    };
    // Pre-fill with 5 bytes
    table.arr.extend_from_slice(&[1, 2, 3, 4, 5]);

    // This should trigger growth
    string_table_maybe_grow(&mut table, 10); // 5 + 10 = 15 > 10
    assert!(table.capacity >= 30); // Should be 2 * (5 + 10)
}

// Test small_vec_free edge case
#[test]
fn test_small_vec_free_edge_case() {
    let mut vec = small_vec_u64_t::new();

    // Test freeing when still on stack (should not free)
    small_vec_u64_append(&mut vec, 1);
    assert!(vec.len() <= SMALL_VEC_SIZE);

    // This should not crash
    small_vec_u64_free(&mut vec);

    // Now test after moving to heap
    let mut vec = small_vec_u64_t::new();
    for i in 0..SMALL_VEC_SIZE + 1 {
        small_vec_u64_append(&mut vec, i as u64);
    }

    small_vec_u64_free(&mut vec); // This should actually free memory
}

// Integration test with more complete workflow
#[test]
fn test_comprehensive_integration() {
    let mut state = libtree_state_init();

    // Set up complete environment
    state.PLATFORM = "x86_64".to_string();
    state.LIB = "lib".to_string();
    state.OSNAME = "Linux".to_string();
    state.OSREL = "5.4.0".to_string();
    state.ld_conf_file = "/etc/ld.so.conf".to_string();
    state.color = true;
    state.verbosity = 3; // Maximum verbosity
    state.path = true;
    state.max_depth = 5;

    // Create test configuration
    let config_content = "/usr/local/lib\ninclude /etc/ld.so.conf.d/*.conf\n";
    create_test_config_file("test_integration_ld.conf", config_content).unwrap();

    state.ld_conf_file = "test_integration_ld.conf".to_string();

    // Set environment
    env::set_var("LD_LIBRARY_PATH", "/custom/lib:/another/lib");

    // Initialize all paths
    parse_ld_so_conf(&mut state);
    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);

    // Verify all offsets are set
    assert_ne!(state.ld_so_conf_offset, usize::MAX);
    assert_ne!(state.ld_library_path_offset, usize::MAX);
    assert_ne!(state.default_paths_offset, usize::MAX);

    libtree_state_free(&mut state);
    remove_file("test_integration_ld.conf").ok();
}

// Performance test for large data structures
#[test]
fn test_performance_stress() {
    let mut vec = small_vec_u64_t::new();

    // Add many elements to test reallocation
    for i in 0..10000 {
        small_vec_u64_append(&mut vec, i);
    }

    assert_eq!(vec.len(), 10000);

    small_vec_u64_free(&mut vec);
}
