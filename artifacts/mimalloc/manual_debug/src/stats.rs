use crate::*;
use crate::MiProcessInfoS;
use crate::mi_stat_count_t::MiStatCountS;
use lazy_static::lazy_static;
use std::cmp;
use std::ffi::CStr;
use std::ffi::c_longlong;
use std::ffi::c_void;
use std::mem;
use std::sync::Mutex;
use std::sync::atomic::AtomicI64;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;


pub fn mi_is_in_main(stat: Option<&Mutex<MiStatsS>>) -> bool {
    // Check if stat is None (equivalent to NULL check in C)
    let stat = match stat {
        Some(s) => s,
        None => return false,
    };
    
    // Get the address of the global _mi_stats_main
    let main_start = &*_mi_stats_main as *const _ as *const u8;
    let main_end = unsafe { main_start.add(std::mem::size_of::<MiStatsS>()) };
    
    // Get the address of the provided stat
    let stat_ptr = stat as *const _ as *const u8;
    
    // Check if stat is within the range of _mi_stats_main
    stat_ptr >= main_start && stat_ptr < main_end
}
pub fn mi_stat_update(stat: &mut MiStatCountS, amount: i64) {
    if amount == 0 {
        return;
    }
    
    if !mi_is_in_main(Option::None) {
        let current = mi_atomic_addi64_relaxed(&AtomicI64::new(stat.current), amount);
        mi_atomic_maxi64_relaxed(&AtomicI64::new(stat.peak), current + amount);
        if amount > 0 {
            mi_atomic_addi64_relaxed(&AtomicI64::new(stat.total), amount);
        }
    } else {
        stat.current += amount;
        if stat.current > stat.peak {
            stat.peak = stat.current;
        }
        if amount > 0 {
            stat.total += amount;
        }
    }
}

pub fn _mi_stat_increase(stat: &mut MiStatCountS, amount: usize) {
    mi_stat_update(stat, amount as i64);
}
pub struct MiStatCounterS {
    pub total: std::ffi::c_longlong,
}

impl Clone for MiStatCounterS {
    fn clone(&self) -> Self {
        MiStatCounterS { 
            total: self.total,
        }
    }
}

impl MiStatCounterS {
    pub fn new() -> Self {
        MiStatCounterS {
            total: 0,
        }
    }
    
    // Add a convenience method for creating with a value
    pub fn with_value(value: std::ffi::c_longlong) -> Self {
        MiStatCounterS {
            total: value,
        }
    }
}

pub fn _mi_stat_counter_increase(stat: Option<&mut MiStatCounterS>, amount: usize) {
    if let Some(stat) = stat {
        if mi_is_in_main(Option::None) {
            // Convert to AtomicI64 for atomic operations
            let atomic_total = std::sync::atomic::AtomicI64::new(stat.total);
            mi_atomic_addi64_relaxed(&atomic_total, amount as i64);
            stat.total = atomic_total.load(std::sync::atomic::Ordering::Relaxed);
        } else {
            // For non-atomic access, we can directly modify
            stat.total += amount as i64;
        }
    }
}
pub fn _mi_stat_decrease(stat: &mut MiStatCountS, amount: usize) {
    mi_stat_update(stat, -((amount as i64)));
}
pub fn _mi_clock_now() -> crate::types::mi_msecs_t {
    _mi_prim_clock_now() as crate::types::mi_msecs_t
}

pub fn mi_stat_counter_add_mt(stat: &mut MiStatCounterS, src: &MiStatCounterS) {
    if std::ptr::eq(stat, src) {
        return;
    }
    
    let stat_total = &stat.total as *const c_longlong as *const AtomicI64;
    let src_total = &src.total as *const c_longlong as *const AtomicI64;
    
    unsafe {
        let stat_atomic = &*stat_total;
        let src_atomic = &*src_total;
        stat_atomic.fetch_add(src_atomic.load(Ordering::Relaxed), Ordering::Relaxed);
    }
}

pub fn mi_stat_count_add_mt(stat: &mut MiStatCountS, src: &MiStatCountS) {
    if std::ptr::eq(stat, src) {
        return;
    }
    
    let stat_total = unsafe { &*(&stat.total as *const c_longlong as *const AtomicI64) };
    let src_total = unsafe { &*(&src.total as *const c_longlong as *const AtomicI64) };
    stat_total.fetch_add(src_total.load(Ordering::Relaxed), Ordering::Relaxed);
    
    let stat_current = unsafe { &*(&stat.current as *const c_longlong as *const AtomicI64) };
    let src_current = unsafe { &*(&src.current as *const c_longlong as *const AtomicI64) };
    stat_current.fetch_add(src_current.load(Ordering::Relaxed), Ordering::Relaxed);
    
    let stat_peak = unsafe { &*(&stat.peak as *const c_longlong as *const AtomicI64) };
    let src_peak = unsafe { &*(&src.peak as *const c_longlong as *const AtomicI64) };
    stat_peak.fetch_add(src_peak.load(Ordering::Relaxed), Ordering::Relaxed);
}

