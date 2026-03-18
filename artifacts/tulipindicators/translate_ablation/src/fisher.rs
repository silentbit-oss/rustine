use crate::*;
use std::f64::consts::LN_2;

pub fn ti_fisher_start(options: Option<&[f64]>) -> Option<i32> {
    let opts = options?;
    let first = opts.first()?;
    Some(*first as i32 - 1)
}
pub fn ti_fisher(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_fisher_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    // Use split_at_mut to safely get mutable references to both outputs
    let (fisher_slice, signal_slice) = outputs.split_at_mut(1);
    let fisher = &mut fisher_slice[0];
    let signal = &mut signal_slice[0];
    
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max_val = 0.5 * (high[0] + low[0]);
    let mut min_val = 0.5 * (high[0] + low[0]);
    let mut val1 = 0.0;
    let mut fish = 0.0;
    
    let mut fisher_idx = 0;
    let mut signal_idx = 0;
    
    for i in (period - 1)..size {
        let mut bar = 0.5 * (high[i as usize] + low[i as usize]);
        
        if maxi < trail {
            maxi = trail;
            max_val = 0.5 * (high[maxi as usize] + low[maxi as usize]);
            let mut j = trail;
            while j <= i {
                bar = 0.5 * (high[j as usize] + low[j as usize]);
                if bar >= max_val {
                    max_val = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max_val {
            maxi = i;
            max_val = bar;
        }
        
        bar = 0.5 * (high[i as usize] + low[i as usize]);
        
        if mini < trail {
            mini = trail;
            min_val = 0.5 * (high[mini as usize] + low[mini as usize]);
            let mut j = trail;
            while j <= i {
                bar = 0.5 * (high[j as usize] + low[j as usize]);
                if bar <= min_val {
                    min_val = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min_val {
            mini = i;
            min_val = bar;
        }
        
        let mm = max_val - min_val;
        let mm = if mm == 0.0 { 0.001 } else { mm };
        
        val1 = ((0.33 * 2.0) * (((0.5 * (high[i as usize] + low[i as usize]) - min_val) / mm) - 0.5)) + (0.67 * val1);
        
        if val1 > 0.99 {
            val1 = 0.999;
        }
        if val1 < -0.99 {
            val1 = -0.999;
        }
        
        signal[signal_idx] = fish;
        signal_idx += 1;
        
        fish = (0.5 * ((1.0 + val1) / (1.0 - val1)).ln()) + (0.5 * fish);
        
        fisher[fisher_idx] = fish;
        fisher_idx += 1;
        
        trail += 1;
    }
    
    let expected_len = (size - start) as usize;
    assert!(fisher_idx == expected_len);
    assert!(signal_idx == expected_len);
    
    0
}
