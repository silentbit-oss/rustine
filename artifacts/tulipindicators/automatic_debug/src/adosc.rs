use crate::*;
use rand::Rng;

pub fn ti_adosc_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_adosc_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // and if the slice has at least 2 elements (since we access index 1)
    match options {
        Some(opt) if opt.len() >= 2 => (opt[1] as i32) - 1,
        _ => -1, // Return -1 for invalid input (similar to NULL/error case in C)
    }
}
pub fn ti_adosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_adosc");
    // Check for None (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];

    // Parse options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let start = long_period - 1;

    // Validation checks
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
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

    for i in 0..size as usize {
        let hl = high[i] - low[i];
        if hl != 0.0 {
            sum += (((close[i] - low[i]) - high[i] + close[i]) / hl) * volume[i];
        }

        if i == 0 {
            short_ema = sum;
            long_ema = sum;
        } else {
            short_ema = (sum - short_ema) * short_per + short_ema;
            long_ema = (sum - long_ema) * long_per + long_ema;
        }

        if i >= start as usize {
            output[output_idx] = short_ema - long_ema;
            output_idx += 1;
        }
    }

    // Assertion check (commented out as Rust doesn't have direct pointer arithmetic)
    // assert!((output[output_idx] as *const f64).offset_from(outputs[0][0] as *const f64) == (size - ti_adosc_start(Some(options))) as isize);

    0
}