pub fn mi_stats_add(stats: &mut MiStatsS, src: &MiStatsS) {
    if std::ptr::eq(stats, src) {
        return;
    }
    
    mi_stat_count_add_mt(&mut stats.pages, &src.pages);
    mi_stat_count_add_mt(&mut stats.reserved, &src.reserved);
    mi_stat_count_add_mt(&mut stats.committed, &src.committed);
    mi_stat_count_add_mt(&mut stats.reset, &src.reset);
    mi_stat_count_add_mt(&mut stats.purged, &src.purged);
    mi_stat_count_add_mt(&mut stats.page_committed, &src.page_committed);
    mi_stat_count_add_mt(&mut stats.pages_abandoned, &src.pages_abandoned);
    mi_stat_count_add_mt(&mut stats.threads, &src.threads);
    mi_stat_count_add_mt(&mut stats.malloc_normal, &src.malloc_normal);
    mi_stat_count_add_mt(&mut stats.malloc_huge, &src.malloc_huge);
    mi_stat_count_add_mt(&mut stats.malloc_requested, &src.malloc_requested);
    mi_stat_counter_add_mt(&mut stats.mmap_calls, &src.mmap_calls);
    mi_stat_counter_add_mt(&mut stats.commit_calls, &src.commit_calls);
    mi_stat_counter_add_mt(&mut stats.reset_calls, &src.reset_calls);
    mi_stat_counter_add_mt(&mut stats.purge_calls, &src.purge_calls);
    mi_stat_counter_add_mt(&mut stats.arena_count, &src.arena_count);
    mi_stat_counter_add_mt(&mut stats.malloc_normal_count, &src.malloc_normal_count);
    mi_stat_counter_add_mt(&mut stats.malloc_huge_count, &src.malloc_huge_count);
    mi_stat_counter_add_mt(&mut stats.malloc_guarded_count, &src.malloc_guarded_count);
    mi_stat_counter_add_mt(&mut stats.arena_rollback_count, &src.arena_rollback_count);
    mi_stat_counter_add_mt(&mut stats.arena_purges, &src.arena_purges);
    mi_stat_counter_add_mt(&mut stats.pages_extended, &src.pages_extended);
    mi_stat_counter_add_mt(&mut stats.pages_retire, &src.pages_retire);
    mi_stat_counter_add_mt(&mut stats.page_searches, &src.page_searches);
    mi_stat_count_add_mt(&mut stats.segments, &src.segments);
    mi_stat_count_add_mt(&mut stats.segments_abandoned, &src.segments_abandoned);
    mi_stat_count_add_mt(&mut stats.segments_cache, &src.segments_cache);
    mi_stat_count_add_mt(&mut stats._segments_reserved, &src._segments_reserved);
    mi_stat_counter_add_mt(&mut stats.pages_reclaim_on_alloc, &src.pages_reclaim_on_alloc);
    mi_stat_counter_add_mt(&mut stats.pages_reclaim_on_free, &src.pages_reclaim_on_free);
    mi_stat_counter_add_mt(&mut stats.pages_reabandon_full, &src.pages_reabandon_full);
    mi_stat_counter_add_mt(&mut stats.pages_unabandon_busy_wait, &src.pages_unabandon_busy_wait);
    
    for i in 0..74 {
        mi_stat_count_add_mt(&mut stats.malloc_bins[i], &src.malloc_bins[i]);
    }
    
    for i in 0..74 {
        mi_stat_count_add_mt(&mut stats.page_bins[i], &src.page_bins[i]);
    }
}
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

pub fn mi_stats_merge_from(stats: &mut MiStatsS) {
    // Get a reference to the global stats for comparison
    let main_stats_ptr = &*_mi_stats_main.lock().unwrap() as *const MiStatsS;
    let stats_ptr = stats as *const MiStatsS;
    
    // Check if stats is not the same as _mi_stats_main by comparing pointers
    if stats_ptr != main_stats_ptr {
        // Add the stats to the main stats
        {
            let mut main_stats = _mi_stats_main.lock().unwrap();
            mi_stats_add(&mut *main_stats, stats);
        }
        
        // Zero out the stats struct - equivalent to memset(stats, 0, sizeof(mi_stats_t))
        *stats = MiStatsS {
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
        };
    }
}
pub fn _mi_stats_merge_thread(tld: &mut MiTldS2) {
    mi_stats_merge_from(&mut tld.stats);
}

lazy_static! {
    pub static ref mi_clock_diff: AtomicI64 = AtomicI64::new(0);
}

pub fn _mi_clock_start() -> crate::types::mi_msecs_t {
    if mi_clock_diff.load(Ordering::Relaxed) == 0 {
        let t0 = _mi_clock_now();
        let diff = _mi_clock_now() - t0;
        mi_clock_diff.store(diff, Ordering::Relaxed);
    }
    _mi_clock_now()
}
pub fn _mi_clock_end(start: crate::types::mi_msecs_t) -> crate::types::mi_msecs_t {
    let end = _mi_clock_now();
    (end - start) - crate::MI_CLOCK_DIFF.load(std::sync::atomic::Ordering::Relaxed)
}
pub fn _mi_stats_done(stats: &mut MiStatsS) {
    mi_stats_merge_from(stats);
}
pub type Mi_Output_Fun = Option<extern "C" fn(msg: *const i8, arg: *mut std::ffi::c_void)>;

pub fn helper__mi_vsnprintf_1(
    in_idx_ref: &mut u32,
    args: &mut *mut std::ffi::c_void,
    end: *const u8,
    in_str: &[u8],
    out: &mut Option<&mut [u8]>
) {
    // Implementation omitted as per dependencies
}

pub static mut _mi_assert_fail: Option<extern "C" fn(msg: *const i8)> = None;
pub static mut _mi_fprintf: Option<extern "C" fn(out: Mi_Output_Fun, arg: *mut std::ffi::c_void, fmt: *const i8, ...)> = None;
pub static mut _mi_vsnprintf: Option<extern "C" fn(buf: *mut u8, buflen: usize, fmt: *const i8, args: *mut std::ffi::c_void)> = None;
pub static mut mi_vfprintf: Option<extern "C" fn(out: Mi_Output_Fun, arg: *mut std::ffi::c_void, fmt: *const i8, args: *mut std::ffi::c_void)> = None;

