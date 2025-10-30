use crate::*;

#[derive(Clone)]
pub struct Hash {
    pub head: Option<Vec<i32>>,
    pub chain: Option<Vec<u16>>,
    pub val: Option<Vec<i32>>,
    pub headz: Option<Vec<i32>>,
    pub chainz: Option<Vec<u16>>,
    pub zeros: Option<Vec<u16>>,
}

