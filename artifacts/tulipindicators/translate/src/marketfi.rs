use crate::*;

pub fn ti_marketfi_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_marketfi(
    size: i32,
    inputs: Option<&[Option<&[f64]>]>,
    options: Option<&f64>,
    outputs: Option<&mut [Option<&mut [f64]>]>,
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

    // Get input slices safely
    let high = match inputs.get(0).and_then(|x| *x) {
        Some(high) => high,
        None => return 0,
    };
    let low = match inputs.get(1).and_then(|x| *x) {
        Some(low) => low,
        None => return 0,
    };
    let volume = match inputs.get(2).and_then(|x| *x) {
        Some(volume) => volume,
        None => return 0,
    };

    // Get output slice safely
    let output = match outputs.get_mut(0).and_then(|x| x.as_mut()) {
        Some(output) => output,
        None => return 0,
    };

    let start = ti_marketfi_start(options);
    if size <= start {
        return 0;
    }

    let size = size as usize;
    let start = start as usize;

    // Ensure we don't go out of bounds
    let iter_len = size.min(high.len()).min(low.len()).min(volume.len()).min(output.len());
    
    for i in 0..iter_len {
        output[i] = (high[i] - low[i]) / volume[i];
    }

    // Assert equivalent - debug_assert! only runs in debug mode
    debug_assert!((output.len() - start) == (size - start));

    0
}
