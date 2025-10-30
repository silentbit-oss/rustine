use crate::*;
use std::assert;

pub fn ti_tema_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;

    // Check if options has at least one element (to avoid panic on index 0)
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    Some((period - 1) * 3)
}

pub fn ti_tema(
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
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];

    if period < 1 {
        return Some(1);
    }

    let tema_start = match ti_tema_start(options) {
        Some(val) => val,
        None => return Some(1),
    };

    if size <= tema_start {
        return Some(0);
    }

    let per = 2.0 / (period as f64 + 1.0);
    let per1 = 1.0 - per;

    let mut ema = input[0];
    let mut ema2 = 0.0;
    let mut ema3 = 0.0;
    let mut output_idx = 0;

    for i in 0..size as usize {
        ema = (ema * per1) + (input[i] * per);

        if i == (period - 1) as usize {
            ema2 = ema;
        }

        if i >= (period - 1) as usize {
            ema2 = (ema2 * per1) + (ema * per);

            if i == ((period - 1) * 2) as usize {
                ema3 = ema2;
            }

            if i >= ((period - 1) * 2) as usize {
                ema3 = (ema3 * per1) + (ema2 * per);

                if i >= ((period - 1) * 3) as usize {
                    output[output_idx] = (3.0 * ema) - (3.0 * ema2) + ema3;
                    output_idx += 1;
                }
            }
        }
    }

    assert!((&output[output_idx] as *const f64 as usize - output.as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - tema_start) as usize);

    Some(0)
}
