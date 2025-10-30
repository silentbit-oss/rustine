use crate::*;
use rand::Rng;

pub fn ti_zlema_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some((((options[0] as i32) - 1) / 2) - 1)
}
pub fn ti_zlema(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let mut outputs = outputs.unwrap();
    
    // Check if inputs and outputs arrays have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let input = inputs[0];
    let period = options[0] as i32;
    let lag = (period - 1) / 2;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    // Check if size is sufficient for the operation
    let start = match ti_zlema_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    
    // Check if we can safely access input[lag - 1]
    if lag - 1 < 0 || (lag - 1) as usize >= input.len() {
        return 1;
    }
    
    let mut val = input[(lag - 1) as usize];
    
    // Check if output has enough space
    if output.is_empty() {
        return 1;
    }
    
    output[0] = val;
    
    let mut output_idx = 1;
    
    for i in lag..size {
        let i_usize = i as usize;
        
        // Check bounds for input access
        if i_usize >= input.len() || (i - lag) as usize >= input.len() {
            return 1;
        }
        
        let c = input[i_usize];
        let l = input[(i - lag) as usize];
        
        val = ((c + (c - l)) - val) * per + val;
        
        // Check bounds for output access
        if output_idx >= output.len() {
            return 1;
        }
        
        output[output_idx] = val;
        output_idx += 1;
    }
    
    // Verify the expected output length matches actual
    let expected_len = (size - start) as usize;
    assert!(output_idx == expected_len, "Output length mismatch: expected {}, got {}", expected_len, output_idx);
    
    0
}
