use crate::*;

pub fn ti_trunc_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_trunc(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let in1 = inputs[0];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = in1[i] as i32 as f64;
    }
    
    0
}
