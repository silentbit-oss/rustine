use crate::*;
use std::clone::Clone;


pub type lfs_block_t = u32;
pub type lfs_size_t = u32;

#[derive(Clone)]
pub struct LfsCache {
    pub block: u32,
    pub off: u32,
    pub size: u32,
    pub buffer: Option<Vec<u8>>,
}

#[derive(Clone)]
pub struct LfsGstate {
    pub tag: u32,
    pub pair: [lfs_block_t; 2],
}

#[derive(Clone)]
pub struct LfsMdir {
    pub pair: [lfs_block_t; 2],
    pub rev: u32,
    pub off: u32,
    pub etag: u32,
    pub count: u16,
    pub erased: bool,
    pub split: bool,
    pub tail: [lfs_block_t; 2],
}

#[derive(Clone)]
pub struct LfsConfig {
    pub context: Option<std::sync::Arc<()>>,
    pub read: Option<fn(&LfsConfig, u32, u32, &mut [u8], u32) -> i32>,
    pub prog: Option<fn(&LfsConfig, u32, u32, &[u8], u32) -> i32>,
    pub erase: Option<fn(&LfsConfig, u32) -> i32>,
    pub sync: Option<fn(&LfsConfig) -> i32>,
    pub read_size: u32,
    pub prog_size: u32,
    pub block_size: u32,
    pub block_count: u32,
    pub block_cycles: i32,
    pub cache_size: u32,
    pub lookahead_size: u32,
    pub compact_thresh: u32,
    pub read_buffer: Option<Vec<u8>>,
    pub prog_buffer: Option<Vec<u8>>,
    pub lookahead_buffer: Option<Vec<u8>>,
    pub name_max: u32,
    pub file_max: u32,
    pub attr_max: u32,
    pub metadata_max: u32,
    pub inline_max: u32,
}

#[derive(Clone)]
pub struct LfsMlist {
    pub next: Option<Box<LfsMlist>>,
    pub id: u16,
    pub r#type: u8,
    pub m: LfsMdir,
}

#[derive(Clone)]
pub struct LfsLookahead {
    pub start: lfs_block_t,
    pub size: lfs_block_t,
    pub next: lfs_block_t,
    pub ckpoint: lfs_block_t,
    pub buffer: Option<Vec<u8>>,
}

#[derive(Clone)]
pub struct Lfs {
    pub rcache: LfsCache,
    pub pcache: LfsCache,
    pub root: [lfs_block_t; 2],
    pub mlist: Option<Box<LfsMlist>>,
    pub seed: u32,
    pub gstate: LfsGstate,
    pub gdisk: LfsGstate,
    pub gdelta: LfsGstate,
    pub lookahead: LfsLookahead,
    pub cfg: Option<Box<LfsConfig>>,
    pub block_count: lfs_size_t,
    pub name_max: lfs_size_t,
    pub file_max: lfs_size_t,
    pub attr_max: lfs_size_t,
    pub inline_max: lfs_size_t,
}

