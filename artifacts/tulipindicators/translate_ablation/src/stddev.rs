use crate::*;
use std::f64::consts::SQRT_2;
use std::os::raw::c_double;
use std::os::raw::c_int;
pub extern "C" fn ti_stddev_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => 0, // Return 0 as default/fallback instead of panicking
    }
}

pub extern "C" fn ti_stddev(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for null pointers using Option
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Check if we have at least one input and output array
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_stddev_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let scale = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    
    // Calculate initial sum and sum of squares for the first period elements
    for i in 0..period as usize {
        if i >= input.len() {
            return 1;
        }
        let val = input[i];
        sum += val;
        sum2 += val * val;
    }
    
    // Calculate and output the first standard deviation
    if output.is_empty() {
        return 1;
    }
    
    let mut s2s2 = (sum2 * scale) - (sum * scale).powi(2);
    if s2s2 > 0.0 {
        s2s2 = libm::sqrt(s2s2);
    }
    output[0] = s2s2;
    
    // Process the remaining elements using a sliding window
    for i in period as usize..size as usize {
        if i >= input.len() {
            return 1;
        }
        
        // Add new element
        let new_val = input[i];
        sum += new_val;
        sum2 += new_val * new_val;
        
        // Remove old element
        let old_index = i - period as usize;
        if old_index >= input.len() {
            return 1;
        }
        let old_val = input[old_index];
        sum -= old_val;
        sum2 -= old_val * old_val;
        
        // Calculate standard deviation and output
        let output_index = i - period as usize + 1;
        if output_index >= output.len() {
            return 1;
        }
        let mut s2s2 = (sum2 * scale) - (sum * scale).powi(2);
        if s2s2 > 0.0 {
            s2s2 = libm::sqrt(s2s2);
        }
        output[output_index] = s2s2;
    }
    
    0
}
