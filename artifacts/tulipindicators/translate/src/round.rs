use crate::*;
use std::f64;

pub fn ti_round_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_round(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = f64::floor(in1[i] + 0.5);
    }
    
    0
}
