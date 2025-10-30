use crate::*;
use std::os::raw::c_uint;
use std::os::raw::c_void;



pub struct LodePNGDecompressSettings {
    pub ignore_adler32: c_uint,
    pub ignore_nlen: c_uint,
    pub max_output_size: usize,
    pub custom_zlib: Option<fn(&mut Option<Vec<u8>>, &mut usize, &[u8], usize, &LodePNGDecompressSettings) -> c_uint>,
    pub custom_inflate: Option<fn(&mut Option<Vec<u8>>, &mut usize, &[u8], usize, &LodePNGDecompressSettings) -> c_uint>,
    pub custom_context: Option<Box<c_void>>,
}

