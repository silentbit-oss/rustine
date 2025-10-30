use crate::*;
use std::f64;

pub fn ti_kama_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL check in C)
    // If options is None, return 0 as default (since C would dereference NULL causing UB)
    // Alternatively, could return Option<i32> if NULL case needs to be handled differently
    match options {
        Some(opts) => opts[0] as i32 - 1,
        None => 0,
    }
}

pub fn ti_kama(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for null inputs/outputs (handled by Option in Rust)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return Err(1),
    };
    let period = match options {
        Some(options) => options[0] as i32,
        None => return Err(1),
    };
    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return Err(1),
    };

    if period < 1 {
        return Err(1);
    }

    let start = ti_kama_start(options);
    if size <= start {
        return Ok(());
    }

    let short_per = 2.0 / (2.0 + 1.0);
    let long_per = 2.0 / (30.0 + 1.0);
    let mut sum = 0.0;
    let mut output_idx = 0;

    for i in 1..period {
        sum += f64::abs(input[i as usize] - input[(i - 1) as usize]);
    }

    let mut kama = input[(period - 1) as usize];
    output[output_idx] = kama;
    output_idx += 1;

    for i in period..size {
        sum += f64::abs(input[i as usize] - input[(i - 1) as usize]);
        if i > period {
            sum -= f64::abs(input[(i - period) as usize] - input[(i - period - 1) as usize]);
        }

        let er = if sum != 0.0 {
            f64::abs(input[i as usize] - input[(i - period) as usize]) / sum
        } else {
            1.0
        };

        let sc = f64::powf(er * (short_per - long_per) + long_per, 2.0);
        kama += sc * (input[i as usize] - kama);
        output[output_idx] = kama;
        output_idx += 1;
    }

    // Assertion check (Rust doesn't have exact pointer arithmetic like C, so we approximate)
    assert!((output_idx as i32) == (size - start));
    Ok(())
}
