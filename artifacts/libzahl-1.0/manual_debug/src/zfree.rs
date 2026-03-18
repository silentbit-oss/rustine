use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn zfree(a: &mut z_t) {
    let a = &mut a[0]; // Dereference the single-element array
    let mut i = 0;
    let mut x;
    let j;
    
    if a.chars.is_none() {
        return;
    }

    x = a.alloced;
    while x != 0 {
        i += 1;
        x >>= 1;
    }

    j = LIBZAHL_POOL_N[i].fetch_add(1, Ordering::SeqCst);
    let pool_alloc = LIBZAHL_POOL_ALLOC.lock().unwrap()[i];
    
    if j == pool_alloc {
        x = if j != 0 { (j * 3) >> 1 } else { 128 };
        
        let mut pool = LIBZAHL_POOL.lock().unwrap();
        let mut pool_alloc_guard = LIBZAHL_POOL_ALLOC.lock().unwrap();
        
        let new_vec = match &pool[i] {
            Some(existing) => {
                let mut new_vec = Vec::with_capacity(x);
                new_vec.extend(existing.iter().cloned());
                new_vec.resize(x, 0);
                Some(new_vec.into_boxed_slice())
            }
            None => {
                let new_vec = vec![0; x].into_boxed_slice();
                Some(new_vec)
            }
        };

        match new_vec {
            Some(new_pool) => {
                pool[i] = Some(new_pool);
                pool_alloc_guard[i] = x;
            }
            None => {
                a.chars = None;
                pool[i] = None;
                LIBZAHL_POOL_N[i].store(0, Ordering::SeqCst);
                pool_alloc_guard[i] = 0;
                return;
            }
        }
    }

    let mut pool = LIBZAHL_POOL.lock().unwrap();
    if let Some(pool_slice) = &mut pool[i] {
        if j < pool_slice.len() {
            if let Some(chars) = a.chars.take() {
                //pool_slice[j] = chars[0];
            }
        }
    }
}
