use crate::*;
use std::f64::consts::LN_2;
use std::assert;

pub fn ti_fisher_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}

pub fn helper_ti_fisher_1(
    fisher_idx_ref: &mut u32,
    signal_idx_ref: &mut u32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    val1_ref: &mut f64,
    bar_ref: &mut f64,
    fish_ref: &mut f64,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    fisher: &mut [f64],
    signal: &mut [f64],
    trail: i32,
    i: i32,
) {
    let mut fisher_idx = *fisher_idx_ref;
    let mut signal_idx = *signal_idx_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut val1 = *val1_ref;
    let mut bar = *bar_ref;
    let mut fish = *fish_ref;
    let mut j = *j_ref;

    bar = 0.5 * (high[i as usize] + low[i as usize]);
    
    if maxi < trail {
        maxi = trail;
        max = 0.5 * (high[maxi as usize] + low[maxi as usize]);
        j = trail;
        while {
            j += 1;
            j <= i
        } {
            bar = 0.5 * (high[j as usize] + low[j as usize]);
            if bar >= max {
                max = bar;
                maxi = j;
            }
        }
    } else if bar >= max {
        maxi = i;
        max = bar;
    }

    bar = 0.5 * (high[i as usize] + low[i as usize]);
    
    if mini < trail {
        mini = trail;
        min = 0.5 * (high[mini as usize] + low[mini as usize]);
        j = trail;
        while {
            j += 1;
            j <= i
        } {
            bar = 0.5 * (high[j as usize] + low[j as usize]);
            if bar <= min {
                min = bar;
                mini = j;
            }
        }
    } else if bar <= min {
        mini = i;
        min = bar;
    }

    let mut mm = max - min;
    if mm == 0.0 {
        mm = 0.001;
    }

    val1 = ((0.33 * 2.0) * ((((0.5 * (high[i as usize] + low[i as usize])) - min) / mm) - 0.5)) + (0.67 * val1);
    if val1 > 0.99 {
        val1 = 0.999;
    }
    if val1 < -0.99 {
        val1 = -0.999;
    }

    signal[signal_idx as usize] = fish;
    signal_idx += 1;
    fish = (0.5 * ((1.0 + val1) / (1.0 - val1)).ln()) + (0.5 * fish);
    fisher[fisher_idx as usize] = fish;
    fisher_idx += 1;

    *fisher_idx_ref = fisher_idx;
    *signal_idx_ref = signal_idx;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *val1_ref = val1;
    *bar_ref = bar;
    *fish_ref = fish;
    *j_ref = j;
}
pub fn ti_fisher(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs/outputs
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let high = inputs[0];
    let low = inputs[1];
    
    // Split outputs into two mutable parts
    let (fisher_slice, signal_slice) = outputs.split_at_mut(1);
    let fisher = &mut fisher_slice[0];
    let signal = &mut signal_slice[0];

    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    let start = ti_fisher_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = 0.5 * (high[0] + low[0]);
    let mut min = 0.5 * (high[0] + low[0]);
    let mut val1 = 0.0;
    let mut bar = 0.0;
    let mut fish = 0.0;
    let mut j = 0;

    let mut fisher_idx = 0;
    let mut signal_idx = 0;

    for i in period - 1..size {
        helper_ti_fisher_1(
            &mut fisher_idx,
            &mut signal_idx,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut val1,
            &mut bar,
            &mut fish,
            &mut j,
            high,
            low,
            fisher,
            signal,
            trail,
            i,
        );
        trail += 1;
    }

    assert!((fisher_idx as i32) == (size - start));
    assert!((signal_idx as i32) == (size - start));

    Some(0)
}
