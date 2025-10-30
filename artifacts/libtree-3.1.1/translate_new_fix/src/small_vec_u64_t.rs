use crate::*;
use std::mem::MaybeUninit;


#[derive(Clone)]
pub struct SmallVecU64T {
    pub buf: [u64; 16],
    pub p: Option<Box<[u64]>>,
    pub n: usize,
    pub capacity: usize,
}

