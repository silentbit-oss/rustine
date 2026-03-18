use crate::*;
use rand::Rng;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc::realloc;
use std::alloc;
use std::assert;
use std::boxed::Box;
use std::cmp::Ordering;
use std::cmp;
use std::eprintln;
use std::io::Write;
use std::io;
use std::mem;
use std::ptr;
use std::vec::Vec;
use std::vec;

pub fn ZopfliGetDistExtraBits(dist: i32) -> i32 {
    if dist < 5 {
        return 0;
    }
    (31 ^ (dist - 1).leading_zeros() as i32) - 1
}
pub fn ZopfliGetDistExtraBitsValue(dist: i32) -> i32 {
    if dist < 5 {
        0
    } else {
        let l = 31 ^ (dist - 1).leading_zeros() as i32;
        (dist - (1 + (1 << l))) & ((1 << (l - 1)) - 1)
    }
}
pub fn ZopfliGetDistSymbol(dist: i32) -> i32 {
    if dist < 5 {
        dist - 1
    } else {
        let l = 31 ^ (dist - 1).leading_zeros() as i32;
        let r = ((dist - 1) >> (l - 1)) & 1;
        (l * 2) + r
    }
}
pub fn ZopfliGetLengthExtraBits(l: usize) -> i32 {
    static TABLE: [i32; 259] = [
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
    ];
    TABLE[l]
}
pub fn ZopfliGetLengthExtraBitsValue(l: usize) -> i32 {
    static TABLE: [i32; 259] = [
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2,
        3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0,
        1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4,
        5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
        19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0,
    ];
    TABLE[l]
}
pub fn ZopfliGetLengthSymbol(l: usize) -> i32 {
    static TABLE: [i32; 259] = [
        0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268,
        269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273,
        273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275,
        275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277,
        277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278,
        278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279,
        279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280,
        280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
        281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
        282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
        282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283,
        283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
        283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284,
        284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
        284, 284, 284, 284, 284, 285,
    ];

    TABLE[l]
}
pub fn ZopfliGetLengthSymbolExtraBits(s: i32) -> i32 {
    const TABLE: [i32; 29] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0];
    TABLE[(s - 257) as usize]
}
pub fn ZopfliGetDistSymbolExtraBits(s: i32) -> i32 {
    static TABLE: [i32; 30] = [0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13];
    TABLE[s as usize]
}

pub fn AddBit(bit: i32, bp: &mut u8, out: &mut Option<Vec<u8>>, outsize: &mut usize) {
    if *bp == 0 {
        if (*outsize & (*outsize - 1)) == 0 {
            let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
            unsafe {
                match out {
                    Some(vec) => {
                        let layout = Layout::array::<u8>(new_size).unwrap();
                        let ptr = realloc(vec.as_mut_ptr() as *mut u8, layout, new_size);
                        if ptr.is_null() {
                            panic!("realloc failed");
                        }
                        *vec = Vec::from_raw_parts(ptr, *outsize, new_size);
                    }
                    None => {
                        let layout = Layout::array::<u8>(1).unwrap();
                        let ptr = alloc(layout);
                        if ptr.is_null() {
                            panic!("alloc failed");
                        }
                        *out = Some(Vec::from_raw_parts(ptr, 0, 1));
                    }
                }
            }
        }
        if let Some(vec) = out {
            vec.push(0);
            *outsize += 1;
        }
    }
    if let Some(vec) = out {
        if *outsize > 0 {
            let last = vec.len() - 1;
            vec[last] |= (bit as u8) << *bp;
        }
    }
    *bp = (*bp + 1) & 7;
}

pub fn AddBits(
    symbol: u32,
    length: u32,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    for i in 0..length {
        let bit = (symbol >> i) & 1;
        
        if *bp == 0 {
            if (*outsize & (*outsize - 1)) == 0 {
                let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
                let layout = Layout::array::<u8>(new_size).expect("Failed to create layout");
                let new_ptr = unsafe {
                    if *outsize == 0 {
                        alloc::alloc(layout)
                    } else {
                        let old_ptr = out.as_mut().unwrap().as_mut_ptr();
                        alloc::realloc(old_ptr as *mut u8, layout, new_size)
                    }
                };

                if new_ptr.is_null() {
                    panic!("Allocation failed");
                }

                let new_vec = unsafe { Vec::from_raw_parts(new_ptr, *outsize, new_size) };
                *out = Some(new_vec);
            }
            
            out.as_mut().unwrap().push(0);
            *outsize += 1;
        }

        let last = out.as_mut().unwrap().last_mut().unwrap();
        *last |= (bit as u8) << *bp;
        *bp = (*bp + 1) & 7;
    }
}

