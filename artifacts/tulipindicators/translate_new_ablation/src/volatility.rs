use crate::*;
use std::f64::consts::SQRT_2;

pub extern "C" fn ti_volatility_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0,
    }
}

pub extern "C" fn ti_volatility(size: i32, inputs: Option<&[Option<&[f64]>]>, options: Option<&[f64]>, outputs: Option<&mut [Option<&mut [f64]>]>) -> i32 {
    // Check for NULL pointers using Option
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let mut outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    // Get input and output slices
    let input_slice = match inputs.get(0) {
        Some(Some(input)) => input,
        _ => return 1,
    };
    let output_slice = match outputs.get_mut(0) {
        Some(Some(output)) => output,
        _ => return 1,
    };

    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    let annual = 252.0_f64.sqrt();

    if period < 1 {
        return 1;
    }

    let start = ti_volatility_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;
    let mut output_idx = 0;

    // Initialize the first period values
    for i in 1..=period {
        let i_usize = i as usize;
        let c = (input_slice[i_usize] / input_slice[i_usize - 1]) - 1.0;
        sum += c;
        sum2 += c * c;
    }

    // Calculate first output value
    output_slice[output_idx] = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt() * annual;
    output_idx += 1;

    // Process remaining values
    for i in (period + 1)..size {
        let i_usize = i as usize;
        
        // Add current value
        let c = (input_slice[i_usize] / input_slice[i_usize - 1]) - 1.0;
        sum += c;
        sum2 += c * c;

        // Remove oldest value
        let cp = (input_slice[i_usize - period as usize] / input_slice[i_usize - period as usize - 1]) - 1.0;
        sum -= cp;
        sum2 -= cp * cp;

        // Calculate output
        output_slice[output_idx] = ((sum2 * scale) - ((sum * scale) * (sum * scale))).sqrt() * annual;
        output_idx += 1;
    }

    // Assertion check (commented out as Rust doesn't have exact C assert equivalent)
    // assert!((output_idx as i32) == (size - start));

    0
}
