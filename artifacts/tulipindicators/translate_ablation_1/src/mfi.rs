use crate::*;
use std::error::Error;

pub fn ti_mfi_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0, // Return 0 for NULL or empty options (safe default)
    }
}

pub fn ti_mfi(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }
    let start = ti_mfi_start(Some(options));
    if size <= start {
        return 0;
    }
    let output = &mut outputs[0];
    let mut ytyp = ((high[0] + low[0]) + close[0]) * (1.0 / 3.0);
    
    // Manual implementation of rolling buffers instead of TiBuffer
    let mut up_vals = vec![0.0; period as usize];
    let mut down_vals = vec![0.0; period as usize];
    let mut up_index = 0;
    let mut down_index = 0;
    let mut up_pushes = 0;
    let mut down_pushes = 0;
    let mut up_sum = 0.0;
    let mut down_sum = 0.0;
    
    let mut output_index = 0;
    
    for i in 1..size as usize {
        let typ = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
        let bar = typ * volume[i];
        
        if typ > ytyp {
            // Update up buffer
            if up_pushes >= period as usize {
                up_sum -= up_vals[up_index];
            }
            up_sum += bar;
            up_vals[up_index] = bar;
            up_pushes += 1;
            up_index = (up_index + 1) % period as usize;
            
            // Update down buffer with 0.0
            if down_pushes >= period as usize {
                down_sum -= down_vals[down_index];
            }
            down_sum += 0.0;
            down_vals[down_index] = 0.0;
            down_pushes += 1;
            down_index = (down_index + 1) % period as usize;
        } else if typ < ytyp {
            // Update down buffer
            if down_pushes >= period as usize {
                down_sum -= down_vals[down_index];
            }
            down_sum += bar;
            down_vals[down_index] = bar;
            down_pushes += 1;
            down_index = (down_index + 1) % period as usize;
            
            // Update up buffer with 0.0
            if up_pushes >= period as usize {
                up_sum -= up_vals[up_index];
            }
            up_sum += 0.0;
            up_vals[up_index] = 0.0;
            up_pushes += 1;
            up_index = (up_index + 1) % period as usize;
        } else {
            // Update both buffers with 0.0
            if up_pushes >= period as usize {
                up_sum -= up_vals[up_index];
            }
            up_sum += 0.0;
            up_vals[up_index] = 0.0;
            up_pushes += 1;
            up_index = (up_index + 1) % period as usize;
            
            if down_pushes >= period as usize {
                down_sum -= down_vals[down_index];
            }
            down_sum += 0.0;
            down_vals[down_index] = 0.0;
            down_pushes += 1;
            down_index = (down_index + 1) % period as usize;
        }
        
        ytyp = typ;
        
        if i >= period as usize {
            let ratio = up_sum / (up_sum + down_sum);
            output[output_index] = ratio * 100.0;
            output_index += 1;
        }
    }
    
    assert!((output_index as i32) == (size - ti_mfi_start(Some(options))));
    0
}
