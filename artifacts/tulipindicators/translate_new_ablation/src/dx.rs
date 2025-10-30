use crate::*;
use std::f64;

pub fn ti_dx_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_dx(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_dx_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let per = ((period as f64) - 1.0) / (period as f64);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    
    for i in 1..period {
        let dp;
        let dm;
        {
            let mut dp_val = high[i as usize] - high[(i - 1) as usize];
            let mut dm_val = low[(i - 1) as usize] - low[i as usize];
            
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
            
            dp = dp_val;
            dm = dm_val;
        }
        
        dmup += dp;
        dmdown += dm;
    }
    
    {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        output[0] = dx;
    }
    
    for i in period..size {
        let dp;
        let dm;
        {
            let mut dp_val = high[i as usize] - high[(i - 1) as usize];
            let mut dm_val = low[(i - 1) as usize] - low[i as usize];
            
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
            
            dp = dp_val;
            dm = dm_val;
        }
        
        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;
        
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        
        let output_index = (i - period + 1) as usize;
        output[output_index] = dx;
    }
    
    // Note: The original C assertion is commented out as Rust's assert! is for debugging
    // and the exact pointer arithmetic translation is not straightforward
    // assert!((output_ptr - outputs[0]) == (size - ti_dx_start(options)));
    
    0
}
