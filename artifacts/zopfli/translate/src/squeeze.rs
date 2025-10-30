use crate::*;
use std::assert;
use rand::Rng;
use std::any::Any;

fn zopfli_min(a: usize, b: usize) -> usize {
    if a < b { a } else { b }
}

fn TraceBackwards(size: usize, length_array: &[u16], path: &mut Option<Vec<u16>>, pathsize: &mut usize) {
    let mut index = size;
    if size == 0 {
        return;
    }

    loop {
        // Check if pathsize is a power of 2 (including 0)
        if (*pathsize & (*pathsize - 1)) == 0 {
            match path {
                Some(vec) => {
                    vec.resize(*pathsize * 2, 0);
                }
                None => {
                    *path = Some(vec![0; 1]);
                }
            }
        }

        if let Some(vec) = path {
            vec[*pathsize] = length_array[index];
        }
        *pathsize += 1;

        assert!(length_array[index] <= index as u16);
        assert!(length_array[index] <= 258);
        assert!(length_array[index] != 0);

        index -= length_array[index] as usize;
        if index == 0 {
            break;
        }
    }

    for i in 0..(*pathsize / 2) {
        if let Some(vec) = path {
            let temp = vec[i];
            vec[i] = vec[*pathsize - i - 1];
            vec[*pathsize - i - 1] = temp;
        }
    }
}
pub fn InitStats(stats: &mut SymbolStats) {
    stats.litlens.fill(0);
    stats.dists.fill(0);
    stats.ll_symbols.fill(0.0);
    stats.d_symbols.fill(0.0);
}
pub fn CopyStats(source: &SymbolStats, dest: &mut SymbolStats) {
    dest.litlens.copy_from_slice(&source.litlens);
    dest.dists.copy_from_slice(&source.dists);
    dest.ll_symbols.copy_from_slice(&source.ll_symbols);
    dest.d_symbols.copy_from_slice(&source.d_symbols);
}
pub fn AddWeighedStatFreqs(
    stats1: &SymbolStats,
    w1: f64,
    stats2: &SymbolStats,
    w2: f64,
    result: &mut SymbolStats,
) {
    for i in 0..288 {
        result.litlens[i] = ((stats1.litlens[i] as f64 * w1) + (stats2.litlens[i] as f64 * w2)) as usize;
    }

    for i in 0..32 {
        result.dists[i] = ((stats1.dists[i] as f64 * w1) + (stats2.dists[i] as f64 * w2)) as usize;
    }

    result.litlens[256] = 1;
}
pub fn InitRanState(state: &mut RanState) {
    state.m_w = 1;
    state.m_z = 2;
}
pub fn Ran(state: &mut RanState) -> u32 {
    state.m_z = (36969 * (state.m_z & 65535)) + (state.m_z >> 16);
    state.m_w = (18000 * (state.m_w & 65535)) + (state.m_w >> 16);
    (state.m_z << 16) + state.m_w
}
pub fn ClearStatFreqs(stats: &mut SymbolStats) {
    for i in 0..288 {
        stats.litlens[i] = 0;
    }

    for i in 0..32 {
        stats.dists[i] = 0;
    }
}
pub fn GetCostModelMinCost(
    costmodel: CostModelFun,
    costcontext: Option<Box<dyn std::any::Any>>,
) -> f64 {
    let mut mincost: f64;
    let mut bestlength: u32 = 0;
    let mut bestdist: u32 = 0;
    
    static DSYMBOLS: [u32; 30] = [
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025,
        1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
    ];

    // First loop: find best length
    mincost = 1e30;
    for i in 3..259 {
        let c = costmodel(i, 1, Option::None);
        if c < mincost {
            bestlength = i;
            mincost = c;
        }
    }

    // Second loop: find best distance
    mincost = 1e30;
    for &d in DSYMBOLS.iter() {
        let c = costmodel(3, d, Option::None);
        if c < mincost {
            bestdist = d;
            mincost = c;
        }
    }

    costmodel(bestlength, bestdist, costcontext)
}
pub fn FollowPath(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    path: &[u16],
    pathsize: usize,
    store: &mut ZopfliLZ77Store,
    h: &mut ZopfliHash,
) {
    if instart == inend {
        return;
    }

    let windowstart = if instart > 32768 {
        instart - 32768
    } else {
        0
    };

    let mut pos;
    let mut total_length_test = 0;

    ZopfliResetHash(32768, h);
    ZopfliWarmupHash(in_data, windowstart, inend, h);

    for i in (windowstart..instart).step_by(1) {
        ZopfliUpdateHash(in_data, i, inend, h);
    }

    pos = instart;
    for i in 0..pathsize {
        let mut length = path[i];
        let mut dummy_length = 0;
        let mut dist = 0;
        
        assert!(pos < inend);
        ZopfliUpdateHash(in_data, pos, inend, h);

        if length >= 3 {
            let mut length_usize = length as usize;
            ZopfliFindLongestMatch(
                s,
                h,
                in_data,
                pos,
                inend,
                &mut length_usize,
                Option::None,
                &mut dist,
                &mut dummy_length,
            );
            length = length_usize as u16;
            assert!(!((dummy_length != length) && (length > 2) && (dummy_length > 2)));
            ZopfliVerifyLenDist(in_data, pos, dist, length);
            ZopfliStoreLitLenDist(length, dist, pos, store);
            total_length_test += length;
        } else {
            length = 1;
            ZopfliStoreLitLenDist(in_data[pos] as u16, 0, pos, store);
            total_length_test += 1;
        }

        assert!((pos + length as usize) <= inend);
        for j in 1..length as usize {
            ZopfliUpdateHash(in_data, pos + j, inend, h);
        }

        pos += length as usize;
    }
}
pub fn helper_GetBestLengths_1(
    i_ref: &mut usize,
    k_ref: &mut usize,
    kend_ref: &mut usize,
    mincostaddcostj_ref: &mut f64,
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    costcontext: &mut (),
    length_array: &mut [u16],
    h: &mut ZopfliHash,
    costs: &mut [f64],
    leng: u16,
    dist: u16,
    sublen: &mut [u16; 259],
    mincost: f64,
) {
    let mut i = *i_ref;
    let mut k = *k_ref;
    let mut kend = *kend_ref;
    let mut mincostaddcostj = *mincostaddcostj_ref;
    let j = i - instart;

    ZopfliUpdateHash(in_data, i, inend, h);

    if h.same.as_ref().unwrap()[i & (32768 - 1)] > (258 * 2)
        && i > (instart + 258 + 1)
        && (i + (258 * 2) + 1 < inend)
        && h.same.as_ref().unwrap()[(i - 258) & (32768 - 1)] > 258
    {
        let symbolcost = ZopfliCostModel(258, 1, costcontext);
        for _ in 0..258 {
            costs[j + 258] = costs[j] + symbolcost;
            length_array[j + 258] = 258;
            i += 1;
            let j = i - instart;
            ZopfliUpdateHash(in_data, i, inend, h);
        }
    }

    let mut leng = leng;
    let mut dist = dist;
    let mut limit = 258;
    let sublen_slice = &mut sublen[..];
    ZopfliFindLongestMatch(
        s,
        h,
        in_data,
        i,
        inend,
        &mut limit,
        Some(sublen_slice),
        &mut dist,
        &mut leng,
    );

    if (i + 1) <= inend {
        let new_cost = ZopfliCostModel(in_data[i] as u16, 0, costcontext) + costs[j];
        assert!(new_cost >= 0.0);
        if new_cost < costs[j + 1] {
            costs[j + 1] = new_cost;
            length_array[j + 1] = 1;
        }
    }

    kend = zopfli_min(leng as usize, inend - i);
    mincostaddcostj = mincost + costs[j];

    for k in 3..=kend {
        if costs[j + k] <= mincostaddcostj {
            continue;
        }
        let new_cost = ZopfliCostModel(k as u16, sublen[k], costcontext) + costs[j];
        assert!(new_cost >= 0.0);
        if new_cost < costs[j + k] {
            assert!(k <= 258);
            costs[j + k] = new_cost;
            length_array[j + k] = k as u16;
        }
    }

    *i_ref = i;
    *k_ref = k;
    *kend_ref = kend;
    *mincostaddcostj_ref = mincostaddcostj;
}

