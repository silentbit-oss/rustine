use crate::*;
use std::alloc::Layout;
use std::alloc;
use std::any::Any;
use std::assert;
use std::fmt::Write;
use std::ptr;
use std::vec::Vec;
use std::vec;

pub fn ZopfliBlockSplitSimple(
    in_data: &[u8],
    instart: usize,
    inend: usize,
    blocksize: usize,
    splitpoints: &mut Vec<usize>,
    npoints: &mut usize,
) {
    let mut i = instart;
    while i < inend {
        // Check if npoints is a power of 2 (including 0)
        if (*npoints & (*npoints - 1)) == 0 {
            // Double the capacity when npoints is a power of 2
            if *npoints == splitpoints.capacity() {
                splitpoints.reserve(if *npoints == 0 { 1 } else { *npoints });
            }
        }

        splitpoints.push(i);
        *npoints += 1;

        i += blocksize;
    }
}

pub fn AddSorted(value: usize, out: &mut Option<Vec<usize>>, outsize: &mut usize) {
    // Check if outsize is a power of 2 (including 0)
    if (*outsize & (*outsize - 1)) == 0 {
        // Equivalent to the C malloc/realloc logic but using Vec
        match out {
            Some(vec) => {
                // Double the capacity when needed (similar to realloc)
                if vec.capacity() == *outsize {
                    vec.reserve(if *outsize == 0 { 1 } else { *outsize });
                }
            }
            None => {
                // Equivalent to malloc for initial allocation
                *out = Some(Vec::with_capacity(1));
            }
        }
    }

    // Push the value to the end (equivalent to line 9-10 in C)
    if let Some(vec) = out {
        vec.push(value);
        *outsize += 1;
    }

    // Find insertion point and shift elements (equivalent to lines 13-26 in C)
    if let Some(vec) = out {
        for i in 0..(*outsize - 1) {
            if vec[i] > value {
                // Shift elements to make space
                vec.insert(i, value);
                // Remove the duplicate at the end (since we pushed earlier)
                vec.pop();
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
        let end = if i == npoints { lz77size - 1 } else { splitpoints[i] };

        if done[start] == 0 && (end - start) > longest {
            *lstart = start;
            *lend = end;
            found = true;
            longest = end - start;
        }
    }

    found
}

pub fn PrintBlockSplitPoints(lz77: &ZopfliLz77Store, lz77splitpoints: &[usize], nlz77points: usize) {
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
                if (npoints & (npoints - 1)) == 0 {
                    if npoints == 0 {
                        splitpoints.reserve(1);
                    } else {
                        splitpoints.reserve(npoints * 2);
                    }
                }
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
    
    let mut output = String::new();
    write!(&mut output, "block split points: ").unwrap();
    for point in &splitpoints {
        write!(&mut output, "{} ", point).unwrap();
    }

    write!(&mut output, "(hex:").unwrap();
    for point in &splitpoints {
        write!(&mut output, " {:x}", point).unwrap();
    }
    write!(&mut output, ")\n").unwrap();

    eprint!("{}", output);
}
pub fn FindMinimum(
    f: FindMinimumFun,
    context: Option<Box<dyn Any + 'static>>,
    mut start: usize,
    mut end: usize,
    smallest: &mut f64,
) -> usize {
    // Convert the context into a static reference
    let static_context: Option<&'static dyn Any> = context.as_ref().map(|c| unsafe {
        let ptr = &**c as *const dyn Any;
        &*ptr
    });

    if (end - start) < 1024 {
        let mut best = 1e30;
        let mut result = start;
        
        for i in start..end {
            // Use the static context reference
            let ctx = static_context.map(|c| Box::new(c) as Box<dyn Any>);
            let v = f(i, ctx);
            if v < best {
                best = v;
                result = i;
            }
        }

        *smallest = best;
        result
    } else {
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
                // Use the static context reference
                let ctx = static_context.map(|c| Box::new(c) as Box<dyn Any>);
                vp[i] = f(p[i], ctx);
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
        pos
    }
}
pub fn EstimateCost(lz77: &ZopfliLz77Store, lstart: usize, lend: usize) -> f64 {
    ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend)
}

pub fn SplitCost(i: usize, context: &SplitCostContext) -> f64 {
    let c = context;
    EstimateCost(c.lz77.as_ref().unwrap(), c.start, i) + EstimateCost(c.lz77.as_ref().unwrap(), i, c.end)
}
pub fn ZopfliBlockSplitLZ77(
    options: &ZopfliOptions,
    lz77: &ZopfliLz77Store,
    maxblocks: usize,
    splitpoints: &mut Option<Vec<usize>>,
    npoints: &mut usize,
) {
    if lz77.size < 10 {
        return;
    }

    let mut done = vec![0u8; lz77.size];
    let mut numblocks = 1;
    let mut lstart = 0;
    let mut lend = lz77.size;

    // Wrapper function to match FindMinimum's expected signature
    fn split_cost_wrapper(i: usize, context: Option<Box<dyn std::any::Any>>) -> f64 {
        if let Some(boxed_context) = context {
            if let Ok(context_ref) = boxed_context.downcast::<SplitCostContext>() {
                return SplitCost(i, &context_ref);
            }
        }
        f64::MAX // Return a large value if context is invalid
    }

    loop {
        if maxblocks > 0 && numblocks >= maxblocks {
            break;
        }

        assert!(lstart < lend);
        
        let mut splitcost = 0.0;
        let c = SplitCostContext {
            lz77: Some(lz77.clone()),
            start: lstart,
            end: lend,
        };
        
        let llpos = FindMinimum(
            split_cost_wrapper,
            Some(Box::new(c)),
            lstart + 1,
            lend,
            &mut splitcost,
        );
        
        assert!(llpos > lstart);
        assert!(llpos < lend);
        
        let origcost = EstimateCost(lz77, lstart, lend);
        
        if splitcost > origcost || llpos == lstart + 1 || llpos == lend {
            done[lstart] = 1;
        } else {
            AddSorted(llpos, splitpoints, npoints);
            numblocks += 1;
        }

        let splitpoints_ref = splitpoints.as_ref().map(|v| v.as_slice()).unwrap_or(&[]);
        if !FindLargestSplittableBlock(
            lz77.size,
            &done,
            splitpoints_ref,
            *npoints,
            &mut lstart,
            &mut lend,
        ) {
            break;
        }

        if lend - lstart < 10 {
            break;
        }
    }

    if options.verbose != 0 {
        let splitpoints_ref = splitpoints.as_ref().map(|v| v.as_slice()).unwrap_or(&[]);
        PrintBlockSplitPoints(lz77, splitpoints_ref, *npoints);
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
    let mut store = ZopfliLz77Store {
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
    ZopfliInitBlockState(Some(Box::new(options.clone())), instart, inend, false, &mut s);
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
                                        *splitpoints = Some(vec![0]);
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
    
    assert!(*npoints == nlz77points);
    
    ZopfliCleanBlockState(&mut s);
    ZopfliCleanLZ77Store(&mut store);
    ZopfliCleanHash(&mut hash);
}
