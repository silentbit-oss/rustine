use crate::*;
use lazy_static::lazy_static;
use std::mem::zeroed;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicI64;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicU32;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
pub static _MI_PROCESS_IS_INITIALIZED: AtomicBool = AtomicBool::new(false);


pub static MI_ARENA_COUNT: AtomicUsize = AtomicUsize::new(0);


pub static MI_ARENAS_PURGE_EXPIRE: AtomicI64 = AtomicI64::new(0);


pub static MI_ARENA_STATIC: Mutex<[u8; ((1 << 3) / 2) * 1024]> = 
    Mutex::new([0; ((1 << 3) / 2) * 1024]);


pub static MI_ARENA_STATIC_TOP: AtomicUsize = AtomicUsize::new(0);


pub static THREAD_COUNT: AtomicUsize = AtomicUsize::new(1);


pub static OS_PRELOADING: AtomicBool = AtomicBool::new(true);


lazy_static! {
    pub static ref MI_MAX_ERROR_COUNT: AtomicI64 = AtomicI64::new(16);
}


lazy_static! {
    pub static ref MI_MAX_WARNING_COUNT: AtomicI64 = AtomicI64::new(16);
}


lazy_static! {
    pub static ref OUT_BUF: std::sync::Mutex<[u8; 16 * 1024 + 1]> =
        std::sync::Mutex::new([0; 16 * 1024 + 1]);
}


pub static OUT_LEN: AtomicUsize = AtomicUsize::new(0);


pub static MI_OUT_ARG: AtomicPtr<()> = AtomicPtr::new(std::ptr::null_mut());


pub static ERROR_COUNT: AtomicUsize = AtomicUsize::new(0);


pub static WARNING_COUNT: AtomicUsize = AtomicUsize::new(0);


lazy_static! {
    pub static ref RECURSE: AtomicBool = AtomicBool::new(false);
}


pub static mut MI_ERROR_ARG: AtomicPtr<()> = AtomicPtr::new(std::ptr::null_mut());


pub static ALIGNED_BASE: AtomicUsize = AtomicUsize::new(0);


pub static MI_HUGE_START: AtomicUsize = AtomicUsize::new(0);


pub static MI_NUMA_NODE_COUNT: AtomicUsize = AtomicUsize::new(0);


pub static DEFERRED_ARG: AtomicPtr<()> = AtomicPtr::new(std::ptr::null_mut());

// Implement Send and Sync for the raw pointer type to satisfy thread safety requirements
// Remove the duplicate global variable definitions - keep only one definition for each
// The existing definitions elsewhere in the file should be used

// Fix for the thread_id conversion - this should be inside a function
fn convert_thread_id(thread_id: types::mi_threadid_t) -> usize {
    // Use pointer-based conversion as a safe alternative to transmute
    // Convert the thread_id to a raw pointer and then to usize
    let ptr = &thread_id as *const types::mi_threadid_t;
    ptr as usize
}

// Example usage in a function context:
fn some_function(thread_id: types::mi_threadid_t) {
    let thread_id_usize = convert_thread_id(thread_id);
    // ... use thread_id_usize
}

// Remove duplicate Send/Sync implementations - only implement once
// The existing implementations elsewhere should be kept
unsafe impl Send for EnvironWrapper {}
unsafe impl Sync for EnvironWrapper {}

lazy_static::lazy_static! {
    pub static ref environ: std::sync::Mutex<Option<EnvironWrapper>> = 
        std::sync::Mutex::new(None);
}


pub static _MI_HEAP_DEFAULT_KEY: AtomicI32 = AtomicI32::new(-1);

