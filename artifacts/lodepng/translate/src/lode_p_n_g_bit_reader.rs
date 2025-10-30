use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct LodePngBitReader {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub bitsize: usize,
    pub bp: usize,
    pub buffer: u32,
}

