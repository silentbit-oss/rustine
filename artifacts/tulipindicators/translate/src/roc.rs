use crate::*;

pub fn ti_roc_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}
pub fn ti_roc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for None values (equivalent to NULL checks in C)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return Err(1),
    };
    let period = match options {
        Some(options) => options[0] as i32,
        None => return Err(1),
    };
    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return Err(1),
    };

    if period < 1 {
        return Err(1);
    }

    let start = ti_roc_start(options);
    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    for i in period..size {
        let denominator = input[(i - period) as usize];
        if denominator == 0.0 {
            return Err(1); // Prevent division by zero
        }
        output[output_idx] = (input[i as usize] - denominator) / denominator;
        output_idx += 1;
    }

    // In Rust, we don't typically use asserts for control flow, so we verify the condition
    // and return an error if it fails, rather than panicking
    let expected_len = (size - start) as usize;
    if output_idx != expected_len {
        return Err(1);
    }

    Ok(())
}
