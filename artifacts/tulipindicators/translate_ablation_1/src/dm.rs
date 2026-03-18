use crate::*;
use std::assert;

pub fn ti_dm_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}
pub fn ti_dm(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start_index = match ti_dm_start(Some(options)) {
        Some(idx) => idx,
        None => return 0,
    };
    
    if size <= start_index {
        return 0;
    }
    
    let per = ((period as f64) - 1.0) / (period as f64);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    
    // Use split_at_mut to get non-overlapping mutable slices
    let (plus_dm_slice, rest) = outputs.split_at_mut(1);
    let plus_dm = &mut plus_dm_slice[0];
    let minus_dm = &mut rest[0];
    
    let mut plus_dm_idx = 0;
    let mut minus_dm_idx = 0;

    for i in 1..period {
        let (dp, dm) = {
            let mut dp = high[i as usize] - high[(i - 1) as usize];
            let mut dm = low[(i - 1) as usize] - low[i as usize];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            (dp, dm)
        };
        
        dmup += dp;
        dmdown += dm;
    }
    
    plus_dm[plus_dm_idx] = dmup;
    plus_dm_idx += 1;
    minus_dm[minus_dm_idx] = dmdown;
    minus_dm_idx += 1;
    
    for i in period..size {
        let (dp, dm) = {
            let i_usize = i as usize;
            let mut dp = high[i_usize] - high[(i - 1) as usize];
            let mut dm = low[(i - 1) as usize] - low[i_usize];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            (dp, dm)
        };
        
        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;
        
        plus_dm[plus_dm_idx] = dmup;
        plus_dm_idx += 1;
        minus_dm[minus_dm_idx] = dmdown;
        minus_dm_idx += 1;
    }
    
    let plus_dm_written = plus_dm_idx;
    let minus_dm_written = minus_dm_idx;
    let expected = (size - start_index) as usize;
    
    assert!(plus_dm_written == expected);
    assert!(minus_dm_written == expected);
    
    0
}
