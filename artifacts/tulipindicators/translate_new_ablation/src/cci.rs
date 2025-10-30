use crate::*;
use std::f64;

pub fn ti_cci_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    let period = options[0] as i32;
    Some((period - 1) * 2)
}

pub fn ti_cci(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_cci_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let output_slice = &mut outputs[0];
    let mut output_idx = 0;
    
    let mut sum = TiBuffer {
        size: period,
        pushes: 0,
        index: 0,
        sum: 0.0,
        vals: vec![0.0; period as usize],
    };
    
    for i in 0..size as usize {
        let today = (high[i] + low[i] + close[i]) * (1.0 / 3.0);
        
        if sum.pushes >= sum.size {
            sum.sum -= sum.vals[sum.index as usize];
        }
        sum.sum += today;
        sum.vals[sum.index as usize] = today;
        sum.pushes += 1;
        sum.index += 1;
        if sum.index >= sum.size {
            sum.index = 0;
        }
        
        let avg = sum.sum * scale;
        
        if i >= ((period * 2) - 2) as usize {
            let mut acc = 0.0;
            for j in 0..period as usize {
                acc += f64::abs(avg - sum.vals[j]);
            }
            
            let mut cci = acc * scale;
            cci *= 0.015;
            cci = (today - avg) / cci;
            
            output_slice[output_idx] = cci;
            output_idx += 1;
        }
    }
    
    assert!((output_idx as i32) == (size - ti_cci_start(Some(options)).unwrap_or(0)));
    0
}
