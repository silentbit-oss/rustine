use crate::*;
use crate::ZopfliFormat::ZOPFLI_FORMAT_DEFLATE;
use crate::ZopfliFormat::ZOPFLI_FORMAT_GZIP;
use std::default::Default;
use std::ffi::CStr;
use std::io;
use std::os::raw::c_char;
use std::time::Duration;
use std::time::Instant;

pub fn verify_gzip_header(data: Option<&[u8]>, size: usize) -> bool {
    // Check if data is None (equivalent to NULL check in C)
    if data.is_none() {
        return false;
    }
    let data = data.unwrap();

    // Check size first (Rust slices are bounds-checked, but we need to verify minimum length)
    if size < 10 {
        return false;
    }

    // Check magic bytes (0x1f, 0x8b)
    if data[0] != 0x1f || data[1] != 0x8b {
        return false;
    }

    // Check compression method (must be 8 for DEFLATE)
    if data[2] != 8 {
        return false;
    }

    true
}
pub fn verify_zlib_header(data: Option<&[u8]>, size: usize) -> bool {
    // Check if data is None (equivalent to NULL check in C)
    let data = match data {
        Some(d) => d,
        None => return false,
    };

    // Check size condition (line 3-6)
    if size < 2 {
        return false;
    }

    // Check first byte condition (line 7-10)
    if (data[0] & 0x0f) != 0x08 {
        return false;
    }

    // Check checksum condition (line 11-14)
    if (u16::from(data[0]) << 8 | u16::from(data[1])) % 31 != 0 {
        return false;
    }

    // All checks passed (line 15)
    true
}
pub fn verify_deflate_format(data: Option<&[u8]>, size: usize) -> bool {
    // Check if data is None or size is too small
    if size < 1 || data.is_none() {
        return false;
    }

    let data = data.unwrap(); // Safe unwrap since we checked is_none()
    let first_byte = data[0];
    let block_type = (first_byte >> 1) & 0x03;
    
    block_type <= 2
}
pub fn test_zopfli_init_options() -> i32 {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);

    if options.verbose != 0 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default verbose should be 0");
        return 0;
    }

    if options.verbose_more != 0 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default verbose_more should be 0");
        return 0;
    }

    if options.numiterations <= 0 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default numiterations should be positive");
        return 0;
    }

    if options.numiterations > 50 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default numiterations should be reasonable");
        return 0;
    }

    if options.blocksplitting < 0 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default blocksplitting should be valid");
        return 0;
    }

    if options.blocksplittingmax < 0 {
        println!("FAIL: {} - {}", "test_zopfli_init_options", "Default blocksplittingmax should be valid");
        return 0;
    }

    println!("  Default iterations: {}, blocksplitting: {}, blocksplittingmax: {}", 
             options.numiterations, options.blocksplitting, options.blocksplittingmax);
    println!("PASS: {}", "test_zopfli_init_options");
    1
}
pub fn test_zopfli_repetitive_data() -> i32 {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    let mut repetitive_data = [0u8; 2000];
    
    // Fill repetitive_data with 'A' to 'E' repeating pattern
    for i in 0..2000 {
        repetitive_data[i] = b'A' + (i % 5) as u8;
    }

    ZopfliInitOptions(&mut options);
    
    let mut out = Vec::new();
    match ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_DEFLATE, Some(&repetitive_data), &mut out) {
        Ok(_) => (),
        Err(e) => {
            println!("FAIL: {} - {}", "test_zopfli_repetitive_data", e);
            return 0;
        }
    }

    if out.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_repetitive_data", "Output size should be greater than 0");
        return 0;
    }

    let outsize = out.len();
    let compression_ratio = outsize as f64 / 2000.0;
    println!("  Repetitive data compression ratio: {:.3} ({} bytes from 2000)", compression_ratio, outsize);

    if outsize >= 100 {
        println!("FAIL: {} - {}", "test_zopfli_repetitive_data", "Repetitive data should compress very well");
        return 0;
    }

    println!("PASS: {}", "test_zopfli_repetitive_data");
    1
}
pub fn test_zopfli_empty_input() -> bool {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);
    
    let empty_data = b"";
    let mut out = Vec::new();
    
    match ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_DEFLATE, Some(empty_data), &mut out) {
        Ok(_) => {
            println!("  Empty input compression: {} bytes", out.len());
            println!("PASS: {}", "test_zopfli_empty_input");
            true
        }
        Err(_) => {
            println!("FAIL: {} - {}", "test_zopfli_empty_input", "Output buffer should not be NULL even for empty input");
            false
        }
    }
}
pub fn test_zopfli_iterations() -> bool {
    
    let mut options1 = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    let mut options2 = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    let mut out1 = Vec::new();
    let mut out2 = Vec::new();
    
    ZopfliInitOptions(&mut options1);
    ZopfliInitOptions(&mut options2);
    
    options1.numiterations = 1;
    options2.numiterations = 25;
    
    let test_data = TEST_DATA_LARGE.as_bytes();
    
    // First compression
    let start = std::time::Instant::now();
    if let Err(e) = ZopfliCompress(&options1, ZOPFLI_FORMAT_DEFLATE, Some(test_data), &mut out1) {
        eprintln!("Error in first compression: {}", e);
        return false;
    }
    let time1 = start.elapsed().as_secs_f64();
    
    // Second compression
    let start = std::time::Instant::now();
    if let Err(e) = ZopfliCompress(&options2, ZOPFLI_FORMAT_DEFLATE, Some(test_data), &mut out2) {
        eprintln!("Error in second compression: {}", e);
        return false;
    }
    let time2 = start.elapsed().as_secs_f64();
    
    // Check first compression result
    if out1.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_iterations", "Fast compression should work");
        return false;
    }
    
    // Check second compression result
    if out2.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_iterations", "Slow compression should work");
        return false;
    }
    
    // Compare compression sizes
    if out2.len() > out1.len() {
        println!("FAIL: {} - {}", "test_zopfli_iterations", "More iterations should give better or equal compression");
        return false;
    }
    
    println!("  1 iteration: {} bytes ({:.3}s), 25 iterations: {} bytes ({:.3}s)",
             out1.len(), time1, out2.len(), time2);
    
    println!("PASS: {}", "test_zopfli_iterations");
    true
}
pub fn test_zopfli_binary_data() -> i32 {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    
    let mut binary_data = [0u8; 256];
    for i in 0..256 {
        binary_data[i] = i as u8;
    }

    ZopfliInitOptions(&mut options);
    let mut out = Vec::new();
    
    match ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_DEFLATE, Some(&binary_data), &mut out) {
        Ok(_) => {
            if out.is_empty() {
                println!("FAIL: {} - {}", "test_zopfli_binary_data", "Output buffer should not be NULL");
                return 0;
            }
            
            let outsize = out.len();
            if outsize == 0 {
                println!("FAIL: {} - {}", "test_zopfli_binary_data", "Output size should be greater than 0");
                return 0;
            }
            
            println!("  Binary data compression: {} bytes (from 256 input bytes)", outsize);
            println!("PASS: {}", "test_zopfli_binary_data");
            1
        }
        Err(e) => {
            println!("FAIL: {} - Compression error: {}", "test_zopfli_binary_data", e);
            0
        }
    }
}
pub fn test_zopfli_block_splitting() -> bool {
    let mut options_on = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    let mut options_off = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options_on);
    ZopfliInitOptions(&mut options_off);
    
    options_on.blocksplitting = 1;
    options_off.blocksplitting = 0;

    let test_data = TEST_DATA_LARGE.as_bytes();
    let mut out_on = Vec::new();
    let mut out_off = Vec::new();

    if let Err(e) = ZopfliCompress(&options_on, ZOPFLI_FORMAT_DEFLATE, Some(test_data), &mut out_on) {
        println!("FAIL: {} - {}", "test_zopfli_block_splitting", "Block splitting ON should work");
        println!("Error: {}", e);
        return false;
    }

    if let Err(e) = ZopfliCompress(&options_off, ZOPFLI_FORMAT_DEFLATE, Some(test_data), &mut out_off) {
        println!("FAIL: {} - {}", "test_zopfli_block_splitting", "Block splitting OFF should work");
        println!("Error: {}", e);
        return false;
    }

    if out_on.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_block_splitting", "Block splitting ON should work");
        return false;
    }

    if out_off.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_block_splitting", "Block splitting OFF should work");
        return false;
    }

    println!("  Block splitting ON: {} bytes, OFF: {} bytes", out_on.len(), out_off.len());

    if out_on.len() > out_off.len() {
        println!("FAIL: {} - {}", "test_zopfli_block_splitting", "Block splitting should improve or maintain compression");
        return false;
    }

    println!("PASS: {}", "test_zopfli_block_splitting");
    true
}
pub fn test_zopfli_consistency() -> bool {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);

    let test_data = TEST_DATA_MEDIUM.as_bytes();
    
    let mut out1 = Vec::new();
    let mut out2 = Vec::new();

    // First compression
    if let Err(e) = ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_GZIP, Some(test_data), &mut out1) {
        println!("FAIL: {} - First compression failed: {}", "test_zopfli_consistency", e);
        return false;
    }

    // Second compression
    if let Err(e) = ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_GZIP, Some(test_data), &mut out2) {
        println!("FAIL: {} - Second compression failed: {}", "test_zopfli_consistency", e);
        return false;
    }

    // Check first compression output
    if out1.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_consistency", "First compression should work");
        return false;
    }

    // Check second compression output
    if out2.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_consistency", "Second compression should work");
        return false;
    }

    // Check consistency
    if out1.len() != out2.len() {
        println!("FAIL: {} - {}", "test_zopfli_consistency", "Compression should be deterministic");
        return false;
    }

    println!("  Consistency check: both compressions produced {} bytes", out1.len());
    println!("PASS: {}", "test_zopfli_consistency");
    true
}
pub fn test_zopfli_verbose_options() -> bool {
    
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);
    options.verbose = 1;

    println!("  Testing with verbose output enabled:");

    let mut out = Vec::new();
    let in_data = TEST_DATA_MEDIUM.as_bytes();
    let result = ZopfliCompress(&options, ZOPFLI_FORMAT_GZIP, Some(in_data), &mut out);

    if result.is_err() || out.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_verbose_options", "Verbose compression should work");
        return false;
    }

    println!("PASS: {}", "test_zopfli_verbose_options");
    true
}
pub fn test_zopfli_deflate_direct() -> i32 {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);
    
    let mut out: Option<Vec<u8>> = Option::None;
    let mut outsize = 0;
    let mut bp = 0;
    
    ZopfliDeflate(
        &options,
        2,
        true,
        TEST_DATA_SMALL.as_bytes(),
        &mut bp,
        &mut out,
        &mut outsize,
    );
    
    // Check if output buffer is not None
    if out.is_none() {
        println!("FAIL: {} - {}", "test_zopfli_deflate_direct", "Output buffer should not be NULL");
        return 0;
    }
    
    // Check if output size is greater than 0
    if outsize == 0 {
        println!("FAIL: {} - {}", "test_zopfli_deflate_direct", "Output size should be greater than 0");
        return 0;
    }
    
    // Verify deflate format
    if !verify_deflate_format(out.as_deref(), outsize) {
        println!("FAIL: {} - {}", "test_zopfli_deflate_direct", "Should produce valid deflate format");
        return 0;
    }
    
    println!(
        "  Direct deflate: {} bytes (from {} input bytes)",
        outsize,
        TEST_DATA_SMALL.len()
    );
    
    println!("PASS: {}", "test_zopfli_deflate_direct");
    1
}
pub fn test_zopfli_gzip_direct() -> bool {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);
    
    let mut out = Vec::new();
    let input_data = TEST_DATA_MEDIUM.as_bytes();
    
    if let Err(e) = ZopfliGzipCompress(&options, Some(input_data), &mut out) {
        println!("FAIL: {} - Compression failed: {}", "test_zopfli_gzip_direct", e);
        return false;
    }
    
    if out.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_gzip_direct", "Output buffer should not be NULL");
        return false;
    }
    
    if out.len() == 0 {
        println!("FAIL: {} - {}", "test_zopfli_gzip_direct", "Output size should be greater than 0");
        return false;
    }
    
    if out.len() >= input_data.len() {
        println!("FAIL: {} - {}", "test_zopfli_gzip_direct", "Compressed should be smaller than original");
        return false;
    }
    
    if !verify_gzip_header(Some(&out), out.len()) {
        println!("FAIL: {} - {}", "test_zopfli_gzip_direct", "Should have valid gzip header");
        return false;
    }
    
    println!("  Gzip compression: {} bytes (from {} input bytes)", out.len(), input_data.len());
    
    println!("PASS: {}", "test_zopfli_gzip_direct");
    true
}

