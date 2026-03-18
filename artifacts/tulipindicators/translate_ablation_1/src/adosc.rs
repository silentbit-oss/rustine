use crate::*;
use rand::Rng;

pub fn ti_adosc_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => {
            if opts.len() > 1 {
                (opts[1] as i32) - 1
            } else {
                -1 // Return -1 if options array doesn't have enough elements
            }
        }
        None => -1, // Return -1 if options is None (equivalent to NULL pointer)
    }
}
pub fn ti_adosc(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let start = long_period - 1;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    if size <= ti_adosc_start(Some(options)) {
        return 0;
    }
    
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);
    let output = &mut outputs[0];
    let mut sum = 0.0;
    let mut short_ema = 0.0;
    let mut long_ema = 0.0;
    let mut output_idx = 0;
    
    for i in 0..size as usize {
        let hl = high[i] - low[i];
        if hl != 0.0 {
            sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
        }
        if i == 0 {
            short_ema = sum;
            long_ema = sum;
        } else {
            short_ema = ((sum - short_ema) * short_per) + short_ema;
            long_ema = ((sum - long_ema) * long_per) + long_ema;
        }
        if i >= start as usize {
            output[output_idx] = short_ema - long_ema;
            output_idx += 1;
        }
    }
    
    0
}
