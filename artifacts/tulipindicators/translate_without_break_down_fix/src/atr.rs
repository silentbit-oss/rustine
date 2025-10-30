use crate::*;
use std::f64;
use std::convert::TryInto;
pub fn ti_atr_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_atr_start");
    // Check if options is None or empty (equivalent to NULL check in C)
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32 - 1,
        _ => -1, // Return -1 as a safe default when options is None or empty
    }
}
pub fn ti_atr(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
	println!("\n* ti_atr");
    // Check for null inputs/outputs (Option::None in Rust)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();
    
    // Get input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    
    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }
    
    // Check if size is sufficient
    if size <= ti_atr_start(Some(options)) {
        return 0;
    }
    
    let per = 1.0 / period as f64;
    let output = &mut outputs[0];
    let mut output_idx = 0;
    
    // Initial sum calculation
    let mut sum = high[0] - low[0];
    for i in 1..period {
        let l = low[i as usize];
        let h = high[i as usize];
        let c = close[(i - 1) as usize];
        
        let ych = (h - c).abs();
        let ycl = (l - c).abs();
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        
        sum += v;
    }
    
    // Initial ATR value
    let mut val = sum / period as f64;
    output[output_idx] = val;
    output_idx += 1;
    
    // Subsequent ATR values
    for i in period..size {
        let l = low[i as usize];
        let h = high[i as usize];
        let c = close[(i - 1) as usize];
        
        let ych = (h - c).abs();
        let ycl = (l - c).abs();
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        
        val = ((v - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }
    
    0
}
pub fn ti_atr_stream_free(stream: Option<Box<TiStream>>) {
	println!("\n* ti_atr_stream_free");
    // In Rust, Box is automatically dropped when it goes out of scope,
    // so no explicit free is needed. The Option wrapper allows for NULL check.
    // Just let the Box drop naturally by doing nothing.
}

pub fn ti_atr_stream_run(
    stream_in: &mut TiStream,
    size: i32,
    inputs: &[&[f64]],
    outputs: &mut [&mut [f64]],
) -> i32 {
	println!("\n* ti_atr_stream_run");
    let stream = unsafe { &mut *(stream_in as *mut TiStream as *mut TiStreamAtr) };
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let per = 1.0 / (stream.period as f64);
    let start = -(stream.period - 1);
    let mut i = 0;

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
            output[output_idx] = val;
            output_idx += 1;
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
            output[output_idx] = val;
            output_idx += 1;
            stream.last_close = close[i];
            stream.progress += 1;
            i += 1;
        }

        stream.last = val;
    }

    0
}

pub fn ti_atr_stream_new(options: Option<&[f64]>, stream_in: Option<&mut Option<Box<TiStreamAtr>>>) -> i32 {
	println!("\n* ti_atr_stream_new");
    // Check if options is None or empty
    let options = match options {
        Some(opts) if !opts.is_empty() => opts,
        _ => return 1, // Invalid period case
    };

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    // Check if stream_in is Some
    let stream_in = match stream_in {
        Some(s) => s,
        None => return 2, // Invalid stream_in pointer
    };

    // Create new TiStreamAtr
    let mut new_stream = Box::new(TiStreamAtr {
        index: 13,
        progress: -ti_atr_start(Some(options)),
        period,
        sum: 0.0,
        last: 0.0,
        last_close: 0.0,
    });

    // Replace the contents of stream_in with our new stream
    *stream_in = Some(new_stream);

    0
}
pub fn ti_atr_ref(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_atr_ref");
    // Check if options is Some and has at least one element
    let period = options.and_then(|opts| opts.first().map(|&p| p as i32))?;
    if period < 1 {
        return Some(1);
    }

    let atr_start = ti_atr_start(options);
    if size <= atr_start {
        return Some(0);
    }

    let tr_start = ti_tr_start(options);
    let tr_size = size - tr_start;

    // Allocate a Vec for truerange instead of raw pointer
    let mut truerange = vec![0.0; tr_size as usize];
    
    // Prepare outputs for ti_tr
    let mut tr_outputs = [truerange.as_mut_slice()];
    
    // Call ti_tr with proper error handling
    let tr_ret = ti_tr(
        size as usize,
        inputs.unwrap_or(&[]),
        &[],
        &mut tr_outputs,
    );
    
    if tr_ret != 0 {
        return Some(tr_ret);
    }

    // Prepare inputs for ti_wilders
    let wilders_inputs = [truerange.as_slice()];
    
    // Call ti_wilders and return its result
    let wilders_ret = ti_wilders(
        tr_size,
        Some(&wilders_inputs),
        options,
        outputs,
    );

    // Assertion check (converted to debug_assert)
    debug_assert!(
        (size - ti_atr_start(options)) == (size - ti_wilders_start(options).unwrap_or(0))
    );

    wilders_ret
}
