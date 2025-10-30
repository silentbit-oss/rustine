use crate::*;
use std::f64;

pub fn ti_ln_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}

pub fn ti_ln(size: usize, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size {
        output[i] = f64::ln(in1[i]);
    }
    
    0
}
