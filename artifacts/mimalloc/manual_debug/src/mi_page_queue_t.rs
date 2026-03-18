use crate::*;
use std::sync::atomic::AtomicUsize;



pub struct MiPageQueueS {
    pub first: Option<Box<MiPageS>>,
    pub last: Option<Box<MiPageS>>,
    pub block_size: usize,
}

pub type MiPageQueueT = MiPageQueueS;

