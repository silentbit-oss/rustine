use crate::*;

pub fn ti_fosc_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // and if the slice has at least one element
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Default return value when options is None or empty
    }
}
pub fn helper_ti_fosc_1(
    output_idx_ref: &mut u32,
    size: usize,
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
    let mut tsf = 0.0;

    for i in 0..(period - 1) as usize {
        let i_plus_1 = (i + 1) as f64;
        x += i_plus_1;
        x2 += i_plus_1 * i_plus_1;
        xy += input[i] * i_plus_1;
        y += input[i];
    }

    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;
    let bd = 1.0 / ((period_f64 * x2) - (x * x));

    for i in (period - 1) as usize..size {
        xy += input[i] * period_f64;
        y += input[i];
        let b = ((period_f64 * xy) - (x * y)) * bd;

        {
            let a = (y - (b * x)) * p;
            if i >= period as usize {
                output[output_idx as usize] = (100.0 * (input[i] - tsf)) / input[i];
                output_idx += 1;
            }
            tsf = a + (b * (period_f64 + 1.0));
        }

        xy -= y;
        y -= input[(i - (period as usize)) + 1];
    }

    *output_idx_ref = output_idx;
}
pub fn ti_fosc(
    size: usize,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> Result<(), i32> {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 1 {
        return Err(1);
    }

    let start = ti_fosc_start(Some(options));
    if size <= start as usize {
        return Ok(());
    }

    helper_ti_fosc_1(&mut output_idx, size, input, period, output);

    debug_assert!(
        (output[output_idx as usize] - outputs[0][0]) == (size as f64 - start as f64)
    );

    Ok(())
}
