use crate::*;
use rand::Rng;
use std::assert;
use std::boxed::Box;
use std::process;
use std::ptr;
use std::vec::Vec;


pub fn ZopfliVerifyLenDist(data: &[u8], pos: usize, dist: u16, length: u16) {
    assert!(pos + length as usize <= data.len(), "Position and length exceed data bounds");
    
    for i in 0..length as usize {
        assert_eq!(
            data[(pos - dist as usize) + i],
            data[pos + i],
            "Mismatch in data verification at position {}",
            i
        );
    }
}
pub fn CeilDiv(a: usize, b: usize) -> usize {
    ((a + b) - 1) / b
}
pub fn GetLengthScore(length: i32, distance: i32) -> i32 {
    if distance > 1024 {
        length - 1
    } else {
        length
    }
}
pub fn GetMatch<'a>(
    scan: &'a [u8],
    match_: &'a [u8],
    end: &'a [u8],
    safe_end: &'a [u8],
) -> Option<&'a [u8]> {
    let mut match_idx = 0;
    let mut scan_idx = 0;
    
    if std::mem::size_of::<usize>() == 8 {
        while scan_idx + 8 <= scan.len()
            && scan_idx + 8 <= safe_end.len()
            && scan[scan_idx..scan_idx + 8] == match_[match_idx..match_idx + 8]
        {
            scan_idx += 8;
            match_idx += 8;
        }
    } else if std::mem::size_of::<u32>() == 4 {
        while scan_idx + 4 <= scan.len()
            && scan_idx + 4 <= safe_end.len()
            && scan[scan_idx..scan_idx + 4] == match_[match_idx..match_idx + 4]
        {
            scan_idx += 4;
            match_idx += 4;
        }
    } else {
        while scan_idx < scan.len()
            && scan_idx < safe_end.len()
            && scan[scan_idx] == match_[match_idx]
        {
            scan_idx += 1;
            match_idx += 1;
        }
    }

    while scan_idx < scan.len()
        && scan_idx < end.len()
        && scan[scan_idx] == match_[match_idx]
    {
        scan_idx += 1;
        match_idx += 1;
    }

    Some(&scan[..scan_idx])
}
pub fn ZopfliInitLZ77Store(data: Option<&[u8]>, store: &mut ZopfliLz77Store) {
    store.size = 0;
    store.litlens = None;
    store.dists = None;
    store.pos = None;
    store.data = data.map(|d| d.to_vec());
    store.ll_symbol = None;
    store.d_symbol = None;
    store.ll_counts = None;
    store.d_counts = None;
}
pub fn ZopfliCleanLZ77Store(store: &mut ZopfliLz77Store) {
    store.litlens = None;
    store.dists = None;
    store.pos = None;
    store.ll_symbol = None;
    store.d_symbol = None;
    store.ll_counts = None;
    store.d_counts = None;
}
pub fn ZopfliLZ77GetByteRange(lz77: &ZopfliLz77Store, lstart: usize, lend: usize) -> usize {
    if lstart == lend {
        return 0;
    }

    let l = lend - 1;
    let pos = lz77.pos.as_ref().expect("pos must be initialized");
    let dists = lz77.dists.as_ref().expect("dists must be initialized");
    let litlens = lz77.litlens.as_ref().expect("litlens must be initialized");

    (pos[l] + if dists[l] == 0 { 1 } else { litlens[l] as usize }) - pos[lstart]
}
pub fn ZopfliLZ77GetHistogramAt(
    lz77: &ZopfliLz77Store,
    lpos: usize,
    ll_counts: &mut [usize],
    d_counts: &mut [usize],
) {
    let llpos = 288 * (lpos / 288);
    let dpos = 32 * (lpos / 32);

    // First loop: copy ll_counts
    if let Some(ref lz77_ll_counts) = lz77.ll_counts {
        for i in 0..288 {
            ll_counts[i] = lz77_ll_counts[llpos + i];
        }
    }

    // Second loop: decrement ll_counts based on ll_symbol
    if let Some(ref lz77_ll_symbol) = &lz77.ll_symbol {
        for i in (lpos + 1)..(llpos + 288).min(lz77.size) {
            let symbol = lz77_ll_symbol[i] as usize;
            ll_counts[symbol] -= 1;
        }
    }

    // Third loop: copy d_counts
    if let Some(ref lz77_d_counts) = lz77.d_counts {
        for i in 0..32 {
            d_counts[i] = lz77_d_counts[dpos + i];
        }
    }

    // Fourth loop: decrement d_counts based on d_symbol and dists
    if let (Some(ref lz77_dists), Some(ref lz77_d_symbol)) = (&lz77.dists, &lz77.d_symbol) {
        for i in (lpos + 1)..(dpos + 32).min(lz77.size) {
            if lz77_dists[i] != 0 {
                let symbol = lz77_d_symbol[i] as usize;
                d_counts[symbol] -= 1;
            }
        }
    }
}

