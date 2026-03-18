use crate::*;
use rand::Rng;

pub fn ti_cmo_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_cmo_start");
    // Check if options is None (equivalent to NULL check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn ti_cmo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_cmo");
    // Check for None inputs (equivalent to NULL checks in C)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return 1,
    };
    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return 1,
    };

    let period = match options {
        Some(opts) => opts[0] as i32,
        None => return 1,
    };

    if period < 1 {
        return 1;
    }

    let start = ti_cmo_start(options);
    if size <= start {
        return 0;
    }

    let mut up_sum = 0.0;
    let mut down_sum = 0.0;
    let mut output_idx = 0;

    // First window calculation
    for i in 1..=period {
        up_sum += if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        down_sum += if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };
    }

    output[output_idx] = (100.0 * (up_sum - down_sum)) / (up_sum + down_sum);
    output_idx += 1;

    // Rolling window calculation
    for i in (period + 1)..size {
        let prev_window = i - period;
        up_sum -= if input[prev_window as usize] > input[(prev_window - 1) as usize] {
            input[prev_window as usize] - input[(prev_window - 1) as usize]
        } else {
            0.0
        };
        down_sum -= if input[prev_window as usize] < input[(prev_window - 1) as usize] {
            input[(prev_window - 1) as usize] - input[prev_window as usize]
        } else {
            0.0
        };

        up_sum += if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        down_sum += if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };

        output[output_idx] = (100.0 * (up_sum - down_sum)) / (up_sum + down_sum);
        output_idx += 1;
    }

    // The assertion in the original C code is not needed in Rust as we're using safe slices
    0
}
