use crate::*;
use std::f64;

pub fn ti_adx_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => ((opts[0] as i32) - 1) * 2,
        None => 0, // Default behavior when NULL is passed (similar to C's undefined behavior)
    }
}
pub fn helper_ti_adx_1(
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
    
    dp = if dp < 0.0 {
        0.0
    } else if dp > dm {
        dm = 0.0;
        dp
    } else {
        dp
    };
    
    dm = if dm < 0.0 {
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

pub fn helper_ti_adx_2(
    output_idx_ref: &mut u32,
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    adx_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    period: i32,
    output: &mut [f64],
    per: f64,
    invper: f64,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    let mut adx = *adx_ref;

    let dp;
    let dm;
    {
        dp = if high[i as usize] - high[(i - 1) as usize] < 0.0 {
            0.0
        } else {
            let temp_dp = high[i as usize] - high[(i - 1) as usize];
            let temp_dm = low[(i - 1) as usize] - low[i as usize];
            if temp_dp > temp_dm { temp_dp } else { 0.0 }
        };

        dm = if low[(i - 1) as usize] - low[i as usize] < 0.0 {
            0.0
        } else {
            let temp_dm = low[(i - 1) as usize] - low[i as usize];
            let temp_dp = high[i as usize] - high[(i - 1) as usize];
            if temp_dm > temp_dp { temp_dm } else { 0.0 }
        };
    }

    dmup = dmup * per + dp;
    dmdown = dmdown * per + dm;
    let di_up = dmup;
    let di_down = dmdown;
    let dm_diff = f64::abs(di_up - di_down);
    let dm_sum = di_up + di_down;
    let dx = (dm_diff / dm_sum) * 100.0;

    if (i - period) < (period - 2) {
        adx += dx;
    } else if (i - period) == (period - 2) {
        adx += dx;
        output[output_idx as usize] = adx * invper;
        output_idx += 1;
    } else {
        adx = adx * per + dx;
        output[output_idx as usize] = adx * invper;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
    *adx_ref = adx;
}

pub fn ti_adx(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.len() < 2 || outputs.is_empty() {
        return 1;
    }

    let high = inputs[0];
    let low = inputs[1];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    if period < 2 {
        return 1;
    }

    let start = ti_adx_start(Some(options));
    if size <= start {
        return 0;
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let invper = 1.0 / f64::from(period);

    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    let mut output_idx = 0;

    // Initialize dmup and dmdown
    for i in 1..period as usize {
        helper_ti_adx_1(&mut dmup, &mut dmdown, high, low, i);
    }

    let mut adx = 0.0;
    {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        adx += dx;
    }

    for i in period..size {
        helper_ti_adx_2(
            &mut output_idx,
            &mut dmup,
            &mut dmdown,
            &mut adx,
            high,
            low,
            period,
            output,
            per,
            invper,
            i,
        );
    }

    // Assertion check (Rust's assert! macro is used here)
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);

    0
}
