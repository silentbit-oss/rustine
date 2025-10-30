use crate::*;
use rand::Rng;

pub fn ti_pvi_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    0
}

pub fn ti_pvi(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let close = inputs[0];
    let volume = inputs[1];
    let output = &mut outputs[0];
    
    let start = ti_pvi_start(options);
    if size <= start {
        return 0;
    }
    
    let mut pvi = 1000.0;
    output[0] = pvi;
    
    for i in 1..size as usize {
        if volume[i] > volume[i - 1] {
            pvi += ((close[i] - close[i - 1]) / close[i - 1]) * pvi;
        }
        output[i] = pvi;
    }
    
    assert!((output.len() as i32) == (size - start));
    0
}
