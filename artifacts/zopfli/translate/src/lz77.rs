use crate::*;
use std::assert;

pub fn ZopfliVerifyLenDist(data: &[u8], pos: usize, dist: u16, length: u16) {
    assert!(pos + length as usize <= data.len());
    for i in 0..length as usize {
        assert_eq!(
            data[(pos - dist as usize) + i],
            data[pos + i],
            "Mismatch at position {}",
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
    match_: &[u8],
    end: &[u8],
    safe_end: &[u8],
) -> Option<&'a [u8]> {
    let mut match_idx = 0;
    let mut scan_idx = 0;

    // Check if we can compare in 8-byte chunks (64-bit system)
    if std::mem::size_of::<usize>() == 8 {
        while scan_idx + 8 <= scan.len()
            && scan_idx + 8 <= safe_end.len()
            && scan[scan_idx..scan_idx + 8] == match_[match_idx..match_idx + 8]
        {
            scan_idx += 8;
            match_idx += 8;
        }
    }
    // Check if we can compare in 4-byte chunks (32-bit system)
    else if std::mem::size_of::<u32>() == 4 {
        while scan_idx + 4 <= scan.len()
            && scan_idx + 4 <= safe_end.len()
            && scan[scan_idx..scan_idx + 4] == match_[match_idx..match_idx + 4]
        {
            scan_idx += 4;
            match_idx += 4;
        }
    }
    // Fall back to byte-by-byte comparison
    else {
        while scan_idx < scan.len()
            && scan_idx < safe_end.len()
            && scan[scan_idx] == match_[match_idx]
        {
            scan_idx += 1;
            match_idx += 1;
        }
    }

    // Final byte-by-byte comparison until end
    while scan_idx < scan.len()
        && scan_idx < end.len()
        && scan[scan_idx] == match_[match_idx]
    {
        scan_idx += 1;
        match_idx += 1;
    }

    Some(&scan[..scan_idx])
}
pub fn ZopfliInitLZ77Store(data: Option<&[u8]>, store: &mut ZopfliLZ77Store) {
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
pub fn ZopfliCleanLZ77Store(store: &mut ZopfliLZ77Store) {
    // In Rust, we don't need to explicitly free memory - dropping the Vec will handle it
    // We can just set all fields to None to clear them
    store.litlens = None;
    store.dists = None;
    store.pos = None;
    store.ll_symbol = None;
    store.d_symbol = None;
    store.ll_counts = None;
    store.d_counts = None;
    // Note: We don't clear `size` and `data` as they weren't in the original C function
}
pub fn ZopfliLZ77GetByteRange(lz77: &ZopfliLZ77Store, lstart: usize, lend: usize) -> usize {
    if lstart == lend {
        return 0;
    }
    
    let l = lend - 1;
    let pos = lz77.pos.as_ref().unwrap();
    let dists = lz77.dists.as_ref().unwrap();
    let litlens = lz77.litlens.as_ref().unwrap();
    
    (pos[l] + if dists[l] == 0 { 1 } else { litlens[l] as usize }) - pos[lstart]
}
pub fn ZopfliLZ77GetHistogramAt(
    lz77: &ZopfliLZ77Store,
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

    // Second loop: adjust ll_counts
    if let (Some(ref ll_symbol), Some(ref lz77_ll_counts)) = (&lz77.ll_symbol, &lz77.ll_counts) {
        for i in (lpos + 1)..(llpos + 288).min(lz77.size) {
            let symbol = ll_symbol[i] as usize;
            ll_counts[symbol] -= 1;
        }
    }

    // Third loop: copy d_counts
    if let Some(ref lz77_d_counts) = lz77.d_counts {
        for i in 0..32 {
            d_counts[i] = lz77_d_counts[dpos + i];
        }
    }

    // Fourth loop: adjust d_counts
    if let (Some(ref d_symbol), Some(ref dists), Some(ref lz77_d_counts)) = 
        (&lz77.d_symbol, &lz77.dists, &lz77.d_counts) 
    {
        for i in (lpos + 1)..(dpos + 32).min(lz77.size) {
            if dists[i] != 0 {
                let symbol = d_symbol[i] as usize;
                d_counts[symbol] -= 1;
            }
        }
    }
}
pub fn ZopfliLZ77GetHistogram(
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
    ll_counts: &mut [usize],
    d_counts: &mut [usize],
) {
    if (lstart + (288 * 3)) > lend {
        ll_counts.fill(0);
        d_counts.fill(0);
        
        if let (Some(ll_symbol), Some(dists), Some(d_symbol)) = (&lz77.ll_symbol, &lz77.dists, &lz77.d_symbol) {
            for i in lstart..lend {
                ll_counts[ll_symbol[i] as usize] += 1;
                if dists[i] != 0 {
                    d_counts[d_symbol[i] as usize] += 1;
                }
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
pub fn ZopfliCleanBlockState(s: &mut ZopfliBlockState) {
    if let Some(mut lmc) = s.lmc.take() {
        ZopfliCleanCache(&mut *lmc);
        // The Box will be dropped here, automatically freeing the memory
    }
}
pub fn helper_ZopfliStoreLitLenDist_1(
    length_ref: &mut u16,
    dist_ref: &mut u16,
    llstart_ref: &mut usize,
    dstart_ref: &mut usize,
    store: &mut ZopfliLZ77Store,
    origsize: usize,
) {
    let length = *length_ref;
    let dist = *dist_ref;
    let llstart = *llstart_ref;
    let dstart = *dstart_ref;
    
    store.size = origsize;
    
    // First block for ll_symbol
    {
        if (store.size & (store.size - 1)) == 0 {
            let new_size = if store.size == 0 { 1 } else { store.size * 2 };
            store.ll_symbol = Some(store.ll_symbol.take().map_or_else(
                || vec![0; new_size],
                |mut v| {
                    v.resize(new_size, 0);
                    v
                },
            ));
        }
        
        if let Some(ref mut ll_symbol) = store.ll_symbol {
            ll_symbol[store.size] = ZopfliGetDistSymbol(length as i32) as u16;
        }
        store.size += 1;
    }
    
    store.size = origsize;
    
    // Second block for d_symbol
    {
        if (store.size & (store.size - 1)) == 0 {
            let new_size = if store.size == 0 { 1 } else { store.size * 2 };
            store.d_symbol = Some(store.d_symbol.take().map_or_else(
                || vec![0; new_size],
                |mut v| {
                    v.resize(new_size, 0);
                    v
                },
            ));
        }
        
        if let Some(ref mut d_symbol) = store.d_symbol {
            d_symbol[store.size] = ZopfliGetDistSymbol(dist as i32) as u16;
        }
        store.size += 1;
    }
    
    // Update counts
    if let Some(ref mut ll_counts) = store.ll_counts {
        ll_counts[llstart + ZopfliGetDistSymbol(length as i32) as usize] += 1;
    }
    if let Some(ref mut d_counts) = store.d_counts {
        d_counts[dstart + ZopfliGetDistSymbol(dist as i32) as usize] += 1;
    }
    
    *length_ref = length;
    *dist_ref = dist;
    *llstart_ref = llstart;
    *dstart_ref = dstart;
}
pub fn ZopfliStoreLitLenDist(length: u16, dist: u16, pos: usize, store: &mut ZopfliLZ77Store) {
    let origsize = store.size;
    let llstart = 288 * (origsize / 288);
    let dstart = 32 * (origsize / 32);

    // Handle ll_counts expansion
    if origsize % 288 == 0 {
        let mut llsize = origsize;
        for _ in 0..288 {
            if (llsize & (llsize - 1)) == 0 {
                let new_size = if llsize == 0 { 1 } else { llsize * 2 };
                store.ll_counts = Some(store.ll_counts.take().map_or_else(
                    || vec![0; new_size],
                    |mut v| {
                        v.resize(new_size, 0);
                        v
                    },
                ));
            }
            
            if let Some(ref mut ll_counts) = store.ll_counts {
                ll_counts[llsize] = if origsize == 0 { 0 } else { ll_counts[(origsize - 288) + (llsize - origsize)] };
            }
            llsize += 1;
        }
    }

    // Handle d_counts expansion
    if origsize % 32 == 0 {
        let mut dsize = origsize;
        for _ in 0..32 {
            if (dsize & (dsize - 1)) == 0 {
                let new_size = if dsize == 0 { 1 } else { dsize * 2 };
                store.d_counts = Some(store.d_counts.take().map_or_else(
                    || vec![0; new_size],
                    |mut v| {
                        v.resize(new_size, 0);
                        v
                    },
                ));
            }
            
            if let Some(ref mut d_counts) = store.d_counts {
                d_counts[dsize] = if origsize == 0 { 0 } else { d_counts[(origsize - 32) + (dsize - origsize)] };
            }
            dsize += 1;
        }
    }

    // Store litlens
    {
        if (store.size & (store.size - 1)) == 0 {
            let new_size = if store.size == 0 { 1 } else { store.size * 2 };
            store.litlens = Some(store.litlens.take().map_or_else(
                || vec![0; new_size],
                |mut v| {
                    v.resize(new_size, 0);
                    v
                },
            ));
        }
        
        if let Some(ref mut litlens) = store.litlens {
            litlens[store.size] = length;
        }
        store.size += 1;
    }

    store.size = origsize;

    // Store dists
    {
        if (store.size & (store.size - 1)) == 0 {
            let new_size = if store.size == 0 { 1 } else { store.size * 2 };
            store.dists = Some(store.dists.take().map_or_else(
                || vec![0; new_size],
                |mut v| {
                    v.resize(new_size, 0);
                    v
                },
            ));
        }
        
        if let Some(ref mut dists) = store.dists {
            dists[store.size] = dist;
        }
        store.size += 1;
    }

    store.size = origsize;

    // Store pos
    {
        if (store.size & (store.size - 1)) == 0 {
            let new_size = if store.size == 0 { 1 } else { store.size * 2 };
            store.pos = Some(store.pos.take().map_or_else(
                || vec![0; new_size],
                |mut v| {
                    v.resize(new_size, 0);
                    v
                },
            ));
        }
        
        if let Some(ref mut pos_vec) = store.pos {
            pos_vec[store.size] = pos;
        }
        store.size += 1;
    }

    assert!(length < 259);

    if dist == 0 {
        store.size = origsize;
        
        // Store ll_symbol
        {
            if (store.size & (store.size - 1)) == 0 {
                let new_size = if store.size == 0 { 1 } else { store.size * 2 };
                store.ll_symbol = Some(store.ll_symbol.take().map_or_else(
                    || vec![0; new_size],
                    |mut v| {
                        v.resize(new_size, 0);
                        v
                    },
                ));
            }
            
            if let Some(ref mut ll_symbol) = store.ll_symbol {
                ll_symbol[store.size] = length;
            }
            store.size += 1;
        }

        store.size = origsize;

        // Store d_symbol
        {
            if (store.size & (store.size - 1)) == 0 {
                let new_size = if store.size == 0 { 1 } else { store.size * 2 };
                store.d_symbol = Some(store.d_symbol.take().map_or_else(
                    || vec![0; new_size],
                    |mut v| {
                        v.resize(new_size, 0);
                        v
                    },
                ));
            }
            
            if let Some(ref mut d_symbol) = store.d_symbol {
                d_symbol[store.size] = 0;
            }
            store.size += 1;
        }

        if let Some(ref mut ll_counts) = store.ll_counts {
            ll_counts[llstart + length as usize] += 1;
        }
    } else {
        helper_ZopfliStoreLitLenDist_1(
            &mut (length.clone()),
            &mut (dist.clone()),
            &mut (llstart.clone()),
            &mut (dstart.clone()),
            store,
            origsize,
        );
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
        lmc.length.as_ref().unwrap()[lmcpos] == 0 || lmc.dist.as_ref().unwrap()[lmcpos] != 0
    });
    
    let limit_ok_for_cache = cache_available && s.lmc.as_ref().map_or(false, |lmc| {
        *limit == 258 
        || lmc.length.as_ref().unwrap()[lmcpos] as usize <= *limit 
        || sublen.is_some() && usize::from(ZopfliMaxCachedSublen(lmc, lmcpos, lmc.length.as_ref().unwrap()[lmcpos] as usize)) >= *limit
    });

    if limit_ok_for_cache && cache_available {
        if let Some(lmc) = s.lmc.as_ref() {
            let length_val = lmc.length.as_ref().unwrap()[lmcpos];
            if sublen.is_none() || length_val <= ZopfliMaxCachedSublen(lmc, lmcpos, length_val as usize) as u16 {
                *length = length_val;
                if *length as usize > *limit {
                    *length = *limit as u16;
                }
                
                if let Some(sublen_slice) = sublen {
                    ZopfliCacheToSublen(lmc, lmcpos, *length as usize, sublen_slice);
                    *distance = sublen_slice[*length as usize];
                    if *limit == 258 && *length >= 3 {
                        assert!(sublen_slice[*length as usize] == lmc.dist.as_ref().unwrap()[lmcpos]);
                    }
                } else {
                    *distance = lmc.dist.as_ref().unwrap()[lmcpos];
                }
                return true;
            }
            *limit = lmc.length.as_ref().unwrap()[lmcpos] as usize;
        }
    }
    false
}

pub fn helper_helper_ZopfliFindLongestMatch_1_1(
    bestdist_ref: &mut u16,
    bestlength_ref: &mut u16,
    scan_idx_ref: &mut u32,
    match_idx_ref: &mut u32,
    currentlength_ref: &mut u16,
    h: &ZopfliHash,
    array: &[u8],
    pos: usize,
    size: usize,
    limit: usize,
    sublen: Option<&mut [u16]>,
    scan: &[u8],
    match_: &[u8],
    arrayend: &[u8],
    arrayend_safe: &[u8],
    dist: u16,
) {
    let mut bestdist = *bestdist_ref;
    let mut bestlength = *bestlength_ref;
    let mut scan_idx = *scan_idx_ref;
    let mut match_idx = *match_idx_ref;
    let mut currentlength = *currentlength_ref;

    assert!(pos < size);
    assert!(dist as usize <= pos);

    scan_idx = pos as u32;
    match_idx = (pos - dist as usize) as u32;

    if (pos + bestlength as usize >= size)
        || (scan[(scan_idx as usize + bestlength as usize)]
            == match_[(match_idx as usize + bestlength as usize)])
    {
        let same0 = h.same.as_ref().unwrap()[pos & (32768 - 1)];
        if same0 > 2 && scan[scan_idx as usize] == match_[match_idx as usize] {
            let same1 = h.same.as_ref().unwrap()[(pos - dist as usize) & (32768 - 1)];
            let mut same = if same0 < same1 { same0 } else { same1 };
            if same > limit as u16 {
                same = limit as u16;
            }
            scan_idx += same as u32;
            match_idx += same as u32;
        }

        let scan_slice = &scan[scan_idx as usize..];
        let match_slice = &match_[match_idx as usize..];
        if let Some(new_scan) = GetMatch(scan_slice, match_slice, arrayend, arrayend_safe) {
            currentlength = (new_scan.as_ptr() as usize - array[pos..].as_ptr() as usize) as u16;
        }
    }

    if currentlength > bestlength {
        if let Some(sublen) = sublen {
            for j in (bestlength + 1)..=currentlength {
                sublen[j as usize] = dist;
            }
        }
        bestdist = dist;
        bestlength = currentlength;
        if currentlength >= limit as u16 {
            return;
        }
    }

    *bestdist_ref = bestdist;
    *bestlength_ref = bestlength;
    *scan_idx_ref = scan_idx;
    *match_idx_ref = match_idx;
    *currentlength_ref = currentlength;
}
pub fn helper_ZopfliFindLongestMatch_1(
    p_ref: &mut u16,
    pp_ref: &mut u16,
    bestdist_ref: &mut u16,
    bestlength_ref: &mut u16,
    scan_idx_ref: &mut u32,
    match_idx_ref: &mut u32,
    chain_counter_ref: &mut i32,
    dist_ref: &mut u32,
    hhead_idx_ref: &mut u32,
    hprev_idx_ref: &mut u32,
    hhashval_idx_ref: &mut u32,
    hval_ref: &mut i32,
    h: &ZopfliHash,
    array: &[u8],
    pos: usize,
    size: usize,
    limit: usize,
    sublen: Option<&mut [u16]>,
    hpos: u16,
    scan: &[u8],
    match_: &[u8],
    arrayend: &[u8],
    arrayend_safe: &[u8],
    hhead: &[i32],
    hprev: &[u16],
    hhashval: &[i32],
) {
    let mut p = *p_ref;
    let mut pp = *pp_ref;
    let mut bestdist = *bestdist_ref;
    let mut bestlength = *bestlength_ref;
    let mut scan_idx = *scan_idx_ref;
    let mut match_idx = *match_idx_ref;
    let mut chain_counter = *chain_counter_ref;
    let mut dist = *dist_ref;
    let mut hhead_idx = *hhead_idx_ref;
    let mut hprev_idx = *hprev_idx_ref;
    let mut hhashval_idx = *hhashval_idx_ref;
    let mut hval = *hval_ref;
    let mut currentlength = 0;

    assert!(p < 32768);
    assert!(p == hprev[pp as usize + hprev_idx as usize]);
    assert!(hhashval[p as usize + hhashval_idx as usize] == hval);

    if dist > 0 {
        helper_helper_ZopfliFindLongestMatch_1_1(
            &mut bestdist,
            &mut bestlength,
            &mut scan_idx,
            &mut match_idx,
            &mut currentlength,
            h,
            array,
            pos,
            size,
            limit,
            sublen,
            scan,
            match_,
            arrayend,
            arrayend_safe,
            dist as u16,
        );
    }

    if hhead[hhead_idx as usize] != h.head2.as_ref().unwrap()[0]
        && bestlength >= h.same.as_ref().unwrap()[hpos as usize]
        && h.val2 == h.hashval2.as_ref().unwrap()[p as usize]
    {
        hhead_idx = h.head2.as_ref().unwrap()[0] as u32;
        hprev_idx = h.prev2.as_ref().unwrap()[0] as u32;
        hhashval_idx = h.hashval2.as_ref().unwrap()[0] as u32;
        hval = h.val2;
    }

    pp = p;
    p = hprev[p as usize + hprev_idx as usize];
    if p == pp {
        return;
    }

    dist += if p < pp {
        (pp - p) as u32
    } else {
        (32768 - p + pp) as u32
    };
    chain_counter -= 1;
    if chain_counter <= 0 {
        return;
    }

    *p_ref = p;
    *pp_ref = pp;
    *bestdist_ref = bestdist;
    *bestlength_ref = bestlength;
    *scan_idx_ref = scan_idx;
    *match_idx_ref = match_idx;
    *chain_counter_ref = chain_counter;
    *dist_ref = dist;
    *hhead_idx_ref = hhead_idx;
    *hprev_idx_ref = hprev_idx;
    *hhashval_idx_ref = hhashval_idx;
    *hval_ref = hval;
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
        (lmc.length.as_ref().unwrap()[lmcpos] == 0) || (lmc.dist.as_ref().unwrap()[lmcpos] != 0)
    });

    if s.lmc.is_some() && limit == 258 && sublen.is_some() && !cache_available {
        if let Some(lmc) = s.lmc.as_mut() {
            assert!(lmc.length.as_ref().unwrap()[lmcpos] == 1 && lmc.dist.as_ref().unwrap()[lmcpos] == 0);
            lmc.dist.as_mut().unwrap()[lmcpos] = if length < 3 { 0 } else { distance };
            lmc.length.as_mut().unwrap()[lmcpos] = if length < 3 { 0 } else { length };
            assert!(!(lmc.length.as_ref().unwrap()[lmcpos] == 1 && lmc.dist.as_ref().unwrap()[lmcpos] == 0));
            ZopfliSublenToCache(sublen.unwrap(), lmcpos, length as usize, lmc);
        }
    }
}
pub fn ZopfliFindLongestMatch(
    s: &mut ZopfliBlockState,
    h: &ZopfliHash,
    array: &[u8],
    pos: usize,
    size: usize,
    limit: &mut usize,
    mut sublen: Option<&mut [u16]>,
    distance: &mut u16,
    length: &mut u16,
) {
    let hpos = (pos & (32768 - 1)) as u16;
    let mut p;
    let mut pp;
    let mut bestdist = 0;
    let mut bestlength = 1;
    let mut chain_counter = 8192;
    let mut dist = 0;
    
    let hhead = h.head.as_ref().unwrap();
    let hprev = h.prev.as_ref().unwrap();
    let hhashval = h.hashval.as_ref().unwrap();
    let mut hval = h.val;

    if TryGetFromLongestMatchCache(s, pos, limit, sublen.as_deref_mut(), distance, length) {
        assert!(pos + (*length as usize) <= size);
        return;
    }

    assert!(*limit <= 258);
    assert!(*limit >= 3);
    assert!(pos < size);

    if size - pos < 3 {
        *length = 0;
        *distance = 0;
        return;
    }

    if pos + *limit > size {
        *limit = size - pos;
    }

    let arrayend = &array[pos..pos + *limit];
    let arrayend_safe = if arrayend.len() >= 8 {
        &arrayend[arrayend.len() - 8..]
    } else {
        arrayend
    };

    assert!(hval < 65536);
    pp = hhead[hval as usize] as u16;  // Cast to u16 here
    p = hprev[pp as usize];
    assert!(pp == hpos.into());

    dist = if i32::from(p) < pp as i32 {
        (pp - p) as u32
    } else {
        (32768 - p + pp) as u32
    };

    while dist < 32768 {
        helper_ZopfliFindLongestMatch_1(
            &mut p,
            &mut pp,
            &mut bestdist,
            &mut bestlength,
            &mut 0,
            &mut 0,
            &mut chain_counter,
            &mut dist,
            &mut 0,
            &mut 0,
            &mut 0,
            &mut hval,
            h,
            array,
            pos,
            size,
            *limit,
            sublen.as_deref_mut(),
            hpos,
            &[],
            &[],
            arrayend,
            arrayend_safe,
            hhead,
            hprev,
            hhashval,
        );
    }

    StoreInLongestMatchCache(s, pos, *limit, sublen.as_deref(), bestdist, bestlength);
    assert!(bestlength as usize <= *limit);
    *distance = bestdist;
    *length = bestlength;
    assert!(pos + (*length as usize) <= size);
}
pub fn ZopfliAppendLZ77Store(store: &ZopfliLZ77Store, target: &mut ZopfliLZ77Store) {
    for i in 0..store.size {
        let litlen = store.litlens.as_ref().map_or(0, |v| v[i]);
        let dist = store.dists.as_ref().map_or(0, |v| v[i]);
        let pos = store.pos.as_ref().map_or(0, |v| v[i]);
        ZopfliStoreLitLenDist(litlen, dist, pos, target);
    }
}
pub fn ZopfliInitBlockState(options: &ZopfliOptions, blockstart: usize, blockend: usize, add_lmc: bool, s: &mut ZopfliBlockState) {
    s.options = Some(Box::new(options.clone()));
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
pub fn helper_helper_ZopfliLZ77Greedy_1_1(
    i_ref: &mut usize,
    j_ref: &mut usize,
    leng_ref: &mut u16,
    dist_ref: &mut u16,
    lengthscore_ref: &mut i32,
    prev_length_ref: &mut u32,
    prev_match_ref: &mut u32,
    match_available_ref: &mut i32,
    in_data: &[u8],
    inend: usize,
    store: &mut ZopfliLZ77Store,
    h: &mut ZopfliHash,
    prevlengthscore: i32,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut leng = *leng_ref;
    let mut dist = *dist_ref;
    let mut lengthscore = *lengthscore_ref;
    let mut prev_length = *prev_length_ref;
    let mut prev_match = *prev_match_ref;
    let mut match_available = *match_available_ref;
    
    match_available = 0;
    
    if lengthscore > (prevlengthscore + 1) {
        ZopfliStoreLitLenDist(in_data[i - 1] as u16, 0, i - 1, store);
        if (lengthscore >= 3) && (leng < 258) {
            match_available = 1;
            prev_length = leng as u32;
            prev_match = dist as u32;
        }
    } else {
        leng = prev_length as u16;
        dist = prev_match as u16;
        lengthscore = prevlengthscore;
        ZopfliVerifyLenDist(in_data, i - 1, dist, leng);
        ZopfliStoreLitLenDist(leng, dist, i - 1, store);
        
        for j in 2..leng {
            assert!(i < inend);
            i += 1;
            ZopfliUpdateHash(in_data, i, inend, h);
        }
    }
    
    *i_ref = i;
    *j_ref = j;
    *leng_ref = leng;
    *dist_ref = dist;
    *lengthscore_ref = lengthscore;
    *prev_length_ref = prev_length;
    *prev_match_ref = prev_match;
    *match_available_ref = match_available;
}
pub fn helper_ZopfliLZ77Greedy_1(
    i_ref: &mut usize,
    j_ref: &mut usize,
    leng_ref: &mut u16,
    dist_ref: &mut u16,
    lengthscore_ref: &mut i32,
    prev_length_ref: &mut u32,
    prev_match_ref: &mut u32,
    prevlengthscore_ref: &mut i32,
    match_available_ref: &mut i32,
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    inend: usize,
    store: &mut ZopfliLZ77Store,
    h: &mut ZopfliHash,
    dummysublen: &mut [u16; 259],
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut leng = *leng_ref;
    let mut dist = *dist_ref;
    let mut lengthscore = *lengthscore_ref;
    let mut prev_length = *prev_length_ref;
    let mut prev_match = *prev_match_ref;
    let mut prevlengthscore = *prevlengthscore_ref;
    let mut match_available = *match_available_ref;

    ZopfliUpdateHash(in_data, i, inend, h);
    ZopfliFindLongestMatch(s, h, in_data, i, inend, &mut 258, Some(dummysublen), &mut dist, &mut leng);
    lengthscore = GetLengthScore(leng as i32, dist as i32);
    prevlengthscore = GetLengthScore(prev_length as i32, prev_match as i32);

    if match_available != 0 {
        helper_helper_ZopfliLZ77Greedy_1_1(
            &mut i,
            &mut j,
            &mut leng,
            &mut dist,
            &mut lengthscore,
            &mut prev_length,
            &mut prev_match,
            &mut match_available,
            in_data,
            inend,
            store,
            h,
            prevlengthscore,
        );
    } else if (lengthscore >= 3) && (leng < 258) {
        match_available = 1;
        prev_length = leng as u32;
        prev_match = dist as u32;
    }

    if lengthscore >= 3 {
        ZopfliVerifyLenDist(in_data, i, dist, leng);
        ZopfliStoreLitLenDist(leng, dist, i, store);
    } else {
        leng = 1;
        ZopfliStoreLitLenDist(in_data[i] as u16, 0, i, store);
    }

    for _ in 1..leng {
        assert!(i < inend);
        i += 1;
        ZopfliUpdateHash(in_data, i, inend, h);
    }

    *i_ref = i;
    *j_ref = j;
    *leng_ref = leng;
    *dist_ref = dist;
    *lengthscore_ref = lengthscore;
    *prev_length_ref = prev_length;
    *prev_match_ref = prev_match;
    *prevlengthscore_ref = prevlengthscore;
    *match_available_ref = match_available;
}
pub fn ZopfliLZ77Greedy(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    store: &mut ZopfliLZ77Store,
    h: &mut ZopfliHash,
) {
    let mut i = 0;
    let mut j = 0;
    let mut leng = 0;
    let mut dist = 0;
    let mut lengthscore = 0;
    let windowstart = if instart > 32768 { instart - 32768 } else { 0 };
    let mut dummysublen = [0u16; 259];
    let mut prev_length = 0;
    let mut prev_match = 0;
    let mut prevlengthscore = 0;
    let mut match_available = 0;

    if instart == inend {
        return;
    }

    ZopfliResetHash(32768, h);
    ZopfliWarmupHash(in_data, windowstart, inend, h);
    
    for i in windowstart..instart {
        ZopfliUpdateHash(in_data, i, inend, h);
    }

    let mut i = instart;
    while i < inend {
        helper_ZopfliLZ77Greedy_1(
            &mut i,
            &mut j,
            &mut leng,
            &mut dist,
            &mut lengthscore,
            &mut prev_length,
            &mut prev_match,
            &mut prevlengthscore,
            &mut match_available,
            s,
            in_data,
            inend,
            store,
            h,
            &mut dummysublen,
        );
    }
}
pub fn ZopfliCopyLZ77Store(source: &ZopfliLZ77Store, dest: &mut ZopfliLZ77Store) {
    let llsize = 288 * CeilDiv(source.size, 288);
    let dsize = 32 * CeilDiv(source.size, 32);
    
    ZopfliCleanLZ77Store(dest);
    ZopfliInitLZ77Store(source.data.as_deref(), dest);
    
    // Allocate vectors with appropriate sizes
    dest.litlens = Some(vec![0; source.size]);
    dest.dists = Some(vec![0; source.size]);
    dest.pos = Some(vec![0; source.size]);
    dest.ll_symbol = Some(vec![0; source.size]);
    dest.d_symbol = Some(vec![0; source.size]);
    dest.ll_counts = Some(vec![0; llsize]);
    dest.d_counts = Some(vec![0; dsize]);
    
    // In Rust, we don't need to check for allocation failure as Vec::new() will panic on OOM
    
    dest.size = source.size;
    
    // Copy data from source to dest
    if let (Some(src_litlens), Some(dest_litlens)) = (&source.litlens, &mut dest.litlens) {
        dest_litlens.copy_from_slice(src_litlens);
    }
    if let (Some(src_dists), Some(dest_dists)) = (&source.dists, &mut dest.dists) {
        dest_dists.copy_from_slice(src_dists);
    }
    if let (Some(src_pos), Some(dest_pos)) = (&source.pos, &mut dest.pos) {
        dest_pos.copy_from_slice(src_pos);
    }
    if let (Some(src_ll_symbol), Some(dest_ll_symbol)) = (&source.ll_symbol, &mut dest.ll_symbol) {
        dest_ll_symbol.copy_from_slice(src_ll_symbol);
    }
    if let (Some(src_d_symbol), Some(dest_d_symbol)) = (&source.d_symbol, &mut dest.d_symbol) {
        dest_d_symbol.copy_from_slice(src_d_symbol);
    }
    if let (Some(src_ll_counts), Some(dest_ll_counts)) = (&source.ll_counts, &mut dest.ll_counts) {
        dest_ll_counts[..llsize].copy_from_slice(&src_ll_counts[..llsize]);
    }
    if let (Some(src_d_counts), Some(dest_d_counts)) = (&source.d_counts, &mut dest.d_counts) {
        dest_d_counts[..dsize].copy_from_slice(&src_d_counts[..dsize]);
    }
}
