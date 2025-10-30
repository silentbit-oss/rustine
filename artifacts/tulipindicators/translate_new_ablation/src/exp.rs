use crate::*;
use std::f64;

pub fn ti_exp_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_exp(size: usize, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size {
        output[i] = f64::exp(in1[i]);
    }
    
    0
}
