use crate::*;
use rand::Rng;

pub fn ti_macd_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_macd_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least 2 elements to safely access options[1]
    if options.len() < 2 {
        return None;
    }

    let long_period = options[1] as i32;
    Some(long_period - 1)
}
pub fn ti_macd(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_macd");
    // Early return if any required parameter is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get input slice
    let input = inputs[0];

    // Split outputs into separate mutable references
    let (first, rest) = outputs.split_at_mut(1);
    let macd = &mut first[0];
    
    let (second, third) = rest.split_at_mut(1);
    let signal = &mut second[0];
    let hist = &mut third[0];

    // Initialize indices
    let mut macd_idx = 0;
    let mut signal_idx = 0;
    let mut hist_idx = 0;

    // Extract periods from options
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let signal_period = options[2] as i32;

    // Validate periods
    if short_period < 1 || long_period < 2 || long_period < short_period || signal_period < 1 {
        return Some(1);
    }

    // Check if size is sufficient
    if let Some(start) = ti_macd_start(Some(options)) {
        if size <= start {
            return Some(0);
        }
    }

    // Calculate periods
    let mut short_per = 2.0 / (short_period as f64 + 1.0);
    let mut long_per = 2.0 / (long_period as f64 + 1.0);
    let signal_per = 2.0 / (signal_period as f64 + 1.0);

    // Special case for standard MACD periods
    if short_period == 12 && long_period == 26 {
        short_per = 0.15;
        long_per = 0.075;
    }

    // Initialize EMAs
    let mut short_ema = input[0];
    let mut long_ema = input[0];
    let mut signal_ema = 0.0;

    // Process each input value
    for i in 1..size as usize {
        short_ema = ((input[i] - short_ema) * short_per) + short_ema;
        long_ema = ((input[i] - long_ema) * long_per) + long_ema;
        let out = short_ema - long_ema;

        if i == (long_period - 1) as usize {
            signal_ema = out;
        }

        if i >= (long_period - 1) as usize {
            signal_ema = ((out - signal_ema) * signal_per) + signal_ema;
            macd[macd_idx] = out;
            macd_idx += 1;
            signal[signal_idx] = signal_ema;
            signal_idx += 1;
            hist[hist_idx] = out - signal_ema;
            hist_idx += 1;
        }
    }

    Some(0)
}
