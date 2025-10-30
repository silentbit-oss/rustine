use crate::*;
use std::f64;

pub fn ti_adxr_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => ((opts[0] as i32) - 1) * 3,
        None => 0, // Default behavior when options is None (NULL in C)
    }
}
pub fn helper_ti_adxr_1(
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
    
    dmup += dp;
    dmdown += dm;
    
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}

pub fn helper_ti_adxr_2(
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
    adxr: &mut TiBuffer,
    first_adxr: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    let mut adx = *adx_ref;
    
    let dp;
    let dm;
    
    // Equivalent to the do-while(0) block in C
    {
        dp = if high[i as usize] - high[(i - 1) as usize] < 0.0 {
            0.0
        } else {
            let temp_dp = high[i as usize] - high[(i - 1) as usize];
            let temp_dm = low[(i - 1) as usize] - low[i as usize];
            if temp_dp > temp_dm { 0.0 } else { temp_dp }
        };
        
        dm = if low[(i - 1) as usize] - low[i as usize] < 0.0 {
            0.0
        } else {
            let temp_dm = low[(i - 1) as usize] - low[i as usize];
            let temp_dp = high[i as usize] - high[(i - 1) as usize];
            if temp_dm > temp_dp { 0.0 } else { temp_dm }
        };
    }
    
    dmup = (dmup * per) + dp;
    dmdown = (dmdown * per) + dm;
    
    let di_up = dmup;
    let di_down = dmdown;
    let dm_diff = f64::abs(di_up - di_down);
    let dm_sum = di_up + di_down;
    let dx = (dm_diff / dm_sum) * 100.0;
    
    if (i - period) < (period - 2) {
        adx += dx;
    } else if (i - period) == (period - 2) {
        adx += dx;
        {
            adxr.vals[adxr.index as usize] = adx * invper;
            adxr.index += 1;
            if adxr.index >= adxr.size {
                adxr.index = 0;
            }
        }
    } else {
        adx = (adx * per) + dx;
        if i >= first_adxr {
            let prev_index = ((adxr.index + adxr.size - 1) + 1) % adxr.size;
            output[output_idx as usize] = 0.5 * ((adx * invper) + adxr.vals[prev_index as usize]);
            output_idx += 1;
        }
        {
            adxr.vals[adxr.index as usize] = adx * invper;
            adxr.index += 1;
            if adxr.index >= adxr.size {
                adxr.index = 0;
            }
        }
    }
    
    *output_idx_ref = output_idx;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
    *adx_ref = adx;
}

pub fn ti_adxr(
    size: i32,
    inputs: &[&[f64]],
    options: Option<&[f64]>,
    outputs: &mut [&mut [f64]],
) -> Result<(), i32> {
    let high = inputs[0];
    let low = inputs[1];
    let period = options.and_then(|opts| opts.first().copied()).map(|p| p as i32).unwrap_or(0);
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 2 {
        return Err(1);
    }

    let first_adxr = ti_adxr_start(options);
    if size <= first_adxr {
        return Ok(());
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let invper = 1.0 / f64::from(period);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    for i in 1..period {
        helper_ti_adxr_1(&mut dmup, &mut dmdown, high, low, i as usize);
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

    let mut adxr = match ti_buffer_new(period - 1) {
        Some(buf) => buf,
        None => return Err(1),
    };

    for i in period..size {
        helper_ti_adxr_2(
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
            &mut adxr,
            first_adxr,
        );
    }

    ti_buffer_free(*adxr);
    assert!((output[output_idx as usize] - outputs[0][0]) == (f64::from(size - first_adxr)));
    Ok(())
}