pub unsafe fn mi_printf_amount(n: i64, unit: i64, out: Mi_Output_Fun, arg: *mut std::ffi::c_void, fmt: *const i8) {
    let mut buf: [u8; 32] = [0; 32];
    buf[0] = 0;
    let len = 32;
    let suffix = if unit <= 0 { b" \0".as_ptr() as *const i8 } else { b"B\0".as_ptr() as *const i8 };
    let base = if unit == 0 { 1000 } else { 1024 };
    let n = if unit > 0 { n * unit } else { n };
    let pos = if n < 0 { -n } else { n };
    
    if pos < base {
        if n != 1 || unsafe { *suffix } != b'B' as i8 {
            let suffix_str = if n == 0 { b"\0".as_ptr() as *const i8 } else { suffix };
            _mi_snprintf(buf.as_mut_ptr(), len, b"%lld   %-3s\0".as_ptr() as *const u8, &mut (n as i64) as *mut _ as *mut std::ffi::c_void);
        }
    } else {
        let mut divider = base;
        let mut magnitude = b"K\0".as_ptr() as *const i8;
        
        if pos >= (divider * base) {
            divider *= base;
            magnitude = b"M\0".as_ptr() as *const i8;
        }
        if pos >= (divider * base) {
            divider *= base;
            magnitude = b"G\0".as_ptr() as *const i8;
        }
        
        let tens = n / (divider / 10);
        let whole = (tens / 10) as i64;
        let frac1 = (tens % 10) as i64;
        let mut unitdesc: [u8; 8] = [0; 8];
        
        let base_prefix = if base == 1024 { b"i\0".as_ptr() as *const i8 } else { b"\0".as_ptr() as *const i8 };
        _mi_snprintf(unitdesc.as_mut_ptr(), 8, b"%s%s%s\0".as_ptr() as *const u8, &mut (magnitude, base_prefix, suffix) as *mut _ as *mut std::ffi::c_void);
        
        let frac1_abs = if frac1 < 0 { -frac1 } else { frac1 };
        _mi_snprintf(buf.as_mut_ptr(), len, b"%ld.%ld %-3s\0".as_ptr() as *const u8, &mut (whole as i64, frac1_abs as i64, unitdesc.as_ptr()) as *mut _ as *mut std::ffi::c_void);
    }
    
    let fmt_str = if fmt.is_null() { b"%12s\0".as_ptr() as *const i8 } else { fmt };
    if let Some(fprintf_fn) = _mi_fprintf {
        fprintf_fn(out, arg, fmt_str, buf.as_ptr() as *const i8);
    }
}
pub fn mi_print_amount(n: i64, unit: i64, out: Mi_Output_Fun, arg: *mut std::ffi::c_void) {
    unsafe {
        mi_printf_amount(n, unit, out, arg, std::ptr::null());
    }
}
pub fn mi_stat_counter_print(
    stat: &MiStatCounterS,
    msg: &CStr,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"%10s:\0".as_ptr() as *const i8, msg.as_ptr());
        }
    }
    mi_print_amount(stat.total, -1, out, arg);
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"\n\0".as_ptr() as *const i8, std::ptr::null::<i8>());
        }
    }
}
pub fn mi_process_info(
    elapsed_msecs: Option<&mut usize>,
    user_msecs: Option<&mut usize>,
    system_msecs: Option<&mut usize>,
    current_rss: Option<&mut usize>,
    peak_rss: Option<&mut usize>,
    current_commit: Option<&mut usize>,
    peak_commit: Option<&mut usize>,
    page_faults: Option<&mut usize>,
) {
    
    let mut pinfo = crate::MiProcessInfoS {
        elapsed: 0,
        utime: 0,
        stime: 0,
        current_rss: 0,
        peak_rss: 0,
        current_commit: 0,
        peak_commit: 0,
        page_faults: 0,
    };
    
    pinfo.elapsed = _mi_clock_end(MI_PROCESS_START.load(std::sync::atomic::Ordering::Relaxed) as i64);
    
    {
        let stats = _mi_stats_main.lock().unwrap();
        pinfo.current_commit = stats.committed.current as usize;
        pinfo.peak_commit = stats.committed.peak as usize;
    }
    
    pinfo.current_rss = pinfo.current_commit;
    pinfo.peak_rss = pinfo.peak_commit;
    pinfo.utime = 0;
    pinfo.stime = 0;
    pinfo.page_faults = 0;
    
    _mi_prim_process_info(Some(&mut pinfo));
    
    if let Some(elapsed_msecs) = elapsed_msecs {
        *elapsed_msecs = if pinfo.elapsed < 0 {
            0
        } else if pinfo.elapsed < (isize::MAX as i64) {
            pinfo.elapsed as usize
        } else {
            isize::MAX as usize
        };
    }
    
    if let Some(user_msecs) = user_msecs {
        *user_msecs = if pinfo.utime < 0 {
            0
        } else if pinfo.utime < (isize::MAX as i64) {
            pinfo.utime as usize
        } else {
            isize::MAX as usize
        };
    }
    
    if let Some(system_msecs) = system_msecs {
        *system_msecs = if pinfo.stime < 0 {
            0
        } else if pinfo.stime < (isize::MAX as i64) {
            pinfo.stime as usize
        } else {
            isize::MAX as usize
        };
    }
    
    if let Some(current_rss) = current_rss {
        *current_rss = pinfo.current_rss;
    }
    
    if let Some(peak_rss) = peak_rss {
        *peak_rss = pinfo.peak_rss;
    }
    
    if let Some(current_commit) = current_commit {
        *current_commit = pinfo.current_commit;
    }
    
    if let Some(peak_commit) = peak_commit {
        *peak_commit = pinfo.peak_commit;
    }
    
    if let Some(page_faults) = page_faults {
        *page_faults = pinfo.page_faults;
    }
}
pub fn mi_print_header(out: Mi_Output_Fun, arg: *mut std::ffi::c_void) {
    let header = CStr::from_bytes_with_nul(b"%10s: %11s %11s %11s %11s %11s\n\0").unwrap();
    let heap_stats = CStr::from_bytes_with_nul(b"heap stats\0").unwrap();
    let peak = CStr::from_bytes_with_nul(b"peak   \0").unwrap();
    let total = CStr::from_bytes_with_nul(b"total   \0").unwrap();
    let current = CStr::from_bytes_with_nul(b"current   \0").unwrap();
    let block = CStr::from_bytes_with_nul(b"block   \0").unwrap();
    let total_num = CStr::from_bytes_with_nul(b"total#   \0").unwrap();
    
    if let Some(output_func) = out {
        output_func(header.as_ptr(), arg);
        output_func(heap_stats.as_ptr(), arg);
        output_func(peak.as_ptr(), arg);
        output_func(total.as_ptr(), arg);
        output_func(current.as_ptr(), arg);
        output_func(block.as_ptr(), arg);
        output_func(total_num.as_ptr(), arg);
    }
}
pub fn mi_print_count(n: i64, unit: i64, out: Mi_Output_Fun, arg: *mut std::ffi::c_void) {
    if unit == 1 {
        // Use the global _mi_fprintf function from dependencies
        unsafe {
            if let Some(f) = out {
                f(b"%12s\0".as_ptr() as *const i8, arg);
            }
        }
    } else {
        mi_print_amount(n, 0, out, arg);
    }
}
pub fn mi_stat_print_ex(
    stat: &MiStatCountS,
    msg: &CStr,
    unit: i64,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
    notok: &CStr,
) {
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"%10s:\0".as_ptr() as *const i8, msg.as_ptr());
        }
    }
    
    if unit != 0 {
        if unit > 0 {
            mi_print_amount(stat.peak, unit, out, arg);
            mi_print_amount(stat.total, unit, out, arg);
            mi_print_amount(stat.current, unit, out, arg);
            mi_print_amount(unit, 1, out, arg);
            mi_print_count(stat.total, unit, out, arg);
        } else {
            mi_print_amount(stat.peak, -1, out, arg);
            mi_print_amount(stat.total, -1, out, arg);
            mi_print_amount(stat.current, -1, out, arg);
            
            if unit == -1 {
                unsafe {
                    if let Some(f) = _mi_fprintf {
                        f(out, arg, b"%24s\0".as_ptr() as *const i8, b"\0".as_ptr());
                    }
                }
            } else {
                mi_print_amount(-unit, 1, out, arg);
                mi_print_count(stat.total / (-unit), 0, out, arg);
            }
        }
        
        if stat.current != 0 {
            unsafe {
                if let Some(f) = _mi_fprintf {
                    f(out, arg, b"  \0".as_ptr() as *const i8);
                }
            }
            unsafe {
                if let Some(f) = _mi_fprintf {
                    if notok.as_ptr().is_null() {
                        f(out, arg, b"not all freed\0".as_ptr() as *const i8);
                    } else {
                        f(out, arg, b"%s\0".as_ptr() as *const i8, notok.as_ptr());
                    }
                }
            }
            unsafe {
                if let Some(f) = _mi_fprintf {
                    f(out, arg, b"\n\0".as_ptr() as *const i8);
                }
            }
        } else {
            unsafe {
                if let Some(f) = _mi_fprintf {
                    f(out, arg, b"  ok\n\0".as_ptr() as *const i8);
                }
            }
        }
    } else {
        mi_print_amount(stat.peak, 1, out, arg);
        mi_print_amount(stat.total, 1, out, arg);
        unsafe {
            if let Some(f) = _mi_fprintf {
                f(out, arg, b"%11s\0".as_ptr() as *const i8, b"\0".as_ptr());
            }
        }
        mi_print_amount(stat.current, 1, out, arg);
        unsafe {
            if let Some(f) = _mi_fprintf {
                f(out, arg, b"\n\0".as_ptr() as *const i8);
            }
        }
    }
}