pub fn ZopfliLZ77GetHistogram(
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    ll_counts: &mut [usize],
    d_counts: &mut [usize],
) {
    if (lstart + (288 * 3)) > lend {
        // Equivalent to memset(ll_counts, 0, sizeof(*ll_counts) * 288)
        for count in ll_counts.iter_mut().take(288) {
            *count = 0;
        }
        
        // Equivalent to memset(d_counts, 0, sizeof(*d_counts) * 32)
        for count in d_counts.iter_mut().take(32) {
            *count = 0;
        }

        // Safe to unwrap since we're in the condition where we're processing the range
        let ll_symbol = lz77.ll_symbol.as_ref().unwrap();
        let dists = lz77.dists.as_ref().unwrap();
        let d_symbol = lz77.d_symbol.as_ref().unwrap();

        for i in lstart..lend {
            ll_counts[ll_symbol[i] as usize] += 1;
            if dists[i] != 0 {
                d_counts[d_symbol[i] as usize] += 1;
            }
        }
    } else {
        ZopfliLZ77GetHistogramAt(lz77, lend - 1, ll_counts, d_counts);
        if lstart > 0 {
            let mut ll_counts2 = [0; 288];
            let mut d_counts2 = [0; 32];
            
            ZopfliLZ77GetHistogramAt(lz77, lstart - 1, &mut ll_counts2, &mut d_counts2);
            
            for i in 0..288 {
                ll_counts[i] -= ll_counts2[i];
            }
            
            for i in 0..32 {
                d_counts[i] -= d_counts2[i];
            }
        }
    }
}

pub fn ZopfliCopyLZ77Store(source: &ZopfliLz77Store, dest: &mut ZopfliLz77Store) {
    let llsize = 288 * CeilDiv(source.size, 288);
    let dsize = 32 * CeilDiv(source.size, 32);
    
    ZopfliCleanLZ77Store(dest);
    ZopfliInitLZ77Store(source.data.as_deref(), dest);
    
    // Allocate vectors with proper capacity
    dest.litlens = Some(vec![0; source.size]);
    dest.dists = Some(vec![0; source.size]);
    dest.pos = Some(vec![0; source.size]);
    dest.ll_symbol = Some(vec![0; source.size]);
    dest.d_symbol = Some(vec![0; source.size]);
    dest.ll_counts = Some(vec![0; llsize]);
    dest.d_counts = Some(vec![0; dsize]);
    
    // Check allocations (Rust's Vec will panic on allocation failure, but we'll handle it explicitly)
    if dest.litlens.is_none() || dest.dists.is_none() {
        process::exit(-1);
    }
    if dest.pos.is_none() {
        process::exit(-1);
    }
    if dest.ll_symbol.is_none() || dest.d_symbol.is_none() {
        process::exit(-1);
    }
    if dest.ll_counts.is_none() || dest.d_counts.is_none() {
        process::exit(-1);
    }
    
    dest.size = source.size;
    
    // Copy data from source to dest
    if let (Some(src_litlens), Some(dest_litlens)) = (&source.litlens, &mut dest.litlens) {
        let sub_source = &src_litlens[..dest_litlens.len()];
        dest_litlens.copy_from_slice(sub_source);
    }
    
    if let (Some(src_dists), Some(dest_dists)) = (&source.dists, &mut dest.dists) {
        let src_portion = &src_dists[..dest_dists.len()];
        dest_dists.copy_from_slice(src_portion);
    }
    
    if let (Some(src_pos), Some(dest_pos)) = (&source.pos, &mut dest.pos) {
        let src_portion = &src_pos[..dest_pos.len()];
        dest_pos.copy_from_slice(src_portion);
    }
    
    if let (Some(src_ll_symbol), Some(dest_ll_symbol)) = (&source.ll_symbol, &mut dest.ll_symbol) {
        let src_portion = &src_ll_symbol[..dest_ll_symbol.len()];
        dest_ll_symbol.copy_from_slice(src_portion);
    }
    
    if let (Some(src_d_symbol), Some(dest_d_symbol)) = (&source.d_symbol, &mut dest.d_symbol) {
        let src_portion = &src_d_symbol[..dest_d_symbol.len()];
        dest_d_symbol.copy_from_slice(src_portion);
    }
    
    if let (Some(src_ll_counts), Some(dest_ll_counts)) = (&source.ll_counts, &mut dest.ll_counts) {
        let src_portion = &src_ll_counts[..dest_ll_counts.len()];
        dest_ll_counts.copy_from_slice(src_portion);
    }
    
    if let (Some(src_d_counts), Some(dest_d_counts)) = (&source.d_counts, &mut dest.d_counts) {
        let src_portion = &src_d_counts[..dest_d_counts.len()];
        dest_d_counts.copy_from_slice(src_portion);
    }
}

