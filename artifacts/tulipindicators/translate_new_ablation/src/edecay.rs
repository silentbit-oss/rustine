use crate::*;

pub fn ti_edecay_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    0
}
pub fn ti_edecay(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output_slice = &mut outputs[0];
    
    let scale = 1.0 - (1.0 / period as f64);
    
    if size > 0 {
        output_slice[0] = input[0];
        
        for i in 1..size as usize {
            let d = output_slice[i - 1] * scale;
            output_slice[i] = if input[i] > d { input[i] } else { d };
        }
    }
    
    0
}
