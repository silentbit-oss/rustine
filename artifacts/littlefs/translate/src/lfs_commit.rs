use crate::*;
use std::clone::Clone;


pub type lfs_block_t = u32;
pub type lfs_off_t = u32;
pub type lfs_tag_t = u32;

#[derive(Clone)]
pub struct LfsCommit {
    pub block: lfs_block_t,
    pub off: lfs_off_t,
    pub ptag: lfs_tag_t,
    pub crc: u32,
    pub begin: lfs_off_t,
    pub end: lfs_off_t,
}

