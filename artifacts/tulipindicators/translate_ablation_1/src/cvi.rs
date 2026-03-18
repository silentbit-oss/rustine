use crate::*;
use rand::Rng;

pub fn ti_cvi_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    let n = options[0] as i32;
    Some((n * 2) - 1)
}

pub fn ti_cvi(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start_index = ti_cvi_start(Some(options)).unwrap_or(0);
    if size <= start_index {
        return 0;
    }
    
    let per = 2.0 / (period as f64 + 1.0);
    let mut lag = ti_buffer_new(period).unwrap();
    let mut val = high[0] - low[0];
    
    for i in 1..((period * 2) - 1) as usize {
        val = ((high[i] - low[i]) - val) * per + val;
        
        {
            lag.vals[lag.index as usize] = val;
            lag.index += 1;
            if lag.index >= lag.size {
                lag.index = 0;
            }
        }
    }
    
    let mut output_idx = 0;
    for i in ((period * 2) - 1) as usize..size as usize {
        val = ((high[i] - low[i]) - val) * per + val;
        let old = lag.vals[lag.index as usize];
        
        output[output_idx] = 100.0 * (val - old) / old;
        output_idx += 1;
        
        {
            lag.vals[lag.index as usize] = val;
            lag.index += 1;
            if lag.index >= lag.size {
                lag.index = 0;
            }
        }
    }
    
    ti_buffer_free(*lag);
    assert!((output_idx as i32) == (size - ti_cvi_start(Some(options)).unwrap_or(0)));
    0
}
