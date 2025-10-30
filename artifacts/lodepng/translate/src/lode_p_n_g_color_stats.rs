use crate::*;

#[derive(Clone)]
pub struct LodePNGColorStats {
    pub colored: u32,
    pub key: u32,
    pub key_r: u16,
    pub key_g: u16,
    pub key_b: u16,
    pub alpha: u32,
    pub numcolors: u32,
    pub palette: [u8; 1024],
    pub bits: u32,
    pub numpixels: usize,
    pub allow_palette: u32,
    pub allow_greyscale: u32,
}

