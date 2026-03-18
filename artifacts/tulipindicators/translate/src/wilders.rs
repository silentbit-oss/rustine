use crate::*;
use rand::Rng;

pub fn ti_wilders_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;

    // Check if the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C, converting to i32
    Some(options[0] as i32 - 1)
}

pub fn ti_wilders(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for null inputs (None in Rust)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];

    if period < 1 {
        return Some(1);
    }

    let start = match ti_wilders_start(options) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let per = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut output_idx = 0;

    // Calculate initial sum
    for i in 0..period {
        sum += input[i as usize];
    }

    let mut val = sum / period as f64;
    output[output_idx] = val;
    output_idx += 1;

    // Calculate remaining values
    for i in period..size {
        let input_val = input[i as usize];
        val = ((input_val - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }

    // Assertion check (commented out as it's debug-only in C)
    // assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - output.as_ptr() as usize
    //     == (size - start) as usize * std::mem::size_of::<f64>());

    Some(0)
}
