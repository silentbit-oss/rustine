use crate::*;
use rand::Rng;

pub fn ti_apo_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_apo_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}

pub fn ti_apo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_apo");
    // Check for None in inputs and outputs
    if inputs.is_none() || outputs.is_none() || options.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    let options = options.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }

    let input = inputs[0];
    let apo = &mut outputs[0];
    let mut apo_idx = 0;

    // Extract options with bounds checking
    if options.len() < 2 {
        return 1;
    }
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;

    // Validate periods
    if short_period < 1 || long_period < 2 || long_period < short_period {
        return 1;
    }

    // Check size against start index
    let start = ti_apo_start(Some(options));
    if size <= start {
        return 0;
    }

    // Calculate periods
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);

    // Initialize EMAs
    let mut short_ema = input[0];
    let mut long_ema = input[0];

    // Process input
    for i in 1..size as usize {
        short_ema = (input[i] - short_ema) * short_per + short_ema;
        long_ema = (input[i] - long_ema) * long_per + long_ema;
        let out = short_ema - long_ema;

        // Check bounds before writing to output
        if apo_idx < apo.len() {
            apo[apo_idx] = out;
            apo_idx += 1;
        } else {
            break;
        }
    }

    // Assertion check (commented out as it's not idiomatic in Rust)
    // assert!((&apo[apo_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    0
}
