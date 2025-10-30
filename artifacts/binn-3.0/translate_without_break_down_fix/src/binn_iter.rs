use crate::*;

#[derive(Clone)]
pub struct BinnIter {
    pub pnext: Option<Vec<u8>>,
    pub plimit: Option<Vec<u8>>,
    pub type_: i32,
    pub count: i32,
    pub current: i32,
}

