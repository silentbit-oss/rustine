use crate::*;
use rand::Rng;

pub fn ti_wma_start(options: Option<&[f64]>) -> Option<i32> {
    match options {
        Some(opts) if !opts.is_empty() => Some(opts[0] as i32 - 1),
        _ => None,
    }
}

pub fn ti_wma(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Check if inputs and outputs arrays have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    // Calculate start index using the dependency function
    let start = match ti_wma_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let weights = (period * (period + 1)) as f64 / 2.0;
    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    
    // First loop: process period - 1 elements
    for i in 0..(period - 1) as usize {
        if i >= input.len() {
            return 1; // Input array too small
        }
        weight_sum += input[i] * (i + 1) as f64;
        sum += input[i];
    }
    
    // Second loop: process from period - 1 to size
    let mut output_idx = 0;
    for i in (period - 1) as usize..size as usize {
        if i >= input.len() || output_idx >= output.len() {
            return 1; // Array bounds check
        }
        
        weight_sum += input[i] * period as f64;
        sum += input[i];
        
        output[output_idx] = weight_sum / weights;
        output_idx += 1;
        
        weight_sum -= sum;
        
        let remove_idx = i as i32 - period + 1;
        if remove_idx >= 0 && (remove_idx as usize) < input.len() {
            sum -= input[remove_idx as usize];
        }
    }
    
    // Verify the number of output elements matches expectation
    let expected_output_count = (size - start) as usize;
    assert!((output_idx) == expected_output_count, 
            "Output count mismatch: expected {}, got {}", expected_output_count, output_idx);
    
    0
}
