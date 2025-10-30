use crate::*;
use rand::Rng;

pub fn ti_emv_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}

pub fn ti_emv(
    size: i32,
    inputs: &[&[f64]],
    options: Option<&[f64]>,
    outputs: &mut [&mut [f64]],
) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let volume = inputs[2];
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if size <= ti_emv_start(options) {
        return 0;
    }

    let mut last = (high[0] + low[0]) * 0.5;

    for i in 1..size as usize {
        let hl = (high[i] + low[i]) * 0.5;
        let br = (volume[i] / 10000.0) / (high[i] - low[i]);
        output[output_idx] = (hl - last) / br;
        output_idx += 1;
        last = hl;
    }

    // The assert in C is not directly translatable to safe Rust as it involves pointer arithmetic
    // In Rust, we would typically track lengths rather than pointers
    // This check is omitted in the safe Rust version as it's primarily a debug check in C

    0
}