pub fn ZopfliStoreLitLenDist(length: u16, dist: u16, pos: usize, store: &mut ZopfliLz77Store) {
    let origsize = store.size;
    let llstart = 288 * (origsize / 288);
    let dstart = 32 * (origsize / 32);

    if origsize % 288 == 0 {
        let mut llsize = origsize;
        for _ in 0..288 {
            if llsize == 0 || (llsize & (llsize - 1)) == 0 {
                let new_capacity = if llsize == 0 { 1 } else { llsize * 2 };
                store.ll_counts.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                    .resize(new_capacity, 0);
            }
            let val = if origsize == 0 { 0 } else { store.ll_counts.as_ref().unwrap()[(origsize - 288) + (llsize - origsize)] };
            store.ll_counts.as_mut().unwrap()[llsize] = val;
            llsize += 1;
        }
    }

    if origsize % 32 == 0 {
        let mut dsize = origsize;
        for _ in 0..32 {
            if dsize == 0 || (dsize & (dsize - 1)) == 0 {
                let new_capacity = if dsize == 0 { 1 } else { dsize * 2 };
                store.d_counts.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                    .resize(new_capacity, 0);
            }
            let val = if origsize == 0 { 0 } else { store.d_counts.as_ref().unwrap()[(origsize - 32) + (dsize - origsize)] };
            store.d_counts.as_mut().unwrap()[dsize] = val;
            dsize += 1;
        }
    }

    if store.size == 0 || (store.size & (store.size - 1)) == 0 {
        let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
        store.litlens.get_or_insert_with(|| Vec::with_capacity(new_capacity))
            .resize(new_capacity, 0);
    }
    store.litlens.as_mut().unwrap()[store.size] = length;
    store.size += 1;

    store.size = origsize;
    if store.size == 0 || (store.size & (store.size - 1)) == 0 {
        let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
        store.dists.get_or_insert_with(|| Vec::with_capacity(new_capacity))
            .resize(new_capacity, 0);
    }
    store.dists.as_mut().unwrap()[store.size] = dist;
    store.size += 1;

    store.size = origsize;
    if store.size == 0 || (store.size & (store.size - 1)) == 0 {
        let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
        store.pos.get_or_insert_with(|| Vec::with_capacity(new_capacity))
            .resize(new_capacity, 0);
    }
    store.pos.as_mut().unwrap()[store.size] = pos;
    store.size += 1;

    assert!(length < 259);
    if dist == 0 {
        store.size = origsize;
        if store.size == 0 || (store.size & (store.size - 1)) == 0 {
            let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
            store.ll_symbol.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                .resize(new_capacity, 0);
        }
        store.ll_symbol.as_mut().unwrap()[store.size] = length;
        store.size += 1;

        store.size = origsize;
        if store.size == 0 || (store.size & (store.size - 1)) == 0 {
            let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
            store.d_symbol.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                .resize(new_capacity, 0);
        }
        store.d_symbol.as_mut().unwrap()[store.size] = 0;
        store.size += 1;

        store.ll_counts.as_mut().unwrap()[llstart + length as usize] += 1;
    } else {
        store.size = origsize;
        if (store.size & (store.size - 1)) == 0 {
            let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
            store.ll_symbol.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                .resize(new_capacity, 0);
        }
        store.ll_symbol.as_mut().unwrap()[store.size] = ZopfliGetLengthSymbol(length as usize) as u16;
        store.size += 1;

        store.size = origsize;
        if (store.size & (store.size - 1)) == 0 {
            let new_capacity = if store.size == 0 { 1 } else { store.size * 2 };
            store.d_symbol.get_or_insert_with(|| Vec::with_capacity(new_capacity))
                .resize(new_capacity, 0);
        }
        store.d_symbol.as_mut().unwrap()[store.size] = ZopfliGetDistSymbol(dist as i32) as u16;
        store.size += 1;

        store.ll_counts.as_mut().unwrap()[llstart + ZopfliGetLengthSymbol(length as usize) as usize] += 1;
        store.d_counts.as_mut().unwrap()[dstart + ZopfliGetDistSymbol(dist as i32) as usize] += 1;
    }
}
pub fn TryGetFromLongestMatchCache(
    s: &ZopfliBlockState,
    pos: usize,
    limit: &mut usize,
    sublen: Option<&mut [u16]>,
    distance: &mut u16,
    length: &mut u16,
) -> bool {
    let lmcpos = pos - s.blockstart;
    
    let cache_available = s.lmc.as_ref().map_or(false, |lmc| {
        lmc.length.as_ref().map_or(false, |lengths| {
            lengths[lmcpos] == 0 || lmc.dist.as_ref().map_or(false, |dists| dists[lmcpos] != 0)
        })
    });

    let limit_ok_for_cache = cache_available && s.lmc.as_ref().map_or(false, |lmc| {
        let lmc_length = lmc.length.as_ref().unwrap()[lmcpos];
        (*limit == 258 || usize::from(lmc_length) <= *limit) || sublen.is_some() && 
            (usize::from(ZopfliMaxCachedSublen(lmc, lmcpos, usize::from(lmc_length))) >= *limit)
    });

    if s.lmc.is_some() && limit_ok_for_cache && cache_available {
        if let Some(lmc) = s.lmc.as_ref() {
            let lmc_length = lmc.length.as_ref().unwrap()[lmcpos];
            if sublen.is_none() || lmc_length <= ZopfliMaxCachedSublen(lmc, lmcpos, usize::from(lmc_length)) {
                *length = lmc_length;
                if usize::from(*length) > *limit {
                    *length = (*limit) as u16;
                }
                
                if let Some(sublen) = sublen {
                    ZopfliCacheToSublen(lmc, lmcpos, usize::from(*length), sublen);
                    *distance = sublen[usize::from(*length)];
                    if *limit == 258 && *length >= 3 {
                        assert!(sublen[usize::from(*length)] == lmc.dist.as_ref().unwrap()[lmcpos]);
                    }
                } else {
                    *distance = lmc.dist.as_ref().unwrap()[lmcpos];
                }
                return true;
            }
            *limit = usize::from(lmc_length);
        }
    }
    false
}

