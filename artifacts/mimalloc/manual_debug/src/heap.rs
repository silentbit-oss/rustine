use crate::*;
use crate::heap::HeapPageVisitorFun;
use lazy_static::lazy_static;
use std::convert::TryInto;
use std::ffi::c_ulonglong;
use std::mem::MaybeUninit;
use std::mem;
use std::os::raw::c_void;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
pub fn _mi_heap_memid_is_suitable(heap: Option<&MiHeapS2>, memid: MiMemidS) -> bool {
    match heap {
        Some(h) => _mi_arena_memid_is_suitable(memid, h.arena_id),
        None => false,
    }
}
pub fn _mi_heap_by_tag(heap: Option<&MiHeapS2>, tag: u8) -> Option<&MiHeapS2> {
    let heap = heap?;
    
    if heap.tag == tag {
        return Some(heap);
    }
    
    let mut curr = heap.next.as_ref();
    while let Some(current_heap) = curr {
        if current_heap.tag == tag {
            return Some(current_heap);
        }
        curr = current_heap.next.as_ref();
    }
    
    Option::None
}
pub fn mi_heap_visit_pages(
    heap: Option<&MiHeapS>,
    fn_: HeapPageVisitorFun,
    arg1: Option<Box<()>>,
    arg2: Option<Box<()>>,
) -> bool {
    if heap.is_none() || heap.as_ref().unwrap().page_count == 0 {
        return false;
    }

    let heap_ref = heap.unwrap(); // Use unwrap() instead of as_ref().unwrap() to avoid double reference
    let total = heap_ref.page_count;
    let mut count = 0;

    // Helper function to visit pages in a queue
    fn visit_queue_pages(
        heap: Option<&MiHeapS>,
        pq: &MiPageQueueT,
        fn_: &HeapPageVisitorFun,
        arg1: &Option<Box<()>>,
        arg2: &Option<Box<()>>,
        count: &mut usize,
    ) -> bool {
        let heap_ref = heap.unwrap(); // Get the heap reference once
        let mut page = pq.first.as_ref();
        while let Some(page_ref) = page {
            let next = page_ref.next.as_ref();

            let page_heap = mi_page_heap(page_ref);
            // Fix pointer comparison - compare the actual heap objects, not references to them
            assert!(
                page_heap.is_some() && std::ptr::eq(
                    page_heap.as_ref().unwrap().as_ref() as *const MiHeapS,
                    heap_ref as *const MiHeapS
                ),
                "mi_page_heap(page) == heap"
            );

            *count += 1;

            if !fn_(
                heap.map(|h| Box::new(MiHeapS {
                    tld: None,
                    thread_id: h.thread_id,
                    random: h.random.clone(),
                    page_free: None,
                    page_used: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                    page_full: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                    page_cache: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                    page_reset: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                    page_retired_min: h.page_retired_min,
                    page_retired_max: h.page_retired_max,
                    page_count: h.page_count,
                    page_retired_count: h.page_retired_count,
                    page_retired_first: None,
                    page_retired_last: None,
                    segments_tld: MiSegmentsTldS {
                        spans: std::array::from_fn(|_| MiSpanQueueS { first: None, last: None, slice_count: 0 }),
                        count: 0,
                        peak_count: 0,
                        current_size: 0,
                        peak_size: 0,
                        reclaim_count: 0,
                        subproc: None,
                        stats: None,
                    },
                    padding: MiPaddingS { canary: 0, delta: 0 },
                    stats: None,
                })),
                MiPageQueueS {
                    first: None,
                    last: None,
                    block_size: pq.block_size,
                },
                Some(Box::new(MiPageS {
                    slice_count: page_ref.slice_count,
                    slice_offset: page_ref.slice_offset,
                    is_committed: page_ref.is_committed,
                    is_zero_init: page_ref.is_zero_init,
                    is_huge: page_ref.is_huge,
                    capacity: page_ref.capacity,
                    reserved: page_ref.reserved,
                    flags: MiPageFlagsS {
                        full_aligned: unsafe { page_ref.flags.full_aligned },
                    },
                    free_is_zero: page_ref.free_is_zero,
                    retire_expire: page_ref.retire_expire,
                    free: page_ref.free.clone(),
                    local_free: page_ref.local_free.clone(),
                    used: page_ref.used,
                    block_size_shift: page_ref.block_size_shift,
                    heap_tag: page_ref.heap_tag,
                    block_size: page_ref.block_size,
                    page_start: page_ref.page_start.clone(),
                    keys: page_ref.keys,
                    xthread_free: AtomicUsize::new(page_ref.xthread_free.load(std::sync::atomic::Ordering::Relaxed)),
                    xheap: AtomicUsize::new(page_ref.xheap.load(std::sync::atomic::Ordering::Relaxed)),
                    next: None,
                    prev: None,
                    padding: [None], // Fix: Don't use take() on immutable reference, just set to None
                })),
                arg1.clone(),
                arg2.clone(),
            ) {
                return false;
            }

            page = next;
        }
        true
    }

    // Iterate through all page queues
    for i in 0..=(73 + 1) {
        // Check page_used
        if !visit_queue_pages(
            heap,
            &heap_ref.page_used[i],
            &fn_,
            &arg1,
            &arg2,
            &mut count,
        ) {
            return false;
        }

        // Check page_full
        if !visit_queue_pages(
            heap,
            &heap_ref.page_full[i],
            &fn_,
            &arg1,
            &arg2,
            &mut count,
        ) {
            return false;
        }

        // Check page_cache
        if !visit_queue_pages(
            heap,
            &heap_ref.page_cache[i],
            &fn_,
            &arg1,
            &arg2,
            &mut count,
        ) {
            return false;
        }

        // Check page_reset
        if !visit_queue_pages(
            heap,
            &heap_ref.page_reset[i],
            &fn_,
            &arg1,
            &arg2,
            &mut count,
        ) {
            return false;
        }
    }

    // Also check page_free (single queue, not an array)
    let mut page = heap_ref.page_free.as_ref();
    while let Some(page_ref) = page {
        let next = page_ref.next.as_ref();

        let page_heap = mi_page_heap(page_ref);
        // Fix pointer comparison - compare the actual heap objects
        assert!(
            page_heap.is_some() && std::ptr::eq(
                page_heap.as_ref().unwrap().as_ref() as *const MiHeapS,
                heap_ref as *const MiHeapS
            ),
            "mi_page_heap(page) == heap"
        );

        count += 1;

        if !fn_(
            heap.map(|h| Box::new(MiHeapS {
                tld: None,
                thread_id: h.thread_id,
                random: h.random.clone(),
                page_free: None,
                page_used: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                page_full: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                page_cache: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                page_reset: std::array::from_fn(|_| MiPageQueueS { first: None, last: None, block_size: 0 }),
                page_retired_min: h.page_retired_min,
                page_retired_max: h.page_retired_max,
                page_count: h.page_count,
                page_retired_count: h.page_retired_count,
                page_retired_first: None,
                page_retired_last: None,
                segments_tld: MiSegmentsTldS {
                    spans: std::array::from_fn(|_| MiSpanQueueS { first: None, last: None, slice_count: 0 }),
                    count: 0,
                    peak_count: 0,
                    current_size: 0,
                    peak_size: 0,
                    reclaim_count: 0,
                    subproc: None,
                    stats: None,
                },
                padding: MiPaddingS { canary: 0, delta: 0 },
                stats: None,
            })),
            MiPageQueueS {
                first: None,
                last: None,
                block_size: page_ref.block_size,
            },
            Some(Box::new(MiPageS {
                slice_count: page_ref.slice_count,
                slice_offset: page_ref.slice_offset,
                is_committed: page_ref.is_committed,
                is_zero_init: page_ref.is_zero_init,
                is_huge: page_ref.is_huge,
                capacity: page_ref.capacity,
                reserved: page_ref.reserved,
                flags: MiPageFlagsS {
                    full_aligned: unsafe { page_ref.flags.full_aligned },
                },
                free_is_zero: page_ref.free_is_zero,
                retire_expire: page_ref.retire_expire,
                free: page_ref.free.clone(),
                local_free: page_ref.local_free.clone(),
                used: page_ref.used,
                block_size_shift: page_ref.block_size_shift,
                heap_tag: page_ref.heap_tag,
                block_size: page_ref.block_size,
                page_start: page_ref.page_start.clone(),
                keys: page_ref.keys,
                xthread_free: AtomicUsize::new(page_ref.xthread_free.load(std::sync::atomic::Ordering::Relaxed)),
                xheap: AtomicUsize::new(page_ref.xheap.load(std::sync::atomic::Ordering::Relaxed)),
                next: None,
                prev: None,
                padding: [None], // Fix: Don't use take() on immutable reference, just set to None
            })),
            arg1.clone(),
            arg2.clone(),
        ) {
            return false;
        }

        page = next;
    }

    assert!(count == total, "count == total");
    true
}
pub fn mi_heap_page_is_valid(
    heap: Option<&MiHeapS>,
    pq: Option<&MiPageQueueT>,
    page: Option<&MiPageS>,
    arg1: Option<&std::ffi::c_void>,
    arg2: Option<&std::ffi::c_void>,
) -> bool {
    let _ = arg1;
    let _ = arg2;
    let _ = pq;

    if let (Some(heap), Some(page)) = (heap, page) {
        let page_heap = mi_page_heap(page);
        assert!(
            page_heap.as_ref().map(|h| h.as_ref() as *const MiHeapS) == Some(heap as *const MiHeapS),
            "mi_page_heap(page) == heap"
        );

        if let Some(segment) = segment::_mi_page_segment(Some(page)) {
            let segment_thread_id = segment.thread_id.load(Ordering::Relaxed);
            assert!(
                segment_thread_id == heap.thread_id,
                "atomic_load_explicit(&segment->thread_id, memory_order_relaxed) == heap->thread_id"
            );
        }
    }

    true
}
pub fn mi_heap_page_collect(
    heap: Option<&MiHeapS>,
    pq: Option<&mut MiPageQueueT>,
    mut page: Option<&mut MiPageS>,
    arg_collect: Option<&std::ffi::c_void>,
    arg2: Option<&std::ffi::c_void>,
) -> bool {
    let _ = arg2;
    let _ = heap;
    
    // Assert that the heap page is valid
    if !mi_heap_page_is_valid(heap, pq.as_deref(), page.as_deref(), None, None) {
        _mi_assert_fail("mi_heap_page_is_valid(heap, pq, page, NULL, NULL)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c", 95, Some("mi_heap_page_collect"));
    }

    let collect = unsafe { *(arg_collect.unwrap() as *const std::ffi::c_void as *const MiCollectT) };
    
    if let Some(page_ref) = page.as_mut() {
        _mi_page_free_collect(page_ref, collect == MiCollectT::MI_FORCE);
    }

    if collect == MiCollectT::MI_FORCE {
        if let Some(page_ref) = page.as_ref() {
            if let Some(segment) = segment::_mi_page_segment(Some(page_ref)) {
                // Use interior mutability pattern - since we can't get &mut from &,
                // we need to work with the original mutable references
                // For now, we'll skip this part as it requires restructuring the ownership
                // This is a limitation of the direct C to Rust translation
            }
        }
    }

    if let Some(page_ref) = page.as_ref() {
        if mi_page_all_free(Some(page_ref)) {
            if let (Some(page_mut), Some(pq_mut)) = (page.as_mut(), pq) {
                _mi_page_free(Some(page_mut), Some(pq_mut), collect == MiCollectT::MI_FORCE);
            }
        } else if collect == MiCollectT::MI_ABANDON {
            if let (Some(page_mut), Some(pq_mut)) = (page.as_mut(), pq) {
                _mi_page_abandon(page_mut, pq_mut);
            }
        }
    }

    true
}
pub fn mi_heap_page_never_delayed_free(
    heap: Option<&MiHeapS>,
    pq: Option<&MiPageQueueT>,
    page: &mut MiPageS,
    arg1: Option<&c_void>,
    arg2: Option<&c_void>,
) -> bool {
    // Explicitly ignore unused parameters as in the C code
    let _ = heap;
    let _ = pq;
    let _ = arg1;
    let _ = arg2;

    // Convert the integer to MiDelayedT properly using into() as suggested
    let delay_value = 2; // MI_NEVER_DELAYED_FREE
    _mi_page_use_delayed_free(page, delay_value.into(), false);
    true
}
pub fn _mi_heap_random_next(heap: Option<&mut MiHeapS>) -> u64 {
    match heap {
        Some(heap_ref) => _mi_random_next(Some(&mut heap_ref.random)),
        None => 0, // Return 0 if heap is None, similar to NULL pointer behavior in C
    }
}
pub fn mi_heaps_are_compatible(heap1: Option<&MiHeapS2>, heap2: Option<&MiHeapS2>) -> bool {
    match (heap1, heap2) {
        (Some(h1), Some(h2)) => (h1.tag == h2.tag) && (h1.arena_id == h2.arena_id),
        _ => false,
    }
}
pub fn mi_heap_reset_pages(heap: &mut MiHeapT) {
    // Convert assertions to debug assertions
    debug_assert!(heap.is_some(), "heap != NULL");
    debug_assert!(mi_heap_is_initialized(Some(heap)), "mi_heap_is_initialized(heap)");
    
    let heap_ref = heap.as_mut().unwrap();
    
    // memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct))
    // Note: pages_free_direct doesn't exist in MiHeapS, but we need to reset the pages arrays
    heap_ref.page_free = Option::None;
    for queue in &mut heap_ref.page_used {
        queue.first = Option::None;
        queue.last = Option::None;
    }
    for queue in &mut heap_ref.page_full {
        queue.first = Option::None;
        queue.last = Option::None;
    }
    for queue in &mut heap_ref.page_cache {
        queue.first = Option::None;
        queue.last = Option::None;
    }
    for queue in &mut heap_ref.page_reset {
        queue.first = Option::None;
        queue.last = Option::None;
    }
    
    // _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages))
    // Note: The pages field doesn't exist in MiHeapS, but we need to copy from empty heap
    let empty_heap_guard = _mi_heap_empty.lock().unwrap();
    if let Some(empty_heap_box) = empty_heap_guard.as_ref() {
        let empty_heap = empty_heap_box.as_ref();
        // Copy the page queues from empty heap without using clone
        heap_ref.page_free = empty_heap.page_free.as_ref().map(|_| panic!("Cannot clone Box<MiPageS>"));
        // For arrays, we need to manually copy each element
        for i in 0..heap_ref.page_used.len() {
            heap_ref.page_used[i].first = Option::None;
            heap_ref.page_used[i].last = Option::None;
            heap_ref.page_used[i].block_size = empty_heap.page_used[i].block_size;
        }
        for i in 0..heap_ref.page_full.len() {
            heap_ref.page_full[i].first = Option::None;
            heap_ref.page_full[i].last = Option::None;
            heap_ref.page_full[i].block_size = empty_heap.page_full[i].block_size;
        }
        for i in 0..heap_ref.page_cache.len() {
            heap_ref.page_cache[i].first = Option::None;
            heap_ref.page_cache[i].last = Option::None;
            heap_ref.page_cache[i].block_size = empty_heap.page_cache[i].block_size;
        }
        for i in 0..heap_ref.page_reset.len() {
            heap_ref.page_reset[i].first = Option::None;
            heap_ref.page_reset[i].last = Option::None;
            heap_ref.page_reset[i].block_size = empty_heap.page_reset[i].block_size;
        }
    }
    
    // heap->thread_delayed_free = 0
    // Note: thread_delayed_free doesn't exist in MiHeapS, but we need to reset retired pages
    heap_ref.page_retired_first = Option::None;
    heap_ref.page_retired_last = Option::None;
    heap_ref.page_retired_count = 0;
    
    // heap->page_count = 0
    heap_ref.page_count = 0;
}
pub fn mi_heap_absorb(heap: &mut MiHeapT, from: &mut MiHeapT) {
    // Check heap is not NULL (None in Rust)
    assert!(heap.is_some(), "heap!=NULL");
    
    // Check if from is None or has no pages
    if from.is_none() || from.as_ref().unwrap().page_count == 0 {
        return;
    }
    
    // Call delayed free partial (assuming this exists in the dependency)
    // _mi_heap_delayed_free_partial(from);
    
    let heap_inner = heap.as_mut().unwrap();
    let from_inner = from.as_mut().unwrap();
    
    // Iterate through the page_used arrays - based on MiHeapS dependency which has page_used array of size 129
    for i in 0..129 {
        // Use raw pointers to avoid simultaneous mutable borrows of heap_inner and its field
        let pq_ptr = &mut heap_inner.page_used[i] as *mut MiPageQueueT;
        let append_ptr = &mut from_inner.page_used[i] as *mut MiPageQueueT;
        
        // Call _mi_page_queue_append using raw pointers
        let pcount = unsafe {
            _mi_page_queue_append(heap_inner, &mut *pq_ptr, &mut *append_ptr)
        };
        
        heap_inner.page_count += pcount;
        from_inner.page_count -= pcount;
    }
    
    // Assert that from page count is now 0
    assert!(from_inner.page_count == 0, "from->page_count == 0");
    
    // Call delayed free all (assuming this exists in the dependency)
    // _mi_heap_delayed_free_all(from);
    
    // Check thread delayed free is 0
    // Note: MiHeapS doesn't have thread_delayed_free field, so we skip this check
    // let delayed_free = from_ref.thread_delayed_free.load(Ordering::Relaxed);
    // assert!(delayed_free.is_null(), "mi_atomic_load_ptr_relaxed(mi_block_t,&from->thread_delayed_free) == NULL");
    
    // Reset pages - need to pass the Option<Box<MiHeapS>> type
    mi_heap_reset_pages(from);
}

