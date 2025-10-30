use crate::*;
use std::assert;

pub fn ti_wilders_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn ti_wilders(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    mut outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for null inputs/outputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let outputs_ref = outputs.as_mut().unwrap();
    let output = &mut outputs_ref[0];

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

    let per = 1.0 / (period as f64);
    let mut sum = 0.0;
    let mut output_idx = 0;

    // Calculate initial sum
    for i in 0..period {
        sum += input[i as usize];
    }

    let mut val = sum / (period as f64);
    output[output_idx] = val;
    output_idx += 1;

    // Calculate remaining values
    for i in period..size {
        let input_val = input[i as usize];
        val = ((input_val - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }

    // Assertion check (Rust's assert! macro)
    assert!((output.as_ptr() as usize - outputs_ref[0].as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - start) as usize);

    Some(0)
}
