use crate::*;

#[derive(Clone)]
pub struct SymbolStats {
    pub litlens: [usize; 288],
    pub dists: [usize; 32],
    pub ll_symbols: [f64; 288],
    pub d_symbols: [f64; 32],
}

