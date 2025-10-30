use crate::*;

#[derive(Clone)]
pub struct ZopfliLZ77Store {
    pub litlens: Option<Vec<u16>>,
    pub dists: Option<Vec<u16>>,
    pub size: usize,
    pub data: Option<Vec<u8>>,
    pub pos: Option<Vec<usize>>,
    pub ll_symbol: Option<Vec<u16>>,
    pub d_symbol: Option<Vec<u16>>,
    pub ll_counts: Option<Vec<usize>>,
    pub d_counts: Option<Vec<usize>>,
}