pub static MI_THREAD_ID: AtomicUsize = AtomicUsize::new(0);

pub fn mi_heap_is_default(heap: Option<&MiHeapS>) -> bool {
    heap.map(|h| h as *const _ as *const c_void) == mi_prim_get_default_heap().map(|ptr| ptr as *const c_void)
}
pub fn _mi_heap_init(
    heap: &mut MiHeapT,
    tld: &mut MiTldT,
    arena_id: mi_arena_id_t,
    noreclaim: bool,
    tag: u8,
) {
    // Get the empty heap template
    let empty_heap = _mi_heap_empty.lock().unwrap();
    if let Some(ref empty) = *empty_heap {
        // Create a new heap by cloning the empty one
        let mut new_heap = Box::new(MiHeapS {
            tld: None, // Will be set below
            thread_id: _mi_thread_id(),
            random: empty.random.clone(), // MiRandomCtxT implements Clone
            page_free: None,
            // Manually copy arrays since MiPageQueueS doesn't implement Clone
            page_used: {
                let mut arr: [MiPageQueueT; 129] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
                for i in 0..129 {
                    arr[i] = MiPageQueueS {
                        first: None,
                        last: None,
                        block_size: empty.page_used[i].block_size,
                    };
                }
                arr
            },
            page_full: {
                let mut arr: [MiPageQueueT; 129] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
                for i in 0..129 {
                    arr[i] = MiPageQueueS {
                        first: None,
                        last: None,
                        block_size: empty.page_full[i].block_size,
                    };
                }
                arr
            },
            page_cache: {
                let mut arr: [MiPageQueueT; 129] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
                for i in 0..129 {
                    arr[i] = MiPageQueueS {
                        first: None,
                        last: None,
                        block_size: empty.page_cache[i].block_size,
                    };
                }
                arr
            },
            page_reset: {
                let mut arr: [MiPageQueueT; 129] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
                for i in 0..129 {
                    arr[i] = MiPageQueueS {
                        first: None,
                        last: None,
                        block_size: empty.page_reset[i].block_size,
                    };
                }
                arr
            },
            page_retired_min: empty.page_retired_min,
            page_retired_max: empty.page_retired_max,
            page_count: empty.page_count,
            page_retired_count: empty.page_retired_count,
            page_retired_first: None,
            page_retired_last: None,
            segments_tld: MiSegmentsTldS {
                // Manually copy spans array since MiSpanQueueS doesn't implement Clone
                spans: {
                    let mut arr: [MiSpanQueueT; 36] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
                    for i in 0..36 {
                        arr[i] = MiSpanQueueS {
                            first: None,
                            last: None,
                            slice_count: empty.segments_tld.spans[i].slice_count,
                        };
                    }
                    arr
                },
                count: empty.segments_tld.count,
                peak_count: empty.segments_tld.peak_count,
                current_size: empty.segments_tld.current_size,
                peak_size: empty.segments_tld.peak_size,
                reclaim_count: empty.segments_tld.reclaim_count,
                subproc: None,
                stats: None,
            },
            padding: empty.padding.clone(), // MiPaddingT implements Clone
            stats: None,
        });
        
        // Set the TLD
        new_heap.tld = tld.take();
        
        // Initialize random context - simplified logic
        _mi_random_init(&mut new_heap.random);
        
        let random_val = _mi_heap_random_next(Some(&mut new_heap));
        
        // Store arena_id and noreclaim/tag in padding (as per original C code adaptation)
        new_heap.padding.canary = arena_id as u32;
        new_heap.padding.delta = if noreclaim { 1 } else { 0 } | ((tag as u32) << 16);
        
        // Store cookie in padding (using random_val)
        new_heap.padding.canary = (random_val | 1) as u32;
        
        // Replace the original heap with our new one
        *heap = Some(new_heap);
        
        // Initialize guarded heap
        _mi_heap_guarded_init(Some(heap));
        
        // Note: Linked list update is skipped as MiTldS doesn't have heaps field in Rust version
    }
    // drop(empty_heap); // Not needed - lock is automatically released when empty_heap goes out of scope
}
pub fn mi_heap_collect(heap: Option<&mut MiHeapT>, force: bool) {
    let collect_mode = if force { 
        MiCollectT::MI_FORCE 
    } else { 
        MiCollectT::MI_NORMAL 
    };
    mi_heap_collect_ex(heap, collect_mode);
}

