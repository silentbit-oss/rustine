use crate::*;

pub fn ti_mom_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0,
    }
}
pub fn ti_mom(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_mom_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[i as usize] - input[(i - period) as usize];
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
