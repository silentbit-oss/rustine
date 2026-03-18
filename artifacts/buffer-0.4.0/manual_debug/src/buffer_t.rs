use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct BufferT {
    pub len: usize,
    pub alloc: Option<Vec<char>>,
    pub data: Option<Vec<char>>,
}

