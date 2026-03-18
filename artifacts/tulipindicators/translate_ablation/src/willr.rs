use crate::*;
use rand::Rng;

pub fn ti_willr_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    Some(options[0] as i32 - 1)
}

pub fn ti_willr(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_willr_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max_val = high[0];
    let mut min_val = low[0];
    let mut bar;
    
    let mut output_idx = 0;
    
    for i in (period - 1) as usize..size as usize {
        bar = high[i];
        if maxi < trail {
            maxi = trail;
            max_val = high[maxi as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = high[j as usize];
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
        
        bar = low[i];
        if mini < trail {
            mini = trail;
            min_val = low[mini as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = low[j as usize];
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
        
        let highlow = max_val - min_val;
        let r = if highlow == 0.0 {
            0.0
        } else {
            -100.0 * ((max_val - close[i]) / highlow)
        };
        
        output[output_idx] = r;
        output_idx += 1;
        trail += 1;
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
