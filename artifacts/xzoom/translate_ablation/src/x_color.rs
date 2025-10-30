use crate::*;
use std::os::raw::c_char;
use std::os::raw::c_ulong;
use std::os::raw::c_ushort;


pub struct XColor {
    pub pixel: c_ulong,
    pub red: c_ushort,
    pub green: c_ushort,
    pub blue: c_ushort,
    pub flags: c_char,
    pub pad: c_char,
}

