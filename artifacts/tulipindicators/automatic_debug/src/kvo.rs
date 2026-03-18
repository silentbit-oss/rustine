use crate::*;
use rand::Rng;

pub fn ti_kvo_start(options: Option<&f64>) -> i32 {
	println!("\n* ti_kvo_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}
pub fn ti_kvo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_kvo");
    // Check for None (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Extract input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];

    // Extract options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    // Validation checks
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }

    let start = ti_kvo_start(Some(&options[0]));
    if size <= start {
        return 0;
    }

    // Calculate periods
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);

    // Get output slice
    let output = &mut outputs[0];

    let mut output_idx = 0;
    let mut cm = 0.0;
    let mut prev_hlc = high[0] + low[0] + close[0];
    let mut trend = -1;
    let mut short_ema = 0.0;
    let mut long_ema = 0.0;

    for i in 1..size as usize {
        let hlc = high[i] + low[i] + close[i];
        let dm = high[i] - low[i];

        if hlc > prev_hlc && trend != 1 {
            trend = 1;
            cm = high[i - 1] - low[i - 1];
        } else if hlc < prev_hlc && trend != 0 {
            trend = 0;
            cm = high[i - 1] - low[i - 1];
        }

        cm += dm;
        let vf = volume[i] * f64::abs((dm / cm) * 2.0 - 1.0) * 100.0 * if trend == 1 { 1.0 } else { -1.0 };

        if i == 1 {
            short_ema = vf;
            long_ema = vf;
        } else {
            short_ema = (vf - short_ema) * short_per + short_ema;
            long_ema = (vf - long_ema) * long_per + long_ema;
        }

        output[output_idx] = short_ema - long_ema;
        output_idx += 1;
        prev_hlc = hlc;
    }

    // Assertion check (commented out as it's debug-only in C)
    // assert!((output.as_ptr().offset(output_idx as isize) as usize - outputs[0].as_ptr() as usize == (size - start) as usize);

    0
}
