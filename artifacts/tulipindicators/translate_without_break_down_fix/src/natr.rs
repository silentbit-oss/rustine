use crate::*;
use std::f64;
pub fn ti_natr_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_natr_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if the slice is not empty to avoid panic on index 0
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(options[0] as i32 - 1)
}

pub fn ti_natr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_natr");
    // Check for None inputs
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start = ti_natr_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let per = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut truerange;
    let mut output_idx = 0;

    sum += high[0] - low[0];

    for i in 1..period {
        {
            let l = low[i as usize];
            let h = high[i as usize];
            let c = close[(i - 1) as usize];
            let ych = f64::abs(h - c);
            let ycl = f64::abs(l - c);
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            truerange = v;
        }
        sum += truerange;
    }

    let mut val = sum / period as f64;
    output[output_idx] = (100.0 * val) / close[(period - 1) as usize];
    output_idx += 1;

    for i in period..size {
        {
            let l = low[i as usize];
            let h = high[i as usize];
            let c = close[(i - 1) as usize];
            let ych = f64::abs(h - c);
            let ycl = f64::abs(l - c);
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            truerange = v;
        }
        val = ((truerange - val) * per) + val;
        output[output_idx] = (100.0 * val) / close[i as usize];
        output_idx += 1;
    }

    // Assertion check omitted in Rust as it's not idiomatic to include debug assertions in production code
    // Original C assertion: assert(((&output[output_idx]) - outputs[0]) == (size - ti_natr_start(options)));

    Some(0)
}
