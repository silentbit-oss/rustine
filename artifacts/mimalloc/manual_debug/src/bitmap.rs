use crate::*;
use std::ptr;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn mi_bitmap_mask_(count: usize, bitidx: usize) -> usize {
    // Assertions translated to debug assertions
    debug_assert!(count + bitidx <= (8 * (1 << 3)), "count + bitidx <= MI_BITMAP_FIELD_BITS");
    debug_assert!(count > 0, "count > 0");

    if count >= (8 * (1 << 3)) {
        return !0; // Equivalent to ~((size_t)0) in C
    }
    if count == 0 {
        return 0;
    }
    
    ((1 << count) - 1) << bitidx
}
pub fn mi_bitmap_mask_across(
    bitmap_idx: mi_bitmap_index_t,
    bitmap_fields: usize,
    count: usize,
    pre_mask: &mut usize,
    mid_mask: &mut usize,
    post_mask: &mut usize
) -> usize {
    let bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
    let bits_per_field = 8 * (1 << 3);
    
    if (bitidx + count) <= bits_per_field {
        *pre_mask = mi_bitmap_mask_(count, bitidx);
        *mid_mask = 0;
        *post_mask = 0;
        assert!(mi_bitmap_index_field(bitmap_idx) < bitmap_fields, "mi_bitmap_index_field(bitmap_idx) < bitmap_fields");
        return 0;
    } else {
        let pre_bits = bits_per_field - bitidx;
        assert!(pre_bits < count, "pre_bits < count");
        *pre_mask = mi_bitmap_mask_(pre_bits, bitidx);
        let remaining_count = count - pre_bits;
        let mid_count = remaining_count / bits_per_field;
        *mid_mask = !0;
        let final_count = remaining_count % bits_per_field;
        *post_mask = if final_count == 0 { 0 } else { mi_bitmap_mask_(final_count, 0) };
        let total_fields = mi_bitmap_index_field(bitmap_idx) + mid_count + if final_count == 0 { 0 } else { 1 };
        assert!(total_fields < bitmap_fields, "mi_bitmap_index_field(bitmap_idx) + mid_count + (count==0 ? 0 : 1) < bitmap_fields");
        return mid_count;
    }
}
pub fn _mi_bitmap_claim_across(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: mi_bitmap_index_t,
    pany_zero: Option<&mut bool>,
    already_set: Option<&mut usize>
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let mut pre_mask: usize = 0;
    let mut mid_mask: usize = 0;
    let mut post_mask: usize = 0;
    let mut mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &mut pre_mask, &mut mid_mask, &mut post_mask);
    let mut all_zero = true;
    let mut any_zero = false;
    let mut one_count = 0;
    
    // Get the field at the specified index - we need to handle the Option properly
    let field = match &bitmap {
        Some(b) => {
            // Since we're dealing with a Box containing a single AtomicUsize,
            // we need to access it directly rather than indexing
            if idx == 0 {
                b.as_ref()
            } else {
                // If idx != 0, this is an error case since we only have one field
                return false;
            }
        },
        None => return false,
    };
    
    let mut field_idx = 0;
    let mut prev = field.fetch_or(pre_mask, Ordering::AcqRel);
    field_idx += 1;
    
    if (prev & pre_mask) != 0 {
        all_zero = false;
        one_count += mi_popcount(prev & pre_mask);
    }
    if (prev & pre_mask) != pre_mask {
        any_zero = true;
    }
    
    while mid_count > 0 {
        prev = field.fetch_or(mid_mask, Ordering::AcqRel);
        field_idx += 1;
        if (prev & mid_mask) != 0 {
            all_zero = false;
            one_count += mi_popcount(prev & mid_mask);
        }
        if (prev & mid_mask) != mid_mask {
            any_zero = true;
        }
        mid_count -= 1;
    }
    
    if post_mask != 0 {
        prev = field.fetch_or(post_mask, Ordering::AcqRel);
        if (prev & post_mask) != 0 {
            all_zero = false;
            one_count += mi_popcount(prev & post_mask);
        }
        if (prev & post_mask) != post_mask {
            any_zero = true;
        }
    }
    
    if let Some(pany_zero_ref) = pany_zero {
        *pany_zero_ref = any_zero;
    }
    
    if let Some(already_set_ref) = already_set {
        *already_set_ref = one_count;
    }
    
    assert!(
        if all_zero { one_count == 0 } else { one_count <= count },
        "all_zero ? one_count == 0 : one_count <= count"
    );
    
    all_zero
}

