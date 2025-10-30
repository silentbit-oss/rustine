use crate::*;

pub fn ti_qstick_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if opts.len() > 0 => opts[0] as i32 - 1,
        _ => -1,
    }
}
pub fn ti_qstick(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Check if input arrays exist
    if inputs.len() < 2 || outputs.is_empty() {
        return 1;
    }
    
    let open = inputs[0];
    let close = inputs[1];
    let output = &mut outputs[0];
    
    // Check if arrays have sufficient length
    if open.len() < size as usize || close.len() < size as usize || output.len() < size as usize {
        return 1;
    }
    
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start_index = ti_qstick_start(Some(options));
    if size <= start_index {
        return 0;
    }
    
    let mut sum = 0.0;
    
    // First loop: calculate initial sum
    for i in 0..period as usize {
        sum += close[i] - open[i];
    }
    
    // Write first output value
    output[0] = sum * scale;
    
    // Second loop: sliding window calculation
    for i in period as usize..size as usize {
        sum += close[i] - open[i];
        sum -= close[i - period as usize] - open[i - period as usize];
        output[i - period as usize + 1] = sum * scale;
    }
    
    // Verify output length matches expectation
    let expected_output_count = (size - start_index) as usize;
    assert!((output[..expected_output_count].len()) == expected_output_count);
    
    0
}
