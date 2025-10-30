use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LodePNGColorType {
    LCT_GREY = 0,
    LCT_RGB = 2,
    LCT_PALETTE = 3,
    LCT_GREY_ALPHA = 4,
    LCT_RGBA = 6,
}

pub const LCT_MAX_OCTET_VALUE: u8 = 255;

