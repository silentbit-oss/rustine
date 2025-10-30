use crate::*;

pub fn ti_bop_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_bop(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let _ = options; // explicitly ignore options to match C behavior
    let output = &mut outputs[0];

    for i in 0..size as usize {
        let hl = high[i] - low[i];
        output[i] = if hl <= 0.0 {
            0.0
        } else {
            (close[i] - open[i]) / hl
        };
    }

    0
}
