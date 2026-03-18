use crate::*;

pub fn ti_wcprice_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_wcprice(
    size: i32,
    inputs: Option<&[Option<&[f64]>]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [Option<&mut [f64]>]>
) -> Option<i32> {
    // Check for None in inputs and outputs (equivalent to NULL checks in C)
    let inputs = inputs?;
    let outputs = outputs?;

    // Get slices for high, low, close (inputs[0], inputs[1], inputs[2])
    let high = inputs.get(0)?.as_ref()?;
    let low = inputs.get(1)?.as_ref()?;
    let close = inputs.get(2)?.as_ref()?;

    // Get mutable slice for output (outputs[0])
    let output = outputs.get_mut(0)?.as_mut()?;

    // Ensure all slices have at least `size` elements
    if high.len() < size as usize || low.len() < size as usize || 
       close.len() < size as usize || output.len() < size as usize {
        return None;
    }

    // Iterate over the range [0, size)
    for i in 0..size as usize {
        output[i] = ((high[i] + low[i]) + close[i] + close[i]) * 0.25;
    }

    Some(0) // Return 0 as in the C code
}
