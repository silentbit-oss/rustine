use crate::*;
use libm::ceil;

pub fn ti_ceil_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_ceil_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_ceil(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_ceil");
    // Check for None in inputs and outputs (equivalent to NULL checks in C)
    if inputs.is_none() || outputs.is_none() {
        return 0;
    }

    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();

    // Get the first input and output slices (equivalent to C's array indexing)
    let in1 = inputs[0];
    let output = &mut outputs[0];

    // Iterate through each element and apply ceil
    for i in 0..size as usize {
        output[i] = ceil(in1[i]);
    }

    0  // Return 0 like the C function
}