pub fn StoreInLongestMatchCache(
    s: &mut ZopfliBlockState,
    pos: usize,
    limit: usize,
    sublen: Option<&[u16]>,
    distance: u16,
    length: u16,
) {
    let lmcpos = pos - s.blockstart;
    let cache_available = s.lmc.as_ref().map_or(false, |lmc| {
        lmc.length.as_ref().map_or(false, |lengths| {
            lengths[lmcpos] == 0 || lmc.dist.as_ref().map_or(false, |dists| dists[lmcpos] != 0)
        })
    });

    if s.lmc.is_some() && limit == 258 && sublen.is_some() && !cache_available {
        if let Some(lmc) = s.lmc.as_mut() {
            assert!(lmc.length.as_ref().map_or(false, |lengths| lengths[lmcpos] == 1)
                && lmc.dist.as_ref().map_or(false, |dists| dists[lmcpos] == 0));

            if let Some(dists) = lmc.dist.as_mut() {
                dists[lmcpos] = if length < 3 { 0 } else { distance };
            }
            if let Some(lengths) = lmc.length.as_mut() {
                lengths[lmcpos] = if length < 3 { 0 } else { length };
            }

            assert!(!(lmc.length.as_ref().map_or(false, |lengths| lengths[lmcpos] == 1)
                && lmc.dist.as_ref().map_or(false, |dists| dists[lmcpos] == 0)));

            if let Some(sublen) = sublen {
                ZopfliSublenToCache(sublen, lmcpos, length as usize, lmc);
            }
        }
    }
}
pub fn ZopfliFindLongestMatch(
    s: &mut ZopfliBlockState,
    h: &ZopfliHash,
    array: &[u8],
    pos: usize,
    size: usize,
    mut limit: usize,  // Made mutable here
    sublen: &mut Option<&mut [u16]>,  // Changed to mutable reference
    distance: &mut u16,
    length: &mut u16,
) {
    let hpos = (pos & (32768 - 1)) as i32;
    let mut bestdist = 0u16;
    let mut bestlength = 1usize;
    let mut chain_counter = 8192;
    let mut dist = 0u16;

    if TryGetFromLongestMatchCache(s, pos, &mut limit, sublen.as_deref_mut(), distance, length) {
        assert!(pos + *length as usize <= size);
        return;
    }

    assert!(limit <= 258);
    assert!(limit >= 3);
    assert!(pos < size);

    if size - pos < 3 {
        *length = 0;
        *distance = 0;
        return;
    }

    if pos + limit > size {
        limit = size - pos;
    }

    let array_slice = &array[pos..];
    let arrayend = &array_slice[..limit];
    let arrayend_safe = if arrayend.len() >= 8 {
        &arrayend[..arrayend.len() - 8]
    } else {
        &[]
    };

    let hval = h.val;
    assert!(hval < 65536);

    let hhead = h.head.as_ref().expect("h.head is None");
    let hprev = h.prev.as_ref().expect("h.prev is None");
    let hhashval = h.hashval.as_ref().expect("h.hashval is None");

    let mut pp = hhead[hval as usize];
    let mut p = hprev[pp as usize] as i32;
    assert!(pp == hpos);

    dist = if p < pp {
        (pp - p) as u16
    } else {
        ((32768 - p) + pp) as u16
    };

    while dist < 32768 {
        let mut currentlength = 0u16;
        assert!(p < 32768);
        assert!(p == hprev[pp as usize] as i32);
        assert!(hhashval[p as usize] == hval);

        if dist > 0 {
            assert!(pos < size);
            assert!(dist as usize <= pos);

            let scan = &array[pos..];
            let match_ = &array[pos - dist as usize..];

            if pos + bestlength >= size || scan[bestlength] == match_[bestlength] {
                let same0 = h.same.as_ref().expect("h.same is None")[hpos as usize];
                if same0 > 2 && scan[0] == match_[0] {
                    let same1 = h.same.as_ref().expect("h.same is None")[(pos - dist as usize) & (32768 - 1)];
                    let same = if same0 < same1 { same0 } else { same1 };
                    let same = if same > limit as u16 { limit as u16 } else { same };

                    let scan_slice = &scan[same as usize..];
                    let match_slice = &match_[same as usize..];

                    if let Some(new_scan) = GetMatch(scan_slice, match_slice, arrayend, arrayend_safe) {
                        currentlength = (new_scan.as_ptr() as usize - scan.as_ptr() as usize) as u16;
                    }
                } else {
                    if let Some(new_scan) = GetMatch(scan, match_, arrayend, arrayend_safe) {
                        currentlength = (new_scan.as_ptr() as usize - scan.as_ptr() as usize) as u16;
                    }
                }
            }

            if currentlength > bestlength as u16 {
                if let Some(sublen_slice) = sublen.as_mut() {
                    for j in (bestlength + 1)..=currentlength as usize {
                        sublen_slice[j] = dist;
                    }
                }
                bestdist = dist;
                bestlength = currentlength as usize;
                if currentlength >= limit as u16 {
                    break;
                }
            }
        }

        if hhead.as_ptr() != h.head2.as_ref().expect("h.head2 is None").as_ptr()
            && bestlength >= h.same.as_ref().expect("h.same is None")[hpos as usize] as usize
            && h.val2 == h.hashval2.as_ref().expect("h.hashval2 is None")[p as usize]
        {
            pp = p;
            p = h.prev2.as_ref().expect("h.prev2 is None")[p as usize] as i32;
            dist += if p < pp {
                (pp - p) as u16
            } else {
                ((32768 - p) + pp) as u16
            };
        } else {
            pp = p;
            p = hprev[p as usize] as i32;
            if p == pp {
                break;
            }
            dist += if p < pp {
                (pp - p) as u16
            } else {
                ((32768 - p) + pp) as u16
            };
        }

        chain_counter -= 1;
        if chain_counter <= 0 {
            break;
        }
    }

    StoreInLongestMatchCache(
        s,
        pos,
        limit,
        sublen.as_deref(),
        bestdist,
        bestlength as u16,
    );
    assert!(bestlength <= limit);
    *distance = bestdist;
    *length = bestlength as u16;
    assert!(pos + *length as usize <= size);
}
pub fn ZopfliLZ77Greedy(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    store: &mut ZopfliLz77Store,
    h: &mut ZopfliHash,
) {
    let mut i = 0;
    let mut j;
    let mut leng: u16 = 0;
    let mut dist: u16 = 0;
    let mut lengthscore: i32;
    let windowstart = if instart > 32768 {
        instart - 32768
    } else {
        0
    };
    let mut dummysublen = [0u16; 259];
    let mut prev_length: u16 = 0;
    let mut prev_match: u16 = 0;
    let mut prevlengthscore: i32;
    let mut match_available = 0;

    if instart == inend {
        return;
    }

    ZopfliResetHash(32768, h);
    ZopfliWarmupHash(in_data, windowstart, inend, h);
    
    i = windowstart;
    while i < instart {
        ZopfliUpdateHash(in_data, i, inend, h);
        i += 1;
    }

    i = instart;
    while i < inend {
        ZopfliUpdateHash(in_data, i, inend, h);
        ZopfliFindLongestMatch(
            s,
            h,
            in_data,
            i,
            inend,
            258,
            &mut Some(&mut dummysublen),
            &mut dist,
            &mut leng,
        );
        lengthscore = GetLengthScore(leng as i32, dist as i32);
        prevlengthscore = GetLengthScore(prev_length as i32, prev_match as i32);

        if match_available != 0 {
            match_available = 0;
            if lengthscore > (prevlengthscore + 1) {
                ZopfliStoreLitLenDist(in_data[i - 1] as u16, 0, i - 1, store);
                if (lengthscore >= 3) && (leng < 258) {
                    match_available = 1;
                    prev_length = leng;
                    prev_match = dist;
                    continue;
                }
            } else {
                leng = prev_length;
                dist = prev_match;
                lengthscore = prevlengthscore;
                ZopfliVerifyLenDist(in_data, i - 1, dist, leng);
                ZopfliStoreLitLenDist(leng, dist, i - 1, store);
                j = 2;
                while j < leng {
                    assert!(i < inend);
                    i += 1;
                    ZopfliUpdateHash(in_data, i, inend, h);
                    j += 1;
                }
                continue;
            }
        } else if (lengthscore >= 3) && (leng < 258) {
            match_available = 1;
            prev_length = leng;
            prev_match = dist;
            continue;
        }

        if lengthscore >= 3 {
            ZopfliVerifyLenDist(in_data, i, dist, leng);
            ZopfliStoreLitLenDist(leng, dist, i, store);
        } else {
            leng = 1;
            ZopfliStoreLitLenDist(in_data[i] as u16, 0, i, store);
        }

        j = 1;
        while j < leng {
            assert!(i < inend);
            i += 1;
            ZopfliUpdateHash(in_data, i, inend, h);
            j += 1;
        }

        i += 1;
    }
}

