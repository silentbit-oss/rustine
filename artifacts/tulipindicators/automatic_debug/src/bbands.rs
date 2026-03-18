use crate::*;
use std::f64::consts::SQRT_2;

pub fn ti_bbands_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_bbands_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C, converting to i32
    Some(options[0] as i32 - 1)
}
pub fn ti_bbands(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_bbands");
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if we have enough inputs and outputs
    if inputs.len() < 1 || outputs.len() < 3 {
        return Some(1);
    }

    let input = inputs[0];
    // Split the outputs into three parts to get mutable references safely
    let (lower_slice, remaining) = outputs.split_at_mut(1);
    let (middle_slice, upper_slice) = remaining.split_at_mut(1);
    let lower = &mut lower_slice[0];
    let middle = &mut middle_slice[0];
    let upper = &mut upper_slice[0];

    let period = options[0] as i32;
    let stddev = options[1];
    let scale = 1.0 / period as f64;

    if period < 1 {
        return Some(1);
    }

    let start = ti_bbands_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // Initialize sum and sum2 for the first period elements
    for i in 0..period as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
    }

    let mut sd = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt();
    middle[0] = sum * scale;
    lower[0] = middle[0] - (stddev * sd);
    upper[0] = middle[0] + (stddev * sd);

    // Process remaining elements
    for i in period as usize..size as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
        sum -= input[i - period as usize];
        sum2 -= input[i - period as usize] * input[i - period as usize];

        sd = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt();
        let middle_val = sum * scale;
        middle[i - period as usize + 1] = middle_val;
        upper[i - period as usize + 1] = middle_val + (stddev * sd);
        lower[i - period as usize + 1] = middle_val - (stddev * sd);
    }

    // Note: The original C asserts are omitted as they're debug checks
    Some(0)
}
