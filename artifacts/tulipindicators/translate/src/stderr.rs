use crate::*;
use std::f64::consts::SQRT_2;
use std::assert;

pub fn ti_stderr_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}

pub fn ti_stderr(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return 1,
    };
    let period = match options {
        Some(options) => options[0] as i32,
        None => return 1,
    };
    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return 1,
    };

    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return 1;
    }

    let start = match ti_stderr_start(options) {
        Some(start) => start,
        None => return 0,
    };

    if size <= start {
        return 0;
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;
    let mul = 1.0 / (period as f64).sqrt();

    // First window calculation
    for i in 0..period {
        let val = input[i as usize];
        sum += val;
        sum2 += val * val;
    }

    {
        let mean = sum * scale;
        let mut s2s2 = (sum2 * scale) - (mean * mean);
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx as usize] = mul * s2s2;
        output_idx += 1;
    }

    // Rolling window calculation
    for i in period..size {
        let new_val = input[i as usize];
        let old_val = input[(i - period) as usize];
        
        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;

        let mean = sum * scale;
        let mut s2s2 = (sum2 * scale) - (mean * mean);
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx as usize] = mul * s2s2;
        output_idx += 1;
    }

    // Assertion check (Rust's assert! macro)
    assert!((output_idx as i32) == (size - start));
    
    0
}
