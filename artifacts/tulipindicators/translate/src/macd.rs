use crate::*;
use std::assert;

pub fn ti_macd_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;

    // Ensure the slice has at least 2 elements (since we access index 1)
    if options.len() < 2 {
        return None;
    }

    let long_period = options[1] as i32;
    Some(long_period - 1)
}
pub fn helper_ti_macd_1(
    macd_idx_ref: &mut u32,
    signal_idx_ref: &mut u32,
    hist_idx_ref: &mut u32,
    short_ema_ref: &mut f64,
    long_ema_ref: &mut f64,
    signal_ema_ref: &mut f64,
    input: &[f64],
    macd: &mut [f64],
    signal: &mut [f64],
    hist: &mut [f64],
    long_period: i32,
    short_per: f64,
    long_per: f64,
    signal_per: f64,
    i: i32,
) {
    let mut macd_idx = *macd_idx_ref;
    let mut signal_idx = *signal_idx_ref;
    let mut hist_idx = *hist_idx_ref;
    let mut short_ema = *short_ema_ref;
    let mut long_ema = *long_ema_ref;
    let mut signal_ema = *signal_ema_ref;

    short_ema = ((input[i as usize] - short_ema) * short_per) + short_ema;
    long_ema = ((input[i as usize] - long_ema) * long_per) + long_ema;
    let out = short_ema - long_ema;

    if i == (long_period - 1) {
        signal_ema = out;
    }

    if i >= (long_period - 1) {
        signal_ema = ((out - signal_ema) * signal_per) + signal_ema;
        macd[macd_idx as usize] = out;
        macd_idx += 1;
        signal[signal_idx as usize] = signal_ema;
        signal_idx += 1;
        hist[hist_idx as usize] = out - signal_ema;
        hist_idx += 1;
    }

    *macd_idx_ref = macd_idx;
    *signal_idx_ref = signal_idx;
    *hist_idx_ref = hist_idx;
    *short_ema_ref = short_ema;
    *long_ema_ref = long_ema;
    *signal_ema_ref = signal_ema;
}
pub fn ti_macd(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Early return if any input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let input = inputs[0];
    let (macd_slice, rest) = outputs.split_at_mut(1);
    let macd = &mut macd_slice[0];
    let mut macd_idx = 0;
    let (signal_slice, hist_slice) = rest.split_at_mut(1);
    let signal = &mut signal_slice[0];
    let mut signal_idx = 0;
    let hist = &mut hist_slice[0];
    let mut hist_idx = 0;

    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    let signal_period = options[2] as i32;

    // Validation checks
    if short_period < 1 || long_period < 2 || long_period < short_period || signal_period < 1 {
        return Some(1);
    }

    let start = ti_macd_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let mut short_per = 2.0 / (short_period as f64 + 1.0);
    let mut long_per = 2.0 / (long_period as f64 + 1.0);
    let signal_per = 2.0 / (signal_period as f64 + 1.0);

    // Special case for standard MACD periods
    if short_period == 12 && long_period == 26 {
        short_per = 0.15;
        long_per = 0.075;
    }

    let mut short_ema = input[0];
    let mut long_ema = input[0];
    let mut signal_ema = 0.0;

    for i in 1..size {
        helper_ti_macd_1(
            &mut macd_idx,
            &mut signal_idx,
            &mut hist_idx,
            &mut short_ema,
            &mut long_ema,
            &mut signal_ema,
            input,
            macd,
            signal,
            hist,
            long_period,
            short_per,
            long_per,
            signal_per,
            i,
        );
    }

    // Assertions (converted to debug_assert! since they're for debugging)
    debug_assert!((macd[macd_idx as usize] - macd[0]) == (size - start) as f64);
    debug_assert!((signal[signal_idx as usize] - signal[0]) == (size - start) as f64);
    debug_assert!((hist[hist_idx as usize] - hist[0]) == (size - start) as f64);

    Some(0)
}
