use crate::*;

pub fn ti_ultosc_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (NULL in C) or if it doesn't have at least 3 elements
    match options {
        Some(opts) if opts.len() >= 3 => opts[2] as i32,
        _ => 0, // Default return value when options is None or too short
    }
}
pub fn helper_helper_ti_ultosc_1_1(
    bp_short_sum_ref: &mut f64,
    bp_medium_sum_ref: &mut f64,
    r_short_sum_ref: &mut f64,
    r_medium_sum_ref: &mut f64,
    short_period: i32,
    medium_period: i32,
    long_period: i32,
    bp_buf: &TiBuffer,
    r_buf: &TiBuffer,
    i: i32,
) {
    let mut bp_short_sum = *bp_short_sum_ref;
    let mut bp_medium_sum = *bp_medium_sum_ref;
    let mut r_short_sum = *r_short_sum_ref;
    let mut r_medium_sum = *r_medium_sum_ref;

    let mut short_index = (bp_buf.index - short_period) - 1;
    if short_index < 0 {
        short_index += long_period;
    }
    bp_short_sum -= bp_buf.vals[short_index as usize];
    r_short_sum -= r_buf.vals[short_index as usize];

    if i > medium_period {
        let mut medium_index = (bp_buf.index - medium_period) - 1;
        if medium_index < 0 {
            medium_index += long_period;
        }
        bp_medium_sum -= bp_buf.vals[medium_index as usize];
        r_medium_sum -= r_buf.vals[medium_index as usize];
    }

    *bp_short_sum_ref = bp_short_sum;
    *bp_medium_sum_ref = bp_medium_sum;
    *r_short_sum_ref = r_short_sum;
    *r_medium_sum_ref = r_medium_sum;
}
pub fn helper_ti_ultosc_1(
    output_idx_ref: &mut u32,
    bp_short_sum_ref: &mut f64,
    bp_medium_sum_ref: &mut f64,
    r_short_sum_ref: &mut f64,
    r_medium_sum_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    short_period: i32,
    medium_period: i32,
    long_period: i32,
    output: &mut [f64],
    bp_buf: &mut TiBuffer,
    r_buf: &mut TiBuffer,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut bp_short_sum = *bp_short_sum_ref;
    let mut bp_medium_sum = *bp_medium_sum_ref;
    let mut r_short_sum = *r_short_sum_ref;
    let mut r_medium_sum = *r_medium_sum_ref;

    let true_low = if low[i as usize] < close[(i - 1) as usize] {
        low[i as usize]
    } else {
        close[(i - 1) as usize]
    };
    let true_high = if high[i as usize] > close[(i - 1) as usize] {
        high[i as usize]
    } else {
        close[(i - 1) as usize]
    };
    let bp = close[i as usize] - true_low;
    let r = true_high - true_low;

    bp_short_sum += bp;
    bp_medium_sum += bp;
    r_short_sum += r;
    r_medium_sum += r;

    // Process bp_buf
    {
        if bp_buf.pushes >= bp_buf.size {
            bp_buf.sum -= bp_buf.vals[bp_buf.index as usize];
        }
        bp_buf.sum += bp;
        bp_buf.vals[bp_buf.index as usize] = bp;
        bp_buf.pushes += 1;
        bp_buf.index += 1;
        if bp_buf.index >= bp_buf.size {
            bp_buf.index = 0;
        }
    }

    // Process r_buf
    {
        if r_buf.pushes >= r_buf.size {
            r_buf.sum -= r_buf.vals[r_buf.index as usize];
        }
        r_buf.sum += r;
        r_buf.vals[r_buf.index as usize] = r;
        r_buf.pushes += 1;
        r_buf.index += 1;
        if r_buf.index >= r_buf.size {
            r_buf.index = 0;
        }
    }

    if i > short_period {
        helper_helper_ti_ultosc_1_1(
            &mut bp_short_sum,
            &mut bp_medium_sum,
            &mut r_short_sum,
            &mut r_medium_sum,
            short_period,
            medium_period,
            long_period,
            bp_buf,
            r_buf,
            i,
        );
    }

    if i >= long_period {
        let first = (4.0 * bp_short_sum) / r_short_sum;
        let second = (2.0 * bp_medium_sum) / r_medium_sum;
        let third = bp_buf.sum / r_buf.sum;
        let ult = ((first + second + third) * 100.0) / 7.0;
        output[output_idx as usize] = ult;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *bp_short_sum_ref = bp_short_sum;
    *bp_medium_sum_ref = bp_medium_sum;
    *r_short_sum_ref = r_short_sum;
    *r_medium_sum_ref = r_medium_sum;
}
pub fn ti_ultosc(
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
    let close = inputs[2];
    
    let short_period = options[0] as i32;
    let medium_period = options[1] as i32;
    let long_period = options[2] as i32;
    
    let output = &mut outputs[0];
    let mut output_idx = 0;

    // Validation checks
    if short_period < 1 {
        return 1;
    }
    if medium_period < short_period {
        return 1;
    }
    if long_period < medium_period {
        return 1;
    }

    let start = ti_ultosc_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut bp_buf = match ti_buffer_new(long_period) {
        Some(buf) => buf,
        None => return 1,
    };
    let mut r_buf = match ti_buffer_new(long_period) {
        Some(buf) => buf,
        None => return 1,
    };

    let mut bp_short_sum = 0.0;
    let mut bp_medium_sum = 0.0;
    let mut r_short_sum = 0.0;
    let mut r_medium_sum = 0.0;

    for i in 1..size {
        helper_ti_ultosc_1(
            &mut output_idx,
            &mut bp_short_sum,
            &mut bp_medium_sum,
            &mut r_short_sum,
            &mut r_medium_sum,
            high,
            low,
            close,
            short_period,
            medium_period,
            long_period,
            output,
            &mut bp_buf,
            &mut r_buf,
            i,
        );
    }

    ti_buffer_free(*bp_buf);
    ti_buffer_free(*r_buf);

    // Assertion check
    assert!((&output[output_idx as usize] as *const f64 as isize - outputs[0].as_ptr() as isize) / std::mem::size_of::<f64>() as isize == (size - start) as isize);

    0
}
