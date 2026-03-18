use crate::*;
use std::assert;

pub fn ti_aroon_start(options: Option<&[f64]>) -> i32 {
    // Use pattern matching to handle the Option safely
    match options {
        Some(opts) => {
            // Access the first element, default to 0 if slice is empty
            opts.first().map_or(0, |&val| val as i32)
        }
        None => 0, // Return 0 if options is None (NULL in C)
    }
}
pub fn ti_aroon(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if we have enough inputs and outputs
    if inputs.len() < 2 || outputs.len() < 2 {
        return 1;
    }

    let high = inputs[0];
    let low = inputs[1];
    
    // Split the outputs slice to get mutable references to both elements
    let (first, rest) = outputs.split_at_mut(1);
    let adown = &mut first[0];
    let aup = &mut rest[0];

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_aroon_start(Some(options));
    if size <= start {
        return 0;
    }

    let scale = 100.0 / period as f64;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar;
    let mut adown_idx = 0;
    let mut aup_idx = 0;

    for i in period..size {
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

        adown[adown_idx] = ((period - (i - mini)) as f64) * scale;
        adown_idx += 1;
        aup[aup_idx] = ((period - (i - maxi)) as f64) * scale;
        aup_idx += 1;
        trail += 1;
    }

    assert!((adown_idx as i32) == (size - start));
    assert!((aup_idx as i32) == (size - start));
    0
}
