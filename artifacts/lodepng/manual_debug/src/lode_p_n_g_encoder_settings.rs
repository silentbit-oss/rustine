use crate::*;
use std::os::raw::c_uchar;

#[derive(Clone)]
pub struct LodePngEncoderSettings {
    pub zlibsettings: LodePngCompressSettings,
    pub auto_convert: u32,
    pub filter_palette_zero: u32,
    pub filter_strategy: LodePNGFilterStrategy,
    pub predefined_filters: Option<*const c_uchar>,
    pub force_palette: u32,
    pub add_id: u32,
    pub text_compression: u32,
}

