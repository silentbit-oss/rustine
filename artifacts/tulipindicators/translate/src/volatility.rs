use crate::*;
use std::f64::consts::SQRT_2;
use rand::Rng;

pub fn ti_volatility_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| opts.first().map(|&val| val as i32))
}

pub fn ti_volatility(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let output = &mut outputs.unwrap()[0];
    let mut output_idx = 0;
    let period = options.unwrap()[0] as i32;
    let scale = 1.0 / period as f64;
    let annual = 252.0_f64.sqrt();

    if period < 1 {
        return Some(1);
    }

    let volatility_start = match ti_volatility_start(options) {
        Some(val) => val,
        None => return Some(1),
    };

    if size <= volatility_start {
        return Some(0);
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

    // Assert equivalent - we'll just check the condition and return error if false
    if (output_idx as i32) != (size - volatility_start) {
        return Some(1);
    }

    Some(0)
}
