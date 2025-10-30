use crate::*;

pub fn ti_rocr_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 if options is None or empty
    }
}
pub fn ti_rocr(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_rocr_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in period as usize..size as usize {
        output[output_idx] = input[i] / input[i - period as usize];
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
