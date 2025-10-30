use crate::*;

pub fn ti_torad_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_torad(
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

    // Get the first input and output slices (equivalent to C's pointer indexing)
    let in1 = inputs[0];
    let output = &mut outputs[0];

    // Ensure the output slice has enough capacity
    if output.len() < size as usize {
        return 0;
    }

    // Convert each input value to radians
    for i in 0..size as usize {
        output[i] = in1[i] * (std::f64::consts::PI / 180.0);
    }

    0
}
