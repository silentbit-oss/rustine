use crate::*;
use std::sync::Arc;

#[derive(Clone)]
pub struct LfsDirFindMatch {
    pub lfs: Option<Box<Lfs>>,
    pub name: Option<Vec<u8>>,
    pub size: u32,
}