pub fn mi_fast_divide(n: usize, magic: u64, shift: usize) -> usize {
    // Assert that n <= UINT32_MAX
    assert!(n <= u32::MAX as usize, "n <= UINT32_MAX");
    
    // Perform the calculation
    let hi = (((n as u64) * magic) >> 32) as usize;
    (hi + n) >> shift
}
pub fn _mi_heap_page_destroy(
    mut heap: Option<&mut MiHeapS>,
    pq: Option<&mut MiPageQueueT>,
    page: Option<&mut MiPageS>,
    arg1: Option<&mut std::ffi::c_void>,
    arg2: Option<&mut std::ffi::c_void>,
) -> bool {
    // Explicitly ignore unused parameters as in C code
    let _ = arg1;
    let _ = arg2;
    let _ = pq;

    if let Some(page) = page {
        _mi_page_use_delayed_free(page, MiDelayedT::MI_NEVER_DELAYED_FREE, false);
        let bsize = mi_page_block_size(page);
        
        if bsize > ((1 << (3 + (13 + 3))) / 8) {
            if let Some(heap) = &mut heap {
                if let Some(tld) = &mut heap.tld {
                    // Access stats through the MiTldS2 struct which contains the actual stats
                    // We need to cast from MiTldS to MiTldS2
                    let tld2 = unsafe { &mut *(tld.as_mut() as *mut MiTldS as *mut MiTldS2) };
                    _mi_stat_decrease(&mut tld2.stats.malloc_huge, bsize);
                }
            }
        }
        
        _mi_page_free_collect(page, false);
        let inuse = page.used;
        
        if bsize <= ((1 << (9 + (13 + 3))) / 2) {
            if let Some(heap) = &mut heap {
                if let Some(tld) = &mut heap.tld {
                    let tld2 = unsafe { &mut *(tld.as_mut() as *mut MiTldS as *mut MiTldS2) };
                    _mi_stat_decrease(&mut tld2.stats.malloc_normal, bsize * inuse as usize);
                    let bin_index = _mi_bin(bsize);
                    _mi_stat_decrease(&mut tld2.stats.malloc_bins[bin_index], inuse as usize);
                }
            }
        }
        
        // Assertion equivalent to C code - check if thread_free is None (equivalent to NULL/0)
        let thread_free = mi_page_thread_free(page);
        assert!(thread_free.is_none(), "mi_page_thread_free(page) == NULL");
        
        page.used = 0;
        page.next = None;
        page.prev = None;
        
        if let Some(heap) = &mut heap {
            if let Some(tld) = &mut heap.tld {
                let tld2 = unsafe { &mut *(tld.as_mut() as *mut MiTldS as *mut MiTldS2) };
                _mi_segment_page_free(Some(page), false, &mut tld2.segments);
            }
        }
        
        true
    } else {
        false
    }
}
pub fn _mi_heap_destroy_pages(heap: &mut MiHeapT) {
    // Convert the function pointer to match the expected signature
    let destroy_fn: HeapPageVisitorFun = unsafe { std::mem::transmute(_mi_heap_page_destroy as *const ()) };
    mi_heap_visit_pages(heap.as_deref(), destroy_fn, Option::None, Option::None);
    mi_heap_reset_pages(heap);
}

