use crate::*;
use std::f64::consts::SQRT_2;

pub fn ti_bbands_start(options: Option<&[f64]>) -> Option<i32> {
    match options {
        Some(opts) if !opts.is_empty() => Some((opts[0] as i32) - 1),
        _ => None,
    }
}
pub fn ti_bbands(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    
    let period = options[0] as i32;
    let stddev = options[1];
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_bbands_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    
    for i in 0..period as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
    }
    
    let mut sd = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt();
    outputs[1][0] = sum * scale;
    outputs[0][0] = outputs[1][0] - (stddev * sd);
    outputs[2][0] = outputs[1][0] + (stddev * sd);
    
    let mut middle_idx = 1;
    let mut lower_idx = 1;
    let mut upper_idx = 1;
    
    for i in period as usize..size as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
        sum -= input[i - period as usize];
        sum2 -= input[i - period as usize] * input[i - period as usize];
        
        sd = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt();
        outputs[1][middle_idx] = sum * scale;
        outputs[2][upper_idx] = outputs[1][middle_idx] + (stddev * sd);
        outputs[0][lower_idx] = outputs[1][middle_idx] - (stddev * sd);
        
        middle_idx += 1;
        lower_idx += 1;
        upper_idx += 1;
    }
    
    let result_size = size - start;
    assert!((lower_idx as i32) == result_size);
    assert!((middle_idx as i32) == result_size);
    assert!((upper_idx as i32) == result_size);
    
    0
}
