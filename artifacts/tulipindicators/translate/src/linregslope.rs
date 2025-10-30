use crate::*;

pub fn ti_linregslope_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn helper_ti_linregslope_1(
    output_idx_ref: &mut u32,
    size: i32,
    input: &[f64],
    period: i32,
    output: &mut [f64],
) {
    let mut output_idx = *output_idx_ref as usize;
    let mut x = 0.0;
    let mut x2 = 0.0;
    let mut y = 0.0;
    let mut xy = 0.0;

    // Initialize sums for the first (period - 1) elements
    for i in 0..(period - 1) as usize {
        let weight = (i + 1) as f64;
        x += weight;
        x2 += weight * weight;
        xy += input[i] * weight;
        y += input[i];
    }

    // Add the period-th element
    let period_f64 = period as f64;
    x += period_f64;
    x2 += period_f64 * period_f64;

    // Precompute denominator
    let bd = 1.0 / ((period_f64 * x2) - (x * x));

    // Main computation loop
    for i in (period - 1) as usize..size as usize {
        xy += input[i] * period_f64;
        y += input[i];

        let b = ((period_f64 * xy) - (x * y)) * bd;
        
        // Store result and increment index
        output[output_idx] = b;
        output_idx += 1;

        // Adjust sums for next iteration
        xy -= y;
        y -= input[(i - (period as usize - 1))];
    }

    *output_idx_ref = output_idx as u32;
}
pub fn ti_linregslope(
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
    let mut output_idx = 0;

    if period < 1 {
        return Some(1);
    }

    let start = match ti_linregslope_start(options) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    helper_ti_linregslope_1(&mut output_idx, size, input, period, output);

    // Assert equivalent in Rust (debug only)
    debug_assert!((output[output_idx as usize..].as_ptr() as usize - output.as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - start) as usize);

    Some(0)
}
