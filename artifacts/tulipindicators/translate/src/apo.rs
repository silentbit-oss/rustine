use crate::*;
use std::assert;

pub fn ti_apo_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}

pub fn ti_apo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let apo = &mut outputs[0];

    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    // Validation checks
    if short_period < 1 || long_period < 2 || long_period < short_period {
        return 1;
    }

    let start = ti_apo_start(Some(options));
    if size <= start {
        return 0;
    }

    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);

    let mut short_ema = input[0];
    let mut long_ema = input[0];
    let mut apo_idx = 0;

    for i in 1..size as usize {
        short_ema = (input[i] - short_ema) * short_per + short_ema;
        long_ema = (input[i] - long_ema) * long_per + long_ema;
        let out = short_ema - long_ema;
        apo[apo_idx] = out;
        apo_idx += 1;
    }

    // Assertion check
    assert!((apo.as_ptr() as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - start) as usize);

    0
}
