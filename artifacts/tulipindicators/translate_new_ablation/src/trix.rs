use crate::*;
use rand::Rng;

pub fn ti_trix_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        opts.first().map(|&x| {
            let period = x as i32;
            ((period - 1) * 3) + 1
        })
    })
}

pub fn ti_trix(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let mut outputs = outputs.unwrap();
    
    // Check if inputs and outputs arrays have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let ti_trix_start_result = ti_trix_start(Some(options));
    if ti_trix_start_result.is_none() {
        return 1;
    }
    let trix_start = ti_trix_start_result.unwrap();
    
    if size <= trix_start {
        return 0;
    }
    
    let start = (period * 3) - 2;
    assert!(start == trix_start);
    let per = 2.0 / (period as f64 + 1.0);
    
    let mut ema1 = input[0];
    let mut ema2 = 0.0;
    let mut ema3 = 0.0;
    
    // First loop: calculate initial EMA values
    for i in 1..start as usize {
        ema1 = ((input[i] - ema1) * per) + ema1;
        
        if i == (period - 1) as usize {
            ema2 = ema1;
        } else if i > (period - 1) as usize {
            ema2 = ((ema1 - ema2) * per) + ema2;
            
            if i == ((period * 2) - 2) as usize {
                ema3 = ema2;
            } else if i > ((period * 2) - 2) as usize {
                ema3 = ((ema2 - ema3) * per) + ema3;
            }
        }
    }
    
    // Second loop: calculate and store output values
    let mut output_idx = 0;
    for i in start as usize..size as usize {
        ema1 = ((input[i] - ema1) * per) + ema1;
        ema2 = ((ema1 - ema2) * per) + ema2;
        let last = ema3;
        ema3 = ((ema2 - ema3) * per) + ema3;
        
        output[output_idx] = ((ema3 - last) / ema3) * 100.0;
        output_idx += 1;
    }
    
    assert!((output_idx as i32) == (size - trix_start));
    0
}
