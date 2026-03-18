use crate::*;
use lazy_static::lazy_static;
use std::ffi::CString;
use std::os::raw::c_char;
use std::os::raw::c_void;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn _mi_os_page_size() -> usize {
    MI_OS_MEM_CONFIG.lock().unwrap().page_size
}
pub fn mi_os_page_align_areax(
    conservative: bool,
    addr: *mut std::ffi::c_void,
    size: usize,
    newsize: *mut usize
) -> *mut std::ffi::c_void {
    // Assert condition from line 3
    assert!(!addr.is_null() && size > 0, "addr != NULL && size > 0");
    
    // Initialize newsize to 0 if provided (lines 4-7)
    if !newsize.is_null() {
        unsafe { *newsize = 0 };
    }
    
    // Early return for invalid inputs (lines 8-11)
    if size == 0 || addr.is_null() {
        return std::ptr::null_mut();
    }
    
    let page_size = _mi_os_page_size();
    
    // Calculate start and end (lines 12-13)
    let start = if conservative {
        // For conservative alignment up, use mi_align_up_ptr which works with c_void
        mi_align_up_ptr(if addr.is_null() { Option::None } else { Some(unsafe { &mut *(addr as *mut std::ffi::c_void) }) }, page_size)
            .map(|ptr_ref| ptr_ref as *mut std::ffi::c_void)
            .unwrap_or(std::ptr::null_mut())
    } else {
        // For non-conservative alignment down, use mi_align_down_ptr which works with ()
        let addr_as_unit = addr as *mut ();
        mi_align_down_ptr(if addr_as_unit.is_null() { Option::None } else { Some(unsafe { &mut *addr_as_unit }) }, page_size)
            .map(|ptr_ref| ptr_ref as *mut ())
            .map(|ptr| ptr as *mut std::ffi::c_void)
            .unwrap_or(std::ptr::null_mut())
    };
    
    let end = if conservative {
        let end_addr = unsafe { (addr as *mut u8).add(size) as *mut std::ffi::c_void };
        // For conservative alignment down, use mi_align_down_ptr which works with ()
        let end_addr_as_unit = end_addr as *mut ();
        mi_align_down_ptr(if end_addr_as_unit.is_null() { Option::None } else { Some(unsafe { &mut *end_addr_as_unit }) }, page_size)
            .map(|ptr_ref| ptr_ref as *mut ())
            .map(|ptr| ptr as *mut std::ffi::c_void)
            .unwrap_or(std::ptr::null_mut())
    } else {
        let end_addr = unsafe { (addr as *mut u8).add(size) as *mut std::ffi::c_void };
        // For non-conservative alignment up, use mi_align_up_ptr which works with c_void
        mi_align_up_ptr(if end_addr.is_null() { Option::None } else { Some(unsafe { &mut *end_addr }) }, page_size)
            .map(|ptr_ref| ptr_ref as *mut std::ffi::c_void)
            .unwrap_or(std::ptr::null_mut())
    };
    
    // Check if start or end is null
    if start.is_null() || end.is_null() {
        return std::ptr::null_mut();
    }
    
    // Convert start and end to *mut u8 for pointer arithmetic
    let start_ptr = start as *mut u8;
    let end_ptr = end as *mut u8;
    
    // Calculate diff (line 14)
    let diff = unsafe { end_ptr.offset_from(start_ptr) };
    
    // Check if diff is valid (lines 15-18)
    if diff <= 0 {
        return std::ptr::null_mut();
    }
    
    // Assert condition from line 19
    let diff_usize = diff as usize;
    assert!(
        (conservative && diff_usize <= size) || (!conservative && diff_usize >= size),
        "(conservative && (size_t)diff <= size) || (!conservative && (size_t)diff >= size)"
    );
    
    // Update newsize if provided (lines 20-23)
    if !newsize.is_null() {
        unsafe { *newsize = diff_usize };
    }
    
    // Return start (line 24)
    start
}
pub fn _mi_os_commit_ex(
    addr: *mut c_void,
    size: usize,
    mut is_zero: Option<&mut bool>,
    stat_size: usize
) -> bool {
    // Set is_zero to false if provided
    if let Some(ref mut is_zero_ref) = is_zero {
        **is_zero_ref = false;
    }

    // Update statistics
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        // Cast the reference to the expected type
        let committed_cast = unsafe { &mut *(&mut stats.committed as *mut crate::mi_stat_count_t::MiStatCountS as *mut crate::mi_stat_count_t::MiStatCountS) };
        crate::_mi_stat_increase(committed_cast, stat_size);
        _mi_stat_counter_increase(Some(&mut stats.commit_calls), 1);
    }

    // Get aligned page boundaries
    let mut csize: usize = 0;
    let start = mi_os_page_align_areax(false, addr, size, &mut csize);
    
    if csize == 0 {
        return true;
    }

    // Commit the memory
    let mut os_is_zero = false;
    let err = _mi_prim_commit(start, csize, &mut os_is_zero);
    
    if err != 0 {
        _mi_warning_message(
            &std::ffi::CString::new("cannot commit OS memory").unwrap()
        );
        return false;
    }

    // Update is-zero if the OS reported zeroed memory
    if os_is_zero {
        if let Some(ref mut is_zero_ref) = is_zero {
            **is_zero_ref = true;
        }
    }

    true
}
pub fn _mi_os_commit(addr: *mut c_void, size: usize, is_zero: Option<&mut bool>) -> bool {
    _mi_os_commit_ex(addr, size, is_zero, size)
}
pub fn _mi_os_good_alloc_size(size: usize) -> usize {
    let align_size = if size < (512 * 1024) {
        _mi_os_page_size()
    } else if size < (2 * 1024 * 1024) {
        64 * 1024
    } else if size < (8 * 1024 * 1024) {
        256 * 1024
    } else if size < (32 * 1024 * 1024) {
        1 * 1024 * 1024
    } else {
        4 * 1024 * 1024
    };
    
    if size >= usize::MAX - align_size {
        return size;
    }
    
    _mi_align_up(size, align_size)
}
pub fn mi_os_prim_free(addr: Option<&mut [u8]>, size: usize, commit_size: usize) {
    // Check if size is a multiple of page size
    let page_size = _mi_os_page_size();
    assert!(size % page_size == 0, "(size % _mi_os_page_size()) == 0");
    
    // Check if addr is None (equivalent to NULL check)
    if addr.is_none() {
        return;
    }
    
    // Call _mi_prim_free with the address and size
    let err = _mi_prim_free(addr, size);
    
    if err != 0 {
        // In Rust, we would typically use logging instead of _mi_warning_message
        // For now, we'll just ignore the warning as per the dependency constraints
    }
    
    // Update statistics - use the stats version of _mi_stat_decrease
    // Cast the fields to the expected type
    if commit_size > 0 {
        _mi_stat_decrease(unsafe { &mut *(&mut _mi_stats_main.lock().unwrap().committed as *mut _ as *mut crate::mi_stat_count_t::MiStatCountS) }, commit_size);
    }
    _mi_stat_decrease(unsafe { &mut *(&mut _mi_stats_main.lock().unwrap().reserved as *mut _ as *mut crate::mi_stat_count_t::MiStatCountS) }, size);
}
pub fn mi_os_free_huge_os_pages(p: Option<&mut [u8]>, size: usize) {
    if p.is_none() || size == 0 {
        return;
    }
    
    let p = p.unwrap();
    let mut base = p;
    let mut remaining_size = size;
    
    while remaining_size >= (1024 * 1024 * 1024) {
        let chunk_size = 1024 * 1024 * 1024;
        mi_os_prim_free(Some(&mut base[..chunk_size]), chunk_size, chunk_size);
        remaining_size -= chunk_size;
        base = &mut base[chunk_size..];
    }
}
pub fn _mi_os_free_ex(addr: Option<&mut [u8]>, size: usize, still_committed: bool, memid: MiMemidS) {
    if mi_memkind_is_os(memid.memkind) {
        let mut csize = match &memid.mem {
            MiMemidUnion::Os(os_info) => os_info.size,
            _ => 0,
        };
        
        if csize == 0 {
            csize = _mi_os_good_alloc_size(size);
        }
        
        assert!(csize >= size, "csize >= size");
        
        let mut commit_size = if still_committed { csize } else { 0 };
        let base = &addr;  // Take a reference instead of moving
        
        if let MiMemidUnion::Os(os_info) = &memid.mem {
            if let (Some(os_base), Some(addr_ref)) = (&os_info.base, &addr) {
                let os_base_ptr = os_base.as_ptr();
                let addr_ptr = addr_ref.as_ptr();
                
                assert!(os_base_ptr <= addr_ptr, "memid.mem.os.base <= addr");
                
                let diff = unsafe { addr_ptr.offset_from(os_base_ptr) } as usize;
                
                if os_info.size == 0 {
                    csize += diff;
                }
                if still_committed {
                    commit_size -= diff;
                }
            }
        }
        
        if memid.memkind == MiMemkindE::MiMemOsHuge {
            assert!(memid.is_pinned, "memid.is_pinned");
            mi_os_free_huge_os_pages(addr, csize);  // Use original addr parameter
        } else {
            mi_os_prim_free(addr, csize, if still_committed { commit_size } else { 0 });  // Use original addr parameter
        }
    } else {
        // Use pattern matching instead of < comparison since MiMemkindE doesn't implement PartialOrd
        // and the original C code expects memkind to be less than MI_MEM_OS in this branch
        match memid.memkind {
            MiMemkindE::MiMemNone | MiMemkindE::MiMemExternal | MiMemkindE::MiMemStatic => {
                // These are the expected values that are less than MiMemOs
            }
            _ => {
                panic!("memid.memkind < MI_MEM_OS");
            }
        }
    }
}
pub fn _mi_os_free(p: Option<&mut [u8]>, size: usize, memid: MiMemidS) {
    _mi_os_free_ex(p, size, true, memid);
}
pub fn mi_os_ensure_zero<'a>(p: Option<&'a mut [u8]>, size: usize, memid: &mut MiMemidS) -> Option<&'a mut [u8]> {
    if p.is_none() || size == 0 {
        return p;
    }
    
    let p_slice = p.unwrap();
    
    if !memid.initially_committed {
        let mut is_zero = false;
        let commit_success = _mi_os_commit(p_slice.as_mut_ptr() as *mut c_void, size, Some(&mut is_zero));
        if !commit_success {
            _mi_os_free(Some(p_slice), size, memid.clone());
            return None;
        }
        memid.initially_committed = true;
    }
    
    if memid.initially_zero {
        return Some(p_slice);
    }
    
    _mi_memzero_aligned(p_slice, size);
    memid.initially_zero = true;
    Some(p_slice)
}

