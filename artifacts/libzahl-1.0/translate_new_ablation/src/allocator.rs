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
    let mut need = need;
    
    // Round up to the next power of two
    if (need & (!need + 1)) != need {
        need |= need >> 1;
        need |= need >> 2;
        need |= need >> 4;
        
        let mut i = std::mem::size_of::<usize>();
        let mut x = 8;
        while i > 0 {
            need |= need >> x;
            i >>= 1;
            x <<= 1;
        }
        need += 1;
    }
    
    // Find the index of the highest set bit (log2 of the power of two)
    let mut i = 0;
    let mut x = need;
    while x > 0 {
        i += 1;
        x >>= 1;
    }
    
    // Access the first element of the z_t array
    let a_first = &mut a[0];
    
    if i >= LIBZAHL_POOL_N.len() {
        // Handle case where need is too large for the pool
        let new_chars = if let Some(ref mut chars) = a_first.chars {
            let mut new_vec = vec![0; need].into_boxed_slice();
            let copy_len = std::cmp::min(chars.len(), need);
            new_vec[..copy_len].copy_from_slice(&chars[..copy_len]);
            new_vec
        } else {
            vec![0; need].into_boxed_slice()
        };
        a_first.chars = Some(new_chars);
    } else if LIBZAHL_POOL_N[i].load(Ordering::Relaxed) > 0 {
        let mut pool_guard = LIBZAHL_POOL.lock().unwrap();
        if let Some(pool_allocation) = pool_guard.get_mut(i) {
            if let Some(mut existing_allocation) = pool_allocation.take() {
                LIBZAHL_POOL_N[i].fetch_sub(1, Ordering::Relaxed);
                
                // Copy existing data to the new block
                if let Some(ref old_chars) = a_first.chars {
                    let copy_len = std::cmp::min(old_chars.len(), existing_allocation.len());
                    existing_allocation[..copy_len].copy_from_slice(&old_chars[..copy_len]);
                }
                
                a_first.chars = Some(existing_allocation);
            }
        }
    } else {
        // Use realloc equivalent - create new allocation and copy
        let new_chars = if let Some(ref old_chars) = a_first.chars {
            let mut new_vec = vec![0; need].into_boxed_slice();
            let copy_len = std::cmp::min(old_chars.len(), need);
            new_vec[..copy_len].copy_from_slice(&old_chars[..copy_len]);
            new_vec
        } else {
            vec![0; need].into_boxed_slice()
        };
        
        // Check for allocation failure
        if new_chars.is_empty() && need > 0 {
            if LIBZAHL_ERROR.load(Ordering::Relaxed) == 0 {
                LIBZAHL_ERROR.store(libc::ENOMEM as i32, Ordering::Relaxed);
            }
            let mut jmp_buf = libzahl_jmp_buf.lock().unwrap();
            // longjmp equivalent - this will unwind the stack
            panic!("Allocation failed - should be caught by setjmp/longjmp handler");
        }
        
        a_first.chars = Some(new_chars);
    }
    
    a_first.alloced = need;
}
