use crate::*;
use std::vec::Vec;


#[derive(Clone)]
pub struct SplitCostContext {
    pub lz77: Option<ZopfliLz77Store>,
    pub start: usize,
    pub end: usize,
}