lazy_static! {
    pub static ref _mi_stats_main: Mutex<MiStatsS> = Mutex::new(MiStatsS {
        version: 0,
        pages: MiStatCountS { total: 0, peak: 0, current: 0 },
        reserved: MiStatCountS { total: 0, peak: 0, current: 0 },
        committed: MiStatCountS { total: 0, peak: 0, current: 0 },
        reset: MiStatCountS { total: 0, peak: 0, current: 0 },
        purged: MiStatCountS { total: 0, peak: 0, current: 0 },
        page_committed: MiStatCountS { total: 0, peak: 0, current: 0 },
        pages_abandoned: MiStatCountS { total: 0, peak: 0, current: 0 },
        threads: MiStatCountS { total: 0, peak: 0, current: 0 },
        malloc_normal: MiStatCountS { total: 0, peak: 0, current: 0 },
        malloc_huge: MiStatCountS { total: 0, peak: 0, current: 0 },
        malloc_requested: MiStatCountS { total: 0, peak: 0, current: 0 },
        mmap_calls: MiStatCounterS { total: 0 },
        commit_calls: MiStatCounterS { total: 0 },
        reset_calls: MiStatCounterS { total: 0 },
        purge_calls: MiStatCounterS { total: 0 },
        arena_count: MiStatCounterS { total: 0 },
        malloc_normal_count: MiStatCounterS { total: 0 },
        malloc_huge_count: MiStatCounterS { total: 0 },
        malloc_guarded_count: MiStatCounterS { total: 0 },
        arena_rollback_count: MiStatCounterS { total: 0 },
        arena_purges: MiStatCounterS { total: 0 },
        pages_extended: MiStatCounterS { total: 0 },
        pages_retire: MiStatCounterS { total: 0 },
        page_searches: MiStatCounterS { total: 0 },
        segments: MiStatCountS { total: 0, peak: 0, current: 0 },
        segments_abandoned: MiStatCountS { total: 0, peak: 0, current: 0 },
        segments_cache: MiStatCountS { total: 0, peak: 0, current: 0 },
        _segments_reserved: MiStatCountS { total: 0, peak: 0, current: 0 },
        pages_reclaim_on_alloc: MiStatCounterS { total: 0 },
        pages_reclaim_on_free: MiStatCounterS { total: 0 },
        pages_reabandon_full: MiStatCounterS { total: 0 },
        pages_unabandon_busy_wait: MiStatCounterS { total: 0 },
        _stat_reserved: [
            MiStatCountS { total: 0, peak: 0, current: 0 },
            MiStatCountS { total: 0, peak: 0, current: 0 },
            MiStatCountS { total: 0, peak: 0, current: 0 },
            MiStatCountS { total: 0, peak: 0, current: 0 }
        ],
        _stat_counter_reserved: [
            MiStatCounterS { total: 0 },
            MiStatCounterS { total: 0 },
            MiStatCounterS { total: 0 },
            MiStatCounterS { total: 0 }
        ],
        malloc_bins: [(); 74].map(|_| MiStatCountS { total: 0, peak: 0, current: 0 }),
        page_bins: [(); 74].map(|_| MiStatCountS { total: 0, peak: 0, current: 0 }),
    });
}


lazy_static! {
    pub static ref _MI_PAGE_EMPTY: std::sync::Mutex<MiPageS> = std::sync::Mutex::new(MiPageS {
        slice_count: 0,
        slice_offset: 0,
        is_committed: 0,
        is_zero_init: 0,
        is_huge: 0,
        capacity: 0,
        reserved: 0,
        flags: MiPageFlagsS { full_aligned: 0 },
        free_is_zero: 0,
        retire_expire: 0,
        free: None,
        local_free: None,
        used: 0,
        block_size_shift: 0,
        heap_tag: 0,
        block_size: 0,
        page_start: None,
        keys: [0, 0],
        xthread_free: AtomicUsize::new(0),
        xheap: AtomicUsize::new(0),
        next: None,
        prev: None,
        padding: [None],
    });
}


// Add unsafe Send/Sync implementations for the problematic types
unsafe impl Send for MiHeapS {}
unsafe impl Sync for MiHeapS {}
unsafe impl Send for MiSubprocS {}
unsafe impl Sync for MiSubprocS {}
unsafe impl Send for MiSegmentsTldS {}
unsafe impl Sync for MiSegmentsTldS {}

lazy_static! {
    pub static ref _mi_heap_empty: Mutex<MiHeapT> = {
        let empty_heap: MiHeapS = unsafe { zeroed() };
        Mutex::new(Some(Box::new(empty_heap)))
    };
}


lazy_static! {
    pub static ref _mi_heap_default: Mutex<Option<MiHeapT>> = Mutex::new(None);
}

// C: static mi_arena_t * _Atomic mi_arenas[132]
// Idiomatic safe Rust: a global, thread-safe, mutable array of 132 optional arena handles.
// We wrap in a Mutex to avoid data races; each slot holds an owned Box<MiArenaS> or None.
lazy_static! {
    pub static ref mi_arenas: Mutex<[Option<Box<MiArenaS>>; 132]> = Mutex::new([
        // 1–12
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 13–24
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 25–36
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 37–48
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 49–60
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 61–72
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 73–84
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 85–96
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 97–108
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 109–120
        None, None, None, None, None, None, None, None, None, None, None, None,
        // 121–132
        None, None, None, None, None, None, None, None, None, None, None, None
    ]);
}