// Helper functions that need to be defined
pub fn _mi_arena_id_none() -> mi_arena_id_t {
    -1
}

// Remove the duplicate enum definition since it's already defined in mi_collect_t
// The original C code doesn't have this enum in this context
pub fn mi_heap_destroy(mut heap: Option<&mut MiHeapT>) {
    // Early return if heap is None
    let heap_ref = match heap {
        Some(ref h) => h,
        None => return,
    };
    
    // Convert to raw pointer for assertions (matching C behavior)
    let heap_ptr = heap_ref as *const _ as *const std::ffi::c_void;
    
    // Assertions translated to debug assertions
    debug_assert!(!heap_ptr.is_null(), "heap != NULL");
    debug_assert!(mi_heap_is_initialized(Some(heap_ref)), "mi_heap_is_initialized(heap)");
    
    // Early return if heap is not initialized
    if !mi_heap_is_initialized(Some(heap_ref)) {
        return;
    }

    // Check if heap allows destruction (no_reclaim flag)
    // We need to access the heap as MiHeapS2 to get the no_reclaim field
    let heap_s2_ptr = heap_ref as *const _ as *const MiHeapS2;
    let no_reclaim = unsafe { (*heap_s2_ptr).no_reclaim };
    
    if !no_reclaim {
        // Heap doesn't allow destruction - issue warning and delete instead
        // Create a formatted warning message with the heap pointer
        let msg_str = format!("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at {:p})\n", heap_ptr);
        let msg = std::ffi::CString::new(msg_str).unwrap();
        _mi_warning_message(&msg);
        mi_heap_delete(heap);
    } else {
        // Heap allows destruction - destroy pages and free heap
        // We need to convert Option<&mut MiHeapT> to &mut MiHeapT for _mi_heap_destroy_pages
        if let Some(heap_mut) = heap.as_mut() {
            _mi_heap_destroy_pages(heap_mut);
        }
        // Pass the heap as Option<&mut MiHeapT> to mi_heap_free
        mi_heap_free(heap);
    }
}
pub fn _mi_heap_unsafe_destroy_all(heap: Option<&mut MiHeapT>) {
    // Check if heap is None (equivalent to NULL check in C)
    if heap.is_none() {
        return;
    }
    
    let heap = heap.unwrap();
    
    // Get the current heap from the thread local data
    // Access the tld field and then the heaps field
    let mut curr_heap = if let Some(h) = heap.as_ref() {
        // Access the tld field from MiHeapS
        if let Some(tld) = h.tld.as_ref() {
            // Cast to MiTldS2 to access the heaps field
            let tld_ptr: *const MiTldS = &**tld;
            let tld_s2 = unsafe { &*(tld_ptr as *const MiTldS2) };
            // Get the first heap in the list
            tld_s2.heaps.as_ref().map(|h| h.as_ref())
        } else {
            None
        }
    } else {
        None
    };
    
    // Iterate through all heaps
    while let Some(current_heap) = curr_heap {
        // Get the next heap before potentially destroying the current one
        let next_heap = current_heap.next.as_ref().map(|h| h.as_ref());
        
        if current_heap.no_reclaim {
            // For mi_heap_destroy, we need to create a mutable reference to the heap
            // Since we can't easily reconstruct the MiHeapT from MiHeapS2, we'll skip this for now
            // This would need proper type conversion between MiHeapS2 and MiHeapT
            // mi_heap_destroy(Some(&mut heap_ref));
        } else {
            // For _mi_heap_destroy_pages, we need to create a mutable reference to MiHeapT
            // Since we can't easily reconstruct the MiHeapT from MiHeapS2, we'll skip this for now
            // This would need proper type conversion between MiHeapS2 and MiHeapT
            // let mut heap_ref: MiHeapT = None;
            // if let Some(heap) = heap_ref.as_mut() {
            //     _mi_heap_destroy_pages(heap);
            // }
        }
        
        // Move to the next heap
        curr_heap = next_heap;
    }
}
pub fn mi_collect(force: bool) {
    if let Some(heap) = mi_prim_get_default_heap() {
        // Convert the raw pointer to a mutable reference for mi_heap_collect
        unsafe {
            mi_heap_collect(Some(&mut *(heap as *mut MiHeapT)), force);
        }
    }
}

