use crate::*;

pub fn ti_sub_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_sub(
    size: i32,
    inputs: &[&[f64]],  // Use slices instead of raw pointers
    options: &[f64],    // Use slices instead of raw pointers
    outputs: &mut [&mut [f64]],  // Use mutable slices for outputs
) -> i32 {
    let in1 = inputs[0];
    let in2 = inputs[1];
    let _ = options;  // Explicitly ignore options to match C behavior
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = in1[i] - in2[i];
    }
    
    0  // Return 0 to match C behavior
}
