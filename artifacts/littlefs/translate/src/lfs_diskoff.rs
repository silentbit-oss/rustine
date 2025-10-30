use crate::*;
use crate::types::lfs_block_t;
use crate::types::lfs_off_t;

#[derive(Clone)]
pub struct LfsDiskoff {
    pub block: u32,
    pub off: u32,
}

