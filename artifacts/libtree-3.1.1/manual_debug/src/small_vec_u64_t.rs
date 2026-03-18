use crate::*;
use std::mem::MaybeUninit;


#[derive(Clone, Debug)]
pub struct SmallVecU64T {
    pub buf: [u64; 16],
    pub p: Option<Vec<u64>>,
    pub n: usize,
    pub capacity: usize,
}

