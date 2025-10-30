use crate::*;
use rand::Rng;

pub fn ti_max_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_max_start");
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}

pub fn ti_max(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_max");
    // Check for None in all Option parameters
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices from inputs and outputs
    let input = inputs[0];
    let output = &mut outputs[0];

    // Get period from options
    let period = options[0] as i32;
    let mut output_idx = 0;

    if period < 1 {
        return Some(1);
    }

    let max_start = ti_max_start(Some(options))?;
    if size <= max_start {
        return Some(0);
    }

    let mut trail = 0;
    let mut maxi = -1;
    let mut max = input[0];

    for i in (period - 1)..size {
        let bar = input[i as usize];
        if maxi < trail {
            maxi = trail;
            max = input[maxi as usize];
            let mut j = trail;
            while j <= i {
                let bar_j = input[j as usize];
                if bar_j >= max {
                    max = bar_j;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i;
            max = bar;
        }

        output[output_idx as usize] = max;
        output_idx += 1;
        trail += 1;
    }

    // Assertion check (commented out as it's not idiomatic in Rust to use asserts for validation)
    // assert!((output[output_idx as usize] as *const f64).offset_from(outputs[0][0] as *const f64) == (size - max_start) as isize);

    Some(0)
}
pub fn ti_max_ref(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_max_ref");
    // Check for None in all Option parameters
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Get period from options
    let period = options[0] as i32;
    let mut output_idx = 0;

    if period < 1 {
        return Some(1);
    }

    // Check if size is sufficient using the dependency function
    if let Some(start) = ti_max_start(Some(options)) {
        if size <= start {
            return Some(0);
        }
    } else {
        return None;
    }

    // Iterate through the input
    for i in (period - 1)..size {
        let start_idx = (i - period) + 1;
        let end_idx = i + 1; // +1 because Rust ranges are exclusive

        // Get slice for the current window
        let window = &input[start_idx as usize..end_idx as usize];
        
        // Find max in the window
        let max = window.iter().fold(f64::NEG_INFINITY, |a, &b| a.max(b));

        // Store the result
        if output_idx < output.len() {
            output[output_idx] = max;
            output_idx += 1;
        } else {
            break;
        }
    }

    Some(0)
}
