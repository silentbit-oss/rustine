use crate::*;
use std::f64;

pub fn ti_exp_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_exp_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_exp(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_exp");
    let mut inputs = inputs.unwrap();
    let mut outputs = outputs.unwrap();
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = f64::exp(in1[i]);
    }
    
    0
}
