use crate::*;
use std::assert;

pub fn ti_cmo_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element, otherwise return 0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}
pub fn ti_cmo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Unwrap options safely
    let options = match options {
        Some(opts) => opts,
        None => return 1,
    };
    
    let period = options[0] as i32;
    if period < 1 {
        return 1;
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

    if size <= ti_cmo_start(Some(options)) {
        return 0;
    }

    let mut output_idx = 0;
    let mut up_sum = 0.0;
    let mut down_sum = 0.0;

    // Initial period calculation
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

    assert!(
        (output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - output.as_ptr() as usize
            == (size - ti_cmo_start(Some(options))) as usize * std::mem::size_of::<f64>()
    );

    0
}
