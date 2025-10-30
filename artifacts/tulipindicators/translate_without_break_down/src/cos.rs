use crate::*;
use libm::cos;

pub fn ti_cos_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_cos(
    size: i32,
    inputs: &[&[f64]],  // Equivalent to const double * const *inputs
    options: &[f64],     // Equivalent to const double *options
    outputs: &mut [&mut [f64]],  // Equivalent to double * const *outputs
) -> i32 {
    let in1 = inputs[0];  // Equivalent to const double *in1 = inputs[0]
    let output = &mut outputs[0];  // Equivalent to double *output = outputs[0]

    for i in 0..size as usize {
        output[i] = cos(in1[i]);  // Compute cosine for each element
    }

    0  // Return 0 like the C function
}
