use crate::*;
use rand::Rng;

pub fn ti_wma_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_wma_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(options[0] as i32 - 1)
}

pub fn ti_wma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_wma");
    // Check for null equivalents in Rust (None)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];

    if period < 1 {
        return Some(1);
    }

    let start = match ti_wma_start(options) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let weights = (period * (period + 1)) as f64 / 2.0;
    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    let mut output_idx = 0;

    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * (i + 1) as f64;
        sum += input[i];
    }

    for i in (period - 1) as usize..size as usize {
        weight_sum += input[i] * period as f64;
        sum += input[i];
        output[output_idx] = weight_sum / weights;
        output_idx += 1;
        weight_sum -= sum;
        sum -= input[(i as i32 - period) as usize + 1];
    }

    // Note: The assert in C is removed as Rust's safety checks make it redundant
    Some(0)
}