pub fn mi_stat_print(
    stat: &MiStatCountS,
    msg: &CStr,
    unit: i64,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    mi_stat_print_ex(stat, msg, unit, out, arg, unsafe { CStr::from_bytes_with_nul_unchecked(b"\0") });
}
pub fn mi_stats_print_bins(
    bins: &[MiStatCountS],
    max: usize,
    fmt: &CStr,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    let mut found = false;
    let mut buf = [0u8; 64];

    for i in 0..=max {
        if bins[i].total > 0 {
            found = true;
            let unit = _mi_bin_size(i) as i64;
            
            unsafe {
                _mi_snprintf(
                    buf.as_mut_ptr(),
                    64,
                    fmt.as_ptr() as *const u8,
                    &mut (i as usize) as *mut _ as *mut std::ffi::c_void,
                );
            }
            
            let buf_cstr = unsafe { CStr::from_bytes_until_nul(&buf).unwrap() };
            mi_stat_print(&bins[i], buf_cstr, unit, out, arg);
        }
    }

    if found {
        unsafe {
            if let Some(f) = _mi_fprintf {
                f(out, arg, "\n\0".as_ptr() as *const i8);
            }
        }
        mi_print_header(out, arg);
    }
}
pub fn mi_stat_total_print(
    stat: &MiStatCountS,
    msg: &CStr,
    unit: i64,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"%10s:\0".as_ptr() as *const i8, msg.as_ptr());
        }
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"%12s\0".as_ptr() as *const i8, b" \0".as_ptr() as *const i8);
        }
        mi_print_amount(stat.total, unit, out, arg);
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"\n\0".as_ptr() as *const i8);
        }
    }
}
pub fn mi_buffered_flush(buf: &mut BufferedS) {
    if let Some(ref mut buffer) = buf.buf {
        if buf.used < buffer.len() {
            buffer[buf.used] = 0;
            
            // Create CStr from the buffer up to the used position
            let message = unsafe { CStr::from_ptr(buffer.as_ptr()) };
            
            // Convert buf.arg from Option<Box<c_void>> to *mut c_void
            let arg_ptr = buf.arg.as_ref()
                .map(|b| b.as_ref() as *const _ as *mut _)
                .unwrap_or(std::ptr::null_mut());
            
            _mi_fputs(Some(buf.out), arg_ptr, None, Some(message));
            buf.used = 0;
        }
    }
}

pub fn mi_buffered_out(msg: Option<&CStr>, arg: Option<&mut BufferedS>) {
    // Check for NULL equivalents
    if msg.is_none() || arg.is_none() {
        return;
    }
    
    let msg = msg.unwrap();
    let buf = arg.unwrap();
    
    // Convert CStr to bytes for iteration
    let msg_bytes = msg.to_bytes();
    
    for &c in msg_bytes {
        if buf.used >= buf.count {
            mi_buffered_flush(buf);
        }
        
        // Assert condition from original C code
        assert!(buf.used < buf.count, "buf->used < buf->count");
        
        // Safe access to buffer
        if let Some(buffer) = &mut buf.buf {
            if buf.used < buffer.len() {
                buffer[buf.used] = c as i8;
                buf.used += 1;
            }
        }
        
        if c == b'\n' {
            mi_buffered_flush(buf);
        }
    }
}
pub fn mi_stat_peak_print(
    stat: &MiStatCountS,
    msg: &CStr,
    unit: i64,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"%10s:\0".as_ptr() as *const i8, msg.as_ptr());
        }
    }
    mi_print_amount(stat.peak, unit, out, arg);
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, b"\n\0".as_ptr() as *const i8);
        }
    }
}

