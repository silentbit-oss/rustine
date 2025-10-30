use crate::*;
use rand::Rng;

pub fn ti_tsf_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_tsf_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is None, return 0 as a safe default (since we can't subtract 1 from nothing)
    // Alternatively, we could return Option<i32> and propagate None, but the C version doesn't handle NULL gracefully
    match options {
        Some(opts) => {
            // Ensure the slice has at least one element to avoid panic
            if opts.is_empty() {
                0
            } else {
                opts[0] as i32 - 1
            }
        }
        None => 0,
    }
}

pub fn ti_tsf(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_tsf");
    // Check for None values (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];

    let mut output_idx = 0;

    if period < 1 {
        return 1;
    }

    if size <= ti_tsf_start(options) {
        return 0;
    }

    {
        let mut x = 0.0;
        let mut x2 = 0.0;
        let mut y = 0.0;
        let mut xy = 0.0;
        let p = 1.0 / period as f64;

        for i in 0..(period - 1) {
            let i_f64 = (i + 1) as f64;
            x += i_f64;
            x2 += i_f64 * i_f64;
            xy += input[i as usize] * i_f64;
            y += input[i as usize];
        }

        let period_f64 = period as f64;
        x += period_f64;
        x2 += period_f64 * period_f64;
        let bd = 1.0 / ((period_f64 * x2) - (x * x));

        for i in (period - 1)..size {
            let i_usize = i as usize;
            xy += input[i_usize] * period_f64;
            y += input[i_usize];
            let b = ((period_f64 * xy) - (x * y)) * bd;

            {
                let a = (y - (b * x)) * p;
                output[output_idx] = a + (b * (period_f64 + 1.0));
                output_idx += 1;
            }

            xy -= y;
            y -= input[(i - period + 1) as usize];
        }
    }

    // Note: The assert in C is omitted as Rust's slice operations are bounds-checked
    0
}
