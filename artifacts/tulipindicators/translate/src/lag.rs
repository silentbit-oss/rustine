use crate::*;
use std::assert;

pub fn ti_lag_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32)
}

pub fn ti_lag(
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

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Get period from options, return error if negative
    let period = options[0] as i32;
    if period < 0 {
        return Some(1);
    }

    // Check if size is sufficient
    let start = match ti_lag_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };
    if size <= start {
        return Some(0);
    }

    // Perform the lag operation
    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[(i - period) as usize];
        output_idx += 1;
    }

    // Assert the output length matches expected
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - outputs[0].as_ptr() as usize
            == ((size - start) as usize * std::mem::size_of::<f64>()));

    Some(0)
}
