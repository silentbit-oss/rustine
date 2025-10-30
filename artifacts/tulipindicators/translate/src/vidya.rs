use crate::*;
use libm::sqrt;
use std::assert;

pub fn ti_vidya_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.len() > 1 {
            Some(opts[1] as i32 - 2)
        } else {
            None
        }
    })
}

pub fn helper_ti_vidya_1(
    output_idx_ref: &mut u32,
    short_sum_ref: &mut f64,
    short_sum2_ref: &mut f64,
    long_sum_ref: &mut f64,
    long_sum2_ref: &mut f64,
    val_ref: &mut f64,
    input: &[f64],
    short_period: i32,
    long_period: i32,
    alpha: f64,
    output: &mut [f64],
    short_div: f64,
    long_div: f64,
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut short_sum = *short_sum_ref;
    let mut short_sum2 = *short_sum2_ref;
    let mut long_sum = *long_sum_ref;
    let mut long_sum2 = *long_sum2_ref;
    let mut val = *val_ref;

    let i_long_period = i - long_period as usize;
    let i_short_period = i - short_period as usize;

    long_sum += input[i];
    long_sum2 += input[i] * input[i];
    short_sum += input[i];
    short_sum2 += input[i] * input[i];
    long_sum -= input[i_long_period];
    long_sum2 -= input[i_long_period] * input[i_long_period];
    short_sum -= input[i_short_period];
    short_sum2 -= input[i_short_period] * input[i_short_period];

    {
        let short_stddev = sqrt((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
        let long_stddev = sqrt((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[i] - val) * k) + val;
        output[output_idx as usize] = val;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *short_sum_ref = short_sum;
    *short_sum2_ref = short_sum2;
    *long_sum_ref = long_sum;
    *long_sum2_ref = long_sum2;
    *val_ref = val;
}
pub fn ti_vidya(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any required input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices from inputs and outputs
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
    if short_period < 1 || long_period < short_period || long_period < 2 || alpha < 0.0 || alpha > 1.0 {
        return Some(1);
    }

    // Check if size is sufficient
    let start = ti_vidya_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    // Calculate divisors
    let short_div = 1.0 / short_period as f64;
    let long_div = 1.0 / long_period as f64;

    let mut output_idx = 0u32;  // Changed from usize to u32
    let mut short_sum = 0.0;
    let mut short_sum2 = 0.0;
    let mut long_sum = 0.0;
    let mut long_sum2 = 0.0;

    // Initialize sums
    for i in 0..long_period as usize {
        if i >= input.len() {
            break;
        }
        long_sum += input[i];
        long_sum2 += input[i] * input[i];
        if i >= (long_period - short_period) as usize {
            short_sum += input[i];
            short_sum2 += input[i] * input[i];
        }
    }

    // First output value
    let mut val = if long_period >= 2 {
        input[(long_period - 2) as usize]
    } else {
        0.0
    };
    output[output_idx as usize] = val;
    output_idx += 1;

    // Second output value if possible
    if (long_period - 1) < size {
        let short_mean = short_sum * short_div;
        let long_mean = long_sum * long_div;
        let short_stddev = sqrt((short_sum2 * short_div) - (short_mean * short_mean));
        let long_stddev = sqrt((long_sum2 * long_div) - (long_mean * long_mean));
        let mut k = short_stddev / long_stddev;
        if k.is_nan() {
            k = 0.0;
        }
        k *= alpha;
        val = ((input[(long_period - 1) as usize] - val) * k) + val;
        output[output_idx as usize] = val;
        output_idx += 1;
    }

    // Process remaining values
    for i in long_period as usize..size as usize {
        if i >= input.len() {
            break;
        }
        helper_ti_vidya_1(
            &mut output_idx,
            &mut short_sum,
            &mut short_sum2,
            &mut long_sum,
            &mut long_sum2,
            &mut val,
            input,
            short_period,
            long_period,
            alpha,
            output,
            short_div,
            long_div,
            i,
        );
    }

    // Assert output length matches expected
    assert!((output_idx as i32) == (size - start));

    Some(0)
}
