use crate::*;
use std::f64;

pub fn ti_tr_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_tr(size: usize, inputs: &[&[f64]], _options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let output = &mut outputs[0];

    output[0] = high[0] - low[0];

    for i in 1..size {
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

        output[i] = v;
    }

    0
}
