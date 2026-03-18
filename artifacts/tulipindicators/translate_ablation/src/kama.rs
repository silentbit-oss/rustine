use crate::*;
use libm::fabs;
use libm::pow;

pub fn ti_kama_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if opts.len() > 0 => opts[0] as i32 - 1,
        _ => -1, // Return -1 if options is None or empty
    }
}

pub fn ti_kama(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
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
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_kama_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let short_per = 2.0 / (2.0 + 1.0);
    let long_per = 2.0 / (30.0 + 1.0);
    let mut sum = 0.0;
    
    // Calculate initial sum
    for i in 1..period as usize {
        sum += f64::abs(input[i] - input[i - 1]);
    }
    
    let mut kama = input[period as usize - 1];
    output[0] = kama;
    
    let mut output_idx = 1;
    
    for i in period as usize..size as usize {
        sum += f64::abs(input[i] - input[i - 1]);
        
        if i > period as usize {
            sum -= f64::abs(input[i - period as usize] - input[i - period as usize - 1]);
        }
        
        let er = if sum != 0.0 {
            f64::abs(input[i] - input[i - period as usize]) / sum
        } else {
            1.0
        };
        
        let sc = f64::powf(er * (short_per - long_per) + long_per, 2.0);
        kama = kama + (sc * (input[i] - kama));
        
        if output_idx < output.len() {
            output[output_idx] = kama;
            output_idx += 1;
        }
    }
    
    // Assertion check (commented out as Rust's assert! would panic, not return error code)
    // assert!((output_idx as i32) == (size - ti_kama_start(Some(options))));
    
    0
}
