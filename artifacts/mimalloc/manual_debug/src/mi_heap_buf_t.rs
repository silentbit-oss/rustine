use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct MiHeapBufS {
    pub buf: Option<Vec<u8>>,
    pub size: usize,
    pub used: usize,
    pub can_realloc: bool,
}

