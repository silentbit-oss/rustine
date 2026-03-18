//! Encode/decode roundtrip tests
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

use libopenaptx::{aptx_init, aptx_encode, aptx_encode_finish, aptx_decode, aptx_finish};

const NB_SAMPLES: usize = 8;
const NB_CHANNELS: usize = 2;

fn test_roundtrip(hd: i32) {
    let enc = aptx_init(hd).expect("Failed to initialize encoder");
    let dec = aptx_init(hd).expect("Failed to initialize decoder");

    // Need enough samples to exceed latency (90 samples = 23 frames of 4 samples each)
    // Use 32 frames = 128 samples
    const TOTAL_SAMPLES: usize = 128;
    let mut pcm_in: [i16; NB_CHANNELS * TOTAL_SAMPLES] = [0; NB_CHANNELS * TOTAL_SAMPLES];
    for i in 0..NB_CHANNELS * TOTAL_SAMPLES {
        pcm_in[i] = ((i * 256) & 0xFFFF) as i16;
    }

    let mut encoded: [u8; 512] = [0; 512];
    let mut written: usize = 0;
    let mut written_finish: usize = 0;

    // Convert i16 array to bytes (2 bytes per sample, little-endian)
    // The C test casts i16* to unsigned char*, which passes the raw bytes
    // of the i16 array to the encoder. The encoder then interprets every
    // 3 bytes as a 24-bit sample, so the i16 values are read misaligned.
    // To match the C test behavior exactly, we pass the raw i16 bytes.
    let pcm_in_bytes: Vec<u8> = pcm_in.iter()
        .flat_map(|&sample| sample.to_le_bytes())
        .collect();

    // Encode the samples
    let mut enc = enc;
    let encoded_len = encoded.len();
    aptx_encode(
        &mut *enc,
        &pcm_in_bytes,
        pcm_in_bytes.len(),
        &mut encoded,
        encoded_len,
        &mut written
    );
    println!("encoded bytes: {}", written);

    // Flush remaining samples due to latency
    let encoded_remaining = encoded_len - written;
    aptx_encode_finish(
        &mut *enc,
        &mut encoded[written..],
        encoded_remaining,
        &mut written_finish
    );
    println!("encoded finish bytes: {}", written_finish);
    written += written_finish;

    // Decode
    let mut pcm_out: [u8; NB_CHANNELS * (TOTAL_SAMPLES + 100) * 2] = [0; NB_CHANNELS * (TOTAL_SAMPLES + 100) * 2];
    let mut decoded: usize = 0;
    let mut dec = dec;
    let pcm_out_len = pcm_out.len();
    aptx_decode(
        &mut *dec,
        &encoded,
        written,
        &mut pcm_out,
        pcm_out_len,
        &mut decoded
    );
    println!("decoded bytes: {}", decoded);

    assert!(decoded > 0, "PCM decoded length should be > 0");
    println!("✅ {} passed", if hd != 0 { "aptX HD roundtrip" } else { "aptX Classic roundtrip" });

    aptx_finish(enc);
    aptx_finish(dec);
}

#[test]
fn test_roundtrip_classic() {
    test_roundtrip(0);
}

#[test]
fn test_roundtrip_hd() {
    test_roundtrip(1);
}
