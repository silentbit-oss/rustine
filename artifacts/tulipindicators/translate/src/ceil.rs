use crate::*;
use libm::ceil;

pub fn ti_ceil_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}

pub fn ti_ceil(
    size: i32,
    inputs: &[&[f64]],  // Use slices instead of raw pointers
    options: &[f64],    // Use slices instead of raw pointers
    outputs: &mut [&mut [f64]],  // Use mutable slices for outputs
) -> i32 {
    let in1 = inputs[0];  // Get the first input slice
    let output = &mut outputs[0];  // Get the first output slice (mutable)

    for i in 0..size as usize {
        output[i] = ceil(in1[i]);  // Apply ceil to each element
    }

    0  // Return 0 as in the C code
}
