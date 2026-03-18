use crate::*;
use std::sync::atomic::AtomicUsize;

pub struct MiSegmentsTldS {
    pub spans: [MiSpanQueueT; 36],
    pub count: usize,
    pub peak_count: usize,
    pub current_size: usize,
    pub peak_size: usize,
    pub reclaim_count: usize,
    pub subproc: Option<Box<MiSubprocT>>,
    pub stats: Option<Box<MiStatsS>>,
}

pub type MiSegmentsTldT = MiSegmentsTldS;