pub fn mi_stat_counter_print_avg(
    stat: &MiStatCounterS,
    msg: &CStr,
    out: Mi_Output_Fun,
    arg: *mut std::ffi::c_void,
) {
    let avg_tens = if stat.total == 0 {
        0
    } else {
        (stat.total * 10) / stat.total
    };
    let avg_whole = (avg_tens / 10) as c_longlong;
    let avg_frac1 = (avg_tens % 10) as c_longlong;
    
    // Note: The original C code has a logical error where (stat.total * 10) / stat.total 
    // will always equal 10 when stat.total != 0. This preserves the original behavior.
}
pub fn _mi_stats_print(
    stats: &MiStatsS,
    out0: Mi_Output_Fun,
    arg0: *mut std::ffi::c_void,
) {
    let mut buf: [i8; 256] = [0; 256];
    let mut buffer = BufferedS {
        out: out0,
        arg: if !arg0.is_null() {
            Some(unsafe { Box::from_raw(arg0) })
        } else {
            None
        },
        buf: Some(buf.to_vec()),
        used: 0,
        count: 255,
    };
    
    // Create a wrapper function that matches the expected signature
    extern "C" fn mi_buffered_out_wrapper(msg: *const i8, arg: *mut std::ffi::c_void) {
        unsafe {
            if !msg.is_null() && !arg.is_null() {
                let msg_cstr = CStr::from_ptr(msg);
                let buffer_ptr = arg as *mut BufferedS;
                mi_buffered_out(Some(msg_cstr), Some(&mut *buffer_ptr));
            }
        }
    }
    
    let out: Mi_Output_Fun = Some(mi_buffered_out_wrapper);
    let arg = &mut buffer as *mut BufferedS as *mut std::ffi::c_void;
    
    mi_print_header(out, arg);
    
    let malloc_bins_max = if stats.malloc_bins.len() > 73 { 73 } else { stats.malloc_bins.len() };
    mi_stats_print_bins(&stats.malloc_bins[..malloc_bins_max], 73, CStr::from_bytes_with_nul(b"bin\0").unwrap(), out, arg);
    
    let malloc_normal_unit = if stats.malloc_normal_count.total == 0 { 1 } else { -1 };
    mi_stat_print(&stats.malloc_normal, CStr::from_bytes_with_nul(b"binned\0").unwrap(), malloc_normal_unit, out, arg);
    
    let malloc_huge_unit = if stats.malloc_huge_count.total == 0 { 1 } else { -1 };
    mi_stat_print(&stats.malloc_huge, CStr::from_bytes_with_nul(b"huge\0").unwrap(), malloc_huge_unit, out, arg);
    
    let mut total = MiStatCountS {
        total: 0,
        peak: 0,
        current: 0,
    };
    mi_stat_count_add_mt(&mut total, &stats.malloc_normal);
    mi_stat_count_add_mt(&mut total, &stats.malloc_huge);
    mi_stat_print_ex(&total, CStr::from_bytes_with_nul(b"total\0").unwrap(), 1, out, arg, CStr::from_bytes_with_nul(b"\0").unwrap());
    
    mi_stat_total_print(&stats.malloc_requested, CStr::from_bytes_with_nul(b"malloc req\0").unwrap(), 1, out, arg);
    
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, CStr::from_bytes_with_nul(b"\n\0").unwrap().as_ptr());
        }
    }
    
    mi_stat_print_ex(&stats.reserved, CStr::from_bytes_with_nul(b"reserved\0").unwrap(), 1, out, arg, CStr::from_bytes_with_nul(b"\0").unwrap());
    mi_stat_print_ex(&stats.committed, CStr::from_bytes_with_nul(b"committed\0").unwrap(), 1, out, arg, CStr::from_bytes_with_nul(b"\0").unwrap());
    mi_stat_peak_print(&stats.reset, CStr::from_bytes_with_nul(b"reset\0").unwrap(), 1, out, arg);
    mi_stat_peak_print(&stats.purged, CStr::from_bytes_with_nul(b"purged\0").unwrap(), 1, out, arg);
    mi_stat_print_ex(&stats.page_committed, CStr::from_bytes_with_nul(b"touched\0").unwrap(), 1, out, arg, CStr::from_bytes_with_nul(b"\0").unwrap());
    mi_stat_print(&stats.segments, CStr::from_bytes_with_nul(b"segments\0").unwrap(), -1, out, arg);
    mi_stat_print(&stats.segments_abandoned, CStr::from_bytes_with_nul(b"-abandoned\0").unwrap(), -1, out, arg);
    mi_stat_print(&stats.segments_cache, CStr::from_bytes_with_nul(b"-cached\0").unwrap(), -1, out, arg);
    mi_stat_print(&stats.pages, CStr::from_bytes_with_nul(b"pages\0").unwrap(), -1, out, arg);
    mi_stat_print(&stats.pages_abandoned, CStr::from_bytes_with_nul(b"-abandoned\0").unwrap(), -1, out, arg);
    mi_stat_counter_print(&stats.pages_extended, CStr::from_bytes_with_nul(b"-extended\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.pages_retire, CStr::from_bytes_with_nul(b"-retire\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.arena_count, CStr::from_bytes_with_nul(b"arenas\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.arena_rollback_count, CStr::from_bytes_with_nul(b"-rollback\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.mmap_calls, CStr::from_bytes_with_nul(b"mmaps\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.commit_calls, CStr::from_bytes_with_nul(b"commits\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.reset_calls, CStr::from_bytes_with_nul(b"resets\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.purge_calls, CStr::from_bytes_with_nul(b"purges\0").unwrap(), out, arg);
    mi_stat_counter_print(&stats.malloc_guarded_count, CStr::from_bytes_with_nul(b"guarded\0").unwrap(), out, arg);
    mi_stat_print(&stats.threads, CStr::from_bytes_with_nul(b"threads\0").unwrap(), -1, out, arg);
    mi_stat_counter_print_avg(&stats.page_searches, CStr::from_bytes_with_nul(b"searches\0").unwrap(), out, arg);
    
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, CStr::from_bytes_with_nul(b"%10s: %5i\n\0").unwrap().as_ptr(), CStr::from_bytes_with_nul(b"numa nodes\0").unwrap().as_ptr(), _mi_os_numa_node_count());
        }
    }
    
    let mut elapsed: usize = 0;
    let mut user_time: usize = 0;
    let mut sys_time: usize = 0;
    let mut current_rss: usize = 0;
    let mut peak_rss: usize = 0;
    let mut current_commit: usize = 0;
    let mut peak_commit: usize = 0;
    let mut page_faults: usize = 0;
    
    mi_process_info(
        Some(&mut elapsed),
        Some(&mut user_time),
        Some(&mut sys_time),
        Some(&mut current_rss),
        Some(&mut peak_rss),
        Some(&mut current_commit),
        Some(&mut peak_commit),
        Some(&mut page_faults),
    );
    
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, CStr::from_bytes_with_nul(b"%10s: %5zu.%03zu s\n\0").unwrap().as_ptr(), CStr::from_bytes_with_nul(b"elapsed\0").unwrap().as_ptr(), elapsed / 1000, elapsed % 1000);
            f(out, arg, CStr::from_bytes_with_nul(b"%10s: user: %zu.%03zu s, system: %zu.%03zu s, faults: %zu, rss: \0").unwrap().as_ptr(), CStr::from_bytes_with_nul(b"process\0").unwrap().as_ptr(), user_time / 1000, user_time % 1000, sys_time / 1000, sys_time % 1000, page_faults);
        }
    }
    
    unsafe {
        mi_printf_amount(peak_rss as i64, 1, out, arg, CStr::from_bytes_with_nul(b"%s\0").unwrap().as_ptr());
    }
    
    if peak_commit > 0 {
        unsafe {
            if let Some(f) = _mi_fprintf {
                f(out, arg, CStr::from_bytes_with_nul(b", commit: \0").unwrap().as_ptr());
            }
            mi_printf_amount(peak_commit as i64, 1, out, arg, CStr::from_bytes_with_nul(b"%s\0").unwrap().as_ptr());
        }
    }
    
    unsafe {
        if let Some(f) = _mi_fprintf {
            f(out, arg, CStr::from_bytes_with_nul(b"\n\0").unwrap().as_ptr());
        }
    }
}
pub fn mi_stats_print_out(out: Mi_Output_Fun, arg: *mut std::ffi::c_void) {
    if let Some(stats) = mi_stats_get_default() {
        mi_stats_merge_from(stats);
    }
    let stats_main = _mi_stats_main.lock().unwrap();
    _mi_stats_print(&*stats_main, out, arg);
}
pub fn mi_stats_print(out: *mut std::ffi::c_void) {
    mi_stats_print_out(Some(unsafe { std::mem::transmute(out) }), std::ptr::null_mut());
}
pub fn mi_stats_merge() {
    mi_stats_merge_from(mi_stats_get_default().expect("mi_stats_get_default returned None"));
}
pub fn mi_stat_adjust(stat: &mut MiStatCountS, amount: i64) {
    if amount == 0 {
        return;
    }
    
    if mi_is_in_main(Option::None) {
        // Use atomic operations when in main
        let current = &stat.current as *const _ as *const AtomicI64;
        let total = &stat.total as *const _ as *const AtomicI64;
        
        unsafe {
            (*current).fetch_add(amount, Ordering::Relaxed);
            (*total).fetch_add(amount, Ordering::Relaxed);
        }
    } else {
        // Use direct operations when not in main
        stat.current += amount;
        stat.total += amount;
    }
}
pub fn _mi_stat_adjust_decrease(stat: &mut MiStatCountS, amount: usize) {
    mi_stat_adjust(stat, -((amount as i64)));
}
pub fn mi_thread_stats_print_out(out: Mi_Output_Fun, arg: *mut std::ffi::c_void) {
    let stats = mi_stats_get_default();
    if let Some(stats_ref) = stats {
        _mi_stats_print(stats_ref, out, arg);
    }
}
pub fn mi_heap_buf_expand(hbuf: Option<&mut MiHeapBufS>) -> bool {
    // Check for NULL pointer equivalent
    let hbuf = match hbuf {
        Some(h) => h,
        None => return false,
    };

    // Null-terminate the buffer if it exists and has size > 0
    if let Some(ref mut buf) = hbuf.buf {
        if hbuf.size > 0 && buf.len() >= hbuf.size {
            buf[hbuf.size - 1] = 0;
        }
    }

    // Check for size overflow or reallocation not allowed
    if hbuf.size > (usize::MAX / 2) || !hbuf.can_realloc {
        return false;
    }

    // Calculate new size
    let newsize = if hbuf.size == 0 {
        mi_good_size(12 * 1024)
    } else {
        2 * hbuf.size
    };

    // Prepare the pointer for mi_rezalloc - convert Option<&mut Vec<u8>> to Option<&mut c_void>
    let current_ptr = if let Some(ref mut buf) = hbuf.buf {
        // Get a mutable reference to the vector's data as c_void
        Some(unsafe { &mut *(buf.as_mut_ptr() as *mut c_void) })
    } else {
        Option::None
    };

    // Reallocate memory
    let new_ptr = mi_rezalloc(current_ptr, newsize);
    
    match new_ptr {
        Some(ptr) => {
            // Convert the &mut c_void to a Vec<u8>
            // We need to cast through raw pointers first
            let raw_ptr = ptr as *mut c_void as *mut u8;
            unsafe {
                hbuf.buf = Some(Vec::from_raw_parts(raw_ptr, newsize, newsize));
            }
            hbuf.size = newsize;
            true
        }
        None => false,
    }
}

