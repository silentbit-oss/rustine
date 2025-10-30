use crate::*;
use rand::Rng;

pub fn ti_mass_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    let sum_p = (options[0] as i32) - 1;
    Some(16 + sum_p)
}

pub fn ti_mass(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs (equivalent to NULL checks in C)
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get high and low slices
    let high = inputs[0];
    let low = inputs[1];

    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Check if size is sufficient
    let start = ti_mass_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    // Get output slice
    let output = &mut outputs[0];

    // Initialize variables
    let per = 2.0 / (9.0 + 1.0);
    let per1 = 1.0 - per;
    let mut ema = high[0] - low[0];
    let mut ema2 = ema;
    let mut sum = ti_buffer_new(period)?;
    let mut output_idx = 0;

    // Main processing loop
    for i in 0..size as usize {
        let hl = high[i] - low[i];
        ema = (ema * per1) + (hl * per);

        if i == 8 {
            ema2 = ema;
        }

        if i >= 8 {
            ema2 = (ema2 * per1) + (ema * per);

            if i >= 16 {
                // Process the sum buffer
                if sum.pushes >= sum.size {
                    sum.sum -= sum.vals[sum.index as usize];
                }
                sum.sum += ema / ema2;
                sum.vals[sum.index as usize] = ema / ema2;
                sum.pushes += 1;
                sum.index = (sum.index + 1) % sum.size;

                if i >= (16 + period as usize - 1) {
                    output[output_idx] = sum.sum;
                    output_idx += 1;
                }
            }
        }
    }

    // Free the buffer
    ti_buffer_free(*sum);

    // Verify output length (assert equivalent)
    debug_assert!(
        (output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>())
            - output.as_ptr() as usize
            == (size as usize - start as usize) * std::mem::size_of::<f64>()
    );

    Some(0)
}
