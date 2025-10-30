use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct Ucvector {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub allocsize: usize,
}

