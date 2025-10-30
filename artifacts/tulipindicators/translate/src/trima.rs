use crate::*;
use std::assert;

pub fn ti_trima_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}
pub fn helper_ti_trima_1(
    output_idx_ref: &mut u32,
    weight_sum_ref: &mut f64,
    lead_sum_ref: &mut f64,
    trail_sum_ref: &mut f64,
    lsi_ref: &mut i32,
    tsi1_ref: &mut i32,
    tsi2_ref: &mut i32,
    input: &[f64],
    output: &mut [f64],
    weights: f64,
    i: usize,
) {
    let output_idx = *output_idx_ref;
    let mut weight_sum = *weight_sum_ref;
    let mut lead_sum = *lead_sum_ref;
    let mut trail_sum = *trail_sum_ref;
    let mut lsi = *lsi_ref;
    let mut tsi1 = *tsi1_ref;
    let mut tsi2 = *tsi2_ref;

    weight_sum += input[i];
    output[output_idx as usize] = weight_sum * weights;
    
    let new_output_idx = output_idx + 1;
    lead_sum += input[i];
    weight_sum += lead_sum;
    weight_sum -= trail_sum;
    lead_sum -= input[lsi as usize];
    lsi += 1;
    trail_sum += input[tsi1 as usize];
    tsi1 += 1;
    trail_sum -= input[tsi2 as usize];
    tsi2 += 1;

    *output_idx_ref = new_output_idx;
    *weight_sum_ref = weight_sum;
    *lead_sum_ref = lead_sum;
    *trail_sum_ref = trail_sum;
    *lsi_ref = lsi;
    *tsi1_ref = tsi1;
    *tsi2_ref = tsi2;
}
pub fn ti_trima(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    mut outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Early return if any required input is None
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return 1,
    };
    let period = match options {
        Some(options) => options[0] as i32,
        None => return 1,
    };
    let output_mut = match outputs.as_mut() {
        Some(outputs) => &mut outputs[0],
        None => return 1,
    };

    let mut output_idx = 0;
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_trima_start(options) {
        Some(start) => start,
        None => return 0,
    };
    
    if size <= start {
        return 0;
    }
    
    if period <= 2 {
        return ti_sma(size, inputs, options, outputs);
    }
    
    let weights = if period % 2 != 0 {
        let half = (period / 2) + 1;
        1.0 / (half * half) as f64
    } else {
        let half = period / 2;
        1.0 / ((half + 1) * half) as f64
    };
    
    let mut weight_sum = 0.0;
    let mut lead_sum = 0.0;
    let mut trail_sum = 0.0;
    
    let lead_period = if period % 2 != 0 {
        period / 2
    } else {
        (period / 2) - 1
    };
    let trail_period = lead_period + 1;
    
    let mut w = 1;
    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * w as f64;
        
        if (i + 1) > (period - lead_period) as usize {
            lead_sum += input[i];
        }
        
        if (i + 1) <= trail_period as usize {
            trail_sum += input[i];
        }
        
        if (i + 1) < trail_period as usize {
            w += 1;
        }
        
        if (i + 1) >= (period - lead_period) as usize {
            w -= 1;
        }
    }
    
    let mut lsi = ((period - 1) - lead_period) + 1;
    let mut tsi1 = (((period - 1) - period) + 1) + trail_period;
    let mut tsi2 = ((period - 1) - period) + 1;
    
    for i in (period - 1) as usize..size as usize {
        helper_ti_trima_1(
            &mut output_idx,
            &mut weight_sum,
            &mut lead_sum,
            &mut trail_sum,
            &mut lsi,
            &mut tsi1,
            &mut tsi2,
            input,
            output_mut,
            weights,
            i,
        );
    }
    
    assert!((output_mut[output_idx as usize] - output_mut[0]) == (size - start) as f64);
    0
}
