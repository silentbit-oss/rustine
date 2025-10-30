use crate::*;
use rand::Rng;

pub fn ti_nvi_start(options: Option<&[f64]>) -> i32 {
    // The C function ignores the options parameter, so we do the same
    let _ = options;
    0
}
pub fn ti_nvi(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let close = inputs[0];
    let volume = inputs[1];
    let output = &mut outputs[0];
    
    let start = ti_nvi_start(options);
    if size <= start {
        return 0;
    }
    
    let mut nvi = 1000.0;
    output[0] = nvi;
    
    for i in 1..size as usize {
        if volume[i] < volume[i - 1] {
            nvi += ((close[i] - close[i - 1]) / close[i - 1]) * nvi;
        }
        output[i] = nvi;
    }
    
    assert!((output.len() as i32) == (size - start));
    0
}
