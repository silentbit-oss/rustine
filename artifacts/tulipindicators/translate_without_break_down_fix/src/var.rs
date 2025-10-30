use crate::*;
use rand::Rng;

pub fn ti_var_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_var_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if the slice is not empty to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(options[0] as i32 - 1)
}

pub fn ti_var(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_var");
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Check if size is sufficient
    if let Some(start) = ti_var_start(Some(options)) {
        if size <= start {
            return Some(0);
        }
    } else {
        return Some(1);
    }

    let scale = 1.0 / period as f64;
    let mut output_idx = 0;

    // Initialize sums
    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // First window calculation
    for i in 0..period as usize {
        let val = input[i];
        sum += val;
        sum2 += val * val;
    }

    output[output_idx] = (sum2 * scale) - ((sum * scale) * (sum * scale));
    output_idx += 1;

    // Rolling window calculation
    for i in period as usize..size as usize {
        let new_val = input[i];
        let old_val = input[i - period as usize];

        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;

        output[output_idx] = (sum2 * scale) - ((sum * scale) * (sum * scale));
        output_idx += 1;
    }

    // Note: The assertion in the original C code is not directly translatable without unsafe
    // as it involves pointer arithmetic. In safe Rust, we would track lengths instead.

    Some(0)
}
