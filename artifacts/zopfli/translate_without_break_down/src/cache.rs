use crate::*;
use std::assert;
use std::process;


pub fn ZopfliInitCache(blocksize: usize, lmc: &mut ZopfliLongestMatchCache) {
    // Allocate vectors for length and dist
    lmc.length = Some(vec![1; blocksize]);
    lmc.dist = Some(vec![0; blocksize]);
    
    // Calculate sublen size (8 * 3 * blocksize)
    let sublen_size = 8 * 3 * blocksize;
    lmc.sublen = Some(vec![0; sublen_size]);
    
    // In Rust, we don't need to manually check for allocation failure like in C
    // because Vec::new() will panic if allocation fails (which is the desired behavior)
    // and we don't need to manually initialize the values since vec![] does that
}
pub fn ZopfliCleanCache(lmc: &mut ZopfliLongestMatchCache) {
    // In Rust, we don't need explicit free() calls - dropping the Vec will handle deallocation
    // We can just set all fields to None, which will drop any existing Vecs
    lmc.length = None;
    lmc.dist = None;
    lmc.sublen = None;
}
pub fn ZopfliMaxCachedSublen(lmc: &ZopfliLongestMatchCache, pos: usize, length: usize) -> u16 {
    // The original C code ignores the length parameter, so we do too
    let _ = length;

    // Safely access the sublen vector
    let cache = match &lmc.sublen {
        Some(c) => c,
        None => return 0,
    };

    // Calculate the cache index (8 * pos * 3)
    let cache_idx = (8 * pos) * 3;

    // Check if we can safely access the required indices
    if cache_idx + 2 >= cache.len() {
        return 0;
    }

    // Check the conditions from the C code
    if cache[cache_idx + 1] == 0 && cache[cache_idx + 2] == 0 {
        return 0;
    }

    // Calculate the final index ((8 - 1) * 3 + cache_idx)
    let final_idx = (7 * 3) + cache_idx;

    // Return the value if the index is valid, otherwise 0
    if final_idx < cache.len() {
        u16::from(cache[final_idx]) + 3
    } else {
        0
    }
}

pub fn ZopfliSublenToCache(sublen: &[u16], pos: usize, length: usize, lmc: &mut ZopfliLongestMatchCache) {
    let mut j = 0;
    let mut bestlength = 0;
    
    // Get mutable reference to cache (sublen) with bounds checking
    let cache_idx = 8 * pos * 3;
    let Some(cache) = lmc.sublen.as_mut() else {
        return;
    };

    if length < 3 {
        return;
    }

    for i in 3..=length {
        if i == length || sublen[i] != sublen[i + 1] {
            // Calculate indices with bounds checking
            if cache_idx + j * 3 + 0 < cache.len() {
                cache[cache_idx + j * 3 + 0] = (i - 3) as u8;
            }
            if cache_idx + j * 3 + 1 < cache.len() {
                cache[cache_idx + j * 3 + 1] = (sublen[i] % 256) as u8;
            }
            if cache_idx + j * 3 + 2 < cache.len() {
                cache[cache_idx + j * 3 + 2] = ((sublen[i] >> 8) % 256) as u8;
            }
            bestlength = i;
            j += 1;
            if j >= 8 {
                break;
            }
        }
    }

    if j < 8 {
        assert!(bestlength == length);
        if cache_idx + (8 - 1) * 3 < cache.len() {
            cache[cache_idx + (8 - 1) * 3] = (bestlength - 3) as u8;
        }
    } else {
        assert!(bestlength <= length);
    }
    assert!(bestlength as u16 == ZopfliMaxCachedSublen(lmc, pos, length));
}
pub fn ZopfliCacheToSublen(lmc: &ZopfliLongestMatchCache, pos: usize, length: usize, sublen: &mut [u16]) {
    if length < 3 {
        return;
    }

    let maxlength = ZopfliMaxCachedSublen(lmc, pos, length);
    let mut prevlength = 0;

    // Get the cache slice starting at the calculated index
    let cache_start = 8 * pos * 3;
    let cache = match &lmc.sublen {
        Some(c) => &c[cache_start..],
        None => return,
    };

    for j in 0..8 {
        let length_val = cache[j * 3] as u16 + 3;
        let dist = cache[j * 3 + 1] as u16 + (256 * cache[j * 3 + 2] as u16);

        for i in prevlength..=length_val {
            if (i as usize) < sublen.len() {
                sublen[i as usize] = dist;
            }
        }

        if length_val == maxlength {
            break;
        }
        prevlength = length_val + 1;
    }
}
