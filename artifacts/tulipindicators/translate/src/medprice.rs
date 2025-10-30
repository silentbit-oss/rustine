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
    // Check for None in inputs and outputs (equivalent to NULL checks in C)
    let inputs = inputs?;
    let mut outputs = outputs?;

    // Get high and low slices from inputs (index 0 and 1)
    let high = inputs.get(0)?;
    let low = inputs.get(1)?;

    // Get mutable output slice from outputs (index 0)
    let output = outputs.get_mut(0)?;

    // Ensure all slices have at least `size` elements
    if high.len() < size as usize || low.len() < size as usize || output.len() < size as usize {
        return None;
    }

    // Calculate median price for each element
    for i in 0..size as usize {
        output[i] = (high[i] + low[i]) * 0.5;
    }

    Some(0) // Return 0 on success (wrapped in Option)
}
