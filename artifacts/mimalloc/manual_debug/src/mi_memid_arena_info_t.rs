use crate::*;
use std::mem;


#[derive(Clone)]
pub struct MiMemidArenaInfo {
    pub block_index: usize,
    pub id: i32,
    pub is_exclusive: bool,
}

