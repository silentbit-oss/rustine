use crate::*;
use libm::tan;

pub fn ti_tan_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_tan(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in inputs and outputs (equivalent to NULL checks in C)
    let inputs = inputs?;
    let mut outputs = outputs?;
    let _options = options;  // Explicitly ignore options as in C code (line 4)

    // Get input and output slices (equivalent to C pointer assignments)
    let in1 = inputs.get(0)?;
    let output = outputs.get_mut(0)?;

    // Ensure output has enough capacity (safety check)
    if output.len() < size as usize {
        return None;
    }

    // Perform the tan operation on each element
    for i in 0..size as usize {
        output[i] = tan(in1[i]);
    }

    Some(0)  // Return 0 as success (equivalent to C return)
}