pub type mi_bitmap_field_t = AtomicUsize;
pub type mi_bitmap_index_t = usize;
pub type mi_bitmap_t = Option<Box<mi_bitmap_field_t>>;

pub fn _mi_bitmap_unclaim_across(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: mi_bitmap_index_t,
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let mut pre_mask = 0;
    let mut mid_mask = 0;
    let mut post_mask = 0;
    let mid_count = mi_bitmap_mask_across(
        bitmap_idx,
        bitmap_fields,
        count,
        &mut pre_mask,
        &mut mid_mask,
        &mut post_mask,
    );
    let mut all_one = true;
    
    if let Some(bitmap_box) = bitmap {
        let field = &bitmap_box;
        let mut field_idx = 0;
        
        {
            let prev = field.fetch_and(!pre_mask, Ordering::AcqRel);
            field_idx += 1;
            if (prev & pre_mask) != pre_mask {
                all_one = false;
            }
        }
        
        let mut current_mid_count = mid_count;
        while current_mid_count > 0 {
            {
                let prev = field.fetch_and(!mid_mask, Ordering::AcqRel);
                field_idx += 1;
                if (prev & mid_mask) != mid_mask {
                    all_one = false;
                }
            }
            current_mid_count -= 1;
        }
        
        if post_mask != 0 {
            {
                let prev = field.fetch_and(!post_mask, Ordering::AcqRel);
                if (prev & post_mask) != post_mask {
                    all_one = false;
                }
            }
        }
    }
    
    all_one
}

pub fn mi_bitmap_is_claimedx_across(
    bitmap: Option<&[mi_bitmap_field_t]>,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: usize,
    pany_ones: Option<&mut bool>,
    already_set: Option<&mut usize>
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let mut pre_mask = 0;
    let mut mid_mask = 0;
    let mut post_mask = 0;
    let mut mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &mut pre_mask, &mut mid_mask, &mut post_mask);
    
    let mut all_ones = true;
    let mut any_ones = false;
    let mut one_count = 0;
    
    let bitmap = match bitmap {
        Some(b) => b,
        None => return false,
    };
    
    let field = &bitmap[idx];
    let mut field_idx = 0;
    
    let mut prev = field.load(Ordering::Relaxed);
    field_idx += 1;
    
    if (prev & pre_mask) != pre_mask {
        all_ones = false;
    }
    if (prev & pre_mask) != 0 {
        any_ones = true;
        one_count += mi_popcount(prev & pre_mask);
    }
    
    while mid_count > 0 {
        prev = field.load(Ordering::Relaxed);
        field_idx += 1;
        if (prev & mid_mask) != mid_mask {
            all_ones = false;
        }
        if (prev & mid_mask) != 0 {
            any_ones = true;
            one_count += mi_popcount(prev & mid_mask);
        }
        mid_count -= 1;
    }
    
    if post_mask != 0 {
        prev = field.load(Ordering::Relaxed);
        if (prev & post_mask) != post_mask {
            all_ones = false;
        }
        if (prev & post_mask) != 0 {
            any_ones = true;
            one_count += mi_popcount(prev & post_mask);
        }
    }
    
    if let Some(pany_ones_ref) = pany_ones {
        *pany_ones_ref = any_ones;
    }
    
    if let Some(already_set_ref) = already_set {
        *already_set_ref = one_count;
    }
    
    assert!(if all_ones { one_count == count } else { one_count < count });
    
    all_ones
}
pub fn _mi_bitmap_is_claimed_across(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: mi_bitmap_index_t,
    already_set: Option<&mut usize>
) -> bool {
    let bitmap_slice = bitmap.as_ref().map(|boxed| std::slice::from_ref(&**boxed));
    mi_bitmap_is_claimedx_across(bitmap_slice, bitmap_fields, count, bitmap_idx, Option::None, already_set)
}

