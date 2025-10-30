use crate::*;
use std::clone::Clone;


pub type lfs_block_t = u32;
pub type lfs_off_t = u32;

#[derive(Clone)]
pub struct LfsDir {
    pub next: Option<Box<LfsDir>>,
    pub id: u16,
    pub type_: u8,
    pub m: LfsMdir,
    pub pos: lfs_off_t,
    pub head: [lfs_block_t; 2],
}

#[derive(Clone)]
pub struct LfsMdir {
    pub pair: [lfs_block_t; 2],
    pub rev: u32,
    pub off: lfs_off_t,
    pub etag: u32,
    pub count: u16,
    pub erased: bool,
    pub split: bool,
    pub tail: [lfs_block_t; 2],
}

