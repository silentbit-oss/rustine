use crate::*;

pub fn ti_dpo_start(options: Option<&[f64]>) -> Option<i32> {
    match options {
        Some(opts) if !opts.is_empty() => Some(opts[0] as i32 - 1),
        _ => None,
    }
}
pub fn ti_dpo(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let back = (period / 2) + 1;
    let output = &mut outputs[0];
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_dpo_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    for i in 0..period as usize {
        sum += input[i];
    }
    
    let mut output_idx = 0;
    output[output_idx] = input[(period - 1) as usize - back as usize] - (sum * scale);
    output_idx += 1;
    
    for i in period as usize..size as usize {
        sum += input[i];
        sum -= input[i - period as usize];
        output[output_idx] = input[i - back as usize] - (sum * scale);
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
