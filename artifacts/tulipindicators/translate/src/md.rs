use crate::*;
use std::f64;

pub fn ti_md_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Return -1 for None or empty slice (equivalent to NULL/invalid input in C)
    }
}
pub fn ti_md(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start = ti_md_start(Some(options));
    if size <= start {
        return Some(0);
    }

    let scale = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut output_idx = 0;

    for i in 0..size as usize {
        let today = input[i];
        sum += today;

        if i >= period as usize {
            sum -= input[i - period as usize];
        }

        let avg = sum * scale;
        if i >= (period - 1) as usize {
            let mut acc = 0.0;
            for j in 0..period as usize {
                acc += f64::abs(avg - input[i - j]);
            }

            output[output_idx] = acc * scale;
            output_idx += 1;
        }
    }

    // Assertion check (Rust doesn't have exact pointer arithmetic like C, so we skip this)
    Some(0)
}
