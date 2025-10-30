use crate::*;
use std::mem;

#[derive(Clone)]
pub struct LfsAttr {
    pub type_: u8,
    pub buffer: Option<Vec<u8>>,
    pub size: u32,
}

