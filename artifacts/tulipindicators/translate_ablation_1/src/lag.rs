use crate::*;
use rand::Rng;

pub fn ti_lag_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => opts[0] as i32,
        None => 0, // Return 0 if options is None (equivalent to NULL pointer)
    }
}

pub fn ti_lag(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 0 {
        return 1;
    }
    
    let start = ti_lag_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[(i - period) as usize];
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
