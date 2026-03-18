use crate::*;

#[derive(Clone)]
pub struct ZopfliLongestMatchCache {
    pub length: Option<Vec<u16>>,
    pub dist: Option<Vec<u16>>,
    pub sublen: Option<Vec<u8>>,
}

