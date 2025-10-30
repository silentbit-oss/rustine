use crate::*;
use std::assert;

pub fn ti_stoch_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;

    // Ensure the slice has at least 3 elements to avoid panic
    if options.len() < 3 {
        return None;
    }

    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;

    Some(((kperiod + kslow) + dperiod) - 3)
}
pub fn helper_helper_ti_stoch_1_1(
    stoch_idx_ref: &mut u32,
    stoch_ma_idx_ref: &mut u32,
    kperiod: i32,
    kslow: i32,
    dperiod: i32,
    kper: f64,
    dper: f64,
    stoch: &mut [f64],
    stoch_ma: &mut [f64],
    k_sum: &mut TiBuffer,
    d_sum: &mut TiBuffer,
    i: i32,
) {
    let stoch_idx = *stoch_idx_ref;
    let stoch_ma_idx = *stoch_ma_idx_ref;
    let k = k_sum.sum * kper;

    {
        if d_sum.pushes >= d_sum.size {
            d_sum.sum -= d_sum.vals[d_sum.index as usize];
        }
        d_sum.sum += k;
        d_sum.vals[d_sum.index as usize] = k;
        d_sum.pushes += 1;
        d_sum.index += 1;
        if d_sum.index >= d_sum.size {
            d_sum.index = 0;
        }
    }

    if i >= ((((kperiod - 1) + kslow - 1) + dperiod) - 1) {
        stoch[stoch_idx as usize] = k;
        *stoch_idx_ref = stoch_idx + 1;
        stoch_ma[stoch_ma_idx as usize] = d_sum.sum * dper;
        *stoch_ma_idx_ref = stoch_ma_idx + 1;
    } else {
        *stoch_idx_ref = stoch_idx;
        *stoch_ma_idx_ref = stoch_ma_idx;
    }
}
pub fn helper_ti_stoch_1(
    stoch_idx_ref: &mut u32,
    stoch_ma_idx_ref: &mut u32,
    trail_ref: &mut i32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    bar_ref: &mut f64,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    kperiod: i32,
    kslow: i32,
    dperiod: i32,
    kper: f64,
    dper: f64,
    stoch: &mut [f64],
    stoch_ma: &mut [f64],
    k_sum: &mut TiBuffer,
    d_sum: &mut TiBuffer,
    i: i32,
) {
    let mut stoch_idx = *stoch_idx_ref;
    let mut stoch_ma_idx = *stoch_ma_idx_ref;
    let mut trail = *trail_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut bar = *bar_ref;
    let mut j = *j_ref;

    if i >= kperiod {
        trail += 1;
    }

    bar = high[i as usize];
    if maxi < trail {
        maxi = trail;
        max = high[maxi as usize];
        j = trail;
        let mut current_j = trail + 1;
        while current_j <= i {
            bar = high[current_j as usize];
            if bar >= max {
                max = bar;
                maxi = current_j;
            }
            current_j += 1;
        }
    } else if bar >= max {
        maxi = i;
        max = bar;
    }

    bar = low[i as usize];
    if mini < trail {
        mini = trail;
        min = low[mini as usize];
        j = trail;
        let mut current_j = trail + 1;
        while current_j <= i {
            bar = low[current_j as usize];
            if bar <= min {
                min = bar;
                mini = current_j;
            }
            current_j += 1;
        }
    } else if bar <= min {
        mini = i;
        min = bar;
    }

    let kdiff = max - min;
    let kfast = if kdiff == 0.0 {
        0.0
    } else {
        100.0 * ((close[i as usize] - min) / kdiff)
    };

    {
        if k_sum.pushes >= k_sum.size {
            k_sum.sum -= k_sum.vals[k_sum.index as usize];
        }
        k_sum.sum += kfast;
        k_sum.vals[k_sum.index as usize] = kfast;
        k_sum.pushes += 1;
        k_sum.index += 1;
        if k_sum.index >= k_sum.size {
            k_sum.index = 0;
        }
    }

    if i >= ((kperiod - 1) + kslow) - 1 {
        helper_helper_ti_stoch_1_1(
            &mut stoch_idx,
            &mut stoch_ma_idx,
            kperiod,
            kslow,
            dperiod,
            kper,
            dper,
            stoch,
            stoch_ma,
            k_sum,
            d_sum,
            i,
        );
    }

    *stoch_idx_ref = stoch_idx;
    *stoch_ma_idx_ref = stoch_ma_idx;
    *trail_ref = trail;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *bar_ref = bar;
    *j_ref = j;
}
pub fn ti_stoch(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Unwrap options safely
    let options = options?;
    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;
    let kper = 1.0 / kslow as f64;
    let dper = 1.0 / dperiod as f64;

    // Check parameter validity
    if kperiod < 1 || kslow < 1 || dperiod < 1 {
        return Some(1);
    }

    // Check if we have enough data
    let start = ti_stoch_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    // Unwrap inputs and outputs safely
    let inputs = inputs?;
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    
    let outputs = outputs?;
    let (stoch, rest) = outputs.split_at_mut(1);
    let stoch_ma = &mut rest[0];
    let stoch = &mut stoch[0];

    // Initialize variables
    let mut stoch_idx = 0;
    let mut stoch_ma_idx = 0;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar = 0.0;
    let mut j = 0;

    // Create buffers
    let mut k_sum = ti_buffer_new(kslow)?;
    let mut d_sum = ti_buffer_new(dperiod)?;

    // Process each element
    for i in 0..size {
        helper_ti_stoch_1(
            &mut stoch_idx,
            &mut stoch_ma_idx,
            &mut trail,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut bar,
            &mut j,
            high,
            low,
            close,
            kperiod,
            kslow,
            dperiod,
            kper,
            dper,
            stoch,
            stoch_ma,
            &mut k_sum,
            &mut d_sum,
            i,
        );
    }

    // Clean up
    ti_buffer_free(*k_sum);
    ti_buffer_free(*d_sum);

    // Verify output lengths
    assert!((stoch_idx as usize) == (size - start) as usize);
    assert!((stoch_ma_idx as usize) == (size - start) as usize);

    Some(0)
}
