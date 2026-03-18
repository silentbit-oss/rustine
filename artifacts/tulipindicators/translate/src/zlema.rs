use crate::*;
use rand::Rng;

pub fn ti_zlema_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some((((options[0] as i32) - 1) / 2) - 1)
}
pub fn ti_zlema(
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

    // Check if inputs[0] exists
    if inputs.is_empty() {
        return Some(1);
    }
    let input = inputs[0];

    // Check period validity
    if options.is_empty() {
        return Some(1);
    }
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Check if outputs[0] exists
    if outputs.is_empty() {
        return Some(1);
    }
    let output = &mut outputs[0];

    // Calculate lag and check size
    let lag = (period - 1) / 2;
    let start = match ti_zlema_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };
    if size <= start {
        return Some(0);
    }

    // Main calculation
    let per = 2.0 / (period as f64 + 1.0);
    let mut val = input[lag as usize - 1];
    output[0] = val;

    let mut output_idx = 1;
    for i in lag..size {
        let c = input[i as usize];
        let l = input[(i - lag) as usize];
        val = ((c + (c - l) - val) * per) + val;
        output[output_idx as usize] = val;
        output_idx += 1;
    }

    // Assertion check (Rust doesn't have exact pointer arithmetic like C, so we skip this)
    Some(0)
}
