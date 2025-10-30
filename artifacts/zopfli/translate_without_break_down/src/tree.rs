use crate::*;
use std::assert;
use std::f64::consts::LN_2;


pub fn ZopfliLengthsToSymbols(lengths: &[u32], n: usize, maxbits: u32, symbols: &mut [u32]) {
    // Allocate vectors instead of using malloc
    let mut bl_count = vec![0; (maxbits + 1) as usize];
    let mut next_code = vec![0; (maxbits + 1) as usize];

    // Initialize symbols to 0
    for i in 0..n {
        symbols[i] = 0;
    }

    // Initialize bl_count to 0
    for bits in 0..=maxbits {
        bl_count[bits as usize] = 0;
    }

    // Count the number of codes for each length
    for i in 0..n {
        assert!(lengths[i] <= maxbits);
        bl_count[lengths[i] as usize] += 1;
    }

    // Calculate the next code for each length
    let mut code = 0;
    bl_count[0] = 0;
    for bits in 1..=maxbits {
        code = (code + bl_count[(bits - 1) as usize]) << 1;
        next_code[bits as usize] = code;
    }

    // Assign symbols
    for i in 0..n {
        let len = lengths[i];
        if len != 0 {
            symbols[i] = next_code[len as usize];
            next_code[len as usize] += 1;
        }
    }
    // Vectors are automatically dropped when they go out of scope
}

pub fn ZopfliCalculateEntropy(count: &[usize], bitlengths: &mut [f64]) {
    const K_INV_LOG2: f64 = 1.4426950408889;  // 1.0 / ln(2)
    
    let sum: usize = count.iter().sum();
    let n = count.len() as f64;
    
    let log2sum = if sum == 0 {
        n.ln() * K_INV_LOG2
    } else {
        (sum as f64).ln() * K_INV_LOG2
    };
    
    for (i, &cnt) in count.iter().enumerate() {
        bitlengths[i] = if cnt == 0 {
            log2sum
        } else {
            log2sum - (cnt as f64).ln() * K_INV_LOG2
        };
        
        // Handle very small negative values (round to zero)
        if bitlengths[i] < 0.0 && bitlengths[i] > -1e-5 {
            bitlengths[i] = 0.0;
        }
        
        assert!(bitlengths[i] >= 0.0, "Bitlength must be non-negative");
    }
}
pub fn ZopfliCalculateBitLengths(
    count: &[usize],
    n: usize,
    maxbits: i32,
    bitlengths: &mut [u32],
) {
    let error = ZopfliLengthLimitedCodeLengths(count, n as i32, maxbits, bitlengths);
    assert!(error == 0);
}
