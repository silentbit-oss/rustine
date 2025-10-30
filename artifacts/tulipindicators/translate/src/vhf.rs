use crate::*;
use std::f64;

pub fn ti_vhf_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // Then safely access the first element or return 0 as default
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}

pub fn helper_ti_vhf_1(
    output_idx_ref: &mut u32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    bar_ref: &mut f64,
    sum_ref: &mut f64,
    j_ref: &mut i32,
    yc_ref: &mut f64,
    c_ref: &mut f64,
    in_data: &[f64],
    period: i32,
    output: &mut [f64],
    trail: i32,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut bar = *bar_ref;
    let mut sum = *sum_ref;
    let mut j = *j_ref;
    let mut yc = *yc_ref;
    let mut c = *c_ref;

    c = in_data[i as usize];
    sum += f64::abs(c - yc);
    yc = c;
    if i > period {
        sum -= f64::abs(in_data[(i - period) as usize] - in_data[(i - period - 1) as usize]);
    }
    bar = c;

    if maxi < trail {
        maxi = trail;
        max = in_data[maxi as usize];
        j = trail;
        let mut j_temp = j + 1;
        while j_temp <= i {
            bar = in_data[j_temp as usize];
            if bar >= max {
                max = bar;
                maxi = j_temp;
            }
            j_temp += 1;
        }
    } else if bar >= max {
        maxi = i;
        max = bar;
    }

    bar = c;
    if mini < trail {
        mini = trail;
        min = in_data[mini as usize];
        j = trail;
        let mut j_temp = j + 1;
        while j_temp <= i {
            bar = in_data[j_temp as usize];
            if bar <= min {
                min = bar;
                mini = j_temp;
            }
            j_temp += 1;
        }
    } else if bar <= min {
        mini = i;
        min = bar;
    }

    output[output_idx as usize] = f64::abs(max - min) / sum;
    output_idx += 1;

    *output_idx_ref = output_idx;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *bar_ref = bar;
    *sum_ref = sum;
    *j_ref = j;
    *yc_ref = yc;
    *c_ref = c;
}
pub fn ti_vhf(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for null inputs/outputs (Option::None)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let mut outputs = outputs.ok_or(1)?;

    let in_data = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Err(1);
    }

    let start = ti_vhf_start(Some(options));
    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    let mut trail = 1;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = in_data[0];
    let mut min = in_data[0];
    let mut bar = 0.0;
    let mut sum = 0.0;
    let mut yc = in_data[0];
    let mut c = in_data[0];  // Initialize c with first value

    // First loop: calculate initial sum
    for i in 1..period as usize {
        c = in_data[i];
        sum += f64::abs(c - yc);
        yc = c;
    }

    // Second loop: process with helper function
    for i in period..size {
        let mut j = 0; // Initialize j for each iteration
        helper_ti_vhf_1(
            &mut output_idx,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut bar,
            &mut sum,
            &mut j,
            &mut yc,
            &mut c,
            in_data,
            period,
            output,
            trail,
            i,
        );
        trail += 1;
    }

    // Assertion check (Rust's assert! macro)
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);

    Ok(())
}
