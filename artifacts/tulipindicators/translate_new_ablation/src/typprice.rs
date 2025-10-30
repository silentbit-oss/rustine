use crate::*;

pub fn ti_typprice_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_typprice(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let output = &mut outputs[0];
    
    for i in 0..size as usize {
        output[i] = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
    }
    
    0
}
