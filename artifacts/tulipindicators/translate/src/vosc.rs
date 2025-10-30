use crate::*;
use std::assert;

pub fn ti_vosc_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.len() > 1 {
            Some(opts[1] as i32 - 1)
        } else {
            None
        }
    })
}

pub fn ti_vosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return Some(1);
    }

    let input = inputs[0];
    let output = &mut outputs[0];
    let mut output_idx = 0;

    // Extract options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    if short_period < 1 || long_period < short_period {
        return Some(1);
    }

    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;

    // Check if size is sufficient
    if let Some(start) = ti_vosc_start(Some(options)) {
        if size <= start {
            return Some(0);
        }
    } else {
        return Some(1);
    }

    let mut short_sum = 0.0;
    let mut long_sum = 0.0;

    // Initialize sums
    for i in 0..long_period {
        if i >= (long_period - short_period) {
            short_sum += input[i as usize];
        }
        long_sum += input[i as usize];
    }

    // Compute first output
    {
        let savg = short_sum * short_div;
        let lavg = long_sum * long_div;
        output[output_idx] = (100.0 * (savg - lavg)) / lavg;
        output_idx += 1;
    }

    // Compute remaining outputs
    for i in long_period..size {
        let i_usize = i as usize;
        let short_period_usize = short_period as usize;
        let long_period_usize = long_period as usize;

        short_sum += input[i_usize];
        short_sum -= input[i_usize - short_period_usize];
        long_sum += input[i_usize];
        long_sum -= input[i_usize - long_period_usize];

        let savg = short_sum * short_div;
        let lavg = long_sum * long_div;
        output[output_idx] = (100.0 * (savg - lavg)) / lavg;
        output_idx += 1;
    }

    // Assertion check (Rust's assert! macro)
    let start = ti_vosc_start(Some(options)).unwrap_or(0);
    assert!((output_idx as i32) == (size - start));

    Some(0)
}
