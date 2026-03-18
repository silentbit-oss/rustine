use crate::*;

#[derive(Clone)]
pub struct StringTableT {
    pub arr: Option<Vec<char>>,
    pub n: usize,
    pub capacity: usize,
}

