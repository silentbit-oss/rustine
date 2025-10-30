use crate::*;

pub fn ti_linreg_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}
pub fn helper_ti_linreg_1(
    output_idx_ref: &mut u32,
    size: i32,
    input: &[f64],
    period: i32,
    output: &mut [f64],
) {
    let mut output_idx = *output_idx_ref;
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;
    let p = 1.0 / period as f64;
    
    // First loop: calculate initial sums
    for i in 0..(period - 1) {
        let i_plus_1 = (i + 1) as f64;
        x += i_plus_1;
        x2 += i_plus_1 * i_plus_1;
        xy += input[i as usize] * i_plus_1;
        y += input[i as usize];
    }

    // Add period values
    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;
    let bd = 1.0 / ((period_f64 * x2) - (x * x));

    // Second loop: process remaining elements
    for i in (period - 1)..size {
        let i_usize = i as usize;
        xy += input[i_usize] * period_f64;
        y += input[i_usize];
        let b = ((period_f64 * xy) - (x * y)) * bd;

        // Equivalent to the do-while(0) block
        {
            let a = (y - (b * x)) * p;
            output[output_idx as usize] = a + (b * period_f64);
            output_idx += 1;
        }

        xy -= y;
        y -= input[(i - period + 1) as usize];
    }

    *output_idx_ref = output_idx;
}
pub fn ti_linreg(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    mut outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let outputs_ref = outputs.as_mut().unwrap();
    let output = &mut outputs_ref[0];

    if period < 1 {
        return Some(1);
    }

    let start = match ti_linreg_start(options) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let mut output_idx = 0;
    helper_ti_linreg_1(&mut output_idx, size, input, period, output);

    // Assert equivalent - we'll panic if the condition fails
    if (output[output_idx as usize] - outputs_ref[0][0]) != (size - start) as f64 {
        panic!("Assertion failed");
    }

    Some(0)
}