pub fn _mi_bitmap_unclaim(
    bitmap: &mut [AtomicUsize],
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: usize,
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
    let mask = mi_bitmap_mask_(count, bitidx);
    
    assert!(bitmap_fields > idx, "bitmap_fields > idx");
    
    let prev = bitmap[idx].fetch_and(!mask, Ordering::AcqRel);
    (prev & mask) == mask
}

pub fn _mi_bitmap_try_claim(
    bitmap: &[AtomicUsize],
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: usize
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
    let mask = mi_bitmap_mask_(count, bitidx);
    
    assert!(bitmap_fields > idx, "bitmap_fields > idx");
    
    let field = &bitmap[idx];
    let mut expected = field.load(Ordering::Relaxed);
    
    loop {
        if (expected & mask) != 0 {
            return false;
        }
        
        match field.compare_exchange_weak(
            expected,
            expected | mask,
            Ordering::AcqRel,
            Ordering::Acquire
        ) {
            Ok(_) => {
                assert!((expected & mask) == 0, "(expected & mask) == 0");
                return true;
            }
            Err(new_expected) => {
                expected = new_expected;
            }
        }
    }
}

pub fn mi_bitmap_is_claimedx(
    bitmap: Option<&[AtomicUsize]>,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: usize,
    any_ones: Option<&mut bool>
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
    let mask = mi_bitmap_mask_(count, bitidx);
    
    assert!(bitmap_fields > idx, "bitmap_fields > idx");
    
    let bitmap = bitmap.expect("bitmap should not be None");
    let field = bitmap[idx].load(Ordering::Relaxed);
    
    if let Some(any_ones_ref) = any_ones {
        *any_ones_ref = (field & mask) != 0;
    }
    
    (field & mask) == mask
}
// Helper functions needed for bitmap operations
fn mi_bitmap_index_field(bitmap_idx: mi_bitmap_index_t) -> usize {
    (bitmap_idx >> mi_bitmap_index_field_shift()) as usize
}

fn mi_bitmap_index_bit_in_field(bitmap_idx: mi_bitmap_index_t) -> usize {
    (bitmap_idx & ((1 << mi_bitmap_index_field_shift()) - 1)) as usize
}

fn mi_bitmap_index_bit_count() -> usize {
    8 * std::mem::size_of::<mi_bitmap_field_t>()
}

fn mi_bitmap_index_field_shift() -> usize {
    (mi_bitmap_index_bit_count().trailing_zeros()) as usize
}

