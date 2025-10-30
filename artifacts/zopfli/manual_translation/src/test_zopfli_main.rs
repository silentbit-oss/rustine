use lazy_static::lazy_static;
use std::env;
use std::ffi::CString;
use std::os::raw::c_char;
use std::process::exit;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use translate_without_break_down::*;

lazy_static::lazy_static! {
    pub static ref VERBOSE: AtomicI32 = AtomicI32::new(0);
}

pub fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() > 1 && args[1] == "-v" {
        VERBOSE.store(1, Ordering::SeqCst);
    }

    println!("Starting Zopfli Test Suite (Zlib-Free Version)");
    println!("===============================================\n");

    // Test 1
    println!("Running {}...", "test_zopfli_init_options");
    if test_zopfli_init_options() != 0 {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 2
    println!("Running {}...", "test_zopfli_compress_formats");
    if test_zopfli_compress_formats() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 3
    println!("Running {}...", "test_zopfli_deflate_direct");
    if test_zopfli_deflate_direct() != 0 {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 4
    println!("Running {}...", "test_zopfli_gzip_direct");
    if test_zopfli_gzip_direct() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 5
    println!("Running {}...", "test_zopfli_zlib_direct");
    if test_zopfli_zlib_direct() != 0 {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 6
    println!("Running {}...", "test_zopfli_empty_input");
    if test_zopfli_empty_input() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 7
    println!("Running {}...", "test_zopfli_iterations");
    if test_zopfli_iterations() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 8
    println!("Running {}...", "test_zopfli_binary_data");
    if test_zopfli_binary_data() != 0 {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 9
    println!("Running {}...", "test_zopfli_block_splitting");
    if test_zopfli_block_splitting() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 10
    println!("Running {}...", "test_zopfli_repetitive_data");
    if test_zopfli_repetitive_data() != 0 {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Test 11
    println!("Running {}...", "test_zopfli_consistency");
    if test_zopfli_consistency() {
        TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
    } else {
        TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
    }
    TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);

    // Optional verbose test
    if VERBOSE.load(Ordering::SeqCst) != 0 {
        println!("Running {}...", "test_zopfli_verbose_options");
        if test_zopfli_verbose_options() {
            TESTS_PASSED.fetch_add(1, Ordering::SeqCst);
        } else {
            TESTS_FAILED.fetch_add(1, Ordering::SeqCst);
        }
        TOTAL_TESTS.fetch_add(1, Ordering::SeqCst);
    }

    println!("\n===============================================");
    println!("Test Results:");
    println!("Total tests: {}", TOTAL_TESTS.load(Ordering::SeqCst));
    println!("Passed: {}", TESTS_PASSED.load(Ordering::SeqCst));
    println!("Failed: {}", TESTS_FAILED.load(Ordering::SeqCst));

    if TESTS_FAILED.load(Ordering::SeqCst) == 0 {
        println!("SUCCESS: All tests passed! ✓");
    } else {
        println!("FAILURE: {} test(s) failed ✗", TESTS_FAILED.load(Ordering::SeqCst));
    }

    let success_rate = (TESTS_PASSED.load(Ordering::SeqCst) as f32 / TOTAL_TESTS.load(Ordering::SeqCst) as f32) * 100.0;
    println!("Success rate: {:.1}%", success_rate);

    exit(if TESTS_FAILED.load(Ordering::SeqCst) == 0 { 0 } else { 1 });
}
