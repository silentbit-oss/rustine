use crate::*;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;

pub struct MiTldS;

pub type MiTldT = Option<Box<MiTldS>>;

pub struct MiHeapS {
    pub tld: MiTldT,
    pub thread_id: usize,
    pub random: MiRandomCtxT,
    pub page_free: Option<Box<MiPageS>>,
    pub page_used: [MiPageQueueT; 129],
    pub page_full: [MiPageQueueT; 129],
    pub page_cache: [MiPageQueueT; 129],
    pub page_reset: [MiPageQueueT; 129],
    pub page_retired_min: usize,
    pub page_retired_max: usize,
    pub page_count: usize,
    pub page_retired_count: usize,
    pub page_retired_first: Option<Box<MiPageS>>,
    pub page_retired_last: Option<Box<MiPageS>>,
    pub segments_tld: MiSegmentsTldT,
    pub padding: MiPaddingT,
    pub stats: Option<Box<MiStatsS>>,
}

pub type MiHeapT = Option<Box<MiHeapS>>;

pub struct MiHeapS2 {
    pub tld: Option<Box<MiTldS>>,
    pub thread_delayed_free: AtomicPtr<MiBlockS>,
    pub thread_id: usize,
    pub arena_id: mi_arena_id_t,
    pub cookie: usize,
    pub keys: [usize; 2],
    pub random: MiRandomCtxT,
    pub page_count: usize,
    pub page_retired_min: usize,
    pub page_retired_max: usize,
    pub generic_count: i64,
    pub generic_collect_count: i64,
    pub next: Option<Box<MiHeapS2>>,
    pub no_reclaim: bool,
    pub tag: u8,
    pub pages_free_direct: [Option<Box<MiPageS>>; (128 + ((((std::mem::size_of::<MiPaddingT>()) + (1 << 3)) - 1) / (1 << 3))) + 1],
    pub pages: [MiPageQueueT; (73 + 1) + 1],
}

pub struct MiTldS2 {
    pub heartbeat: u64,
    pub recurse: bool,
    pub heap_backing: Option<Box<MiHeapS2>>,
    pub heaps: Option<Box<MiHeapS2>>,
    pub segments: MiSegmentsTldT,
    pub stats: MiStatsS,
}

