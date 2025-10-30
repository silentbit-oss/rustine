use crate::*;

pub fn ti_add_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_add(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None in inputs and outputs (equivalent to NULL checks in C)
    if inputs.is_none() || outputs.is_none() {
        return 0;
    }

    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();

    // Ensure we have at least two input slices and one output slice
    if inputs.len() < 2 || outputs.is_empty() {
        return 0;
    }

    let in1 = inputs[0];
    let in2 = inputs[1];
    let output = &mut outputs[0];

    // Ensure all slices have at least `size` elements
    if in1.len() < size as usize || in2.len() < size as usize || output.len() < size as usize {
        return 0;
    }

    // Perform the addition operation
    for i in 0..size as usize {
        output[i] = in1[i] + in2[i];
    }

    0
}