pub fn ZopfliInitBlockState(
    options: Option<Box<ZopfliOptions>>,
    blockstart: usize,
    blockend: usize,
    add_lmc: bool,
    s: &mut ZopfliBlockState,
) {
    s.options = options;
    s.blockstart = blockstart;
    s.blockend = blockend;
    
    if add_lmc {
        let mut lmc = Box::new(ZopfliLongestMatchCache {
            length: None,
            dist: None,
            sublen: None,
        });
        ZopfliInitCache(blockend - blockstart, &mut lmc);
        s.lmc = Some(lmc);
    } else {
        s.lmc = None;
    }
}
pub fn ZopfliCleanBlockState(s: &mut ZopfliBlockState) {
    if let Some(mut lmc) = s.lmc.take() {
        ZopfliCleanCache(&mut *lmc);
        // The Box will be automatically dropped here, freeing the memory
    }
}
pub fn ZopfliAppendLZ77Store(store: &ZopfliLz77Store, target: &mut ZopfliLz77Store) {
    // Assuming store.litlens, store.dists, and store.pos are all Some(Vec<_>)
    if let (Some(litlens), Some(dists), Some(pos)) = (&store.litlens, &store.dists, &store.pos) {
        for i in 0..store.size {
            ZopfliStoreLitLenDist(litlens[i], dists[i], pos[i], target);
        }
    }
}
