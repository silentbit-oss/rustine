use crate::*;
use std::clone::Clone;


pub type lfs_size_t = u32;

#[derive(Clone)]
pub struct LfsFsinfo {
    pub disk_version: u32,
    pub block_size: lfs_size_t,
    pub block_count: lfs_size_t,
    pub name_max: lfs_size_t,
    pub file_max: lfs_size_t,
    pub attr_max: lfs_size_t,
}

