use crate::*;
use rand::Rng;

pub fn ti_rsi_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0,
    }
}

pub fn ti_rsi(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let mut outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_rsi_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let per = 1.0 / (period as f64);
    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;
    
    for i in 1..=period {
        let upward = if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        let downward = if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };
        smooth_up += upward;
        smooth_down += downward;
    }
    
    smooth_up /= period as f64;
    smooth_down /= period as f64;
    
    output[0] = 100.0 * (smooth_up / (smooth_up + smooth_down));
    
    for i in (period + 1)..size {
        let upward = if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        let downward = if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };
        
        smooth_up = ((upward - smooth_up) * per) + smooth_up;
        smooth_down = ((downward - smooth_down) * per) + smooth_down;
        
        output[(i - period) as usize] = 100.0 * (smooth_up / (smooth_up + smooth_down));
    }
    
    assert!((output.len() as i32) == (size - start));
    0
}
