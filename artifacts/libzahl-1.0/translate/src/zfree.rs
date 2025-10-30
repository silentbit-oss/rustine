use crate::*;

pub fn zfree(a: &mut Z) {
    if a.chars.is_none() {
        return;
    }

    let i = a.alloced.leading_zeros().count_zeros() as usize;
    
    let mut libzahl_pool_n = LIBZAHL_POOL_N.lock().unwrap();
    let j = libzahl_pool_n[i];
    libzahl_pool_n[i] += 1;

    let mut libzahl_pool_alloc = LIBZAHL_POOL_ALLOC.lock().unwrap();
    if j == libzahl_pool_alloc[i] {
        let x = if j != 0 { (j * 3) / 2 } else { 128 };
        
        let mut libzahl_pool = LIBZAHL_POOL.lock().unwrap();
        let mut new_vec = match libzahl_pool[i].take() {
            Some(existing) => {
                let mut vec = existing.into_vec();
                vec.reserve_exact(x - vec.len());
                vec
            }
            Option::None => Vec::with_capacity(x),
        };

        libzahl_pool[i] = Some(new_vec.into_boxed_slice());
        libzahl_pool_alloc[i] = x;
    }

    let mut libzahl_pool = LIBZAHL_POOL.lock().unwrap();
    if let Some(pool) = &mut libzahl_pool[i] {
        if j < pool.len() {
            if let Some(chars) = a.chars.take() {
                if !chars.is_empty() {
                    pool[j] = chars[0]; // Take the first element of the slice
                }
            }
        } else {
            // Handle error case similar to C version
            a.chars = Option::None;
            libzahl_pool[i] = Option::None;
            libzahl_pool_n[i] = 0;
            libzahl_pool_alloc[i] = 0;
        }
    }
}
