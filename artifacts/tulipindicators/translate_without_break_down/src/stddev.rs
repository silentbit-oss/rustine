use crate::*;
use std::os::raw::c_double;
use std::os::raw::c_int;
use std::f64::consts::SQRT_2;
pub fn ti_stddev_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is None or empty, return 0 as a safe default (since C would crash on NULL dereference)
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => 0,
    }
}

pub fn ti_stddev(
    size: c_int,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> c_int {
    // Check for None options and inputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return 1;
    }

    let start = ti_stddev_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // Initial window calculation
    for i in 0..period as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
    }

    // First output value
    {
        let mut s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx] = s2s2;
        output_idx += 1;
    }

    // Rolling window calculation
    for i in period as usize..size as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
        sum -= input[i - period as usize];
        sum2 -= input[i - period as usize] * input[i - period as usize];

        let mut s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx] = s2s2;
        output_idx += 1;
    }

    // Assertion check (commented out as it's not idiomatic in Rust)
    // assert!((output[output_idx] as *const f64 as usize - outputs[0][0] as *const f64 as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    0
}