lazy_static! {
    pub static ref MI_SUBPROC_DEFAULT: Mutex<Option<Box<MiSubprocT>>> = 
        Mutex::new(None);
}
/// Exact per-bin defaults mirrored from the C initializer:
/// Each element is MiStatCountS { total: 0, peak: 0, current: <size> }
/// Count: 36 elements.
pub const TLD_EMPTY_BIN_STATS: [MiStatCountS; 36] = [
    MiStatCountS { total: 0, peak: 0, current: 1  }, // 1
    MiStatCountS { total: 0, peak: 0, current: 1  }, // 2
    MiStatCountS { total: 0, peak: 0, current: 2  }, // 3
    MiStatCountS { total: 0, peak: 0, current: 3  }, // 4
    MiStatCountS { total: 0, peak: 0, current: 4  }, // 5
    MiStatCountS { total: 0, peak: 0, current: 5  }, // 6
    MiStatCountS { total: 0, peak: 0, current: 6  }, // 7
    MiStatCountS { total: 0, peak: 0, current: 7  }, // 8
    MiStatCountS { total: 0, peak: 0, current: 10 }, // 9
    MiStatCountS { total: 0, peak: 0, current: 12 }, // 10
    MiStatCountS { total: 0, peak: 0, current: 14 }, // 11
    MiStatCountS { total: 0, peak: 0, current: 16 }, // 12
    MiStatCountS { total: 0, peak: 0, current: 20 }, // 13
    MiStatCountS { total: 0, peak: 0, current: 24 }, // 14
    MiStatCountS { total: 0, peak: 0, current: 28 }, // 15
    MiStatCountS { total: 0, peak: 0, current: 32 }, // 16
    MiStatCountS { total: 0, peak: 0, current: 40 }, // 17
    MiStatCountS { total: 0, peak: 0, current: 48 }, // 18
    MiStatCountS { total: 0, peak: 0, current: 56 }, // 19
    MiStatCountS { total: 0, peak: 0, current: 64 }, // 20
    MiStatCountS { total: 0, peak: 0, current: 80 }, // 21
    MiStatCountS { total: 0, peak: 0, current: 96 }, // 22
    MiStatCountS { total: 0, peak: 0, current: 112 }, // 23
    MiStatCountS { total: 0, peak: 0, current: 128 }, // 24
    MiStatCountS { total: 0, peak: 0, current: 160 }, // 25
    MiStatCountS { total: 0, peak: 0, current: 192 }, // 26
    MiStatCountS { total: 0, peak: 0, current: 224 }, // 27
    MiStatCountS { total: 0, peak: 0, current: 256 }, // 28
    MiStatCountS { total: 0, peak: 0, current: 320 }, // 29
    MiStatCountS { total: 0, peak: 0, current: 384 }, // 30
    MiStatCountS { total: 0, peak: 0, current: 448 }, // 31
    MiStatCountS { total: 0, peak: 0, current: 512 }, // 32
    MiStatCountS { total: 0, peak: 0, current: 640 }, // 33
    MiStatCountS { total: 0, peak: 0, current: 768 }, // 34
    MiStatCountS { total: 0, peak: 0, current: 896 }, // 35
    MiStatCountS { total: 0, peak: 0, current: 1024 } // 36 (no trailing comma)
];

lazy_static! {
    /// Thread-safe global equivalent of the C `static const mi_tld_t tld_empty`.
    /// The corresponding Rust type per provided dependencies is `MiTldT = Option<Box<MiTldS>>`.
    /// We keep it as `None` to represent the "empty" state safely.
    pub static ref tld_empty: Mutex<MiTldT> = Mutex::new(None);
}

lazy_static! {
    pub static ref _mi_heap_main: Mutex<MiHeapT> = Mutex::new(None);
}

