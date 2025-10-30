use crate::*;
use rand::Rng;

pub fn ti_mass_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    let sum_p = options[0] as i32 - 1;
    Some(16 + sum_p)
}

pub fn ti_mass(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start_index = ti_mass_start(Some(options)).unwrap_or(0);
    if size <= start_index {
        return 0;
    }
    
    let per = 2.0 / (9.0 + 1.0);
    let per1 = 1.0 - per;
    let mut ema = high[0] - low[0];
    let mut ema2 = ema;
    
    let mut sum = ti_buffer_new(period).unwrap();
    let mut output_idx = 0;
    
    for i in 0..size as usize {
        let hl = high[i] - low[i];
        ema = (ema * per1) + (hl * per);
        
        if i == 8 {
            ema2 = ema;
        }
        
        if i >= 8 {
            ema2 = (ema2 * per1) + (ema * per);
            
            if i >= 16 {
                if sum.pushes >= sum.size {
                    sum.sum -= sum.vals[sum.index as usize];
                }
                sum.sum += ema / ema2;
                sum.vals[sum.index as usize] = ema / ema2;
                sum.pushes += 1;
                sum.index = sum.index + 1;
                if sum.index >= sum.size {
                    sum.index = 0;
                }
                
                if i >= ((16 + period as usize) - 1) {
                    output[output_idx] = sum.sum;
                    output_idx += 1;
                }
            }
        }
    }
    
    ti_buffer_free(*sum);
    assert!((output_idx as i32) == (size - ti_mass_start(Some(options)).unwrap_or(0)));
    0
}
