use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct LodePngBitWriter {
    pub data: Option<Ucvector>,
    pub bp: u8,
}

