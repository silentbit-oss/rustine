use crate::*;
use std::assert;
use std::f64;

pub fn ti_kvo_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}

pub fn helper_ti_kvo_1(
    output_idx_ref: &mut u32,
    cm_ref: &mut f64,
    prev_hlc_ref: &mut f64,
    trend_ref: &mut i32,
    short_ema_ref: &mut f64,
    long_ema_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    volume: &[f64],
    short_per: f64,
    long_per: f64,
    output: &mut [f64],
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut cm = *cm_ref;
    let mut prev_hlc = *prev_hlc_ref;
    let mut trend = *trend_ref;
    let mut short_ema = *short_ema_ref;
    let mut long_ema = *long_ema_ref;

    let hlc = (high[i] + low[i]) + close[i];
    let dm = high[i] - low[i];

    if (hlc > prev_hlc) && (trend != 1) {
        trend = 1;
        cm = high[i - 1] - low[i - 1];
    } else if (hlc < prev_hlc) && (trend != 0) {
        trend = 0;
        cm = high[i - 1] - low[i - 1];
    }

    cm += dm;
    let vf = ((volume[i] * f64::abs(((dm / cm) * 2.0) - 1.0)) * 100.0) * if trend != 0 { 1.0 } else { -1.0 };

    if i == 1 {
        short_ema = vf;
        long_ema = vf;
    } else {
        short_ema = ((vf - short_ema) * short_per) + short_ema;
        long_ema = ((vf - long_ema) * long_per) + long_ema;
    }

    output[output_idx as usize] = short_ema - long_ema;
    output_idx += 1;
    prev_hlc = hlc;

    *output_idx_ref = output_idx;
    *cm_ref = cm;
    *prev_hlc_ref = prev_hlc;
    *trend_ref = trend;
    *short_ema_ref = short_ema;
    *long_ema_ref = long_ema;
}

pub fn ti_kvo(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    if size <= ti_kvo_start(Some(&options[0])) {
        return 0;
    }
    
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);
    
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let mut cm = 0.0;
    let mut prev_hlc = high[0] + low[0] + close[0];
    let mut trend = -1;
    let mut short_ema = 0.0;
    let mut long_ema = 0.0;
    
    for i in 1..size as usize {
        helper_ti_kvo_1(
            &mut output_idx,
            &mut cm,
            &mut prev_hlc,
            &mut trend,
            &mut short_ema,
            &mut long_ema,
            high,
            low,
            close,
            volume,
            short_per,
            long_per,
            output,
            i,
        );
    }
    
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - ti_kvo_start(Some(&options[0]))) as f64);
    
    0
}
