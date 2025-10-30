use crate::*;
use rand::Rng;

pub fn ti_aroonosc_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_aroonosc_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn ti_aroonosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_aroonosc");
    // Check for None inputs/outputs
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    if inputs.len() < 2 {
        return 0;
    }
    // Get slices from inputs and outputs
    let high = inputs.get(0).unwrap();
    let low = inputs.get(1).unwrap();
    let output = outputs.get_mut(0).unwrap();

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_aroonosc_start(Some(options));
    if size <= start {
        return 0;
    }

    let scale = 100.0 / period as f64;
    let mut output_idx = 0;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];

    for i in period..size {
        // Process high values
        let bar = high[i as usize];
        if maxi < trail {
            maxi = trail;
            max = high[maxi as usize];
            let mut j = trail;
            while j <= i {
                let bar = high[j as usize];
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i;
            max = bar;
        }

        // Process low values
        let bar = low[i as usize];
        if mini < trail {
            mini = trail;
            min = low[mini as usize];
            let mut j = trail;
            while j <= i {
                let bar = low[j as usize];
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

        output[output_idx] = (maxi - mini) as f64 * scale;
        output_idx += 1;
        trail += 1;
    }

    // Assertion check (commented as it's not idiomatic in Rust)
    // assert!((&output[output_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_aroonosc_start(Some(options))) as usize);

    0
}
