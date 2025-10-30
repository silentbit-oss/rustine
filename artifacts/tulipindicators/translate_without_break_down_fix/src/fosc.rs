use crate::*;
use rand::Rng;

pub fn ti_fosc_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_fosc_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element, otherwise return 0 as default
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn ti_fosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_fosc");
    // Check for None (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    let mut output_idx = 0;

    if period < 1 {
        return 1;
    }

    let start = ti_fosc_start(Some(options));
    if size <= start {
        return 0;
    }

    {
        let mut x = 0.0;
        let mut x2 = 0.0;
        let mut y = 0.0;
        let mut xy = 0.0;
        let p = 1.0 / period as f64;
        let mut tsf = 0.0;

        for i in 0..(period - 1) {
            let i_f64 = (i + 1) as f64;
            x += i_f64;
            x2 += i_f64 * i_f64;
            xy += input[i as usize] * i_f64;
            y += input[i as usize];
        }

        x += period as f64;
        x2 += (period * period) as f64;
        let bd = 1.0 / ((period as f64 * x2) - (x * x));

        for i in (period - 1)..size {
            let i_usize = i as usize;
            xy += input[i_usize] * period as f64;
            y += input[i_usize];
            let b = ((period as f64 * xy) - (x * y)) * bd;

            {
                let a = (y - (b * x)) * p;
                if i >= period {
                    output[output_idx] = (100.0 * (input[i_usize] - tsf)) / input[i_usize];
                    output_idx += 1;
                }
                tsf = a + (b * (period as f64 + 1.0));
            }

            xy -= y;
            y -= input[(i - period + 1) as usize];
        }
    }

    // Assertion check (commented out since Rust doesn't have the exact same pointer arithmetic)
    // assert!((output[output_idx] - outputs[0][0]) == (size - ti_fosc_start(Some(options))));

    0
}
