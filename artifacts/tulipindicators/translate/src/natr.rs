use crate::*;
use std::assert;

pub fn ti_natr_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn helper_ti_natr_1(
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
pub fn helper_ti_natr_2(
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
    output[output_idx as usize] = (100.0 * val) / close[i];
    
    *output_idx_ref = output_idx + 1;
    *truerange_ref = truerange;
    *val_ref = val;
}
pub fn ti_natr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get slices from inputs
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];

    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    // Get output slice
    let output = &mut outputs[0];

    // Check if size is sufficient
    if let Some(start) = ti_natr_start(Some(options)) {
        if size <= start {
            return 0;
        }
    } else {
        return 1;
    }

    let per = 1.0 / period as f64;
    let mut sum = 0.0;
    let mut truerange = 0.0;
    let mut output_idx: u32 = 0;

    // Initial sum calculation
    sum += high[0] - low[0];

    for i in 1..period as usize {
        helper_ti_natr_1(&mut sum, &mut truerange, high, low, close, i);
    }

    let mut val = sum / period as f64;
    output[output_idx as usize] = (100.0 * val) / close[period as usize - 1];
    output_idx += 1;

    for i in period as usize..size as usize {
        helper_ti_natr_2(
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

    // Assertion check
    assert!((output.as_ptr() as usize + output_idx as usize * std::mem::size_of::<f64>())
        - outputs[0].as_ptr() as usize
        == (size - ti_natr_start(Some(options)).unwrap()) as usize * std::mem::size_of::<f64>());

    0
}
