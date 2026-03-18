use crate::*;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;


pub type MiBlockVisitFun = fn(
    heap: Option<&MiHeapS>,
    area: Option<&MiHeapAreaS>,
    block: Option<&[u8]>,
    block_size: usize,
    arg: Option<&[u8]>,
) -> bool;

