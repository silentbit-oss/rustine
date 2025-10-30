use crate::*;


pub struct LodePNGEncoderSettings {
    pub zlibsettings: LodePNGCompressSettings,
    pub auto_convert: u32,
    pub filter_palette_zero: u32,
    pub filter_strategy: LodePngFilterStrategy,
    pub predefined_filters: Option<Vec<u8>>,
    pub force_palette: u32,
    pub add_id: u32,
    pub text_compression: u32,
}

