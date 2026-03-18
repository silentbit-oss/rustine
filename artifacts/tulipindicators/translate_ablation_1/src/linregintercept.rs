use crate::*;
use rand::Rng;

pub fn ti_linregintercept_start(options: Option<&[f64]>) -> Option<i32> {
    match options {
        Some(opts) if !opts.is_empty() => Some(opts[0] as i32 - 1),
        _ => Option::None,
    }
}
pub fn ti_linregintercept(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
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
    
    // Calculate start index using the dependency function
    let start = match ti_linregintercept_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;
    let p = 1.0 / period as f64;
    
    // Pre-calculate the sum for the first period-1 elements
    for i in 0..(period - 1) as usize {
        let weight = (i + 1) as f64;
        x += weight;
        x2 += weight * weight;
        xy += input[i] * weight;
        y += input[i];
    }
    
    // Add the period-th element
    x += period as f64;
    x2 += (period * period) as f64;
    let bd = 1.0 / ((period as f64 * x2) - (x * x));
    
    let mut output_idx = 0;
    
    // Main calculation loop
    for i in (period - 1) as usize..size as usize {
        xy += input[i] * period as f64;
        y += input[i];
        
        let b = ((period as f64 * xy) - (x * y)) * bd;
        let a = (y - (b * x)) * p;
        
        output[output_idx] = a + (b * 1.0);
        output_idx += 1;
        
        xy -= y;
        if i >= period as usize {
            y -= input[i - period as usize + 1];
        }
    }
    
    // Verify the output length matches expectations
    assert!((output_idx as i32) == (size - start));
    
    0
}