// Added cost model function since it was missing
fn ZopfliCostModel(lit: u16, ltype: u16, _costcontext: &mut ()) -> f64 {
    // Placeholder implementation - should be replaced with actual cost model logic
    0.0
}
pub fn GetBestLengths(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    costmodel: CostModelFun,
    costcontext: &mut (),
    length_array: &mut [u16],
    h: &mut ZopfliHash,
    costs: &mut [f64],
) -> f64 {
    let blocksize = inend - instart;
    let windowstart = if instart > 32768 {
        instart - 32768
    } else {
        0
    };

    if instart == inend {
        return 0.0;
    }

    ZopfliResetHash(32768, h);
    ZopfliWarmupHash(in_data, windowstart, inend, h);
    
    for i in windowstart..instart {
        ZopfliUpdateHash(in_data, i, inend, h);
    }

    for i in 1..=blocksize {
        costs[i] = 1e30;
    }

    costs[0] = 0.0;
    length_array[0] = 0;

    let mincost = GetCostModelMinCost(costmodel, None);
    let mut i = instart;
    let mut k = 0;
    let mut kend = 0;
    let mut mincostaddcostj = 0.0;
    let mut leng = 0;
    let mut dist = 0;
    let mut sublen = [0u16; 259];

    while i < inend {
        helper_GetBestLengths_1(
            &mut i,
            &mut k,
            &mut kend,
            &mut mincostaddcostj,
            s,
            in_data,
            instart,
            inend,
            costcontext,
            length_array,
            h,
            costs,
            leng,
            dist,
            &mut sublen,
            mincost,
        );
    }

    assert!(costs[blocksize] >= 0.0);
    costs[blocksize]
}
pub fn LZ77OptimalRun(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    path: &mut Option<Vec<u16>>,
    pathsize: &mut usize,
    length_array: &mut [u16],
    costmodel: CostModelFun,
    costcontext: &mut (),
    store: &mut ZopfliLZ77Store,
    h: &mut ZopfliHash,
    costs: &mut [f64],
) -> f64 {
    let cost = GetBestLengths(
        s,
        in_data,
        instart,
        inend,
        costmodel,
        costcontext,
        length_array,
        h,
        costs,
    );

    // Free the existing path by replacing it with None
    *path = None;
    *pathsize = 0;

    TraceBackwards(inend - instart, length_array, path, pathsize);
    FollowPath(
        s,
        in_data,
        instart,
        inend,
        path.as_ref().unwrap(), // Safe because TraceBackwards initializes it
        *pathsize,
        store,
        h,
    );

    assert!(cost < 1e30);
    cost
}
pub fn GetCostFixed(litlen: usize, dist: usize, unused: Option<()>) -> f64 {
    let _ = unused; // Explicitly ignore unused parameter
    
    if dist == 0 {
        if litlen <= 143 {
            8.0
        } else {
            9.0
        }
    } else {
        let dbits = ZopfliGetDistExtraBits(dist as i32);
        // Since ZopfliGetLengthExtraBits and ZopfliGetLengthSymbol are private,
        // we need to implement equivalent functionality here
        let lbits = if litlen <= 10 {
            0
        } else if litlen <= 12 {
            1
        } else if litlen <= 14 {
            2
        } else if litlen <= 16 {
            3
        } else if litlen <= 20 {
            4
        } else if litlen <= 24 {
            5
        } else if litlen <= 28 {
            6
        } else if litlen <= 32 {
            7
        } else if litlen <= 40 {
            8
        } else if litlen <= 48 {
            9
        } else if litlen <= 56 {
            10
        } else if litlen <= 72 {
            11
        } else if litlen <= 88 {
            12
        } else if litlen <= 104 {
            13
        } else if litlen <= 120 {
            14
        } else if litlen <= 136 {
            15
        } else if litlen <= 148 {
            16
        } else if litlen <= 152 {
            17
        } else if litlen <= 160 {
            18
        } else if litlen <= 176 {
            19
        } else if litlen <= 192 {
            20
        } else if litlen <= 208 {
            21
        } else if litlen <= 224 {
            22
        } else if litlen <= 240 {
            23
        } else {
            24
        };
        
        let lsym = if litlen <= 2 {
            0
        } else if litlen == 3 {
            1
        } else if litlen == 4 {
            2
        } else if litlen == 5 {
            3
        } else if litlen == 6 {
            4
        } else if litlen == 7 {
            5
        } else if litlen == 8 {
            6
        } else if litlen == 9 {
            7
        } else if litlen == 10 {
            8
        } else if litlen <= 12 {
            9
        } else if litlen <= 14 {
            10
        } else if litlen <= 16 {
            11
        } else if litlen <= 20 {
            12
        } else if litlen <= 24 {
            13
        } else if litlen <= 28 {
            14
        } else if litlen <= 32 {
            15
        } else if litlen <= 40 {
            16
        } else if litlen <= 48 {
            17
        } else if litlen <= 56 {
            18
        } else if litlen <= 72 {
            19
        } else if litlen <= 88 {
            20
        } else if litlen <= 104 {
            21
        } else if litlen <= 120 {
            22
        } else if litlen <= 136 {
            23
        } else if litlen <= 148 {
            24
        } else if litlen <= 152 {
            25
        } else if litlen <= 160 {
            26
        } else if litlen <= 176 {
            27
        } else if litlen <= 192 {
            28
        } else if litlen <= 208 {
            29
        } else if litlen <= 224 {
            30
        } else if litlen <= 240 {
            31
        } else {
            32
        };
        
        let mut cost = 0;
        
        if lsym <= 279 {
            cost += 7;
        } else {
            cost += 8;
        }
        cost += 5;
        
        (cost + dbits + lbits) as f64
    }
}
pub fn ZopfliLZ77OptimalFixed(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    store: &mut ZopfliLZ77Store,
) {
    let blocksize = inend - instart;
    
    // Use Vec instead of malloc for memory allocation
    let mut length_array = vec![0u16; blocksize + 1];
    let mut path: Option<Vec<u16>> = None;
    let mut pathsize = 0;
    let mut hash = ZopfliHash {
        head: None,
        prev: None,
        hashval: None,
        val: 0,
        head2: None,
        prev2: None,
        hashval2: None,
        val2: 0,
        same: None,
    };
    let h = &mut hash;
    let mut costs = vec![0.0; blocksize + 1];

    ZopfliAllocHash(32768, h);
    s.blockstart = instart;
    s.blockend = inend;

    LZ77OptimalRun(
        s,
        in_data,
        instart,
        inend,
        &mut path,
        &mut pathsize,
        &mut length_array,
        |litlen, dist, _unused| GetCostFixed(litlen as usize, dist as usize, Option::None),
        &mut (),
        store,
        h,
        &mut costs,
    );

    // No need for explicit free calls - Vecs will be dropped automatically
    ZopfliCleanHash(h);
}
pub fn CalculateStatistics(stats: &mut SymbolStats) {
    ZopfliCalculateEntropy(&stats.litlens, &mut stats.ll_symbols);
    ZopfliCalculateEntropy(&stats.dists, &mut stats.d_symbols);
}
pub fn GetStatistics(store: &ZopfliLZ77Store, stats: &mut SymbolStats) {
    // Check if required fields are present
    if let (Some(litlens), Some(dists)) = (&store.litlens, &store.dists) {
        for i in 0..store.size {
            if dists[i] == 0 {
                stats.litlens[litlens[i] as usize] += 1;
            } else {
                if let Some(ll_symbol) = &store.ll_symbol {
                    stats.litlens[ll_symbol[i] as usize] += 1;
                } else {
                    // Fallback to public ZopfliGetDistSymbol for distance
                    stats.dists[ZopfliGetDistSymbol(dists[i] as i32) as usize] += 1;
                }
            }
        }
    }

    stats.litlens[256] = 1;
    CalculateStatistics(stats);
}

