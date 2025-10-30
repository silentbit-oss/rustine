use crate::*;
use std::assert;
use std::convert::TryInto;
use std::alloc::Layout;
use std::alloc::alloc;

pub fn ti_sma_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    Some(options[0] as i32 - 1)
}

pub fn ti_sma(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return 1;
    }

    // Check if size is sufficient
    let start = match ti_sma_start(Some(options)) {
        Some(s) => s,
        None => return 0,
    };

    if size <= start {
        return 0;
    }

    // Calculate initial sum
    let mut sum = 0.0;
    for i in 0..period {
        sum += input[i as usize];
    }

    output[output_idx] = sum * scale;
    output_idx += 1;

    // Calculate rolling sum
    for i in period..size {
        let i_usize = i as usize;
        sum += input[i_usize];
        sum -= input[i_usize - period as usize];
        output[output_idx] = sum * scale;
        output_idx += 1;
    }

    // Verify output length matches expectation
    assert!((output[output_idx - 1] - outputs[0][0]) == (size - start) as f64);

    0
}
pub fn ti_sma_stream_free(stream: Option<Box<TiStream>>) {
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // so no explicit free is needed. The Option wrapper allows for NULL checking.
    // Just let the stream drop naturally if it's Some
}

pub fn ti_sma_stream_run(
    stream_in: &mut TiStream,
    size: i32,
    inputs: &[&[f64]],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let stream = unsafe { &mut *(stream_in as *mut TiStream as *mut TiStreamSma) };
    let mut progress = stream.progress;
    let real = inputs[0];
    let period = stream.period;
    let sma = &mut outputs[0];
    let mut sma_idx = 0;
    let per = stream.per;
    let mut sum = stream.sum;
    let mut buffer_idx = stream.buffer_idx;
    let buffer = stream.buffer.as_mut().expect("Buffer must be initialized");

    if progress == ((-period) + 1) {
        // No action needed for this case
    } else {
        // No action needed for this case
    }

    let mut i = 0;
    while progress < 1 && i < size {
        buffer_idx += 1;
        let val = real[i as usize] * per;
        buffer[buffer_idx as usize] = val;
        sum += val;
        i += 1;
        progress += 1;
    }

    if i > 0 && progress == 1 {
        sma[sma_idx as usize] = sum;
        sma_idx += 1;
    }

    while i < size {
        buffer_idx += 1;
        if buffer_idx == period {
            buffer_idx = 0;
        }
        sum -= buffer[buffer_idx as usize];
        let val = real[i as usize] * per;
        buffer[buffer_idx as usize] = val;
        sum += val;
        sma[sma_idx as usize] = sum;
        sma_idx += 1;
        i += 1;
        progress += 1;
    }

    stream.progress = progress;
    stream.sum = sum;
    stream.buffer_idx = buffer_idx;
    0
}

pub fn ti_sma_stream_new(options: Option<&[f64]>, stream_in: Option<&mut Option<Box<TiStreamSma>>>) -> i32 {
    // Check if options or stream_in is None (equivalent to NULL checks in C)
    if options.is_none() || stream_in.is_none() {
        return 1;
    }
    let options = options.unwrap();
    let stream_in = stream_in.unwrap();

    // Get period from options (equivalent to line 4 in C)
    if options.is_empty() {
        return 1;
    }
    let period = options[0] as i32;

    // Check period validity (equivalent to lines 5-8 in C)
    if period < 1 {
        return 1;
    }

    // Create new TiStreamSma (equivalent to malloc in C)
    let mut stream = Box::new(TiStreamSma {
        index: 72,
        progress: -ti_sma_start(Some(options)).unwrap_or(0),
        period,
        per: 1.0 / period as f64,
        sum: 0.0,
        buffer_idx: -1,
        buffer: Some(vec![0.0; period as usize]),
    });

    // Assign to output parameter (equivalent to line 9-20 in C)
    *stream_in = Some(stream);

    0 // Success
}
