use crate::*;

pub fn ti_torad_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_torad(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Early return if any required input is None
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 0,
    };
    let outputs = match outputs {
        Some(outputs) => outputs,
        None => return 0,
    };

    // Get the first input and output slices
    let in1 = inputs[0];
    let output = &mut outputs[0];

    // Ensure the output slice has enough capacity
    if output.len() < size as usize {
        return 0;
    }

    // Perform the conversion
    for i in 0..size as usize {
        output[i] = in1[i] * (std::f64::consts::PI / 180.0);
    }

    0
}
