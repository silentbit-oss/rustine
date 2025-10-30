use crate::*;
use std::convert::TryInto;

pub fn ti_linreg_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_linreg_start");
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}

pub fn ti_linreg(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_linreg");
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

    let start = match ti_linreg_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let mut output_idx: usize = 0;

    // Main calculation block
    {
        let mut x = 0.0;
        let mut x2 = 0.0;
        let mut y = 0.0;
        let mut xy = 0.0;
        let p = 1.0 / period as f64;

        // First loop (period - 1 iterations)
        for i in 0..(period - 1) as usize {
            let i_f64 = (i + 1) as f64;
            x += i_f64;
            x2 += i_f64 * i_f64;
            xy += input[i] * i_f64;
            y += input[i];
        }

        // Add the period term
        let period_f64 = period as f64;
        x += period_f64;
        x2 += period_f64 * period_f64;
        let bd = 1.0 / ((period_f64 * x2) - (x * x));

        // Second loop (from period-1 to size-1)
        for i in (period - 1) as usize..size as usize {
            xy += input[i] * period_f64;
            y += input[i];

            let b = ((period_f64 * xy) - (x * y)) * bd;
            let a = (y - (b * x)) * p;
            output[output_idx] = a + (b * period_f64);
            output_idx += 1;

            xy -= y;
            y -= input[(i - (period - 1) as usize)];
        }
    }

    // Assertion check (converted to debug assertion)
    debug_assert_eq!(
        output_idx,
        (size - start) as usize,
        "Output index mismatch"
    );

    Some(0)
}
