use crate::*;
use std::f64;

pub fn ti_cci_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_cci_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if options has at least one element (to avoid panic on index 0)
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    Some((period - 1) * 2)
}

pub fn ti_cci(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_cci");
    // Early return if any required input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Extract input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];

    // Parse options
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return Some(1);
    }

    let start = ti_cci_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let output = &mut outputs[0];
    let mut output_idx = 0;

    let mut sum = match ti_buffer_new(period) {
        Some(s) => s,
        None => return None,
    };

    for i in 0..size as usize {
        let today = (high[i] + low[i] + close[i]) * (1.0 / 3.0);

        // Push value to buffer
        {
            if sum.pushes >= sum.size {
                sum.sum -= sum.vals[sum.index as usize];
            }
            sum.sum += today;
            sum.vals[sum.index as usize] = today;
            sum.pushes += 1;
            sum.index = (sum.index + 1) % sum.size;
        }

        let avg = sum.sum * scale;

        if i >= (period * 2 - 2) as usize {
            let mut acc = 0.0;
            for j in 0..period as usize {
                acc += f64::abs(avg - sum.vals[j]);
            }

            let mut cci = acc * scale;
            cci *= 0.015;
            cci = (today - avg) / cci;
            output[output_idx] = cci;
            output_idx += 1;
        }
    }

    ti_buffer_free(*sum);
    Some(0)
}
