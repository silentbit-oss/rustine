use crate::*;

pub fn ti_medprice_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_medprice(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in all Option parameters
    let inputs = inputs?;
    let outputs = outputs?;
    // Options is unused per line 5 in C code, so we ignore it

    // Get slices safely, return None if indices are out of bounds
    let high = inputs.get(0)?;
    let low = inputs.get(1)?;
    let output = outputs.get_mut(0)?;

    // Ensure all slices have at least `size` elements
    if high.len() < size as usize || low.len() < size as usize || output.len() < size as usize {
        return None;
    }

    // Calculate median price for each element
    for i in 0..size as usize {
        output[i] = (high[i] + low[i]) * 0.5;
    }

    Some(0) // Return 0 to match C function's success return value
}
