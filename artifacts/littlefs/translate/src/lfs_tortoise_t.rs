use crate::*;
use crate::types::lfs_block_t;
use crate::types::lfs_size_t;


#[derive(Clone)]
pub struct LfsTortoiseT {
    pub pair: [lfs_block_t; 2],
    pub i: lfs_size_t,
    pub period: lfs_size_t,
}

