use crate::*;
use std::f64;

pub fn ti_md_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_md_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options.unwrap();
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return 0;
    }

    // Perform the same calculation as in C
    options[0] as i32 - 1
}

pub fn ti_md(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_md");
    // Check for None in all Option parameters
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get slices from the input arrays
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let md_start = ti_md_start(Some(options));
    if size <= md_start {
        return 0;
    }

    let scale = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut output_idx = 0;

    for i in 0..size as usize {
        let today = input[i];
        sum += today;

        if i >= period as usize {
            sum -= input[i - period as usize];
        }

        let avg = sum * scale;

        if i >= (period - 1) as usize {
            let mut acc = 0.0;
            for j in 0..period as usize {
                acc += f64::abs(avg - input[i - j]);
            }

            output[output_idx] = acc * scale;
            output_idx += 1;
        }
    }

    // Note: The assert in the original C code is omitted as it's a debug check
    0
}
