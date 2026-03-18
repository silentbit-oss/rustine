use crate::*;
use rand::Rng;

pub fn ti_wilders_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_wilders(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Option<i32> {
    let input = inputs?[0];
    let period = options?[0] as i32;
    let output_slice = &mut outputs?[0];
    
    if period < 1 {
        return Some(1);
    }
    
    let start = match ti_wilders_start(options) {
        Some(s) => s,
        None => return Some(1),
    };
    
    if size <= start {
        return Some(0);
    }
    
    let per = 1.0 / period as f64;
    let mut sum = 0.0;
    
    for i in 0..period as usize {
        sum += input[i];
    }
    
    let mut val = sum / period as f64;
    let mut output_idx = 0;
    output_slice[output_idx] = val;
    output_idx += 1;
    
    for i in period as usize..size as usize {
        val = ((input[i] - val) * per) + val;
        output_slice[output_idx] = val;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    Some(0)
}
