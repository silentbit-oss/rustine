use crate::*;
use rand::Rng;

pub fn ti_lag_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_lag_start");
    // Use unwrap_or to handle None case, defaulting to 0.0 if options is None or empty
    options.and_then(|opts| opts.first().copied()).unwrap_or(0.0) as i32
}

pub fn ti_lag(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
	println!("\n* ti_lag");
    // Check for null equivalents (None in Rust)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return Err(1),
    };

    let period = match options {
        Some(options) => options[0] as i32,
        None => return Err(1),
    };

    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return Err(1),
    };

    if period < 0 {
        return Err(1);
    }

    let start = ti_lag_start(options);
    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[(i - period) as usize];
        output_idx += 1;
    }

    // The assert in C is not needed in Rust as bounds are checked automatically
    Ok(())
}
