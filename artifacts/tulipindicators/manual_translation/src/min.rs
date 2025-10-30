use crate::*;
use rand::Rng;

pub fn ti_min_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_min_start");
    // Check if options is None (equivalent to NULL check in C)
    // Then safely access the first element or return a default value
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Default return value when options is None or empty
    }
}

pub fn ti_min(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_min");
    // Check for None inputs
    let inputs = inputs.unwrap();//ok_or("inputs is None")?;
    let options = options.unwrap();//ok_or("options is None")?;
    let outputs = outputs.unwrap();//ok_or("outputs is None")?;

    // Get slices from inputs and outputs
    let input = inputs[0];
    let output = &mut outputs[0];

    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return 0;//Err("period must be >= 1");
    }

    // Check size requirements
    let min_start = ti_min_start(Some(options));
    if size <= min_start {
        return 0;//Ok(0);
    }

    let mut output_idx = 0;
    let mut trail = 0;
    let mut mini = -1;
    let mut min = input[0];

    for i in period - 1..size {
        let bar = input[i as usize];
        if mini < trail {
            mini = trail;
            min = input[mini as usize];
            let mut j = trail;
            while j <= i {
                let bar = input[j as usize];
                if bar <= min {
                    min = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min {
            mini = i;
            min = bar;
        }

        output[output_idx as usize] = min;
        output_idx += 1;
        trail += 1;
    }

    // Verify output length matches expected
    let expected_len = (size - min_start) as usize;
    if output_idx as usize != expected_len {
        return 0;//Err("output length mismatch");
    }

    0
}

pub fn ti_min_ref(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_min_ref");
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let min_start = ti_min_start(Some(options));
    if size <= min_start {
        return 0;
    }

    let mut output_idx = 0;
    for i in (period - 1)..size {
        let mut min = input[(i - period + 1) as usize];
        for j in (i - period + 2)..=i {
            let val = input[j as usize];
            min = if min < val { min } else { val };
        }

        output[output_idx] = min;
        output_idx += 1;
    }

    // The assertion in C is not directly translatable without unsafe,
    // but we can verify the length matches expectations
    let expected_len = (size - min_start) as usize;
    assert_eq!(output_idx, expected_len);

    0
}
