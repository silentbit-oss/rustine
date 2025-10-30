use crate::*;
use std::sync::Arc;

#[derive(Clone)]
pub struct LfsConfig {
    pub context: Option<Arc<()>>,
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

