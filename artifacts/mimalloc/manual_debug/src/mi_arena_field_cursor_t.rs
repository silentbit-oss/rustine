use crate::*;
use std::sync::atomic::AtomicUsize;



pub struct MiArenaFieldCursorS {
    pub os_list_count: usize,
    pub start: usize,
    pub end: usize,
    pub bitmap_idx: usize,
    pub subproc: Option<Box<MiSubprocT>>,
    pub visit_all: bool,
    pub hold_visit_lock: bool,
}

pub type MiArenaFieldCursorT = MiArenaFieldCursorS;

