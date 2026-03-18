use crate::*;
use rand::Rng;

pub fn ti_ema_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_ema_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_ema(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
	println!("\n* ti_ema");
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Err(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    if period < 1 {
        return Err(1);
    }

    let ema_start = ti_ema_start(Some(options));
    if size <= ema_start {
        return Ok(());
    }

    let per = 2.0 / (period as f64 + 1.0);
    let mut val = input[0];
    let mut output_idx = 0;

    output[output_idx] = val;
    output_idx += 1;

    for i in 1..size as usize {
        val = ((input[i] - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }

    // The assertion in C is not needed in safe Rust as bounds are checked
    Ok(())
}
