use crate::*;
use std::assert;

pub fn ti_dm_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Return -1 for None or empty slice (similar to NULL/invalid input handling)
    }
}
pub fn helper_ti_dm_1(
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    i: usize,
) {
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    
    let mut dp;
    let mut dm;
    
    {
        dp = high[i] - high[i - 1];
        dm = low[i - 1] - low[i];
    }
    
    let mut dp = if dp < 0.0 {
        0.0
    } else if dp > dm {
        dm = 0.0;
        dp
    } else {
        dp
    };
    
    let dm = if dm < 0.0 {
        0.0
    } else if dm > dp {
        dp = 0.0;
        dm
    } else {
        dm
    };
    
    dmup += dp;
    dmdown += dm;
    
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn helper_ti_dm_2(
    plus_dm_idx_ref: &mut u32,
    minus_dm_idx_ref: &mut u32,
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    plus_dm: &mut [f64],
    minus_dm: &mut [f64],
    per: f64,
    i: usize,
) {
    let mut plus_dm_idx = *plus_dm_idx_ref;
    let mut minus_dm_idx = *minus_dm_idx_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;

    let dp = {
        let mut dp = high[i] - high[i - 1];
        let mut dm = low[i - 1] - low[i];
        
        if dp < 0.0 {
            dp = 0.0;
        } else if dp > dm {
            dm = 0.0;
        }
        
        if dm < 0.0 {
            dm = 0.0;
        } else if dm > dp {
            dp = 0.0;
        }
        
        dp
    };

    let dm = {
        let mut dp = high[i] - high[i - 1];
        let mut dm = low[i - 1] - low[i];
        
        if dp < 0.0 {
            dp = 0.0;
        } else if dp > dm {
            dm = 0.0;
        }
        
        if dm < 0.0 {
            dm = 0.0;
        } else if dm > dp {
            dp = 0.0;
        }
        
        dm
    };

    dmup = (dmup * per) + dp;
    dmdown = (dmdown * per) + dm;

    plus_dm[plus_dm_idx as usize] = dmup;
    plus_dm_idx += 1;
    minus_dm[minus_dm_idx as usize] = dmdown;
    minus_dm_idx += 1;

    *plus_dm_idx_ref = plus_dm_idx;
    *minus_dm_idx_ref = minus_dm_idx;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn ti_dm(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Early return if any required input is None
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };

    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;

    if period < 1 {
        return 1;
    }

    let start = ti_dm_start(Some(options));
    if size <= start {
        return 0;
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    // Use split_at_mut to get mutable references to both output slices
    let (plus_dm_slice, minus_dm_slice) = outputs.split_at_mut(1);
    let mut plus_dm = &mut plus_dm_slice[0];
    let mut minus_dm = &mut minus_dm_slice[0];
    let mut plus_dm_idx = 0;
    let mut minus_dm_idx = 0;

    // First loop (i from 1 to period-1)
    for i in 1..period as usize {
        helper_ti_dm_1(&mut dmup, &mut dmdown, high, low, i);
    }

    plus_dm[plus_dm_idx as usize] = dmup;
    plus_dm_idx += 1;
    minus_dm[minus_dm_idx as usize] = dmdown;
    minus_dm_idx += 1;

    // Second loop (i from period to size-1)
    for i in period as usize..size as usize {
        helper_ti_dm_2(
            &mut plus_dm_idx,
            &mut minus_dm_idx,
            &mut dmup,
            &mut dmdown,
            high,
            low,
            plus_dm,
            minus_dm,
            per,
            i,
        );
    }

    // Assertions - calculate lengths without borrowing conflicts
    let plus_dm_len = plus_dm_idx as usize;
    let minus_dm_len = minus_dm_idx as usize;
    let expected_len = (size - start) as usize;
    assert!(plus_dm_len == expected_len);
    assert!(minus_dm_len == expected_len);

    0
}
