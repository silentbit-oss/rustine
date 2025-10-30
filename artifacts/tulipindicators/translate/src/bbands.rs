use crate::*;
use libm::sqrt;

pub fn ti_bbands_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL check in C)
    // and if the slice has at least one element
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32 - 1,
        _ => -1, // Return -1 for NULL or empty slice (common error value in C)
    }
}

pub fn helper_ti_bbands_1(
    lower_idx_ref: &mut u32,
    middle_idx_ref: &mut u32,
    upper_idx_ref: &mut u32,
    sum_ref: &mut f64,
    sum2_ref: &mut f64,
    sd_ref: &mut f64,
    input: &[f64],
    lower: &mut [f64],
    middle: &mut [f64],
    upper: &mut [f64],
    period: i32,
    stddev: f64,
    scale: f64,
    i: usize,
) {
    let mut lower_idx = *lower_idx_ref;
    let mut middle_idx = *middle_idx_ref;
    let mut upper_idx = *upper_idx_ref;
    let mut sum = *sum_ref;
    let mut sum2 = *sum2_ref;
    let mut sd = *sd_ref;

    sum += input[i];
    sum2 += input[i] * input[i];
    sum -= input[i - period as usize];
    sum2 -= input[i - period as usize] * input[i - period as usize];

    sd = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale)));

    middle[middle_idx as usize] = sum * scale;
    upper[upper_idx as usize] = middle[middle_idx as usize] + (stddev * sd);
    upper_idx += 1;
    lower[lower_idx as usize] = middle[middle_idx as usize] - (stddev * sd);
    lower_idx += 1;
    middle_idx += 1;

    *lower_idx_ref = lower_idx;
    *middle_idx_ref = middle_idx;
    *upper_idx_ref = upper_idx;
    *sum_ref = sum;
    *sum2_ref = sum2;
    *sd_ref = sd;
}
pub fn ti_bbands(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let input = inputs[0];
    
    // Use split_at_mut to safely get mutable references to different output slices
    let (first, rest) = outputs.split_at_mut(1);
    let lower = &mut first[0];
    let mut lower_idx = 0;
    
    let (middle_slice, upper_slice) = rest.split_at_mut(1);
    let middle = &mut middle_slice[0];
    let mut middle_idx = 0;
    
    let upper = &mut upper_slice[0];
    let mut upper_idx = 0;
    
    let period = options[0] as i32;
    let stddev = options[1];
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    if size <= ti_bbands_start(Some(options)) {
        return 0;
    }
    
    let mut sum = 0.0;
    let mut sum2 = 0.0;
    
    for i in 0..period as usize {
        sum += input[i];
        sum2 += input[i] * input[i];
    }
    
    let mut sd = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale)));
    middle[middle_idx as usize] = sum * scale;
    lower[lower_idx as usize] = middle[middle_idx as usize] - (stddev * sd);
    lower_idx += 1;
    upper[upper_idx as usize] = middle[middle_idx as usize] + (stddev * sd);
    upper_idx += 1;
    middle_idx += 1;
    
    for i in period as usize..size as usize {
        helper_ti_bbands_1(
            &mut lower_idx,
            &mut middle_idx,
            &mut upper_idx,
            &mut sum,
            &mut sum2,
            &mut sd,
            input,
            lower,
            middle,
            upper,
            period,
            stddev,
            scale,
            i,
        );
    }
    
    assert!(lower_idx as isize == (size - ti_bbands_start(Some(options))) as isize);
    assert!(middle_idx as isize == (size - ti_bbands_start(Some(options))) as isize);
    assert!(upper_idx as isize == (size - ti_bbands_start(Some(options))) as isize);
    
    0
}
