use crate::*;
use std::assert;

pub fn ti_dm_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options?;
    
    // Check if the slice is not empty to avoid panic on index 0
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C: cast to int and subtract 1
    Some(options[0] as i32 - 1)
}
pub fn ti_dm(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices from inputs and outputs
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;

    // Get mutable references to output slices using split_at_mut
    let (plus_dm, minus_dm) = {
        let (first, rest) = outputs.split_at_mut(1);
        (&mut first[0], &mut rest[0])
    };

    // Check period validity
    if period < 1 {
        return Some(1);
    }

    // Check size validity
    let start = ti_dm_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    // First loop: initial period
    for i in 1..period {
        let (dp, dm) = {
            let dp = high[i as usize] - high[(i - 1) as usize];
            let dm = low[(i - 1) as usize] - low[i as usize];

            let dp = if dp < 0.0 { 0.0 } else { dp };
            let dm = if dm < 0.0 { 0.0 } else { dm };

            let (dp, dm) = if dp > dm {
                (dp, 0.0)
            } else if dm > dp {
                (0.0, dm)
            } else {
                (dp, dm)
            };

            (dp, dm)
        };

        dmup += dp;
        dmdown += dm;
    }

    // Store initial values
    plus_dm[0] = dmup;
    minus_dm[0] = dmdown;

    // Second loop: remaining periods
    for i in period..size {
        let (dp, dm) = {
            let dp = high[i as usize] - high[(i - 1) as usize];
            let dm = low[(i - 1) as usize] - low[i as usize];

            let dp = if dp < 0.0 { 0.0 } else { dp };
            let dm = if dm < 0.0 { 0.0 } else { dm };

            let (dp, dm) = if dp > dm {
                (dp, 0.0)
            } else if dm > dp {
                (0.0, dm)
            } else {
                (dp, dm)
            };

            (dp, dm)
        };

        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;

        let idx = (i - period + 1) as usize;
        plus_dm[idx] = dmup;
        minus_dm[idx] = dmdown;
    }

    // Verify output lengths
    let expected_len = (size - start) as usize;
    assert!(plus_dm.len() >= expected_len);
    assert!(minus_dm.len() >= expected_len);

    Some(0)
}
