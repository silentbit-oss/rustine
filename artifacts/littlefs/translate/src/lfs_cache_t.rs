use crate::*;
use std::vec::Vec;

#[derive(Clone)]
pub struct LfsCache {
    pub block: u32,
    pub off: u32,
    pub size: u32,
    pub buffer: Option<Vec<u8>>,
}