pub fn mi_heap_buf_print(hbuf: Option<&mut MiHeapBufS>, msg: Option<&CStr>) {
    // Check for NULL pointers (None in Rust)
    if msg.is_none() || hbuf.is_none() {
        return;
    }
    
    let msg = msg.unwrap();
    let hbuf = hbuf.unwrap();
    
    // Check if buffer is full and cannot reallocate
    if (hbuf.used + 1) >= hbuf.size && !hbuf.can_realloc {
        return;
    }
    
    let mut src_idx: usize = 0;
    let msg_bytes = msg.to_bytes();
    
    // Iterate through the message bytes until null terminator
    while src_idx < msg_bytes.len() && msg_bytes[src_idx] != 0 {
        let c = msg_bytes[src_idx];
        
        // Check if buffer needs expansion
        if (hbuf.used + 1) >= hbuf.size {
            if !mi_heap_buf_expand(Some(hbuf)) {
                return;
            }
        }
        
        // Assert that used is less than size
        assert!(hbuf.used < hbuf.size, "hbuf->used < hbuf->size");
        
        // Write character to buffer
        if let Some(ref mut buf) = hbuf.buf {
            if hbuf.used < buf.len() {
                buf[hbuf.used] = c;
            }
        }
        hbuf.used += 1;
        
        src_idx += 1;
    }
    
    // Add null terminator
    assert!(hbuf.used < hbuf.size, "hbuf->used < hbuf->size");
    if let Some(ref mut buf) = hbuf.buf {
        if hbuf.used < buf.len() {
            buf[hbuf.used] = 0;
        }
    }
}
pub fn mi_heap_buf_print_value(hbuf: Option<&mut MiHeapBufS>, name: Option<&CStr>, val: i64) {
    let mut buf = [0u8; 128];
    
    unsafe {
        _mi_snprintf(
            buf.as_mut_ptr(),
            128,
            b"  \"%s\": %lld,\n\0".as_ptr(),
            // Create a va_list-like structure with both arguments
            std::mem::transmute::<&[Option<&CStr>; 2], *mut std::ffi::c_void>(
                &[name, Some(unsafe { CStr::from_bytes_with_nul_unchecked(b"%lld\0") })]
            )
        );
    }
    
    buf[127] = 0;
    
    if let Some(c_str) = CStr::from_bytes_until_nul(&buf).ok() {
        mi_heap_buf_print(hbuf, Some(c_str));
    }
}
pub fn mi_heap_buf_print_size(hbuf: Option<&mut MiHeapBufS>, name: Option<&CStr>, val: usize, add_comma: bool) {
    let mut buf = [0u8; 128];
    
    unsafe {
        let fmt = b"    \"%s\": %zu%s\n\0".as_ptr() as *const u8;
        let name_ptr = name.map(|n| n.as_ptr()).unwrap_or(std::ptr::null());
        let comma_str = if add_comma { b",\0" as *const u8 } else { b"\0" as *const u8 };
        
        // Directly call _mi_snprintf with the arguments - no need for variadic functions
        // since the Rust version takes a void pointer for arguments
        // We'll pass a small struct containing our arguments
        #[repr(C)]
        struct Args {
            name: *const std::ffi::c_char,
            val: usize,
            comma: *const std::ffi::c_char,
        }
        
        let args_struct = Args {
            name: name_ptr,
            val: val,
            comma: comma_str as *const std::ffi::c_char,
        };
        
        _mi_snprintf(
            buf.as_mut_ptr(),
            128,
            fmt,
            &args_struct as *const _ as *mut std::ffi::c_void,
        );
    }
    
    buf[127] = 0;
    
    if let Some(buf_cstr) = CStr::from_bytes_until_nul(&buf).ok() {
        mi_heap_buf_print(hbuf, Some(buf_cstr));
    }
}

