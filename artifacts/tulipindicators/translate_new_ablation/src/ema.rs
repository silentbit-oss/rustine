use crate::*;
use rand::Rng;

pub fn ti_ema_start(options: Option<&[f64]>) -> i32 {
    // The C function ignores the options parameter, so we do the same
    // The (void)options; cast in C is equivalent to ignoring the parameter in Rust
    let _ = options;
    0
}
pub fn ti_ema(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
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
    
    let start = ti_ema_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    let mut val = input[0];
    
    // Check if output slice has enough capacity
    if output.len() < (size - start) as usize {
        return 1;
    }
    
    output[0] = val;
    
    for i in 1..size as usize {
        if i >= input.len() {
            break;
        }
        val = ((input[i] - val) * per) + val;
        if (i as i32 - start) >= 0 {
            output[i as usize - start as usize] = val;
        }
    }
    
    // Rust's assert macro works similarly to C's
    assert!((output.len() as i32) == (size - start));
    
    0
}
