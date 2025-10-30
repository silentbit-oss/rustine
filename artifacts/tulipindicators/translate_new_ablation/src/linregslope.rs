use crate::*;
use rand::Rng;

pub fn ti_linregslope_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Return -1 for None or empty slice (equivalent to NULL/invalid pointer)
    }
}

pub fn ti_linregslope(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_linregslope_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;
    
    for i in 0..(period - 1) {
        let weight = (i + 1) as f64;
        x += weight;
        x2 += weight * weight;
        xy += input[i as usize] * weight;
        y += input[i as usize];
    }
    
    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;
    let bd = 1.0 / ((period_f64 * x2) - (x * x));
    
    let mut output_idx = 0;
    for i in (period - 1)..size {
        let i_usize = i as usize;
        xy += input[i_usize] * period_f64;
        y += input[i_usize];
        
        let b = ((period_f64 * xy) - (x * y)) * bd;
        output[output_idx] = b;
        output_idx += 1;
        
        xy -= y;
        y -= input[(i - period + 1) as usize];
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
