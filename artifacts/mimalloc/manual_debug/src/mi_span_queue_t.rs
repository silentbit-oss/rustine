use crate::*;
use std::sync::atomic::AtomicUsize;



pub struct MiSpanQueueS {
    pub first: Option<Box<MiPageS>>,
    pub last: Option<Box<MiPageS>>,
    pub slice_count: usize,
}

pub type MiSpanQueueT = MiSpanQueueS;