lazy_static! {
    pub static ref TLD_MAIN: Mutex<MiTldS2> = Mutex::new(MiTldS2 {
        heartbeat: 0,
        recurse: false,
        heap_backing: None,
        heaps: None,
        segments: MiSegmentsTldS {
            spans: [
                // 36 elements total (matching [MiSpanQueueS; 36])
                MiSpanQueueS { first: None, last: None, slice_count: 1 },   // 1
                MiSpanQueueS { first: None, last: None, slice_count: 1 },   // 2
                MiSpanQueueS { first: None, last: None, slice_count: 2 },   // 3
                MiSpanQueueS { first: None, last: None, slice_count: 3 },   // 4
                MiSpanQueueS { first: None, last: None, slice_count: 4 },   // 5
                MiSpanQueueS { first: None, last: None, slice_count: 5 },   // 6
                MiSpanQueueS { first: None, last: None, slice_count: 6 },   // 7
                MiSpanQueueS { first: None, last: None, slice_count: 7 },   // 8
                MiSpanQueueS { first: None, last: None, slice_count: 10 },  // 9
                MiSpanQueueS { first: None, last: None, slice_count: 12 },  // 10
                MiSpanQueueS { first: None, last: None, slice_count: 14 },  // 11
                MiSpanQueueS { first: None, last: None, slice_count: 16 },  // 12
                MiSpanQueueS { first: None, last: None, slice_count: 20 },  // 13
                MiSpanQueueS { first: None, last: None, slice_count: 24 },  // 14
                MiSpanQueueS { first: None, last: None, slice_count: 28 },  // 15
                MiSpanQueueS { first: None, last: None, slice_count: 32 },  // 16
                MiSpanQueueS { first: None, last: None, slice_count: 40 },  // 17
                MiSpanQueueS { first: None, last: None, slice_count: 48 },  // 18
                MiSpanQueueS { first: None, last: None, slice_count: 56 },  // 19
                MiSpanQueueS { first: None, last: None, slice_count: 64 },  // 20
                MiSpanQueueS { first: None, last: None, slice_count: 80 },  // 21
                MiSpanQueueS { first: None, last: None, slice_count: 96 },  // 22
                MiSpanQueueS { first: None, last: None, slice_count: 112 }, // 23
                MiSpanQueueS { first: None, last: None, slice_count: 128 }, // 24
                MiSpanQueueS { first: None, last: None, slice_count: 160 }, // 25
                MiSpanQueueS { first: None, last: None, slice_count: 192 }, // 26
                MiSpanQueueS { first: None, last: None, slice_count: 224 }, // 27
                MiSpanQueueS { first: None, last: None, slice_count: 256 }, // 28
                MiSpanQueueS { first: None, last: None, slice_count: 320 }, // 29
                MiSpanQueueS { first: None, last: None, slice_count: 384 }, // 30
                MiSpanQueueS { first: None, last: None, slice_count: 448 }, // 31
                MiSpanQueueS { first: None, last: None, slice_count: 512 }, // 32
                MiSpanQueueS { first: None, last: None, slice_count: 640 }, // 33
                MiSpanQueueS { first: None, last: None, slice_count: 768 }, // 34
                MiSpanQueueS { first: None, last: None, slice_count: 896 }, // 35
                MiSpanQueueS { first: None, last: None, slice_count: 1024 },// 36
            ],
            count: 0,
            peak_count: 0,
            current_size: 0,
            peak_size: 0,
            reclaim_count: 0,
            subproc: None,
            stats: None,
        },
        stats: MiStatsS {
            version: 1,
            pages: MiStatCountS { total: 0, peak: 0, current: 0 },
            reserved: MiStatCountS { total: 0, peak: 0, current: 0 },
            committed: MiStatCountS { total: 0, peak: 0, current: 0 },
            reset: MiStatCountS { total: 0, peak: 0, current: 0 },
            purged: MiStatCountS { total: 0, peak: 0, current: 0 },
            page_committed: MiStatCountS { total: 0, peak: 0, current: 0 },
            pages_abandoned: MiStatCountS { total: 0, peak: 0, current: 0 },
            threads: MiStatCountS { total: 0, peak: 0, current: 0 },
            malloc_normal: MiStatCountS { total: 0, peak: 0, current: 0 },
            malloc_huge: MiStatCountS { total: 0, peak: 0, current: 0 },
            malloc_requested: MiStatCountS { total: 0, peak: 0, current: 0 },
            mmap_calls: MiStatCounterS { total: 0 },
            commit_calls: MiStatCounterS { total: 0 },
            reset_calls: MiStatCounterS { total: 0 },
            purge_calls: MiStatCounterS { total: 0 },
            arena_count: MiStatCounterS { total: 0 },
            malloc_normal_count: MiStatCounterS { total: 0 },
            malloc_huge_count: MiStatCounterS { total: 0 },
            malloc_guarded_count: MiStatCounterS { total: 0 },
            arena_rollback_count: MiStatCounterS { total: 0 },
            arena_purges: MiStatCounterS { total: 0 },
            pages_extended: MiStatCounterS { total: 0 },
            pages_retire: MiStatCounterS { total: 0 },
            page_searches: MiStatCounterS { total: 0 },
            segments: MiStatCountS { total: 0, peak: 0, current: 0 },
            segments_abandoned: MiStatCountS { total: 0, peak: 0, current: 0 },
            segments_cache: MiStatCountS { total: 0, peak: 0, current: 0 },
            _segments_reserved: MiStatCountS { total: 0, peak: 0, current: 0 },
            pages_reclaim_on_alloc: MiStatCounterS { total: 0 },
            pages_reclaim_on_free: MiStatCounterS { total: 0 },
            pages_reabandon_full: MiStatCounterS { total: 0 },
            pages_unabandon_busy_wait: MiStatCounterS { total: 0 },
            _stat_reserved: [
                MiStatCountS { total: 0, peak: 0, current: 0 },
                MiStatCountS { total: 0, peak: 0, current: 0 },
                MiStatCountS { total: 0, peak: 0, current: 0 },
                MiStatCountS { total: 0, peak: 0, current: 0 },
            ],
            _stat_counter_reserved: [
                MiStatCounterS { total: 0 },
                MiStatCounterS { total: 0 },
                MiStatCounterS { total: 0 },
                MiStatCounterS { total: 0 },
            ],
            malloc_bins: [
                // 74 elements total (matching [MiStatCountS; 74])
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 1
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 2
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 3
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 4
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 5
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 6
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 7
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 8
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 9
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 10
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 11
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 12
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 13
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 14
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 15
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 16
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 17
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 18
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 19
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 20
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 21
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 22
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 23
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 24
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 25
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 26
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 27
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 28
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 29
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 30
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 31
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 32
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 33
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 34
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 35
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 36
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 37
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 38
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 39
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 40
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 41
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 42
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 43
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 44
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 45
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 46
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 47
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 48
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 49
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 50
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 51
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 52
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 53
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 54
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 55
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 56
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 57
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 58
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 59
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 60
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 61
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 62
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 63
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 64
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 65
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 66
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 67
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 68
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 69
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 70
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 71
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 72
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 73
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 74
            ],
            page_bins: [
                // 74 elements total (matching [MiStatCountS; 74])
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 1
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 2
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 3
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 4
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 5
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 6
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 7
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 8
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 9
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 10
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 11
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 12
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 13
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 14
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 15
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 16
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 17
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 18
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 19
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 20
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 21
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 22
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 23
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 24
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 25
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 26
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 27
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 28
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 29
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 30
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 31
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 32
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 33
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 34
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 35
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 36
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 37
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 38
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 39
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 40
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 41
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 42
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 43
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 44
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 45
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 46
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 47
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 48
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 49
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 50
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 51
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 52
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 53
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 54
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 55
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 56
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 57
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 58
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 59
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 60
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 61
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 62
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 63
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 64
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 65
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 66
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 67
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 68
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 69
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 70
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 71
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 72
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 73
                MiStatCountS { total: 0, peak: 0, current: 0 }, // 74
            ],
        },
    });
}


