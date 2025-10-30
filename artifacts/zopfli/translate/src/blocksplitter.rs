use crate::*;
use std::io;
use std::io::Write;

pub fn ZopfliBlockSplitSimple(
    in_data: &[u8],
    instart: usize,
    inend: usize,
    blocksize: usize,
    splitpoints: &mut Option<Vec<usize>>,
    npoints: &mut usize,
) {
    let mut i = instart;
    while i < inend {
        // Check if npoints is a power of two (including zero)
        if (*npoints & (*npoints - 1)) == 0 {
            // Equivalent to the C realloc logic
            match splitpoints {
                Some(vec) => {
                    let new_capacity = if *npoints == 0 { 1 } else { *npoints * 2 };
                    vec.reserve(new_capacity - vec.len());
                }
                None => {
                    *splitpoints = Some(Vec::with_capacity(1));
                }
            }
        }

        if let Some(vec) = splitpoints {
            vec.push(i);
        }
        *npoints += 1;
        i += blocksize;
    }
}
pub fn AddSorted(value: usize, out: &mut Option<Vec<usize>>, outsize: &mut usize) {
    // Check if outsize is a power of two (including zero)
    if (*outsize & (*outsize - 1)) == 0 {
        match out {
            Some(vec) => {
                // Double the capacity when outsize is a power of two
                if *outsize == 0 {
                    *out = Some(vec![0; 1]);
                } else {
                    vec.resize(*outsize * 2, 0);
                }
            }
            None => {
                // Initialize with capacity 1 if out is None
                *out = Some(vec![0; 1]);
            }
        }
    }

    // Push the value to the end (will be sorted later)
    if let Some(vec) = out {
        if *outsize >= vec.len() {
            vec.push(value);
        } else {
            vec[*outsize] = value;
        }
        *outsize += 1;
    }

    // Perform insertion sort to maintain sorted order
    if let Some(vec) = out {
        for i in 0..(*outsize - 1) {
            if vec[i] > value {
                // Shift elements to make space
                for j in (i + 1..*outsize).rev() {
                    vec[j] = vec[j - 1];
                }
                // Insert the value at the correct position
                vec[i] = value;
                break;
            }
        }
    }
}
pub fn FindLargestSplittableBlock(
    lz77size: usize,
    done: &[u8],
    splitpoints: &[usize],
    npoints: usize,
    lstart: &mut usize,
    lend: &mut usize,
) -> bool {
    let mut longest = 0;
    let mut found = false;

    for i in 0..=npoints {
        let start = if i == 0 { 0 } else { splitpoints[i - 1] };
        let end = if i == npoints {
            lz77size - 1
        } else {
            splitpoints[i]
        };

        if done[start] == 0 && (end - start) > longest {
            *lstart = start;
            *lend = end;
            found = true;
            longest = end - start;
        }
    }

    found
}
pub fn helper_FindMinimum_1<F>(
    start_ref: &mut usize,
    end_ref: &mut usize,
    context: &mut (),
    smallest: &mut f64,
    f: F,
) -> usize
where
    F: Fn(usize, &mut ()) -> f64,
{
    let mut start = *start_ref;
    let mut end = *end_ref;
    let mut p = [0; 9];
    let mut vp = [0.0; 9];
    let mut besti;
    let mut best;
    let mut lastbest = 1e30;
    let mut pos = start;

    loop {
        if (end - start) <= 9 {
            break;
        }

        for i in 0..9 {
            p[i] = start + ((i + 1) * ((end - start) / (9 + 1)));
            vp[i] = f(p[i], context);
        }

        besti = 0;
        best = vp[0];
        for i in 1..9 {
            if vp[i] < best {
                best = vp[i];
                besti = i;
            }
        }

        if best > lastbest {
            break;
        }

        start = if besti == 0 { start } else { p[besti - 1] };
        end = if besti == (9 - 1) { end } else { p[besti + 1] };
        pos = p[besti];
        lastbest = best;
    }

    *smallest = lastbest;
    *start_ref = start;
    *end_ref = end;
    pos
}