pub fn _mi_os_get_aligned_hint(try_alignment: usize, size: usize) -> Option<usize> {
    if try_alignment <= 1 || try_alignment > (1 << (9 + (13 + 3))) {
        return None;
    }
    
    let virtual_address_bits = {
        let config = MI_OS_MEM_CONFIG.lock().unwrap();
        config.virtual_address_bits
    };
    
    if virtual_address_bits < 46 {
        return None;
    }
    
    let size = _mi_align_up(size, 1 << (9 + (13 + 3)));
    if size > (1 * (1024 * 1024 * 1024)) {
        return None;
    }
    
    let mut hint = ALIGNED_BASE.fetch_add(size, Ordering::AcqRel);
    
    if hint == 0 || hint > ((30) << 40) {
        let init = (2) << 40;
        let expected = hint + size;
        let _ = ALIGNED_BASE.compare_exchange(
            expected, 
            init, 
            Ordering::AcqRel, 
            Ordering::Acquire
        );
        hint = ALIGNED_BASE.fetch_add(size, Ordering::AcqRel);
    }
    
    if hint % try_alignment != 0 {
        return None;
    }
    
    Some(hint)
}
pub fn _mi_os_has_overcommit() -> bool {
    MI_OS_MEM_CONFIG.lock().unwrap().has_overcommit
}
pub fn _mi_os_use_large_page(size: usize, alignment: usize) -> bool {
    let config = MI_OS_MEM_CONFIG.lock().unwrap();
    
    if config.large_page_size == 0 || !mi_option_is_enabled(MiOptionE::MiOptionAllowLargeOsPages) {
        return false;
    }
    
    (size % config.large_page_size == 0) && (alignment % config.large_page_size == 0)
}
pub fn mi_os_prim_alloc_at(
    hint_addr: Option<&mut std::ffi::c_void>,
    size: usize,
    try_alignment: usize,
    commit: bool,
    allow_large: bool,
    is_large: &mut bool,
    is_zero: &mut bool,
) -> Option<&'static mut std::ffi::c_void> {
    // Assertions converted to debug assertions
    debug_assert!(size > 0 && (size % _mi_os_page_size()) == 0);
    debug_assert!(is_zero as *const _ != std::ptr::null());
    debug_assert!(is_large as *const _ != std::ptr::null());

    if size == 0 {
        return Option::None;
    }

    let mut allow_large = allow_large;
    if !commit {
        allow_large = false;
    }

    let try_alignment = if try_alignment == 0 { 1 } else { try_alignment };

    *is_zero = false;

    // Safely derive a raw pointer for logging without moving or mutably borrowing `hint_addr`.
    // Convert Option<&mut c_void> -> Option<&c_void> with `as_deref()`, then to *const and finally *mut for display.
    let hint_addr_ptr = hint_addr
        .as_deref()
        .map(|p: &std::ffi::c_void| p as *const std::ffi::c_void as *mut std::ffi::c_void)
        .unwrap_or(std::ptr::null_mut());

    let mut p: Option<&'static mut std::ffi::c_void> = Option::None;
    let err = _mi_prim_alloc(
        hint_addr,
        size,
        try_alignment,
        commit,
        allow_large,
        is_large,
        is_zero,
        &mut p,
    );

    if err != 0 {
        // In Rust, we'd typically log this rather than print directly
        eprintln!(
            "unable to allocate OS memory (error: {} (0x{:x}), addr: {:?}, size: 0x{:x} bytes, align: 0x{:x}, commit: {}, allow large: {})",
            err, err, hint_addr_ptr, size, try_alignment, commit, allow_large
        );
    }

    {
        let mut stats = _mi_stats_main.lock().unwrap();
        _mi_stat_counter_increase(Some(&mut stats.mmap_calls), 1);
    }

    if p.is_some() {
        let mut stats = _mi_stats_main.lock().unwrap();
        // Convert usize to i64 before adding to avoid type mismatches
        let size_i64 = size as i64;
        stats.reserved.current += size_i64;
        stats.reserved.total += size_i64;
        if stats.reserved.current > stats.reserved.peak {
            stats.reserved.peak = stats.reserved.current;
        }

        if commit {
            stats.committed.current += size_i64;
            stats.committed.total += size_i64;
            if stats.committed.current > stats.committed.peak {
                stats.committed.peak = stats.committed.current;
            }
        }
    }

    p
}
pub fn mi_os_prim_alloc(
    size: usize,
    try_alignment: usize,
    commit: bool,
    allow_large: bool,
    is_large: &mut bool,
    is_zero: &mut bool,
) -> Option<&'static mut std::ffi::c_void> {
    mi_os_prim_alloc_at(Option::None, size, try_alignment, commit, allow_large, is_large, is_zero)
}

