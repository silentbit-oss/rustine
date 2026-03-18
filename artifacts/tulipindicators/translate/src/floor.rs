use crate::*;
use libm::floor;

pub fn ti_floor_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_floor(
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

    // Get first input and output slices (equivalent to inputs[0] and outputs[0] in C)
    let in1 = inputs[0];
    let output = &mut outputs[0];

    // Iterate through each element and apply floor function
    for i in 0..size as usize {
        output[i] = floor(in1[i]);
    }

    0  // Return 0 like the C function
}
