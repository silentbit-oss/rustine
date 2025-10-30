use crate::*;

pub fn ti_obv_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_obv(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let close = inputs[0];
    let volume = inputs[1];
    let _ = options; // Explicitly ignore options to avoid unused variable warning
    let output = &mut outputs[0];

    let mut output_idx = 0;
    let mut sum = 0.0;
    output[output_idx] = sum;
    output_idx += 1;

    let mut prev = close[0];
    for i in 1..size as usize {
        if close[i] > prev {
            sum += volume[i];
        } else if close[i] < prev {
            sum -= volume[i];
        }
        prev = close[i];
        output[output_idx] = sum;
        output_idx += 1;
    }

    0
}
