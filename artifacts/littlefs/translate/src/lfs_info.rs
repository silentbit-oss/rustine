use crate::*;
use std::mem::MaybeUninit;


#[derive(Clone)]
pub struct LfsInfo {
    pub type_: u8,
    pub size: lfs_size_t,
    pub name: [u8; 255 + 1],
}

