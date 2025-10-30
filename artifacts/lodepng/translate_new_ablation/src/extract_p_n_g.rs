use crate::*;

#[derive(Clone)]
pub struct ExtractPng {
    pub zlibinfo: Option<Box<ZlibBlockInfo>>,
    pub error: i32,
}