lazy_static! {
    pub static ref TD_CACHE: [AtomicPtr<MiThreadDataS>; 32] = [
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
        AtomicPtr::new(std::ptr::null_mut()),
    ];
}

lazy_static! {
    pub static ref OPTIONS: Mutex<[MiOptionDescT; 40]> = Mutex::new([
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionShowErrors, name: Some("show_errors".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionShowStats, name: Some("show_stats".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionVerbose, name: Some("verbose".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionEagerCommit, name: Some("eager_commit".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 2, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaEagerCommit, name: Some("arena_eager_commit".to_string()), legacy_name: Some("eager_region_commit".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeDecommits, name: Some("purge_decommits".to_string()), legacy_name: Some("reset_decommits".to_string()) },
        MiOptionDescS { value: 2, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAllowLargeOsPages, name: Some("allow_large_os_pages".to_string()), legacy_name: Some("large_os_pages".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveHugeOsPages, name: Some("reserve_huge_os_pages".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: -1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveHugeOsPagesAt, name: Some("reserve_huge_os_pages_at".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionReserveOsMemory, name: Some("reserve_os_memory".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedSegmentCache, name: Some("deprecated_segment_cache".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedPageReset, name: Some("deprecated_page_reset".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAbandonedPagePurge, name: Some("abandoned_page_purge".to_string()), legacy_name: Some("abandoned_page_reset".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDeprecatedSegmentReset, name: Some("deprecated_segment_reset".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionEagerCommitDelay, name: Some("eager_commit_delay".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeDelay, name: Some("purge_delay".to_string()), legacy_name: Some("reset_delay".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionUseNumaNodes, name: Some("use_numa_nodes".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDisallowOsAlloc, name: Some("disallow_os_alloc".to_string()), legacy_name: Some("limit_os_alloc".to_string()) },
        MiOptionDescS { value: 100, init: MiInitT::UNINIT, option: MiOptionT::MiOptionOsTag, name: Some("os_tag".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 32, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxErrors, name: Some("max_errors".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 32, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxWarnings, name: Some("max_warnings".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionMaxSegmentReclaim, name: Some("max_segment_reclaim".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDestroyOnExit, name: Some("destroy_on_exit".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1024 * 1024, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaReserve, name: Some("arena_reserve".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10, init: MiInitT::UNINIT, option: MiOptionT::MiOptionArenaPurgeMult, name: Some("arena_purge_mult".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 1, init: MiInitT::UNINIT, option: MiOptionT::MiOptionPurgeExtendDelay, name: Some("purge_extend_delay".to_string()), legacy_name: Some("decommit_extend_delay".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionAbandonedReclaimOnFree, name: Some("abandoned_reclaim_on_free".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionDisallowArenaAlloc, name: Some("disallow_arena_alloc".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 400, init: MiInitT::UNINIT, option: MiOptionT::MiOptionRetryOnOom, name: Some("retry_on_oom".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionVisitAbandoned, name: Some("visit_abandoned".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedMin, name: Some("guarded_min".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: (1024 * 1024 * 1024) as i64, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedMax, name: Some("guarded_max".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedPrecise, name: Some("guarded_precise".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedSampleRate, name: Some("guarded_sample_rate".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGuardedSampleSeed, name: Some("guarded_sample_seed".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::MiOptionTargetSegmentsPerThread, name: Some("target_segments_per_thread".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 10000, init: MiInitT::UNINIT, option: MiOptionT::MiOptionGenericCollect, name: Some("generic_collect".to_string()), legacy_name: Some("0".to_string()) },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
        // Add two more elements to reach the required 40
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
        MiOptionDescS { value: 0, init: MiInitT::UNINIT, option: MiOptionT::_MiOptionLast, name: None, legacy_name: None },
    ]);
}


lazy_static! {
    pub static ref MI_OUT_DEFAULT: AtomicPtr<Mi_Output_Fun> = 
        AtomicPtr::new(std::ptr::null_mut());
}


lazy_static! {
    pub static ref mi_error_handler: AtomicPtr<Mi_Error_Fun> = 
        AtomicPtr::new(std::ptr::null_mut());
}


lazy_static! {
    pub static ref MI_OS_MEM_CONFIG: std::sync::Mutex<MiOsMemConfigS> = 
        std::sync::Mutex::new(MiOsMemConfigS {
            page_size: 4096,
            large_page_size: 0,
            alloc_granularity: 4096,
            physical_memory_in_kib: 32 * (1024 * 1024),
            virtual_address_bits: 48,
            has_overcommit: true,
            has_partial_free: false,
            has_virtual_reserve: true,
        });
}


lazy_static! {
    pub static ref DEFERRED_FREE: AtomicPtr<MiDeferredFreeFun> = 
        AtomicPtr::new(std::ptr::null_mut());
}


lazy_static! {
    pub static ref MI_SEGMENT_MAP: [AtomicPtr<MiSegmapPartT>; 4097] = {
        const ARRAY_SIZE: usize = 4097;
        let mut array: [AtomicPtr<MiSegmapPartT>; ARRAY_SIZE] = unsafe {
            std::mem::MaybeUninit::uninit().assume_init()
        };
        for i in 0..ARRAY_SIZE {
            array[i] = AtomicPtr::new(std::ptr::null_mut());
        }
        array
    };
}


lazy_static! {
    pub static ref MI_PROCESS_START: AtomicI64 = AtomicI64::new(0);
}


lazy_static! {
    pub static ref MI_CLOCK_DIFF: AtomicI64 = AtomicI64::new(0);
}

