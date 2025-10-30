use crate::*;
use std::os::raw::c_uchar;
use std::os::raw::c_void;


#[derive(Clone)]
pub struct LodePNGDecompressSettings {
    pub ignore_adler32: u32,
    pub ignore_nlen: u32,
    pub max_output_size: usize,
    pub custom_zlib: Option<fn(*mut *mut c_uchar, *mut usize, *const c_uchar, usize, *const LodePNGDecompressSettings) -> u32>,
    pub custom_inflate: Option<fn(*mut *mut c_uchar, *mut usize, *const c_uchar, usize, *const LodePNGDecompressSettings) -> u32>,
    pub custom_context: Option<*const c_void>,
}

