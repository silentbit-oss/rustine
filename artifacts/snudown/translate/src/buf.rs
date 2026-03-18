use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct Buf {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub asize: usize,
    pub unit: usize,
}

