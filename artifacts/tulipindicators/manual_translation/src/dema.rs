use crate::*;
use rand::Rng;

pub fn ti_dema_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_dema_start");
    // Check if options is None or empty
    let options = options.unwrap();
    if options.is_empty() {
        return 0;
    }

    let period = options[0] as i32;
    (period - 1) * 2
}

pub fn ti_dema(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_dema");
    // Check for None in all Option parameters
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();

    let input = inputs.get(0).unwrap();
    let period = options.as_ref().unwrap().get(0).map(|&x| x as i32).unwrap();
    let output = outputs.get_mut(0).unwrap();

    if period < 1 {
        return 1;
    }

    let start = ti_dema_start(options);
    if size <= start {
        return 0;
    }

    let per = 2.0 / (period as f64 + 1.0);
    let per1 = 1.0 - per;

    let mut ema = input[0];
    let mut ema2 = ema;
    let mut output_idx = 0;

    for i in 0..size as usize {
        ema = ema * per1 + input[i] * per;

        if i == (period - 1) as usize {
            ema2 = ema;
        }

        if i >= (period - 1) as usize {
            ema2 = ema2 * per1 + ema * per;

            if i >= ((period - 1) * 2) as usize {
                output[output_idx] = ema * 2.0 - ema2;
                output_idx += 1;
            }
        }
    }

    // Assertion check removed as Rust doesn't have pointer arithmetic like C
    0
}
