use crate::*;
use std::clone::Clone;
use std::fs::File;


pub type lfs_block_t = u32;
pub type lfs_off_t = u32;
pub type lfs_size_t = u32;

#[derive(Clone)]
pub struct LfsCache {
    pub block: u32,
    pub off: u32,
    pub size: u32,
    pub buffer: Option<Vec<u8>>,
}

#[derive(Clone)]
pub struct LfsFileConfig {
    pub buffer: Option<Vec<u8>>,
    pub attrs: Option<Vec<LfsAttr>>,
    pub attr_count: crate::types::lfs_size_t,
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

#[derive(Clone)]
pub struct LfsFile {
    pub next: Option<Box<LfsFile>>,
    pub id: u16,
    pub type_: u8,
    pub m: LfsMdir,
    pub ctz: LfsCtz,
    pub flags: u32,
    pub pos: lfs_off_t,
    pub block: lfs_block_t,
    pub off: lfs_off_t,
    pub cache: LfsCache,
    pub cfg: Option<Box<LfsFileConfig>>,
}

#[derive(Clone)]
pub struct LfsCtz {
    pub head: lfs_block_t,
    pub size: lfs_size_t,
}