pub fn AddHuffmanBits(
    symbol: u32,
    length: u32,
    bp: &mut u8,
    out: &mut Option<Box<[u8]>>,
    outsize: &mut usize,
) {
    for i in 0..length {
        let bit = (symbol >> ((length - i) - 1)) & 1;
        if *bp == 0 {
            if (*outsize & (*outsize - 1)) == 0 {
                let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
                let layout = Layout::array::<u8>(new_size).unwrap();
                
                let new_ptr = unsafe {
                    if let Some(ref mut boxed_slice) = out {
                        realloc(boxed_slice.as_mut_ptr() as *mut u8, layout, new_size)
                    } else {
                        alloc(layout)
                    }
                };

                if new_ptr.is_null() {
                    panic!("Allocation failed");
                }

                *out = Some(unsafe { Box::from_raw(std::slice::from_raw_parts_mut(new_ptr, new_size)) });
            }
            if let Some(ref mut boxed_slice) = out {
                boxed_slice[*outsize] = 0;
            }
            *outsize += 1;
        }

        if let Some(ref mut boxed_slice) = out {
            boxed_slice[(*outsize) - 1] |= (bit as u8) << *bp;
        }
        *bp = (*bp + 1) & 7;
    }
}
pub fn PatchDistanceCodesForBuggyDecoders(d_lengths: &mut [u32; 30]) {
    let mut num_dist_codes = 0;
    
    // Check for at least 2 non-zero distance codes
    for &length in d_lengths.iter() {
        if length != 0 {
            num_dist_codes += 1;
            if num_dist_codes >= 2 {
                return;
            }
        }
    }

    match num_dist_codes {
        0 => {
            // If no distance codes, set both 0 and 1 to 1
            d_lengths[0] = 1;
            d_lengths[1] = 1;
        },
        1 => {
            // If only one distance code, set the other index to 1
            if d_lengths[0] != 0 {
                d_lengths[1] = 1;
            } else {
                d_lengths[0] = 1;
            }
        },
        _ => () // No action needed for >= 2 (already returned earlier)
    }
}
pub fn GetFixedTree(ll_lengths: &mut [u32], d_lengths: &mut [u32]) {
    // Initialize ll_lengths
    for i in 0..144 {
        ll_lengths[i] = 8;
    }
    
    for i in 144..256 {
        ll_lengths[i] = 9;
    }
    
    for i in 256..280 {
        ll_lengths[i] = 7;
    }
    
    for i in 280..288 {
        ll_lengths[i] = 8;
    }
    
    // Initialize d_lengths
    for i in 0..32 {
        d_lengths[i] = 5;
    }
}
pub fn AbsDiff(x: usize, y: usize) -> usize {
    if x > y {
        x - y
    } else {
        y - x
    }
}

