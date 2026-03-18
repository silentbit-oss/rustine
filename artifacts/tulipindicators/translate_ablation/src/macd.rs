use crate::*;
use rand::Rng;

fn ti_macd_start(options: Option<&[f64]>) -> Option<i32> {
    let opts = options?;
    if opts.len() < 2 {
        return None;
    }
    let long_period = opts[1] as i32;
    Some(long_period - 1)
}
pub fn ti_macd(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None values in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Check if inputs and outputs have sufficient length
    if inputs.len() < 1 || outputs.len() < 3 {
        return 1;
    }
    
    let input = inputs[0];
    
    // Use split_at_mut to safely get multiple mutable references
    let (first, rest) = outputs.split_at_mut(1);
    let (second, third) = rest.split_at_mut(1);
    
    let macd = &mut first[0];
    let signal = &mut second[0];
    let hist = &mut third[0];
    
    // Check if options has sufficient length
    if options.len() < 3 {
        return 1;
    }
    
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let signal_period = options[2] as i32;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < 2 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    if signal_period < 1 {
        return 1;
    }
    
    let start = match ti_macd_start(Some(options)) {
        Some(val) => val,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut short_per = 2.0 / (short_period as f64 + 1.0);
    let mut long_per = 2.0 / (long_period as f64 + 1.0);
    let signal_per = 2.0 / (signal_period as f64 + 1.0);
    
    if short_period == 12 && long_period == 26 {
        short_per = 0.15;
        long_per = 0.075;
    }
    
    let mut short_ema = input[0];
    let mut long_ema = input[0];
    let mut signal_ema = 0.0;
    
    let mut macd_idx = 0;
    let mut signal_idx = 0;
    let mut hist_idx = 0;
    
    for i in 1..size as usize {
        short_ema = ((input[i] - short_ema) * short_per) + short_ema;
        long_ema = ((input[i] - long_ema) * long_per) + long_ema;
        let out = short_ema - long_ema;
        
        if i == (long_period - 1) as usize {
            signal_ema = out;
        }
        
        if i >= (long_period - 1) as usize {
            signal_ema = ((out - signal_ema) * signal_per) + signal_ema;
            
            if macd_idx < macd.len() {
                macd[macd_idx] = out;
                macd_idx += 1;
            }
            
            if signal_idx < signal.len() {
                signal[signal_idx] = signal_ema;
                signal_idx += 1;
            }
            
            if hist_idx < hist.len() {
                hist[hist_idx] = out - signal_ema;
                hist_idx += 1;
            }
        }
    }
    
    let expected_len = (size - start) as usize;
    assert!(macd_idx == expected_len);
    assert!(signal_idx == expected_len);
    assert!(hist_idx == expected_len);
    
    0
}
