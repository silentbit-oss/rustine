use crate::*;
use rand::Rng;

pub fn ti_min_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => (opts[0] as i32) - 1,
        None => 0, // Return a default value when no options are provided
    }
}

pub fn ti_min(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_min_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut trail = 0;
    let mut mini = -1;
    let mut min = input[0];
    let mut output_idx = 0;
    
    let mut i = period - 1;
    while i < size {
        let bar = input[i as usize];
        
        if mini < trail {
            mini = trail;
            min = input[mini as usize];
            let mut j = trail;
            
            while j <= i {
                let current_bar = input[j as usize];
                if current_bar <= min {
                    min = current_bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min {
            mini = i;
            min = bar;
        }
        
        output[output_idx] = min;
        output_idx += 1;
        
        i += 1;
        trail += 1;
    }
    
    assert!((output_idx as i32) == (size - ti_min_start(Some(options))));
    0
}

pub fn ti_min_ref(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let min_start = ti_min_start(Some(options));
    if size <= min_start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in (period - 1)..size {
        let mut min_val = input[((i - period) + 1) as usize];
        
        for j in ((i - period) + 2)..=i {
            let current_val = input[j as usize];
            if current_val < min_val {
                min_val = current_val;
            }
        }
        
        output[output_idx] = min_val;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - ti_min_start(Some(options))));
    0
}
