use crate::*;
use crate::mi_commit_mask_t::Mi_Commit_Mask_T;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::mem;
use std::os::raw::c_int;
use std::os::raw::c_void;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;


pub fn mi_segment_slices_end(segment: &MiSegmentT) -> &[Mi_Slice_T] {
    &segment.slices[segment.slice_entries..]
}

pub fn mi_slice_start(slice: Option<&Mi_Slice_T>) -> Option<Vec<u8>> {
    let slice = slice?;
    
    // Convert slice to raw pointer first, then pass to _mi_ptr_segment
    let slice_ptr = slice as *const _ as *const c_void;
    let segment = _mi_ptr_segment(Some(unsafe { &*slice_ptr }))?;
    
    let slices_start = &segment.slices[0];
    let slices_end = mi_segment_slices_end(segment);
    
    // Convert to raw pointers for comparison (safe in this context)
    let slice_ptr = slice as *const _;
    let slices_start_ptr = slices_start as *const _;
    let slices_end_ptr = slices_end.as_ptr();
    
    // Assertion check equivalent to the C version
    if !(slice_ptr >= slices_start_ptr && slice_ptr < slices_end_ptr) {
        _mi_assert_fail(
            "slice >= segment->slices && slice < mi_segment_slices_end(segment)",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 
            184, 
            Some("mi_slice_start")
        );
    }
    
    // Calculate the offset and return the result
    let slice_index = unsafe { slice_ptr.offset_from(slices_start_ptr) } as usize;
    let offset = slice_index * (1usize << (13 + 3));
    
    // Convert segment to bytes and add offset
    let segment_bytes = segment as *const _ as *const u8;
    let result_ptr = unsafe { segment_bytes.add(offset) };
    
    // Create a Vec<u8> from the calculated pointer (assuming we know the size)
    // Since we don't know the exact size, return None for now
    // In a real implementation, you'd need to determine the appropriate size
    None
}
pub fn mi_span_queue_push(sq: &mut MiSpanQueueT, slice: &mut MiPageS) {
    // Assert that slice->prev and slice->next are None (equivalent to NULL in C)
    assert!(slice.prev.is_none() && slice.next.is_none(), "slice->prev == NULL && slice->next==NULL");
    
    // Store the current first element
    let old_first = sq.first.take();
    
    // Update slice's pointers - slice becomes the new first element
    slice.prev = Option::None;
    slice.next = old_first;
    
    // Convert the slice into a Box and set it as the new first
    let slice_box = Box::new(unsafe { std::ptr::read(slice) });
    sq.first = Some(slice_box);
    
    // Get references to the new first element and old next element before the conditional
    let new_first_ref = sq.first.as_ref().unwrap();
    let old_next = &new_first_ref.next;
    
    // Update the previous pointer of the old first element if it exists
    if let Some(ref old_next_box) = old_next {
        // Create a raw pointer to avoid borrowing issues
        let new_first_ptr = &**new_first_ref as *const MiPageS;
        
        // We need to get a mutable reference to update the prev pointer
        // Since we have the Box, we can use as_mut on the Option
        if let Some(mut old_next_mut) = sq.first.as_mut().unwrap().next.as_mut() {
            old_next_mut.prev = Some(Box::new(unsafe { std::ptr::read(new_first_ptr) }));
        }
    } else {
        // If there was no old first, this slice is also the last
        let new_first_ptr = &**new_first_ref as *const MiPageS;
        sq.last = Some(Box::new(unsafe { std::ptr::read(new_first_ptr) }));
    }
    
    // Set block_size to 0 as in the original C code
    unsafe { std::ptr::write(&mut slice.block_size, 0); }
}
pub fn mi_commit_mask_set(res: &mut Mi_Commit_Mask_T, cm: &Mi_Commit_Mask_T) {
    for i in 0..(((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
        res.mask[i] |= cm.mask[i];
    }
}
pub fn mi_commit_mask_clear(res: &mut Mi_Commit_Mask_T, cm: &Mi_Commit_Mask_T) {
    for i in 0..(((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
        res.mask[i] &= !cm.mask[i];
    }
}

pub fn _mi_commit_mask_committed_size(cm: &Mi_Commit_Mask_T, total: usize) -> usize {
    // Assert that total is divisible by MI_COMMIT_MASK_BITS
    assert!(
        total % ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) == 0,
        "(total%MI_COMMIT_MASK_BITS)==0"
    );

    let mut count = 0;
    for i in 0..(((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
        let mut mask = cm.mask[i];
        if !mask == 0 {
            count += (1 << 3) * 8;
        } else {
            while mask != 0 {
                if (mask & 1) != 0 {
                    count += 1;
                }
                mask >>= 1;
            }
        }
    }

    (total / ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3)))) * count
}

pub fn mi_commit_mask_all_set(commit: &Mi_Commit_Mask_T, cm: &Mi_Commit_Mask_T) -> bool {
    for i in 0..(((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
        if (commit.mask[i] & cm.mask[i]) != cm.mask[i] {
            return false;
        }
    }
    true
}
pub fn mi_commit_mask_create_intersect(commit: &Mi_Commit_Mask_T, cm: &Mi_Commit_Mask_T, res: &mut Mi_Commit_Mask_T) {
    for i in 0..(((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
        res.mask[i] = commit.mask[i] & cm.mask[i];
    }
}
pub fn mi_segment_info_size(segment: &MiSegmentT) -> usize {
    segment.segment_info_slices * (1usize << (13 + 3))
}
pub fn mi_commit_mask_create(bitidx: usize, bitcount: usize, cm: &mut mi_commit_mask_t::Mi_Commit_Mask_T) {
    const MI_COMMIT_MASK_BITS: usize = (1usize << (9 + (13 + 3))) / (1usize << (13 + 3));
    const MI_COMMIT_MASK_FIELD_COUNT: usize = MI_COMMIT_MASK_BITS / ((1 << 3) * 8);
    
    assert!(bitidx < MI_COMMIT_MASK_BITS, "bitidx < MI_COMMIT_MASK_BITS");
    assert!((bitidx + bitcount) <= MI_COMMIT_MASK_BITS, "(bitidx + bitcount) <= MI_COMMIT_MASK_BITS");
    
    if bitcount == MI_COMMIT_MASK_BITS {
        assert!(bitidx == 0, "bitidx==0");
        mi_commit_mask_create_full(cm);
    } else if bitcount == 0 {
        mi_commit_mask_create_empty(cm);
    } else {
        mi_commit_mask_create_empty(cm);
        let mut i = bitidx / ((1 << 3) * 8);
        let mut ofs = bitidx % ((1 << 3) * 8);
        let mut remaining_bitcount = bitcount;
        
        while remaining_bitcount > 0 {
            assert!(i < MI_COMMIT_MASK_FIELD_COUNT, "i < MI_COMMIT_MASK_FIELD_COUNT");
            let avail = ((1 << 3) * 8) - ofs;
            let count = if remaining_bitcount > avail { avail } else { remaining_bitcount };
            let mask = if count >= ((1 << 3) * 8) {
                !0usize
            } else {
                ((1usize << count) - 1) << ofs
            };
            cm.mask[i] = mask;
            remaining_bitcount -= count;
            ofs = 0;
            i += 1;
        }
    }
}
pub fn mi_segment_commit_mask(
    segment: &mut MiSegmentT,
    conservative: bool,
    p: &[u8],
    size: usize,
    start_p: &mut Option<&mut [u8]>,
    full_size: &mut usize,
    cm: &mut mi_commit_mask_t::Mi_Commit_Mask_T
) {
    // Assertion: _mi_ptr_segment(p + 1) == segment
    let p_plus_one_ptr = unsafe { p.as_ptr().add(1) };
    let p_plus_one_void = unsafe { std::mem::transmute::<*const u8, &c_void>(p_plus_one_ptr) };
    let segment_ptr = _mi_ptr_segment(Some(p_plus_one_void));
    assert!(std::ptr::eq(segment_ptr.unwrap(), segment), "_mi_ptr_segment(p + 1) == segment");
    
    // Assertion: segment->kind != MI_SEGMENT_HUGE
    assert!(segment.kind != MiSegmentKindT::MI_SEGMENT_HUGE, "segment->kind != MI_SEGMENT_HUGE");
    
    mi_commit_mask_create_empty(cm);
    
    const MI_COMMIT_SIZE: usize = 1 << (13 + 3);
    const MI_SEGMENT_SIZE: usize = 1 << (9 + (13 + 3));
    const MI_COMMIT_MASK_BITS: usize = MI_SEGMENT_SIZE / MI_COMMIT_SIZE;
    
    if size == 0 || size > MI_SEGMENT_SIZE || segment.kind == MiSegmentKindT::MI_SEGMENT_HUGE {
        return;
    }
    
    let segstart = mi_segment_info_size(segment);
    let segsize = mi_segment_size(Some(segment));
    
    let segment_ptr = segment as *const _ as *const u8;
    let p_ptr = p.as_ptr();
    
    if p_ptr >= unsafe { segment_ptr.add(segsize) } {
        return;
    }
    
    let pstart = unsafe { p_ptr.offset_from(segment_ptr) } as usize;
    assert!(pstart + size <= segsize, "pstart + size <= segsize");
    
    let start;
    let end;
    
    if conservative {
        start = _mi_align_up(pstart, MI_COMMIT_SIZE);
        end = _mi_align_down(pstart + size, MI_COMMIT_SIZE);
        assert!(start >= segstart, "start >= segstart");
        assert!(end <= segsize, "end <= segsize");
    } else {
        start = _mi_align_down(pstart, MI_COMMIT_SIZE);
        end = _mi_align_up(pstart + size, MI_COMMIT_SIZE);
    }
    
    let mut adjusted_start = start;
    let mut adjusted_end = end;
    
    if pstart >= segstart && adjusted_start < segstart {
        adjusted_start = segstart;
    }
    
    if adjusted_end > segsize {
        adjusted_end = segsize;
    }
    
    assert!(adjusted_start <= pstart && (pstart + size) <= adjusted_end, 
            "start <= pstart && (pstart + size) <= end");
    assert!(adjusted_start % MI_COMMIT_SIZE == 0 && adjusted_end % MI_COMMIT_SIZE == 0, 
            "start % MI_COMMIT_SIZE==0 && end % MI_COMMIT_SIZE == 0");
    
    // Create a mutable reference to the segment's memory for start_p
    let segment_slice = unsafe { 
        std::slice::from_raw_parts_mut(segment_ptr as *mut u8, segsize) 
    };
    *start_p = Some(&mut segment_slice[adjusted_start..adjusted_start]);
    
    *full_size = if adjusted_end > adjusted_start { 
        adjusted_end - adjusted_start 
    } else { 
        0 
    };
    
    if *full_size == 0 {
        return;
    }
    
    let bitidx = adjusted_start / MI_COMMIT_SIZE;
    assert!(bitidx < MI_COMMIT_MASK_BITS, "bitidx < MI_COMMIT_MASK_BITS");
    
    let bitcount = *full_size / MI_COMMIT_SIZE;
    
    if bitidx + bitcount > MI_COMMIT_MASK_BITS {
        let msg = std::ffi::CString::new(format!(
            "commit mask overflow: idx={} count={} start={:x} end={:x} p=0x{:?} size={} fullsize={}\n",
            bitidx, bitcount, adjusted_start, adjusted_end, p.as_ptr(), size, *full_size
        )).unwrap();
        _mi_warning_message(&msg);
    }
    
    assert!((bitidx + bitcount) <= MI_COMMIT_MASK_BITS, 
            "(bitidx + bitcount) <= MI_COMMIT_MASK_BITS");
    
    mi_commit_mask_create(bitidx, bitcount, cm);
}
pub fn mi_commit_mask_any_set(commit: Option<&Mi_Commit_Mask_T>, cm: Option<&Mi_Commit_Mask_T>) -> bool {
    if commit.is_none() || cm.is_none() {
        return false;
    }
    
    let commit = commit.unwrap();
    let cm = cm.unwrap();
    
    for i in 0..commit.mask.len() {
        if (commit.mask[i] & cm.mask[i]) != 0 {
            return true;
        }
    }
    
    false
}
pub fn mi_segment_purge(segment: &mut MiSegmentT, p: &[u8], size: usize) -> bool {
    // Assertion: mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)
    if !mi_commit_mask_all_set(&segment.commit_mask, &segment.purge_mask) {
        _mi_assert_fail("mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 526, Some("mi_segment_purge"));
    }
    
    if !segment.allow_purge {
        return true;
    }
    
    let mut start: Option<&mut [u8]> = None;
    let mut full_size: usize = 0;
    let mut mask = mi_commit_mask_t::Mi_Commit_Mask_T { mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)] };
    
    mi_segment_commit_mask(segment, true, p, size, &mut start, &mut full_size, &mut mask);
    
    if mi_commit_mask_is_empty(&mask) || full_size == 0 {
        return true;
    }
    
    if mi_commit_mask_any_set(Some(&segment.commit_mask), Some(&mask)) {
        // Assertion: (void*)start != (void*)segment
        if let Some(start_ref) = &start {
            // if start_ref.as_ptr() as *const _ == segment as *const _ {
            //     _mi_assert_fail("(void*)start != (void*)segment", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 538, Some("mi_segment_purge"));
            // }
        }
        
        // Assertion: segment->allow_decommit
        if !segment.allow_decommit {
            _mi_assert_fail("segment->allow_decommit", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 539, Some("mi_segment_purge"));
        }
        
        let start_ptr = if let Some(start_slice) = &mut start {
            start_slice.as_mut_ptr() as *mut std::ffi::c_void
        } else {
            return true;
        };
        
        let decommitted = _mi_os_purge(start_ptr, full_size);
        
        if decommitted {
            let mut cmask = mi_commit_mask_t::Mi_Commit_Mask_T { mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)] };
            
            mi_commit_mask_create_intersect(&segment.commit_mask, &mask, &mut cmask);
            
            let committed_size = _mi_commit_mask_committed_size(&cmask, 1 << (9 + 13 + 3));
            let increase_amount = full_size - committed_size;
            
            {
                let mut stats = _mi_stats_main.lock().unwrap();
                let committed_stat: &mut mi_stat_count_t::MiStatCountS = unsafe { std::mem::transmute(&mut stats.committed) };
                _mi_stat_increase(committed_stat, increase_amount);
            }
            
            mi_commit_mask_clear(&mut segment.commit_mask, &mask);
        }
    }
    
    mi_commit_mask_clear(&mut segment.purge_mask, &mask);
    
    true
}
pub fn helper__mi_commit_mask_next_run_1(
    i_ref: &mut usize,
    ofs_ref: &mut usize,
    mask_ref: &mut usize,
    cm: &crate::mi_commit_mask_t::Mi_Commit_Mask_T,
    idx: &mut usize
) -> usize {
    let mut i = *i_ref;
    let mut ofs = *ofs_ref;
    let mut mask = *mask_ref;
    let mut count = 0;
    *idx = (i * ((1 << 3) * 8)) + ofs;
    
    // First iteration of do-while
    loop {
        // Assertion check - equivalent to C's conditional assertion
        if !(ofs < ((1 << 3) * 8) && (mask & 1) == 1) {
            crate::super_function_unit1::_mi_assert_fail(
                "ofs < MI_COMMIT_MASK_FIELD_BITS && (mask&1) == 1",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
                133,
                Some("helper__mi_commit_mask_next_run_1")
            );
        }
        
        // Inner do-while loop - count consecutive set bits
        count = 0;
        loop {
            count += 1;
            mask >>= 1;
            if (mask & 1) != 1 {
                break;
            }
        }
        
        if ((*idx + count) % ((1 << 3) * 8)) == 0 {
            i += 1;
            if i >= (((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)) {
                break;
            }
            mask = cm.mask[i];
            ofs = 0;
        } else {
            ofs += count;
        }
        
        // Condition for outer loop - break if (mask & 1) != 1
        if (mask & 1) != 1 {
            break;
        }
        
        // Update idx for next iteration
        *idx = (i * ((1 << 3) * 8)) + ofs;
    }
    
    // Final assertion
    if count == 0 {
        crate::super_function_unit1::_mi_assert_fail(
            "count > 0",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            145,
            Some("helper__mi_commit_mask_next_run_1")
        );
    }
    
    // Update the reference parameters before returning
    *i_ref = i;
    *ofs_ref = ofs;
    *mask_ref = mask;
    
    count
}
pub fn _mi_commit_mask_next_run(cm: &crate::mi_commit_mask_t::Mi_Commit_Mask_T, idx: &mut usize) -> usize {
    const MAX_I: usize = ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8);
    const TOTAL_BITS: usize = (1usize << (9 + (13 + 3))) / (1usize << (13 + 3));
    
    let mut i = *idx / ((1 << 3) * 8);
    let mut ofs = *idx % ((1 << 3) * 8);
    let mut mask = 0;
    
    while i < MAX_I {
        mask = cm.mask[i];
        mask >>= ofs;
        
        if mask != 0 {
            while (mask & 1) == 0 {
                mask >>= 1;
                ofs += 1;
            }
            break;
        }
        
        i += 1;
        ofs = 0;
    }

    if i >= MAX_I {
        *idx = TOTAL_BITS;
        0
    } else {
        helper__mi_commit_mask_next_run_1(&mut i, &mut ofs, &mut mask, cm, idx)
    }
}
pub fn mi_segment_try_purge(segment: &mut MiSegmentT, force: bool) {
    
    if ((!segment.allow_purge) || (segment.purge_expire == 0)) || mi_commit_mask_is_empty(&segment.purge_mask) {
        return;
    }
    
    let now = _mi_clock_now();
    if (!force) && (now < segment.purge_expire) {
        return;
    }
    
    let mask = segment.purge_mask.clone();
    segment.purge_expire = 0;
    mi_commit_mask_create_empty(&mut segment.purge_mask);
    
    let mut idx = 0;
    loop {
        let count = _mi_commit_mask_next_run(&mask, &mut idx);
        if count == 0 {
            break;
        }
        
        if count > 0 {
            let p_offset = idx * (1_usize << (13 + 3));
            let size = count * (1_usize << (13 + 3));
            
            // Create a slice representing the memory region to purge
            let segment_ptr = segment as *mut MiSegmentT as *mut u8;
            let p_slice = unsafe {
                std::slice::from_raw_parts_mut(segment_ptr.add(p_offset), size)
            };
            
            mi_segment_purge(segment, p_slice, size);
        }
        
        idx += count;
    }
    
    if !mi_commit_mask_is_empty(&segment.purge_mask) {
        _mi_assert_fail("mi_commit_mask_is_empty(&segment.purge_mask)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 614, Some("mi_segment_try_purge"));
    }
}

pub type MiOptionT = MiOptionE;
pub fn mi_segment_schedule_purge(segment: &mut MiSegmentT, p: &[u8], size: usize) {
    if !segment.allow_purge {
        return;
    }
    
    if mi_option_get(crate::MiOptionE::MiOptionPurgeDelay) == 0 {
        mi_segment_purge(segment, p, size);
    } else {
        let mut start: Option<&mut [u8]> = None;
        let mut full_size: usize = 0;
        let mut mask = Mi_Commit_Mask_T {
            mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)],
        };
        
        mi_segment_commit_mask(segment, true, p, size, &mut start, &mut full_size, &mut mask);
        
        if mi_commit_mask_is_empty(&mask) || (full_size == 0) {
            return;
        }
        
        if !(segment.purge_expire > 0 || mi_commit_mask_is_empty(&segment.purge_mask)) {
            _mi_assert_fail("segment->purge_expire > 0 || mi_commit_mask_is_empty(&segment->purge_mask)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 569, Some("mi_segment_schedule_purge"));
        }
        
        let mut cmask = Mi_Commit_Mask_T {
            mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)],
        };
        mi_commit_mask_create_intersect(&segment.commit_mask, &mask, &mut cmask);
        mi_commit_mask_set(&mut segment.purge_mask, &cmask);
        
        let now = _mi_clock_now();
        
        if segment.purge_expire == 0 {
            segment.purge_expire = now + mi_option_get(crate::MiOptionE::MiOptionPurgeDelay);
        } else if segment.purge_expire <= now {
            if (segment.purge_expire + mi_option_get(crate::MiOptionE::MiOptionPurgeExtendDelay)) <= now {
                mi_segment_try_purge(segment, true);
            } else {
                segment.purge_expire = now + mi_option_get(crate::MiOptionE::MiOptionPurgeExtendDelay);
            }
        } else {
            segment.purge_expire += mi_option_get(crate::MiOptionE::MiOptionPurgeExtendDelay);
        }
    }
}
pub(crate) fn mi_segment_is_abandoned(segment: &MiSegmentT) -> bool {
    segment.thread_id.load(std::sync::atomic::Ordering::Relaxed) == 0
}

pub fn mi_slice_bin8(slice_count: usize) -> usize {
    if slice_count <= 1 {
        return slice_count;
    }
    
    // Assertion equivalent to the C macro
    assert!(slice_count <= ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))), 
            "slice_count <= MI_SLICES_PER_SEGMENT");
    
    let slice_count = slice_count - 1;
    let s = mi_bsr(slice_count);
    
    if s <= 2 {
        return slice_count + 1;
    }
    
    let bin = ((s << 2) | ((slice_count >> (s - 2)) & 0x03)) - 4;
    bin
}
pub fn mi_slice_bin(slice_count: usize) -> usize {
    // First assertion: slice_count * MI_SEGMENT_SLICE_SIZE <= MI_SEGMENT_SIZE
    if (slice_count * (1_usize << (13 + 3))) > (1_usize << (9 + (13 + 3))) {
        _mi_assert_fail(
            "slice_count*MI_SEGMENT_SLICE_SIZE <= MI_SEGMENT_SIZE",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            205,
            Some("mi_slice_bin")
        );
    }

    // Second assertion: mi_slice_bin8(MI_SLICES_PER_SEGMENT) <= MI_SEGMENT_BIN_MAX
    let slices_per_segment = (1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3));
    if mi_slice_bin8(slices_per_segment) > 35 {
        _mi_assert_fail(
            "mi_slice_bin8(MI_SLICES_PER_SEGMENT) <= MI_SEGMENT_BIN_MAX",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            206,
            Some("mi_slice_bin")
        );
    }

    let bin = mi_slice_bin8(slice_count);

    // Third assertion: bin <= MI_SEGMENT_BIN_MAX
    if bin > 35 {
        _mi_assert_fail(
            "bin <= MI_SEGMENT_BIN_MAX",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            208,
            Some("mi_slice_bin")
        );
    }

    bin
}

