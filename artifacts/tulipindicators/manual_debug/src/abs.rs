use crate::*;

pub fn ti_abs_stream_new(options: Option<&[f64]>, stream: &mut Option<Box<TiStream>>) -> i32 {
    0
}

pub fn ti_abs_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_abs_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_abs(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_abs");
    // Early return if any required input is None
    if inputs.is_none() || outputs.is_none() {
        return 0;
    }

    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 0;
    }

    let in1 = inputs[0];
    let output = &mut outputs[0];

    // Ensure the output slice has enough capacity
    if output.len() < size as usize {
        return 0;
    }

    // Process each element
    for i in 0..size as usize {
        output[i] = in1[i].abs();
    }

    0
}
