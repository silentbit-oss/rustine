use crate::*;

pub fn ti_qstick_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => opts[0] as i32 - 1,
        None => -1, // Return -1 if options is None (equivalent to NULL in C)
    }
}
pub fn ti_qstick(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let open = inputs[0];
    let close = inputs[1];
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let period = options[0] as i32;
    let scale = 1.0 / period as f64;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_qstick_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let mut sum = 0.0;
    for i in 0..period as usize {
        sum += close[i] - open[i];
    }
    
    output[output_idx] = sum * scale;
    output_idx += 1;
    
    for i in period as usize..size as usize {
        sum += close[i] - open[i];
        sum -= close[i - period as usize] - open[i - period as usize];
        output[output_idx] = sum * scale;
        output_idx += 1;
    }
    
    debug_assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - outputs[0].as_ptr() as usize == 
                 ((size - start) as usize * std::mem::size_of::<f64>()));
    
    0
}
