use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct LodePngIcc {
    pub inputspace: i32,
    pub version_major: i32,
    pub version_minor: i32,
    pub version_bugfix: i32,
    pub illuminant: [f32; 3],
    pub has_chad: u32,
    pub chad: [f32; 9],
    pub has_whitepoint: u32,
    pub white: [f32; 3],
    pub has_chromaticity: u32,
    pub red: [f32; 3],
    pub green: [f32; 3],
    pub blue: [f32; 3],
    pub has_trc: u32,
    pub trc: [LodePngIccCurve; 3],
}

