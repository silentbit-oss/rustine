use crate::*;
use std::f64;

pub fn ti_adxr_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(((options[0] as i32) - 1) * 3)
}
pub fn ti_adxr(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };
    
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 2 {
        return 1;
    }
    
    let first_adxr = match ti_adxr_start(Some(options)) {
        Some(f) => f,
        None => return 1,
    };
    if size <= first_adxr {
        return 0;
    }
    
    let per = (period as f64 - 1.0) / period as f64;
    let invper = 1.0 / period as f64;
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
    
    let adxr_ptr = unsafe { ti_buffer_new((period - 1) as i32) };
    let mut adxr = match adxr_ptr {
        Some(ptr) => ptr,
        None => return 1,
    };
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
        
        dmup = dmup * per + dp;
        dmdown = dmdown * per + dm;
        
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        
        let i_minus_period = i - period;
        
        if i_minus_period < period - 2 {
            adx += dx;
        } else if i_minus_period == period - 2 {
            adx += dx;
            unsafe {
                (*adxr).vals[(*adxr).index as usize] = adx * invper;
                (*adxr).index = ((*adxr).index + 1) % (*adxr).size;
            }
        } else {
            adx = adx * per + dx;
            
            if i >= first_adxr {
                unsafe {
                    // Get the previous value from the circular buffer
                    let prev_index = if (*adxr).index == 0 {
                        (*adxr).size - 1
                    } else {
                        (*adxr).index - 1
                    };
                    let adxr_val = (*adxr).vals[prev_index as usize];
                    output[output_idx] = 0.5 * ((adx * invper) + adxr_val);
                    output_idx += 1;
                }
            }
            
            unsafe {
                (*adxr).vals[(*adxr).index as usize] = adx * invper;
                (*adxr).index = ((*adxr).index + 1) % (*adxr).size;
            }
        }
    }
    
    unsafe {
        ti_buffer_free(*adxr);
    }
    
    assert!(output_idx == (size - first_adxr) as usize);
    0
}
