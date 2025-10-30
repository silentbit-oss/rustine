use crate::*;
use libm::sqrt;

pub fn ti_sqrt_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}

pub fn ti_sqrt(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = sqrt(in1[i]);
    }
    
    0
}
