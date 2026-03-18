use crate::*;


pub struct BzStream {
    pub next_in: Option<Box<[u8]>>,
    pub avail_in: u32,
    pub total_in_lo32: u32,
    pub total_in_hi32: u32,
    pub next_out: Option<Box<[u8]>>,
    pub avail_out: u32,
    pub total_out_lo32: u32,
    pub total_out_hi32: u32,
    pub state: Option<Box<()>>,
    pub bzalloc: Option<Box<dyn FnMut(Option<Box<()>>, i32, i32) -> Option<Box<()>>>>,
    pub bzfree: Option<Box<dyn FnMut(Option<Box<()>>, Option<Box<()>>)>>,
    pub opaque: Option<Box<()>>,
}

