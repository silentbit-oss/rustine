use crate::*;

pub fn ti_atan_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_atan_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_atan(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_atan");
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = in1[i].atan();
    }
    
    0
}
