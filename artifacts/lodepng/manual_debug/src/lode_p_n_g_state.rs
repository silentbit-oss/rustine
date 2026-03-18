use crate::*;
use std::os::raw::c_uchar;
use std::os::raw::c_uint;
use std::os::raw::c_void;


#[derive(Clone)]
pub struct LodePngState {
    pub decoder: LodePngDecoderSettings,
    pub encoder: LodePngEncoderSettings,
    pub info_raw: LodePNGColorMode,
    pub info_png: LodePngInfo,
    pub error: u32,
}