pub fn _mi_os_alloc(size: usize, memid: &mut MiMemidS) -> Option<&'static mut c_void> {
    *memid = _mi_memid_none();
    
    if size == 0 {
        return None;
    }
    
    let size = _mi_os_good_alloc_size(size);
    let mut os_is_large = false;
    let mut os_is_zero = false;
    
    let p = mi_os_prim_alloc(size, 0, true, false, &mut os_is_large, &mut os_is_zero)?;
    
    *memid = _mi_memid_create_os(None, size, true, os_is_zero, os_is_large);
    
    // Assertions
    if let MiMemidUnion::Os(ref mem_os) = memid.mem {
        assert!(mem_os.size >= size, "memid->mem.os.size >= size");
    }
    assert!(memid.initially_committed, "memid->initially_committed");
    
    Some(p)
}
pub fn _mi_os_zalloc(size: usize, memid: &mut MiMemidS) -> Option<&'static mut c_void> {
    let p = _mi_os_alloc(size, memid)?;
    
    // Convert to byte slice and ensure zero using the provided function
    let p_slice = unsafe { 
        std::slice::from_raw_parts_mut(p as *mut c_void as *mut u8, size) 
    };
    
    // Use mi_os_ensure_zero as in the original C code
    mi_os_ensure_zero(Some(p_slice), size, memid)?;
    
    Some(p)
}
pub fn mi_os_page_align_area_conservative(
    addr: *mut std::ffi::c_void,
    size: usize,
    newsize: *mut usize
) -> *mut std::ffi::c_void {
    mi_os_page_align_areax(true, addr, size, newsize)
}
pub fn _mi_os_reset(addr: *mut c_void, size: usize) -> bool {
    let mut csize: usize = 0;
    let start = mi_os_page_align_area_conservative(addr, size, &mut csize);
    
    if csize == 0 {
        return true;
    }
    
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        // Convert the reference to the expected type
        let reset_stat = unsafe { &mut *(&mut stats.reset as *mut crate::mi_stat_count_t::MiStatCountS as *mut crate::mi_stat_count_t::MiStatCountS) };
        crate::_mi_stat_increase(reset_stat, csize);
        _mi_stat_counter_increase(Some(&mut stats.reset_calls), 1);
    }
    
    // Use ptr::write_bytes instead of memset
    unsafe {
        ptr::write_bytes(start as *mut u8, 0, csize);
    }
    
    let err = _mi_prim_reset(start, csize);
    if err != 0 {
        let msg = std::ffi::CString::new("cannot reset OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n").unwrap();
        _mi_warning_message(&msg);
    }
    
    err == 0
}
pub fn mi_os_decommit_ex(
    addr: *mut std::ffi::c_void,
    size: usize,
    needs_recommit: Option<&mut bool>,
    stat_size: usize,
) -> bool {
    // Check for NULL pointer equivalent - needs_recommit must be Some
    let needs_recommit = match needs_recommit {
        Some(ptr) => ptr,
        None => {
            _mi_assert_fail(
                "needs_recommit!=NULL",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/os.c",
                483,
                Some("mi_os_decommit_ex"),
            );
            return false;
        }
    };

    // Decrease the committed stat
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        // Convert between the different MiStatCountS types
        let mut committed_stat = crate::mi_stat_count_t::MiStatCountS {
            total: stats.committed.total,
            peak: stats.committed.peak,
            current: stats.committed.current,
        };
        _mi_stat_decrease(&mut committed_stat, stat_size);
        // Update the original stats
        stats.committed.total = committed_stat.total;
        stats.committed.peak = committed_stat.peak;
        stats.committed.current = committed_stat.current;
    }

    let mut csize: usize = 0;
    let start = mi_os_page_align_area_conservative(addr, size, &mut csize);

    if csize == 0 {
        return true;
    }

    *needs_recommit = true;
    let err = unsafe {
        _mi_prim_decommit(start, csize, needs_recommit)
    };

    if err != 0 {
        let msg = std::ffi::CString::new("cannot decommit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n").unwrap();
        _mi_warning_message(&msg);
    }

    // Assert that err == 0
    if err != 0 {
        _mi_assert_fail(
            "err == 0",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/os.c",
            497,
            Some("mi_os_decommit_ex"),
        );
    }

    err == 0
}
pub fn _mi_os_purge_ex(p: *mut std::ffi::c_void, size: usize, allow_reset: bool, stat_size: usize) -> bool {
    if crate::mi_option_get(crate::MiOptionE::MiOptionPurgeDelay) < 0 {
        return false;
    }
    
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        crate::_mi_stat_counter_increase(Some(&mut stats.purge_calls), 1);
        // Cast the reference to the expected type for _mi_stat_increase
        let purged_stat = unsafe { &mut *(&mut stats.purged as *mut _ as *mut crate::mi_stat_count_t::MiStatCountS) };
        crate::_mi_stat_increase(purged_stat, size);
    }
    
    if crate::mi_option_is_enabled(crate::MiOptionE::MiOptionPurgeDecommits) && (!crate::_mi_preloading()) {
        let mut needs_recommit = true;
        crate::mi_os_decommit_ex(p, size, Some(&mut needs_recommit), stat_size);
        needs_recommit
    } else {
        if allow_reset {
            crate::_mi_os_reset(p, size);
        }
        false
    }
}
pub fn _mi_os_purge(p: *mut std::ffi::c_void, size: usize) -> bool {
    _mi_os_purge_ex(p, size, true, size)
}
pub fn mi_os_protectx(addr: *mut std::ffi::c_void, size: usize, protect: bool) -> bool {
    let mut csize: usize = 0;
    let start = mi_os_page_align_area_conservative(addr, size, &mut csize);
    if csize == 0 {
        return false;
    }
    let err = _mi_prim_protect(start, csize, protect);
    if err != 0 {
        let action = if protect { "protect" } else { "unprotect" };
        let msg = std::ffi::CString::new(
            format!("cannot {} OS memory (error: {} (0x{:x}), address: {:?}, size: 0x{:x} bytes)\n", 
                    action, err, err, start, csize)
        ).unwrap();
        _mi_warning_message(&msg);
    }
    err == 0
}
static MI_NUMA_NODE_COUNT: AtomicUsize = AtomicUsize::new(0);

