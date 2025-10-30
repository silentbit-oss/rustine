use crate::*;
use std::f64;

pub fn ti_vidya_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.len() < 2 {
        return None;
    }
    Some(options[1] as i32 - 2)
}
pub fn ti_vidya(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let alpha = options[2];
    let output = &mut outputs[0];
    
    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    if long_period < 2 {
        return 1;
    }
    if alpha < 0.0 || alpha > 1.0 {
        return 1;
    }
    
    let start = match ti_vidya_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut short_sum = 0.0;
    let mut short_sum2 = 0.0;
    let mut long_sum = 0.0;
    let mut long_sum2 = 0.0;
    
    for i in 0..long_period as usize {
        long_sum += input[i];
        long_sum2 += input[i] * input[i];
        if i >= (long_period - short_period) as usize {
            short_sum += input[i];
            short_sum2 += input[i] * input[i];
        }
    }
    
    let mut val = input[long_period as usize - 2];
    output[0] = val;
    let mut output_idx = 1;
    
    if (long_period - 1) < size {
        let short_stddev = ((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div))).sqrt();
        let long_stddev = ((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div))).sqrt();
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[long_period as usize - 1] - val) * k) + val;
        output[output_idx] = val;
        output_idx += 1;
    }
    
    for i in long_period as usize..size as usize {
        long_sum += input[i];
        long_sum2 += input[i] * input[i];
        short_sum += input[i];
        short_sum2 += input[i] * input[i];
        long_sum -= input[i - long_period as usize];
        long_sum2 -= input[i - long_period as usize] * input[i - long_period as usize];
        short_sum -= input[i - short_period as usize];
        short_sum2 -= input[i - short_period as usize] * input[i - short_period as usize];
        
        let short_stddev = ((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div))).sqrt();
        let long_stddev = ((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div))).sqrt();
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[i] - val) * k) + val;
        output[output_idx] = val;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
