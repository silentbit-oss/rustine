use crate::*;
use rand::Rng;

pub fn ti_tema_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    
    if options.is_empty() {
        return None;
    }
    
    let period = options[0] as i32;
    Some((period - 1) * 3)
}

pub fn ti_tema(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None values (equivalent to NULL checks in C)
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
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_tema_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    let per1 = 1.0 - per;
    let mut ema = input[0];
    let mut ema2 = 0.0;
    let mut ema3 = 0.0;
    
    let mut output_idx = 0;
    
    for i in 0..size as usize {
        ema = (ema * per1) + (input[i] * per);
        
        if i == (period - 1) as usize {
            ema2 = ema;
        }
        
        if i >= (period - 1) as usize {
            ema2 = (ema2 * per1) + (ema * per);
            
            if i == ((period - 1) * 2) as usize {
                ema3 = ema2;
            }
            
            if i >= ((period - 1) * 2) as usize {
                ema3 = (ema3 * per1) + (ema2 * per);
                
                if i >= ((period - 1) * 3) as usize {
                    output[output_idx] = (3.0 * ema) - (3.0 * ema2) + ema3;
                    output_idx += 1;
                }
            }
        }
    }
    
    let expected_outputs = size - start;
    assert!(output_idx as i32 == expected_outputs);
    0
}
