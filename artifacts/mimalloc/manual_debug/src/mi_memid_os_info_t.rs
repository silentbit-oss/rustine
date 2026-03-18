use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct MiMemidOsInfo {
    pub base: Option<Box<[u8]>>,
    pub size: usize,
}

