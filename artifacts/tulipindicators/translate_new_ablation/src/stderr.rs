use crate::*;
use std::f64;

pub fn ti_stderr_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_stderr(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_stderr_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    let mul = 1.0 / (period as f64).sqrt();
    
    for i in 0..period as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
    }
    
    {
        let mut s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[0] = mul * s2s2;
    }
    
    let mut output_idx = 1;
    for i in period as usize..size as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
        sum -= input[i - period as usize];
        sum2 -= input[i - period as usize] * input[i - period as usize];
        
        let mut s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx] = mul * s2s2;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
