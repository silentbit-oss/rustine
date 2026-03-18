use crate::*;
use std::ffi::c_void;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;


pub struct MiSegmentS {
    pub memid: MiMemidS,
    pub allow_decommit: bool,
    pub allow_purge: bool,
    pub segment_size: usize,
    pub subproc: Option<Box<MiSubprocT>>,
    pub purge_expire: i64,
    pub purge_mask: Mi_Commit_Mask_T,
    pub commit_mask: Mi_Commit_Mask_T,
    pub next: Option<Box<MiSegmentS>>,
    pub was_reclaimed: bool,
    pub dont_free: bool,
    pub abandoned: usize,
    pub abandoned_visits: usize,
    pub used: usize,
    pub cookie: usize,
    pub abandoned_os_next: Option<Box<MiSegmentS>>,
    pub abandoned_os_prev: Option<Box<MiSegmentS>>,
    pub segment_slices: usize,
    pub segment_info_slices: usize,
    pub kind: MiSegmentKindT,
    pub slice_entries: usize,
    pub thread_id: AtomicUsize,
    pub slices: [Mi_Slice_T; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) + 1],
}

pub type MiSegmentT = MiSegmentS;

pub struct MiSubprocS {
    pub abandoned_count: AtomicUsize,
    pub abandoned_os_list_count: AtomicUsize,
    pub abandoned_os_lock: Mutex<()>,
    pub abandoned_os_visit_lock: Mutex<()>,
    pub abandoned_os_list: Option<Box<MiSegmentT>>,
    pub abandoned_os_list_tail: Option<Box<MiSegmentT>>,
    pub memid: MiMemidS,
}

pub type MiSubprocT = MiSubprocS;