pub fn _mi_bitmap_is_claimed(bitmap: mi_bitmap_t, bitmap_fields: usize, count: usize, bitmap_idx: mi_bitmap_index_t) -> bool {
    // Convert Option<Box<mi_bitmap_field_t>> to Option<&[AtomicUsize]>
    // Since we don't have the actual conversion logic, we'll use a slice of the boxed data
    // assuming mi_bitmap_field_t is compatible with AtomicUsize
    let bitmap_slice = bitmap.as_ref().map(|boxed| {
        // Create a slice from the boxed data
        std::slice::from_ref(&**boxed)
    });
    mi_bitmap_is_claimedx(bitmap_slice, bitmap_fields, count, bitmap_idx, Option::None)
}
pub fn _mi_bitmap_claim(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    count: usize,
    bitmap_idx: mi_bitmap_index_t,
    any_zero: Option<&mut bool>
) -> bool {
    let idx = mi_bitmap_index_field(bitmap_idx);
    let bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
    let mask = mi_bitmap_mask_(count, bitidx);
    
    // Check bounds like the C assertion - use > instead of >=
    if bitmap_fields <= idx {
        _mi_assert_fail("bitmap_fields > idx", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/bitmap.c", 149, Some("_mi_bitmap_claim"));
        if let Some(any_zero_ref) = any_zero {
            *any_zero_ref = true;
        }
        return false;
    }
    
    // Handle None case for the bitmap
    let bitmap_ptr = match bitmap {
        Some(ptr) => ptr,
        None => {
            if let Some(any_zero_ref) = any_zero {
                *any_zero_ref = true;
            }
            return false;
        }
    };
    
    // Access the specific field using index - the bitmap is an array of atomic values
    unsafe {
        // Treat the boxed pointer as pointing to an array of AtomicUsize
        let atomic_fields = std::slice::from_raw_parts(bitmap_ptr.as_ptr() as *const std::sync::atomic::AtomicUsize, bitmap_fields);
        let prev = atomic_fields[idx].fetch_or(mask, std::sync::atomic::Ordering::AcqRel);
        
        if let Some(any_zero_ref) = any_zero {
            *any_zero_ref = (prev & mask) != mask;
        }
        
        (prev & mask) == 0
    }
}
#[inline]
pub fn _mi_bitmap_try_find_claim_field(
    bitmap: &[mi_bitmap_field_t],
    idx: usize,
    count: usize,
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
) -> bool {
    assert!(bitmap_idx.is_some(), "bitmap_idx != NULL");
    assert!(count <= (8 * (1 << 3)), "count <= MI_BITMAP_FIELD_BITS");
    assert!(count > 0, "count > 0");

    let field = &bitmap[idx];
    let mut map = field.load(Ordering::Relaxed);

    if map == !0 {
        return false;
    }

    let mask = mi_bitmap_mask_(count, 0);
    let bitidx_max = (8 * (1 << 3)) - count;
    let mut bitidx = mi_ctz(!map as u64) as usize;
    let mut m = mask << bitidx;

    while bitidx <= bitidx_max {
        let mapm = map & m;
        if mapm == 0 {
            assert!((m >> bitidx) == mask, "(m >> bitidx) == mask");
            let newmap = map | m;
            assert!(
                ((newmap ^ map) >> bitidx) == mask,
                "(newmap^map) >> bitidx == mask"
            );

            if field
                .compare_exchange_weak(
                    map,
                    newmap,
                    Ordering::AcqRel,
                    Ordering::Acquire,
                )
                .is_err()
            {
                map = field.load(Ordering::Relaxed);
                continue;
            } else {
                *bitmap_idx = Some(mi_bitmap_index_create(idx, bitidx));
                return true;
            }
        } else {
            assert!(mapm != 0, "mapm != 0");
            let shift = if count == 1 {
                1
            } else {
                ((8 * (1 << 3)) - mi_clz(mapm)) - bitidx
            };
            assert!(
                shift > 0 && shift <= count,
                "shift > 0 && shift <= count"
            );
            bitidx += shift;
            m <<= shift;
        }
    }

    false
}
pub fn _mi_bitmap_try_find_from_claim(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    start_field_idx: usize,
    count: usize,
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
) -> bool {
    let mut idx = start_field_idx;
    
    for visited in 0..bitmap_fields {
        if idx >= bitmap_fields {
            idx = 0;
        }
        
        if let Some(bitmap_ref) = &bitmap {
            // Create a slice containing the single AtomicUsize element
            let bitmap_slice = std::slice::from_ref(&**bitmap_ref);
            if _mi_bitmap_try_find_claim_field(bitmap_slice, idx, count, bitmap_idx) {
                return true;
            }
        }
        
        idx += 1;
    }
    
    false
}

pub fn mi_bitmap_try_find_claim_field_across(
    bitmap: &[mi_bitmap_field_t],
    bitmap_fields: usize,
    idx: usize,
    count: usize,
    retries: usize,
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
) -> bool {
    // Check for NULL pointer equivalent
    if bitmap_idx.is_none() {
        return false;
    }

    let field = &bitmap[idx];
    let mut field_idx = 0;
    let map = field.load(Ordering::Relaxed);
    let initial = mi_clz(map);
    
    if initial == 0 {
        return false;
    }
    
    if initial >= count {
        return _mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx);
    }
    
    if _mi_divide_up(count - initial, 8 * (1 << 3)) >= (bitmap_fields - idx) {
        return false;
    }
    
    let mut found = initial;
    let mut mask = 0;
    
    while found < count {
        field_idx += 1;
        let map = field.load(Ordering::Relaxed);
        let mask_bits = if (found + (8 * (1 << 3))) <= count {
            8 * (1 << 3)
        } else {
            count - found
        };
        
        mask = mi_bitmap_mask_(mask_bits, 0);
        if (map & mask) != 0 {
            return false;
        }
        found += mask_bits;
    }

    let final_field = &bitmap[idx + field_idx];
    let final_mask = mask;
    let initial_field = &bitmap[idx];
    let initial_idx = (8 * (1 << 3)) - initial;
    let initial_mask = mi_bitmap_mask_(initial, initial_idx);
    
    // Try to claim the initial field
    let mut map = initial_field.load(Ordering::Relaxed);
    loop {
        let newmap = map | initial_mask;
        if (map & initial_mask) != 0 {
            return rollback(bitmap, bitmap_fields, idx, count, retries, bitmap_idx, initial_field, initial_mask);
        }
        
        match initial_field.compare_exchange_weak(
            map,
            newmap,
            Ordering::AcqRel,
            Ordering::Acquire,
        ) {
            Ok(_) => break,
            Err(current) => map = current,
        }
    }
    
    // Claim intermediate fields
    for i in 1..field_idx {
        let field = &bitmap[idx + i];
        let mut map = field.load(Ordering::Relaxed);
        let newmap = !0usize;
        
        match field.compare_exchange_weak(
            map,
            newmap,
            Ordering::AcqRel,
            Ordering::Acquire,
        ) {
            Ok(_) => continue,
            Err(_) => return rollback(bitmap, bitmap_fields, idx, count, retries, bitmap_idx, initial_field, initial_mask),
        }
    }
    
    // Claim final field
    let mut map = final_field.load(Ordering::Relaxed);
    loop {
        let newmap = map | final_mask;
        if (map & final_mask) != 0 {
            return rollback(bitmap, bitmap_fields, idx, count, retries, bitmap_idx, initial_field, initial_mask);
        }
        
        match final_field.compare_exchange_weak(
            map,
            newmap,
            Ordering::AcqRel,
            Ordering::Acquire,
        ) {
            Ok(_) => {
                *bitmap_idx = Some(mi_bitmap_index_create(idx, initial_idx));
                return true;
            }
            Err(current) => map = current,
        }
    }
}

