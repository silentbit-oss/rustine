use crate::*;
use std::fs::File;

#[derive(Clone)]
pub struct LfsFileConfig {
    pub buffer: Option<Vec<u8>>,
    pub attrs: Option<Vec<LfsAttr>>,
    pub attr_count: crate::types::lfs_size_t,
}

