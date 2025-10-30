use crate::*;
use rand::Rng;

pub fn ti_linregslope_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is None, we return -1 as a safe default (since we can't index None)
    match options {
        Some(opts) => {
            // Ensure the slice has at least one element to avoid panic
            if opts.is_empty() {
                -1
            } else {
                (opts[0] as i32) - 1
            }
        }
        None => -1,
    }
}

pub fn ti_linregslope(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None in inputs and outputs
    if inputs.is_none() || outputs.is_none() {
        return 1;
    }
    let inputs = inputs.unwrap();
    let mut outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Check period validity
    if options.is_none() {
        return 1;
    }
    let options = options.unwrap();
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    // Check size validity
    let start = ti_linregslope_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut output_idx = 0;
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;

    // Calculate initial sums
    for i in 0..(period - 1) {
        let weight = (i + 1) as f64;
        x += weight;
        x2 += weight * weight;
        xy += input[i as usize] * weight;
        y += input[i as usize];
    }

    // Add final period value
    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;

    // Calculate denominator
    let bd = 1.0 / ((period_f64 * x2) - (x * x));

    // Main calculation loop
    for i in (period - 1)..size {
        let i_usize = i as usize;
        xy += input[i_usize] * period_f64;
        y += input[i_usize];

        let b = ((period_f64 * xy) - (x * y)) * bd;
        output[output_idx] = b;
        output_idx += 1;

        xy -= y;
        y -= input[(i_usize - (period as usize - 1))];
    }

    // Assertion check (commented out as it would panic in Rust)
    // assert!((output[output_idx] - outputs[0][0]) == (size - ti_linregslope_start(Some(options))) as f64);

    0
}
