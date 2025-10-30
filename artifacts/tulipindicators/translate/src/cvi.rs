use crate::*;
use std::assert;

pub fn ti_cvi_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    let n = options[0] as i32;
    Some((n * 2) - 1)
}

pub fn ti_cvi(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Extract high and low from inputs
    let high = inputs[0];
    let low = inputs[1];

    // Extract period from options
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Get output slice
    let output = &mut outputs[0];

    // Check if size is sufficient
    let start = ti_cvi_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let per = 2.0 / (period as f64 + 1.0);
    let mut lag = ti_buffer_new(period)?;
    let mut val = high[0] - low[0];
    let mut output_idx = 0;

    // First loop
    for i in 1..(period * 2 - 1) as usize {
        val = ((high[i] - low[i] - val) * per) + val;
        {
            lag.vals[lag.index as usize] = val;
            lag.index += 1;
            if lag.index >= lag.size {
                lag.index = 0;
            }
        }
    }

    // Second loop
    for i in (period * 2 - 1) as usize..size as usize {
        val = ((high[i] - low[i] - val) * per) + val;
        let old = lag.vals[lag.index as usize];
        output[output_idx] = 100.0 * (val - old) / old;
        output_idx += 1;
        {
            lag.vals[lag.index as usize] = val;
            lag.index += 1;
            if lag.index >= lag.size {
                lag.index = 0;
            }
        }
    }

    ti_buffer_free(*lag);

    // Assertion check
    assert!((output[output_idx] - outputs[0][0]) == (size - start) as f64);

    Some(0)
}
