use crate::*;
use std::assert;

pub fn ti_mfi_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is None, return 0 as default (since C would dereference NULL causing UB)
    // Alternatively, could return Option<i32> if NULL case needs to be handled differently
    match options {
        Some(opts) => opts[0] as i32,
        None => 0,
    }
}
pub fn helper_helper_ti_mfi_1_1(up: &mut TiBuffer, down: &mut TiBuffer, bar: f64) {
    {
        if up.pushes >= up.size {
            up.sum -= up.vals[up.index as usize];
        }
        up.sum += bar;
        up.vals[up.index as usize] = bar;
        up.pushes += 1;
        up.index += 1;
        if up.index >= up.size {
            up.index = 0;
        }
    }
    {
        if down.pushes >= down.size {
            down.sum -= down.vals[down.index as usize];
        }
        down.sum += 0.0;
        down.vals[down.index as usize] = 0.0;
        down.pushes += 1;
        down.index += 1;
        if down.index >= down.size {
            down.index = 0;
        }
    }
}
pub fn helper_helper_ti_mfi_1_2(up: &mut TiBuffer, down: &mut TiBuffer, bar: f64) {
    {
        if down.pushes >= down.size {
            down.sum -= down.vals[down.index as usize];
        }
        down.sum += bar;
        down.vals[down.index as usize] = bar;
        down.pushes += 1;
        down.index += 1;
        if down.index >= down.size {
            down.index = 0;
        }
    }
    
    {
        if up.pushes >= up.size {
            up.sum -= up.vals[up.index as usize];
        }
        up.sum += 0.0;
        up.vals[up.index as usize] = 0.0;
        up.pushes += 1;
        up.index += 1;
        if up.index >= up.size {
            up.index = 0;
        }
    }
}
pub fn helper_helper_ti_mfi_1_3(up: &mut TiBuffer, down: &mut TiBuffer) {
    {
        if up.pushes >= up.size {
            up.sum -= up.vals[up.index as usize];
        }
        up.sum += 0.0;
        up.vals[up.index as usize] = 0.0;
        up.pushes += 1;
        up.index += 1;
        if up.index >= up.size {
            up.index = 0;
        }
    }
    
    {
        if down.pushes >= down.size {
            down.sum -= down.vals[down.index as usize];
        }
        down.sum += 0.0;
        down.vals[down.index as usize] = 0.0;
        down.pushes += 1;
        down.index += 1;
        if down.index >= down.size {
            down.index = 0;
        }
    }
}
pub fn helper_ti_mfi_1(
    output_idx_ref: &mut u32,
    ytyp_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    volume: &[f64],
    period: i32,
    output: &mut [f64],
    i: usize,
    up: &mut TiBuffer,
    down: &mut TiBuffer,
) {
    let mut output_idx = *output_idx_ref;
    let mut ytyp = *ytyp_ref;
    let typ = (high[i] + low[i] + close[i]) * (1.0 / 3.0);
    let bar = typ * volume[i];

    if typ > ytyp {
        helper_helper_ti_mfi_1_1(up, down, bar);
    } else if typ < ytyp {
        helper_helper_ti_mfi_1_2(up, down, bar);
    } else {
        helper_helper_ti_mfi_1_3(up, down);
    }

    ytyp = typ;

    if i >= period as usize {
        output[output_idx as usize] = (up.sum / (up.sum + down.sum)) * 100.0;
        output_idx += 1;
    }

    *output_idx_ref = output_idx;
    *ytyp_ref = ytyp;
}

pub fn ti_mfi(
    size: i32,
    inputs: &[&[f64]],
    options: Option<&[f64]>,
    outputs: &mut [&mut [f64]],
) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    
    let period = match options {
        Some(opts) => opts[0] as i32,
        None => return 1,
    };
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_mfi_start(options);
    if size <= start {
        return 0;
    }
    
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let mut ytyp = ((high[0] + low[0]) + close[0]) * (1.0 / 3.0);
    
    let mut up = match ti_buffer_new(period) {
        Some(buffer) => buffer,
        None => return 1,
    };
    let mut down = match ti_buffer_new(period) {
        Some(buffer) => buffer,
        None => {
            ti_buffer_free(*up);
            return 1;
        }
    };
    
    for i in 1..size as usize {
        helper_ti_mfi_1(
            &mut output_idx,
            &mut ytyp,
            high,
            low,
            close,
            volume,
            period,
            output,
            i,
            &mut up,
            &mut down,
        );
    }
    
    ti_buffer_free(*up);
    ti_buffer_free(*down);
    
    assert!((output[output_idx as usize] - outputs[0][0]) == (size - ti_mfi_start(options)) as f64);
    
    0
}