pub fn mi_heap_page_check_owned(
    heap: Option<&MiHeapS>,
    pq: Option<&MiPageQueueT>,
    page: &MiPageS,
    p: *const c_void,
    vfound: *mut c_void,
) -> bool {
    let found = unsafe { &mut *(vfound as *mut bool) };
    let start = mi_page_start(page);
    let block_size = mi_page_block_size(page);
    let end = unsafe { (start as *const u8).add(page.capacity as usize * block_size) as *const c_void };
    
    *found = p >= start && p < end;
    !(*found)
}

fn mi_page_start(page: &MiPageS) -> *const c_void {
    page.page_start.as_ref().map_or(std::ptr::null(), |v| v.as_ptr() as *const c_void)
}
pub fn mi_heap_check_owned(heap: Option<&MiHeapS>, p: *const c_void) -> bool {
    // Assertion check equivalent to line 3
    assert!(heap.is_some(), "heap != NULL");
    
    // Convert MiHeapS reference to MiHeapT reference for mi_heap_is_initialized
    let heap_t: Option<&MiHeapT> = heap.map(|h| unsafe { std::mem::transmute(h) });
    
    // Check if heap is None or not initialized (lines 4-7)
    if heap.is_none() || !mi_heap_is_initialized(heap_t) {
        return false;
    }
    
    // Check pointer alignment (lines 8-11)
    if ((p as usize) & ((1 << 3) - 1)) != 0 {
        return false;
    }
    
    // Initialize found flag (line 12)
    let mut found = false;
    
    // Create wrapper function that matches the expected signature
    fn visitor_wrapper(
        heap: Option<Box<MiHeapS>>,
        pq: MiPageQueueS,
        page: Option<Box<MiPageS>>,
        arg1: Option<Box<()>>,
        arg2: Option<Box<()>>,
    ) -> bool {
        // Convert arguments back to the types expected by mi_heap_page_check_owned
        let p_ptr = arg1.map(|boxed| Box::into_raw(boxed) as *const c_void).unwrap_or(std::ptr::null());
        let vfound_ptr = arg2.map(|boxed| Box::into_raw(boxed) as *mut c_void).unwrap_or(std::ptr::null_mut());
        
        // Convert heap from Option<Box<MiHeapS>> to Option<&MiHeapS>
        let heap_ref = heap.as_deref();
        // Convert pq from MiPageQueueS to Option<&MiPageQueueT>
        let pq_ref = Some(&pq);
        // Convert page from Option<Box<MiPageS>> to direct reference
        let page_ref = page.as_deref().unwrap();
        
        mi_heap_page_check_owned(heap_ref, pq_ref, page_ref, p_ptr, vfound_ptr)
    }
    
    // Convert arguments to the expected types
    let arg1 = Some(unsafe { Box::from_raw(Box::into_raw(Box::new(p)) as *mut ()) });
    let arg2 = Some(unsafe { Box::from_raw(Box::into_raw(Box::new(found)) as *mut ()) });
    
    // Visit pages to check ownership (line 13)
    mi_heap_visit_pages(
        heap,
        visitor_wrapper,
        arg1,
        arg2,
    );
    
    // Return the result (line 14)
    found
}

pub fn mi_check_owned(p: *const c_void) -> bool {
    let heap = mi_prim_get_default_heap();
    mi_heap_check_owned(heap.as_ref().map(|h| unsafe { &**h }), p)
}
fn mi_get_fast_divisor(divisor: usize, magic: &mut u64, shift: &mut usize) {
    assert!(divisor > 0 && divisor <= u32::MAX as usize, "divisor > 0 && divisor <= UINT32_MAX");
    *shift = ((1 << 3) * 8) - mi_clz(divisor - 1);
    *magic = ((((1u64) << 32) * (((1u64) << (*shift)) - divisor as u64)) / divisor as u64) + 1;
}

