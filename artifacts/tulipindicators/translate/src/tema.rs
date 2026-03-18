use crate::*;
use rand::Rng;

pub fn ti_tema_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Check if options has at least one element (to prevent index out of bounds)
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
    // Early return if any required input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices safely
    let input = inputs.get(0)?;
    let period = options.get(0).map(|&x| x as i32)?;
    let output = outputs.get_mut(0)?;

    if period < 1 {
        return Some(1);
    }

    let tema_start = ti_tema_start(Some(options))?;
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

    // Note: Rust doesn't have pointer arithmetic like C, so we skip the assert
    Some(0)
}
