use crate::*;

pub fn ti_zlema_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| {
        (((opts[0] as i32) - 1) / 2) - 1
    })
}
pub fn ti_zlema(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Option<i32> {
    // Check for None in all Option parameters
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;
    
    // Get references to the input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];
    
    // Convert options
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }
    
    let lag = (period - 1) / 2;
    
    // Check size requirements
    let start = ti_zlema_start(Some(options))?;
    if size <= start {
        return Some(0);
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    let mut val = input[lag as usize - 1];
    let mut output_idx = 0;
    
    output[output_idx] = val;
    output_idx += 1;
    
    for i in lag..size {
        let c = input[i as usize];
        let l = input[(i - lag) as usize];
        val = ((c + (c - l) - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }
    
    // Assertion check (Rust's assert! macro)
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - outputs[0].as_ptr() as usize == 
            ((size - start) as usize) * std::mem::size_of::<f64>());
    
    Some(0)
}
