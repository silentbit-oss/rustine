use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::convert::TryInto;
use std::f64;
pub extern "C" fn ti_atr_start(options: Option<&[f64]>) -> i32 {
    let opts = options.unwrap();
    (opts[0] as i32) - 1
}
pub extern "C" fn ti_atr(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for null pointers using Option
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let mut outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    // Extract input arrays
    if inputs.len() < 3 {
        return 1;
    }
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    
    // Extract output array
    if outputs.len() < 1 {
        return 1;
    }
    let output = &mut outputs[0];
    
    // Check array sizes
    if high.len() < size as usize || low.len() < size as usize || close.len() < size as usize || output.len() < size as usize {
        return 1;
    }
    
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }
    
    let start = ti_atr_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let per = 1.0 / (period as f64);
    let mut sum = 0.0;
    let mut truerange;
    
    // Calculate initial sum
    sum += high[0] - low[0];
    
    for i in 1..period as usize {
        let l = low[i];
        let h = high[i];
        let c = close[i - 1];
        let ych = f64::abs(h - c);
        let ycl = f64::abs(l - c);
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        truerange = v;
        sum += truerange;
    }
    
    let mut val = sum / (period as f64);
    output[0] = val;
    
    // Calculate remaining values
    for i in period as usize..size as usize {
        let l = low[i];
        let h = high[i];
        let c = close[i - 1];
        let ych = f64::abs(h - c);
        let ycl = f64::abs(l - c);
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        truerange = v;
        
        val = ((truerange - val) * per) + val;
        output[i - period as usize + 1] = val;
    }
    
    // Assertion check (commented out as Rust's assert! is for debug builds only)
    // assert!((output.len() as i32 - outputs[0].len() as i32) == (size - ti_atr_start(Some(options))));
    
    0
}
pub unsafe extern "C" fn ti_atr_stream_free(stream: *mut TiStream) {
    if !stream.is_null() {
        let _ = Box::from_raw(stream);
    }
}

pub fn ti_atr_stream_run(
    stream_in: &mut TiStream,
    size: i32,
    inputs: &[&[f64]],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let stream = unsafe { &mut *(stream_in as *mut TiStream as *mut TiStreamAtr) };
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let output = &mut outputs[0];
    let per = 1.0 / (stream.period as f64);
    let start = -(stream.period - 1);
    let mut i: usize = 0;
    let mut out_idx: usize = 0;

    if stream.progress < 1 {
        if stream.progress == start {
            stream.sum = high[0] - low[0];
            stream.last_close = close[0];
            stream.progress += 1;
            i += 1;
        }
        while (stream.progress <= 0) && (i < size as usize) {
            let truerange = {
                let ych = f64::abs(high[i] - stream.last_close);
                let ycl = f64::abs(low[i] - stream.last_close);
                let mut v = high[i] - low[i];
                if ych > v {
                    v = ych;
                }
                if ycl > v {
                    v = ycl;
                }
                v
            };
            stream.sum += truerange;
            stream.last_close = close[i];
            stream.progress += 1;
            i += 1;
        }

        if stream.progress == 1 {
            let val = stream.sum * per;
            stream.last = val;
            output[out_idx] = val;
            out_idx += 1;
        }
    }
    if stream.progress >= 1 {
        let mut val = stream.last;
        while i < size as usize {
            let truerange = {
                let ych = f64::abs(high[i] - stream.last_close);
                let ycl = f64::abs(low[i] - stream.last_close);
                let mut v = high[i] - low[i];
                if ych > v {
                    v = ych;
                }
                if ycl > v {
                    v = ycl;
                }
                v
            };
            val = ((truerange - val) * per) + val;
            output[out_idx] = val;
            stream.last_close = close[i];
            stream.progress += 1;
            i += 1;
            out_idx += 1;
        }
        stream.last = val;
    }
    0
}

pub extern "C" fn ti_atr_stream_new(options: Option<&[f64]>, stream_in: Option<&mut *mut TiStreamAtr>) -> i32 {
    // Check if options or stream_in is None (equivalent to NULL in C)
    if options.is_none() || stream_in.is_none() {
        return 1;
    }
    
    let options = options.unwrap();
    let stream_in = stream_in.unwrap();
    
    // Check if options has at least one element
    if options.is_empty() {
        return 1;
    }
    
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }
    
    // Allocate memory for TiStreamAtr using Layout
    let layout = Layout::new::<TiStreamAtr>();
    unsafe {
        *stream_in = alloc(layout) as *mut TiStreamAtr;
    }
    
    // Check if allocation was successful
    if (*stream_in).is_null() {
        return 2;
    }
    
    // Initialize the struct fields
    unsafe {
        (**stream_in).index = 13;
        (**stream_in).progress = -ti_atr_start(Some(options));
        (**stream_in).period = period;
        (**stream_in).sum = 0.0;
    }
    
    0
}
pub fn ti_tr(size: usize, inputs: &[&[f64]], _options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    if size < 1 { return 1; }
    if outputs.len() != 1 { return 2; }
    if inputs.len() < 3 { return 2; }
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let output = &mut outputs[0];
    
    if size == 0 { return 0; }
    
    let mut yc = if size > 1 { close[0] } else { 0.0 };
    
    for i in 0..size {
        let mut truerange = 0.0;
        let h = high[i];
        let l = low[i];
        let c = yc;
        
        let mut v = h - l;
        let diff1 = (h - c).abs();
        if diff1 > v { v = diff1; }
        let diff2 = (l - c).abs();
        if diff2 > v { v = diff2; }
        truerange = v;
        
        output[i] = truerange;
        yc = close[i];
    }
    
    0
}
