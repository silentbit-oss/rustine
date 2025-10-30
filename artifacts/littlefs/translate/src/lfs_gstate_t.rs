use crate::*;
use std::clone::Clone;


#[derive(Clone)]
pub struct LfsGstate {
    pub tag: u32,
    pub pair: [lfs_block_t; 2],
}

pub type lfs_block_t = u32;

