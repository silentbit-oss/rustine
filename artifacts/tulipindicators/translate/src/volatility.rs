use crate::*;
use std::f64::consts::SQRT_2;

pub fn ti_volatility_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn ti_volatility(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    if options.is_none() || inputs.is_none() || outputs.is_none() {
        return 1;
    }

    let input = inputs.unwrap()[0];
    let output = &mut outputs.unwrap()[0];
    let mut output_idx = 0;
    let period = options.unwrap()[0] as i32;
    let scale = 1.0 / period as f64;
    let annual = 252.0f64.sqrt();

    if period < 1 {
        return 1;
    }

    let start = ti_volatility_start(options);
    if size <= start {
        return 0;
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // First window calculation
    for i in 1..=period {
        let c = (input[i as usize] / input[(i - 1) as usize]) - 1.0;
        sum += c;
        sum2 += c * c;
    }

    output[output_idx] = ((sum2 * scale) - (sum * scale).powi(2)).sqrt() * annual;
    output_idx += 1;

    // Rolling window calculation
    for i in (period + 1)..size {
        let c = (input[i as usize] / input[(i - 1) as usize]) - 1.0;
        sum += c;
        sum2 += c * c;

        let cp = (input[(i - period) as usize] / input[(i - period - 1) as usize]) - 1.0;
        sum -= cp;
        sum2 -= cp * cp;

        output[output_idx] = ((sum2 * scale) - (sum * scale).powi(2)).sqrt() * annual;
        output_idx += 1;
    }

    // Assertion check (commented out as it's debug-only in C)
    // assert!((output.as_ptr() as usize - outputs.unwrap()[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    0
}
