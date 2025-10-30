use crate::*;

#[derive(Clone)]
pub struct LodePNGColorMode {
    pub colortype: LodePNGColorType,
    pub bitdepth: u32,
    pub palette: Option<Vec<u8>>,
    pub palettesize: usize,
    pub key_defined: u32,
    pub key_r: u32,
    pub key_g: u32,
    pub key_b: u32,
}

