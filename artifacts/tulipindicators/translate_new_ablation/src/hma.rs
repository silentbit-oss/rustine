use crate::*;
use libm::sqrt;
use rand::Rng;


pub fn ti_hma_start(options: Option<&[f64]>) -> Option<std::os::raw::c_int> {
    let options = options?;
    if options.is_empty() {
        return None;
    }
    let period = options[0] as std::os::raw::c_int;
    let periodsqrt = (period as f64).sqrt() as std::os::raw::c_int;
    Some((period + periodsqrt) - 2)
}

pub fn ti_hma(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_hma_start(Some(options)).unwrap_or(0);
    if size <= start {
        return 0;
    }
    
    let period2 = (period / 2) as i32;
    let periodsqrt = (f64::sqrt(period as f64)) as i32;
    let weights = (period * (period + 1)) as f64 / 2.0;
    let weights2 = (period2 * (period2 + 1)) as f64 / 2.0;
    let weightssqrt = (periodsqrt * (periodsqrt + 1)) as f64 / 2.0;
    
    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    let mut sum2 = 0.0;
    let mut weight_sum2 = 0.0;
    let mut sumsqrt = 0.0;
    let mut weight_sumsqrt = 0.0;
    
    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * (i + 1) as f64;
        sum += input[i];
        
        if i >= (period - period2) as usize {
            weight_sum2 += input[i] * ((i + 1) - (period - period2) as usize) as f64;
            sum2 += input[i];
        }
    }
    
    let mut buff = Vec::with_capacity(periodsqrt as usize);
    let mut buff_index = 0;
    
    for i in (period - 1) as usize..size as usize {
        weight_sum += input[i] * period as f64;
        sum += input[i];
        weight_sum2 += input[i] * period2 as f64;
        sum2 += input[i];
        
        let wma = weight_sum / weights;
        let wma2 = weight_sum2 / weights2;
        let diff = (2.0 * wma2) - wma;
        
        weight_sumsqrt += diff * periodsqrt as f64;
        sumsqrt += diff;
        
        if buff.len() < periodsqrt as usize {
            buff.push(diff);
        } else {
            buff[buff_index] = diff;
        }
        buff_index = (buff_index + 1) % periodsqrt as usize;
        
        if i >= ((period - 1) + (periodsqrt - 1)) as usize {
            output[0] = weight_sumsqrt / weightssqrt;
            
            weight_sumsqrt -= sumsqrt;
            let remove_index = (buff_index + periodsqrt as usize - 1) % periodsqrt as usize;
            sumsqrt -= buff[remove_index];
        } else {
            weight_sumsqrt -= sumsqrt;
        }
        
        weight_sum -= sum;
        sum -= input[i - period as usize + 1];
        weight_sum2 -= sum2;
        sum2 -= input[i - period2 as usize + 1];
    }
    
    0
}
