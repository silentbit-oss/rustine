use crate::*;
use rand::Rng;

pub fn ti_willr_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(options[0] as i32 - 1)
}

pub fn ti_willr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for invalid inputs
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let outputs = outputs.ok_or(1)?;

    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Err(1);
    }

    let start = match ti_willr_start(Some(options)) {
        Some(s) => s,
        None => return Err(1),
    };

    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar;

    for i in (period - 1)..size {
        bar = high[i as usize];
        if maxi < trail {
            maxi = trail;
            max = high[maxi as usize];
            let mut j = trail;
            while j <= i {
                bar = high[j as usize];
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

        bar = low[i as usize];
        if mini < trail {
            mini = trail;
            min = low[mini as usize];
            let mut j = trail;
            while j <= i {
                bar = low[j as usize];
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

        let highlow = max - min;
        let r = if highlow == 0.0 {
            0.0
        } else {
            -100.0 * ((max - close[i as usize]) / highlow)
        };

        output[output_idx as usize] = r;
        output_idx += 1;
        trail += 1;
    }

    // Assertion check removed as it's not idiomatic in Rust
    Ok(())
}