pub fn test_zopfli_zlib_direct() -> i32 {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);

    let mut out = Vec::new();
    let input_data = TEST_DATA_MEDIUM.as_bytes();
    
    if let Err(e) = ZopfliZlibCompress(&options, input_data, &mut out) {
        println!("FAIL: {} - Compression failed: {}", "test_zopfli_zlib_direct", e);
        return 0;
    }

    let outsize = out.len();

    if out.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_zlib_direct", "Output buffer should not be NULL");
        return 0;
    }

    if outsize == 0 {
        println!("FAIL: {} - {}", "test_zopfli_zlib_direct", "Output size should be greater than 0");
        return 0;
    }

    if outsize >= input_data.len() {
        println!("FAIL: {} - {}", "test_zopfli_zlib_direct", "Compressed should be smaller than original");
        return 0;
    }

    if !verify_zlib_header(Some(&out), outsize) {
        println!("FAIL: {} - {}", "test_zopfli_zlib_direct", "Should have valid zlib header");
        return 0;
    }

    println!("  Zlib compression: {} bytes (from {} input bytes)", outsize, input_data.len());
    println!("PASS: {}", "test_zopfli_zlib_direct");
    1
}
pub fn test_zopfli_compress_formats() -> bool {
    let mut options = ZopfliOptions {
        verbose: 0,
        verbose_more: 0,
        numiterations: 0,
        blocksplitting: 0,
        blocksplittinglast: 0,
        blocksplittingmax: 0,
    };
    ZopfliInitOptions(&mut options);

    let test_data = TEST_DATA_MEDIUM.as_bytes();
    
    let mut out_deflate = Vec::new();
    let mut out_gzip = Vec::new();
    let mut out_zlib = Vec::new();

    // Compress in different formats
    if ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_DEFLATE, Some(test_data), &mut out_deflate).is_err() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Deflate compression should work");
        return false;
    }

    if ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_GZIP, Some(test_data), &mut out_gzip).is_err() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Gzip compression should work");
        return false;
    }

    if ZopfliCompress(&options, ZopfliFormat::ZOPFLI_FORMAT_ZLIB, Some(test_data), &mut out_zlib).is_err() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Zlib compression should work");
        return false;
    }

    // Check output sizes
    if out_deflate.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Deflate compression should work");
        return false;
    }

    if out_gzip.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Gzip compression should work");
        return false;
    }

    if out_zlib.is_empty() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Zlib compression should work");
        return false;
    }

    if out_gzip.len() <= out_deflate.len() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Gzip should be larger than deflate");
        return false;
    }

    if out_zlib.len() <= out_deflate.len() {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Zlib should be larger than deflate");
        return false;
    }

    // Verify headers
    if !verify_gzip_header(Some(&out_gzip), out_gzip.len()) {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Gzip should have valid header");
        return false;
    }

    if !verify_zlib_header(Some(&out_zlib), out_zlib.len()) {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Zlib should have valid header");
        return false;
    }

    if !verify_deflate_format(Some(&out_deflate), out_deflate.len()) {
        println!("FAIL: {} - {}", "test_zopfli_compress_formats", "Deflate should have valid format");
        return false;
    }

    println!("  Deflate: {} bytes, Gzip: {} bytes, Zlib: {} bytes", 
        out_deflate.len(), out_gzip.len(), out_zlib.len());

    println!("PASS: {}", "test_zopfli_compress_formats");
    true
}
