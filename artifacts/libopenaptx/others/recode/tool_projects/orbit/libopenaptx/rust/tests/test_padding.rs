//! Encoding padding tests
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

#[allow(unused)]
mod common;

use libopenaptx::{aptx_init, aptx_finish, aptx_encode, aptx_encode_finish};

#[test]
fn test_encode_padding() {
    let mut ctx = aptx_init(0).expect("Failed to initialize encoder");

    let pcm = [1u8, 2u8, 3u8];
    let mut out = [0u8; 8];
    let mut written: usize = 0;

    let pcm_len = pcm.len();
    let out_len = out.len();
    let used = aptx_encode(&mut ctx, &pcm, pcm_len, &mut out, out_len, &mut written);
    let _ = used;  // Suppress unused variable warning
    assert!(written == 0, "Should not write on partial input");

    aptx_encode_finish(&mut ctx, &mut out, out_len, &mut written);
    assert!(written > 0, "Finish should pad with silence");

    println!("aptX encode finish with padding passed");
    aptx_finish(ctx);
}
