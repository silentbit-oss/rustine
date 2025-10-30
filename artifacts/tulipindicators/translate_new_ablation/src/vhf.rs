use crate::*;
use libm::fabs;
use rand::Rng;
pub fn ti_vhf_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 if options is None or empty
    }
}
pub fn ti_vhf(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let mut outputs = outputs.unwrap();
    
    // Check if inputs and outputs arrays have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let in_arr = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_vhf_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut trail = 1;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max_val = in_arr[0];
    let mut min_val = in_arr[0];
    let mut bar;
    let mut sum = 0.0;
    let mut yc = in_arr[0];
    let mut c;
    
    // Initialize sum with absolute differences for the first period
    for i in 1..period as usize {
        c = in_arr[i];
        sum += f64::abs(c - yc);
        yc = c;
    }
    
    let mut output_idx = 0;
    for i in period as usize..size as usize {
        c = in_arr[i];
        sum += f64::abs(c - yc);
        yc = c;
        
        if i > period as usize {
            sum -= f64::abs(in_arr[i - period as usize] - in_arr[(i - period as usize) - 1]);
        }
        
        bar = c;
        
        // Update maximum tracking
        if maxi < trail {
            maxi = trail;
            max_val = in_arr[maxi as usize];
            let mut j = trail + 1;
            while j <= i as i32 {
                bar = in_arr[j as usize];
                if bar >= max_val {
                    max_val = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max_val {
            maxi = i as i32;
            max_val = bar;
        }
        
        bar = c;
        
        // Update minimum tracking
        if mini < trail {
            mini = trail;
            min_val = in_arr[mini as usize];
            let mut j = trail + 1;
            while j <= i as i32 {
                bar = in_arr[j as usize];
                if bar <= min_val {
                    min_val = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min_val {
            mini = i as i32;
            min_val = bar;
        }
        
        // Calculate and store the result
        output[output_idx] = f64::abs(max_val - min_val) / sum;
        output_idx += 1;
        trail += 1;
    }
    
    // The assert from C is omitted in safe Rust as it would panic
    // assert!((output_idx as i32) == (size - ti_vhf_start(Some(options))));
    
    0
}
