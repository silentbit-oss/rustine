use crate::*;
use rand::Rng;

pub fn ti_wad_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}

pub fn ti_wad(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    
    if size <= ti_wad_start(options) {
        return 0;
    }
    
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let mut sum = 0.0;
    let mut yc = close[0];
    
    for i in 1..size as usize {
        let c = close[i];
        if c > yc {
            sum += c - if yc < low[i] { yc } else { low[i] };
        } else if c < yc {
            sum += c - if yc > high[i] { yc } else { high[i] };
        }
        
        output[output_idx] = sum;
        output_idx += 1;
        yc = close[i];
    }
    
    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>() - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_wad_start(options)) as usize);
    0
}
