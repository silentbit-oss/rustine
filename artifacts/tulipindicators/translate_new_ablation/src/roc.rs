use crate::*;
use rand::Rng;

pub fn ti_roc_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 for NULL pointer or empty slice
    }
}

pub fn ti_roc(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_roc_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in period..size {
        let value = (input[i as usize] - input[(i - period) as usize]) / input[(i - period) as usize];
        output[output_idx] = value;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - ti_roc_start(Some(options))));
    0
}