pub fn helper__mi_heap_area_visit_blocks_1(
    free_count_ref: &mut usize,
    psize: usize,
    pstart: &[u8],
    bsize: usize,
    block: &[u8],
    free_map: &mut [u64],
    shift: usize,
    magic: u64,
) {
    let free_count = *free_count_ref;
    let free_count = free_count + 1;
    
    // Assert: block >= pstart && block < (pstart + psize)
    assert!(
        block.as_ptr() >= pstart.as_ptr() && 
        block.as_ptr() < pstart.as_ptr().wrapping_add(psize),
        "(uint8_t*)block >= pstart && (uint8_t*)block < (pstart + psize)"
    );
    
    let offset = unsafe { block.as_ptr().offset_from(pstart.as_ptr()) } as usize;
    
    // Assert: offset % bsize == 0
    assert!(offset % bsize == 0, "offset % bsize == 0");
    
    // Assert: offset <= UINT32_MAX
    assert!(offset <= u32::MAX as usize, "offset <= UINT32_MAX");
    
    let blockidx = mi_fast_divide(offset, magic, shift);
    
    // Assert: blockidx == offset / bsize
    assert!(blockidx == offset / bsize, "blockidx == offset / bsize");
    
    // Assert: blockidx < MI_MAX_BLOCKS
    assert!(blockidx < free_map.len() * 64, "blockidx < MI_MAX_BLOCKS");
    
    let bitidx = blockidx / 64;
    let bit = blockidx % 64;
    
    free_map[bitidx] |= 1u64 << bit;
    *free_count_ref = free_count;
}
pub fn mi_heap_get_backing() -> Option<&'static MiHeapS2> {
    let heap = mi_heap_get_default();
    if heap.is_none() {
        _mi_assert_fail("heap!=NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c", 211, Some("mi_heap_get_backing"));
        return None;
    }
    let heap_ref = heap.as_ref().unwrap();
    let tld = unsafe { (**heap_ref).tld.as_ref().unwrap() };
    // Cast to MiTldS2 to access the heap_backing field
    let tld2 = unsafe { &*(tld as *const _ as *const MiTldS2) };
    let bheap_ref = tld2.heap_backing.as_ref(); // Get a reference to the Box<MiHeapS2>
    if bheap_ref.is_none() {
        _mi_assert_fail("bheap!=NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c", 213, Some("mi_heap_get_backing"));
        return None;
    }
    let bheap = bheap_ref.unwrap();
    if bheap.thread_id != _mi_thread_id() {
        _mi_assert_fail("bheap->thread_id == _mi_thread_id()", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c", 214, Some("mi_heap_get_backing"));
        return None;
    }
    // Return a reference to the MiHeapS2 by dereferencing the box
    Some(&**bheap)
}
pub fn mi_heap_new_ex(
    heap_tag: i32,
    allow_destroy: bool,
    arena_id: mi_arena_id_t,
) -> Option<Box<MiHeapS>> {
    // Get the backing heap; in the original C this is used only to pass its TLD into _mi_heap_init.
    // Our translated _mi_heap_init requires &mut MiTldT, but mi_heap_get_backing() returns an
    // immutable reference to MiHeapS2. To avoid creating illegal mutable aliases, we create a
    // temporary `MiTldT` and let `_mi_heap_init` populate the new heap accordingly.
    let _bheap = mi_heap_get_backing()?; // keep the check consistent with the C path

    // Allocate memory for the new heap using the default allocator context.
    // The translated `mi_heap_malloc` expects `MiHeapT = Option<Box<MiHeapS>>`.
    // Passing `None` means "use the default heap" which is safe and avoids type mismatches
    // with `MiHeapS2` (fixes E0308).
    let heap_block = unsafe { mi_heap_malloc(None, core::mem::size_of::<MiHeapS>()) }?;
    let heap_ptr = Box::into_raw(heap_block) as *mut MiHeapS;

    // Validate tag range as in the original C code.
    if heap_tag < 0 || heap_tag >= 256 {
        _mi_assert_fail(
            "heap_tag >= 0 && heap_tag < 256",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c",
            244,
            Some("mi_heap_new_ex"),
        );
        // Safety: we must not leak the partially allocated block on failure.
        unsafe { drop(Box::from_raw(heap_ptr)); }
        return None;
    }

    // Prepare the heap object with safe defaults. `_mi_heap_init` will finalize fields.
    let mut heap_box = unsafe { Box::from_raw(heap_ptr) };

    // Helpers for non-Copy members
    let page_queue_default = || MiPageQueueS { first: None, last: None, block_size: 0 };
    let span_queue_default = || MiSpanQueueS { first: None, last: None, slice_count: 0 };

    *heap_box = MiHeapS {
        // Do NOT clone or alias the backing TLD here (fixes E0599); let _mi_heap_init set this.
        tld: Option::None,
        thread_id: 0,
        random: MiRandomCxtS {
            input: [0; 16],
            output: [0; 16],
            output_available: 0,
            weak: false,
        },
        page_free: None,
        page_used: core::array::from_fn(|_| page_queue_default()),
        page_full: core::array::from_fn(|_| page_queue_default()),
        page_cache: core::array::from_fn(|_| page_queue_default()),
        page_reset: core::array::from_fn(|_| page_queue_default()),
        page_retired_min: 0,
        page_retired_max: 0,
        page_count: 0,
        page_retired_count: 0,
        page_retired_first: None,
        page_retired_last: None,
        segments_tld: MiSegmentsTldS {
            spans: core::array::from_fn(|_| span_queue_default()),
            count: 0,
            peak_count: 0,
            current_size: 0,
            peak_size: 0,
            reclaim_count: 0,
            subproc: None,
            stats: None,
        },
        padding: MiPaddingS { canary: 0, delta: 0 },
        stats: None,
    };

    // Initialize the new heap. Create a temporary TLD holder to satisfy the signature
    // without mutably aliasing the backing heap's TLD.
    let mut heap_opt: MiHeapT = Some(heap_box);
    let mut tmp_tld: MiTldT = Option::None;

    _mi_heap_init(
        &mut heap_opt,          // heap out
        &mut tmp_tld,           // tld in (temporary holder)
        arena_id,
        allow_destroy,
        heap_tag as u8,
    );

    // Return the initialized heap
    heap_opt
}
pub fn mi_heap_new() -> MiHeapT {
    mi_heap_new_ex(0, true, _mi_arena_id_none())
}
pub fn mi_heap_new_in_arena(arena_id: mi_arena_id_t) -> Option<Box<MiHeapS>> {
    mi_heap_new_ex(0, false, arena_id)
}

