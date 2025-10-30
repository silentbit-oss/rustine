use crate::*;
use std::os::raw::c_double;
use std::f64;
pub fn ti_dx_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn helper_ti_dx_1(
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    i: usize,
) {
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    
    let mut dp;
    let mut dm;
    
    // The do-while(0) loop in C is just a way to create a scope block
    {
        dp = high[i] - high[i - 1];
        dm = low[i - 1] - low[i];
        
        if dp < 0.0 {
            dp = 0.0;
        } else if dp > dm {
            dm = 0.0;
        }
        
        if dm < 0.0 {
            dm = 0.0;
        } else if dm > dp {
            dp = 0.0;
        }
    }
    
    dmup += dp;
    dmdown += dm;
    
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn helper_ti_dx_2(
    output_idx_ref: &mut u32,
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    output: &mut [f64],
    per: f64,
    i: usize,
) {
    let mut output_idx = *output_idx_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    let mut dp;
    let mut dm;

    // Equivalent of the do-while(0) block
    {
        dp = {
            let val = high[i] - high[i - 1];
            if val < 0.0 { 0.0 } else { val }
        };
        dm = {
            let val = low[i - 1] - low[i];
            if val < 0.0 { 0.0 } else { val }
        };

        if dp > dm {
            dm = 0.0;
        }
        if dm > dp {
            dp = 0.0;
        }
    }

    dmup = (dmup * per) + dp;
    dmdown = (dmdown * per) + dm;
    let di_up = dmup;
    let di_down = dmdown;
    let dm_diff = f64::abs(di_up - di_down);
    let dm_sum = di_up + di_down;
    let dx = (dm_diff / dm_sum) * 100.0;

    output[output_idx as usize] = dx;
    output_idx += 1;

    *output_idx_ref = output_idx;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn ti_dx(
    size: usize,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> Result<(), i32> {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx: u32 = 0;

    if period < 1 {
        return Err(1);
    }

    let start = match ti_dx_start(Some(options)) {
        Some(s) => s,
        None => return Err(0),
    };

    if size <= start as usize {
        return Err(0);
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    for i in 1..period as usize {
        helper_ti_dx_1(&mut dmup, &mut dmdown, high, low, i);
    }

    {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        output[output_idx as usize] = dx;
        output_idx += 1;
    }

    for i in period as usize..size {
        helper_ti_dx_2(
            &mut output_idx,
            &mut dmup,
            &mut dmdown,
            high,
            low,
            output,
            per,
            i,
        );
    }

    debug_assert!((output.as_ptr() as usize + output_idx as usize * std::mem::size_of::<f64>()) - output.as_ptr() as usize
        == (size - start as usize) * std::mem::size_of::<f64>());

    Ok(())
}
