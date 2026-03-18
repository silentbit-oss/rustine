use crate::*;
use rand::Rng;

pub fn ti_sum_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_sum_start");
    match options {
        Some(opts) => opts[0] as i32 - 1,
        None => -1, // Return -1 if options is None (equivalent to NULL in C)
    }
}

pub fn ti_sum(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
	println!("\n* ti_sum");
    // Check for None values (equivalent to NULL checks in C)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let mut outputs = outputs.ok_or(1)?;

    // Get the input and output slices
    let input = inputs.first().ok_or(1)?;
    let output = outputs.first_mut().ok_or(1)?;

    // Get period from options
    let period = options.first().map(|&p| p as i32).ok_or(1)?;
    if period < 1 {
        return Err(1);
    }

    // Check size requirements
    let start = ti_sum_start(Some(options));
    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    let mut sum = 0.0;

    // Calculate initial sum
    for i in 0..period as usize {
        sum += input[i];
    }

    // Store first result
    if output_idx < output.len() {
        output[output_idx] = sum;
        output_idx += 1;
    }

    // Calculate rolling sum
    for i in period as usize..size as usize {
        sum += input[i];
        sum -= input[i - period as usize];

        if output_idx < output.len() {
            output[output_idx] = sum;
            output_idx += 1;
        }
    }

    // In Rust we don't need the assertion since bounds are checked automatically
    Ok(())
}
