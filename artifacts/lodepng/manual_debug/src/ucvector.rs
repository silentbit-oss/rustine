use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct Ucvector {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub allocsize: usize,
}

