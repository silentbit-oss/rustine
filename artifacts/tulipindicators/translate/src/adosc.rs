use crate::*;
use std::assert;

pub fn ti_adosc_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None or if the slice is too short (less than 2 elements)
    match options {
        Some(opts) if opts.len() >= 2 => (opts[1] as i32) - 1,
        _ => -1, // Return -1 as an error indicator (common C convention)
    }
}
pub fn helper_ti_adosc_1(
    output_idx_ref: &mut u32,
    sum_ref: &mut f64,
    short_ema_ref: &mut f64,
    long_ema_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    volume: &[f64],
    start: i32,
    short_per: f64,
    long_per: f64,
    output: &mut [f64],
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut sum = *sum_ref;
    let mut short_ema = *short_ema_ref;
    let mut long_ema = *long_ema_ref;
    
    let hl = high[i] - low[i];
    if hl != 0.0 {
        sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
    }
    
    if i == 0 {
        short_ema = sum;
        long_ema = sum;
    } else {
        short_ema = ((sum - short_ema) * short_per) + short_ema;
        long_ema = ((sum - long_ema) * long_per) + long_ema;
    }
    
    if i >= start as usize {
        output[output_idx as usize] = short_ema - long_ema;
        output_idx += 1;
    }
    
    *output_idx_ref = output_idx;
    *sum_ref = sum;
    *short_ema_ref = short_ema;
    *long_ema_ref = long_ema;
}

pub fn ti_adosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Early return if any required input is None
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };

    // Unwrap inputs
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];

    // Extract periods from options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let start = long_period - 1;

    // Validate periods
    if short_period < 1 || long_period < short_period {
        return 1;
    }

    // Check size
    if size <= ti_adosc_start(Some(options)) {
        return 0;
    }

    // Calculate periods
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);

    // Get output slice
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let mut sum = 0.0;
    let mut short_ema = 0.0;
    let mut long_ema = 0.0;

    // Process each element
    for i in 0..size as usize {
        helper_ti_adosc_1(
            &mut output_idx,
            &mut sum,
            &mut short_ema,
            &mut long_ema,
            high,
            low,
            close,
            volume,
            start,
            short_per,
            long_per,
            output,
            i,
        );
    }

    // Verify output length
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - ti_adosc_start(Some(options))) as f64);

    0
}
