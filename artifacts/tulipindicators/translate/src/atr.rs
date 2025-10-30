use crate::*;
use std::assert;
use std::f64;
pub fn ti_atr_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn helper_ti_atr_1(
    sum_ref: &mut f64,
    truerange_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    i: usize,
) {
    let mut sum = *sum_ref;
    let mut truerange = *truerange_ref;

    {
        let l = low[i];
        let h = high[i];
        let c = close[i - 1];
        let ych = (h - c).abs();
        let ycl = (l - c).abs();
        let mut v = h - l;

        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        truerange = v;
    }

    sum += truerange;
    *sum_ref = sum;
    *truerange_ref = truerange;
}
pub fn helper_ti_atr_2(
    output_idx_ref: &mut u32,
    truerange_ref: &mut f64,
    val_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    output: &mut [f64],
    per: f64,
    i: usize,
) {
    let output_idx = *output_idx_ref;
    let mut truerange = *truerange_ref;
    let mut val = *val_ref;

    {
        let l = low[i];
        let h = high[i];
        let c = close[i - 1];
        let ych = (h - c).abs();
        let ycl = (l - c).abs();
        let mut v = h - l;
        
        if ych > v {
            v = ych;
        }
        if ycl > v {
            v = ycl;
        }
        truerange = v;
    }

    val = ((truerange - val) * per) + val;
    output[output_idx as usize] = val;
    
    *output_idx_ref = output_idx + 1;
    *truerange_ref = truerange;
    *val_ref = val;
}
pub fn ti_atr_stream_free(stream: Option<Box<TiStream>>) {
    // In Rust, Box<T> automatically frees memory when it goes out of scope,
    // so we don't need to explicitly free it. Just let the Option<Box> drop.
    // The function takes ownership of the Box and will drop it when done.
}

pub fn helper_ti_atr_stream_run_1(
    output_idx_ref: &mut u32,
    i_ref: &mut i32,
    size: i32,
    stream: &mut TiStreamAtr,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    output: &mut [f64],
    per: f64,
) {
    let mut output_idx = *output_idx_ref;
    let mut i = *i_ref;
    let mut val = stream.last;

    while i < size {
        let truerange = {
            let ych = f64::abs(high[i as usize] - stream.last_close);
            let ycl = f64::abs(low[i as usize] - stream.last_close);
            let mut v = high[i as usize] - low[i as usize];
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };

        val = ((truerange - val) * per) + val;
        output[output_idx as usize] = val;
        output_idx += 1;
        stream.last_close = close[i as usize];
        stream.progress += 1;
        i += 1;
    }

    stream.last = val;
    *output_idx_ref = output_idx;
    *i_ref = i;
}
pub fn helper_ti_atr_stream_run_2(
    output_idx_ref: &mut u32,
    i_ref: &mut i32,
    size: i32,
    stream: &mut TiStreamAtr,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    output: &mut [f64],
    per: f64,
    start: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut i = *i_ref;

    if stream.progress == start {
        stream.sum = high[0] - low[0];
        stream.last_close = close[0];
        stream.progress += 1;
        i += 1;
    }

    while (stream.progress <= 0) && (i < size) {
        let truerange = {
            let ych = (high[i as usize] - stream.last_close).abs();
            let ycl = (low[i as usize] - stream.last_close).abs();
            let mut v = high[i as usize] - low[i as usize];
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };

        stream.sum += truerange;
        stream.last_close = close[i as usize];
        stream.progress += 1;
        i += 1;
    }

    if stream.progress == 1 {
        let val = stream.sum * per;
        stream.last = val;
        output[output_idx as usize] = val;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *i_ref = i;
}
pub fn ti_atr(size: usize, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx: u32 = 0;

    if period < 1 {
        return 1;
    }

    let start = match ti_atr_start(Some(options)) {
        Some(s) => s,
        None => return 1,
    };

    if size <= start as usize {
        return 0;
    }

    let per = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut truerange = 0.0;

    sum += high[0] - low[0];

    for i in 1..period as usize {
        helper_ti_atr_1(&mut sum, &mut truerange, high, low, close, i);
    }

    let mut val = sum / period as f64;
    output[output_idx as usize] = val;
    output_idx += 1;

    for i in period as usize..size {
        helper_ti_atr_2(
            &mut output_idx,
            &mut truerange,
            &mut val,
            high,
            low,
            close,
            output,
            per,
            i,
        );
    }

    assert!((output.as_ptr().wrapping_offset(output_idx as isize) as usize - output.as_ptr() as usize)
        / std::mem::size_of::<f64>()
        == (size - start as usize));
    0
}
pub fn ti_atr_stream_new(options: Option<&[f64]>, stream_in: Option<&mut Option<Box<TiStream>>>) -> Option<i32> {
    // Check if options is None or empty
    let options = options?;
    if options.is_empty() {
        return Some(1);
    }

    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Check if stream_in is None
    let stream_in = stream_in?;

    // Create new TiStreamAtr
    let mut stream = Box::new(TiStreamAtr {
        index: 13,
        progress: -ti_atr_start(Some(options))?,
        period,
        sum: 0.0,
        last: 0.0,
        last_close: 0.0,
    });

    // Convert Box<TiStreamAtr> to Box<TiStream> using unsafe cast
    // This matches the C code's behavior of casting ti_stream_atr* to ti_stream*
    let stream_as_ti: Box<TiStream> = unsafe {
        Box::from_raw(Box::into_raw(stream) as *mut TiStream)
    };

    // Replace the content of stream_in with our new stream
    *stream_in = Some(stream_as_ti);

    Some(0)
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
    let mut output_idx = 0;
    let per = 1.0 / (stream.period as f64);
    let start = -(stream.period - 1);
    let mut i = 0;

    if stream.progress < 1 {
        helper_ti_atr_stream_run_2(
            &mut output_idx,
            &mut i,
            size,
            stream,
            high,
            low,
            close,
            output,
            per,
            start,
        );
    }
    if stream.progress >= 1 {
        helper_ti_atr_stream_run_1(
            &mut output_idx,
            &mut i,
            size,
            stream,
            high,
            low,
            close,
            output,
            per,
        );
    }
    0
}
pub fn ti_atr_ref(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    mut outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    let period = options.and_then(|opts| opts.first().copied()).map(|p| p as i32);
    if period.map_or(true, |p| p < 1) {
        return 1;
    }

    if size <= ti_atr_start(options).unwrap_or(0) {
        return 0;
    }

    let tr_start = ti_tr_start(options);
    let tr_size = size - tr_start;

    // Use Vec instead of manual malloc/free
    let mut truerange = vec![0.0; tr_size as usize];
    
    // Create a mutable slice reference for tr_outputs
    let tr_outputs = &mut [truerange.as_mut_slice()];
    
    let tr_ret = ti_tr(size as usize, inputs.unwrap_or(&[]), &[], tr_outputs);
    if tr_ret != 0 {
        return tr_ret;
    }

    let wilders_inputs = &[truerange.as_slice()];
    let wilders_ret = ti_wilders(tr_size, Some(wilders_inputs), options, outputs);

    // Assertion translated to debug_assert!
    debug_assert!(
        (size - ti_atr_start(options).unwrap_or(0)) == (size - ti_wilders_start(options).unwrap_or(0))
    );

    wilders_ret.unwrap_or(0)
}
