use crate::*;
use rand::Rng;

pub fn ti_trix_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;

    // Check if options has at least one element (to avoid panic on index 0)
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    Some(((period - 1) * 3) + 1)
}

pub fn ti_trix(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let options = options.unwrap();
    let output = &mut outputs.unwrap()[0];

    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    let start = match ti_trix_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let per = 2.0 / (period as f64 + 1.0);
    let mut ema1 = input[0];
    let mut ema2 = 0.0;
    let mut ema3 = 0.0;
    let mut output_idx = 0;

    for i in 1..start {
        ema1 = ((input[i as usize] - ema1) * per) + ema1;
        if i == (period - 1) {
            ema2 = ema1;
        } else if i > (period - 1) {
            ema2 = ((ema1 - ema2) * per) + ema2;
            if i == ((period * 2) - 2) {
                ema3 = ema2;
            } else if i > ((period * 2) - 2) {
                ema3 = ((ema2 - ema3) * per) + ema3;
            }
        }
    }

    for i in start..size {
        ema1 = ((input[i as usize] - ema1) * per) + ema1;
        ema2 = ((ema1 - ema2) * per) + ema2;
        let last = ema3;
        ema3 = ((ema2 - ema3) * per) + ema3;
        output[output_idx as usize] = ((ema3 - last) / ema3) * 100.0;
        output_idx += 1;
    }

    // Note: The assert in C is not directly translatable to Rust without unsafe,
    // but we can verify the length matches
    if (output_idx as i32) != (size - start) {
        return Some(1);
    }

    Some(0)
}
