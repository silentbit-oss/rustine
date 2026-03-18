use crate::*;

#[derive(Clone)]
pub struct ZopfliHash {
    pub head: Option<Vec<i32>>,
    pub prev: Option<Vec<u16>>,
    pub hashval: Option<Vec<i32>>,
    pub val: i32,
    pub head2: Option<Vec<i32>>,
    pub prev2: Option<Vec<u16>>,
    pub hashval2: Option<Vec<i32>>,
    pub val2: i32,
    pub same: Option<Vec<u16>>,
}

