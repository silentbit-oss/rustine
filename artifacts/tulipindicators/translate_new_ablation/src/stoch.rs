use crate::*;
use rand::Rng;

pub fn ti_stoch_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.len() < 3 {
        return None;
    }
    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;
    Some((kperiod + kslow + dperiod) - 3)
}
pub fn ti_stoch(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;
    let kper = 1.0 / kslow as f64;
    let dper = 1.0 / dperiod as f64;
    
    // Use split_at_mut to safely get mutable references to both output slices
    let (first, second) = outputs.split_at_mut(1);
    let stoch = &mut first[0];
    let stoch_ma = &mut second[0];
    
    if kperiod < 1 {
        return 1;
    }
    if kslow < 1 {
        return 1;
    }
    if dperiod < 1 {
        return 1;
    }
    
    let start = ti_stoch_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max_val = high[0];
    let mut min_val = low[0];
    let mut bar;
    
    let mut k_sum = TiBuffer {
        size: kslow,
        pushes: 0,
        index: 0,
        sum: 0.0,
        vals: vec![0.0; kslow as usize],
    };
    let mut d_sum = TiBuffer {
        size: dperiod,
        pushes: 0,
        index: 0,
        sum: 0.0,
        vals: vec![0.0; dperiod as usize],
    };
    
    let mut stoch_idx = 0;
    let mut stoch_ma_idx = 0;
    
    for i in 0..size as usize {
        if i >= kperiod as usize {
            trail += 1;
        }
        
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
        
        let kdiff = max_val - min_val;
        let kfast = if kdiff == 0.0 {
            0.0
        } else {
            100.0 * ((close[i] - min_val) / kdiff)
        };
        
        // Push kfast to k_sum buffer
        if k_sum.pushes >= k_sum.size {
            k_sum.sum -= k_sum.vals[k_sum.index as usize];
        }
        k_sum.sum += kfast;
        k_sum.vals[k_sum.index as usize] = kfast;
        k_sum.pushes += 1;
        k_sum.index += 1;
        if k_sum.index >= k_sum.size {
            k_sum.index = 0;
        }
        
        if i >= (((kperiod - 1) + kslow) - 1) as usize {
            let k = k_sum.sum * kper;
            
            // Push k to d_sum buffer
            if d_sum.pushes >= d_sum.size {
                d_sum.sum -= d_sum.vals[d_sum.index as usize];
            }
            d_sum.sum += k;
            d_sum.vals[d_sum.index as usize] = k;
            d_sum.pushes += 1;
            d_sum.index += 1;
            if d_sum.index >= d_sum.size {
                d_sum.index = 0;
            }
            
            if i >= (((((kperiod - 1) + kslow) - 1) + dperiod) - 1) as usize {
                stoch[stoch_idx] = k;
                stoch_idx += 1;
                stoch_ma[stoch_ma_idx] = d_sum.sum * dper;
                stoch_ma_idx += 1;
            }
        }
    }
    
    assert!((stoch_idx as i32) == (size - ti_stoch_start(Some(options)).unwrap_or(0)));
    assert!((stoch_ma_idx as i32) == (size - ti_stoch_start(Some(options)).unwrap_or(0)));
    
    0
}
