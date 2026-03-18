use crate::*;
use std::mem::size_of;



pub struct SdMarkdown {
    pub cb: SdCallbacks,
    pub opaque: Option<Box<dyn std::any::Any>>,
    pub refs: [Option<Box<LinkRef>>; 8],
    pub active_char: [u8; 256],
    pub work_bufs: [Stack; 2],
    pub ext_flags: u32,
    pub max_nesting: usize,
    pub max_table_cols: usize,
    pub in_link_body: i32,
}

