use crate::*;
use std::assert;

pub fn ti_aroon_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => {
            if opts.is_empty() {
                0
            } else {
                opts[0] as i32
            }
        }
        None => 0,
    }
}
pub fn ti_aroon(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let (adown_slice, aup_slice) = outputs.split_at_mut(1);
    let adown = &mut adown_slice[0];
    let aup = &mut aup_slice[0];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_aroon_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let scale = 100.0 / period as f64;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max_val = high[0];
    let mut min_val = low[0];
    let mut bar;
    
    let mut adown_idx = 0;
    let mut aup_idx = 0;
    
    for i in period as usize..size as usize {
        bar = high[i];
        if maxi < trail {
            maxi = trail;
            max_val = high[maxi as usize];
            let mut j = trail;
            while j < i as i32 {
                j += 1;
                bar = high[j as usize];
                if bar >= max_val {
                    max_val = bar;
                    maxi = j;
                }
            }
        } else if bar >= max_val {
            maxi = i as i32;
            max_val = bar;
        }
        
        bar = low[i];
        if mini < trail {
            mini = trail;
            min_val = low[mini as usize];
            let mut j = trail;
            while j < i as i32 {
                j += 1;
                bar = low[j as usize];
                if bar <= min_val {
                    min_val = bar;
                    mini = j;
                }
            }
        } else if bar <= min_val {
            mini = i as i32;
            min_val = bar;
        }
        
        adown[adown_idx] = ((period - (i as i32 - mini)) as f64) * scale;
        adown_idx += 1;
        
        aup[aup_idx] = ((period - (i as i32 - maxi)) as f64) * scale;
        aup_idx += 1;
        
        trail += 1;
    }
    
    let expected_len = (size - start) as usize;
    assert!(adown_idx == expected_len);
    assert!(aup_idx == expected_len);
    
    0
}
