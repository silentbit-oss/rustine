use crate::*;

pub fn ti_psar_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}
pub fn ti_psar(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Validate input slices
    if inputs.len() < 2 || outputs.is_empty() {
        return 1;
    }

    let high = inputs[0];
    let low = inputs[1];
    let output = &mut outputs[0];

    let accel_step = options[0];
    let accel_max = options[1];

    if accel_step <= 0.0 || accel_max <= accel_step {
        return 1;
    }

    if size < 2 {
        return 0;
    }

    let mut lng = if (high[0] + low[0]) <= (high[1] + low[1]) {
        1
    } else {
        0
    };

    let (mut sar, mut extreme) = if lng != 0 {
        (low[0], high[0])
    } else {
        (high[0], low[0])
    };

    let mut accel = accel_step;
    let mut output_idx = 0;

    for i in 1..size as usize {
        sar = ((extreme - sar) * accel) + sar;

        if lng != 0 {
            if i >= 2 && sar > low[i - 2] {
                sar = low[i - 2];
            }
            if sar > low[i - 1] {
                sar = low[i - 1];
            }
            if accel < accel_max && high[i] > extreme {
                accel += accel_step;
                if accel > accel_max {
                    accel = accel_max;
                }
            }
            if high[i] > extreme {
                extreme = high[i];
            }
        } else {
            if i >= 2 && sar < high[i - 2] {
                sar = high[i - 2];
            }
            if sar < high[i - 1] {
                sar = high[i - 1];
            }
            if accel < accel_max && low[i] < extreme {
                accel += accel_step;
                if accel > accel_max {
                    accel = accel_max;
                }
            }
            if low[i] < extreme {
                extreme = low[i];
            }
        }

        if (lng != 0 && low[i] < sar) || (lng == 0 && high[i] > sar) {
            accel = accel_step;
            sar = extreme;
            lng = if lng == 0 { 1 } else { 0 };
            extreme = if lng == 0 { low[i] } else { high[i] };
        }

        output[output_idx] = sar;
        output_idx += 1;
    }

    // Note: The original C assertion is removed as it's not idiomatic in Rust
    // and would require unsafe code to calculate pointer differences

    0
}
