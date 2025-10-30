use crate::*;

pub fn ti_div_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_div_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_div(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_div");
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    
    if inputs.len() < 2 {
        return 0;
    }
    let in1 = inputs[0];  // First input slice
    let in2 = inputs[1];  // Second input slice
    let output = &mut outputs[0];  // Mutable reference to output slice

    for i in 0..size as usize {
        output[i] = in1[i] / in2[i];  // Perform division
    }

    0  // Return success code
}