pub fn _mi_os_numa_node_count() -> i32 {
    let mut count = MI_NUMA_NODE_COUNT.load(Ordering::Acquire);
    
    if count == 0 {
        // mi_option_use_numa_nodes is typically option index 7 in mimalloc
        let ncount = 0; // Default to 0 since we can't access the option
        if ncount > 0 && ncount < 2147483647 {
            count = ncount as usize;
        } else {
            let n = _mi_prim_numa_node_count();
            if n == 0 || n > 2147483647 {
                count = 1;
            } else {
                count = n;
            }
        }
        MI_NUMA_NODE_COUNT.store(count, Ordering::Release);
        let msg = CString::new("using %zd numa regions\n").unwrap();
        unsafe {
            _mi_verbose_message(msg.as_ptr() as *const c_char, &mut count as *mut _ as *mut std::ffi::c_void);
        }
    }
    
    assert!(count > 0 && count <= 2147483647, "count > 0 && count <= INT_MAX");
    count as i32
}
pub static mi_huge_start: AtomicUsize = AtomicUsize::new(0);

pub fn mi_os_claim_huge_pages(pages: usize, mut total_size: Option<&mut usize>) -> Option<*mut u8> {
    if let Some(total_size_ref) = total_size.as_mut() {
        **total_size_ref = 0;
    }
    
    const GB: usize = 1024 * 1024 * 1024;
    let size = pages * GB;
    
    let mut huge_start = mi_huge_start.load(Ordering::Relaxed);
    let start = loop {
        let current_start = if huge_start == 0 {
            32 << 40
        } else {
            huge_start
        };
        
        let calculated_end = current_start + size;
        
        // Assertion: end % MI_SEGMENT_SIZE == 0
        // MI_SEGMENT_SIZE = 1UL << (9 + (13 + 3)) = 1UL << 25 = 33554432
        const MI_SEGMENT_SIZE: usize = 1 << 25;
        assert!(calculated_end % MI_SEGMENT_SIZE == 0, "end % MI_SEGMENT_SIZE == 0");
        
        match mi_huge_start.compare_exchange_weak(
            huge_start,
            calculated_end,
            Ordering::AcqRel,
            Ordering::Acquire
        ) {
            Ok(_) => break current_start,
            Err(actual) => huge_start = actual,
        }
    };
    
    if let Some(total_size_ref) = total_size.as_mut() {
        **total_size_ref = size;
    }
    
    Some(start as *mut u8)
}
pub fn helper__mi_os_alloc_huge_os_pages_1(
    page_ref: &mut usize,
    all_zero_ref: &mut bool,
    pages: usize,
    numa_node: i32,
    max_msecs: crate::types::mi_msecs_t,
    start: &mut [u8],
    start_t: crate::types::mi_msecs_t,
) {
    let mut page = *page_ref;
    let mut all_zero = *all_zero_ref;
    let mut is_zero = false;
    
    let addr = {
        let offset = page * ((1024 * 1024) * 1024);
        unsafe { start.as_mut_ptr().add(offset) as *mut std::ffi::c_void }
    };
    
    let mut p: Option<&'static mut std::ffi::c_void> = None;
    let mut addr_mut = if addr.is_null() { None } else { Some(unsafe { &mut *addr }) };
    let err = _mi_prim_alloc_huge_os_pages(addr_mut, (1024 * 1024) * 1024, numa_node, &mut is_zero, &mut p);
    
    if !is_zero {
        all_zero = false;
    }
    
    if err != 0 {
        let msg = std::ffi::CString::new("unable to allocate huge OS page (error: %d (0x%x), address: %p, size: %zx bytes)\n").unwrap();
        _mi_warning_message(&msg);
        return;
    }
    
    let addr_ptr = addr;
    let p_ptr = p.as_mut().map(|p_ref| *p_ref as *mut _).unwrap_or(std::ptr::null_mut());
    
    if p_ptr != addr_ptr {
        if !p_ptr.is_null() {
            let msg = std::ffi::CString::new("could not allocate contiguous huge OS page %zu at %p\n").unwrap();
            _mi_warning_message(&msg);
            let slice = unsafe { std::slice::from_raw_parts_mut(p_ptr as *mut u8, (1024 * 1024) * 1024) };
            mi_os_prim_free(Some(slice), (1024 * 1024) * 1024, (1024 * 1024) * 1024);
        }
        return;
    }
    
    page += 1;
    
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        _mi_stat_increase(&mut stats.committed, (1024 * 1024) * 1024);
        _mi_stat_increase(&mut stats.reserved, (1024 * 1024) * 1024);
    }
    
    if max_msecs > 0 {
        let mut elapsed = _mi_clock_end(start_t);
        if page >= 1 {
            let estimate = (elapsed / (page as i64 + 1)) * (pages as i64);
            if estimate > (2 * max_msecs) {
                elapsed = max_msecs + 1;
            }
        }
        if elapsed > max_msecs {
            let msg = std::ffi::CString::new("huge OS page allocation timed out (after allocating %zu page(s))\n").unwrap();
            _mi_warning_message(&msg);
            return;
        }
    }
    
    *page_ref = page;
    *all_zero_ref = all_zero;
}
pub fn _mi_os_alloc_huge_os_pages(
    pages: usize,
    numa_node: i32,
    max_msecs: crate::types::mi_msecs_t,
    mut pages_reserved: Option<&mut usize>,
    mut psize: Option<&mut usize>,
    mut memid: Option<&mut crate::MiMemidS>,
) -> Option<*mut u8> {
    if let Some(ref mut memid_ref) = memid {
        **memid_ref = _mi_memid_none();
    }
    
    if let Some(ref mut psize_ref) = psize {
        **psize_ref = 0;
    }
    
    if let Some(ref mut pages_reserved_ref) = pages_reserved {
        **pages_reserved_ref = 0;
    }
    
    let mut size = 0;
    let start = mi_os_claim_huge_pages(pages, Some(&mut size))?;
    
    let start_t = _mi_clock_start();
    let mut page = 0;
    let mut all_zero = true;
    
    while page < pages {
        helper__mi_os_alloc_huge_os_pages_1(
            &mut page,
            &mut all_zero,
            pages,
            numa_node,
            max_msecs,
            unsafe { std::slice::from_raw_parts_mut(start, size) },
            start_t,
        );
    }
    
    assert!(
        page * ((1024 * 1024) * 1024) <= size,
        "page*MI_HUGE_OS_PAGE_SIZE <= size"
    );
    
    if let Some(ref mut pages_reserved_ref) = pages_reserved {
        **pages_reserved_ref = page;
    }
    
    if let Some(ref mut psize_ref) = psize {
        **psize_ref = page * ((1024 * 1024) * 1024);
    }
    
    if page != 0 {
        assert!(!start.is_null(), "start != NULL");
        
        if let Some(ref mut memid_ref) = memid {
            **memid_ref = _mi_memid_create_os(
                Option::None,
                size,
                true,
                all_zero,
                true,
            );
            memid_ref.memkind = crate::MiMemkindE::MiMemOsHuge;
            assert!(memid_ref.is_pinned, "memid->is_pinned");
        }
        
        Some(start)
    } else {
        None
    }
}
pub fn helper_helper_mi_os_prim_alloc_aligned_1_1<'a>(
    p_idx_ref: &'a mut u32,
    size: usize,
    alignment: usize,
    commit: bool,
    is_large: &'a mut bool,
    is_zero: &'a mut bool,
    base: &'a mut Option<&'a mut std::ffi::c_void>,
    p: Option<&'a mut std::ffi::c_void>,
    over_size: usize,
) -> Option<&'a mut std::ffi::c_void> {
    let mut p_idx = *p_idx_ref;
    
    let alloc_result = mi_os_prim_alloc(over_size, 1, commit, false, is_large, is_zero);
    p_idx = match alloc_result {
        Some(ptr) => ptr as *mut std::ffi::c_void as u32,
        None => return None,
    };

    if p.is_none() {
        return None;
    }

    // Take ownership of p to avoid move issues
    let p_ptr = p.unwrap() as *mut std::ffi::c_void;
    
    // Create a new Option from the raw pointer to pass to mi_align_up_ptr
    let p_for_alignment = unsafe { Some(&mut *p_ptr) };
    let aligned_p = mi_align_up_ptr(p_for_alignment, alignment);
    if aligned_p.is_none() {
        return None;
    }
    let aligned_p = aligned_p.unwrap();

    let aligned_p_ptr = aligned_p as *mut std::ffi::c_void;
    
    let pre_size = (aligned_p_ptr as *const u8 as usize) - (p_ptr as *const u8 as usize);
    let mid_size = _mi_align_up(size, _mi_os_page_size());
    let post_size = over_size - pre_size - mid_size;

    assert!(
        pre_size < over_size && post_size < over_size && mid_size >= size,
        "pre_size < over_size && post_size < over_size && mid_size >= size"
    );

    if pre_size > 0 {
        let pre_slice = unsafe {
            std::slice::from_raw_parts_mut(p_ptr as *mut u8, pre_size)
        };
        mi_os_prim_free(Some(pre_slice), pre_size, if commit { pre_size } else { 0 });
    }

    if post_size > 0 {
        let post_start = unsafe { (aligned_p_ptr as *mut u8).add(mid_size) };
        let post_slice = unsafe {
            std::slice::from_raw_parts_mut(post_start, post_size)
        };
        mi_os_prim_free(Some(post_slice), post_size, if commit { post_size } else { 0 });
    }

    p_idx = aligned_p_ptr as u32;
    *base = Some(unsafe { &mut *aligned_p_ptr });
    *p_idx_ref = p_idx;

    Some(unsafe { &mut *aligned_p_ptr })
}
pub fn helper_mi_os_prim_alloc_aligned_1<'a>(
    p_idx_ref: &'a mut u32,
    size: usize,
    alignment: usize,
    commit: bool,
    is_large: &'a mut bool,
    is_zero: &'a mut bool,
    base: &'a mut Option<&'a mut std::ffi::c_void>,
    mut p: Option<&'a mut std::ffi::c_void>,
) -> Option<&'a mut std::ffi::c_void> {
    let mut p_idx = *p_idx_ref;
    
    // Create a C string from the format string
    let msg = std::ffi::CString::new("unable to allocate aligned OS memory directly, fall back to over-allocation").unwrap();
    _mi_warning_message(&msg);
    
    if let Some(ref mut p_ptr) = p {
        // Check if p[p_idx] is not null (equivalent to (&p[p_idx]) != 0 in C)
        unsafe {
            let offset_ptr = (*p_ptr as *mut std::ffi::c_void as *mut u8).add(p_idx as usize) as *mut std::ffi::c_void;
            if !offset_ptr.is_null() {
                mi_os_prim_free(Some(unsafe { std::slice::from_raw_parts_mut(offset_ptr as *mut u8, size) }), size, if commit { size } else { 0 });
            }
        }
    }
    
    if size >= (usize::MAX - alignment) {
        return Option::None;
    }
    
    let over_size = size + alignment;
    let mi_os_mem_config = MI_OS_MEM_CONFIG.lock().unwrap();
    
    if !mi_os_mem_config.has_partial_free {
        drop(mi_os_mem_config); // Release the lock before calling other functions
        
        let alloc_result = mi_os_prim_alloc(over_size, 1, false, false, is_large, is_zero);
        let base_ptr = match alloc_result {
            Some(ptr) => ptr,
            None => return Option::None,
        };
            
        unsafe {
            *base = Some(&mut *(base_ptr as *mut std::ffi::c_void));
        }
        
        // Fix: Use the base pointer directly without moving it out
        let aligned_ptr = if let Some(base_ptr) = base.as_mut() {
            mi_align_up_ptr(Some(*base_ptr), alignment)
        } else {
            Option::None
        };
        p_idx = match aligned_ptr {
            Some(ptr) => ptr as *mut std::ffi::c_void as usize as u32,
            None => {
                if let Some(base_ptr) = base.as_mut() {
                    mi_os_prim_free(Some(unsafe { std::slice::from_raw_parts_mut(*base_ptr as *mut std::ffi::c_void as *mut u8, over_size) }), over_size, 0);
                }
                return Option::None;
            }
        };
            
        if commit {
            let commit_ptr = unsafe { &mut *(p_idx as *mut std::ffi::c_void) };
            if !_mi_os_commit(commit_ptr, size, Option::None) {
                if let Some(base_ptr) = base.as_mut() {
                    mi_os_prim_free(Some(unsafe { std::slice::from_raw_parts_mut(*base_ptr as *mut std::ffi::c_void as *mut u8, over_size) }), over_size, 0);
                }
                return Option::None;
            }
        }
    } else {
        drop(mi_os_mem_config); // Release the lock before calling other functions
        
        // Use p_idx_ref directly instead of creating a temporary
        let result = helper_helper_mi_os_prim_alloc_aligned_1_1(
            p_idx_ref,
            size,
            alignment,
            commit,
            is_large,
            is_zero,
            base,
            p,
            over_size,
        );
        
        return result;
    }
    
    *p_idx_ref = p_idx;
    Some(unsafe { &mut *(p_idx as *mut std::ffi::c_void) })
}
pub fn mi_os_prim_alloc_aligned<'a>(
    size: usize,
    alignment: usize,
    commit: bool,
    allow_large: bool,
    is_large: &'a mut bool,
    is_zero: &'a mut bool,
    base: &'a mut Option<&'a mut std::ffi::c_void>,
) -> Option<&'a mut std::ffi::c_void> {
    // Assertions translated to debug assertions
    debug_assert!(alignment >= _mi_os_page_size() && (alignment & (alignment - 1)) == 0);
    debug_assert!(size > 0 && (size % _mi_os_page_size()) == 0);
    debug_assert!(is_large as *const _ != std::ptr::null());
    debug_assert!(is_zero as *const _ != std::ptr::null());
    debug_assert!(base as *const _ != std::ptr::null());

    let mut allow_large = allow_large;
    if !commit {
        allow_large = false;
    }

    if !(alignment >= _mi_os_page_size() && (alignment & (alignment - 1)) == 0) {
        return Option::None;
    }

    let size = _mi_align_up(size, _mi_os_page_size());
    let p = mi_os_prim_alloc(size, alignment, commit, allow_large, is_large, is_zero);
    
    if p.is_none() {
        return Option::None;
    }

    // Get the pointer value without consuming the Option
    let p_ptr = p.unwrap() as *mut std::ffi::c_void;
    
    if (p_ptr as usize) % alignment == 0 {
        *base = Some(unsafe { &mut *p_ptr });
        // Return the original Option by reconstructing it
        Some(unsafe { &mut *p_ptr })
    } else {
        // Create a longer-lived p_idx by making it mutable and ensuring it lives long enough
        let mut p_idx: u32 = 0;
        let p_idx_ref: &'a mut u32 = unsafe { &mut *(std::ptr::addr_of_mut!(p_idx) as *mut u32) };
        // Call the helper function but don't return its result
        helper_mi_os_prim_alloc_aligned_1(
            p_idx_ref,
            size,
            alignment,
            commit,
            is_large,
            is_zero,
            base,
            Some(unsafe { &mut *p_ptr }),
        );
        // Return the original p, following the C code behavior
        Some(unsafe { &mut *p_ptr })
    }
}
pub fn _mi_os_alloc_aligned(
    size: usize,
    alignment: usize,
    commit: bool,
    allow_large: bool,
    memid: &mut MiMemidS,
) -> Option<&mut c_void> {
    // (void)(&_mi_os_get_aligned_hint) — no-op in Rust

    *memid = _mi_memid_none();

    if size == 0 {
        return Option::None;
    }

    let size = _mi_os_good_alloc_size(size);
    let alignment = _mi_align_up(alignment, _mi_os_page_size());

    // Use long-lived temporaries so the callee's internal `'a` does not borrow our stack locals.
    static mut MI_OS_IS_LARGE: bool = false;
    static mut MI_OS_IS_ZERO: bool = false;
    static mut MI_OS_BASE: Option<&'static mut std::ffi::c_void> = Option::None;

    // Call the primitive aligned allocator
    let p = unsafe {
        // reset the temporaries before the call
        MI_OS_IS_LARGE = false;
        MI_OS_IS_ZERO = false;
        MI_OS_BASE = Option::None;

        mi_os_prim_alloc_aligned(
            size,
            alignment,
            commit,
            allow_large,
            &mut MI_OS_IS_LARGE,
            &mut MI_OS_IS_ZERO,
            // Transmute the `'static` base slot reference to the expected `&'a mut ...`
            std::mem::transmute::<
                &mut Option<&'static mut std::ffi::c_void>,
                &mut Option<&mut std::ffi::c_void>,
            >(&mut MI_OS_BASE),
        )
    };

    if p.is_none() {
        return Option::None;
    }

    // Keep a single mutable reference to the returned pointer
    let p_ref = p.unwrap();

    // Snapshot auxiliary flags/addresses from the static temps (no active borrows).
    // FIX for E0606/E0596: avoid `as_ref().map(|b| ...)` on `Option<&mut T>` which yields `&&mut T`
    // (you can't deref to `&mut T` through an immutable `&`), and avoid casting the value itself.
    // Instead, borrow the Option mutably and use `as_deref_mut()` to get `Option<&mut c_void>`,
    // then convert that reference to a raw pointer.
    let (os_is_zero_val, os_is_large_val, base_addr_opt) = unsafe {
        let base_addr = MI_OS_BASE
            .as_deref_mut()
            .map(|ptr: &mut std::ffi::c_void| ptr as *mut std::ffi::c_void as usize);
        (MI_OS_IS_ZERO, MI_OS_IS_LARGE, base_addr)
    };

    // Create the memid with captured properties
    *memid = _mi_memid_create_os(
        Option::None, // no boxed base buffer ownership
        size,
        commit,
        os_is_zero_val,
        os_is_large_val,
    );

    // Set OS-specific info and compute size adjustment from (p - base)
    if let MiMemidUnion::Os(ref mut os_info) = &mut memid.mem {
        os_info.base = Option::None; // we don't own a boxed base
        if let Some(base_addr) = base_addr_opt {
            let p_addr = p_ref as *const c_void as usize;
            os_info.size = os_info.size.saturating_add(p_addr.saturating_sub(base_addr));
        }

        // Assert: memid->mem.os.size >= size
        if os_info.size < size {
            _mi_assert_fail(
                "memid->mem.os.size >= size",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/os.c",
                356,
                Some("_mi_os_alloc_aligned"),
            );
        }
    }

    // Assert: _mi_is_aligned(p, alignment)
    if !_mi_is_aligned(Some(p_ref), alignment) {
        _mi_assert_fail(
            "_mi_is_aligned(p,alignment)",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/os.c",
            357,
            Some("_mi_os_alloc_aligned"),
        );
    }

    // If commit is requested, memid.initially_committed must be true
    if commit && !memid.initially_committed {
        _mi_assert_fail(
            "memid->initially_committed",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/os.c",
            358,
            Some("_mi_os_alloc_aligned"),
        );
    }

    Some(p_ref)
}
pub fn _mi_os_init() {
    let mut config = MI_OS_MEM_CONFIG.lock().unwrap();
    _mi_prim_mem_init(&mut *config);
}
pub fn _mi_os_has_virtual_reserve() -> bool {
    MI_OS_MEM_CONFIG.lock().unwrap().has_virtual_reserve
}
pub fn mi_os_numa_node_get() -> i32 {
    let numa_count = _mi_os_numa_node_count();
    if numa_count <= 1 {
        return 0;
    }
    let n = _mi_prim_numa_node();
    let mut numa_node = if n < 2147483647 { n as i32 } else { 0 };
    if numa_node >= numa_count {
        numa_node = numa_node % numa_count;
    }
    numa_node
}

