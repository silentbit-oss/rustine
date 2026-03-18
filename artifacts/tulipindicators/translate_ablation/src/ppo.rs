use crate::*;
use rand::Rng;

pub fn ti_ppo_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    1
}

pub fn ti_ppo(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let ppo = &mut outputs[0];
    
    let short_period = options[0] as i32;
    let long_period = options[1] as i32;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < 2 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    
    let start_index = ti_ppo_start(Some(options));
    if size <= start_index {
        return 0;
    }
    
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);
    
    let mut short_ema = input[0];
    let mut long_ema = input[0];
    
    let mut output_idx = 0;
    for i in 1..size as usize {
        short_ema = ((input[i] - short_ema) * short_per) + short_ema;
        long_ema = ((input[i] - long_ema) * long_per) + long_ema;
        
        let out = (100.0 * (short_ema - long_ema)) / long_ema;
        ppo[output_idx] = out;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - start_index));
    0
}
