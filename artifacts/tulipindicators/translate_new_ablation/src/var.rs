use crate::*;
use rand::Rng;

pub fn ti_var_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}

pub fn ti_var(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None values (equivalent to NULL checks in C)
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
    
    let start = match ti_var_start(Some(options)) {
        Some(val) => val,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let scale = 1.0 / period as f64;
    
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    
    // Initialize sum and sum2 for the first period elements
    for i in 0..period {
        let val = input[i as usize];
        sum += val;
        sum2 += val * val;
    }
    
    // Calculate first output value
    output[0] = (sum2 * scale) - ((sum * scale) * (sum * scale));
    
    // Process remaining elements using sliding window
    for i in period..size {
        let current_idx = i as usize;
        let prev_idx = (i - period) as usize;
        
        let new_val = input[current_idx];
        let old_val = input[prev_idx];
        
        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;
        
        let output_idx = (i - period + 1) as usize;
        output[output_idx] = (sum2 * scale) - ((sum * scale) * (sum * scale));
    }
    
    // Verify the number of output elements matches expectation
    let expected_output_count = (size - start) as usize;
    assert!(output.len() >= expected_output_count);
    
    0
}
