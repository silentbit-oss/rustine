use crate::*;
use rand::Rng;

pub fn ti_cmo_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 for NULL or empty options (safe default)
    }
}

pub fn ti_cmo(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let output = &mut outputs[0];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_cmo_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut up_sum = 0.0;
    let mut down_sum = 0.0;
    
    for i in 1..=period {
        let i_usize = i as usize;
        up_sum += if input[i_usize] > input[i_usize - 1] {
            input[i_usize] - input[i_usize - 1]
        } else {
            0.0
        };
        down_sum += if input[i_usize] < input[i_usize - 1] {
            input[i_usize - 1] - input[i_usize]
        } else {
            0.0
        };
    }
    
    output[0] = (100.0 * (up_sum - down_sum)) / (up_sum + down_sum);
    
    let mut output_idx = 1;
    for i in (period + 1)..size {
        let i_usize = i as usize;
        let prev_period_idx = i_usize - period as usize;
        
        up_sum -= if input[prev_period_idx] > input[prev_period_idx - 1] {
            input[prev_period_idx] - input[prev_period_idx - 1]
        } else {
            0.0
        };
        down_sum -= if input[prev_period_idx] < input[prev_period_idx - 1] {
            input[prev_period_idx - 1] - input[prev_period_idx]
        } else {
            0.0
        };
        
        up_sum += if input[i_usize] > input[i_usize - 1] {
            input[i_usize] - input[i_usize - 1]
        } else {
            0.0
        };
        down_sum += if input[i_usize] < input[i_usize - 1] {
            input[i_usize - 1] - input[i_usize]
        } else {
            0.0
        };
        
        output[output_idx] = (100.0 * (up_sum - down_sum)) / (up_sum + down_sum);
        output_idx += 1;
    }
    
    assert!((output_idx) == (size - ti_cmo_start(Some(options))) as usize);
    0
}
