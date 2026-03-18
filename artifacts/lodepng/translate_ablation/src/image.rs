use crate::*;

#[derive(Clone)]
pub struct Image {
    pub data: Option<Vec<u8>>,
    pub data_size: usize,
    pub width: u32,
    pub height: u32,
    pub colorType: LodePNGColorType,
    pub bitDepth: u32,
}

