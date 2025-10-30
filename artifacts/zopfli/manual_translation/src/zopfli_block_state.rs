use crate::*;

#[derive(Clone)]
pub struct ZopfliBlockState {
    pub options: Option<Box<ZopfliOptions>>,
    pub lmc: Option<Box<ZopfliLongestMatchCache>>,
    pub blockstart: usize,
    pub blockend: usize,
}

