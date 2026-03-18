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
    let _ = length; // Explicitly ignore the unused parameter
    
    // Access the sublen vector safely
    let Some(sublen) = &lmc.sublen else {
        return 0;
    };
    
    let cache_idx = (8 * pos) * 3;
    
    // Check if we can safely access the required indices
    if cache_idx + 2 >= sublen.len() {
        return 0;
    }
    
    if sublen[cache_idx + 1] == 0 && sublen[cache_idx + 2] == 0 {
        return 0;
    }
    
    let final_idx = cache_idx + (8 - 1) * 3;
    if final_idx >= sublen.len() {
        return 0;
    }
    
    u16::from(sublen[final_idx]) + 3
}

pub fn ZopfliSublenToCache(sublen: &[u16], pos: usize, length: usize, lmc: &mut ZopfliLongestMatchCache) {
    let mut j = 0;
    let mut bestlength = 0;
    
    if length < 3 {
        return;
    }
    
    let cache_start = (8 * pos) * 3;
    let cache_slice = lmc.sublen.as_mut().unwrap();
    let cache = &mut cache_slice[cache_start..cache_start + 24]; // 8 * 3 = 24 bytes
    
    for i in (3..=length).step_by(1) {
        if i == length || sublen[i] != sublen[i + 1] {
            cache[j * 3] = (i - 3) as u8;
            cache[(j * 3) + 1] = (sublen[i] % 256) as u8;
            cache[(j * 3) + 2] = ((sublen[i] >> 8) % 256) as u8;
            bestlength = i;
            j += 1;
            
            if j >= 8 {
                break;
            }
        }
    }
    
    if j < 8 {
        assert!(bestlength == length, "bestlength should equal length");
        cache[(8 - 1) * 3] = (bestlength - 3) as u8;
    } else {
        assert!(bestlength <= length, "bestlength should be <= length");
    }
    
    assert!(bestlength as u16 == ZopfliMaxCachedSublen(lmc, pos, length), 
            "bestlength should match cached sublen");
}
pub fn ZopfliCacheToSublen(lmc: &ZopfliLongestMatchCache, pos: usize, length: usize, sublen: &mut [u16]) {
    if length < 3 {
        return;
    }
    
    let maxlength = ZopfliMaxCachedSublen(lmc, pos, length);
    let mut prevlength: u16 = 0;
    
    // Get a reference to the cache data
    let cache_start = (8 * pos) * 3;
    let Some(cache_data) = lmc.sublen.as_ref() else {
        return;
    };
    
    // Ensure we don't go out of bounds
    if cache_start + 24 > cache_data.len() {
        return;
    }
    
    let cache = &cache_data[cache_start..cache_start + 24];
    
    for j in 0..8 {
        let length_val = cache[j * 3] as u16 + 3;
        let dist = cache[(j * 3) + 1] as u16 + (256 * cache[(j * 3) + 2] as u16);
        
        for i in prevlength..=length_val {
            if i < sublen.len() as u16 {
                sublen[i as usize] = dist;
            }
        }
        
        if length_val == maxlength {
            break;
        }
        prevlength = length_val + 1;
    }
}
