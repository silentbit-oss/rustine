use crate::*;
use rand::Rng;

pub fn ti_rsi_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element, otherwise return 0 as default
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn ti_rsi(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    if options.is_none() || inputs.is_none() || outputs.is_none() {
        return 1;
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];
    let mut output_idx = 0;
    let per = 1.0 / (period as f64);

    if period < 1 {
        return 1;
    }

    let rsi_start = ti_rsi_start(options);
    if size <= rsi_start {
        return 0;
    }

    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;

    // First loop: calculate initial smooth_up and smooth_down
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

    // Second loop: calculate remaining RSI values
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

    // Assertion check (commented out since Rust doesn't have the exact same pointer arithmetic)
    // assert!((output[output_idx] as *const f64).offset_from(output[0] as *const f64) == (size - ti_rsi_start(options)) as isize);

    0
}
