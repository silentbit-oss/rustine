use crate::*;
use std::convert::TryInto;
use std::ptr;

pub fn libzahl_realloc(a: &mut Z, need: usize) {
    // Calculate the next power of two for the allocation size
    let mut rounded_need = need;
    if (rounded_need & ((!rounded_need) + 1)) != rounded_need {
        rounded_need |= rounded_need >> 1;
        rounded_need |= rounded_need >> 2;
        rounded_need |= rounded_need >> 4;
        for i in (0..std::mem::size_of::<usize>()).rev() {
            let x = 8 << i;
            rounded_need |= rounded_need >> x;
        }
        rounded_need += 1;
    }

    // Find the index in the pool based on the allocation size
    let i = rounded_need.leading_zeros().count_zeros() as usize;

    // Try to get a block from the pool
    let mut libzahl_pool_n = LIBZAHL_POOL_N.lock().unwrap();
    if libzahl_pool_n[i] > 0 {
        libzahl_pool_n[i] -= 1;
        let new_idx = {
            let libzahl_pool = LIBZAHL_POOL.lock().unwrap();
            if let Some(pool) = &libzahl_pool[i] {
                pool[libzahl_pool_n[i]]
            } else {
                // Handle error case - similar to C version
                let mut libzahl_error = LIBZAHL_ERROR.lock().unwrap();
                *libzahl_error = std::io::Error::from_raw_os_error(12).raw_os_error().unwrap_or(0); // ENOMEM = 12
                unsafe { 
                    extern "C" {
                        fn longjmp(env: *mut jmp_buf, val: i32);
                    }
                    longjmp(&mut libzahl_jmp_buf as *mut _, 1);
                }
                return; // This line is unreachable but satisfies the type checker
            }
        };

        // Create new allocation and copy data
        let mut new_allocation = vec![0; rounded_need].into_boxed_slice();
        if let Some(old_chars) = &a.chars {
            let copy_len = std::cmp::min(a.alloced, rounded_need);
            new_allocation[..copy_len].copy_from_slice(&old_chars[..copy_len]);
        }

        zfree(a);
        a.chars = Some(new_allocation);
    } else {
        // Fall back to reallocation
        let mut new_allocation = match a.chars.take() {
            Some(existing) => {
                let mut vec = existing.into_vec();
                vec.resize(rounded_need, 0);
                vec.into_boxed_slice()
            }
            None => vec![0; rounded_need].into_boxed_slice(),
        };

        a.chars = Some(new_allocation);
    }

    a.alloced = rounded_need;
}
