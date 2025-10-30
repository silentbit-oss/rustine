use crate::*;
use std::assert;

pub fn ti_min_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => opts[0] as i32 - 1,
        None => -1, // Return -1 if options is None (equivalent to NULL in C)
    }
}
pub fn ti_min(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 1 {
        return 1;
    }

    let min_start = ti_min_start(Some(options));
    if size <= min_start {
        return 0;
    }

    let mut trail = 0;
    let mut mini = -1;
    let mut min = input[0];
    
    for i in (period - 1)..size {
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

    assert!(output_idx == (size - min_start) as usize);
    0
}
pub fn ti_min_ref(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    if options.is_none() || inputs.is_none() || outputs.is_none() {
        return 1;
    }
    let options = options.unwrap();
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();

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
            min = min.min(input[j as usize]);
        }

        output[output_idx] = min;
        output_idx += 1;
    }

    // Rust's assert! macro is equivalent to C's assert
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>() - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - min_start) as usize);

    0
}
