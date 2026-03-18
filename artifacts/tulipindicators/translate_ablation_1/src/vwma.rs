use crate::*;
use std::assert;

pub fn ti_vwma_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if opts.len() > 0 => opts[0] as i32 - 1,
        _ => -1,
    }
}

pub fn ti_vwma(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let volume = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_vwma_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    let mut vsum = 0.0;
    
    for i in 0..period as usize {
        sum += input[i] * volume[i];
        vsum += volume[i];
    }
    
    output[0] = sum / vsum;
    
    for i in period as usize..size as usize {
        sum += input[i] * volume[i];
        sum -= input[i - period as usize] * volume[i - period as usize];
        vsum += volume[i];
        vsum -= volume[i - period as usize];
        output[i - period as usize + 1] = sum / vsum;
    }
    
    let output_len = (size - start) as usize;
    assert!((output[..output_len].len()) == output_len);
    
    0
}
