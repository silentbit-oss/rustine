use crate::*;
use std::f64;

pub fn ti_di_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}
pub fn ti_di(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start_index = match ti_di_start(Some(options)) {
        Some(idx) => idx,
        None => return 0,
    };
    
    if size <= start_index {
        return 0;
    }
    
    let per = ((period as f64) - 1.0) / (period as f64);
    let mut atr = 0.0;
    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    
    // Split outputs to get mutable references to both slices
    let (plus_di_slice, minus_di_slice) = {
        let (first, second) = outputs.split_at_mut(1);
        (&mut first[0], &mut second[0])
    };
    
    let mut plus_di_idx = 0;
    let mut minus_di_idx = 0;
    
    for i in 1..period as usize {
        let truerange = {
            let l = low[i];
            let h = high[i];
            let c = close[i - 1];
            let ych = f64::abs(h - c);
            let ycl = f64::abs(l - c);
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };
        
        atr += truerange;
        
        let (dp, dm) = {
            let mut dp_val = high[i] - high[i - 1];
            let mut dm_val = low[i - 1] - low[i];
            
            if dp_val < 0.0 {
                dp_val = 0.0;
            } else if dp_val > dm_val {
                dm_val = 0.0;
            }
            
            if dm_val < 0.0 {
                dm_val = 0.0;
            } else if dm_val > dp_val {
                dp_val = 0.0;
            }
            
            (dp_val, dm_val)
        };
        
        dmup += dp;
        dmdown += dm;
    }
    
    plus_di_slice[plus_di_idx] = (100.0 * dmup) / atr;
    plus_di_idx += 1;
    minus_di_slice[minus_di_idx] = (100.0 * dmdown) / atr;
    minus_di_idx += 1;
    
    for i in period as usize..size as usize {
        let truerange = {
            let l = low[i];
            let h = high[i];
            let c = close[i - 1];
            let ych = f64::abs(h - c);
            let ycl = f64::abs(l - c);
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };
        
        atr = (atr * per) + truerange;
        
        let (dp, dm) = {
            let mut dp_val = high[i] - high[i - 1];
            let mut dm_val = low[i - 1] - low[i];
            
            if dp_val < 0.0 {
                dp_val = 0.0;
            } else if dp_val > dm_val {
                dm_val = 0.0;
            }
            
            if dm_val < 0.0 {
                dm_val = 0.0;
            } else if dm_val > dp_val {
                dp_val = 0.0;
            }
            
            (dp_val, dm_val)
        };
        
        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;
        
        plus_di_slice[plus_di_idx] = (100.0 * dmup) / atr;
        plus_di_idx += 1;
        minus_di_slice[minus_di_idx] = (100.0 * dmdown) / atr;
        minus_di_idx += 1;
    }
    
    assert!((plus_di_idx as i32) == (size - start_index));
    assert!((minus_di_idx as i32) == (size - start_index));
    
    0
}
