use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct LodePngBitReader {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub bitsize: usize,
    pub bp: usize,
    pub buffer: u32,
}

