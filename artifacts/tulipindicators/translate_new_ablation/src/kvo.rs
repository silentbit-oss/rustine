use crate::*;
use rand::Rng;

#[no_mangle]
pub extern "C" fn ti_kvo_start(options: Option<*const f64>) -> i32 {
    let _ = options;
    1
}
pub fn ti_kvo(size: i32, inputs: Option<*const *const f64>, options: Option<*const f64>, outputs: Option<*const *mut f64>) -> i32 {
    let inputs_ptr = match inputs {
        Some(ptr) => ptr,
        None => return 1,
    };
    let options = match options {
        Some(ptr) => ptr,
        None => return 1,
    };
    let outputs_ptr = match outputs {
        Some(ptr) => ptr,
        None => return 1,
    };

    let high = unsafe { *inputs_ptr.offset(0) };
    let low = unsafe { *inputs_ptr.offset(1) };
    let close = unsafe { *inputs_ptr.offset(2) };
    let volume = unsafe { *inputs_ptr.offset(3) };
    
    let short_period = unsafe { *options.offset(0) } as i32;
    let long_period = unsafe { *options.offset(1) } as i32;
    
    if short_period < 1 {
        return 1;
    }
    if long_period < short_period {
        return 1;
    }
    
    let start_index = ti_kvo_start(Some(options));
    if size <= start_index {
        return 0;
    }
    
    let short_per = 2.0 / (short_period as f64 + 1.0);
    let long_per = 2.0 / (long_period as f64 + 1.0);
    
    let output = unsafe { *outputs_ptr.offset(0) };
    let mut out = output;
    let mut cm = 0.0;
    let mut prev_hlc = unsafe { *high.offset(0) } + unsafe { *low.offset(0) } + unsafe { *close.offset(0) };
    let mut trend = -1;
    let mut short_ema = 0.0;
    let mut long_ema = 0.0;
    
    for i in 1..size as usize {
        let hlc = unsafe { *high.offset(i as isize) } + unsafe { *low.offset(i as isize) } + unsafe { *close.offset(i as isize) };
        let dm = unsafe { *high.offset(i as isize) } - unsafe { *low.offset(i as isize) };
        
        if hlc > prev_hlc && trend != 1 {
            trend = 1;
            cm = unsafe { *high.offset((i - 1) as isize) } - unsafe { *low.offset((i - 1) as isize) };
        } else if hlc < prev_hlc && trend != 0 {
            trend = 0;
            cm = unsafe { *high.offset((i - 1) as isize) } - unsafe { *low.offset((i - 1) as isize) };
        }
        
        cm += dm;
        
        let vf = unsafe { *volume.offset(i as isize) } * f64::abs((dm / cm) * 2.0 - 1.0) * 100.0 * if trend == 1 { 1.0 } else { -1.0 };
        
        if i == 1 {
            short_ema = vf;
            long_ema = vf;
        } else {
            short_ema = (vf - short_ema) * short_per + short_ema;
            long_ema = (vf - long_ema) * long_per + long_ema;
        }
        
        unsafe { *out = short_ema - long_ema };
        out = unsafe { out.offset(1) };
        prev_hlc = hlc;
    }
    
    let output_count = unsafe { out.offset_from(output) } as i32;
    assert!(output_count == (size - start_index));
    
    0
}
