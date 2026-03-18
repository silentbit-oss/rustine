use crate::*;
use std::sync::atomic::AtomicUsize;


pub type HeapPageVisitorFun = fn(
    heap: Option<Box<MiHeapS>>,
    pq: MiPageQueueT,
    page: Option<Box<MiPageS>>,
    arg1: Option<Box<()>>,
    arg2: Option<Box<()>>,
) -> bool;