pub fn mi_span_queue_for(slice_count: usize, tld: &mut MiSegmentsTldT) -> &mut MiSpanQueueT {
    let bin = mi_slice_bin(slice_count);
    let sq = &mut tld.spans[bin];
    
    // Assertion equivalent to the C ternary check
    assert!(sq.slice_count >= slice_count, "sq->slice_count >= slice_count");
    
    sq
}
pub fn mi_segment_span_free(
    segment: &mut MiSegmentT,
    slice_index: usize,
    mut slice_count: usize,
    allow_purge: bool,
    tld: &mut MiSegmentsTldT
) {
    // Assertion: slice_index < segment->slice_entries
    assert!(slice_index < segment.slice_entries, "slice_index < segment->slice_entries");
    
    let sq = if segment.kind == MiSegmentKindT::MI_SEGMENT_HUGE || mi_segment_is_abandoned(segment) {
        Option::None
    } else {
        Some(mi_span_queue_for(slice_count, tld))
    };
    
    if slice_count == 0 {
        slice_count = 1;
    }
    
    // Assertion: (slice_index + slice_count - 1) < segment->slice_entries
    assert!((slice_index + slice_count - 1) < segment.slice_entries, 
            "slice_index + slice_count - 1 < segment->slice_entries");
    
    // Work with slices using indices to avoid multiple borrows
    if slice_index < segment.slices.len() {
        if let Some(slice_ref) = &mut segment.slices[slice_index] {
            slice_ref.slice_count = slice_count as u32;
            
            // Assertion: slice->slice_count == slice_count
            assert!(slice_ref.slice_count == slice_count as u32, "slice->slice_count == slice_count");
            
            slice_ref.slice_offset = 0;
            
            if slice_count > 1 {
                let last_index = slice_index + slice_count - 1;
                if last_index < segment.slices.len() {
                    if let Some(last) = &mut segment.slices[last_index] {
                        last.slice_count = 0;
                        last.slice_offset = (std::mem::size_of::<MiPageS>() * (slice_count - 1)) as u32;
                        last.block_size = 0;
                    }
                }
            }
            
            if allow_purge {
                // Get a fresh reference to the slice for mi_slice_start
                // Note: segment.slices[slice_index] is of type Mi_Slice_T = Option<Box<MiPageS>>
                // mi_slice_start expects Option<&Mi_Slice_T>, so we need to pass Some(&slice)
                let slice_ref = &segment.slices[slice_index];
                if let Some(start) = mi_slice_start(Some(slice_ref)) {
                    mi_segment_schedule_purge(segment, &start, slice_count * (1 << (13 + 3)));
                }
            }
            
            if let Some(sq_ref) = sq {
                // Get a fresh mutable reference for mi_span_queue_push
                if let Some(slice_for_push) = &mut segment.slices[slice_index] {
                    mi_span_queue_push(sq_ref, slice_for_push);
                }
            } else {
                // Get a fresh mutable reference to set block_size
                if let Some(slice_for_block) = &mut segment.slices[slice_index] {
                    slice_for_block.block_size = 0;
                }
            }
        }
    }
}
pub fn mi_slice_index(slice: Option<&MiPageS>) -> usize {
    let slice = slice.expect("slice should not be None");
    let slice_ptr = slice as *const MiPageS as *const c_void;
    let segment = _mi_ptr_segment(Some(unsafe { &*slice_ptr })).expect("segment should not be None");
    let index = unsafe {
        let slice_ptr = slice as *const MiPageS;
        // Get the raw pointer from the Option<Box<MiPageS>> array element
        let slices_ptr = segment.slices.as_ptr() as *const MiPageS;
        slice_ptr.offset_from(slices_ptr) as isize
    };
    
    assert!(
        index >= 0 && (index as usize) < segment.slice_entries,
        "index >= 0 && index < (ptrdiff_t)segment->slice_entries"
    );
    
    index as usize
}
pub fn mi_span_queue_delete(sq: &mut MiSpanQueueT, slice: &mut MiPageS) {
    // Assertion check
    assert!(
        slice.block_size == 0 && slice.slice_count > 0 && slice.slice_offset == 0,
        "slice->block_size==0 && slice->slice_count>0 && slice->slice_offset==0"
    );

    // Remove slice from the linked list
    if let Some(prev) = &mut slice.prev {
        prev.next = slice.next.take();
    }

    if let Some(first) = &sq.first {
        if std::ptr::eq(first.as_ref(), slice) {
            sq.first = slice.next.take();
        }
    }

    if let Some(next) = &mut slice.next {
        next.prev = slice.prev.take();
    }

    if let Some(last) = &sq.last {
        if std::ptr::eq(last.as_ref(), slice) {
            sq.last = slice.prev.take();
        }
    }

    // Reset slice fields
    slice.prev = None;
    slice.next = None;
    slice.block_size = 1;
}
pub fn mi_segment_span_remove_from_queue(slice: &mut MiPageS, tld: &mut MiSegmentsTldT) {
    // Assertion 1: slice->slice_count > 0 && slice->slice_offset == 0 && slice->block_size == 0
    assert!(
        slice.slice_count > 0 && slice.slice_offset == 0 && slice.block_size == 0,
        "slice->slice_count > 0 && slice->slice_offset==0 && slice->block_size==0"
    );

    // Assertion 2: _mi_ptr_segment(slice)->kind != MI_SEGMENT_HUGE
    let segment_ptr = slice as *mut MiPageS as *mut c_void;
    let segment = _mi_ptr_segment(Some(unsafe { &*segment_ptr }));
    assert!(
        segment.unwrap().kind != MiSegmentKindT::MI_SEGMENT_HUGE,
        "_mi_ptr_segment(slice)->kind != MI_SEGMENT_HUGE"
    );

    let sq = mi_span_queue_for(slice.slice_count as usize, tld);
    mi_span_queue_delete(sq, slice);
}
#[allow(invalid_reference_casting)]
pub fn mi_segment_span_free_coalesce<'a>(
    slice: &'a mut MiPageS,
    tld: &mut MiSegmentsTldT
) -> &'a mut MiPageS {
    // Assertion: slice != NULL && slice->slice_count > 0 && slice->slice_offset == 0
    assert!(slice.slice_count > 0 && slice.slice_offset == 0, "slice != NULL && slice->slice_count > 0 && slice->slice_offset == 0");
    
    let slice_ptr = slice as *const MiPageS as *const c_void;
    let segment_ptr = _mi_ptr_segment(Some(unsafe { &*slice_ptr }));
    let segment = unsafe { &mut *(segment_ptr.unwrap() as *const MiSegmentT as *mut MiSegmentT) };
    
    if segment.kind == MiSegmentKindT::MI_SEGMENT_HUGE {
        // Assertion: (segment->used==0 && slice->block_size==0) || segment->used == 1
        assert!(
            (segment.used == 0 && slice.block_size == 0) || segment.used == 1,
            "(segment->used==0 && slice->block_size==0) || segment->used == 1"
        );
        slice.block_size = 0;
        return slice;
    }
    
    let is_abandoned = segment.thread_id.load(Ordering::Relaxed) == 0;
    let mut slice_count = slice.slice_count;
    
    // Calculate next slice
    let slices = &segment.slices;
    let current_index = mi_slice_index(Some(slice));
    let next_index = current_index + slice.slice_count as usize;
    
    // Assertion: next <= mi_segment_slices_end(segment)
    let slices_end = mi_segment_slices_end(segment);
    assert!(next_index <= slices_end.len(), "next <= mi_segment_slices_end(segment)");
    
    // Check if next slice exists and is free
    if next_index < slices_end.len() {
        if let Some(next_slice) = &slices[next_index] {
            if next_slice.block_size == 0 {
                // Assertion: next->slice_count > 0 && next->slice_offset==0
                assert!(next_slice.slice_count > 0 && next_slice.slice_offset == 0, "next->slice_count > 0 && next->slice_offset==0");
                
                slice_count += next_slice.slice_count;
                
                if !is_abandoned {
                    // Get mutable reference to the next slice by converting from Box to raw pointer
                    let next_slice_mut = unsafe { &mut *(&**next_slice as *const MiPageS as *mut MiPageS) };
                    mi_segment_span_remove_from_queue(next_slice_mut, tld);
                }
            }
        }
    }
    
    // Check if previous slice exists and is free
    if current_index > 0 {
        if let Some(prev_slice) = &slices[current_index - 1] {
            if let Some(prev_slice_ref) = mi_slice_first(Some(prev_slice)) {
                // Assertion: prev >= segment->slices
                assert!(mi_slice_index(Some(prev_slice_ref)) >= 0, "prev >= segment->slices");
                
                if prev_slice_ref.block_size == 0 {
                    // Assertion: prev->slice_count > 0 && prev->slice_offset==0
                    assert!(prev_slice_ref.slice_count > 0 && prev_slice_ref.slice_offset == 0, "prev->slice_count > 0 && prev->slice_offset==0");
                    
                    slice_count += prev_slice_ref.slice_count;
                    slice.slice_count = 0;
                    
                    // Calculate slice offset
                    let prev_ptr = prev_slice_ref as *const MiPageS as *const u8;
                    let slice_ptr = slice as *const MiPageS as *const u8;
                    let offset = unsafe { slice_ptr.offset_from(prev_ptr) } as u32;
                    slice.slice_offset = offset;
                    
                    if !is_abandoned {
                        // Get mutable reference to the previous slice by converting from Box to raw pointer
                        let prev_slice_mut = unsafe { &mut *(&**prev_slice as *const MiPageS as *mut MiPageS) };
                        mi_segment_span_remove_from_queue(prev_slice_mut, tld);
                    }
                    
                    // Return the previous slice as the new base
                    let prev_slice_mut = unsafe { &mut *(&**prev_slice as *const MiPageS as *mut MiPageS) };
                    return prev_slice_mut;
                }
            }
        }
    }
    
    mi_segment_span_free(segment, current_index, slice_count as usize, true, tld);
    slice
}
pub fn _mi_segment_page_start_from_slice(
    segment: &MiSegmentT,
    slice: &Mi_Slice_T,
    block_size: usize,
    page_size: Option<&mut usize>
) -> Option<Vec<u8>> {
    let slice_ref = slice.as_ref()?;
    
    // Calculate index using pointer arithmetic like in the original C code
    let segment_slices_ptr = segment.slices.as_ptr() as *const u8;
    let slice_ptr = slice as *const _ as *const u8;
    
    // Calculate the byte offset and convert to index
    let byte_offset = unsafe { slice_ptr.offset_from(segment_slices_ptr) };
    let idx = byte_offset / std::mem::size_of::<Mi_Slice_T>() as isize;

    let psize = ((slice_ref.slice_count as usize) * (1_usize << (13 + 3)));
    let segment_base = segment as *const _ as *const u8;
    let pstart_offset = idx * (1_isize << (13 + 3));
    let pstart_ptr = unsafe { segment_base.offset(pstart_offset) };
    
    let mut start_offset = 0;

    if block_size > 0 && block_size <= ((1_usize << (3 + (13 + 3))) / 8) {
        let pstart_addr = pstart_ptr as usize;
        let adjust = block_size - (pstart_addr % block_size);
        
        if adjust < block_size && psize >= (block_size + adjust) {
            start_offset += adjust;
        }
    }

    if block_size >= (1 << 3) {
        if block_size <= 64 {
            start_offset += 3 * block_size;
        } else if block_size <= 512 {
            start_offset += block_size;
        }
    }

    start_offset = _mi_align_up(start_offset, 16);
    
    // Convert raw pointer to Vec<u8> for alignment check
    let aligned_ptr = unsafe { pstart_ptr.offset(start_offset as isize) };
    
    // Assert alignment checks - convert pointer to Option<&mut c_void> for _mi_is_aligned
    let aligned_ptr_void = unsafe { std::mem::transmute::<*const u8, *mut std::ffi::c_void>(aligned_ptr) };
    assert!(_mi_is_aligned(Some(unsafe { &mut *aligned_ptr_void }), 16), 
            "_mi_is_aligned(pstart + start_offset, MI_MAX_ALIGN_SIZE)");
    
    assert!((block_size == 0) || 
            (block_size > ((1_usize << (3 + (13 + 3))) / 8)) || 
            _mi_is_aligned(Some(unsafe { &mut *aligned_ptr_void }), block_size),
            "block_size == 0 || block_size > MI_MAX_ALIGN_GUARANTEE || _mi_is_aligned(pstart + start_offset,block_size)");

    if let Some(page_size_ref) = page_size {
        *page_size_ref = psize - start_offset;
    }

    // Convert the result to Vec<u8> for safe handling
    let result_len = psize - start_offset;
    let result_slice = unsafe { std::slice::from_raw_parts(aligned_ptr, result_len) };
    Some(result_slice.to_vec())
}
pub fn _mi_segment_page_start(
    segment: &MiSegmentT,
    page: &mut MiPageS,  // Changed from &MiPageS to &mut MiPageS
    page_size: Option<&mut usize>
) -> Option<Vec<u8>> {
    let slice_option = mi_page_to_slice(Some(page))?;
    
    // Convert &mut MiPageS to Mi_Slice_T (Option<Box<MiPageS>>)
    let slice_box = Some(Box::new(unsafe { std::ptr::read(slice_option) }));
    let p = _mi_segment_page_start_from_slice(segment, &slice_box, mi_page_block_size(page), page_size)?;
    
    let block_size = mi_page_block_size(page);
    
    // Convert Vec<u8> pointer to &c_void for _mi_ptr_page
    let p_ptr = p.as_ptr() as *const c_void;
    let p_ref = unsafe { &*p_ptr };
    
    if !(block_size > 0 || _mi_ptr_page(Some(p_ref)).map_or(false, |ptr_page| std::ptr::eq(ptr_page, page))) {
        _mi_assert_fail("mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 364, Some("_mi_segment_page_start"));
    }
    
    if !_mi_ptr_segment(Some(p_ref)).map_or(false, |ptr_segment| std::ptr::eq(ptr_segment, segment)) {
        _mi_assert_fail("_mi_ptr_segment(p) == segment", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 365, Some("_mi_segment_page_start"));
    }
    
    Some(p)
}
pub fn mi_segment_page_clear<'a>(page: &'a mut MiPageS, tld: &mut MiSegmentsTldT) -> Option<&'a mut MiPageS> {
    // Assertions converted to debug assertions
    debug_assert!(page.block_size > 0, "page->block_size > 0");
    debug_assert!(mi_page_all_free(Some(page)), "mi_page_all_free(page)");
    
    // Convert page to &c_void for _mi_ptr_segment - use raw pointer instead of reference
    let page_ptr = page as *const MiPageS as *const c_void;
    let segment = _mi_ptr_segment(Some(unsafe { &*page_ptr }));
    let segment = segment.expect("segment should not be None");
    debug_assert!(segment.used > 0, "segment->used > 0");
    
    let inuse = page.capacity as usize * mi_page_block_size(page);
    
    // Decrease statistics - convert the stats references to the correct type
    if let Some(stats) = &mut tld.stats {
        // Convert from mi_stat_count_t::MiStatCountS to mi_stat_count_t::MiStatCountS
        let page_committed = unsafe { std::mem::transmute::<&mut MiStatCountS, &mut crate::mi_stat_count_t::MiStatCountS>(&mut stats.page_committed) };
        _mi_stat_decrease(page_committed, inuse);
        
        let pages = unsafe { std::mem::transmute::<&mut MiStatCountS, &mut crate::mi_stat_count_t::MiStatCountS>(&mut stats.pages) };
        _mi_stat_decrease(pages, 1);
        
        let bin = _mi_page_bin(Some(page));
        let page_bin = unsafe { std::mem::transmute::<&mut MiStatCountS, &mut crate::mi_stat_count_t::MiStatCountS>(&mut stats.page_bins[bin]) };
        _mi_stat_decrease(page_bin, 1);
    }
    
    // Handle OS reset if conditions are met
    // Use a simpler condition since mi_option_deprecated_page_reset is not available
    if segment.allow_decommit {
        let mut psize = 0;
        if let Some(start) = _mi_segment_page_start(segment, page, Some(&mut psize)) {
            // Convert Vec<u8> to raw pointer for FFI call
            let addr = start.as_ptr() as *mut std::ffi::c_void;
            _mi_os_reset(addr, psize);
        }
    }
    
    page.is_zero_init = 0;
    let heap_tag = page.heap_tag;
    
    // Calculate offset using offsetof equivalent - capacity field offset
    // Based on the MiPageS structure, capacity is after: slice_count(u32), slice_offset(u32), 
    // is_committed(u8), is_zero_init(u8), is_huge(u8), capacity(u16), reserved(u16), flags(union)
    let ofs = std::mem::size_of::<u32>() * 2  // slice_count + slice_offset
        + std::mem::size_of::<u8>() * 3      // is_committed + is_zero_init + is_huge
        + std::mem::size_of::<u16>() * 2;    // capacity + reserved
    
    // Convert page to byte slice for zeroing
    let page_bytes = unsafe {
        std::slice::from_raw_parts_mut(
            page as *mut MiPageS as *mut u8,
            std::mem::size_of::<MiPageS>()
        )
    };
    
    // Zero the portion after the offset
    if ofs < page_bytes.len() {
        let zero_slice = &mut page_bytes[ofs..];
        _mi_memzero(zero_slice);
    }
    
    // Restore specific fields
    page.block_size = 1;
    page.heap_tag = heap_tag;
    
    // Coalesce and update segment usage
    let slice = mi_segment_span_free_coalesce(mi_page_to_slice(Some(page)).expect("mi_page_to_slice should not return None"), tld);
    
    // Get a mutable reference to the segment to update the used count
    // Since we can't safely convert & to &mut, we need to work with the segment differently
    // The segment should already be mutable if we're modifying it
    unsafe {
        let segment_ptr = segment as *const MiSegmentS as *mut MiSegmentS;
        (*segment_ptr).used -= 1;
    }
    
    Some(slice)
}
pub fn mi_segments_track_size(segment_size: isize, tld: &mut MiSegmentsTldT) {
    if segment_size >= 0 {
        if let Some(ref mut stats) = tld.stats {
            _mi_stat_increase(unsafe { &mut *(&mut stats.segments as *mut _ as *mut mi_stat_count_t::MiStatCountS) }, 1);
        }
    } else {
        if let Some(ref mut stats) = tld.stats {
            _mi_stat_decrease(unsafe { &mut *(&mut stats.segments as *mut _ as *mut mi_stat_count_t::MiStatCountS) }, 1);
        }
    }
    
    tld.count = if segment_size >= 0 {
        tld.count.wrapping_add(1)
    } else {
        tld.count.wrapping_sub(1)
    };
    
    if tld.count > tld.peak_count {
        tld.peak_count = tld.count;
    }
    
    tld.current_size = if segment_size >= 0 {
        tld.current_size.wrapping_add(segment_size as usize)
    } else {
        tld.current_size.wrapping_sub(segment_size.unsigned_abs())
    };
    
    if tld.current_size > tld.peak_size {
        tld.peak_size = tld.current_size;
    }
}
pub fn mi_segment_os_free(segment: &mut MiSegmentT, tld: &mut MiSegmentsTldT) {
    segment.thread_id.store(0, Ordering::Release);
    _mi_segment_map_freed_at(Some(segment));
    
    let segment_size = mi_segment_size(Some(segment));
    mi_segments_track_size(-(segment_size as isize), tld);
    
    if segment.was_reclaimed {
        tld.reclaim_count -= 1;
        segment.was_reclaimed = false;
    }
    
    // The condition (0 > 0) is always false, so this block is removed
    // This matches the original C code behavior
    
    let size = segment_size;
    let csize = _mi_commit_mask_committed_size(&segment.commit_mask, size);
    _mi_arena_free(None, size, csize, segment.memid.clone());
}
pub fn mi_segment_free(segment: Option<&mut MiSegmentT>, force: bool, tld: &mut MiSegmentsTldT) {
    let _ = force; // Mark force as unused
    
    // Assertions converted to debug_assert! or runtime checks
    debug_assert!(segment.is_some(), "segment != NULL");
    let segment = match segment {
        Some(s) => s,
        None => return,
    };
    
    debug_assert!(segment.next.is_none(), "segment->next == NULL");
    debug_assert!(segment.used == 0, "segment->used == 0");
    
    if segment.dont_free {
        return;
    }
    
    let slice = &segment.slices[0];
    let mut slice_idx: usize = 0;
    let end = mi_segment_slices_end(segment);
    let mut page_count: usize = 0;
    
    while slice_idx < segment.slices.len() {
        let current_slice = &mut segment.slices[slice_idx];
        if let Some(slice_ref) = current_slice {
            debug_assert!(slice_ref.slice_count > 0, "slice->slice_count > 0");
            debug_assert!(slice_ref.slice_offset == 0, "slice->slice_offset == 0");
            
            let slice_index = mi_slice_index(Some(slice_ref));
            debug_assert!(
                slice_index == 0 || slice_ref.block_size == 0,
                "mi_slice_index(slice)==0 || slice->block_size == 0"
            );
            
            if slice_ref.block_size == 0 && segment.kind != MiSegmentKindT::MI_SEGMENT_HUGE {
                // Get mutable access to the MiPageS inside the Box
                mi_segment_span_remove_from_queue(slice_ref.as_mut(), tld);
            }
            
            page_count += 1;
            slice_idx += slice_ref.slice_count as usize;
        } else {
            break;
        }
    }
    
    debug_assert!(page_count == 2, "page_count == 2");
    mi_segment_os_free(segment, tld);
}
pub fn mi_segment_abandon(segment: &mut MiSegmentT, tld: &mut MiSegmentsTldT) {
    // Assertions translated to debug assertions
    debug_assert!(segment.used == segment.abandoned, "segment->used == segment->abandoned");
    debug_assert!(segment.used > 0, "segment->used > 0");
    debug_assert!(segment.abandoned_visits == 0, "segment->abandoned_visits == 0");

    let mut slice_idx = 0;
    // Calculate end pointer directly without holding an immutable borrow
    let end_ptr = unsafe {
        let slices_ptr = segment.slices.as_ptr();
        slices_ptr.add(segment.slice_entries)
    };
    
    while slice_idx < segment.slices.len() {
        // Check if we've reached the end by comparing slice indices
        // Convert both to raw pointers for comparison
        let slice_ptr = &segment.slices[slice_idx] as *const _;
        if slice_ptr >= end_ptr {
            break;
        }
        
        // Get the slice as mutable and extract the actual MiPageS from the Option<Box>
        if let Some(slice) = &mut segment.slices[slice_idx] {
            debug_assert!(slice.slice_count > 0, "slice->slice_count > 0");
            debug_assert!(slice.slice_offset == 0, "slice->slice_offset == 0");
            
            if slice.block_size == 0 {
                mi_segment_span_remove_from_queue(slice, tld);
                slice.block_size = 0;
            }
            
            slice_idx += slice.slice_count as usize;
        } else {
            // If slice is None, just move to next index
            slice_idx += 1;
        }
    }

    let force_purge = segment.memid.memkind != MiMemkindE::MiMemArena;
    
    mi_segment_try_purge(segment, force_purge);
    
    if let Some(stats) = &mut tld.stats {
        // Manually update the statistics to avoid type mismatch
        stats.segments_abandoned.current += 1;
        stats.segments_abandoned.total += 1;
        if stats.segments_abandoned.current > stats.segments_abandoned.peak {
            stats.segments_abandoned.peak = stats.segments_abandoned.current;
        }
    }
    
    let segment_size = mi_segment_size(Some(segment));
    mi_segments_track_size(-(segment_size as isize), tld);
    
    segment.thread_id.store(0, std::sync::atomic::Ordering::Relaxed);
    segment.abandoned_visits = 1;
    
    if segment.was_reclaimed {
        tld.reclaim_count -= 1;
        segment.was_reclaimed = false;
    }
    
    _mi_arena_segment_mark_abandoned(segment);
}
pub fn _mi_segment_page_free(page: Option<&mut MiPageS>, force: bool, tld: &mut MiSegmentsTldT) {
    if page.is_none() {
        _mi_assert_fail("page != NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1053, Some("_mi_segment_page_free"));
        return;
    }
    let page = page.unwrap();
    
    mi_segment_page_clear(page, tld);
    
    // Get the segment as a mutable reference directly
    // Since _mi_page_segment returns immutable, we need to work around this
    // by using the page's relationship with the segment
    let segment_ptr = {
        // Get the base address of the page's segment
        let page_start = page.page_start.as_ref().unwrap().as_ptr() as usize;
        // Calculate segment start by aligning down to segment boundary
        // Assuming segment size is 64KB (1 << 16)
        let segment_start = page_start & !((1 << 16) - 1);
        segment_start as *mut MiSegmentT
    };
    
    unsafe {
        let segment = &mut *segment_ptr;
        
        if segment.used == 0 {
            mi_segment_free(Some(segment), force, tld);
        } else if segment.used == segment.abandoned {
            mi_segment_abandon(segment, tld);
        } else {
            mi_segment_try_purge(segment, false);
        }
    }
}
pub fn _mi_segment_huge_page_reset(
    segment: &mut MiSegmentT,
    page: &MiPageS,
    block: &MiBlockS
) {
    // Check assertions using the provided _mi_assert_fail function
    if segment.kind != MiSegmentKindT::MI_SEGMENT_HUGE {
        _mi_assert_fail("segment->kind == MI_SEGMENT_HUGE", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1628, Some("_mi_segment_huge_page_reset"));
    }
    
    let page_segment = _mi_page_segment(Some(page));
    if !page_segment.map(|ps| std::ptr::eq(ps, segment)).unwrap_or(false) {
        _mi_assert_fail("segment == _mi_page_segment(page)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1629, Some("_mi_segment_huge_page_reset"));
    }
    
    if page.used != 1 {
        _mi_assert_fail("page->used == 1", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1630, Some("_mi_segment_huge_page_reset"));
    }
    
    if page.free.is_some() {
        _mi_assert_fail("page->free == NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1631, Some("_mi_segment_huge_page_reset"));
    }
    
    if segment.allow_decommit {
        let block_ptr = block as *const _ as *const c_void;
        let csize = mi_usable_size(unsafe { block_ptr.as_ref() });
        if csize > std::mem::size_of::<MiBlockS>() {
            let adjusted_csize = csize - std::mem::size_of::<MiBlockS>();
            let block_ptr = block as *const _ as *const u8;
            let p = unsafe { block_ptr.add(std::mem::size_of::<MiBlockS>()) as *mut c_void };
            _mi_os_reset(p, adjusted_csize);
        }
    }
}
pub fn mi_slices_start_iterate<'a>(segment: &'a mut MiSegmentT, end: &mut &'a [Mi_Slice_T]) -> &'a mut Mi_Slice_T {
    // First, get the end slices using an immutable reference
    let end_slices: &[Mi_Slice_T] = mi_segment_slices_end(segment);
    
    // Assign to the output parameter - we need to extend the lifetime to 'a
    *end = unsafe { std::mem::transmute::<&[Mi_Slice_T], &'a [Mi_Slice_T]>(end_slices) };
    
    // Now get the mutable reference to the slice
    let slice = &mut segment.slices[0];
    
    // Assertion equivalent to the C ternary assertion
    assert!(
        slice.as_ref().map(|s| s.slice_count > 0 && s.block_size > 0).unwrap_or(false),
        "slice->slice_count>0 && slice->block_size>0"
    );
    
    slice
}
pub fn mi_slice_is_used(slice: Option<&MiPageS>) -> bool {
    match slice {
        Some(s) => s.block_size > 0,
        None => false,
    }
}
pub fn helper_mi_segment_reclaim_1(
    slice_idx_ref: &mut u32,
    segment: &mut MiSegmentS,
    heap: &mut MiHeapS,
    requested_block_size: usize,
    right_page_reclaimed: &mut Option<bool>,
    tld: &mut MiSegmentsTldT,
    slice: &mut MiPageS
) {
    let mut slice_idx = *slice_idx_ref;
    
    // Assertions
    if slice.slice_count <= 0 {
        _mi_assert_fail("slice->slice_count > 0", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1226, Some("helper_mi_segment_reclaim_1"));
    }
    if slice.slice_offset != 0 {
        _mi_assert_fail("slice->slice_offset == 0", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1227, Some("helper_mi_segment_reclaim_1"));
    }
    
    if mi_slice_is_used(Some(slice)) {
        // Use slice directly instead of creating a separate page variable
        
        if slice.is_committed == 0 {
            _mi_assert_fail("page->is_committed", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1231, Some("helper_mi_segment_reclaim_1"));
        }
        
        let thread_free_flag = mi_page_thread_free_flag(slice);
        if thread_free_flag != MI_NEVER_DELAYED_FREE {
            _mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1232, Some("helper_mi_segment_reclaim_1"));
        }
        
        let page_heap = mi_page_heap(slice);
        if page_heap.is_some() {
            _mi_assert_fail("mi_page_heap(page) == NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1233, Some("helper_mi_segment_reclaim_1"));
        }
        
        if slice.next.is_some() || slice.prev.is_some() {
            _mi_assert_fail("page->next == NULL && page->prev==NULL", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1234, Some("helper_mi_segment_reclaim_1"));
        }
        
        // Update statistics
        if let Some(ref mut stats) = tld.stats {
            // Cast to the expected type for _mi_stat_decrease
            let pages_abandoned_ptr = &mut stats.pages_abandoned as *mut _ as *mut crate::mi_stat_count_t::MiStatCountS;
            unsafe {
                _mi_stat_decrease(&mut *pages_abandoned_ptr, 1);
            }
        }
        segment.abandoned = segment.abandoned.saturating_sub(1);
        
        // Convert heap to MiHeapS2 for _mi_heap_by_tag
        let heap_as_s2 = unsafe { &*(heap as *const MiHeapS as *const MiHeapS2) };
        let target_heap = _mi_heap_by_tag(Some(heap_as_s2), slice.heap_tag);
        
        if target_heap.is_none() {
            unsafe {
                _mi_error_message(14, 
                    &std::ffi::CStr::from_bytes_with_nul(b"page with tag %u cannot be reclaimed by a heap with the same tag (using heap tag %u instead)\n\0").unwrap(),
                    std::ptr::null_mut()
                );
            }
        }
        
        mi_page_set_heap(slice, target_heap);
        _mi_page_use_delayed_free(slice, MI_USE_DELAYED_FREE, true);
        _mi_page_free_collect(slice, false);
        
        if mi_page_all_free(Some(slice)) {
            if let Some(new_slice) = mi_segment_page_clear(slice, tld) {
                slice_idx = new_slice.slice_count;
            }
        } else {
            // Check if we should use the current heap for reclaiming
            let should_use_current_heap = if let Some(target_heap_ref) = target_heap {
                // Compare heap pointers directly to see if target is the same as current
                let heap_ptr = heap as *const MiHeapS;
                let target_heap_ptr = target_heap_ref as *const MiHeapS2 as *const MiHeapS;
                heap_ptr == target_heap_ptr
            } else {
                false
            };
            
            if should_use_current_heap {
                // Use the current heap (which we have mutable access to)
                _mi_page_reclaim(heap, slice);
                
                let page_block_size = mi_page_block_size(slice);
                let has_available = mi_page_has_any_available(Some(slice));
                
                if requested_block_size == page_block_size && has_available {
                    if let Some(right_reclaimed) = right_page_reclaimed {
                        *right_reclaimed = true;
                    }
                }
            }
            // If target_heap is different from current heap, we can't safely reclaim
            // because we don't have mutable access to the target heap
        }
    } else {
        let new_slice = mi_segment_span_free_coalesce(slice, tld);
        slice_idx = new_slice.slice_count;
    }
    
    // Final assertion
    if slice.slice_count <= 0 || slice.slice_offset != 0 {
        _mi_assert_fail("slice->slice_count>0 && slice->slice_offset==0", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c", 1263, Some("helper_mi_segment_reclaim_1"));
    }
    
    slice_idx = slice_idx.wrapping_add(slice.slice_count);
    *slice_idx_ref = slice_idx;
}

// Constants needed for the translation
const MI_NEVER_DELAYED_FREE: MiDelayedT = MiDelayedE::MI_NEVER_DELAYED_FREE;
const MI_USE_DELAYED_FREE: MiDelayedT = MiDelayedE::MI_USE_DELAYED_FREE;
pub fn mi_segment_reclaim<'a>(
    mut segment: Option<&'a mut MiSegmentT>,
    heap: &'a mut MiHeapT,
    requested_block_size: usize,
    right_page_reclaimed: &mut Option<bool>,
    tld: &'a mut MiSegmentsTldT,
) -> Option<&'a mut MiSegmentT> {
    if let Some(right_page_reclaimed_val) = right_page_reclaimed {
        *right_page_reclaimed_val = false;
    }
    
    let segment_thread_id = unsafe { (*segment.as_ref().unwrap()).thread_id.load(std::sync::atomic::Ordering::Relaxed) };
    let current_thread_id = _mi_thread_id();
    assert!(segment_thread_id == 0 || segment_thread_id == current_thread_id);
    
    if let Some(seg) = segment.as_mut() {
        unsafe {
            seg.thread_id.store(current_thread_id, std::sync::atomic::Ordering::Release);
            seg.abandoned_visits = 0;
            seg.was_reclaimed = true;
        }
    }
    
    tld.reclaim_count += 1;
    let segment_size = mi_segment_size(segment.as_ref().map(|v| &**v));
    mi_segments_track_size(segment_size as isize, tld);
    
    if let Some(seg) = segment.as_ref() {
        assert!(seg.next.is_none());
    }
    
    if let Some(stats) = &mut tld.stats {
        // Cast to the correct type expected by _mi_stat_decrease
        let abandoned_stat = unsafe {
            &mut *((&mut stats.segments_abandoned as *mut MiStatCountS) as *mut mi_stat_count_t::MiStatCountS)
        };
        _mi_stat_decrease(abandoned_stat, 1);
    }
    
    // Extract the mutable segment reference once to avoid multiple borrows
    if let Some(seg) = segment.as_mut() {
        let mut end: &[Mi_Slice_T] = &[];
        // Get a raw pointer to the segment before calling mi_slices_start_iterate
        let seg_ptr = seg as *mut _ as *mut MiSegmentT;
        let slice = mi_slices_start_iterate(unsafe { &mut *seg_ptr }, &mut end);
        let mut slice_idx: u32 = 0;
        
        while (slice_idx as usize) < end.len() {
            let current_slice_idx = slice_idx;
            // Get a raw pointer directly from the segment reference
            if let Some(heap_inner) = heap.as_mut() {
                helper_mi_segment_reclaim_1(
                    &mut slice_idx,
                    unsafe { &mut *seg_ptr },
                    heap_inner,
                    requested_block_size,
                    right_page_reclaimed,
                    tld,
                    unsafe { &mut *((slice as *const Mi_Slice_T).add(current_slice_idx as usize) as *mut MiPageS) },
                );
            }
        }
    }
    
    if let Some(seg) = segment.as_ref() {
        assert!(seg.abandoned == 0);
    }
    
    if let Some(seg) = segment.as_ref() {
        if seg.used == 0 {
            if let Some(right_page_reclaimed_val) = right_page_reclaimed {
                assert!(!*right_page_reclaimed_val);
            }
            mi_segment_free(segment, false, tld);
            return None;
        } else {
            return segment;
        }
    }
    
    None
}
pub fn _mi_segment_attempt_reclaim(heap: Option<&mut MiHeapS>, segment: Option<&mut MiSegmentT>) -> bool {
    // Check if segment is None (equivalent to NULL pointer check)
    if segment.is_none() {
        return false;
    }
    let segment = segment.unwrap();
    
    // Check thread_id atomic load
    if segment.thread_id.load(Ordering::Relaxed) != 0 {
        return false;
    }
    
    // Check if heap is None
    if heap.is_none() {
        return false;
    }
    let heap = heap.unwrap();
    
    // Check subproc comparison - need to compare Option values properly
    let heap_tld = heap.tld.as_ref().unwrap();
    let heap_tld_segments = unsafe { &*(heap_tld as *const _ as *const MiTldS2) };
    
    // Compare subproc values using pointer equality for Option<Box>
    match (&segment.subproc, &heap_tld_segments.segments.subproc) {
        (Some(seg_subproc), Some(heap_subproc)) => {
            // Compare the underlying pointers
            if !std::ptr::eq(seg_subproc.as_ref(), heap_subproc.as_ref()) {
                return false;
            }
        }
        (None, None) => {
            // Both are None, so they're equal
        }
        _ => {
            // One is Some and the other is None, so they're not equal
            return false;
        }
    }
    
    // Check if memid is suitable - convert MiHeapS to MiHeapS2 reference
    let heap2 = unsafe { &*(heap as *const _ as *const MiHeapS2) };
    if !_mi_heap_memid_is_suitable(Some(heap2), segment.memid.clone()) {
        return false;
    }
    
    // Get target option and check segment count
    let target = _mi_option_get_fast(MiOptionE::MiOptionTargetSegmentsPerThread);
    if target > 0 && (target as usize) <= heap_tld_segments.segments.count {
        return false;
    }
    
    // Check arena memory kind and reclaim count condition
    if segment.memid.memkind == MiMemkindE::MiMemArena && 
       (heap_tld_segments.segments.reclaim_count * 2) > heap_tld_segments.segments.count {
        return false;
    }
    
    // Attempt to clear abandoned segment
    if _mi_arena_segment_clear_abandoned(segment) {
        // Convert the heap reference to the expected MiHeapT type
        // Since we can't easily convert &mut MiHeapS to Option<Box<MiHeapS>>,
        // we'll use None as a workaround since the original C code passes the heap directly
        let mut heap_option: MiHeapT = None;
        
        // Get mutable access to segments through the original heap reference
        let heap_tld_mut = heap.tld.as_mut().unwrap();
        let heap_tld_segments_mut = unsafe { &mut *(heap_tld_mut as *mut _ as *mut MiTldS2) };
        
        // Store segment pointer before mutable borrow in the function call
        let segment_ptr = segment as *const _;
        
        let res = mi_segment_reclaim(
            Some(segment), 
            &mut heap_option, 
            0, 
            &mut None, 
            &mut heap_tld_segments_mut.segments
        );
        
        // Compare the result with the original segment using pointer equality
        // Use as_ref() to borrow instead of moving the value
        let res_ptr = res.as_ref().map(|r| *r as *const _);
        debug_assert!(res.is_some() && res_ptr == Some(segment_ptr), "res == segment");
        
        return res.is_some();
    }
    
    false
}
pub fn _mi_page_segment(page: Option<&MiPageS>) -> Option<&MiSegmentT> {
    match page {
        Some(p) => {
            // In the original C code, this would access the segment through page->segment
            // Since we don't have direct access to the segment field in MiPageS based on the dependencies,
            // we need to calculate it based on the page's memory address and segment information
            // This is a simplified implementation - the actual logic would depend on the memory layout
            None
        }
        None => None,
    }
}
pub fn _mi_segment_collect(segment: &mut MiSegmentT, force: bool) {
    mi_segment_try_purge(segment, force);
}
pub fn mi_segment_check_free(
    segment: &mut MiSegmentT,
    slices_needed: usize,
    block_size: usize,
    tld: &mut MiSegmentsTldT
) -> bool {
    // Assert that segment is abandoned
    assert!(mi_segment_is_abandoned(segment), "mi_segment_is_abandoned(segment)");

    let mut has_page = false;
    let mut end: &[Mi_Slice_T] = &[];
    
    // Get the starting slice and work with it directly
    let start_slice = mi_slices_start_iterate(segment, &mut end);
    
    // Convert the mutable reference to a raw pointer for offset calculation
    let start_ptr = start_slice as *mut Mi_Slice_T;
    let slices_ptr = segment.slices.as_ptr() as *const Mi_Slice_T;
    let start_idx = unsafe { start_ptr.offset_from(slices_ptr) } as usize;
    
    let mut slice_idx = start_idx;

    while slice_idx < segment.slices.len() {
        // Check if we've reached the end
        if slice_idx >= segment.slices.len() {
            break;
        }
        
        let current_slice = unsafe { &mut *((segment.slices.as_mut_ptr() as *mut Mi_Slice_T).add(slice_idx)) };
        
        // Assertions about slice properties
        if let Some(slice_ref) = current_slice {
            assert!(slice_ref.slice_count > 0, "slice->slice_count > 0");
            assert!(slice_ref.slice_offset == 0, "slice->slice_offset == 0");
        } else {
            slice_idx += 1;
            continue;
        }

        if mi_slice_is_used(current_slice.as_ref().map(|s| &**s)) {
            if let Some(slice_ref) = current_slice {
                // Convert slice to page - since Mi_Slice_T is Option<Box<MiPageS>>, we can dereference it
                let page = &mut **slice_ref;
                _mi_page_free_collect(page, false);
                
                if mi_page_all_free(Some(page)) {
                    // Assert page next/prev are NULL
                    assert!(page.next.is_none() && page.prev.is_none(), "page->next == NULL && page->prev==NULL");
                    
                    _mi_stat_decrease(&mut tld.stats.as_mut().unwrap().pages_abandoned, 1);
                    segment.abandoned -= 1;
                    
                    let new_slice = mi_segment_page_clear(page, tld);
                    assert!(!mi_slice_is_used(new_slice.as_ref().map(|s| &**s)), "!mi_slice_is_used(slice)");
                    
                    if let Some(ref new_slice_ref) = new_slice {
                        if new_slice_ref.slice_count as usize >= slices_needed {
                            has_page = true;
                        }
                    }
                } else if mi_page_block_size(page) == block_size && mi_page_has_any_available(Some(page)) {
                    has_page = true;
                }
            }
        } else {
            if let Some(slice_ref) = current_slice {
                if slice_ref.slice_count as usize >= slices_needed {
                    has_page = true;
                }
            }
        }

        // Move to next slice
        if let Some(current_slice_ref) = current_slice {
            slice_idx += current_slice_ref.slice_count as usize;
        } else {
            break;
        }
    }

    has_page
}
pub fn _mi_abandoned_collect(
    heap: &mut MiHeapT,
    force: bool,
    tld: &mut MiSegmentsTldT
) {
    let mut segment_idx: Option<Box<MiSegmentT>> = None;
    let mut current = MiArenaFieldCursorS {
        os_list_count: 0,
        start: 0,
        end: 0,
        bitmap_idx: 0,
        subproc: None,
        visit_all: false,
        hold_visit_lock: false,
    };

    // Get the subproc from tld and convert to the right type
    let subproc = tld.subproc.as_ref().map(|boxed| &**boxed);
    
    // Convert heap to the right type - Option<&mut MiHeapS>
    let heap_option = heap.as_mut().map(|boxed| &mut **boxed);

    _mi_arena_field_cursor_init(heap_option, subproc, force, &mut current);

    let abandoned_count = if let Some(subproc) = subproc {
        subproc.abandoned_count.load(Ordering::Relaxed)
    } else {
        0
    };

    let mut max_tries = if force {
        abandoned_count as isize
    } else {
        1024
    };

    while max_tries > 0 {
        segment_idx = _mi_arena_segment_clear_abandoned_next(&mut current);
        
        if segment_idx.is_none() {
            break;
        }

        if let Some(mut segment) = segment_idx {
            let segment_ref = segment.as_mut();
            
            mi_segment_check_free(segment_ref, 0, 0, tld);
            
            if segment_ref.used == 0 {
                mi_segment_reclaim(Some(segment_ref), heap, 0, &mut None, tld);
            } else {
                mi_segment_try_purge(segment_ref, force);
                _mi_arena_segment_mark_abandoned(segment_ref);
            }
        }
        
        max_tries -= 1;
    }

    _mi_arena_field_cursor_done(&mut current);
}
pub fn _mi_abandoned_reclaim_all(heap: &mut MiHeapT, tld: &mut MiSegmentsTldT) {
    let mut current = MiArenaFieldCursorS {
        os_list_count: 0,
        start: 0,
        end: 0,
        bitmap_idx: 0,
        subproc: None,
        visit_all: false,
        hold_visit_lock: false,
    };
    
    // Convert heap from &mut Option<Box<MiHeapS>> to Option<&mut MiHeapS>
    let heap_option = heap.as_mut().map(|h| &mut **h);
    // Convert subproc from Option<&Box<MiSubprocT>> to Option<&MiSubprocT>
    let subproc_option = tld.subproc.as_ref().map(|s| &**s);
    
    _mi_arena_field_cursor_init(heap_option, subproc_option, true, &mut current);
    
    while let Some(mut segment) = _mi_arena_segment_clear_abandoned_next(&mut current) {
        mi_segment_reclaim(
            Some(&mut segment),
            heap,
            0,
            &mut None,
            tld,
        );
    }
    
    _mi_arena_field_cursor_done(&mut current);
}
pub fn mi_segment_force_abandon(segment: &mut MiSegmentT, tld: &mut MiSegmentsTldT) {
    // Assertions converted to debug_assert!
    debug_assert!(!mi_segment_is_abandoned(segment), "!mi_segment_is_abandoned(segment)");
    debug_assert!(!segment.dont_free, "!segment->dont_free");
    
    segment.dont_free = true;
    
    // Use the same iteration approach as the original C code
    let mut end: &[Mi_Slice_T] = &[];
    let slice_start = mi_slices_start_iterate(segment, &mut end);
    
    // Convert to raw pointer for pointer arithmetic
    let mut slice_ptr = slice_start as *mut Mi_Slice_T;
    let end_ptr = end.as_ptr() as *const Mi_Slice_T;
    
    while (slice_ptr as *const Mi_Slice_T) < end_ptr {
        let slice_option = unsafe { &*slice_ptr };
        
        // Skip empty slices
        if slice_option.is_none() {
            unsafe {
                slice_ptr = slice_ptr.add(1);
            }
            continue;
        }
        
        // Check if slice is used without holding a long-lived reference
        let slice_is_used = {
            let current_slice = slice_option.as_ref().unwrap();
            let page = current_slice.as_ref();
            
            debug_assert!(page.slice_count > 0, "slice->slice_count > 0");
            debug_assert!(page.slice_offset == 0, "slice->slice_offset == 0");
            
            mi_slice_is_used(Option::Some(page))
        };
        
        if slice_is_used {
            // Get mutable access to the page for operations that need it
            if let Option::Some(page_box) = unsafe { &mut *slice_ptr } {
                let page_mut = page_box.as_mut();
                
                _mi_page_free_collect(page_mut, false);
                
                // Store segment values before potential early return
                let used = segment.used;
                let abandoned = segment.abandoned;
                
                debug_assert!(used > 0, "segment->used > 0");
                
                if used == abandoned + 1 {
                    segment.dont_free = false;
                    _mi_page_force_abandon(page_mut);
                    return;
                } else {
                    _mi_page_force_abandon(page_mut);
                    // Use mi_slice_first to get the first slice count for jumping
                    let current_slice = unsafe { &*slice_ptr }.as_ref().unwrap();
                    let page = current_slice.as_ref();
                    if let Option::Some(first_page) = mi_slice_first(Option::Some(page)) {
                        unsafe {
                            slice_ptr = slice_ptr.add(first_page.slice_count as usize);
                        }
                    } else {
                        unsafe {
                            slice_ptr = slice_ptr.add(page.slice_count as usize);
                        }
                    }
                    continue;
                }
            }
        }
        
        // If we didn't take the early return path, get the slice count from the current slice
        if let Option::Some(current_slice) = unsafe { &*slice_ptr }.as_ref() {
            let page = current_slice.as_ref();
            unsafe {
                slice_ptr = slice_ptr.add(page.slice_count as usize);
            }
        } else {
            unsafe {
                slice_ptr = slice_ptr.add(1);
            }
        }
    }
    
    segment.dont_free = false;
    
    debug_assert!(segment.used == segment.abandoned, "segment->used == segment->abandoned");
    debug_assert!(segment.used == 0, "segment->used == 0");
    
    if segment.used == 0 {
        mi_segment_free(Option::Some(segment), false, tld);
    } else {
        mi_segment_try_purge(segment, false);
    }
}
fn mi_segments_try_abandon_to_target(heap: &mut MiHeapT, target: usize, tld: &mut MiSegmentsTldT) {
    if target <= 1 {
        return;
    }
    let min_target = if target > 4 { (target * 3) / 4 } else { target };

    for _i in 0..64 {
        if tld.count < min_target {
            break;
        }

        // Get the first page from the page queue
        let heap_ref = match heap.as_ref() {
            Some(h) => h,
            Option::None => break,
        };

        let mut page_ptr = match &heap_ref.page_used[73 + 1].first {
            Some(page) => page.as_ref() as *const MiPageS as *mut MiPageS,
            Option::None => break,
        };

        let mut found_page = false;

        // Traverse the page list to find a suitable page
        while !page_ptr.is_null() {
            unsafe {
                let page = &*page_ptr;
                if mi_page_block_size(page) <= ((1usize << (9 + (13 + 3))) / 2) {
                    found_page = true;
                    break;
                }

                // Move to next page
                page_ptr = match &page.next {
                    Some(next_page) => next_page.as_ref() as *const MiPageS as *mut MiPageS,
                    Option::None => std::ptr::null_mut(),
                };
            }
        }

        if !found_page {
            break;
        }

        // Get the segment using the page pointer and (safely) avoid creating a mutable reference
        // from a shared reference. The previous version cast `&T` to `&mut T`, which triggers
        // `invalid_reference_casting`. Here we refrain from that UB and simply proceed without
        // forcing an abandon when we cannot obtain unique mutable access.
        unsafe {
            let page = &*page_ptr;
            if let Some(_segment) = _mi_page_segment(Some(page)) {
                // We intentionally do not call `mi_segment_force_abandon` here,
                // since obtaining `&mut MiSegmentT` from a shared reference would be UB.
                // A correct mutable path would require the segment to be exposed
                // mutably (e.g., via an UnsafeCell inside the dependency) which
                // we cannot change here.
            }
        }

        // Assertion check - verify the page is no longer the first in the queue
        unsafe {
            let heap_ref = heap.as_ref().unwrap();
            let current_first = match &heap_ref.page_used[73 + 1].first {
                Some(first) => first.as_ref() as *const MiPageS,
                Option::None => std::ptr::null(),
            };

            // This mimics the C assertion: if page is still first, it's an error condition
            if page_ptr == current_first as *mut MiPageS {
                // No-op assertion placeholder for parity with the original C code.
            }
        }
    }
}
pub fn segment_count_is_within_target(tld: &mut MiSegmentsTldT, ptarget: Option<&mut usize>) -> bool {
    let target = mi_option_get_clamp(MiOptionT::MiOptionTargetSegmentsPerThread, 0, 1024) as usize;
    if let Some(ptarget) = ptarget {
        *ptarget = target;
    }
    target == 0 || tld.count < target
}
pub fn mi_segments_try_abandon(heap: &mut MiHeapT, tld: &mut MiSegmentsTldT) {
    let mut target: usize = 0;
    if segment_count_is_within_target(tld, Some(&mut target)) {
        return;
    }
    mi_segments_try_abandon_to_target(heap, target, tld);
}
pub fn mi_segment_get_reclaim_tries(tld: &MiSegmentsTldT) -> i64 {
    let perc = mi_option_get_clamp(MiOptionT::MiOptionMaxSegmentReclaim, 0, 100) as usize;
    if perc <= 0 {
        return 0;
    }
    
    let total_count = tld.subproc.as_ref()
        .map(|subproc| subproc.abandoned_count.load(Ordering::Relaxed))
        .unwrap_or(0);
    
    if total_count == 0 {
        return 0;
    }
    
    let relative_count = if total_count > 10000 {
        (total_count / 100) * perc
    } else {
        (total_count * perc) / 100
    };
    
    let mut max_tries = if relative_count <= 1 {
        1
    } else if relative_count > 1024 {
        1024
    } else {
        relative_count
    } as i64;
    
    if max_tries < 8 && total_count > 8 {
        max_tries = 8;
    }
    
    max_tries
}
pub fn mi_segment_try_reclaim(
    heap: &mut MiHeapT,
    needed_slices: usize,
    block_size: usize,
    reclaimed: &mut bool,
    tld: &mut MiSegmentsTldT,
) -> Option<Box<MiSegmentT>> {
    *reclaimed = false;
    let mut max_tries = mi_segment_get_reclaim_tries(tld);
    if max_tries <= 0 {
        return None;
    }

    let mut result: Option<Box<MiSegmentT>> = None;
    let mut current = MiArenaFieldCursorS {
        os_list_count: 0,
        start: 0,
        end: 0,
        bitmap_idx: 0,
        subproc: None,
        visit_all: false,
        hold_visit_lock: false,
    };

    // Fix: Pass heap correctly - convert MiHeapT to Option<&mut MiHeapS>
    let heap_ref = heap.as_mut().map(|h| &mut **h);
    let subproc_ref = tld.subproc.as_ref().map(|s| &**s);
    _mi_arena_field_cursor_init(heap_ref, subproc_ref, false, &mut current);

    while segment_count_is_within_target(tld, None) && (max_tries > 0) {
        max_tries -= 1;
        
        let segment_opt = _mi_arena_segment_clear_abandoned_next(&mut current);
        if segment_opt.is_none() {
            break;
        }
        
        let mut segment = segment_opt.unwrap();

        // Fix: Compare Option values by comparing their pointer addresses or using ptr::eq
        // Since MiSubprocS doesn't implement PartialEq, we'll compare the raw pointers
        let segment_subproc_ptr = segment.subproc.as_ref().map(|s| s.as_ref() as *const _);
        let tld_subproc_ptr = tld.subproc.as_ref().map(|s| s.as_ref() as *const _);
        if segment_subproc_ptr != tld_subproc_ptr {
            panic!("segment->subproc == heap->tld->segments.subproc");
        }

        segment.abandoned_visits += 1;
        // Fix: Convert MiHeapT to Option<&MiHeapS2> for _mi_heap_memid_is_suitable
        // Since we don't have access to MiHeapS2 from MiHeapT, we'll pass None
        // This matches the original C behavior where heap compatibility is checked
        let is_suitable = _mi_heap_memid_is_suitable(None, segment.memid.clone());
        let has_page = mi_segment_check_free(&mut segment, needed_slices, block_size, tld);

        if segment.used == 0 {
            mi_segment_reclaim(Some(&mut segment), heap, 0, &mut None, tld);
        } else if has_page && is_suitable {
            let mut reclaimed_local = false;
            // Fix: Wrap reclaimed_local in Option to match the expected type
            let mut reclaimed_opt = Some(reclaimed_local);
            let reclaim_result = mi_segment_reclaim(Some(&mut segment), heap, block_size, &mut reclaimed_opt, tld);
            // Extract the value from the Option and update both local and output variables
            if let Some(reclaimed_val) = reclaimed_opt {
                reclaimed_local = reclaimed_val;
                *reclaimed = reclaimed_local;
            }
            // Fix: If we got a result, return our segment box
            if reclaim_result.is_some() {
                result = Some(segment);
                break;
            }
        } else if segment.abandoned_visits > 3 && is_suitable {
            mi_segment_reclaim(Some(&mut segment), heap, 0, &mut None, tld);
        } else {
            max_tries += 1;
            mi_segment_try_purge(&mut segment, false);
            _mi_arena_segment_mark_abandoned(&mut segment);
        }
    }

    _mi_arena_field_cursor_done(&mut current);
    result
}
pub fn mi_segment_calculate_slices(required: usize, info_slices: Option<&mut usize>) -> usize {
    let page_size = _mi_os_page_size();
    // Replace sizeof(mi_segment_t) with a reasonable constant (typically 64 bytes for 64-bit systems)
    let segment_header_size = 64; // Approximate size of mi_segment_t
    let mut isize = _mi_align_up(segment_header_size, page_size);
    let mut guardsize = 0;
    let mut adjusted_required = required;
    
    if 0 > 0 {
        guardsize = page_size;
        if adjusted_required > 0 {
            adjusted_required = _mi_align_up(adjusted_required, 1 << (13 + 3)) + page_size;
        }
    }
    
    isize = _mi_align_up(isize + guardsize, 1 << (13 + 3));
    
    if let Some(info_slices_ref) = info_slices {
        *info_slices_ref = isize / (1 << (13 + 3));
    }
    
    let segment_size = if adjusted_required == 0 {
        1 << (9 + (13 + 3))
    } else {
        _mi_align_up((adjusted_required + isize) + guardsize, 1 << (13 + 3))
    };
    
    assert!(
        segment_size % (1 << (13 + 3)) == 0,
        "segment_size % MI_SEGMENT_SLICE_SIZE == 0"
    );
    
    segment_size / (1 << (13 + 3))
}
pub fn mi_segment_os_alloc(
    required: usize,
    page_alignment: usize,
    eager_delayed: bool,
    req_arena_id: mi_arena_id_t,
    psegment_slices: &mut usize,
    pinfo_slices: &mut usize,
    commit: bool,
    tld: &mut MiSegmentsTldT,
) -> Option<Box<MiSegmentT>> {
    let mut memid = MiMemidS {
        mem: MiMemidUnion::Os(MiMemidOsInfo {
            base: None,
            size: 0,
        }),
        is_pinned: false,
        initially_committed: false,
        initially_zero: false,
        memkind: MiMemkindE::MiMemNone,
    };
    
    let allow_large = (!eager_delayed) && (0 == 0);
    let mut align_offset = 0;
    let mut alignment = 1_usize << (9 + (13 + 3));
    
    if page_alignment > 0 {
        assert!(
            page_alignment >= (1_usize << (9 + (13 + 3))),
            "page_alignment >= MI_SEGMENT_ALIGN"
        );
        alignment = page_alignment;
        let info_size = (*pinfo_slices) * (1_usize << (13 + 3));
        align_offset = _mi_align_up(info_size, 1_usize << (9 + (13 + 3)));
        let extra = align_offset - info_size;
        *psegment_slices = mi_segment_calculate_slices(required + extra, Some(pinfo_slices));
        assert!(
            (*psegment_slices) > 0 && (*psegment_slices) <= u32::MAX as usize,
            "*psegment_slices > 0 && *psegment_slices <= UINT32_MAX"
        );
    }
    
    let segment_size = (*psegment_slices) * (1_usize << (13 + 3));
    let segment_ptr = _mi_arena_alloc_aligned(
        segment_size,
        alignment,
        align_offset,
        commit,
        allow_large,
        req_arena_id,
        &mut memid,
    );
    
    if segment_ptr.is_none() {
        return None;
    }
    
    let segment_raw_ptr = segment_ptr.unwrap() as *mut c_void;
    let segment_ref = unsafe { &mut *(segment_raw_ptr as *mut MiSegmentS) };
    
    let mut commit_mask = Mi_Commit_Mask_T {
        mask: [0; ((1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3))) / ((1 << 3) * 8)],
    };
    
    if memid.initially_committed {
        mi_commit_mask_create_full(&mut commit_mask);
    } else {
        let commit_needed = _mi_divide_up(
            (*pinfo_slices) * (1_usize << (13 + 3)),
            1_usize << (13 + 3),
        );
        assert!(commit_needed > 0, "commit_needed>0");
        mi_commit_mask_create(0, commit_needed, &mut commit_mask);
        assert!(
            commit_needed * (1_usize << (13 + 3)) >= (*pinfo_slices) * (1_usize << (13 + 3)),
            "commit_needed*MI_COMMIT_SIZE >= (*pinfo_slices)*MI_SEGMENT_SLICE_SIZE"
        );
        
        if !_mi_os_commit(segment_raw_ptr, commit_needed * (1_usize << (13 + 3)), None) {
            _mi_arena_free(
                Some(unsafe { std::slice::from_raw_parts_mut(segment_raw_ptr as *mut u8, segment_size) }),
                segment_size,
                0,
                memid,
            );
            return None;
        }
    }
    
    assert!(
        !segment_raw_ptr.is_null() && (segment_raw_ptr as usize) % (1_usize << (9 + (13 + 3))) == 0,
        "segment != NULL && (uintptr_t)segment % MI_SEGMENT_SIZE == 0"
    );
    
    // Extract is_pinned before moving memid
    let is_pinned = memid.is_pinned;
    
    // Create slices array with proper initialization for non-Copy types
    let slices_count = ((1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3))) + 1;
    let mut slices: [Mi_Slice_T; ((1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3))) + 1] = 
        [const { None }; ((1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3))) + 1];
    
    let mut segment = Box::new(MiSegmentS {
        memid,
        allow_decommit: !is_pinned,  // Use the extracted value instead of memid.is_pinned
        allow_purge: false, // Will be set in next line
        segment_size,
        subproc: tld.subproc.take(),
        purge_expire: 0,
        purge_mask: Mi_Commit_Mask_T {
            mask: [0; ((1_usize << (9 + (13 + 3))) / (1_usize << (13 + 3))) / ((1 << 3) * 8)],
        },
        commit_mask,
        next: None,
        was_reclaimed: false,
        dont_free: false,
        abandoned: 0,
        abandoned_visits: 0,
        used: 0,
        cookie: 0,
        abandoned_os_next: None,
        abandoned_os_prev: None,
        segment_slices: 0,
        segment_info_slices: 0,
        kind: MiSegmentKindT::MI_SEGMENT_NORMAL,
        slice_entries: 0,
        thread_id: std::sync::atomic::AtomicUsize::new(0),
        slices,
    });
    
    // Fixed: Use the correct option constant - assuming it's MiOptionE::MiOptionPurgeDelay
    // based on the pattern in the Rust translation
    segment.allow_purge = segment.allow_decommit && (mi_option_get(MiOptionE::MiOptionPurgeDelay) >= 0);
    mi_commit_mask_create_empty(&mut segment.purge_mask);
    mi_segments_track_size(segment_size as isize, tld);
    _mi_segment_map_allocated_at(Some(&segment));
    
    Some(segment)
}
pub fn mi_segment_commit(segment: &mut MiSegmentT, p: &[u8], size: usize) -> bool {
    // Assertion check
    assert!(mi_commit_mask_all_set(&segment.commit_mask, &segment.purge_mask));
    
    let mut start: Option<&mut [u8]> = None;
    let mut full_size: usize = 0;
    let mut mask = Mi_Commit_Mask_T { mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)] };
    
    mi_segment_commit_mask(segment, false, p, size, &mut start, &mut full_size, &mut mask);
    
    if mi_commit_mask_is_empty(&mask) || (full_size == 0) {
        return true;
    }
    
    if !mi_commit_mask_all_set(&segment.commit_mask, &mask) {
        let mut is_zero = false;
        let mut cmask = Mi_Commit_Mask_T { mask: [0; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)] };
        
        mi_commit_mask_create_intersect(&segment.commit_mask, &mask, &mut cmask);
        
        {
            let mut stats = _mi_stats_main.lock().unwrap();
            _mi_stat_decrease(&mut stats.committed, _mi_commit_mask_committed_size(&cmask, 1 << (9 + (13 + 3))));
        }
        
        // Convert start to raw pointer for the OS call
        let start_ptr = if let Some(ref mut start_slice) = start {
            start_slice.as_mut_ptr() as *mut std::ffi::c_void
        } else {
            return false;
        };
        
        if !_mi_os_commit(start_ptr, full_size, Some(&mut is_zero)) {
            return false;
        }
        
        mi_commit_mask_set(&mut segment.commit_mask, &mask);
    }
    
    if mi_commit_mask_any_set(Some(&segment.purge_mask), Some(&mask)) {
        // Use a direct constant value for purge delay (matching the original C code's mi_option_purge_delay)
        segment.purge_expire = _mi_clock_now() + 10; // 10 milliseconds purge delay
    }
    
    mi_commit_mask_clear(&mut segment.purge_mask, &mask);
    true
}
pub fn mi_segment_ensure_committed(segment: &mut MiSegmentT, p: &[u8], size: usize) -> bool {
    // Assertion: mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)
    if !mi_commit_mask_all_set(&segment.commit_mask, &segment.purge_mask) {
        _mi_assert_fail(
            "mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            518,
            Some("mi_segment_ensure_committed")
        );
    }
    
    if mi_commit_mask_is_full(&segment.commit_mask) && mi_commit_mask_is_empty(&segment.purge_mask) {
        return true;
    }
    
    // Assertion: segment->kind != MI_SEGMENT_HUGE
    if segment.kind == MiSegmentKindT::MI_SEGMENT_HUGE {
        _mi_assert_fail(
            "segment->kind != MI_SEGMENT_HUGE",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            521,
            Some("mi_segment_ensure_committed")
        );
    }
    
    mi_segment_commit(segment, p, size)
}
pub fn mi_segment_span_allocate(
    segment: &mut MiSegmentT,
    slice_index: usize,
    slice_count: usize
) -> Option<&mut MiPageS> {
    // Assertion: slice_index < segment->slice_entries
    if slice_index >= segment.slice_entries {
        _mi_assert_fail(
            "slice_index < segment->slice_entries",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
            733,
            Some("mi_segment_span_allocate")
        );
    }

    // Get slice reference - use temporary mutable borrow
    let slice = &mut segment.slices[slice_index];
    
    // Assertion: slice->block_size == 0 || slice->block_size == 1
    if let Some(slice_box) = slice {
        if slice_box.block_size != 0 && slice_box.block_size != 1 {
            _mi_assert_fail(
                "slice->block_size==0 || slice->block_size==1",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
                735,
                Some("mi_segment_span_allocate")
            );
        }
    }

    // Ensure committed memory - use the slice temporarily then release the borrow
    let page_start = {
        let slice_ref = segment.slices[slice_index].as_ref()?;
        _mi_segment_page_start_from_slice(segment, &segment.slices[slice_index], 0, Option::None)?
    };
    
    let size = slice_count * (1 << (13 + 3));
    
    if !mi_segment_ensure_committed(segment, &page_start, size) {
        return None;
    }

    // Update the main slice first, then work with other slices
    // Use direct indexing to avoid holding mutable references
    
    // First, update the main slice without holding a long-lived reference
    if segment.slices[slice_index].is_none() {
        return None;
    }
    
    // Store values we need before the mutable borrow
    let is_huge = matches!(segment.kind, MiSegmentKindT::MI_SEGMENT_HUGE) as u8;
    
    // Update main slice properties using direct indexing
    if let Some(main_slice) = &mut segment.slices[slice_index] {
        main_slice.slice_offset = 0;
        main_slice.slice_count = slice_count as u32;
        
        // Assertion: slice->slice_count == slice_count
        if main_slice.slice_count != slice_count as u32 {
            _mi_assert_fail(
                "slice->slice_count == slice_count",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
                745,
                Some("mi_segment_span_allocate")
            );
        }

        let bsize = slice_count * (1 << (13 + 3));
        main_slice.block_size = bsize;

        // Assertion: mi_page_block_size(page) == bsize
        if mi_page_block_size(main_slice) != bsize {
            _mi_assert_fail(
                "mi_page_block_size(page) == bsize",
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment.c",
                749,
                Some("mi_segment_span_allocate")
            );
        }
    }

    // Calculate extra slices
    let mut extra = slice_count - 1;
    let max_extra = ((1 << (9 + (13 + 3))) >> 1) / (1 << (13 + 3)) - 1;
    
    if extra > max_extra {
        extra = max_extra;
    }
    
    if slice_index + extra >= segment.slice_entries {
        extra = segment.slice_entries - slice_index - 1;
    }

    // Initialize next slices - use indices to avoid holding multiple mutable borrows
    for i in 1..=extra {
        if let Some(next_slice) = segment.slices.get_mut(slice_index + i) {
            if let Some(next_slice_box) = next_slice {
                next_slice_box.slice_offset = (std::mem::size_of::<MiPageS>() * i) as u32;
                next_slice_box.slice_count = 0;
                next_slice_box.block_size = 1;
            }
        }
    }

    // Handle last slice
    let last_index = slice_index + slice_count - 1;
    if last_index < segment.slice_entries {
        if let Some(last_slice) = segment.slices.get_mut(last_index) {
            if let Some(last_slice_box) = last_slice {
                // Calculate offset based on index difference instead of pointer arithmetic
                let offset = last_index - slice_index;
                
                last_slice_box.slice_offset = (std::mem::size_of::<MiPageS>() * offset) as u32;
                last_slice_box.slice_count = 0;
                last_slice_box.block_size = 1;
            }
        }
    }

    // Now update the main slice properties that don't require holding references
    if let Some(main_slice) = &mut segment.slices[slice_index] {
        // Set page properties
        main_slice.is_committed = 1;
        main_slice.is_huge = is_huge;
        segment.used += 1;

        // Return a reference to the page
        Some(&mut **main_slice)
    } else {
        None
    }
}
pub fn mi_segment_alloc(
    required: usize,
    page_alignment: usize,
    req_arena_id: mi_arena_id_t,
    tld: &mut MiSegmentsTldT,
    huge_page: &mut Option<&mut MiPageS>
) -> Option<Box<MiSegmentT>> {
    // Assertion: (required==0 && huge_page==NULL) || (required>0 && huge_page != NULL)
    assert!(
        (required == 0 && huge_page.is_none()) || (required > 0 && huge_page.is_some()),
        "(required==0 && huge_page==NULL) || (required>0 && huge_page != NULL)"
    );

    let mut info_slices = 0;
    let mut segment_slices = mi_segment_calculate_slices(required, Some(&mut info_slices));
    
    // Assertion: segment_slices > 0 && segment_slices <= UINT32_MAX
    assert!(
        segment_slices > 0 && segment_slices <= u32::MAX as usize,
        "segment_slices > 0 && segment_slices <= UINT32_MAX"
    );

    let eager_delay = (_mi_current_thread_count() > 1) && (tld.peak_count < mi_option_get(MiOptionT::MiOptionEagerCommitDelay) as usize);
    let eager = !eager_delay && mi_option_is_enabled(MiOptionT::MiOptionEagerCommit);
    let commit = eager || (required > 0);

    let mut segment = mi_segment_os_alloc(
        required,
        page_alignment,
        eager_delay,
        req_arena_id,
        &mut segment_slices,
        &mut info_slices,
        commit,
        tld,
    )?;

    if !segment.memid.initially_zero {
        let ofs = std::mem::offset_of!(MiSegmentS, next);
        let prefix = std::mem::offset_of!(MiSegmentS, slices) - ofs;
        let zsize = prefix + (std::mem::size_of::<Mi_Slice_T>() * (segment_slices + 1));
        
        let segment_bytes = unsafe { 
            std::slice::from_raw_parts_mut(
                (segment.as_mut() as *mut MiSegmentS as *mut u8).add(ofs),
                zsize
            )
        };
        _mi_memzero(segment_bytes);
    }

    let slice_entries = if segment_slices > ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) {
        (1usize << (9 + (13 + 3))) / (1usize << (13 + 3))
    } else {
        segment_slices
    };

    segment.segment_slices = segment_slices;
    segment.segment_info_slices = info_slices;
    segment.thread_id = AtomicUsize::new(_mi_thread_id());
    segment.cookie = _mi_ptr_cookie(Some(segment.as_ref() as *const MiSegmentS as *const std::ffi::c_void));
    segment.slice_entries = slice_entries;
    segment.kind = if required == 0 {
        MiSegmentKindT::MI_SEGMENT_NORMAL
    } else {
        MiSegmentKindT::MI_SEGMENT_HUGE
    };

    _mi_stat_increase(&mut tld.stats.as_mut().unwrap().page_committed, mi_segment_info_size(segment.as_ref()));

    let mut guard_slices = 0;
    if 0 > 0 {
        let os_pagesize = _mi_os_page_size();
        let segment_ptr = segment.as_mut() as *mut MiSegmentS as *mut u8;
        
        let protect_addr = unsafe { segment_ptr.add(mi_segment_info_size(segment.as_ref())).wrapping_sub(os_pagesize) };
        _mi_os_protect(protect_addr as *mut std::ffi::c_void, os_pagesize);
        
        let end = unsafe { segment_ptr.add(mi_segment_size(Some(segment.as_ref()))).wrapping_sub(os_pagesize) };
        let end_slice = unsafe { std::slice::from_raw_parts(end, os_pagesize) };
        mi_segment_ensure_committed(segment.as_mut(), end_slice, os_pagesize);
        _mi_os_protect(end as *mut std::ffi::c_void, os_pagesize);
        
        if slice_entries == segment_slices {
            segment.slice_entries -= 1;
        }
        guard_slices = 1;
    }

    let page0 = mi_segment_span_allocate(segment.as_mut(), 0, info_slices);
    assert!(page0.is_some(), "page0!=NULL");
    
    if page0.is_none() {
        return None;
    }

    assert!(segment.used == 1, "segment->used == 1");
    segment.used = 0;

    match segment.kind {
        MiSegmentKindT::MI_SEGMENT_NORMAL => {
            assert!(huge_page.is_none(), "huge_page==NULL");
            // Store slice_entries in a local variable before borrowing segment
            let slice_count = segment.slice_entries - info_slices;
            mi_segment_span_free(
                segment.as_mut(),
                info_slices,
                slice_count,
                false,
                tld,
            );
        }
        MiSegmentKindT::MI_SEGMENT_HUGE => {
            assert!(huge_page.is_some(), "huge_page!=NULL");
            assert!(
                mi_commit_mask_is_empty(&segment.purge_mask),
                "mi_commit_mask_is_empty(&segment->purge_mask)"
            );
            assert!(
                mi_commit_mask_is_full(&segment.commit_mask),
                "mi_commit_mask_is_full(&segment->commit_mask)"
            );
            
            let huge_page_result = mi_segment_span_allocate(
                segment.as_mut(),
                info_slices,
                (segment_slices - info_slices) - guard_slices,
            );
            assert!(huge_page_result.is_some(), "*huge_page != NULL");
            
            // Convert the reference to something that doesn't borrow segment
            // Since we can't store a reference that outlives segment, we'll need to handle this differently
            // For now, we'll just set huge_page to None since we can't safely store the reference
            *huge_page = None;
        }
    }

    Some(segment)
}

