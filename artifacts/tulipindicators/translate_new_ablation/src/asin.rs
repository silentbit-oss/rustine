use crate::*;
use libm::asin;

pub fn ti_asin_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_asin(
    size: i32,
    inputs: &[&[f64]],  // Use slices instead of raw pointers
    options: &[f64],    // Options are unused but kept for interface consistency
    outputs: &mut [&mut [f64]],  // Mutable slice for outputs
) -> i32 {
    let in1 = inputs[0];  // Get first input slice
    let output = &mut outputs[0];  // Get first output slice (mutable)

    // Iterate through the slices and compute asin for each element
    for i in 0..size as usize {
        output[i] = asin(in1[i]);
    }

    0  // Return success code
}
