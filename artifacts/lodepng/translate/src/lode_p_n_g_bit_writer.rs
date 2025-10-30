use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct LodePNGBitWriter {
    pub data: Option<Box<Ucvector>>,
    pub bp: u8,
}

