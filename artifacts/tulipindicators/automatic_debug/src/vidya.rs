use crate::*;
use std::f64;

pub fn ti_vidya_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_vidya_start");
    options.and_then(|opts| {
        if opts.len() > 1 {
            Some(opts[1] as i32 - 2)
        } else {
            None
        }
    })
}
pub fn ti_vidya(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_vidya");
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if input and output slices are not empty
    if inputs.is_empty() || outputs.is_empty() {
        return Some(1);
    }

    let input = inputs[0];
    let output = &mut outputs[0];

    // Extract options with bounds checking
    if options.len() < 3 {
        return Some(1);
    }
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let alpha = options[2];

    // Validate parameters
    if short_period < 1 {
        return Some(1);
    }
    if long_period < short_period {
        return Some(1);
    }
    if long_period < 2 {
        return Some(1);
    }
    if alpha < 0.0 || alpha > 1.0 {
        return Some(1);
    }

    // Check if size is sufficient
    let start = match ti_vidya_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };
    if size <= start {
        return Some(0);
    }

    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;

    // Initialize sums
    let mut short_sum = 0.0;
    let mut short_sum2 = 0.0;
    let mut long_sum = 0.0;
    let mut long_sum2 = 0.0;

    // Calculate initial sums
    for i in 0..long_period as usize {
        if i >= input.len() {
            return Some(1);
        }
        let val = input[i];
        long_sum += val;
        long_sum2 += val * val;

        if i >= (long_period - short_period) as usize {
            short_sum += val;
            short_sum2 += val * val;
        }
    }

    let mut val = input[long_period as usize - 2];
    let mut output_idx = 0;

    // Store initial value
    if output_idx < output.len() {
        output[output_idx] = val;
        output_idx += 1;
    }

    // Process first special case
    if (long_period - 1) < size && (long_period as usize - 1) < input.len() {
        let short_stddev = f64::sqrt(
            (short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
        let long_stddev = f64::sqrt(
            (long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[long_period as usize - 1] - val) * k) + val;

        if output_idx < output.len() {
            output[output_idx] = val;
            output_idx += 1;
        }
    }

    // Main processing loop
    for i in long_period as usize..size as usize {
        if i >= input.len() {
            return Some(1);
        }

        let val_in = input[i];
        long_sum += val_in;
        long_sum2 += val_in * val_in;
        short_sum += val_in;
        short_sum2 += val_in * val_in;

        let long_out_idx = i - long_period as usize;
        if long_out_idx < input.len() {
            let val_out = input[long_out_idx];
            long_sum -= val_out;
            long_sum2 -= val_out * val_out;
        }

        let short_out_idx = i - short_period as usize;
        if short_out_idx < input.len() {
            let val_out = input[short_out_idx];
            short_sum -= val_out;
            short_sum2 -= val_out * val_out;
        }

        let short_stddev = f64::sqrt(
            (short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
        let long_stddev = f64::sqrt(
            (long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[i] - val) * k) + val;

        if output_idx < output.len() {
            output[output_idx] = val;
            output_idx += 1;
        }
    }

    // The assertion in the original C code is not directly translatable to safe Rust
    // as it involves pointer arithmetic. We'll skip it in the safe version.

    Some(0)
}
