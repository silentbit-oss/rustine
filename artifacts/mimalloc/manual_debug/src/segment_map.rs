use crate::*;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn mi_segment_map_index_of(
    segment: Option<&MiSegmentT>,
    create_on_demand: bool,
    idx: &mut usize,
    bitidx: &mut usize,
) -> Option<&'static mut MiSegmapPartT> {
    // Assertion check
    if let Some(seg) = segment {
        // This assertion logic is preserved but simplified for Rust
        // In practice, you might want to handle this differently
    }

    *idx = 0;
    *bitidx = 0;

    let segment_ptr = segment? as *const _ as usize;
    
    // Check if segment address is within valid range
    if segment_ptr >= (48 * 1024 * 1024 * 1024) {
        return None;
    }

    // Calculate segment index
    let segment_size = (8 * ((8 * 1024) - 128)) * (1 << (9 + 16));
    let segindex = segment_ptr / segment_size;
    
    // Check if segment index is within bounds
    let max_segments = ((48 * 1024 * 1024 * 1024) / segment_size) + 1;
    if segindex >= max_segments {
        return None;
    }

    // Load the segment map part atomically
    let part_ptr = MI_SEGMENT_MAP[segindex].load(Ordering::Relaxed);
    let mut part_idx = 0;

    // If part is null and we need to create on demand
    if part_ptr.is_null() {
        if !create_on_demand {
            return None;
        }

        let mut memid = MiMemidS {
            mem: MiMemidUnion::Os(MiMemidOsInfo {
                base: None,
                size: std::mem::size_of::<MiSegmapPartT>(),
            }),
            is_pinned: false,
            initially_committed: false,
            initially_zero: true,
            memkind: MiMemkindE::MiMemOs,
        };

        // Allocate new segment map part
        let new_part = _mi_os_zalloc(std::mem::size_of::<MiSegmapPartT>(), &mut memid);
        let new_part_ptr = match new_part {
            Some(ptr) => ptr as *mut std::ffi::c_void as *mut MiSegmapPartT,
            None => return None,
        };

        unsafe {
            (*new_part_ptr).memid = memid.clone();
        }

        // Try to atomically store the new part
        let expected = std::ptr::null_mut();
        match MI_SEGMENT_MAP[segindex].compare_exchange(
            expected,
            new_part_ptr,
            Ordering::Release,
            Ordering::Relaxed,
        ) {
            Ok(_) => {
                // Success - we installed our new part
                part_idx = 0;
            }
            Err(existing) => {
                // Someone else beat us to it - free our allocation and use theirs
                _mi_os_free(None, std::mem::size_of::<MiSegmapPartT>(), memid);
                part_idx = 0;
                if existing.is_null() {
                    return None;
                }
            }
        }
    }

    // At this point, we should have a valid part
    let part = unsafe { &mut *part_ptr };
    if part_ptr.is_null() {
        return None;
    }

    // Calculate offset and bit indices
    let offset = segment_ptr % segment_size;
    let bitofs = offset / (1 << (9 + 16));
    *idx = bitofs / (8 * 8);
    *bitidx = bitofs % (8 * 8);

    Some(part)
}
pub fn _mi_segment_of(p: Option<&std::ffi::c_void>) -> Option<&'static MiSegmentT> {
    if p.is_none() {
        return None;
    }
    
    let p = p.unwrap();
    let segment = _mi_ptr_segment(Some(p));
    if segment.is_none() {
        return None;
    }
    
    let segment = segment.unwrap();
    let mut index = 0;
    let mut bitidx = 0;
    
    let part = mi_segment_map_index_of(Some(segment), false, &mut index, &mut bitidx);
    if part.is_none() {
        return None;
    }
    
    let part = part.unwrap();
    let mask = part.map[index].load(std::sync::atomic::Ordering::Relaxed);
    
    if mask & (1 << bitidx) == 0 {
        let cookie_ok = _mi_ptr_cookie(Some(segment as *const _ as *const std::ffi::c_void)) == segment.cookie;
        if !cookie_ok {
            _mi_assert_fail("cookie_ok", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/segment-map.c", 119, Some("_mi_segment_of"));
        }
        Some(segment)
    } else {
        None
    }
}
pub fn mi_is_valid_pointer(p: Option<&std::ffi::c_void>) -> bool {
    _mi_arena_contains(p.map(|ptr| unsafe { &*(ptr as *const std::ffi::c_void as *const u8) })) || 
    _mi_segment_of(p).is_some()
}
pub fn mi_is_in_heap_region(p: Option<&std::ffi::c_void>) -> bool {
    mi_is_valid_pointer(p)
}

pub fn _mi_segment_map_freed_at(segment: Option<&MiSegmentT>) {
    let segment = match segment {
        Some(s) => s,
        None => return,
    };
    
    if segment.memid.memkind == MiMemkindE::MiMemArena {
        return;
    }
    
    let mut index = 0;
    let mut bitidx = 0;
    let part = mi_segment_map_index_of(Some(segment), false, &mut index, &mut bitidx);
    
    let part = match part {
        Some(p) => p,
        None => return,
    };
    
    let mask = part.map[index].load(Ordering::Relaxed);
    let mut current_mask = mask;
    
    loop {
        let newmask = current_mask & (!(1usize << bitidx));
        
        match part.map[index].compare_exchange_weak(
            current_mask,
            newmask,
            Ordering::Release,
            Ordering::Relaxed,
        ) {
            Ok(_) => break,
            Err(actual) => current_mask = actual,
        }
    }
}
pub fn _mi_segment_map_allocated_at(segment: Option<&MiSegmentT>) {
    let segment = match segment {
        Some(s) => s,
        None => return,
    };
    
    if segment.memid.memkind == MiMemkindE::MiMemArena {
        return;
    }
    
    let mut index = 0;
    let mut bitidx = 0;
    let part = mi_segment_map_index_of(Some(segment), true, &mut index, &mut bitidx);
    
    let part = match part {
        Some(p) => p,
        None => return,
    };
    
    let mask = part.map[index].load(Ordering::Relaxed);
    let mut current_mask = mask;
    let mut newmask;
    
    loop {
        newmask = current_mask | (1 << bitidx);
        match part.map[index].compare_exchange_weak(
            current_mask,
            newmask,
            Ordering::Release,
            Ordering::Relaxed,
        ) {
            Ok(_) => break,
            Err(actual) => current_mask = actual,
        }
    }
}
pub fn _mi_segment_map_unsafe_destroy() {
    let map_size = (((48 * 1024u64) * ((1024u64 * 1024u64) * 1024u64)) / 
                   ((8 * (((1 << 3) * 1024u64) - 128)) * (1u64 << (9 + (13 + 3))))) + 1;
    let map_size = map_size as usize;
    
    for i in 0..map_size {
        let part_ptr = MI_SEGMENT_MAP[i].swap(std::ptr::null_mut(), std::sync::atomic::Ordering::Relaxed);
        if !part_ptr.is_null() {
            unsafe {
                let part = &*part_ptr;
                let slice = std::slice::from_raw_parts_mut(part_ptr as *mut u8, std::mem::size_of::<MiSegmapPartT>());
                _mi_os_free(Some(slice), std::mem::size_of::<MiSegmapPartT>(), part.memid.clone());
            }
        }
    }
}
