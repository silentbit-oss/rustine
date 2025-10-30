use crate::*;
use rand::Rng;

pub fn ti_fosc_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 for NULL or empty options (safe default)
    }
}

pub fn ti_fosc(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_fosc_start(Some(options));
    if size <= start {
        return 0;
    }
    
    {
        let mut x = 0.0;
        let mut x2 = 0.0;
        let mut y = 0.0;
        let mut xy = 0.0;
        let p = 1.0 / period as f64;
        let mut tsf = 0.0;
        
        for i in 0..(period - 1) {
            let weight = (i + 1) as f64;
            x += weight;
            x2 += weight * weight;
            xy += input[i as usize] * weight;
            y += input[i as usize];
        }
        
        let period_f64 = period as f64;
        x += period_f64;
        x2 += period_f64 * period_f64;
        let bd = 1.0 / ((period_f64 * x2) - (x * x));
        
        let mut output_idx = 0;
        for i in (period - 1)..size {
            let i_usize = i as usize;
            xy += input[i_usize] * period_f64;
            y += input[i_usize];
            
            let b = ((period_f64 * xy) - (x * y)) * bd;
            
            {
                let a = (y - (b * x)) * p;
                if i >= period {
                    outputs[0][output_idx] = (100.0 * (input[i_usize] - tsf)) / input[i_usize];
                    output_idx += 1;
                }
                tsf = a + (b * (period_f64 + 1.0));
            }
            
            xy -= y;
            let prev_index = (i - period + 1) as usize;
            y -= input[prev_index];
        }
        
        assert!((output_idx as i32) == (size - start));
    }
    
    0
}
