use crate::*;
use rand::Rng;
use std::slice;

pub fn ti_aroonosc_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => opts[0] as i32,
        None => 0,
    }
}

pub unsafe fn ti_aroonosc(size: i32, inputs: *const *const f64, options: *const f64, outputs: *mut *mut f64) -> i32 {
    if inputs.is_null() || outputs.is_null() {
        return 1;
    }
    
    let high = slice::from_raw_parts(*inputs.offset(0), size as usize);
    let low = slice::from_raw_parts(*inputs.offset(1), size as usize);
    let mut output_ptr = *outputs.offset(0);
    
    if options.is_null() {
        return 1;
    }
    let options_slice = slice::from_raw_parts(options, 1);
    if options_slice.is_empty() {
        return 1;
    }
    let period = options_slice[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_aroonosc_start(Some(&[period as f64]));
    if size <= start {
        return 0;
    }
    
    let scale = 100.0 / (period as f64);
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    
    let size_usize = size as usize;
    let period_usize = period as usize;
    
    for i in period..size {
        let i_usize = i as usize;
        let bar_high = high[i_usize];
        
        if maxi < trail {
            maxi = trail;
            let maxi_usize = maxi as usize;
            max = high[maxi_usize];
            let mut j = trail + 1;
            while j <= i {
                let j_usize = j as usize;
                let bar = high[j_usize];
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar_high >= max {
            maxi = i;
            max = bar_high;
        }
        
        let bar_low = low[i_usize];
        
        if mini < trail {
            mini = trail;
            let mini_usize = mini as usize;
            min = low[mini_usize];
            let mut j = trail + 1;
            while j <= i {
                let j_usize = j as usize;
                let bar = low[j_usize];
                if bar <= min {
                    min = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar_low <= min {
            mini = i;
            min = bar_low;
        }
        
        if !output_ptr.is_null() {
            *output_ptr = ((maxi - mini) as f64) * scale;
            output_ptr = output_ptr.offset(1);
        }
        
        trail += 1;
    }
    
    0
}
