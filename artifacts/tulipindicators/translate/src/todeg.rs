use crate::*;

pub fn ti_todeg_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_todeg(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = in1[i] * (180.0 / std::f64::consts::PI);
    }
    
    0
}
