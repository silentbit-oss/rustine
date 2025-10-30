use crate::*;
use std::assert;

pub fn ti_willr_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn helper_ti_willr_1(
    output_idx_ref: &mut u32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    bar_ref: &mut f64,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    output: &mut [f64],
    trail: i32,
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut bar = *bar_ref;
    let mut j = *j_ref;

    bar = high[i];
    if maxi < trail {
        maxi = trail;
        max = high[maxi as usize];
        j = trail;
        let mut current_j = j + 1;
        while current_j <= i as i32 {
            bar = high[current_j as usize];
            if bar >= max {
                max = bar;
                maxi = current_j;
            }
            current_j += 1;
        }
    } else if bar >= max {
        maxi = i as i32;
        max = bar;
    }

    bar = low[i];
    if mini < trail {
        mini = trail;
        min = low[mini as usize];
        j = trail;
        let mut current_j = j + 1;
        while current_j <= i as i32 {
            bar = low[current_j as usize];
            if bar <= min {
                min = bar;
                mini = current_j;
            }
            current_j += 1;
        }
    } else if bar <= min {
        mini = i as i32;
        min = bar;
    }

    let highlow = max - min;
    let r = if highlow == 0.0 {
        0.0
    } else {
        -100.0 * ((max - close[i]) / highlow)
    };

    output[output_idx as usize] = r;
    output_idx += 1;

    *output_idx_ref = output_idx;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *bar_ref = bar;
    *j_ref = j;
}

pub fn ti_willr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Extract slices from inputs and outputs
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start = ti_willr_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let mut output_idx = 0;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar = 0.0;
    let mut j = 0;

    for i in (period - 1)..size {
        helper_ti_willr_1(
            &mut output_idx,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut bar,
            &mut j,
            high,
            low,
            close,
            output,
            trail,
            i as usize,
        );
        trail += 1;
    }

    // Convert the assertion to a debug assertion
    debug_assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);

    Some(0)
}
