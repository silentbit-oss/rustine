use crate::*;

#[derive(Clone)]
pub struct SplitCostContext {
    pub lz77: Option<ZopfliLZ77Store>,
    pub start: usize,
    pub end: usize,
}

