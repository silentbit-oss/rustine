use crate::*;
use std::mem::MaybeUninit;


#[derive(Clone)]
pub struct MiHeapAreaS {
    pub blocks: Option<Box<[MaybeUninit<u8>]>>,
    pub reserved: usize,
    pub committed: usize,
    pub used: usize,
    pub block_size: usize,
    pub full_block_size: usize,
    pub heap_tag: i32,
}

