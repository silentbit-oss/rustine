use crate::*;
use libm::acos;

pub fn ti_acos_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_acos_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_acos(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_acos");
    let in1 = inputs.unwrap()[0];  // Equivalent to const double *in1 = inputs[0]
    let output = &mut outputs.unwrap()[0];  // Equivalent to double *output = outputs[0]

    for i in 0..size as usize {
        output[i] = acos(in1[i]);
    }

    0  // Return 0 like the C function
}
