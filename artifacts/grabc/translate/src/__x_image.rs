use crate::*;
use std::os::raw::c_char;
use std::os::raw::c_int;
use std::os::raw::c_ulong;


#[derive(Clone)]
pub struct XImage {
    pub width: c_int,
    pub height: c_int,
    pub xoffset: c_int,
    pub format: c_int,
    pub data: Option<Vec<c_char>>,
    pub byte_order: c_int,
    pub bitmap_unit: c_int,
    pub bitmap_bit_order: c_int,
    pub bitmap_pad: c_int,
    pub depth: c_int,
    pub bytes_per_line: c_int,
    pub bits_per_pixel: c_int,
    pub red_mask: c_ulong,
    pub green_mask: c_ulong,
    pub blue_mask: c_ulong,
    pub obdata: XPointer,
    pub f: XImageFuncs,
}

pub type XPointer = Option<Box<()>>;

#[derive(Clone)]
pub struct XImageFuncs;