pub fn EncodeTree(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    use_16: bool,
    use_17: bool,
    use_18: bool,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) -> usize {
    let mut lld_total;
    let mut rle: Vec<u32> = Vec::new();
    let mut rle_bits: Vec<u32> = Vec::new();
    let mut hlit = 29;
    let mut hdist = 29;
    let mut hclen;
    let mut hlit2;
    let mut clcounts = [0; 19];
    let mut clcl = [0; 19];
    let mut clsymbols = [0; 19];
    const ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];
    let size_only = out.is_none();
    let mut result_size = 0;

    while hlit > 0 && ll_lengths[(257 + hlit) - 1] == 0 {
        hlit -= 1;
    }

    while hdist > 0 && d_lengths[(1 + hdist) - 1] == 0 {
        hdist -= 1;
    }

    hlit2 = hlit + 257;
    lld_total = (hlit2 + hdist) + 1;

    let mut i = 0;
    while i < lld_total {
        let symbol = if i < hlit2 {
            ll_lengths[i]
        } else {
            d_lengths[i - hlit2]
        };
        let mut count = 1;

        if use_16 || (symbol == 0 && (use_17 || use_18)) {
            let mut j = i + 1;
            while j < lld_total && symbol == if j < hlit2 { ll_lengths[j] } else { d_lengths[j - hlit2] } {
                count += 1;
                j += 1;
            }
        }

        i += count - 1;

        if symbol == 0 && count >= 3 {
            if use_18 {
                let mut remaining = count;
                while remaining >= 11 {
                    let count2 = if remaining > 138 { 138 } else { remaining };
                    if !size_only {
                        rle.push(18);
                        rle_bits.push((count2 - 11) as u32);
                    }
                    clcounts[18] += 1;
                    remaining -= count2;
                }
            }

            if use_17 {
                let mut remaining = count;
                while remaining >= 3 {
                    let count2 = if remaining > 10 { 10 } else { remaining };
                    if !size_only {
                        rle.push(17);
                        rle_bits.push((count2 - 3) as u32);
                    }
                    clcounts[17] += 1;
                    remaining -= count2;
                }
            }
        }

        if use_16 && count >= 4 {
            count -= 1;
            clcounts[symbol as usize] += 1;
            if !size_only {
                rle.push(symbol);
                rle_bits.push(0);
            }

            let mut remaining = count;
            while remaining >= 3 {
                let count2 = if remaining > 6 { 6 } else { remaining };
                if !size_only {
                    rle.push(16);
                    rle_bits.push((count2 - 3) as u32);
                }
                clcounts[16] += 1;
                remaining -= count2;
            }
        }

        clcounts[symbol as usize] += count as usize;
        if !size_only {
            for _ in 0..count {
                rle.push(symbol);
                rle_bits.push(0);
            }
        }

        i += 1;
    }

    ZopfliCalculateBitLengths(&clcounts, 19, 7, &mut clcl);
    if !size_only {
        ZopfliLengthsToSymbols(&clcl, 19, 7, &mut clsymbols);
    }

    hclen = 15;
    while hclen > 0 && clcounts[ORDER[(hclen + 4) - 1]] == 0 {
        hclen -= 1;
    }

    if !size_only {
        AddBits(hlit as u32, 5, bp, out, outsize);
        AddBits(hdist as u32, 5, bp, out, outsize);
        AddBits(hclen as u32, 4, bp, out, outsize);
        for i in 0..(hclen + 4) {
            AddBits(clcl[ORDER[i]], 3, bp, out, outsize);
        }

        // Convert Vec to Boxed slice for AddHuffmanBits
        let mut boxed_out = out.as_mut().map(|v| v.clone().into_boxed_slice());
        for i in 0..rle.len() {
            let symbol = clsymbols[rle[i] as usize];
            AddHuffmanBits(symbol as u32, clcl[rle[i] as usize], bp, &mut boxed_out, outsize);
            match rle[i] {
                16 => AddBits(rle_bits[i], 2, bp, out, outsize),
                17 => AddBits(rle_bits[i], 3, bp, out, outsize),
                18 => AddBits(rle_bits[i], 7, bp, out, outsize),
                _ => (),
            }
        }
        // Convert back to Vec if needed
        if let Some(boxed) = boxed_out {
            *out = Some(boxed.into_vec());
        }
    }

    result_size += 14;
    result_size += (hclen + 4) * 3;
    for i in 0..19 {
        result_size += clcl[i] as usize * clcounts[i];
    }

    result_size += clcounts[16] * 2;
    result_size += clcounts[17] * 3;
    result_size += clcounts[18] * 7;

    result_size
}
pub fn AddDynamicTree(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut best = 0;
    let mut bestsize = 0;

    for i in 0..8 {
        let size = EncodeTree(
            ll_lengths,
            d_lengths,
            (i & 1) != 0,
            (i & 2) != 0,
            (i & 4) != 0,
            &mut 0,  // Temporary mutable reference for comparison
            &mut None,  // Temporary mutable reference for comparison
            &mut 0,  // Temporary mutable reference for comparison
        );

        if bestsize == 0 || size < bestsize {
            bestsize = size;
            best = i;
        }
    }

    EncodeTree(
        ll_lengths,
        d_lengths,
        (best & 1) != 0,
        (best & 2) != 0,
        (best & 4) != 0,
        bp,
        out,
        outsize,
    );
}
pub fn CalculateTreeSize(ll_lengths: &[u32], d_lengths: &[u32]) -> usize {
    let mut result = 0;
    
    for i in 0..8 {
        let mut bp = 0;
        let mut out = None;
        let mut outsize = 0;
        
        let size = EncodeTree(
            ll_lengths,
            d_lengths,
            (i & 1) != 0,
            (i & 2) != 0,
            (i & 4) != 0,
            &mut bp,
            &mut out,
            &mut outsize,
        );
        
        if result == 0 || size < result {
            result = size;
        }
    }
    
    result
}
pub fn OptimizeHuffmanForRle(length: i32, counts: &mut [usize]) {
    let mut length = length;
    
    // Find the last non-zero element
    while length >= 0 {
        if length == 0 {
            return;
        }
        if counts[(length - 1) as usize] != 0 {
            break;
        }
        length -= 1;
    }

    let length_usize = length as usize;
    let mut good_for_rle = vec![0; length_usize];

    let mut symbol = counts[0];
    let mut stride = 0;
    
    for i in 0..=length_usize {
        if i == length_usize || counts[i] != symbol {
            if (symbol == 0 && stride >= 5) || (symbol != 0 && stride >= 7) {
                for k in 0..stride {
                    let idx = (i - k) - 1;
                    good_for_rle[idx] = 1;
                }
            }
            stride = 1;
            if i != length_usize {
                symbol = counts[i];
            }
        } else {
            stride += 1;
        }
    }

    let mut stride = 0;
    let mut limit = counts[0];
    let mut sum = 0;
    
    for i in 0..=length_usize {
        if i == length_usize || good_for_rle[i] != 0 || AbsDiff(counts[i], limit) >= 4 {
            if stride >= 4 || (stride >= 3 && sum == 0) {
                let mut count = (sum + (stride / 2)) / stride;
                if count < 1 {
                    count = 1;
                }
                if sum == 0 {
                    count = 0;
                }
                for k in 0..stride {
                    let idx = (i - k) - 1;
                    counts[idx] = count;
                }
            }
            stride = 0;
            sum = 0;
            
            if i < length_usize - 3 {
                limit = (counts[i] + counts[i + 1] + counts[i + 2] + counts[i + 3] + 2) / 4;
            } else if i < length_usize {
                limit = counts[i];
            } else {
                limit = 0;
            }
        }
        stride += 1;
        if i != length_usize {
            sum += counts[i];
        }
    }
}
pub fn CalculateBlockSymbolSizeSmall(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    let mut result = 0usize;

    for i in lstart..lend {
        assert!(i < lz77.size, "Index out of bounds");
        assert!(
            lz77.litlens.as_ref().map_or(false, |v| v[i] < 259),
            "Literal length out of bounds"
        );

        if lz77.dists.as_ref().map_or(false, |v| v[i] == 0) {
            result += ll_lengths[lz77.litlens.as_ref().unwrap()[i] as usize] as usize;
        } else {
            let ll_symbol = ZopfliGetLengthSymbol(lz77.litlens.as_ref().unwrap()[i] as usize);
            let d_symbol = ZopfliGetDistSymbol(lz77.dists.as_ref().unwrap()[i] as i32);
            result += ll_lengths[ll_symbol as usize] as usize;
            result += d_lengths[d_symbol as usize] as usize;
            result += ZopfliGetLengthSymbolExtraBits(ll_symbol) as usize;
            result += ZopfliGetDistSymbolExtraBits(d_symbol) as usize;
        }
    }

    result += ll_lengths[256] as usize;
    result
}
pub fn CalculateBlockSymbolSizeGivenCounts(
    ll_counts: &[usize],
    d_counts: &[usize],
    ll_lengths: &[u32],
    d_lengths: &[u32],
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    let mut result = 0;

    if (lstart + (288 * 3)) > lend {
        return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
    } else {
        for i in 0..256 {
            result += ll_lengths[i] as usize * ll_counts[i];
        }

        for i in 257..286 {
            result += ll_lengths[i] as usize * ll_counts[i];
            result += ZopfliGetLengthSymbolExtraBits(i as i32) as usize * ll_counts[i];
        }

        for i in 0..30 {
            result += d_lengths[i] as usize * d_counts[i];
            result += ZopfliGetDistSymbolExtraBits(i as i32) as usize * d_counts[i];
        }

        result += ll_lengths[256] as usize;
        result
    }
}
pub fn TryOptimizeHuffmanForRle(
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    ll_counts: &[usize],
    d_counts: &[usize],
    ll_lengths: &mut [u32],
    d_lengths: &mut [u32],
) -> f64 {
    let mut ll_counts2: [usize; 288] = [0; 288];
    let mut d_counts2: [usize; 32] = [0; 32];
    let mut ll_lengths2: [u32; 288] = [0; 288];
    let mut d_lengths2: [u32; 32] = [0; 32];
    
    let treesize = CalculateTreeSize(ll_lengths, d_lengths);
    let datasize = CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend
    );
    
    ll_counts2.copy_from_slice(&ll_counts[..288]);
    d_counts2.copy_from_slice(&d_counts[..32]);
    
    OptimizeHuffmanForRle(288, &mut ll_counts2);
    OptimizeHuffmanForRle(32, &mut d_counts2);
    
    ZopfliCalculateBitLengths(&ll_counts2, 288, 15, &mut ll_lengths2);
    ZopfliCalculateBitLengths(&d_counts2, 32, 15, &mut d_lengths2);
    
    // Create a temporary array of size 30 for PatchDistanceCodesForBuggyDecoders
    let mut d_lengths2_temp: [u32; 30] = [0; 30];
    d_lengths2_temp.copy_from_slice(&d_lengths2[..30]);
    PatchDistanceCodesForBuggyDecoders(&mut d_lengths2_temp);
    // Copy the modified values back to the original array
    d_lengths2[..30].copy_from_slice(&d_lengths2_temp);
    
    let treesize2 = CalculateTreeSize(&ll_lengths2, &d_lengths2);
    let datasize2 = CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, &ll_lengths2, &d_lengths2, lz77, lstart, lend
    );
    
    if (treesize2 + datasize2) < (treesize + datasize) {
        ll_lengths[..288].copy_from_slice(&ll_lengths2);
        d_lengths[..32].copy_from_slice(&d_lengths2);
        return (treesize2 + datasize2) as f64;
    }
    
    (treesize + datasize) as f64
}
pub fn GetDynamicLengths(
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    ll_lengths: &mut [u32; 288],
    d_lengths: &mut [u32; 32],
) -> f64 {
    let mut ll_counts = [0usize; 288];
    let mut d_counts = [0usize; 32];
    
    ZopfliLZ77GetHistogram(lz77, lstart, lend, &mut ll_counts, &mut d_counts);
    
    ll_counts[256] = 1;
    
    ZopfliCalculateBitLengths(&ll_counts, 288, 15, ll_lengths);
    ZopfliCalculateBitLengths(&d_counts, 32, 15, d_lengths);
    
    // Create a temporary array for the distance codes fix
    let mut fixed_d_lengths = [0u32; 30];
    fixed_d_lengths.copy_from_slice(&d_lengths[..30]);
    PatchDistanceCodesForBuggyDecoders(&mut fixed_d_lengths);
    d_lengths[..30].copy_from_slice(&fixed_d_lengths);
    
    TryOptimizeHuffmanForRle(
        lz77,
        lstart,
        lend,
        &ll_counts,
        &d_counts,
        ll_lengths,
        d_lengths,
    )
}
pub fn CalculateBlockSymbolSize(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    if (lstart + (288 * 3)) > lend {
        CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend)
    } else {
        let mut ll_counts = [0; 288];
        let mut d_counts = [0; 32];
        ZopfliLZ77GetHistogram(lz77, lstart, lend, &mut ll_counts, &mut d_counts);
        CalculateBlockSymbolSizeGivenCounts(
            &ll_counts,
            &d_counts,
            ll_lengths,
            d_lengths,
            lz77,
            lstart,
            lend,
        )
    }
}

