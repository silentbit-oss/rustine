use crate::*;

pub fn ti_abs_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_abs(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = in1[i].abs(); // f64::abs() is the Rust equivalent of fabs()
    }
    
    0
}