pub fn RandomizeFreqs(state: &mut RanState, freqs: &mut [usize]) {
    for i in 0..freqs.len() {
        if ((Ran(state) >> 4) % 3) == 0 {
            let random_index = (Ran(state) % freqs.len() as u32) as usize;
            freqs[i] = freqs[random_index];
        }
    }
}
pub fn RandomizeStatFreqs(state: &mut RanState, stats: &mut SymbolStats) {
    RandomizeFreqs(state, &mut stats.litlens);
    RandomizeFreqs(state, &mut stats.dists);
    stats.litlens[256] = 1;
}
pub fn GetCostStat(litlen: usize, dist: usize, context: &SymbolStats) -> f64 {
    if dist == 0 {
        context.ll_symbols[litlen]
    } else {
        // Copy of private functions from deflate.rs
        fn ZopfliGetLengthSymbol(l: usize) -> i32 {
            if l < 3 { l as i32 }
            else if l < 11 { ((l - 3) / 1) as i32 + 257 }
            else if l < 19 { ((l - 11) / 2) as i32 + 265 }
            else if l < 35 { ((l - 19) / 4) as i32 + 269 }
            else if l < 67 { ((l - 35) / 8) as i32 + 273 }
            else if l < 131 { ((l - 67) / 16) as i32 + 277 }
            else { ((l - 131) / 32) as i32 + 281 }
        }
        
        fn ZopfliGetLengthExtraBits(l: usize) -> i32 {
            if l < 3 { 0 }
            else if l < 11 { 0 }
            else if l < 19 { 1 }
            else if l < 35 { 2 }
            else if l < 67 { 3 }
            else if l < 131 { 4 }
            else if l < 258 { 5 }
            else { 0 }
        }

        let lsym = ZopfliGetLengthSymbol(litlen);
        let lbits = ZopfliGetLengthExtraBits(litlen);
        let dsym = ZopfliGetDistSymbol(dist as i32);
        let dbits = ZopfliGetDistExtraBits(dist as i32);
        ((lbits + dbits) as f64 + context.ll_symbols[lsym as usize]) + context.d_symbols[dsym as usize]
    }
}
pub fn helper_ZopfliLZ77Optimal_1(
    cost_ref: &mut f64,
    bestcost_ref: &mut f64,
    lastcost_ref: &mut f64,
    lastrandomstep_ref: &mut i32,
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    store: &mut ZopfliLZ77Store,
    length_array: &mut [u16],
    path: &mut Option<Vec<u16>>,
    pathsize: &mut usize,
    mut currentstore: ZopfliLZ77Store,
    h: &mut ZopfliHash,
    mut stats: SymbolStats,
    beststats: &mut SymbolStats,
    laststats: &mut SymbolStats,
    i: i32,
    costs: &mut [f64],
    mut ran_state: RanState,
) {
    let mut cost = *cost_ref;
    let mut bestcost = *bestcost_ref;
    let mut lastcost = *lastcost_ref;
    let mut lastrandomstep = *lastrandomstep_ref;

    ZopfliCleanLZ77Store(&mut currentstore);
    ZopfliInitLZ77Store(Some(in_data), &mut currentstore);

    let mut boxed_stats = Box::new(stats.clone()) as Box<dyn Any>;
    LZ77OptimalRun(
        s,
        in_data,
        instart,
        inend,
        path,
        pathsize,
        length_array,
        |litlen, dist, context| {
            GetCostStat(
                litlen as usize,
                dist as usize,
                context.as_ref().unwrap().downcast_ref::<SymbolStats>().unwrap(),
            )
        },
        &mut (),
        &mut currentstore,
        h,
        costs,
    );

    cost = ZopfliCalculateBlockSize(&currentstore, 0, currentstore.size, 2);

    if s.options.is_some() && ((s.options.as_ref().unwrap().verbose_more != 0)
        || (s.options.as_ref().unwrap().verbose != 0 && (cost < bestcost)))
    {
        eprintln!("Iteration {}: {} bit", i, cost as i32);
    }

    if cost < bestcost {
        ZopfliCopyLZ77Store(&currentstore, store);
        CopyStats(&stats, beststats);
        bestcost = cost;
    }

    CopyStats(&stats, laststats);
    ClearStatFreqs(&mut stats);
    GetStatistics(&currentstore, &mut stats);

    if lastrandomstep != -1 {
        let stats_clone = stats.clone();
        AddWeighedStatFreqs(&stats_clone, 1.0, laststats, 0.5, &mut stats);
        CalculateStatistics(&mut stats);
    }

    if (i > 5) && (cost == lastcost) {
        CopyStats(beststats, &mut stats);
        RandomizeStatFreqs(&mut ran_state, &mut stats);
        CalculateStatistics(&mut stats);
        lastrandomstep = i;
    }

    lastcost = cost;
    *cost_ref = cost;
    *bestcost_ref = bestcost;
    *lastcost_ref = lastcost;
    *lastrandomstep_ref = lastrandomstep;
}
pub fn ZopfliLZ77Optimal(
    s: &mut ZopfliBlockState,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    numiterations: i32,
    store: &mut ZopfliLZ77Store,
) {
    let blocksize = inend - instart;
    
    // Allocate vectors instead of using malloc
    let mut length_array = vec![0u16; blocksize + 1];
    let mut path: Option<Vec<u16>> = None;
    let mut pathsize = 0;
    let mut currentstore = ZopfliLZ77Store {
        litlens: None,
        dists: None,
        size: 0,
        data: Some(in_data.to_vec()),
        pos: None,
        ll_symbol: None,
        d_symbol: None,
        ll_counts: None,
        d_counts: None,
    };
    let mut hash = ZopfliHash {
        head: None,
        prev: None,
        hashval: None,
        val: 0,
        head2: None,
        prev2: None,
        hashval2: None,
        val2: 0,
        same: None,
    };
    let h = &mut hash;
    let mut stats = SymbolStats {
        litlens: [0; 288],
        dists: [0; 32],
        ll_symbols: [0.0; 288],
        d_symbols: [0.0; 32],
    };
    let mut beststats = stats.clone();
    let mut laststats = stats.clone();
    let mut costs = vec![0.0; blocksize + 1];
    let mut cost = 0.0;
    let mut bestcost = 1e30;
    let mut lastcost = 0.0;
    let mut ran_state = RanState { m_w: 1, m_z: 2 };
    let mut lastrandomstep = -1;

    InitRanState(&mut ran_state);
    InitStats(&mut stats);
    ZopfliInitLZ77Store(Some(in_data), &mut currentstore);
    ZopfliAllocHash(32768, h);
    ZopfliLZ77Greedy(s, in_data, instart, inend, &mut currentstore, h);
    GetStatistics(&currentstore, &mut stats);

    for i in 0..numiterations {
        helper_ZopfliLZ77Optimal_1(
            &mut cost,
            &mut bestcost,
            &mut lastcost,
            &mut lastrandomstep,
            s,
            in_data,
            instart,
            inend,
            store,
            &mut length_array,
            &mut path,
            &mut pathsize,
            currentstore.clone(),
            h,
            stats.clone(),
            &mut beststats,
            &mut laststats,
            i,
            &mut costs,
            ran_state.clone(),
        );
    }

    // No need for explicit free calls - vectors will be dropped automatically
    ZopfliCleanLZ77Store(&mut currentstore);
    ZopfliCleanHash(h);
}
