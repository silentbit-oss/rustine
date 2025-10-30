use crate::*;
use std::assert;

pub fn ti_mass_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
    if options.is_empty() {
        return None;
    }

    let sum_p = options[0] as i32 - 1;
    Some(16 + sum_p)
}
pub fn helper_ti_mass_1(
    output_idx_ref: &mut u32,
    ema_ref: &mut f64,
    ema2_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    period: i32,
    output: &mut [f64],
    per: f64,
    per1: f64,
    sum: &mut TiBuffer,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut ema = *ema_ref;
    let mut ema2 = *ema2_ref;
    let hl = high[i as usize] - low[i as usize];
    
    ema = (ema * per1) + (hl * per);
    
    if i == 8 {
        ema2 = ema;
    }
    
    if i >= 8 {
        ema2 = (ema2 * per1) + (ema * per);
        
        if i >= 16 {
            if sum.pushes >= sum.size {
                sum.sum -= sum.vals[sum.index as usize];
            }
            let ratio = ema / ema2;
            sum.sum += ratio;
            sum.vals[sum.index as usize] = ratio;
            sum.pushes += 1;
            sum.index += 1;
            if sum.index >= sum.size {
                sum.index = 0;
            }
            
            if i >= (16 + period - 1) {
                output[output_idx as usize] = sum.sum;
                output_idx += 1;
            }
        }
    }
    
    *output_idx_ref = output_idx;
    *ema_ref = ema;
    *ema2_ref = ema2;
}

pub fn ti_mass(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> Result<(), i32> {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 1 {
        return Err(1);
    }

    let start = match ti_mass_start(Some(options)) {
        Some(s) => s,
        None => return Err(0),
    };

    if size <= start {
        return Err(0);
    }

    let per = 2.0 / (9.0 + 1.0);
    let per1 = 1.0 - per;
    let mut ema = high[0] - low[0];
    let mut ema2 = ema;

    let mut sum = match ti_buffer_new(period) {
        Some(s) => s,
        None => return Err(1),
    };

    for i in 0..size {
        helper_ti_mass_1(
            &mut output_idx,
            &mut ema,
            &mut ema2,
            high,
            low,
            period,
            output,
            per,
            per1,
            &mut sum,
            i,
        );
    }

    ti_buffer_free(*sum);

    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);
    Ok(())
}
