use crate::*;

pub fn ti_mul_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_mul_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_mul(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_mul");
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    if inputs.len() < 2 {
        return 0;
    }
    let in1 = inputs[0];
    let in2 = inputs[1];
    let _ = options; // Explicitly ignore options to match C behavior
    let output = &mut outputs[0];

    for i in 0..size as usize {
        output[i] = in1[i] * in2[i];
    }

    0 // Return 0 to match C behavior
}
