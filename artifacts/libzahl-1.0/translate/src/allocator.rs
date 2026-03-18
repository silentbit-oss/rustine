use crate::*;
use lazy_static::lazy_static;
use rand::Rng;
use std::mem;
use std::ptr;
use std::slice;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn libzahl_realloc(a: &mut z_t, need: usize) {

    // Calculate the next power of two for need
    let mut adjusted_need = need;
    if (adjusted_need & ((!adjusted_need) + 1)) != adjusted_need {
        adjusted_need |= adjusted_need >> 1;
        adjusted_need |= adjusted_need >> 2;
        adjusted_need |= adjusted_need >> 4;
        for i in 0..std::mem::size_of::<usize>() {
            let shift = 8 << i;
            adjusted_need |= adjusted_need >> shift;
        }
        adjusted_need += 1;
    }

    // Calculate log2 of adjusted_need
    let mut log2 = 0;
    let mut x = adjusted_need;
    while x != 0 {
        x >>= 1;
        log2 += 1;
    }

    // Try to get from pool
    if LIBZAHL_POOL_N[log2].load(Ordering::Relaxed) > 0 {
        LIBZAHL_POOL_N[log2].fetch_sub(1, Ordering::Relaxed);
        let mut pool = LIBZAHL_POOL.lock().unwrap();
        if let Some(pool_allocation) = pool[log2].take() {
            // Copy old data to new allocation
            if let Some(old_chars) = &a[0].chars {
                let old_slice = old_chars.as_ref();
                unsafe {
                    ptr::copy_nonoverlapping(
                        old_slice.as_ptr(),
                        pool_allocation.as_ptr() as *mut u32,
                        a[0].alloced.min(old_slice.len()),
                    );
                }
            }
            
            zfree(a);
            a[0].chars = Some(pool_allocation);
        }
    } else {
        // Fall back to realloc
        let new_chars = if let Some(old_chars) = &a[0].chars {
            let mut new_vec = old_chars.to_vec();
            new_vec.resize(adjusted_need, 0);
            new_vec.into_boxed_slice()
        } else {
            vec![0; adjusted_need].into_boxed_slice()
        };

        a[0].chars = Some(new_chars);
    }
    a[0].alloced = adjusted_need;
}
