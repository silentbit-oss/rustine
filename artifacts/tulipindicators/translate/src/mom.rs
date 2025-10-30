use crate::*;

pub fn ti_mom_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}
pub fn ti_mom(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for invalid period
    let period = options.and_then(|opts| opts.first().map(|&p| p as i32)).unwrap_or(0);
    if period < 1 {
        return 1;
    }

    // Check if size is too small
    let start = ti_mom_start(options);
    if size <= start {
        return 0;
    }

    // Safely unwrap inputs and outputs
    let input = match inputs {
        Some(inp) => inp[0],
        None => return 1,
    };
    let output = match outputs {
        Some(out) => &mut out[0],
        None => return 1,
    };

    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[i as usize] - input[(i - period) as usize];
        output_idx += 1;
    }

    // Assertion check (using debug_assert! since it's a debug check)
    debug_assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) 
        - output.as_ptr() as usize == ((size - start) as usize * std::mem::size_of::<f64>()));

    0
}
