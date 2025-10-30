use crate::*;

#[derive(Clone)]
pub struct LodePNGDecoderSettings {
    pub zlibsettings: LodePNGDecompressSettings,
    pub ignore_crc: u32,
    pub ignore_critical: u32,
    pub ignore_end: u32,
    pub color_convert: u32,
    pub read_text_chunks: u32,
    pub remember_unknown_chunks: u32,
    pub max_text_size: usize,
    pub max_icc_size: usize,
}

