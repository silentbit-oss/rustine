use crate::*;
use std::clone::Clone;

#[derive(Clone)]
pub struct LfsFcrc {
    pub size: u32,
    pub crc: u32,
}

