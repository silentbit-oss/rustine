use crate::*;


pub struct LodePNGCompressSettings {
    pub btype: u32,
    pub use_lz77: u32,
    pub windowsize: u32,
    pub minmatch: u32,
    pub nicematch: u32,
    pub lazymatching: u32,
    pub custom_zlib: Option<fn(&mut Vec<u8>, &[u8], &LodePNGCompressSettings) -> u32>,
    pub custom_deflate: Option<fn(&mut Vec<u8>, &[u8], &LodePNGCompressSettings) -> u32>,
    pub custom_context: Option<Box<dyn std::any::Any>>,
}

