use crate::*;
use std::os::raw::c_uchar;
use std::os::raw::c_void;


#[derive(Clone)]
pub struct LodePngCompressSettings {
    pub btype: u32,
    pub use_lz77: u32,
    pub windowsize: u32,
    pub minmatch: u32,
    pub nicematch: u32,
    pub lazymatching: u32,
    pub custom_zlib: Option<fn(*mut *mut c_uchar, *mut usize, *const c_uchar, usize, *const LodePngCompressSettings) -> u32>,
    pub custom_deflate: Option<fn(*mut *mut c_uchar, *mut usize, *const c_uchar, usize, *const LodePngCompressSettings) -> u32>,
    pub custom_context: Option<*const c_void>,
}

