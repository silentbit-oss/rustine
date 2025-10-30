use crate::*;
use std::os::raw;


#[derive(Clone)]
pub struct XColor {
    pub pixel: raw::c_ulong,
    pub red: raw::c_ushort,
    pub green: raw::c_ushort,
    pub blue: raw::c_ushort,
    pub flags: raw::c_char,
    pub pad: raw::c_char,
}

