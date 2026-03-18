//! Basic test suite
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

#[allow(unused)]
mod common;

use libopenaptx::{aptx_init, aptx_finish, aptx_encode, aptx_decode, aptx_decode_sync, aptx_decode_sync_finish};

fn assert_true(condition: bool, test_name: &str) {
    if condition {
        println!("[PASS] {}", test_name);
    } else {
        println!("[FAIL] {}", test_name);
    }
}

#[test]
fn test_aptx_encode_decode_various() {
    let mut ctx_enc = aptx_init(0).expect("Failed to initialize encoder");
    let mut ctx_dec = aptx_init(0).expect("Failed to initialize decoder");

    let mut input = [0u8; 24];
    let mut encoded = [0u8; 10];
    let mut decoded = [0u8; 24];
    let mut written_enc: usize = 0;
    let mut written_dec: usize = 0;

    let encoded_len = encoded.len();
    let processed = aptx_encode(&mut ctx_enc, &input, 0, &mut encoded, encoded_len, &mut written_enc);
    assert_true(processed == 0, "Encoding empty input returns 0");

    for i in 0..24 {
        input[i] = 255;
    }
    let input_len = input.len();
    let processed = aptx_encode(&mut ctx_enc, &input, input_len, &mut encoded, encoded_len, &mut written_enc);
    assert_true(processed == input_len, "Encoding max value input");

    let mut pass = true;
    for _i in 0..5 {
        let processed = aptx_encode(&mut ctx_enc, &input, input_len, &mut encoded, encoded_len, &mut written_enc);
        if processed != input_len {
            pass = false;
        }
        let decoded_len = decoded.len();
        let processed = aptx_decode(&mut ctx_dec, &encoded, written_enc, &mut decoded, decoded_len, &mut written_dec);
        if processed != written_enc {
            pass = false;
        }
    }
    assert_true(pass, "Encode-decode loop multiple iterations");

    aptx_finish(ctx_enc);
    aptx_finish(ctx_dec);
}

#[test]
fn test_aptx_hd_mode() {
    let mut ctx_enc = aptx_init(1).expect("Failed to initialize encoder");
    let mut ctx_dec = aptx_init(1).expect("Failed to initialize decoder");

    let mut input = [0u8; 24];
    let mut encoded = [0u8; 10];
    let mut decoded = [0u8; 24];
    let mut written_enc: usize = 0;
    let mut written_dec: usize = 0;

    for i in 0..24 {
        input[i] = i as u8;
    }

    let input_len = input.len();
    let encoded_len = encoded.len();
    let decoded_len = decoded.len();
    let processed_enc = aptx_encode(&mut ctx_enc, &input, input_len, &mut encoded, encoded_len, &mut written_enc);
    let processed_dec = aptx_decode(&mut ctx_dec, &encoded, written_enc, &mut decoded, decoded_len, &mut written_dec);

    assert_true(processed_enc == input_len, "HD mode encoding processed size");
    assert_true(processed_dec == written_enc, "HD mode decoding processed size");

    aptx_finish(ctx_enc);
    aptx_finish(ctx_dec);
}

#[test]
fn test_aptx_decode_sync() {
    let mut ctx_dec = aptx_init(0).expect("Failed to initialize decoder");

    let input = [0u8; 10];
    let mut output = [0u8; 24];
    let mut written: usize = 0;
    let mut synced: i32 = 0;
    let mut dropped: usize = 0;

    let input_len = input.len();
    let output_len = output.len();
    let processed = aptx_decode_sync(
        &mut ctx_dec,
        &input,
        input_len,
        &mut output,
        output_len,
        &mut written,
        &mut synced,
        &mut dropped
    );

    assert_true(processed == input_len, "decode_sync processed size");
    assert_true(synced == 1, "decode_sync synced flag");

    println!("[INFO] decode_sync dropped bytes: {}", dropped);

    let dropped_finish = aptx_decode_sync_finish(&mut ctx_dec);
    println!("[INFO] decode_sync_finish dropped bytes: {}", dropped_finish);

    aptx_finish(ctx_dec);
}

#[test]
fn test_aptx_invalid_inputs() {
    let mut ctx = aptx_init(0).expect("Failed to initialize context");
    let mut out = [0u8; 10];
    let mut written: usize = 0;

    let empty: [u8; 0] = [];
    let out_len = out.len();
    let processed = aptx_encode(&mut ctx, &empty, 0, &mut out, out_len, &mut written);
    assert_true(processed == 0, "Encode with NULL input length 0 returns 0");

    let input = [0u8; 24];
    let input_len = input.len();
    let processed = aptx_encode(&mut ctx, &input, input_len, &mut out, 1, &mut written);
    assert_true(processed == 0 || written == 0, "Encode with tiny output buffer fails or writes 0");

    aptx_finish(ctx);
}

fn main() {
    println!("=== Running various inputs test ===");
    test_aptx_encode_decode_various();

    println!("\n=== Running HD mode test ===");
    test_aptx_hd_mode();

    println!("\n=== Running decode sync test ===");
    test_aptx_decode_sync();

    println!("\n=== Running invalid inputs test ===");
    test_aptx_invalid_inputs();
}
