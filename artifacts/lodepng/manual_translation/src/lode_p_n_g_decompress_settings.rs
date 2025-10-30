use crate::*;
use std::os::raw::c_uint;
use std::os::raw::c_void;


#[derive(Clone)]
pub struct LodePngDecompressSettings {
    pub ignore_adler32: c_uint,
    pub ignore_nlen: c_uint,
    pub max_output_size: usize,
    pub custom_zlib: Option<fn(&mut *mut u8, &mut usize, &u8, usize, &LodePngDecompressSettings) -> c_uint>,
    pub custom_inflate: Option<fn(&mut *mut u8, &mut usize, &u8, usize, &LodePngDecompressSettings) -> c_uint>,
    pub custom_context: Option<*const c_void>,
}

