use crate::*;
use std::assert;
use std::f64;

pub fn ti_cci_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    Some((period - 1) * 2)
}

pub fn helper_ti_cci_1(
    output_idx_ref: &mut u32,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    period: i32,
    scale: f64,
    output: &mut [f64],
    sum: &mut TiBuffer,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut j = *j_ref;
    let today = ((high[i as usize] + low[i as usize]) + close[i as usize]) * (1.0 / 3.0);

    {
        if sum.pushes >= sum.size {
            sum.sum -= sum.vals[sum.index as usize];
        }
        sum.sum += today;
        sum.vals[sum.index as usize] = today;
        sum.pushes += 1;
        sum.index += 1;
        if sum.index >= sum.size {
            sum.index = 0;
        }
    }

    let avg = sum.sum * scale;
    if i >= ((period * 2) - 2) {
        let mut acc = 0.0;
        for j_val in 0..period {
            acc += f64::abs(avg - sum.vals[j_val as usize]);
        }

        let mut cci = acc * scale;
        cci *= 0.015;
        cci = (today - avg) / cci;
        output[output_idx as usize] = cci;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *j_ref = j;
}

pub fn ti_cci(
    size: i32,
    inputs: &[&[f64]],
    options: Option<&[f64]>,
    outputs: &mut [&mut [f64]],
) -> Option<i32> {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    
    let options = options?;
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return Some(1);
    }
    
    let start = ti_cci_start(Some(options))?;
    if size <= start {
        return Some(0);
    }
    
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let mut sum = ti_buffer_new(period)?;
    
    for i in 0..size {
        helper_ti_cci_1(
            &mut output_idx,
            &mut 0, // j is initialized to 0 in C code (line 20)
            high,
            low,
            close,
            period,
            scale,
            output,
            &mut sum,
            i,
        );
    }
    
    ti_buffer_free(*sum);
    
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);
    Some(0)
}
