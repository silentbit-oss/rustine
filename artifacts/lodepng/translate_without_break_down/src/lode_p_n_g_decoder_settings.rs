use crate::*;
use std::os::raw::c_uint;



pub struct LodePNGDecoderSettings {
    pub zlibsettings: LodePNGDecompressSettings,
    pub ignore_crc: c_uint,
    pub ignore_critical: c_uint,
    pub ignore_end: c_uint,
    pub color_convert: c_uint,
    pub read_text_chunks: c_uint,
    pub remember_unknown_chunks: c_uint,
    pub max_text_size: usize,
    pub max_icc_size: usize,
}