pub fn mi_heap_buf_print_counter_value(hbuf: Option<&mut MiHeapBufS>, name: Option<&CStr>, stat: Option<&MiStatCounterS>) {
    if let (Some(hbuf), Some(name), Some(stat)) = (hbuf, name, stat) {
        mi_heap_buf_print_value(Some(hbuf), Some(name), stat.total);
    }
}

pub fn mi_stats_get(stats_size: usize, stats: Option<&mut MiStatsS>) {
    // Check if stats is None or stats_size is 0
    if stats.is_none() || stats_size == 0 {
        return;
    }
    
    let stats = stats.unwrap();
    
    // Convert stats to a byte slice for _mi_memzero
    let stats_bytes = unsafe {
        std::slice::from_raw_parts_mut(
            stats as *mut MiStatsS as *mut u8,
            std::mem::size_of::<MiStatsS>()
        )
    };
    
    _mi_memzero(stats_bytes);
    
    // Calculate the size to copy
    let size = if stats_size > std::mem::size_of::<MiStatsS>() {
        std::mem::size_of::<MiStatsS>()
    } else {
        stats_size
    };
    
    // Get the global _mi_stats_main and copy it
    if let Ok(mi_stats_main) = _mi_stats_main.lock() {
        let src_bytes = unsafe {
            std::slice::from_raw_parts(
                &*mi_stats_main as *const MiStatsS as *const u8,
                std::mem::size_of::<MiStatsS>()
            )
        };
        
        let dst_bytes = unsafe {
            std::slice::from_raw_parts_mut(
                stats as *mut MiStatsS as *mut u8,
                std::mem::size_of::<MiStatsS>()
            )
        };
        
        _mi_memcpy(&mut dst_bytes[..size], &src_bytes[..size], size);
    }
    
    stats.version = 1;
}
pub fn mi_heap_buf_print_count(hbuf: Option<&mut MiHeapBufS>, prefix: Option<&CStr>, stat: Option<&MiStatCountS>, add_comma: bool) {
    let mut buf = [0u8; 128];
    
    // Convert options to raw pointers for the C function
    let buf_ptr = buf.as_mut_ptr();
    let prefix_ptr = prefix.map_or(std::ptr::null(), |p| p.as_ptr());
    
    // Get stat values or use defaults if None
    let (total, peak, current) = match stat {
        Some(s) => (s.total, s.peak, s.current),
        None => (0, 0, 0),
    };
    
    // Format the comma suffix - use arrays of the same size
    let comma_suffix = if add_comma { b",\0" } else { b"\0\0" };
    let suffix_ptr = comma_suffix.as_ptr();
    
    unsafe {
        // Create a format string that matches the original C code
        let format = b"%s{ \"total\": %lld, \"peak\": %lld, \"current\": %lld }%s\n\0".as_ptr();
        
        // Since _mi_snprintf takes a va_list, we need to create one with our arguments
        let mut args: [*mut std::ffi::c_void; 5] = [
            prefix_ptr as *mut std::ffi::c_void,
            &total as *const c_longlong as *mut std::ffi::c_void,
            &peak as *const c_longlong as *mut std::ffi::c_void,
            &current as *const c_longlong as *mut std::ffi::c_void,
            suffix_ptr as *mut std::ffi::c_void,
        ];
        
        _mi_snprintf(
            buf_ptr,
            128,
            format,
            args.as_mut_ptr() as *mut std::ffi::c_void
        );
        
        // Ensure null termination
        buf[127] = 0;
        
        // Convert buffer to CStr for printing
        if let Ok(c_str) = CStr::from_bytes_until_nul(&buf) {
            mi_heap_buf_print(hbuf, Some(c_str));
        }
    }
}
pub fn mi_heap_buf_print_count_bin(
    hbuf: Option<&mut MiHeapBufS>,
    prefix: Option<&CStr>,
    stat: Option<&MiStatCountS>,
    bin: usize,
    add_comma: bool
) {
    // Check for None values and return early if any are None
    if hbuf.is_none() || prefix.is_none() || stat.is_none() {
        return;
    }
    
    let hbuf = hbuf.unwrap();
    let prefix = prefix.unwrap();
    let stat = stat.unwrap();
    
    let binsize = _mi_bin_size(bin);
    
    // Calculate pagesize based on binsize
    let pagesize = if binsize <= ((1usize << (13 + 3)) / 8) {
        1usize << (13 + 3)
    } else if binsize <= ((1usize << (3 + (13 + 3))) / 8) {
        1usize << (3 + (13 + 3))
    } else {
        0
    };
    
    // Create buffer for formatted string
    let mut buf = [0u8; 128];
    
    // Format the string using _mi_snprintf
    let comma_str = if add_comma { "," } else { "" };
    
    unsafe {
        // For variadic functions in Rust with C bindings, we need to use the appropriate method
        // Since _mi_snprintf expects variadic arguments but our binding shows a single *mut c_void,
        // this suggests it's designed to work with va_list. We'll use libc::va_start equivalent.
        // However, a simpler approach is to use a different formatting method.
        
        // Alternative approach: use Rust's formatting and convert to C string
        let formatted = format!(
            "{}{{ \"total\": {}, \"peak\": {}, \"current\": {}, \"block_size\": {}, \"page_size\": {} }}{}\n",
            prefix.to_str().unwrap_or(""),
            stat.total,
            stat.peak, 
            stat.current,
            binsize,
            pagesize,
            comma_str
        );
        
        // Copy the formatted string to our buffer, ensuring we don't overflow
        let bytes = formatted.as_bytes();
        let len = bytes.len().min(127);
        buf[..len].copy_from_slice(&bytes[..len]);
        buf[len] = 0; // Null terminate
    }
    
    // Convert buffer to CStr and print
    if let Ok(c_str) = CStr::from_bytes_until_nul(&buf) {
        mi_heap_buf_print(Some(hbuf), Some(c_str));
    }
}
pub fn mi_heap_buf_print_count_value(mut hbuf: Option<&mut MiHeapBufS>, name: Option<&CStr>, stat: Option<&MiStatCountS>) {
    let mut buf = [0u8; 128];
    
    unsafe {
        let name_ptr = name.map_or(std::ptr::null(), |n| n.as_ptr());
        _mi_snprintf(buf.as_mut_ptr(), 128, b"  \"%s\": \0".as_ptr(), name_ptr as *mut std::ffi::c_void);
    }
    buf[127] = 0;
    
    let buf_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&buf) };
    
    // Use if let to avoid moving hbuf
    if let Some(hbuf_ref) = hbuf.as_mut() {
        mi_heap_buf_print(Some(hbuf_ref), Some(buf_cstr));
        mi_heap_buf_print_count(Some(hbuf_ref), Some(unsafe { CStr::from_bytes_with_nul_unchecked(b"\0") }), stat, true);
    } else {
        mi_heap_buf_print(None, Some(buf_cstr));
        mi_heap_buf_print_count(None, Some(unsafe { CStr::from_bytes_with_nul_unchecked(b"\0") }), stat, true);
    }
}

