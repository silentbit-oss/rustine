use crate::*;

pub fn ti_decay_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_decay(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let input = inputs[0];
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    
    output[output_idx] = input[0];
    output_idx += 1;
    
    for i in 1..size as usize {
        let d = output[output_idx - 1] - scale;
        output[output_idx] = if input[i] > d { input[i] } else { d };
        output_idx += 1;
    }
    
    0
}
