use crate::*;

#[derive(Clone)]
pub struct ExtractZlib {
    pub zlibinfo: Option<Box<ZlibBlockInfo>>,
    pub error: i32,
}

