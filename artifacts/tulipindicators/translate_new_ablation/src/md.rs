use crate::*;
use std::f64;

pub fn ti_md_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_md(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_md_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    let mut output_idx = 0;
    
    for i in 0..size as usize {
        let today = input[i];
        sum += today;
        
        if i >= period as usize {
            sum -= input[i - period as usize];
        }
        
        let avg = sum * scale;
        
        if i >= (period - 1) as usize {
            let mut acc = 0.0;
            
            for j in 0..period as usize {
                acc += f64::abs(avg - input[i - j]);
            }
            
            output[output_idx] = acc * scale;
            output_idx += 1;
        }
    }
    
    // Assert equivalent - check if the number of output values matches expected
    let expected_output_count = (size - start) as usize;
    assert!(output_idx == expected_output_count, 
            "Output count mismatch: expected {}, got {}", expected_output_count, output_idx);
    
    0
}