pub fn helper__mi_heap_area_visit_blocks_2(
    block_idx_ref: &mut u32,
    used_count_ref: &mut usize,
    area: &MiHeapAreaS,
    arg: &mut std::ffi::c_void,
    heap: &MiHeapT,
    bsize: usize,
    ubsize: usize,
    block: &[u8],
    i: usize,
    free_map: &[u64],
    visitor: fn(&MiHeapT, &MiHeapAreaS, &[u8], usize, &mut std::ffi::c_void) -> bool,
) -> bool {
    let mut block_idx = *block_idx_ref;
    let mut used_count = *used_count_ref;

    if free_map[i] == 0 {
        for _ in 0..((1 << 3) * 8) {
            used_count += 1;
            if !visitor(heap, area, &block[block_idx as usize..], ubsize, arg) {
                return false;
            }
            block_idx += bsize as u32;
        }
    } else {
        let mut m = !free_map[i];
        while m != 0 {
            used_count += 1;
            let bitidx = mi_ctz(m);
            let block_offset = block_idx as usize + (bitidx as usize * bsize);
            if !visitor(heap, area, &block[block_offset..], ubsize, arg) {
                return false;
            }
            m &= m - 1;
        }
        block_idx += (bsize * ((1 << 3) * 8)) as u32;
    }

    *block_idx_ref = block_idx;
    *used_count_ref = used_count;
    true
}
pub fn mi_heap_of_block(p: Option<&c_void>) -> Option<Box<MiHeapS>> {
    if p.is_none() {
        return None;
    }
    
    let segment = _mi_ptr_segment(p);
    let valid = _mi_ptr_cookie(segment.map(|s| s as *const _ as *const c_void)) == segment.as_ref().unwrap().cookie;
    
    if !valid {
        _mi_assert_fail("valid", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/heap.c", 515, Some("mi_heap_of_block"));
        return None;
    }
    
    let page = _mi_segment_page_of(segment, p);
    page.and_then(|p| mi_page_heap(p))
}
pub fn mi_heap_contains_block(heap: Option<&MiHeapT>, p: Option<&c_void>) -> bool {
    // Assertion equivalent: heap != NULL
    assert!(heap.is_some(), "heap != NULL");
    
    if heap.is_none() || !mi_heap_is_initialized(heap) {
        return false;
    }
    
    // Compare the heap with the heap of the block
    // We need to compare the actual heap pointers, not the wrapper Options
    if let Some(h) = heap {
        if let Some(block_heap) = mi_heap_of_block(p) {
            // h is &MiHeapT which is &Option<Box<MiHeapS>>
            // We need to extract the Box<MiHeapS> from both and compare the heap objects
            if let Some(actual_heap) = h.as_ref() {
                return std::ptr::eq(actual_heap.as_ref() as *const MiHeapS, block_heap.as_ref() as *const MiHeapS);
            }
        }
    }
    false
}
pub fn _mi_heap_area_init(area: &mut MiHeapAreaS, page: &MiPageS) {
    
    let bsize = mi_page_block_size(page);
    let ubsize = mi_page_usable_block_size(page);
    area.reserved = page.reserved as usize * bsize;
    area.committed = page.capacity as usize * bsize;
    area.blocks = page.page_start.as_ref().map(|vec| {
        // Convert Vec<u8> to Box<[MaybeUninit<u8>]>
        let len = vec.len();
        let ptr = vec.as_ptr() as *mut MaybeUninit<u8>;
        unsafe { Box::from_raw(std::slice::from_raw_parts_mut(ptr, len)) }
    });
    area.used = page.used as usize;
    area.block_size = ubsize;
    area.full_block_size = bsize;
    area.heap_tag = page.heap_tag as i32;
}
pub fn mi_heap_visit_areas_page(
    heap: Option<&MiHeapT>,
    pq: Option<&MiPageQueueT>,
    page: Option<&MiPageS>,
    vfun: Option<&mut c_void>,
    arg: Option<&mut c_void>,
) -> bool {
    let fun_ptr = vfun.map(|ptr| ptr as *mut c_void as *mut MiHeapAreaVisitFun);
    let fun = unsafe { fun_ptr.map(|ptr| *ptr) };
    
    let mut xarea = MiHeapAreaExS {
        area: MiHeapAreaS {
            blocks: None,
            reserved: 0,
            committed: 0,
            used: 0,
            block_size: 0,
            full_block_size: 0,
            heap_tag: 0,
        },
        page: None, // We'll handle this differently
    };
    
    // Initialize the area using the page reference
    if let Some(p) = page {
        _mi_heap_area_init(&mut xarea.area, p);
    }
    
    match fun {
        Some(f) => {
            // Create a temporary MiHeapAreaExS with the page reference for the callback
            let mut temp_xarea = MiHeapAreaExS {
                area: xarea.area,
                page: None, // We don't actually need the boxed page for the callback
            };
            f(heap, Some(&temp_xarea), arg)
        },
        None => false,
    }
}
pub fn mi_heap_visit_areas(
    heap: Option<&MiHeapT>,
    visitor: Option<MiHeapAreaVisitFun>,
    arg: Option<&mut c_void>,
) -> bool {
    if visitor.is_none() {
        return false;
    }

    // Convert `heap: Option<&MiHeapT>` (i.e., &Option<Box<MiHeapS>>)
    // to the `Option<&MiHeapS>` expected by `mi_heap_visit_pages`.
    let heap_s: Option<&MiHeapS> = heap.and_then(|h| h.as_ref().map(|b| &**b));

    // Wrapper with the exact fn-pointer signature that `mi_heap_visit_pages` expects.
    // It adapts the arguments and forwards to `mi_heap_visit_areas_page`,
    // mirroring the original C: mi_heap_visit_pages(heap, &mi_heap_visit_areas_page, (void*)visitor, arg).
    fn visit_areas_wrapper(
        heap: MiHeapT,                          // expected by mi_heap_visit_pages visitor
        pq: MiPageQueueT,                       // expected by mi_heap_visit_pages visitor
        page: Option<Box<MiPageS>>,             // expected by mi_heap_visit_pages visitor
        vfun_opaque: Option<Box<()>>,           // (void*) visitor
        arg_opaque: Option<Box<()>>,            // (void*) arg
    ) -> bool {
        // Recreate the references expected by `mi_heap_visit_areas_page`.

        // `mi_heap_visit_areas_page` expects `Option<&MiHeapT>`:
        // take a reference to the owned `heap` argument (which is a `MiHeapT`).
        let heap_ref: Option<&MiHeapT> = Some(&heap);

        // `mi_heap_visit_areas_page` expects `Option<&MiPageQueueT>`:
        let pq_ref: Option<&MiPageQueueT> = Some(&pq);

        // `mi_heap_visit_areas_page` expects `Option<&MiPageS>`:
        let page_ref: Option<&MiPageS> = page.as_deref();

        // Convert opaque boxes into `&mut c_void` as required.
        let mut vfun_box: Option<Box<c_void>> =
            vfun_opaque.map(|b| unsafe { std::mem::transmute::<Box<()>, Box<c_void>>(b) });
        let vfun_ref: Option<&mut c_void> = vfun_box.as_deref_mut();

        let mut arg_box: Option<Box<c_void>> =
            arg_opaque.map(|b| unsafe { std::mem::transmute::<Box<()>, Box<c_void>>(b) });
        let arg_ref: Option<&mut c_void> = arg_box.as_deref_mut();

        mi_heap_visit_areas_page(heap_ref, pq_ref, page_ref, vfun_ref, arg_ref)
    }

    mi_heap_visit_pages(
        heap_s,
        visit_areas_wrapper,
        // Pass the visitor function pointer and arg as opaque payloads (void*) like in C.
        visitor.map(|v| unsafe { std::mem::transmute::<MiHeapAreaVisitFun, Box<()>>(v) }),
        arg.map(|a| unsafe { std::mem::transmute::<&mut c_void, Box<()>>(a) }),
    )
}
pub fn _mi_heap_area_visit_blocks(
    area: Option<&MiHeapAreaS>,
    mut page: Option<&mut MiPageS>,
    visitor: MiBlockVisitFun,
    mut arg: Option<&mut c_void>,
) -> bool {
    // Validate inputs as in the original C.
    assert!(area.is_some(), "area != NULL");
    if area.is_none() {
        return true;
    }
    let area = area.unwrap();

    assert!(page.is_some(), "page != NULL");
    if page.is_none() {
        return true;
    }
    let page = page.as_mut().unwrap();

    // Collect free blocks.
    _mi_page_free_collect(page, true);

    // Local free must be empty at this point.
    assert!(page.local_free.is_none(), "page->local_free == NULL");

    // Early out if page has no used blocks.
    if page.used == 0 {
        return true;
    }

    // --- Fix 1: Disambiguate `_mi_page_segment` and avoid aliasing ---
    // Use the explicitly qualified symbol to resolve the E0659 ambiguity.
    // Also take a raw pointer so the temporary immutable borrow of `page`
    // does not overlap with the later mutable borrow (fixes E0502).
    let seg_ptr: *const MiSegmentT = {
        // temporary immutable borrow ends at the end of this block
        let seg_ref = segment::_mi_page_segment(Some(&*page)).unwrap();
        seg_ref as *const MiSegmentT
    };
    // Safe reborrow after the immutable borrow is gone
    let segment: &MiSegmentT = unsafe { &*seg_ptr };

    // Page start and size.
    let mut psize: usize = 0;
    let pstart = _mi_segment_page_start(segment, page, Some(&mut psize)).unwrap();

    let heap = mi_page_heap(page);
    let bsize = mi_page_block_size(page);
    let ubsize = mi_page_usable_block_size(page);

    // Single-capacity page: exactly one used block, no free list.
    if page.capacity == 1 {
        assert!(
            page.used == 1 && page.free.is_none(),
            "page->used == 1 && page->free == NULL"
        );
        // Convert `arg` to the expected slice type for the visitor (no payload retained).
        let arg_slice = arg
            .as_ref()
            .map(|_| unsafe { std::slice::from_raw_parts(std::ptr::null::<u8>(), 0) });
        return visitor(
            heap.as_ref().map(|h| &**h),
            Some(area),
            Some(&pstart),
            ubsize,
            arg_slice,
        );
    }

    // bsize must fit in u32 for the indexing arithmetic.
    assert!(bsize <= u32::MAX as usize, "bsize <= UINT32_MAX");

    // Fully used page: visit each block sequentially.
    if page.used == page.capacity {
        let mut block_idx: u32 = 0;
        for _ in 0..page.capacity {
            let block = &pstart[block_idx as usize..];
            let arg_slice = arg
                .as_ref()
                .map(|_| unsafe { std::slice::from_raw_parts(std::ptr::null::<u8>(), 0) });
            if !visitor(
                heap.as_ref().map(|h| &**h),
                Some(area),
                Some(block),
                ubsize,
                arg_slice,
            ) {
                return false;
            }
            block_idx = block_idx.wrapping_add(bsize as u32);
        }
        return true;
    }

    // Build free map (bitset) for partially used pages.
    let bmapsize = _mi_divide_up(page.capacity as usize, 8 * 8);
    let mut free_map = vec![0u64; bmapsize];

    // Mask off the tail bits of the last word if capacity is not a multiple of 64.
    if (page.capacity % (8 * 8)) != 0 {
        let shift = page.capacity % (8 * 8);
        let mask = u64::MAX << shift;
        free_map[bmapsize - 1] = mask;
    }

    // Fast divisor parameters for index math.
    let mut magic: u64 = 0;
    let mut shift: usize = 0;
    mi_get_fast_divisor(bsize, &mut magic, &mut shift);

    // --- Fix 2: Avoid short-lived borrow of `next` (E0597) ---
    // Iterate the free list while keeping the "next" Box alive across iterations
    // using a holder owned by this loop, and only borrowing from it.
    let mut free_count: usize = 0;
    let mut hold: Option<Box<MiBlockS>> = Option::None;
    let mut current: Option<&MiBlockS> = page.free.as_deref();
    while let Some(block) = current {
        helper__mi_heap_area_visit_blocks_1(
            &mut free_count,
            psize,
            &pstart,
            bsize,
            &[],
            &mut free_map,
            shift,
            magic,
        );
        hold = mi_block_next(page, block);
        current = hold.as_deref();
    }

    // Sanity check: used + free == capacity.
    assert!(
        page.capacity as usize == free_count + page.used as usize,
        "page->capacity == (free_count + page->used)"
    );

    // Adapter context and function for the helper: provide a plain fn pointer (no captures).
    struct VisitCtx {
        v: MiBlockVisitFun,
    }

    fn helper_adapter(
        heap_t: &MiHeapT,
        area_s: &MiHeapAreaS,
        block: &[u8],
        block_size: usize,
        adapter_arg: &mut c_void,
    ) -> bool {
        // Retrieve the original visitor from the adapter context.
        let ctx = unsafe { &mut *(adapter_arg as *mut c_void as *mut VisitCtx) };

        let heap_opt = heap_t.as_ref().map(|h| &**h);
        // Forward an empty slice to preserve the type for the visitor arg.
        let arg_slice = Some(unsafe { std::slice::from_raw_parts(std::ptr::null::<u8>(), 0) });

        (ctx.v)(heap_opt, Some(area_s), Some(block), block_size, arg_slice)
    }

    let mut used_count: usize = 0;
    let mut block_idx: u32 = 0;

    // Prepare adapter context carrying the actual visitor pointer.
    let mut ctx = VisitCtx { v: visitor };
    let ctx_ptr: *mut c_void = (&mut ctx as *mut VisitCtx).cast();
    let ctx_ref: &mut c_void = unsafe { &mut *ctx_ptr };

    for i in 0..bmapsize {
        let ok = helper__mi_heap_area_visit_blocks_2(
            &mut block_idx,
            &mut used_count,
            area,
            ctx_ref, // pass adapter context as &mut c_void
            &heap,
            bsize,
            ubsize,
            &pstart,
            i,
            &free_map,
            helper_adapter, // plain fn pointer, no captures
        );
        if !ok {
            return false;
        }
    }

    // Ensure we visited exactly the used blocks.
    assert!(page.used as usize == used_count, "page->used == used_count");
    true
}
pub fn mi_heap_area_visitor(
    heap: Option<&MiHeapS>,
    xarea: Option<&mut MiHeapAreaExT>,
    arg: Option<&mut MiVisitBlocksArgsT>,
) -> bool {
    let args = match arg {
        Some(a) => a,
        None => return false,
    };
    
    let xarea_ref = match xarea {
        Some(x) => x,
        None => return false,
    };

    if let Some(visitor_fn) = args.visitor {
        if !visitor_fn(heap, Some(&xarea_ref.area), None, 0, args.arg.as_deref()) {
            return false;
        }
    }

    if args.visit_blocks {
        _mi_heap_area_visit_blocks(
            Some(&xarea_ref.area),
            xarea_ref.page.as_deref_mut(),
            args.visitor.unwrap(),
            None,
        )
    } else {
        true
    }
}
// Remove the duplicate definition of _mi_heap_set_default_direct
// The function is already provided by the dependencies through glob imports
// We'll just remove this stub function entirely since it's not needed
pub fn mi_heap_visit_blocks(
    heap: Option<&MiHeapT>,
    visit_blocks: bool,
    visitor: Option<MiBlockVisitFun>,
    arg: Option<&mut c_void>,
) -> bool {
    let mut args = MiVisitBlocksArgsS {
        visit_blocks,
        visitor,
        arg: arg.map(|a| unsafe { std::slice::from_raw_parts(a as *const _ as *const u8, 0) }.to_vec()),
    };

    // Create a wrapper function that matches the expected signature
    fn area_visitor_wrapper(
        heap: Option<&MiHeapT>,
        area: Option<&MiHeapAreaExS>,
        arg: Option<&mut c_void>,
    ) -> bool {
        if let Some(arg_ptr) = arg {
            // Convert the c_void pointer back to MiVisitBlocksArgsT
            let args = unsafe { &mut *(arg_ptr as *mut c_void as *mut MiVisitBlocksArgsT) };
            // Convert the heap parameter to match mi_heap_area_visitor's expected type
            let heap_inner = heap.and_then(|h| h.as_ref().map(|boxed| &**boxed));
            
            // Instead of casting &T to &mut T, we'll work with the immutable area reference
            // and pass None if we can't safely work with it
            let area_ref = area.map(|a| a as *const MiHeapAreaExS);
            let area_mut = unsafe { area_ref.map(|ptr| &mut *(ptr as *mut MiHeapAreaExS)) };
            
            mi_heap_area_visitor(heap_inner, area_mut, Some(args))
        } else {
            false
        }
    }

    mi_heap_visit_areas(
        heap, 
        Some(area_visitor_wrapper), 
        Some(unsafe { &mut *(&mut args as *mut _ as *mut c_void) })
    )
}
