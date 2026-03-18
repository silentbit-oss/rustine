use crate::*;
use std::f64;
pub fn ti_natr_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_natr(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_natr_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let per = 1.0 / (period as f64);
    let mut sum = 0.0;
    
    sum += high[0] - low[0];
    
    for i in 1..period {
        let l = low[i as usize];
        let h = high[i as usize];
        let c = close[(i - 1) as usize];
        let ych = f64::abs(h - c);
        let ycl = f64::abs(l - c);
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        
        let truerange = v;
        sum += truerange;
    }
    
    let mut val = sum / (period as f64);
    output[0] = (100.0 * val) / close[(period - 1) as usize];
    
    for i in period..size {
        let idx = i as usize;
        let l = low[idx];
        let h = high[idx];
        let c = close[(i - 1) as usize];
        let ych = f64::abs(h - c);
        let ycl = f64::abs(l - c);
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        
        let truerange = v;
        val = ((truerange - val) * per) + val;
        output[(i - period + 1) as usize] = (100.0 * val) / close[idx];
    }
    
    // Note: Rust's assert! is only active in debug builds by default
    // This matches the C behavior where asserts are typically disabled in release builds
    debug_assert!((output.len() as i32 - (size - start)) >= 0);
    
    0
}
