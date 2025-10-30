use crate::*;
use std::f64;

pub fn ti_stderr_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C, but safely
    Some(options[0] as i32 - 1)
}

pub fn ti_stderr(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Option<i32> {
    // Check for None in all Option parameters
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;
    
    // Get slices safely
    let input = inputs.get(0)?;
    let period = options.get(0).map(|&x| x as i32)?;
    let output = outputs.get_mut(0)?;
    
    if period < 1 {
        return Some(1);
    }
    
    let start = ti_stderr_start(Some(options))?;
    if size <= start {
        return Some(0);
    }
    
    let scale = 1.0 / period as f64;
    let mul = 1.0 / (period as f64).sqrt();
    
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    let mut output_idx = 0;
    
    // Initialize sum and sum2 for first period elements
    for i in 0..period as usize {
        let val = input.get(i)?;
        sum += val;
        sum2 += val * val;
    }
    
    // Calculate first output value
    {
        let mean = sum * scale;
        let mut s2s2 = (sum2 * scale) - (mean * mean);
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx] = mul * s2s2;
        output_idx += 1;
    }
    
    // Calculate remaining output values
    for i in period as usize..size as usize {
        let new_val = input.get(i)?;
        let old_val = input.get(i - period as usize)?;
        
        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;
        
        let mean = sum * scale;
        let mut s2s2 = (sum2 * scale) - (mean * mean);
        if s2s2 > 0.0 {
            s2s2 = s2s2.sqrt();
        }
        output[output_idx] = mul * s2s2;
        output_idx += 1;
    }
    
    // The assertion in the original C code is not needed in Rust as bounds are checked
    Some(0)
}
