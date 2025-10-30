use crate::*;
use rand::Rng;

pub fn ti_emv_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    1
}

pub fn ti_emv(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let volume = inputs[2];
    let _ = options;
    let output_slice = &mut outputs[0];
    
    let start = ti_emv_start(options);
    if size <= start {
        return 0;
    }
    
    let mut last = (high[0] + low[0]) * 0.5;
    let mut output_idx = 0;
    
    for i in 1..size as usize {
        let hl = (high[i] + low[i]) * 0.5;
        let br = (volume[i] / 10000.0) / (high[i] - low[i]);
        output_slice[output_idx] = (hl - last) / br;
        output_idx += 1;
        last = hl;
    }
    
    assert!((output_idx as i32) == (size - ti_emv_start(options)));
    0
}