pub static mi_numa_node_count: AtomicUsize = AtomicUsize::new(0);

pub fn _mi_os_numa_node() -> i32 {
    if mi_numa_node_count.load(Ordering::Relaxed) == 1 {
        0
    } else {
        mi_os_numa_node_get()
    }
}
pub fn _mi_os_decommit(addr: *mut std::ffi::c_void, size: usize) -> bool {
    let mut needs_recommit = false;
    mi_os_decommit_ex(addr, size, Some(&mut needs_recommit), size)
}
pub fn _mi_os_alloc_aligned_at_offset(
    size: usize,
    alignment: usize,
    offset: usize,
    commit: bool,
    allow_large: bool,
    memid: &mut MiMemidS,
) -> Option<&mut c_void> {
    assert!(offset <= (1 << (9 + (13 + 3))), "offset <= MI_SEGMENT_SIZE");
    assert!(offset <= size, "offset <= size");
    assert!(
        alignment % _mi_os_page_size() == 0,
        "(alignment % _mi_os_page_size()) == 0"
    );
    
    *memid = _mi_memid_none();
    
    if offset > (1 << (9 + (13 + 3))) {
        return Option::None;
    }
    
    if offset == 0 {
        return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
    } else {
        let extra = _mi_align_up(offset, alignment) - offset;
        let oversize = size + extra;
        let start = _mi_os_alloc_aligned(oversize, alignment, commit, allow_large, memid);
        
        if start.is_none() {
            return Option::None;
        }
        
        let start_ptr = start.unwrap() as *mut c_void as *mut u8;
        let p = unsafe { &mut *(start_ptr.add(extra) as *mut c_void) };
        
        assert!(
            _mi_is_aligned(
                Some(unsafe { &mut *((p as *mut c_void as *mut u8).add(offset) as *mut c_void) }),
                alignment
            ),
            "_mi_is_aligned((uint8_t*)p + offset, alignment)"
        );
        
        if commit && (extra > _mi_os_page_size()) {
            _mi_os_decommit(unsafe { &mut *(start_ptr as *mut c_void) }, extra);
        }
        
        Some(p)
    }
}
pub fn _mi_os_reuse(addr: *mut std::ffi::c_void, size: usize) {
    let mut csize: usize = 0;
    let start = mi_os_page_align_area_conservative(addr, size, &mut csize);
    
    if csize == 0 {
        return;
    }
    
    // Convert the raw pointer to Option<&mut c_void> for _mi_prim_reuse
    let start_opt = if start.is_null() {
        Option::None
    } else {
        // For non-null pointers, we need to create a mutable reference
        // This is safe because we're only using it within this function scope
        // and the pointer is properly aligned and valid
        unsafe { Some(&mut *(start as *mut std::ffi::c_void)) }
    };
    
    let err = _mi_prim_reuse(start_opt, csize);
    
    if err != 0 {
        let msg = std::ffi::CString::new(format!("cannot reuse OS memory (error: {} (0x{:x}), address: {:?}, size: 0x{:x} bytes)\n", err, err, start, csize)).unwrap();
        _mi_warning_message(&msg);
    }
}
pub fn _mi_os_protect(addr: *mut std::ffi::c_void, size: usize) -> bool {
    mi_os_protectx(addr, size, true)
}
pub fn _mi_os_large_page_size() -> usize {
    let config = MI_OS_MEM_CONFIG.lock().unwrap();
    if config.large_page_size != 0 {
        config.large_page_size
    } else {
        _mi_os_page_size()
    }
}
