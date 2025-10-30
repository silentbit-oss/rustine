use crate::*;
use libm::cosh;

pub fn ti_cosh_start(options: Option<&f64>) -> i32 {
	println!("\n* ti_cosh_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_cosh(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
	println!("\n* ti_cosh");
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = cosh(in1[i]);
    }
    
    0
}
