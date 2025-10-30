use crate::*;
use rand::Rng;

pub fn ti_stochrsi_start(options: Option<&[f64]>) -> Option<i32> {
    let options = options?;
    let first = options.first()?;
    Some((*first as i32) * 2 - 1)
}

pub fn ti_stochrsi(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let per = 1.0 / (period as f64);
    
    if period < 2 {
        return 1;
    }
    
    let start = ti_stochrsi_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let mut rsi = ti_buffer_new(period).unwrap();
    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;
    
    for i in 1..=period {
        let upward = if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        let downward = if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };
        smooth_up += upward;
        smooth_down += downward;
    }
    
    smooth_up /= period as f64;
    smooth_down /= period as f64;
    let mut r = 100.0 * (smooth_up / (smooth_up + smooth_down));
    
    {
        if rsi.pushes >= rsi.size {
            rsi.sum -= rsi.vals[rsi.index as usize];
        }
        rsi.sum += r;
        rsi.vals[rsi.index as usize] = r;
        rsi.pushes += 1;
        rsi.index += 1;
        if rsi.index >= rsi.size {
            rsi.index = 0;
        }
    }
    
    let mut min = r;
    let mut max = r;
    let mut mini = 0;
    let mut maxi = 0;
    let mut output_idx = 0;
    
    for i in (period + 1)..size {
        let i_usize = i as usize;
        let upward = if input[i_usize] > input[i_usize - 1] {
            input[i_usize] - input[i_usize - 1]
        } else {
            0.0
        };
        let downward = if input[i_usize] < input[i_usize - 1] {
            input[i_usize - 1] - input[i_usize]
        } else {
            0.0
        };
        
        smooth_up = ((upward - smooth_up) * per) + smooth_up;
        smooth_down = ((downward - smooth_down) * per) + smooth_down;
        r = 100.0 * (smooth_up / (smooth_up + smooth_down));
        
        if r > max {
            max = r;
            maxi = rsi.index;
        } else if maxi == rsi.index {
            max = r;
            for j in 0..rsi.size {
                if j == rsi.index {
                    continue;
                }
                if rsi.vals[j as usize] > max {
                    max = rsi.vals[j as usize];
                    maxi = j;
                }
            }
        }
        
        if r < min {
            min = r;
            mini = rsi.index;
        } else if mini == rsi.index {
            min = r;
            for j in 0..rsi.size {
                if j == rsi.index {
                    continue;
                }
                if rsi.vals[j as usize] < min {
                    min = rsi.vals[j as usize];
                    mini = j;
                }
            }
        }
        
        {
            rsi.vals[rsi.index as usize] = r;
            rsi.index += 1;
            if rsi.index >= rsi.size {
                rsi.index = 0;
            }
        }
        
        if i > ((period * 2) - 2) {
            let diff = max - min;
            if diff == 0.0 {
                output[output_idx] = 0.0;
            } else {
                output[output_idx] = (r - min) / diff;
            }
            output_idx += 1;
        }
    }
    
    ti_buffer_free(*rsi);
    assert!((output_idx as i32) == (size - start));
    0
}
