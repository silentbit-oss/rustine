use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct LodePngIccCurve {
    pub type_: u32,
    pub lut: Option<Vec<f32>>,
    pub lut_size: usize,
    pub gamma: f32,
    pub a: f32,
    pub b: f32,
    pub c: f32,
    pub d: f32,
    pub e: f32,
    pub f: f32,
}

