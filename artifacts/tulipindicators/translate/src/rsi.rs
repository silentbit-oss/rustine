use crate::*;
use std::assert;

pub fn ti_rsi_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // and if the slice has at least one element
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32,
        _ => 0, // Default return value when options is None or empty
    }
}

pub fn ti_rsi(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Unwrap options safely
    let options = match options {
        Some(opts) => opts,
        None => return 1,
    };
    
    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    // Check if size is sufficient
    let start = ti_rsi_start(Some(options));
    if size <= start {
        return 0;
    }

    // Unwrap inputs and outputs safely
    let input = match inputs {
        Some(inp) => inp[0],
        None => return 1,
    };
    let output = match outputs {
        Some(out) => &mut out[0],
        None => return 1,
    };

    let per = 1.0 / (period as f64);
    let mut output_idx = 0;
    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;

    // Calculate initial smooth values
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
    output[output_idx] = 100.0 * (smooth_up / (smooth_up + smooth_down));
    output_idx += 1;

    // Calculate remaining values
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
        output[output_idx] = 100.0 * (smooth_up / (smooth_up + smooth_down));
        output_idx += 1;
    }

    // Verify output length
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - output.as_ptr() as usize
            == ((size - start) as usize * std::mem::size_of::<f64>()));

    0
}
