use crate::*;
use std::assert;

pub fn ti_trix_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
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
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start_idx = ti_trix_start(Some(options))?;
    if size <= start_idx {
        return Some(0);
    }

    let start = (period * 3) - 2;
    assert!(start == ti_trix_start(Some(options)).unwrap());

    let per = 2.0 / (period as f64 + 1.0);
    let mut ema1 = input[0];
    let mut ema2 = 0.0;
    let mut ema3 = 0.0;

    // First loop: calculate EMAs
    for i in 1..start as usize {
        ema1 = (input[i] - ema1) * per + ema1;
        if i == (period - 1) as usize {
            ema2 = ema1;
        } else if i > (period - 1) as usize {
            ema2 = (ema1 - ema2) * per + ema2;
            if i == (period * 2 - 2) as usize {
                ema3 = ema2;
            } else if i > (period * 2 - 2) as usize {
                ema3 = (ema2 - ema3) * per + ema3;
            }
        }
    }

    // Second loop: calculate outputs
    let mut output_idx = 0;
    for i in start as usize..size as usize {
        ema1 = (input[i] - ema1) * per + ema1;
        ema2 = (ema1 - ema2) * per + ema2;
        let last = ema3;
        ema3 = (ema2 - ema3) * per + ema3;
        output[output_idx] = ((ema3 - last) / ema3) * 100.0;
        output_idx += 1;
    }

    assert!((output_idx as i32) == (size - ti_trix_start(Some(options)).unwrap()));

    Some(0)
}
