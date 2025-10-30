use crate::*;

pub fn ZopfliInitCache(blocksize: usize, lmc: &mut ZopfliLongestMatchCache) {
    // Allocate vectors with capacity `blocksize` for length and dist
    lmc.length = Some(vec![1; blocksize]);
    lmc.dist = Some(vec![0; blocksize]);
    
    // Calculate sublen size (8 * 3 * blocksize)
    let sublen_size = 8 * 3 * blocksize;
    lmc.sublen = Some(vec![0; sublen_size]);
    
    // In Rust, Vec allocation will panic if out of memory, so no need for explicit error checking
    // The initialization values are set directly in the vec! macro calls
}
pub fn ZopfliCleanCache(lmc: &mut ZopfliLongestMatchCache) {
    // In Rust, dropping the Vecs (by setting them to None) will automatically free their memory
    lmc.length = None;
    lmc.dist = None;
    lmc.sublen = None;
}
pub fn ZopfliMaxCachedSublen(lmc: &ZopfliLongestMatchCache, pos: usize, length: usize) -> u8 {
    // The `length` parameter is unused, so we silence the warning
    let _ = length;
    
    // Safely access the sublen vector
    let cache = match &lmc.sublen {
        Some(c) => c,
        None => return 0,
    };

    // Calculate the cache index
    let cache_idx = (8 * pos) * 3;
    
    // Check if we can safely access the required indices
    if cache_idx + 2 >= cache.len() {
        return 0;
    }

    // Check the conditions from the C code
    if cache[cache_idx + 1] == 0 && cache[cache_idx + 2] == 0 {
        return 0;
    }

    // Calculate the final index and return the result
    let final_idx = ((8 - 1) * 3) + cache_idx;
    if final_idx >= cache.len() {
        return 0;
    }
    
    cache[final_idx] + 3
}
pub fn ZopfliSublenToCache(sublen: &[u16], pos: usize, length: usize, lmc: &mut ZopfliLongestMatchCache) {
    let mut j = 0;
    let mut bestlength = 0;
    
    // Early return if length is less than 3
    if length < 3 {
        return;
    }

    // Get mutable access to the cache
    let cache = match &mut lmc.sublen {
        Some(c) => c,
        None => return,
    };

    let cache_idx = (8 * pos) * 3;

    for i in 3..=length {
        if i == length || sublen[i] != sublen[i + 1] {
            // Check bounds before writing
            if cache_idx + (j * 3) + 2 < cache.len() {
                cache[cache_idx + (j * 3)] = (i - 3) as u8;
                cache[cache_idx + (j * 3) + 1] = (sublen[i] % 256) as u8;
                cache[cache_idx + (j * 3) + 2] = ((sublen[i] >> 8) % 256) as u8;
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
        // Check bounds before writing
        if cache_idx + ((8 - 1) * 3) < cache.len() {
            cache[cache_idx + ((8 - 1) * 3)] = (bestlength - 3) as u8;
        }
    } else {
        assert!(bestlength <= length);
    }
    assert!(bestlength == ZopfliMaxCachedSublen(lmc, pos, length) as usize);
}
pub fn ZopfliCacheToSublen(lmc: &ZopfliLongestMatchCache, pos: usize, length: usize, sublen: &mut [u16]) {
    if length < 3 {
        return;
    }

    let maxlength = ZopfliMaxCachedSublen(lmc, pos, length);
    let mut prevlength = 0;

    let cache = match &lmc.sublen {
        Some(c) => c,
        None => return,
    };

    let cache_idx = (8 * pos) * 3;
    if cache_idx >= cache.len() {
        return;
    }

    for j in 0..8 {
        let j_offset = (j * 3) + cache_idx;
        if j_offset + 2 >= cache.len() {
            break;
        }

        let length_val = cache[j_offset] + 3;
        let dist = cache[j_offset + 1] as u16 + (256 * cache[j_offset + 2] as u16);

        for i in prevlength..=length_val {
            if usize::from(i) < sublen.len() {
                sublen[i as usize] = dist;
            }
        }

        if length_val == maxlength {
            break;
        }
        prevlength = length_val + 1;
    }
}
