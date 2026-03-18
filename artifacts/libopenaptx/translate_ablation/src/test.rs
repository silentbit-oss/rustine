use crate::*;
use std::assert_eq;

pub fn assert_true(condition: bool, test_name: &str) {
    if condition {
        println!("[PASS] {}", test_name);
    } else {
        println!("[FAIL] {}", test_name);
    }
}
pub fn test_aptx_invalid_inputs() {
    // Initialize context with hd=false (0 in C)
    let mut ctx = aptx_init(false).expect("aptx_init should succeed");
    
    // Test NULL input with length 0
    let mut out = [0u8; 10];
    let mut written = 0;
    let processed = aptx_encode(&mut ctx, &[], &mut out, &mut written);
    assert_true(processed == 0, "Encode with NULL input length 0 returns 0");
    
    // Test with tiny output buffer
    let input = [0u8; 24];
    let processed = aptx_encode(&mut ctx, &input, &mut out[..1], &mut written);
    assert_true(
        processed == 0 || written == 0,
        "Encode with tiny output buffer fails or writes 0",
    );
    
    // Finish context
    aptx_finish(Some(ctx));
}

pub fn test_aptx_hd_mode() {
    // Initialize contexts using Option<Box<AptxContext>> as per aptx_init's return type
    let mut ctx_enc = aptx_init(true).expect("Failed to initialize encoder context");
    let mut ctx_dec = aptx_init(true).expect("Failed to initialize decoder context");

    // Initialize buffers with fixed sizes matching C code
    let mut input = [0u8; 24];
    let mut encoded = [0u8; 10];
    let mut decoded = [0u8; 24];
    let mut written_enc = 0;
    let mut written_dec = 0;

    // Fill input buffer with values 0..24
    for i in 0..24 {
        input[i] = i as u8;
    }

    // Encoding process
    let processed_enc = aptx_encode(
        &mut ctx_enc,
        &input,
        &mut encoded,
        &mut written_enc,
    );

    // Decoding process
    let processed_dec = aptx_decode(
        &mut ctx_dec,
        &encoded[..written_enc],
        &mut decoded,
        &mut written_dec,
    );

    // Assertions
    assert_true(processed_enc == input.len(), "HD mode encoding processed size");
    assert_true(processed_dec == written_enc, "HD mode decoding processed size");

    // Clean up contexts
    aptx_finish(Some(ctx_enc));
    aptx_finish(Some(ctx_dec));
}
pub fn test_aptx_encode_decode_various() {
    let mut ctx_enc = aptx_init(false).expect("Failed to initialize encoder context");
    let mut ctx_dec = aptx_init(false).expect("Failed to initialize decoder context");
    
    let mut input = [0u8; 24];
    let mut encoded = [0u8; 10];
    let mut decoded = [0u8; 24];
    let mut written_enc = 0;
    let mut written_dec = 0;

    // Test empty input
    let processed = aptx_encode(
        &mut ctx_enc,
        &input[..0],
        &mut encoded,
        &mut written_enc,
    );
    assert_true(processed == 0, "Encoding empty input returns 0");

    // Fill input with max value
    input.iter_mut().for_each(|x| *x = 255);

    // Test max value input
    let processed = aptx_encode(
        &mut ctx_enc,
        &input,
        &mut encoded,
        &mut written_enc,
    );
    assert_true(processed == input.len(), "Encoding max value input");

    // Test encode-decode loop
    let mut pass = true;
    for _ in 0..5 {
        let processed = aptx_encode(
            &mut ctx_enc,
            &input,
            &mut encoded,
            &mut written_enc,
        );
        if processed != input.len() {
            pass = false;
        }

        let processed = aptx_decode(
            &mut ctx_dec,
            &encoded[..written_enc],
            &mut decoded,
            &mut written_dec,
        );
        if processed != written_enc {
            pass = false;
        }
    }

    assert_true(pass, "Encode-decode loop multiple iterations");

    aptx_finish(Some(ctx_enc));
    aptx_finish(Some(ctx_dec));
}
pub fn test_aptx_decode_sync() {
    // Initialize the decoder context (hd = false)
    let mut ctx_dec = aptx_init(false).expect("Failed to initialize aptx context");
    
    // Initialize input and output buffers
    let input = [0u8; 10];
    let mut output = [0u8; 24];
    
    // Variables to be modified by aptx_decode_sync
    let mut written = 0;
    let mut synced = 0;
    let mut dropped = 0;
    
    // Call aptx_decode_sync
    let processed = aptx_decode_sync(
        &mut ctx_dec,
        &input,
        &mut output,
        &mut written,
        &mut synced,
        &mut dropped,
    );
    
    // Assertions
    assert_true(processed == input.len(), "decode_sync processed size");
    assert_true(synced == 1, "decode_sync synced flag");
    
    println!("[INFO] decode_sync dropped bytes: {}", dropped);
    
    // Call aptx_decode_sync_finish
    let dropped_finish = aptx_decode_sync_finish(&mut ctx_dec);
    println!("[INFO] decode_sync_finish dropped bytes: {}", dropped_finish);
    
    // Clean up
    aptx_finish(Some(ctx_dec));
}
