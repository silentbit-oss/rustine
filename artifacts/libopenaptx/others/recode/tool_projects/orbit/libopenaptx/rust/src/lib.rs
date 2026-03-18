//! libopenaptx - Open Source implementation of aptX codec
//!
//! This crate provides encoding and decoding for aptX and aptX HD audio codecs.
//!
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

pub mod openaptx;

// Re-export public API
pub use openaptx::{
    OPENAPTX_MAJOR,
    OPENAPTX_MINOR,
    OPENAPTX_PATCH,
    aptx_major,
    aptx_minor,
    aptx_patch,
    aptx_context,
    aptx_init,
    aptx_reset,
    aptx_finish,
    aptx_encode,
    aptx_encode_finish,
    aptx_decode,
    aptx_decode_sync,
    aptx_decode_sync_finish,
};
