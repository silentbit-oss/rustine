use crate::*;

pub fn ti_tsf_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Return -1 for None or empty slice (similar to NULL/invalid pointer case in C)
    }
}
pub fn helper_ti_tsf_1(
    output_idx_ref: &mut u32,
    size: i32,
    input: &[f64],
    period: i32,
    output: &mut [f64],
) {
    let mut output_idx = *output_idx_ref;
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;
    let p = 1.0 / period as f64;
    
    // First loop: calculate initial sums
    for i in 0..(period - 1) {
        let i_plus_1 = (i + 1) as f64;
        x += i_plus_1;
        x2 += i_plus_1 * i_plus_1;
        xy += input[i as usize] * i_plus_1;
        y += input[i as usize];
    }

    // Add period values
    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;
    let bd = 1.0 / ((period_f64 * x2) - (x * x));

    // Second loop: process remaining elements
    for i in (period - 1)..size {
        let i_usize = i as usize;
        let period_minus_1_usize = (i - (period - 1)) as usize;
        
        xy += input[i_usize] * period_f64;
        y += input[i_usize];
        let b = ((period_f64 * xy) - (x * y)) * bd;

        // Equivalent to the do-while(false) block
        {
            let a = (y - (b * x)) * p;
            output[output_idx as usize] = a + (b * (period_f64 + 1.0));
            output_idx += 1;
        }

        xy -= y;
        y -= input[period_minus_1_usize + 1];
    }

    *output_idx_ref = output_idx;
}
pub fn ti_tsf(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None in inputs, options, and outputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Get input and output slices (equivalent to C pointer dereferencing)
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    let mut output_idx: u32 = 0;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_tsf_start(Some(options));
    if size <= start {
        return 0;
    }
    
    // Call helper function with mutable references
    helper_ti_tsf_1(&mut output_idx, size, input, period, output);
    
    // Assertion check (using Rust's assert! macro)
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);
    
    0
}
