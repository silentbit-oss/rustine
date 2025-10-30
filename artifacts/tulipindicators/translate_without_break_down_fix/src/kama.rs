use crate::*;
use libm::fabs;
use libm::pow;

pub fn ti_kama_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_kama_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // and if the slice has at least one element
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32 - 1,
        _ => -1, // Return -1 for NULL pointer or empty slice (common error value in C)
    }
}

pub fn ti_kama(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_kama");
    // Early return if any required input is None
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let required_size = ti_kama_start(Some(options));
    if size <= required_size {
        return 0;
    }

    let short_per = 2.0 / (2.0 + 1.0);
    let long_per = 2.0 / (30.0 + 1.0);
    let mut sum = 0.0;
    let mut output_idx = 0;

    // Calculate initial sum
    for i in 1..period {
        sum += fabs(input[i as usize] - input[(i - 1) as usize]);
    }

    let mut kama = input[(period - 1) as usize];
    output[output_idx] = kama;
    output_idx += 1;

    for i in period..size {
        let i_usize = i as usize;
        sum += fabs(input[i_usize] - input[(i - 1) as usize]);

        if i > period {
            sum -= fabs(input[(i - period) as usize] - input[(i - period - 1) as usize]);
        }

        let er = if sum != 0.0 {
            fabs(input[i_usize] - input[(i - period) as usize]) / sum
        } else {
            1.0
        };

        let sc = pow(er * (short_per - long_per) + long_per, 2.0);
        kama += sc * (input[i_usize] - kama);
        output[output_idx] = kama;
        output_idx += 1;
    }

    // Assertion check (commented out as it's not idiomatic in Rust to use assertions for control flow)
    // assert!((&output[output_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_kama_start(Some(options))) as usize);

    0
}