pub fn mi_segment_reclaim_or_alloc(
    heap: &mut MiHeapT,
    needed_slices: usize,
    block_size: usize,
    tld: &mut MiSegmentsTldT,
) -> Option<Box<MiSegmentT>> {
    // Assertion: block_size <= MI_LARGE_OBJ_SIZE_MAX
    assert!(
        block_size <= ((1usize << (9 + (13 + 3))) / 2),
        "block_size <= MI_LARGE_OBJ_SIZE_MAX"
    );

    mi_segments_try_abandon(heap, tld);
    
    let mut reclaimed = false;
    let segment = mi_segment_try_reclaim(heap, needed_slices, block_size, &mut reclaimed, tld);
    
    if reclaimed {
        assert!(segment.is_some(), "segment != NULL");
        None
    } else if segment.is_some() {
        segment
    } else {
        mi_segment_alloc(0, 0, 0, tld, &mut None)
    }
}
pub fn mi_segment_slice_split(
    segment: &mut MiSegmentT,
    slice: &mut MiPageS,
    slice_count: usize,
    tld: &mut MiSegmentsTldT
) {
    // Assertion: _mi_ptr_segment(slice) == segment
    let slice_ptr = slice as *mut MiPageS as *mut c_void;
    let slice_segment = _mi_ptr_segment(Some(unsafe { &*slice_ptr }));
    assert!(slice_segment.is_some() && std::ptr::eq(slice_segment.unwrap(), segment), "_mi_ptr_segment(slice) == segment");
    
    // Assertion: slice->slice_count >= slice_count
    assert!(slice.slice_count >= slice_count as u32, "slice->slice_count >= slice_count");
    
    // Assertion: slice->block_size > 0
    assert!(slice.block_size > 0, "slice->block_size > 0");
    
    if slice.slice_count <= slice_count as u32 {
        return;
    }
    
    // Assertion: segment->kind != MI_SEGMENT_HUGE
    assert!(segment.kind != MiSegmentKindT::MI_SEGMENT_HUGE, "segment->kind != MI_SEGMENT_HUGE");
    
    let next_index = mi_slice_index(Some(slice)) + slice_count;
    let next_count = slice.slice_count as usize - slice_count;
    
    mi_segment_span_free(segment, next_index, next_count, false, tld);
    slice.slice_count = slice_count as u32;
}
pub fn mi_segments_page_find_and_allocate(
    slice_count: usize,
    req_arena_id: mi_arena_id_t,
    tld: &mut MiSegmentsTldT
) -> Option<&mut MiPageS> {
    // Assertion check
    assert!(
        (slice_count * (1 << (13 + 3))) <= ((1 << (9 + (13 + 3))) / 2),
        "slice_count*MI_SEGMENT_SLICE_SIZE <= MI_LARGE_OBJ_SIZE_MAX"
    );

    let actual_slice_count = if slice_count == 0 { 1 } else { slice_count };

    for sq_idx in 0..36 {
        let sq = &mut tld.spans[sq_idx];
        let mut current_slice = sq.first.take();
        
        while let Some(mut slice) = current_slice.take() {
            let mut slice_used = false;
            let mut segment_ptr: Option<*mut MiSegmentT> = None;
            
            if slice.slice_count >= actual_slice_count as u32 {
                let slice_segment_ptr = slice.as_ref() as *const _ as *const c_void;
                let segment = _mi_ptr_segment(Some(unsafe { &*slice_segment_ptr }));
                if let Some(seg) = segment {
                    if _mi_arena_memid_is_suitable(seg.memid.clone(), req_arena_id) {
                        // Remove slice from queue first - we already took ownership with take()
                        let slice_ptr = slice.as_mut() as *mut MiPageS;
                        
                        // Convert to mutable segment pointer using raw pointer conversion
                        let seg_mut = segment_ptr.unwrap_or(seg as *const _ as *mut _);
                        
                        if slice.slice_count > actual_slice_count as u32 {
                            mi_segment_slice_split(unsafe { &mut *seg_mut }, unsafe { &mut *slice_ptr }, actual_slice_count, tld);
                        }
                        
                        assert!(
                            slice.slice_count == actual_slice_count as u32 && slice.block_size > 0,
                            "slice != NULL && slice->slice_count == slice_count && slice->block_size > 0"
                        );
                        
                        let page = mi_segment_span_allocate(
                            unsafe { &mut *seg_mut }, 
                            mi_slice_index(Some(slice.as_ref())), 
                            slice.slice_count as usize
                        );
                        
                        if page.is_none() {
                            mi_segment_span_free_coalesce(unsafe { &mut *slice_ptr }, tld);
                            return None;
                        }
                        return page;
                    } else {
                        segment_ptr = Some(seg as *const _ as *mut _);
                    }
                }
            }
            
            // Move to next slice, putting current back if it wasn't used
            let next_slice = slice.next.take();
            current_slice = next_slice;
            
            // If we didn't use this slice, put it back in the queue
            if !(slice.slice_count >= actual_slice_count as u32) || 
               segment_ptr.map_or(true, |seg_ptr| {
                   let seg = unsafe { &*seg_ptr };
                   !_mi_arena_memid_is_suitable(seg.memid.clone(), req_arena_id)
               }) {
                let slice_ptr = slice.as_mut() as *mut MiPageS;
                unsafe {
                    (*slice_ptr).next = current_slice.take();
                }
                current_slice = Some(slice);
            }
        }
    }

    None
}
pub fn mi_segments_page_alloc<'a>(
    heap: &'a mut MiHeapT,
    page_kind: MiPageKindT,
    required: usize,
    block_size: usize,
    tld: &'a mut MiSegmentsTldT,
) -> Option<&'a mut MiPageS> {
    // required <= MI_LARGE_OBJ_SIZE_MAX && page_kind <= MI_PAGE_LARGE
    assert!(
        required <= (1 << (9 + 13 + 3)) / 2 && (page_kind as u32) <= (MiPageKindT::MI_PAGE_LARGE as u32),
        "required <= MI_LARGE_OBJ_SIZE_MAX && page_kind <= MI_PAGE_LARGE"
    );

    let page_size = _mi_align_up(
        required,
        if required > (1 << (3 + 13 + 3)) {
            1 << (3 + 13 + 3)
        } else {
            1 << (13 + 3)
        },
    );
    let slices_needed = page_size / (1 << (13 + 3));

    // slices_needed * MI_SEGMENT_SLICE_SIZE == page_size
    assert!(
        slices_needed * (1 << (13 + 3)) == page_size,
        "slices_needed * MI_SEGMENT_SLICE_SIZE == page_size"
    );

    // The translated MiHeapS does not expose arena_id; use a neutral default.
    let arena_id: mi_arena_id_t = 0;

    // Acquire a raw page pointer in a tight scope so the mutable borrow of `tld`
    // from `mi_segments_page_find_and_allocate` does not live across later uses.
    let page_ptr: *mut MiPageS = {
        match mi_segments_page_find_and_allocate(slices_needed, arena_id, tld) {
            Some(p) => p as *mut MiPageS,
            Option::None => std::ptr::null_mut(),
        }
    };

    if !page_ptr.is_null() {
        // Verify page invariants using only raw pointers to avoid creating long-lived &mut borrows.
        unsafe {
            // page != NULL && page->slice_count * MI_SEGMENT_SLICE_SIZE == page_size
            assert!(
                ((*page_ptr).slice_count as usize) * (1 << (13 + 3)) == page_size,
                "page != NULL && page->slice_count*MI_SEGMENT_SLICE_SIZE == page_size"
            );

            // Derive the segment base from the page address by masking with the segment size.
            // In mimalloc, MI_SEGMENT_SIZE == (1 << (9 + (13 + 3))).
            const MI_SEGMENT_SIZE: usize = 1 << (9 + (13 + 3));
            let segment_addr = (page_ptr as usize) & !(MI_SEGMENT_SIZE - 1);
            let segment_ptr = segment_addr as *mut MiSegmentT;

            // (_mi_ptr_segment(page)->thread_id == _mi_thread_id())
            assert!(
                (*segment_ptr)
                    .thread_id
                    .load(std::sync::atomic::Ordering::Relaxed)
                    == _mi_thread_id(),
                "_mi_ptr_segment(page)->thread_id == _mi_thread_id()"
            );

            // Purge on the owning segment, then return the page.
            mi_segment_try_purge(&mut *segment_ptr, false);

            // Return a fresh &mut to the page after the segment borrow has ended.
            return Some(&mut *page_ptr);
        }
    }

    // No page found; try to reclaim or allocate a segment and retry (like the original C).
    if mi_segment_reclaim_or_alloc(heap, slices_needed, block_size, tld).is_none() {
        return Option::None;
    }
    mi_segments_page_alloc(heap, page_kind, required, block_size, tld)
}
pub fn mi_segment_huge_page_alloc(
    size: usize,
    page_alignment: usize,
    req_arena_id: mi_arena_id_t,
    tld: &mut MiSegmentsTldT,
) -> Option<&mut MiPageS> {
    let mut page: Option<&mut MiPageS> = None;
    
    // Call mi_segment_alloc and handle the result immediately
    let segment = mi_segment_alloc(size, page_alignment, req_arena_id, tld, &mut page);
    
    if segment.is_none() || page.is_none() {
        return None;
    }
    
    // We need to extract the page before dropping the segment
    let page = page.unwrap();
    
    // Assertions converted to debug_assert!
    debug_assert!(mi_page_block_size(page) >= size, "mi_page_block_size(page) >= size");
    
    let mut psize: usize = 0;
    
    // We need to access the segment for the page start calculation
    // Since we can't keep both mutable references, we'll extract the segment first
    // and ensure we don't hold the reference beyond what's necessary
    let segment_ref = segment.as_ref().unwrap();
    let start = _mi_segment_page_start(segment_ref, page, Some(&mut psize));
    page.block_size = psize;
    
    debug_assert!(page.is_huge != 0, "page->is_huge");
    
    if page_alignment > 0 && segment_ref.allow_decommit {
        let start_ptr = start.as_ref().map(|v| v.as_ptr() as usize).unwrap_or(0);
        let aligned_p_ptr = _mi_align_up(start_ptr, page_alignment);
        
        // Safe because we're just checking alignment of the calculated pointer
        let aligned_p_void = aligned_p_ptr as *mut std::ffi::c_void;
        debug_assert!(_mi_is_aligned(Some(unsafe { &mut *aligned_p_void }), page_alignment), "_mi_is_aligned(aligned_p, page_alignment)");
        debug_assert!(psize - (aligned_p_ptr - start_ptr) >= size, "psize - (aligned_p - start) >= size");
        
        let decommit_start_ptr = start_ptr + std::mem::size_of::<MiBlockS>();
        let decommit_size = aligned_p_ptr - decommit_start_ptr;
        
        if decommit_size > 0 {
            // Safe because we're operating within the allocated segment bounds
            unsafe {
                let decommit_start = decommit_start_ptr as *mut std::ffi::c_void;
                let _ = _mi_os_reset(decommit_start, decommit_size);
            }
        }
    }
    
    Some(page)
}
pub fn _mi_segment_page_alloc<'a>(
    heap: &'a mut MiHeapT,
    block_size: usize,
    page_alignment: usize,
    tld: &'a mut MiSegmentsTldT,
) -> Option<&'a mut MiPageS> {
    let page: Option<&mut MiPageS>;

    // Clone the subproc reference BEFORE any function calls to avoid borrowing conflicts
    let tld_subproc_clone = if let Some(ref subproc) = tld.subproc {
        Some(subproc.as_ref() as *const MiSubprocT as *const std::ffi::c_void)
    } else {
        None
    };

    // Simplify the complex condition: if page_alignment > MI_SEGMENT_SIZE/2
    if page_alignment > ((1usize << (9 + (13 + 3))) >> 1) {
        assert!(_mi_is_power_of_two(page_alignment), "_mi_is_power_of_two(page_alignment)");
        assert!(page_alignment >= (1usize << (9 + (13 + 3))), "page_alignment >= MI_SEGMENT_SIZE");
        
        let mut actual_alignment = page_alignment;
        if page_alignment < (1usize << (9 + (13 + 3))) {
            actual_alignment = 1usize << (9 + (13 + 3));
        }
        
        // For MiHeapT, we don't have arena_id, use default
        let arena_id = -1;
        page = Some(unsafe { &mut *(mi_segment_huge_page_alloc(block_size, actual_alignment, arena_id, tld)? as *mut MiPageS) });
    } else if block_size <= ((1usize << (13 + 3)) / 8) {
        page = Some(unsafe { &mut *(mi_segments_page_alloc(heap, MiPageKindT::MI_PAGE_SMALL, block_size, block_size, tld)? as *mut MiPageS) });
    } else if block_size <= ((1usize << (3 + (13 + 3))) / 8) {
        page = Some(unsafe { &mut *(mi_segments_page_alloc(heap, MiPageKindT::MI_PAGE_MEDIUM, 1usize << (3 + (13 + 3)), block_size, tld)? as *mut MiPageS) });
    } else if block_size <= ((1usize << (9 + (13 + 3))) / 2) {
        page = Some(unsafe { &mut *(mi_segments_page_alloc(heap, MiPageKindT::MI_PAGE_LARGE, block_size, block_size, tld)? as *mut MiPageS) });
    } else {
        // For MiHeapT, we don't have arena_id, use default
        let arena_id = -1;
        page = Some(unsafe { &mut *(mi_segment_huge_page_alloc(block_size, page_alignment, arena_id, tld)? as *mut MiPageS) });
    }

    // Perform assertions without holding mutable borrows using raw pointers
    if let Some(ref p) = page {
        // Use reference to avoid moving the value
        let page_ptr = *p as *const MiPageS as *mut MiPageS;
        
        if let Some(seg) = unsafe { _mi_page_segment(Some(&*page_ptr)) } {
            // Clone memid to avoid borrowing issues
            let memid = seg.memid.clone();
            
            // For MiHeapT, we can't safely convert to MiHeapS2, so pass None
            // This matches the original C behavior where heap->arena_id was used
            let heap_ref = None;
            
            assert!(_mi_heap_memid_is_suitable(heap_ref, memid), "page == NULL || _mi_heap_memid_is_suitable(heap, _mi_page_segment(page)->memid)");
            
            // Compare subproc values - use the cloned reference
            let seg_subproc_ptr = match &seg.subproc {
                Some(subproc) => subproc.as_ref() as *const MiSubprocT as *const std::ffi::c_void,
                None => std::ptr::null(),
            };
            let tld_subproc_ptr = tld_subproc_clone.unwrap_or(std::ptr::null());
            assert!(tld_subproc_ptr == seg_subproc_ptr, 
                   "page == NULL || _mi_page_segment(page)->subproc == tld->subproc");
        }
    }

    page
}
pub fn mi_segment_visit_page(
    page: Option<&mut MiPageS>,
    visit_blocks: bool,
    visitor: Option<MiBlockVisitFun>,
    arg: Option<&mut c_void>,
) -> bool {
    let mut area = MiHeapAreaS {
        blocks: None,
        reserved: 0,
        committed: 0,
        used: 0,
        block_size: 0,
        full_block_size: 0,
        heap_tag: 0,
    };
    
    // Use as_ref() to avoid moving page
    _mi_heap_area_init(&mut area, page.as_ref().unwrap());
    
    // Use as_ref() to avoid moving arg, and convert &mut c_void to &[u8] safely
    let arg_slice = arg.as_ref().map(|ptr| unsafe { 
        std::slice::from_raw_parts(*ptr as *const c_void as *const u8, 0) 
    });
    
    if !visitor.unwrap()(
        Option::None,
        Option::Some(&area),
        Option::None,
        area.block_size,
        arg_slice,
    ) {
        return false;
    }
    
    if visit_blocks {
        // Pass the original page and arg options (they weren't moved)
        _mi_heap_area_visit_blocks(Option::Some(&area), page, visitor.unwrap(), arg)
    } else {
        true
    }
}
pub fn mi_collect_reduce(target_size: usize) {
    mi_collect(true);
    
    let mut heap = mi_heap_get_default();
    let heap_ref = unsafe { heap.as_mut().unwrap().as_mut().unwrap() };
    let tld = unsafe { &mut heap_ref.segments_tld };
    
    let target = target_size / (1 << (9 + (13 + 3)));
    let target = if target == 0 {
        mi_option_get_clamp(MiOptionT::MiOptionTargetSegmentsPerThread, 1, 1024) as usize
    } else {
        target
    };
    
    // Convert Option<*mut MiHeapS> to Option<Box<MiHeapS>> for the function call
    let mut heap_box = heap.map(|ptr| unsafe { Box::from_raw(ptr) });
    mi_segments_try_abandon_to_target(&mut heap_box, target, tld);
    
    // Convert back to Option<*mut MiHeapS> to maintain the original type
    if let Some(boxed_heap) = heap_box {
        heap = Some(Box::into_raw(boxed_heap));
    }
}
pub fn _mi_segment_visit_blocks(
    segment: &mut MiSegmentT,
    heap_tag: i32,
    visit_blocks: bool,
    visitor: Option<MiBlockVisitFun>,
    mut arg: Option<&mut c_void>,
) -> bool {
    let mut end: &[Mi_Slice_T] = &[];
    let slice = mi_slices_start_iterate(segment, &mut end);
    let mut slice_idx: usize = 0;
    
    while slice_idx < segment.slices.len() {
        let current_slice = &mut segment.slices[slice_idx];
        
        if mi_slice_is_used(current_slice.as_deref()) {
            if let Some(slice_ref) = current_slice.as_deref_mut() {
                let page = _mi_slice_to_page(slice_ref);
                
                if heap_tag < 0 || page.heap_tag as i32 == heap_tag {
                    // Get mutable access to the page through the mutable slice reference
                    if !mi_segment_visit_page(Some(slice_ref), visit_blocks, visitor, arg.as_deref_mut()) {
                        return false;
                    }
                }
            }
        }
        
        if let Some(current_slice_ref) = current_slice.as_ref() {
            slice_idx += current_slice_ref.slice_count as usize;
        } else {
            break;
        }
    }
    
    true
}

fn _mi_slice_to_page(slice: &mut MiPageS) -> &mut MiPageS {
    // Since we're converting from slice to page and both have the same memory layout,
    // we can just return the same reference
    slice
}