fn rollback(
    bitmap: &[mi_bitmap_field_t],
    bitmap_fields: usize,
    idx: usize,
    count: usize,
    retries: usize,
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
    initial_field: &mi_bitmap_field_t,
    initial_mask: usize,
) -> bool {
    // Rollback intermediate fields
    for i in 1..(bitmap_fields - idx) {
        let field = &bitmap[idx + i];
        let map = field.load(Ordering::Relaxed);
        if map == !0usize {
            field.store(0, Ordering::Release);
        }
    }
    
    // Rollback initial field
    let mut map = initial_field.load(Ordering::Relaxed);
    loop {
        let newmap = map & (!initial_mask);
        match initial_field.compare_exchange_weak(
            map,
            newmap,
            Ordering::AcqRel,
            Ordering::Acquire,
        ) {
            Ok(_) => break,
            Err(current) => map = current,
        }
    }
    
    {
        let mut stats = _mi_stats_main.lock().unwrap();
        stats.arena_rollback_count.total += 1;
    }
    
    if retries <= 2 {
        mi_bitmap_try_find_claim_field_across(bitmap, bitmap_fields, idx, count, retries + 1, bitmap_idx)
    } else {
        false
    }
}
pub fn _mi_bitmap_try_find_from_claim_across(
    bitmap: mi_bitmap_t,
    bitmap_fields: usize,
    start_field_idx: usize,
    count: usize,
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
) -> bool {
    assert!(count > 0, "count > 0");
    
    if count <= 2 {
        return _mi_bitmap_try_find_from_claim(bitmap, bitmap_fields, start_field_idx, count, bitmap_idx);
    }
    
    let mut idx = start_field_idx;
    for visited in 0..bitmap_fields {
        if idx >= bitmap_fields {
            idx = 0;
        }
        
        // Convert Option<Box<mi_bitmap_field_t>> to &[mi_bitmap_field_t]
        if let Some(bitmap_ref) = bitmap.as_ref() {
            // Create a slice containing just the dereferenced box content
            let field_slice = std::slice::from_ref(&**bitmap_ref);
            if mi_bitmap_try_find_claim_field_across(field_slice, bitmap_fields, idx, count, 0, bitmap_idx) {
                return true;
            }
        } else {
            // Handle None case - bitmap is not available
            return false;
        }
        
        idx += 1;
    }
    
    false
}
pub fn _mi_bitmap_is_any_claimed(bitmap: mi_bitmap_t, bitmap_fields: usize, count: usize, bitmap_idx: mi_bitmap_index_t) -> bool {
    let mut any_ones = false;
    let bitmap_slice = bitmap.as_ref().map(|boxed| std::slice::from_ref(&**boxed));
    mi_bitmap_is_claimedx(bitmap_slice, bitmap_fields, count, bitmap_idx, Some(&mut any_ones));
    any_ones
}
pub fn _mi_bitmap_is_any_claimed_across(bitmap: mi_bitmap_t, bitmap_fields: usize, count: usize, bitmap_idx: mi_bitmap_index_t) -> bool {
    let mut any_ones = false;
    let bitmap_slice = bitmap.as_deref().map(|field| std::slice::from_ref(field));
    mi_bitmap_is_claimedx_across(
        bitmap_slice, 
        bitmap_fields, 
        count, 
        bitmap_idx, 
        Some(&mut any_ones), 
        Option::None
    );
    any_ones
}
pub fn _mi_bitmap_try_find_from_claim_pred(
    bitmap: &mut [mi_bitmap_field_t],
    bitmap_fields: usize,
    start_field_idx: usize,
    count: usize,
    pred_fun: Option<fn(mi_bitmap_index_t, Option<&mut ()>) -> bool>,
    pred_arg: *mut (),
    bitmap_idx: &mut Option<mi_bitmap_index_t>,
) -> bool {
    let mut idx = start_field_idx;
    
    for _visited in 0..bitmap_fields {
        if idx >= bitmap_fields {
            idx = 0;
        }
        
        if _mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx) {
            match pred_fun {
                Some(pred) => {
                    if let Some(bitmap_idx_val) = *bitmap_idx {
                        // Convert raw pointer to Option<&mut ()> for predicate call
                        let pred_arg_option = if pred_arg.is_null() {
                            Option::None
                        } else {
                            Some(unsafe { &mut *(pred_arg as *mut ()) })
                        };
                        if pred(bitmap_idx_val, pred_arg_option) {
                            return true;
                        }
                        _mi_bitmap_unclaim(bitmap, bitmap_fields, count, bitmap_idx_val);
                    }
                }
                Option::None => {
                    // No predicate function, so we accept the claim
                    return true;
                }
            }
        }
        
        idx += 1;
    }
    
    false
}
