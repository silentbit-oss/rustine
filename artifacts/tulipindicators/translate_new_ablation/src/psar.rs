use crate::*;

pub fn ti_psar_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    1
}
pub fn ti_psar(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let accel_step = options[0];
    let accel_max = options[1];
    let output = &mut outputs[0];
    
    if accel_step <= 0.0 {
        return 1;
    }
    if accel_max <= accel_step {
        return 1;
    }
    if size < 2 {
        return 0;
    }
    
    let lng = if (high[0] + low[0]) <= (high[1] + low[1]) {
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
    let mut lng_flag = lng != 0;
    
    for i in 1..size as usize {
        sar = ((extreme - sar) * accel) + sar;
        
        if lng_flag {
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
        
        if (lng_flag && (low[i] < sar)) || (!lng_flag && (high[i] > sar)) {
            accel = accel_step;
            sar = extreme;
            lng_flag = !lng_flag;
            if !lng_flag {
                extreme = low[i];
            } else {
                extreme = high[i];
            }
        }
        
        output[i - 1] = sar;
    }
    
    let expected_len = (size - ti_psar_start(Some(&options[0]))) as usize;
    assert!((output.len() - 1) == expected_len);
    
    0
}
