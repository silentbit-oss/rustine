use crate::*;
use std::clone::Clone;


pub type lfs_tag_t = u32;

#[derive(Clone)]
pub struct LfsMattr {
    pub tag: lfs_tag_t,
    pub buffer: Option<Vec<u8>>,
}

