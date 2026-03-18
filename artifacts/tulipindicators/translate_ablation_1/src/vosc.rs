use crate::*;
use rand::Rng;

pub fn ti_vosc_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.len() < 2 {
        return None;
    }
    Some(options[1] as i32 - 1)
}

pub fn ti_vosc(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None values (equivalent to NULL checks in C)
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let mut outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Extract options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    // Validate parameters
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }

    // Get start index
    let start = match ti_vosc_start(Some(options)) {
        Some(start) => start,
        None => return 1,
    };

    if size <= start {
        return 0;
    }

    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;

    let mut short_sum = 0.0;
    let mut long_sum = 0.0;

    // Initialize sums for the first long_period elements
    for i in 0..long_period as usize {
        if i >= (long_period - short_period) as usize {
            short_sum += input[i];
        }
        long_sum += input[i];
    }

    // Calculate first output value
    let savg = short_sum * short_div;
    let lavg = long_sum * long_div;
    output[0] = (100.0 * (savg - lavg)) / lavg;

    // Process remaining elements
    for i in long_period as usize..size as usize {
        short_sum += input[i];
        short_sum -= input[i - short_period as usize];
        long_sum += input[i];
        long_sum -= input[i - long_period as usize];

        let savg = short_sum * short_div;
        let lavg = long_sum * long_div;
        output[i - long_period as usize + 1] = (100.0 * (savg - lavg)) / lavg;
    }

    // Verify output length matches expected
    let expected_outputs = (size - start) as usize;
    assert!((output.len() >= expected_outputs), "Output buffer too small");

    0
}
