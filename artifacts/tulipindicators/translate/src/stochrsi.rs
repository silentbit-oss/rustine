use crate::*;
use std::assert;

pub fn ti_stochrsi_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = match options {
        Some(opt) if !opt.is_empty() => opt,
        _ => return -1, // Return -1 if options is None or empty (similar to NULL pointer case)
    };

    ((options[0] as i32) * 2) - 1
}
pub fn helper_ti_stochrsi_1(
    output_idx_ref: &mut u32,
    smooth_up_ref: &mut f64,
    smooth_down_ref: &mut f64,
    r_ref: &mut f64,
    min_ref: &mut f64,
    max_ref: &mut f64,
    mini_ref: &mut i32,
    maxi_ref: &mut i32,
    input: &[f64],
    period: i32,
    output: &mut [f64],
    per: f64,
    rsi: &mut TiBuffer,
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut smooth_up = *smooth_up_ref;
    let mut smooth_down = *smooth_down_ref;
    let mut r = *r_ref;
    let mut min = *min_ref;
    let mut max = *max_ref;
    let mut mini = *mini_ref;
    let mut maxi = *maxi_ref;

    let upward = if input[i] > input[i - 1] {
        input[i] - input[i - 1]
    } else {
        0.0
    };
    let downward = if input[i] < input[i - 1] {
        input[i - 1] - input[i]
    } else {
        0.0
    };

    smooth_up = ((upward - smooth_up) * per) + smooth_up;
    smooth_down = ((downward - smooth_down) * per) + smooth_down;
    r = 100.0 * (smooth_up / (smooth_up + smooth_down));

    if r > max {
        max = r;
        maxi = rsi.index;
    } else if maxi == rsi.index {
        max = r;
        for j in 0..rsi.size {
            if j == rsi.index {
                continue;
            }
            if rsi.vals[j as usize] > max {
                max = rsi.vals[j as usize];
                maxi = j;
            }
        }
    }

    if r < min {
        min = r;
        mini = rsi.index;
    } else if mini == rsi.index {
        min = r;
        for j in 0..rsi.size {
            if j == rsi.index {
                continue;
            }
            if rsi.vals[j as usize] < min {
                min = rsi.vals[j as usize];
                mini = j;
            }
        }
    }

    rsi.vals[rsi.index as usize] = r;
    rsi.index += 1;
    if rsi.index >= rsi.size {
        rsi.index = 0;
    }

    if i > ((period * 2) - 2) as usize {
        let diff = max - min;
        if diff == 0.0 {
            output[output_idx as usize] = 0.0;
            output_idx += 1;
        } else {
            output[output_idx as usize] = (r - min) / diff;
            output_idx += 1;
        }
    }

    *output_idx_ref = output_idx;
    *smooth_up_ref = smooth_up;
    *smooth_down_ref = smooth_down;
    *r_ref = r;
    *min_ref = min;
    *max_ref = max;
    *mini_ref = mini;
    *maxi_ref = maxi;
}

pub fn ti_stochrsi(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Early return if any required input is None
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let per = 1.0 / (period as f64);

    if period < 2 {
        return 1;
    }

    let start = ti_stochrsi_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut rsi = match ti_buffer_new(period) {
        Some(b) => *b,
        None => return 1,
    };

    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;

    for i in 1..=period as usize {
        let upward = if input[i] > input[i - 1] {
            input[i] - input[i - 1]
        } else {
            0.0
        };
        let downward = if input[i] < input[i - 1] {
            input[i - 1] - input[i]
        } else {
            0.0
        };
        smooth_up += upward;
        smooth_down += downward;
    }

    smooth_up /= period as f64;
    smooth_down /= period as f64;
    let mut r = 100.0 * (smooth_up / (smooth_up + smooth_down));

    {
        if rsi.pushes >= rsi.size {
            rsi.sum -= rsi.vals[rsi.index as usize];
        }
        rsi.sum += r;
        rsi.vals[rsi.index as usize] = r;
        rsi.pushes += 1;
        rsi.index += 1;
        if rsi.index >= rsi.size {
            rsi.index = 0;
        }
    }

    let mut min = r;
    let mut max = r;
    let mut mini = 0;
    let mut maxi = 0;

    for i in (period + 1) as usize..size as usize {
        helper_ti_stochrsi_1(
            &mut output_idx,
            &mut smooth_up,
            &mut smooth_down,
            &mut r,
            &mut min,
            &mut max,
            &mut mini,
            &mut maxi,
            input,
            period,
            output,
            per,
            &mut rsi,
            i,
        );
    }

    ti_buffer_free(rsi);

    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);
    0
}