pub fn ZopfliCalculateBlockSize(
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    btype: i32,
) -> f64 {
    let mut ll_lengths = [0u32; 288];
    let mut d_lengths = [0u32; 32];
    let mut result = 3.0;

    match btype {
        0 => {
            let length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
            let rem = length % 65535;
            let blocks = (length / 65535) + if rem != 0 { 1 } else { 0 };
            return ((blocks * 5) * 8 + (length * 8)) as f64;
        }
        1 => {
            GetFixedTree(&mut ll_lengths, &mut d_lengths);
            result += CalculateBlockSymbolSize(
                &ll_lengths,
                &d_lengths,
                lz77,
                lstart,
                lend,
            ) as f64;
        }
        _ => {
            result += GetDynamicLengths(
                lz77,
                lstart,
                lend,
                &mut ll_lengths,
                &mut d_lengths,
            );
        }
    }

    result
}
pub fn ZopfliCalculateBlockSizeAutoType(lz77: &ZopfliLz77Store, lstart: usize, lend: usize) -> f64 {
    let uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
    let fixedcost = if lz77.size > 1000 {
        uncompressedcost
    } else {
        ZopfliCalculateBlockSize(lz77, lstart, lend, 1)
    };
    let dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);

    if uncompressedcost < fixedcost && uncompressedcost < dyncost {
        uncompressedcost
    } else if fixedcost < dyncost {
        fixedcost
    } else {
        dyncost
    }
}
pub fn AddNonCompressedBlock(
    options: &ZopfliOptions,
    final_block: bool,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    bp: &mut u8,
    out: &mut Vec<u8>,
) {
    let mut pos = instart;
    let _ = options; // Explicitly mark as unused
    let mut outsize = out.len();

    loop {
        let blocksize = if pos + 65535 > inend {
            inend - pos
        } else {
            65535
        } as u16;

        let currentfinal = (pos + blocksize as usize) >= inend;
        let nlen = !blocksize;

        let mut out_option = Some(out.to_vec());
        AddBit(
            if final_block && currentfinal { 1 } else { 0 },
            bp,
            &mut out_option,
            &mut outsize,
        );
        AddBit(0, bp, &mut out_option, &mut outsize);
        AddBit(0, bp, &mut out_option, &mut outsize);
        *bp = 0;

        // Write blocksize (little-endian)
        out.push((blocksize % 256) as u8);
        out.push((blocksize / 256) as u8);

        // Write nlen (little-endian)
        out.push((nlen % 256) as u8);
        out.push((nlen / 256) as u8);

        // Copy block data
        let block_end = pos + blocksize as usize;
        out.extend_from_slice(&in_data[pos..block_end]);

        if currentfinal {
            break;
        }
        pos += blocksize as usize;
    }
}
pub fn AddLZ77Data(
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    expected_data_size: usize,
    ll_symbols: &[u32],
    ll_lengths: &[u32],
    d_symbols: &[u32],
    d_lengths: &[u32],
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut testlength = 0;

    for i in lstart..lend {
        let dist = lz77.dists.as_ref().unwrap()[i];
        let litlen = lz77.litlens.as_ref().unwrap()[i];

        if dist == 0 {
            assert!(litlen < 256);
            assert!(ll_lengths[litlen as usize] > 0);
            AddHuffmanBits(
                ll_symbols[litlen as usize],
                ll_lengths[litlen as usize],
                bp,
                &mut out.as_mut().map(|v| v.clone().into_boxed_slice()),
                outsize,
            );
            testlength += 1;
        } else {
            let lls = ZopfliGetLengthSymbol(litlen as usize) as usize;
            let ds = ZopfliGetDistSymbol(dist as i32) as usize;
            assert!((litlen >= 3) && (litlen <= 288));
            assert!(ll_lengths[lls] > 0);
            assert!(d_lengths[ds] > 0);
            
            AddHuffmanBits(ll_symbols[lls], ll_lengths[lls], bp, &mut out.as_mut().map(|v| v.clone().into_boxed_slice()), outsize);
            AddBits(
                ZopfliGetLengthExtraBitsValue(litlen as usize).try_into().unwrap(),
                ZopfliGetLengthExtraBits(litlen as usize).try_into().unwrap(),
                bp,
                out,
                outsize,
            );
            AddHuffmanBits(d_symbols[ds], d_lengths[ds], bp, &mut out.as_mut().map(|v| v.clone().into_boxed_slice()), outsize);
            AddBits(
                ZopfliGetDistExtraBitsValue(dist as i32).try_into().unwrap(),
                ZopfliGetDistExtraBits(dist as i32).try_into().unwrap(),
                bp,
                out,
                outsize,
            );
            testlength += litlen as usize;
        }
    }

    assert!((expected_data_size == 0) || (testlength == expected_data_size));
}
pub fn AddLZ77Block(
    options: &ZopfliOptions,
    btype: i32,
    final_block: bool,
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    expected_data_size: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut ll_lengths = [0u32; 288];
    let mut d_lengths = [0u32; 32];
    let mut ll_symbols = [0u32; 288];
    let mut d_symbols = [0u32; 32];
    let mut detect_block_size = *outsize;
    let mut uncompressed_size = 0;

    if btype == 0 {
        let length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
        let pos = if lstart == lend { 0 } else { lz77.pos.as_ref().unwrap()[lstart] };
        let end = pos + length;
        let mut vec_out = out.as_mut().unwrap();
        AddNonCompressedBlock(
            options,
            final_block,
            lz77.data.as_ref().unwrap(),
            pos,
            end,
            bp,
            &mut vec_out,
        );
        return;
    }

    AddBit(final_block as i32, bp, out, outsize);
    AddBit(btype & 1, bp, out, outsize);
    AddBit((btype & 2) >> 1, bp, out, outsize);

    if btype == 1 {
        GetFixedTree(&mut ll_lengths, &mut d_lengths);
    } else {
        assert!(btype == 2);
        GetDynamicLengths(lz77, lstart, lend, &mut ll_lengths, &mut d_lengths);
        let detect_tree_size = *outsize;
        AddDynamicTree(&ll_lengths, &d_lengths, bp, out, outsize);
        if options.verbose > 0 {
            eprintln!("treesize: {}", (*outsize - detect_tree_size) as i32);
        }
    }

    ZopfliLengthsToSymbols(&ll_lengths, 288, 15, &mut ll_symbols);
    ZopfliLengthsToSymbols(&d_lengths, 32, 15, &mut d_symbols);
    detect_block_size = *outsize;

    AddLZ77Data(
        lz77,
        lstart,
        lend,
        expected_data_size,
        &ll_symbols,
        &ll_lengths,
        &d_symbols,
        &d_lengths,
        bp,
        out,
        outsize,
    );

    let mut boxed_out: Option<Box<[u8]>> = out.as_mut().map(|v| v.clone().into_boxed_slice());
    AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, &mut boxed_out, outsize);
    if let Some(b) = boxed_out {
        *out = Some(b.into_vec());
    }

    if let (Some(litlens), Some(dists)) = (&lz77.litlens, &lz77.dists) {
        for i in lstart..lend {
            uncompressed_size += if dists[i] == 0 { 1 } else { litlens[i] as usize };
        }
    }

    let compressed_size = *outsize - detect_block_size;
    if options.verbose > 0 {
        eprintln!(
            "compressed block size: {} ({}k) (unc: {})",
            compressed_size as i32,
            (compressed_size / 1024) as i32,
            uncompressed_size as i32
        );
    }
}
pub fn AddLZ77BlockAutoType(
    options: &ZopfliOptions,
    final_block: bool,
    lz77: &ZopfliLz77Store,
    lstart: usize,
    lend: usize,
    expected_data_size: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
    let fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
    let dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
    let expensivefixed = (lz77.size < 1000) || (fixedcost <= (dyncost * 1.1));

    let mut fixedstore = ZopfliLz77Store {
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

    if lstart == lend {
        AddBits(final_block as u32, 1, bp, out, outsize);
        AddBits(1, 2, bp, out, outsize);
        AddBits(0, 7, bp, out, outsize);
        return;
    }

    ZopfliInitLZ77Store(lz77.data.as_deref(), &mut fixedstore);

    if expensivefixed {
        let instart = lz77.pos.as_ref().unwrap()[lstart];
        let inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);
        let mut s = ZopfliBlockState {
            options: None,
            lmc: None,
            blockstart: 0,
            blockend: 0,
        };
        ZopfliInitBlockState(Some(Box::new(options.clone())), instart, inend, true, &mut s);
        ZopfliLZ77OptimalFixed(&mut s, lz77.data.as_ref().unwrap(), instart, inend, &mut fixedstore);
        let fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
        ZopfliCleanBlockState(&mut s);
    }

    if (uncompressedcost < fixedcost) && (uncompressedcost < dyncost) {
        AddLZ77Block(options, 0, final_block, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    } else if fixedcost < dyncost {
        if expensivefixed {
            AddLZ77Block(options, 1, final_block, &fixedstore, 0, fixedstore.size, expected_data_size, bp, out, outsize);
        } else {
            AddLZ77Block(options, 1, final_block, lz77, lstart, lend, expected_data_size, bp, out, outsize);
        }
    } else {
        AddLZ77Block(options, 2, final_block, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    }

    ZopfliCleanLZ77Store(&mut fixedstore);
}
pub fn ZopfliDeflatePart(
    options: &ZopfliOptions,
    btype: i32,
    final_block: bool,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut splitpoints_uncompressed: Option<Vec<usize>> = None;
    let mut npoints: usize = 0;
    let mut splitpoints: Option<Vec<usize>> = None;
    let mut totalcost: f64 = 0.0;
    let mut lz77 = ZopfliLz77Store {
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

    if btype == 0 {
        // Convert Option<Vec<u8>> to Vec<u8> for AddNonCompressedBlock
        let mut vec_out = out.take().unwrap_or_default();
        AddNonCompressedBlock(options, final_block, in_data, instart, inend, bp, &mut vec_out);
        *out = Some(vec_out);
        return;
    } else if btype == 1 {
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
        let mut s = ZopfliBlockState {
            options: None,
            lmc: None,
            blockstart: 0,
            blockend: 0,
        };
        ZopfliInitLZ77Store(Some(in_data), &mut store);
        ZopfliInitBlockState(Some(Box::new(options.clone())), instart, inend, true, &mut s);
        ZopfliLZ77OptimalFixed(&mut s, in_data, instart, inend, &mut store);
        AddLZ77Block(
            options,
            btype,
            final_block,
            &store,
            0,
            store.size,
            0,
            bp,
            out,
            outsize,
        );
        ZopfliCleanBlockState(&mut s);
        ZopfliCleanLZ77Store(&mut store);
        return;
    }

    if options.blocksplitting != 0 {
        ZopfliBlockSplit(
            options,
            in_data,
            instart,
            inend,
            options.blocksplittingmax as usize,
            &mut splitpoints_uncompressed,
            &mut npoints,
        );
        if npoints > 0 {
            splitpoints = Some(vec![0; npoints]);
        }
    }

    ZopfliInitLZ77Store(Some(in_data), &mut lz77);

    for i in 0..=npoints {
        let start = if i == 0 {
            instart
        } else {
            splitpoints_uncompressed.as_ref().unwrap()[i - 1]
        };
        let end = if i == npoints {
            inend
        } else {
            splitpoints_uncompressed.as_ref().unwrap()[i]
        };

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
        let mut s = ZopfliBlockState {
            options: None,
            lmc: None,
            blockstart: 0,
            blockend: 0,
        };

        ZopfliInitLZ77Store(Some(in_data), &mut store);
        ZopfliInitBlockState(Some(Box::new(options.clone())), start, end, true, &mut s);
        ZopfliLZ77Optimal(
            &mut s,
            in_data,
            start,
            end,
            options.numiterations,
            &mut store,
        );
        totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);
        ZopfliAppendLZ77Store(&store, &mut lz77);

        if i < npoints {
            if let Some(ref mut sp) = splitpoints {
                sp[i] = lz77.size;
            }
        }

        ZopfliCleanBlockState(&mut s);
        ZopfliCleanLZ77Store(&mut store);
    }

    if options.blocksplitting != 0 && npoints > 1 {
        let mut splitpoints2: Option<Vec<usize>> = None;
        let mut npoints2: usize = 0;
        let mut totalcost2: f64 = 0.0;

        ZopfliBlockSplitLZ77(
            options,
            &lz77,
            options.blocksplittingmax as usize,
            &mut splitpoints2,
            &mut npoints2,
        );

        for i in 0..=npoints2 {
            let start = if i == 0 {
                0
            } else {
                splitpoints2.as_ref().unwrap()[i - 1]
            };
            let end = if i == npoints2 {
                lz77.size
            } else {
                splitpoints2.as_ref().unwrap()[i]
            };
            totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
        }

        if totalcost2 < totalcost {
            splitpoints = splitpoints2;
            npoints = npoints2;
        }
    }

    for i in 0..=npoints {
        let start = if i == 0 {
            0
        } else {
            splitpoints.as_ref().unwrap()[i - 1]
        };
        let end = if i == npoints {
            lz77.size
        } else {
            splitpoints.as_ref().unwrap()[i]
        };
        AddLZ77BlockAutoType(
            options,
            i == npoints && final_block,
            &lz77,
            start,
            end,
            0,
            bp,
            out,
            outsize,
        );
    }

    ZopfliCleanLZ77Store(&mut lz77);
}

pub fn ZopfliDeflate(
    options: &ZopfliOptions,
    btype: i32,
    final_block: bool,
    in_data: &[u8],
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let offset = *outsize;
    let mut i = 0;
    while i < in_data.len() {
        let masterfinal = (i + 1000000) >= in_data.len();
        let final2 = final_block && masterfinal;
        let size = if masterfinal {
            in_data.len() - i
        } else {
            1000000
        };
        
        ZopfliDeflatePart(
            options,
            btype,
            final2,
            in_data,
            i,
            i + size,
            bp,
            out,
            outsize,
        );
        i += size;
    }

    if options.verbose != 0 {
        let original_size = in_data.len();
        let compressed_size = *outsize - offset;
        let compression_ratio = 100.0 * (original_size as f64 - compressed_size as f64) / original_size as f64;
        
        writeln!(
            io::stderr(),
            "Original Size: {}, Deflate: {}, Compression: {:.2}% Removed",
            original_size,
            compressed_size,
            compression_ratio
        ).unwrap();
    }
}
