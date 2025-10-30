use crate::*;

pub fn ti_ad_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_ad(size: usize, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    let output = &mut outputs[0];
    let mut sum = 0.0;

    for i in 0..size {
        let hl = high[i] - low[i];
        if hl != 0.0 {
            sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
        }
        output[i] = sum;
    }

    0
}
