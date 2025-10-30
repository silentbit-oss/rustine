use crate::*;
use std::mem;
use std::io;
use std::cmp::min;
use std::io::Write;

pub fn ZopfliGetDistExtraBits(dist: i32) -> i32 {
    if dist < 5 {
        0
    } else {
        // Equivalent to (31 ^ __builtin_clz(dist - 1)) - 1
        // Using the stable leading_zeros() method instead of ctlz intrinsic
        let leading_zeros = (dist as u32 - 1).leading_zeros() as i32;
        (31 ^ leading_zeros) - 1
    }
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
    const TABLE: [i32; 259] = [
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0
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
pub fn ZopfliGetDistSymbolExtraBits(s: usize) -> i32 {
    const TABLE: [i32; 30] = [0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13];
    TABLE[s]
}
pub fn AddBit(bit: i32, bp: &mut u8, out: &mut Option<Vec<u8>>, outsize: &mut usize) {
    if *bp == 0 {
        if (*outsize & (*outsize - 1)) == 0 {
            // Equivalent to the malloc/realloc logic
            let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
            match out {
                Some(vec) => vec.resize(new_size, 0),
                None => *out = Some(vec![0; new_size]),
            }
        }
        *outsize += 1;
    }

    if let Some(vec) = out {
        if *outsize > 0 {
            let last_pos = *outsize - 1;
            if last_pos < vec.len() {
                vec[last_pos] |= (bit as u8) << *bp;
            }
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
            // Check if outsize is a power of two (or zero)
            if (*outsize & (*outsize - 1)) == 0 {
                // Resize the vector if needed (equivalent to malloc/realloc)
                if *outsize == 0 {
                    *out = Some(vec![0]);
                } else {
                    if let Some(vec) = out {
                        let new_size = *outsize * 2;
                        vec.resize(new_size, 0);
                    }
                }
            }
            *outsize += 1;
        }

        if let Some(vec) = out {
            if *outsize > 0 {
                let last_pos = *outsize - 1;
                vec[last_pos] |= (bit as u8) << *bp;
            }
        }

        *bp = (*bp + 1) & 7;
    }
}

pub fn AddHuffmanBits(
    symbol: u32,
    length: u32,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    for i in 0..length {
        let bit = (symbol >> ((length - i) - 1)) & 1;
        if *bp == 0 {
            if (*outsize & (*outsize - 1)) == 0 {
                match out {
                    Some(vec) => {
                        let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
                        vec.resize(new_size, 0);
                    }
                    None => {
                        *out = Some(vec![0]);
                    }
                }
            }
            *outsize += 1;
        }

        if let Some(vec) = out {
            if *outsize > 0 {
                let last = vec.len() - 1;
                vec[last] |= (bit as u8) << *bp;
            }
        }
        
        *bp = (*bp + 1) & 7;
    }
}
pub fn PatchDistanceCodesForBuggyDecoders(d_lengths: &mut [u32; 30]) {
    let mut num_dist_codes = 0;
    
    // Count non-zero distance codes (lines 3-15)
    for i in 0..30 {
        if d_lengths[i] != 0 {
            num_dist_codes += 1;
        }
        if num_dist_codes >= 2 {
            return;
        }
    }

    // Handle cases based on num_dist_codes (lines 17-25)
    match num_dist_codes {
        0 => {
            d_lengths[0] = 1;
            d_lengths[1] = 1;
        },
        1 => {
            let index = if d_lengths[0] != 0 { 1 } else { 0 };
            d_lengths[index] = 1;
        },
        _ => (),  // num_dist_codes >= 2 already returned earlier
    }
}
pub fn GetFixedTree(ll_lengths: &mut [u32], d_lengths: &mut [u32]) {
    // First block: indices 0..144
    for i in 0..144 {
        ll_lengths[i] = 8;
    }

    // Second block: indices 144..256
    for i in 144..256 {
        ll_lengths[i] = 9;
    }

    // Third block: indices 256..280
    for i in 256..280 {
        ll_lengths[i] = 7;
    }

    // Fourth block: indices 280..288
    for i in 280..288 {
        ll_lengths[i] = 8;
    }

    // Distance lengths: indices 0..32
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

pub fn helper_helper_helper_EncodeTree_1_1_1(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    count_ref: &mut u32,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let mut count = *count_ref;
    let count2 = if count > 6 { 6 } else { count };

    if !size_only {
        {
            if (rle_size & (rle_size - 1)) == 0 {
                if rle_size == 0 {
                    rle.push(0); // Initialize with default value
                } else {
                    let new_capacity = rle_size * 2;
                    rle.resize(new_capacity, 0);
                }
            }
            rle[rle_size] = 16;
            rle_size += 1;
        }

        {
            if (rle_bits_size & (rle_bits_size - 1)) == 0 {
                if rle_bits_size == 0 {
                    rle_bits.push(0); // Initialize with default value
                } else {
                    let new_capacity = rle_bits_size * 2;
                    rle_bits.resize(new_capacity, 0);
                }
            }
            rle_bits[rle_bits_size] = count2 - 3;
            rle_bits_size += 1;
        }
    }

    clcounts[16] += 1;
    count -= count2;

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *count_ref = count;
}
pub fn helper_helper_helper_EncodeTree_1_2_1(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    count_ref: &mut u32,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let mut count = *count_ref;

    while count >= 11 {
        let count2 = if count > 138 { 138 } else { count };
        if !size_only {
            // Handle rle vector expansion and push
            if rle_size.is_power_of_two() {
                let new_capacity = if rle_size == 0 { 1 } else { rle_size * 2 };
                rle.resize(new_capacity, 0);
            }
            rle[rle_size] = 18;
            rle_size += 1;

            // Handle rle_bits vector expansion and push
            if rle_bits_size.is_power_of_two() {
                let new_capacity = if rle_bits_size == 0 { 1 } else { rle_bits_size * 2 };
                rle_bits.resize(new_capacity, 0);
            }
            rle_bits[rle_bits_size] = count2 - 11;
            rle_bits_size += 1;
        }
        clcounts[18] += 1;
        count -= count2;
    }

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *count_ref = count;
}
pub fn helper_helper_helper_EncodeTree_1_2_2(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    count_ref: &mut u32,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let mut count = *count_ref;

    while count >= 3 {
        let count2 = if count > 10 { 10 } else { count };
        if !size_only {
            // Handle rle vector expansion and push
            if (rle_size & (rle_size - 1)) == 0 {
                let new_capacity = if rle_size == 0 { 1 } else { rle_size * 2 };
                rle.resize(new_capacity, 0);
            }
            rle[rle_size] = 17;
            rle_size += 1;

            // Handle rle_bits vector expansion and push
            if (rle_bits_size & (rle_bits_size - 1)) == 0 {
                let new_capacity = if rle_bits_size == 0 { 1 } else { rle_bits_size * 2 };
                rle_bits.resize(new_capacity, 0);
            }
            rle_bits[rle_bits_size] = count2 - 3;
            rle_bits_size += 1;
        }
        clcounts[17] += 1;
        count -= count2;
    }

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *count_ref = count;
}
pub fn helper_helper_EncodeTree_1_2(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    count_ref: &mut u32,
    use_17: bool,
    use_18: bool,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let mut count = *count_ref;

    if use_18 {
        helper_helper_helper_EncodeTree_1_2_1(
            &mut rle_size,
            &mut rle_bits_size,
            &mut count,
            rle,
            rle_bits,
            clcounts,
            size_only,
        );
    }
    if use_17 {
        helper_helper_helper_EncodeTree_1_2_2(
            &mut rle_size,
            &mut rle_bits_size,
            &mut count,
            rle,
            rle_bits,
            clcounts,
            size_only,
        );
    }

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *count_ref = count;
}
pub fn helper_helper_EncodeTree_1_1(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    symbol_ref: &mut u8,
    count_ref: &mut u32,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let symbol = *symbol_ref;
    let mut count = *count_ref;
    
    count -= 1;
    clcounts[symbol as usize] += 1;

    if !size_only {
        {
            if (rle_size & (rle_size - 1)) == 0 {
                if rle_size == 0 {
                    rle.push(0); // Initialize with default value
                } else {
                    let new_capacity = rle_size * 2;
                    rle.resize(new_capacity, 0);
                }
            }
            rle[rle_size] = symbol as u32;
            rle_size += 1;
        }

        {
            if (rle_bits_size & (rle_bits_size - 1)) == 0 {
                if rle_bits_size == 0 {
                    rle_bits.push(0); // Initialize with default value
                } else {
                    let new_capacity = rle_bits_size * 2;
                    rle_bits.resize(new_capacity, 0);
                }
            }
            rle_bits[rle_bits_size] = 0;
            rle_bits_size += 1;
        }
    }

    while count >= 3 {
        helper_helper_helper_EncodeTree_1_1_1(
            &mut rle_size,
            &mut rle_bits_size,
            &mut count,
            rle,
            rle_bits,
            clcounts,
            size_only,
        );
    }

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *symbol_ref = symbol;
    *count_ref = count;
}
pub fn helper_EncodeTree_1(
    rle_size_ref: &mut usize,
    rle_bits_size_ref: &mut usize,
    i_ref: &mut usize,
    j_ref: &mut usize,
    ll_lengths: &[u32],
    d_lengths: &[u32],
    use_16: bool,
    use_17: bool,
    use_18: bool,
    lld_total: u32,
    rle: &mut Vec<u32>,
    rle_bits: &mut Vec<u32>,
    hlit2: usize,
    clcounts: &mut [usize; 19],
    size_only: bool,
) {
    let mut rle_size = *rle_size_ref;
    let mut rle_bits_size = *rle_bits_size_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;

    let symbol = if i < hlit2 {
        ll_lengths[i] as u8
    } else {
        d_lengths[i - hlit2] as u8
    };
    let mut count = 1;

    if use_16 || ((symbol == 0) && (use_17 || use_18)) {
        j = i + 1;
        while j < lld_total as usize {
            let next_symbol = if j < hlit2 {
                ll_lengths[j] as u8
            } else {
                d_lengths[j - hlit2] as u8
            };
            if next_symbol != symbol {
                break;
            }
            count += 1;
            j += 1;
        }
    }

    i += count as usize - 1;

    if (symbol == 0) && (count >= 3) {
        helper_helper_EncodeTree_1_2(
            &mut rle_size,
            &mut rle_bits_size,
            &mut count,
            use_17,
            use_18,
            rle,
            rle_bits,
            clcounts,
            size_only,
        );
    }

    if use_16 && (count >= 4) {
        let mut symbol_mut = symbol;
        helper_helper_EncodeTree_1_1(
            &mut rle_size,
            &mut rle_bits_size,
            &mut symbol_mut,
            &mut count,
            rle,
            rle_bits,
            clcounts,
            size_only,
        );
    }

    clcounts[symbol as usize] += count as usize;

    while count > 0 {
        if !size_only {
            {
                if (rle_size & (rle_size - 1)) == 0 {
                    if rle_size == 0 {
                        rle.push(0);
                    } else {
                        let new_capacity = rle_size * 2;
                        rle.resize(new_capacity, 0);
                    }
                }
                rle[rle_size] = symbol as u32;
                rle_size += 1;
            }

            {
                if (rle_bits_size & (rle_bits_size - 1)) == 0 {
                    if rle_bits_size == 0 {
                        rle_bits.push(0);
                    } else {
                        let new_capacity = rle_bits_size * 2;
                        rle_bits.resize(new_capacity, 0);
                    }
                }
                rle_bits[rle_bits_size] = 0;
                rle_bits_size += 1;
            }
        }
        count -= 1;
    }

    *rle_size_ref = rle_size;
    *rle_bits_size_ref = rle_bits_size;
    *i_ref = i;
    *j_ref = j;
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
    let mut rle = Vec::new();
    let mut rle_bits = Vec::new();
    let mut rle_size = 0;
    let mut rle_bits_size = 0;
    let mut hlit = 29;
    let mut hdist = 29;
    let mut hclen;
    let mut hlit2;
    let mut j = 0;
    let mut clcounts = [0; 19];
    let mut clcl = [0; 19];
    let mut clsymbols = [0; 19];
    const ORDER: [usize; 19] = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15];
    let size_only = out.is_none();
    let mut result_size = 0;

    while hlit > 0 && ll_lengths[(257 + hlit) - 1] == 0 {
        hlit -= 1;
    }
    hlit -= 1;

    while hdist > 0 && d_lengths[(1 + hdist) - 1] == 0 {
        hdist -= 1;
    }
    hdist -= 1;

    hlit2 = hlit + 257;
    lld_total = (hlit2 + hdist) + 1;

    for mut i in 0..lld_total as usize {
        helper_EncodeTree_1(
            &mut rle_size,
            &mut rle_bits_size,
            &mut i,
            &mut j,
            ll_lengths,
            d_lengths,
            use_16,
            use_17,
            use_18,
            lld_total as u32,
            &mut rle,
            &mut rle_bits,
            hlit2,
            &mut clcounts,
            size_only,
        );
    }

    ZopfliCalculateBitLengths(&clcounts, 19, 7, &mut clcl);
    if !size_only {
        ZopfliLengthsToSymbols(&clcl, 19, 7, &mut clsymbols);
    }

    hclen = 15;
    while hclen > 0 && clcounts[ORDER[(hclen + 4) - 1]] == 0 {
        hclen -= 1;
    }
    hclen -= 1;

    if !size_only {
        AddBits(hlit as u32, 5, bp, out, outsize);
        AddBits(hdist as u32, 5, bp, out, outsize);
        AddBits(hclen as u32, 4, bp, out, outsize);
        
        for i in 0..(hclen + 4) {
            AddBits(clcl[ORDER[i]], 3, bp, out, outsize);
        }

        for i in 0..rle_size {
            let symbol = clsymbols[rle[i] as usize];
            AddHuffmanBits(symbol, clcl[rle[i] as usize], bp, out, outsize);
            match rle[i] {
                16 => AddBits(rle_bits[i], 2, bp, out, outsize),
                17 => AddBits(rle_bits[i], 3, bp, out, outsize),
                18 => AddBits(rle_bits[i], 7, bp, out, outsize),
                _ => (),
            }
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
            &mut 0,  // Temporary bp for size calculation
            &mut None,  // No output needed for size calculation
            &mut 0,  // No outsize needed for size calculation
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
        let size = EncodeTree(
            ll_lengths,
            d_lengths,
            (i & 1) != 0,
            (i & 2) != 0,
            (i & 4) != 0,
            &mut 0,
            &mut None,
            &mut 0,
        );

        if result == 0 || size < result {
            result = size;
        }
    }

    result
}
pub fn helper_OptimizeHuffmanForRle_1(
    i_ref: &mut i32,
    k_ref: &mut i32,
    stride_ref: &mut i32,
    sum_ref: &mut usize,
    limit_ref: &mut usize,
    length: i32,
    counts: &mut [usize],
    good_for_rle: &[i32],
    good_for_rle_idx: usize,
) {
    let mut i = *i_ref;
    let mut k = *k_ref;
    let mut stride = *stride_ref;
    let mut sum = *sum_ref;
    let mut limit = *limit_ref;

    if i == length || good_for_rle[i as usize + good_for_rle_idx] != 0 || AbsDiff(counts[i as usize], limit) >= 4 {
        if stride >= 4 || (stride >= 3 && sum == 0) {
            let mut count = (sum + (stride as usize / 2)) / stride as usize;
            if count < 1 {
                count = 1;
            }
            if sum == 0 {
                count = 0;
            }
            for k in 0..stride {
                counts[(i - k - 1) as usize] = count;
            }
        }
        stride = 0;
        sum = 0;
        limit = if i < (length - 3) {
            (counts[i as usize] + counts[(i + 1) as usize] + counts[(i + 2) as usize] + counts[(i + 3) as usize] + 2) / 4
        } else if i < length {
            counts[i as usize]
        } else {
            0
        };
    }

    stride += 1;
    if i != length {
        sum += counts[i as usize];
    }

    *i_ref = i;
    *k_ref = k;
    *stride_ref = stride;
    *sum_ref = sum;
    *limit_ref = limit;
}

pub fn OptimizeHuffmanForRle(length: i32, counts: &mut [usize]) {
    let mut length = length;
    // Find the last non-zero count
    while length > 0 {
        if counts[(length - 1) as usize] != 0 {
            break;
        }
        length -= 1;
    }
    if length == 0 {
        return;
    }

    // Allocate and initialize good_for_rle vector
    let mut good_for_rle = vec![0; length as usize];
    let good_for_rle_idx = 0;

    // First pass: mark runs that are good for RLE
    let mut symbol = counts[0];
    let mut stride = 0;
    for i in 0..=length {
        if i == length || counts[i as usize] != symbol {
            if (symbol == 0 && stride >= 5) || (symbol != 0 && stride >= 7) {
                for k in 0..stride {
                    good_for_rle[(i - k - 1) as usize] = 1;
                }
            }
            stride = 1;
            if i != length {
                symbol = counts[i as usize];
            }
        } else {
            stride += 1;
        }
    }

    // Second pass: use helper function
    let mut stride = 0;
    let mut limit = counts[0];
    let mut sum = 0;
    let mut i = 0;
    let mut k = 0;

    for _ in 0..=length {
        helper_OptimizeHuffmanForRle_1(
            &mut i,
            &mut k,
            &mut stride,
            &mut sum,
            &mut limit,
            length,
            counts,
            &good_for_rle,
            good_for_rle_idx,
        );
    }
}
pub fn helper_AddNonCompressedBlock_1(
    pos_ref: &mut usize,
    final_: bool,
    in_: &[u8],
    inend: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) -> bool {
    let pos = *pos_ref;
    let mut blocksize: u16 = 65535;
    
    if pos + blocksize as usize > inend {
        blocksize = (inend - pos) as u16;
    }
    
    let currentfinal = pos + blocksize as usize >= inend;
    let nlen = !blocksize;
    
    AddBit((final_ && currentfinal) as i32, bp, out, outsize);
    AddBit(0, bp, out, outsize);
    AddBit(0, bp, out, outsize);
    *bp = 0;
    
    // Helper closure to add bytes to output with dynamic resizing
    let mut add_byte = |byte: u8, out: &mut Option<Vec<u8>>, outsize: &mut usize| {
        if (*outsize & (*outsize - 1)) == 0 {
            let new_size = if *outsize == 0 { 1 } else { *outsize * 2 };
            match out {
                Some(vec) => vec.resize(new_size, 0),
                None => *out = Some(vec![0; new_size]),
            }
        }
        if let Some(vec) = out {
            if *outsize < vec.len() {
                vec[*outsize] = byte;
            }
        }
        *outsize += 1;
    };
    
    add_byte((blocksize % 256) as u8, out, outsize);
    add_byte((blocksize / 256 % 256) as u8, out, outsize);
    add_byte((nlen % 256) as u8, out, outsize);
    add_byte((nlen / 256 % 256) as u8, out, outsize);
    
    for i in 0..blocksize as usize {
        add_byte(in_[pos + i], out, outsize);
    }
    
    if currentfinal {
        return true;
    }
    
    *pos_ref = pos + blocksize as usize;
    false
}
pub fn CalculateBlockSymbolSizeSmall(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    let mut result = 0usize;

    // Check that litlens and dists exist
    let litlens = lz77.litlens.as_ref().expect("litlens must exist");
    let dists = lz77.dists.as_ref().expect("dists must exist");

    for i in lstart..lend {
        assert!(i < lz77.size, "index out of bounds");
        assert!(litlens[i] < 259, "invalid litlen value");

        if dists[i] == 0 {
            result += ll_lengths[litlens[i] as usize] as usize;
        } else {
            let ll_symbol = ZopfliGetLengthSymbol(litlens[i] as usize);
            let d_symbol = ZopfliGetDistSymbol(dists[i] as i32);
            result += ll_lengths[ll_symbol as usize] as usize;
            result += d_lengths[d_symbol as usize] as usize;
            result += ZopfliGetLengthSymbolExtraBits(ll_symbol) as usize;
            result += ZopfliGetDistSymbolExtraBits(d_symbol as usize) as usize;
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
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    if lstart + (288 * 3) > lend {
        return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
    }

    let mut result = 0usize;

    // First loop: 0..256
    for i in 0..256 {
        result += ll_lengths[i] as usize * ll_counts[i];
    }

    // Second loop: 257..286
    for i in 257..286 {
        result += ll_lengths[i] as usize * ll_counts[i];
        result += ZopfliGetLengthSymbolExtraBits(i as i32) as usize * ll_counts[i];
    }

    // Third loop: 0..30
    for i in 0..30 {
        result += d_lengths[i] as usize * d_counts[i];
        result += ZopfliGetDistSymbolExtraBits(i) as usize * d_counts[i];
    }

    result += ll_lengths[256] as usize;
    result
}
pub fn TryOptimizeHuffmanForRle(
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
    ll_counts: &[usize],
    d_counts: &[usize],
    ll_lengths: &mut [u32],
    d_lengths: &mut [u32],
) -> f64 {
    let mut ll_counts2 = [0; 288];
    let mut d_counts2 = [0; 32];
    let mut ll_lengths2 = [0; 288];
    let mut d_lengths2 = [0; 32];
    
    // Calculate initial tree and data sizes
    let treesize = CalculateTreeSize(ll_lengths, d_lengths) as f64;
    let datasize = CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend
    ) as f64;

    // Copy counts arrays (equivalent to memcpy)
    ll_counts2.copy_from_slice(&ll_counts[..288]);
    d_counts2.copy_from_slice(&d_counts[..32]);

    // Optimize for RLE and recalculate
    OptimizeHuffmanForRle(288, &mut ll_counts2);
    OptimizeHuffmanForRle(32, &mut d_counts2);
    
    ZopfliCalculateBitLengths(&ll_counts2, 288, 15, &mut ll_lengths2);
    ZopfliCalculateBitLengths(&d_counts2, 32, 15, &mut d_lengths2);
    PatchDistanceCodesForBuggyDecoders(&mut d_lengths2[..30].try_into().unwrap());
    
    let treesize2 = CalculateTreeSize(&ll_lengths2, &d_lengths2) as f64;
    let datasize2 = CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, &ll_lengths2, &d_lengths2, lz77, lstart, lend
    ) as f64;

    // Compare and return the better option
    if (treesize2 + datasize2) < (treesize + datasize) {
        ll_lengths.copy_from_slice(&ll_lengths2);
        d_lengths.copy_from_slice(&d_lengths2);
        treesize2 + datasize2
    } else {
        treesize + datasize
    }
}
pub fn GetDynamicLengths(
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
    ll_lengths: &mut [u32],
    d_lengths: &mut [u32],
) -> f64 {
    let mut ll_counts = [0; 288];
    let mut d_counts = [0; 32];
    
    ZopfliLZ77GetHistogram(lz77, lstart, lend, &mut ll_counts, &mut d_counts);
    ll_counts[256] = 1;
    
    ZopfliCalculateBitLengths(&ll_counts, 288, 15, ll_lengths);
    ZopfliCalculateBitLengths(&d_counts, 32, 15, d_lengths);
    
    // Convert d_lengths slice to array for PatchDistanceCodesForBuggyDecoders
    let mut d_lengths_array: [u32; 30] = [0; 30];
    d_lengths_array.copy_from_slice(&d_lengths[..30]);
    PatchDistanceCodesForBuggyDecoders(&mut d_lengths_array);
    d_lengths[..30].copy_from_slice(&d_lengths_array);
    
    TryOptimizeHuffmanForRle(lz77, lstart, lend, &ll_counts, &d_counts, ll_lengths, d_lengths)
}
pub fn CalculateBlockSymbolSize(
    ll_lengths: &[u32],
    d_lengths: &[u32],
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
) -> usize {
    if (lstart + (288 * 3)) > lend {
        CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend)
    } else {
        let mut ll_counts = [0; 288];
        let mut d_counts = [0; 32];
        ZopfliLZ77GetHistogram(lz77, lstart, lend, &mut ll_counts, &mut d_counts);
        CalculateBlockSymbolSizeGivenCounts(&ll_counts, &d_counts, ll_lengths, d_lengths, lz77, lstart, lend)
    }
}
pub fn ZopfliCalculateBlockSize(lz77: &ZopfliLZ77Store, lstart: usize, lend: usize, btype: i32) -> f64 {
    let mut ll_lengths = [0u32; 288];
    let mut d_lengths = [0u32; 32];
    let mut result = 3.0;

    match btype {
        0 => {
            let length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
            let rem = length % 65535;
            let blocks = (length / 65535) + if rem != 0 { 1 } else { 0 };
            return ((blocks * 5) * 8) as f64 + (length * 8) as f64;
        }
        1 => {
            GetFixedTree(&mut ll_lengths, &mut d_lengths);
            result += CalculateBlockSymbolSize(&ll_lengths, &d_lengths, lz77, lstart, lend) as f64;
        }
        _ => {
            result += GetDynamicLengths(lz77, lstart, lend, &mut ll_lengths, &mut d_lengths);
        }
    }

    result
}
pub fn ZopfliCalculateBlockSizeAutoType(lz77: &ZopfliLZ77Store, lstart: usize, lend: usize) -> f64 {
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
    final_: bool,
    in_: &[u8],
    instart: usize,
    inend: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut pos = instart;
    let _ = options; // Explicitly mark options as unused
    
    loop {
        let should_break = helper_AddNonCompressedBlock_1(
            &mut pos,
            final_,
            in_,
            inend,
            bp,
            out,
            outsize,
        );
        if should_break {
            break;
        }
    }
}
pub fn AddLZ77Data(
    lz77: &ZopfliLZ77Store,
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
        let dist = lz77.dists.as_ref().unwrap()[i] as u32;
        let litlen = lz77.litlens.as_ref().unwrap()[i] as u32;

        if dist == 0 {
            assert!(litlen < 256);
            assert!(ll_lengths[litlen as usize] > 0);
            AddHuffmanBits(
                ll_symbols[litlen as usize],
                ll_lengths[litlen as usize],
                bp,
                out,
                outsize,
            );
            testlength += 1;
        } else {
            let lls = ZopfliGetLengthSymbol(litlen as usize) as u32;
            let ds = ZopfliGetDistSymbol(dist as i32) as u32;
            assert!((litlen >= 3) && (litlen <= 288));
            assert!(ll_lengths[lls as usize] > 0);
            assert!(d_lengths[ds as usize] > 0);
            
            AddHuffmanBits(ll_symbols[lls as usize], ll_lengths[lls as usize], bp, out, outsize);
            AddBits(
                ZopfliGetLengthExtraBitsValue(litlen as usize) as u32,
                ZopfliGetLengthExtraBits(litlen as usize) as u32,
                bp,
                out,
                outsize,
            );
            AddHuffmanBits(d_symbols[ds as usize], d_lengths[ds as usize], bp, out, outsize);
            AddBits(
                ZopfliGetDistExtraBitsValue(dist as i32) as u32,
                ZopfliGetDistExtraBits(dist as i32) as u32,
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
    final_: bool,
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
    expected_data_size: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut ll_lengths = [0; 288];
    let mut d_lengths = [0; 32];
    let mut ll_symbols = [0; 288];
    let mut d_symbols = [0; 32];
    let detect_block_size = *outsize;
    let mut uncompressed_size = 0;

    if btype == 0 {
        let length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
        let pos = if lstart == lend { 0 } else { lz77.pos.as_ref().unwrap()[lstart] };
        let end = pos + length;
        AddNonCompressedBlock(options, final_, lz77.data.as_ref().unwrap(), pos, end, bp, out, outsize);
        return;
    }

    AddBit(final_ as i32, bp, out, outsize);
    AddBit(btype & 1, bp, out, outsize);
    AddBit((btype & 2) >> 1, bp, out, outsize);

    if btype == 1 {
        GetFixedTree(&mut ll_lengths, &mut d_lengths);
    } else {
        assert!(btype == 2);
        let detect_tree_size = *outsize;
        GetDynamicLengths(lz77, lstart, lend, &mut ll_lengths, &mut d_lengths);
        AddDynamicTree(&ll_lengths, &d_lengths, bp, out, outsize);
        if options.verbose > 0 {
            eprintln!("treesize: {}", (*outsize - detect_tree_size));
        }
    }

    ZopfliLengthsToSymbols(&ll_lengths, 288, 15, &mut ll_symbols);
    ZopfliLengthsToSymbols(&d_lengths, 32, 15, &mut d_symbols);
    let detect_block_size = *outsize;
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
    AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);

    for i in lstart..lend {
        uncompressed_size += if lz77.dists.as_ref().unwrap()[i] == 0 {
            1
        } else {
            lz77.litlens.as_ref().unwrap()[i] as usize
        };
    }

    let compressed_size = *outsize - detect_block_size;
    if options.verbose > 0 {
        eprintln!(
            "compressed block size: {} ({}k) (unc: {})",
            compressed_size,
            compressed_size / 1024,
            uncompressed_size
        );
    }
}
pub fn AddLZ77BlockAutoType(
    options: &ZopfliOptions,
    final_: bool,
    lz77: &ZopfliLZ77Store,
    lstart: usize,
    lend: usize,
    expected_data_size: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
    let mut fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
    let dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
    let expensivefixed = (lz77.size < 1000) || (fixedcost <= (dyncost * 1.1));
    let mut fixedstore = ZopfliLZ77Store {
        litlens: Option::None,
        dists: Option::None,
        size: 0,
        data: Option::None,
        pos: Option::None,
        ll_symbol: Option::None,
        d_symbol: Option::None,
        ll_counts: Option::None,
        d_counts: Option::None,
    };

    if lstart == lend {
        AddBits(final_ as u32, 1, bp, out, outsize);
        AddBits(1, 2, bp, out, outsize);
        AddBits(0, 7, bp, out, outsize);
        return;
    }

    ZopfliInitLZ77Store(lz77.data.as_deref(), &mut fixedstore);

    if expensivefixed {
        let instart = lz77.pos.as_ref().unwrap()[lstart];
        let inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);
        let mut s = ZopfliBlockState {
            options: Option::None,
            lmc: Option::None,
            blockstart: 0,
            blockend: 0,
        };
        ZopfliInitBlockState(options, instart, inend, true, &mut s);
        ZopfliLZ77OptimalFixed(&mut s, lz77.data.as_ref().unwrap(), instart, inend, &mut fixedstore);
        fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
        ZopfliCleanBlockState(&mut s);
    }

    if (uncompressedcost < fixedcost) && (uncompressedcost < dyncost) {
        AddLZ77Block(options, 0, final_, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    } else if fixedcost < dyncost {
        if expensivefixed {
            AddLZ77Block(options, 1, final_, &fixedstore, 0, fixedstore.size, expected_data_size, bp, out, outsize);
        } else {
            AddLZ77Block(options, 1, final_, lz77, lstart, lend, expected_data_size, bp, out, outsize);
        }
    } else {
        AddLZ77Block(options, 2, final_, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    }

    ZopfliCleanLZ77Store(&mut fixedstore);
}
pub fn ZopfliDeflatePart(
    options: &ZopfliOptions,
    btype: i32,
    final_: bool,
    in_data: &[u8],
    instart: usize,
    inend: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    if btype == 0 {
        AddNonCompressedBlock(options, final_, in_data, instart, inend, bp, out, outsize);
        return;
    } else if btype == 1 {
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
        let mut s = ZopfliBlockState {
            options: None,
            lmc: None,
            blockstart: 0,
            blockend: 0,
        };
        
        ZopfliInitLZ77Store(Some(in_data), &mut store);
        ZopfliInitBlockState(options, instart, inend, true, &mut s);
        ZopfliLZ77OptimalFixed(&mut s, in_data, instart, inend, &mut store);
        AddLZ77Block(options, btype, final_, &store, 0, store.size, 0, bp, out, outsize);
        
        ZopfliCleanBlockState(&mut s);
        ZopfliCleanLZ77Store(&mut store);
        return;
    }

    let mut splitpoints_uncompressed: Option<Vec<usize>> = None;
    let mut npoints = 0;
    let mut splitpoints: Option<Vec<usize>> = None;
    let mut splitpoints_idx = 0;
    let mut totalcost = 0.0;
    let mut lz77 = ZopfliLZ77Store {
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

    if options.blocksplitting != 0 {
        ZopfliBlockSplit(
            options,
            in_data,
            instart,
            inend,
            options.blocksplittingmax.try_into().unwrap(),
            &mut splitpoints_uncompressed,
            &mut npoints,
        );
        if npoints > 0 {
            splitpoints = Some(vec![0; npoints]);
        }
    }

    ZopfliInitLZ77Store(Some(in_data), &mut lz77);

    for i in 0..=npoints {
        let start = if i == 0 { instart } else { splitpoints_uncompressed.as_ref().unwrap()[i - 1] };
        let end = if i == npoints { inend } else { splitpoints_uncompressed.as_ref().unwrap()[i] };
        
        let mut s = ZopfliBlockState {
            options: None,
            lmc: None,
            blockstart: 0,
            blockend: 0,
        };
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
        
        ZopfliInitLZ77Store(Some(in_data), &mut store);
        ZopfliInitBlockState(options, start, end, true, &mut s);
        ZopfliLZ77Optimal(&mut s, in_data, start, end, options.numiterations, &mut store);
        totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);
        ZopfliAppendLZ77Store(&store, &mut lz77);
        
        if i < npoints {
            splitpoints.as_mut().unwrap()[i + splitpoints_idx] = lz77.size;
        }
        
        ZopfliCleanBlockState(&mut s);
        ZopfliCleanLZ77Store(&mut store);
    }

    if options.blocksplitting != 0 && npoints > 1 {
        let mut splitpoints2: Option<Vec<usize>> = None;
        let mut npoints2 = 0;
        let mut totalcost2 = 0.0;
        
        ZopfliBlockSplitLZ77(
            options,
            &lz77,
            options.blocksplittingmax.try_into().unwrap(),
            &mut splitpoints2,
            &mut npoints2,
        );
        
        for i in 0..=npoints2 {
            let start = if i == 0 { 0 } else { splitpoints2.as_ref().unwrap()[i - 1] };
            let end = if i == npoints2 { lz77.size } else { splitpoints2.as_ref().unwrap()[i] };
            totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
        }

        if totalcost2 < totalcost {
            splitpoints = splitpoints2;
            npoints = npoints2;
        }
    }

    for i in 0..=npoints {
        let start = if i == 0 { 0 } else { splitpoints.as_ref().unwrap()[(i - 1) + splitpoints_idx] };
        let end = if i == npoints { lz77.size } else { splitpoints.as_ref().unwrap()[i + splitpoints_idx] };
        AddLZ77BlockAutoType(options, (i == npoints) && final_, &lz77, start, end, 0, bp, out, outsize);
    }

    ZopfliCleanLZ77Store(&mut lz77);
}

pub fn ZopfliDeflate(
    options: &ZopfliOptions,
    btype: i32,
    final_: bool,
    in_data: &[u8],
    insize: usize,
    bp: &mut u8,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let offset = *outsize;
    let mut i = 0;
    
    while i < insize {
        let masterfinal = (i + 1000000) >= insize;
        let final2 = final_ && masterfinal;
        let size = if masterfinal { insize - i } else { 1000000 };
        
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
        let compressed_size = *outsize - offset;
        let compression_ratio = 100.0 * (insize as f64 - compressed_size as f64) / insize as f64;
        
        writeln!(
            io::stderr(),
            "Original Size: {}, Deflate: {}, Compression: {:.2}% Removed",
            insize,
            compressed_size,
            compression_ratio
        ).unwrap();
    }
}
