use crate::*;
use rand::Rng;

pub fn ti_dema_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    let period = options[0] as i32;
    Some((period - 1) * 2)
}

pub fn ti_dema(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = match ti_dema_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    let per1 = 1.0 - per;
    
    let mut ema = input[0];
    let mut ema2 = ema;
    let mut output_idx = 0;
    
    for i in 0..size as usize {
        ema = (ema * per1) + (input[i] * per);
        
        if i == (period - 1) as usize {
            ema2 = ema;
        }
        
        if i >= (period - 1) as usize {
            ema2 = (ema2 * per1) + (ema * per);
            
            if i >= ((period - 1) * 2) as usize {
                output[output_idx] = (ema * 2.0) - ema2;
                output_idx += 1;
            }
        }
    }
    
    assert!((output_idx as i32) == (size - start));
    0
}
