use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct LodePngBitWriter {
    pub data: Option<Box<Ucvector>>,
    pub bp: u8,
}

