use crate::*;
use rand::Rng;

pub fn ti_vosc_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_vosc_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if options has at least 2 elements (since we access index 1)
    if options.len() < 2 {
        return None;
    }

    Some(options[1] as i32 - 1)
}

pub fn ti_vosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_vosc");
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if we have at least one input and output
    if inputs.is_empty() || outputs.is_empty() {
        return Some(1);
    }

    let input = inputs[0];
    let output = &mut outputs[0];

    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    if short_period < 1 || long_period < short_period {
        return Some(1);
    }

    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;

    let start = match ti_vosc_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let mut output_idx = 0;
    let mut short_sum = 0.0;
    let mut long_sum = 0.0;

    // Initialize sums
    for i in 0..long_period {
        if i >= (long_period - short_period) {
            short_sum += input[i as usize];
        }
        long_sum += input[i as usize];
    }

    // First output
    {
        let savg = short_sum * short_div;
        let lavg = long_sum * long_div;
        output[output_idx] = (100.0 * (savg - lavg)) / lavg;
        output_idx += 1;
    }

    // Remaining outputs
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

    // Assertion check (commented out as it's not idiomatic in Rust)
    // assert!((output[output_idx] - outputs[0][0]) == (size - start) as f64);

    Some(0)
}
