use crate::*;
use std::assert;

pub fn ti_vwma_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_vwma_start");
    // Check if options is None (equivalent to NULL check in C)
    // If options is None, accessing [0] would panic, so we return a default value
    // Note: The C version doesn't handle NULL, but Rust forces us to be explicit
    match options {
        Some(opts) => {
            if opts.is_empty() {
                // Handle empty slice case (C would likely crash here)
                -1
            } else {
                (opts[0] as i32) - 1
            }
        }
        None => -1, // Default return when options is None
    }
}

pub fn ti_vwma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_vwma");
    // Check for None values (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input slices
    let input = inputs[0];
    let volume = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let start = ti_vwma_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut output_idx = 0;
    let mut sum = 0.0;
    let mut vsum = 0.0;

    // Initial window calculation
    for i in 0..period as usize {
        sum += input[i] * volume[i];
        vsum += volume[i];
    }

    output[output_idx] = sum / vsum;
    output_idx += 1;

    // Rolling window calculation
    for i in period as usize..size as usize {
        sum += input[i] * volume[i];
        sum -= input[i - period as usize] * volume[i - period as usize];
        vsum += volume[i];
        vsum -= volume[i - period as usize];
        output[output_idx] = sum / vsum;
        output_idx += 1;
    }

    // Assertion check (Rust uses usize for pointer arithmetic)
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - output.as_ptr() as usize
        == ((size - start) as usize) * std::mem::size_of::<f64>());

    0
}