pub fn PrintBlockSplitPoints(lz77: &ZopfliLZ77Store, lz77splitpoints: &[usize], nlz77points: usize) {
    let mut splitpoints = Vec::new();
    let mut npoints = 0;
    let mut pos = 0;

    if nlz77points > 0 {
        for i in 0..lz77.size {
            let length = if lz77.dists.as_ref().unwrap()[i] == 0 {
                1
            } else {
                lz77.litlens.as_ref().unwrap()[i] as usize
            };

            if lz77splitpoints[npoints] == i {
                splitpoints.push(pos);
                npoints += 1;

                if npoints == nlz77points {
                    break;
                }
            }
            pos += length;
        }
    }

    assert_eq!(npoints, nlz77points);
    
    let stderr = io::stderr();
    let mut handle = stderr.lock();
    
    write!(handle, "block split points: ").unwrap();
    for &point in &splitpoints {
        write!(handle, "{} ", point).unwrap();
    }

    write!(handle, "(hex:").unwrap();
    for &point in &splitpoints {
        write!(handle, " {:x}", point).unwrap();
    }
    writeln!(handle, ")").unwrap();
}
pub fn FindMinimum(
    f: FindMinimumFun,
    context: Option<Box<dyn std::any::Any>>,
    start: usize,
    end: usize,
    smallest: &mut f64,
) -> usize {
    if (end - start) < 1024 {
        let mut best = 1e30;
        let mut result = start;
        
        for i in start..end {
            let v = f(i, Option::None);
            if v < best {
                best = v;
                result = i;
            }
        }

        *smallest = best;
        result
    } else {
        let mut start = start;
        let mut end = end;
        helper_FindMinimum_1(
            &mut start,
            &mut end,
            &mut (),
            smallest,
            move |i, _| f(i, Option::None),
        )
    }
}
pub fn EstimateCost(lz77: &ZopfliLZ77Store, lstart: usize, lend: usize) -> f64 {
    ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend)
}
pub fn SplitCost(i: usize, context: &SplitCostContext) -> f64 {
    let c = context;
    EstimateCost(c.lz77.as_ref().unwrap(), c.start, i) + EstimateCost(c.lz77.as_ref().unwrap(), i, c.end)
}
pub fn helper_ZopfliBlockSplitLZ77_1(
    lstart_ref: &mut usize,
    llpos_ref: &mut usize,
    numblocks_ref: &mut usize,
    done_idx_ref: &mut u32,
    origcost_ref: &mut f64,
    lz77: &ZopfliLZ77Store,
    maxblocks: usize,
    splitpoints: &mut Option<Vec<usize>>,
    npoints: &mut usize,
    mut lend: usize,
    done: &mut [u8],
    splitcost: f64,
) -> Option<()> {
    let mut lstart = *lstart_ref;
    let mut llpos = *llpos_ref;
    let mut numblocks = *numblocks_ref;
    let done_idx = *done_idx_ref;
    let mut origcost = *origcost_ref;

    if maxblocks > 0 && numblocks >= maxblocks {
        return None;
    }

    let mut c = SplitCostContext {
        lz77: Some(lz77.clone()),
        start: lstart,
        end: lend,
    };

    assert!(lstart < lend);
    llpos = FindMinimum(
        |i, ctx| SplitCost(i, ctx.unwrap().downcast_ref::<SplitCostContext>().unwrap()),
        Some(Box::new(c.clone())),
        lstart + 1,
        lend,
        &mut splitcost.clone(),
    );
    assert!(llpos > lstart);
    assert!(llpos < lend);

    origcost = EstimateCost(lz77, lstart, lend);

    if splitcost > origcost || llpos == lstart + 1 || llpos == lend {
        done[lstart + done_idx as usize] = 1;
    } else {
        AddSorted(llpos, splitpoints, npoints);
        numblocks += 1;
    }

    if !FindLargestSplittableBlock(
        lz77.size,
        done,
        splitpoints.as_ref().unwrap_or(&vec![]),
        *npoints,
        &mut lstart,
        &mut lend,
    ) {
        return None;
    }

    if lend - lstart < 10 {
        return None;
    }

    *lstart_ref = lstart;
    *llpos_ref = llpos;
    *numblocks_ref = numblocks;
    *done_idx_ref = done_idx;
    *origcost_ref = origcost;

    Some(())
}
pub fn ZopfliBlockSplitLZ77(
    options: &ZopfliOptions,
    lz77: &ZopfliLZ77Store,
    maxblocks: usize,
    splitpoints: &mut Option<Vec<usize>>,
    npoints: &mut usize,
) {
    if lz77.size < 10 {
        return;
    }

    let mut done = vec![0u8; lz77.size];
    let mut done_idx = 0u32;
    let mut lstart = 0;
    let mut lend = lz77.size;
    let mut llpos = 0;
    let mut numblocks = 1;
    let mut splitcost = 0.0;
    let mut origcost = 0.0;

    loop {
        let result = helper_ZopfliBlockSplitLZ77_1(
            &mut lstart,
            &mut llpos,
            &mut numblocks,
            &mut done_idx,
            &mut origcost,
            lz77,
            maxblocks,
            splitpoints,
            npoints,
            lend,
            &mut done,
            splitcost,
        );

        if result.is_none() {
            break;
        }
    }

    if options.verbose != 0 {
        PrintBlockSplitPoints(
            lz77,
            splitpoints.as_ref().unwrap_or(&Vec::new()),
            *npoints,
        );
    }
}
pub fn ZopfliBlockSplit(
    options: &ZopfliOptions,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    maxblocks: usize,
    splitpoints: &mut Option<Vec<usize>>,
    npoints: &mut usize,
) {
    let mut pos = instart;
    let mut s = ZopfliBlockState {
        options: None,
        lmc: None,
        blockstart: 0,
        blockend: 0,
    };
    let mut lz77splitpoints = None;
    let mut nlz77points = 0;
    let mut store = ZopfliLZ77Store {
        litlens: None,
        dists: None,
        size: 0,
        data: None,
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
    
    ZopfliInitLZ77Store(Some(in_data), &mut store);
    ZopfliInitBlockState(options, instart, inend, false, &mut s);
    ZopfliAllocHash(32768, &mut hash);
    
    *npoints = 0;
    *splitpoints = None;
    
    ZopfliLZ77Greedy(&mut s, in_data, instart, inend, &mut store, &mut hash);
    ZopfliBlockSplitLZ77(options, &store, maxblocks, &mut lz77splitpoints, &mut nlz77points);
    
    if nlz77points > 0 {
        if let Some(lz77splitpoints) = &lz77splitpoints {
            if let Some(store_dists) = &store.dists {
                if let Some(store_litlens) = &store.litlens {
                    for i in 0..store.size {
                        let length = if store_dists[i] == 0 { 1 } else { store_litlens[i] };
                        
                        if lz77splitpoints[*npoints] == i {
                            if (*npoints & (*npoints - 1)) == 0 {
                                match splitpoints {
                                    Some(vec) => {
                                        let new_size = if *npoints == 0 { 1 } else { *npoints * 2 };
                                        vec.resize(new_size, 0);
                                    }
                                    None => {
                                        *splitpoints = Some(vec![0; 1]);
                                    }
                                }
                            }
                            
                            if let Some(sp) = splitpoints {
                                sp[*npoints] = pos;
                            }
                            *npoints += 1;
                            
                            if *npoints == nlz77points {
                                break;
                            }
                        }
                        pos += length as usize;
                    }
                }
            }
        }
    }
    
    assert_eq!(*npoints, nlz77points);
    
    ZopfliCleanBlockState(&mut s);
    ZopfliCleanLZ77Store(&mut store);
    ZopfliCleanHash(&mut hash);
}
