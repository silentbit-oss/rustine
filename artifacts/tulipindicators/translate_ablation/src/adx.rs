use crate::*;
use std::f64;

pub fn ti_adx_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|op| op.first().map(|x| (*x as i32 - 1) * 2))
}

pub fn ti_adx(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 2 {
        return 1;
    }
    
    let start = ti_adx_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let per = ((period as f64) - 1.0) / (period as f64);
    let invper = 1.0 / (period as f64);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    
    for i in 1..period {
        let dp;
        let dm;
        {
            let mut temp_dp = high[i as usize] - high[(i - 1) as usize];
            let mut temp_dm = low[(i - 1) as usize] - low[i as usize];
            
            if temp_dp < 0.0 {
                temp_dp = 0.0;
            } else if temp_dp > temp_dm {
                temp_dm = 0.0;
            }
            
            if temp_dm < 0.0 {
                temp_dm = 0.0;
            } else if temp_dm > temp_dp {
                temp_dp = 0.0;
            }
            
            dp = temp_dp;
            dm = temp_dm;
        }
        
        dmup += dp;
        dmdown += dm;
    }
    
    let mut adx = 0.0;
    {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        adx += dx;
    }
    
    let mut output_idx = 0;
    for i in period..size {
        let dp;
        let dm;
        {
            let mut temp_dp = high[i as usize] - high[(i - 1) as usize];
            let mut temp_dm = low[(i - 1) as usize] - low[i as usize];
            
            if temp_dp < 0.0 {
                temp_dp = 0.0;
            } else if temp_dp > temp_dm {
                temp_dm = 0.0;
            }
            
            if temp_dm < 0.0 {
                temp_dm = 0.0;
            } else if temp_dm > temp_dp {
                temp_dp = 0.0;
            }
            
            dp = temp_dp;
            dm = temp_dm;
        }
        
        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;
        
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        
        let i_minus_period = i - period;
        if i_minus_period < (period - 2) {
            adx += dx;
        } else if i_minus_period == (period - 2) {
            adx += dx;
            output[output_idx] = adx * invper;
            output_idx += 1;
        } else {
            adx = (adx * per) + dx;
            output[output_idx] = adx * invper;
            output_idx += 1;
        }
    }
    
    0
}
