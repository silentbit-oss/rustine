use crate::*;
use std::assert;

pub fn ti_psar_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    1
}
pub fn helper_ti_psar_1(
    output_idx_ref: &mut u32,
    lng_ref: &mut i32,
    sar_ref: &mut f64,
    extreme_ref: &mut f64,
    accel_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    accel_step: f64,
    accel_max: f64,
    output: &mut [f64],
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut lng = *lng_ref;
    let mut sar = *sar_ref;
    let mut extreme = *extreme_ref;
    let mut accel = *accel_ref;

    sar = ((extreme - sar) * accel) + sar;

    if lng != 0 {
        if (i >= 2) && (sar > low[i - 2]) {
            sar = low[i - 2];
        }
        if sar > low[i - 1] {
            sar = low[i - 1];
        }
        if (accel < accel_max) && (high[i] > extreme) {
            accel += accel_step;
            if accel > accel_max {
                accel = accel_max;
            }
        }
        if high[i] > extreme {
            extreme = high[i];
        }
    } else {
        if (i >= 2) && (sar < high[i - 2]) {
            sar = high[i - 2];
        }
        if sar < high[i - 1] {
            sar = high[i - 1];
        }
        if (accel < accel_max) && (low[i] < extreme) {
            accel += accel_step;
            if accel > accel_max {
                accel = accel_max;
            }
        }
        if low[i] < extreme {
            extreme = low[i];
        }
    }

    if (lng != 0 && (low[i] < sar)) || ((lng == 0) && (high[i] > sar)) {
        accel = accel_step;
        sar = extreme;
        lng = !lng;
        if lng == 0 {
            extreme = low[i];
        } else {
            extreme = high[i];
        }
    }

    output[output_idx as usize] = sar;
    output_idx += 1;

    *output_idx_ref = output_idx;
    *lng_ref = lng;
    *sar_ref = sar;
    *extreme_ref = extreme;
    *accel_ref = accel;
}
pub fn ti_psar(
    size: usize,
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

    // Extract slices from inputs and outputs
    let high = inputs[0];
    let low = inputs[1];
    let output = &mut outputs[0];

    // Extract options
    let accel_step = options[0];
    let accel_max = options[1];

    // Early returns for invalid conditions (lines 9-20)
    if accel_step <= 0.0 {
        return 1;
    }
    if accel_max <= accel_step {
        return 1;
    }
    if size < 2 {
        return 0;
    }

    // Determine initial lng value (lines 21-27)
    let mut lng = if (high[0] + low[0]) <= (high[1] + low[1]) {
        1
    } else {
        0
    };

    // Initialize sar and extreme (lines 28-39)
    let (mut sar, mut extreme) = if lng != 0 {
        (low[0], high[0])
    } else {
        (high[0], low[0])
    };

    let mut accel = accel_step;
    let mut output_idx = 0;

    // Main processing loop (lines 42-45)
    for i in 1..size {
        helper_ti_psar_1(
            &mut output_idx,
            &mut lng,
            &mut sar,
            &mut extreme,
            &mut accel,
            high,
            low,
            accel_step,
            accel_max,
            output,
            i,
        );
    }

    // Assertion check (line 47)
    assert!((output[output_idx as usize] - outputs[0][0]) == (size as f64 - ti_psar_start(Some(options)) as f64));

    0
}