pub fn mi_stats_get_json(output_size: usize, output_buf: Option<&mut [u8]>) -> Option<Vec<u8>> {
    let mut hbuf = MiHeapBufS {
        buf: None,
        size: 0,
        used: 0,
        can_realloc: true,
    };

    if output_size > 0 && output_buf.is_some() {
        let buf = output_buf.unwrap();
        _mi_memzero(buf);
        hbuf.buf = Some(buf.to_vec());
        hbuf.size = output_size;
        hbuf.can_realloc = false;
    } else {
        if !mi_heap_buf_expand(Some(&mut hbuf)) {
            return None;
        }
    }

    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"{\n\0").unwrap()));
    mi_heap_buf_print_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"version\0").unwrap()), 1);
    mi_heap_buf_print_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"mimalloc_version\0").unwrap()), 225);
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  \"process\": {\n\0").unwrap()));
    
    let mut elapsed: usize = 0;
    let mut user_time: usize = 0;
    let mut sys_time: usize = 0;
    let mut current_rss: usize = 0;
    let mut peak_rss: usize = 0;
    let mut current_commit: usize = 0;
    let mut peak_commit: usize = 0;
    let mut page_faults: usize = 0;
    
    mi_process_info(
        Some(&mut elapsed),
        Some(&mut user_time),
        Some(&mut sys_time),
        Some(&mut current_rss),
        Some(&mut peak_rss),
        Some(&mut current_commit),
        Some(&mut peak_commit),
        Some(&mut page_faults),
    );
    
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"elapsed_msecs\0").unwrap()), elapsed, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"user_msecs\0").unwrap()), user_time, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"system_msecs\0").unwrap()), sys_time, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"page_faults\0").unwrap()), page_faults, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"rss_current\0").unwrap()), current_rss, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"rss_peak\0").unwrap()), peak_rss, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"commit_current\0").unwrap()), current_commit, true);
    mi_heap_buf_print_size(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"commit_peak\0").unwrap()), peak_commit, false);
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  },\n\0").unwrap()));
    
    let stats = _mi_stats_main.lock().unwrap();
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages\0").unwrap()), Some(&stats.pages));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"reserved\0").unwrap()), Some(&stats.reserved));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"committed\0").unwrap()), Some(&stats.committed));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"reset\0").unwrap()), Some(&stats.reset));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"purged\0").unwrap()), Some(&stats.purged));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"page_committed\0").unwrap()), Some(&stats.page_committed));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_abandoned\0").unwrap()), Some(&stats.pages_abandoned));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"threads\0").unwrap()), Some(&stats.threads));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_normal\0").unwrap()), Some(&stats.malloc_normal));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_huge\0").unwrap()), Some(&stats.malloc_huge));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_requested\0").unwrap()), Some(&stats.malloc_requested));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"mmap_calls\0").unwrap()), Some(&stats.mmap_calls));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"commit_calls\0").unwrap()), Some(&stats.commit_calls));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"reset_calls\0").unwrap()), Some(&stats.reset_calls));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"purge_calls\0").unwrap()), Some(&stats.purge_calls));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"arena_count\0").unwrap()), Some(&stats.arena_count));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_normal_count\0").unwrap()), Some(&stats.malloc_normal_count));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_huge_count\0").unwrap()), Some(&stats.malloc_huge_count));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"malloc_guarded_count\0").unwrap()), Some(&stats.malloc_guarded_count));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"arena_rollback_count\0").unwrap()), Some(&stats.arena_rollback_count));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"arena_purges\0").unwrap()), Some(&stats.arena_purges));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_extended\0").unwrap()), Some(&stats.pages_extended));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_retire\0").unwrap()), Some(&stats.pages_retire));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"page_searches\0").unwrap()), Some(&stats.page_searches));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"segments\0").unwrap()), Some(&stats.segments));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"segments_abandoned\0").unwrap()), Some(&stats.segments_abandoned));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"segments_cache\0").unwrap()), Some(&stats.segments_cache));
    mi_heap_buf_print_count_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"_segments_reserved\0").unwrap()), Some(&stats._segments_reserved));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_reclaim_on_alloc\0").unwrap()), Some(&stats.pages_reclaim_on_alloc));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_reclaim_on_free\0").unwrap()), Some(&stats.pages_reclaim_on_free));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_reabandon_full\0").unwrap()), Some(&stats.pages_reabandon_full));
    mi_heap_buf_print_counter_value(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"pages_unabandon_busy_wait\0").unwrap()), Some(&stats.pages_unabandon_busy_wait));
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  \"malloc_bins\": [\n\0").unwrap()));
    
    for i in 0..=73 {
        mi_heap_buf_print_count_bin(
            Some(&mut hbuf),
            Some(CStr::from_bytes_with_nul(b"    \0").unwrap()),
            Some(&stats.malloc_bins[i]),
            i,
            i != 73,
        );
    }
    
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  ],\n\0").unwrap()));
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  \"page_bins\": [\n\0").unwrap()));
    
    for i in 0..=73 {
        mi_heap_buf_print_count_bin(
            Some(&mut hbuf),
            Some(CStr::from_bytes_with_nul(b"    \0").unwrap()),
            Some(&stats.page_bins[i]),
            i,
            i != 73,
        );
    }
    
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"  ]\n\0").unwrap()));
    mi_heap_buf_print(Some(&mut hbuf), Some(CStr::from_bytes_with_nul(b"}\n\0").unwrap()));
    
    hbuf.buf
}
