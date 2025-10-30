use crate::*;
use libm::fabs;

pub fn ti_di_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}

pub fn helper_helper_ti_di_1_1(
    truerange_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    i: usize,
) {
    let l = low[i];
    let h = high[i];
    let c = close[i - 1];
    let ych = fabs(h - c);
    let ycl = fabs(l - c);
    let mut v = h - l;
    
    if ych > v {
        v = ych;
    }
    if ycl > v {
        v = ycl;
    }
    
    *truerange_ref = v;
}
pub fn helper_helper_ti_di_2_1(
    truerange_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    i: usize,
) {
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
    
    *truerange_ref = v;
}
pub fn helper_ti_di_1(
    atr_ref: &mut f64,
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    i: usize,
) {
    let mut atr = *atr_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    let mut truerange = 0.0;  // Initialize truerange with default value

    {
        helper_helper_ti_di_1_1(&mut truerange, high, low, close, i);
    }

    atr += truerange;

    let (dp, dm) = {
        let dp_val = high[i] - high[i - 1];
        let dm_val = low[i - 1] - low[i];
        
        let dp = if dp_val < 0.0 { 0.0 } else { dp_val };
        let dm = if dm_val < 0.0 { 0.0 } else { dm_val };
        
        let (final_dp, final_dm) = if dp > dm {
            (dp, 0.0)
        } else if dm > dp {
            (0.0, dm)
        } else {
            (dp, dm)
        };
        
        (final_dp, final_dm)
    };

    dmup += dp;
    dmdown += dm;

    *atr_ref = atr;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn helper_ti_di_2(
    plus_di_idx_ref: &mut usize,
    minus_di_idx_ref: &mut usize,
    atr_ref: &mut f64,
    dmup_ref: &mut f64,
    dmdown_ref: &mut f64,
    high: &[f64],
    low: &[f64],
    close: &[f64],
    plus_di: &mut [f64],
    minus_di: &mut [f64],
    per: f64,
    i: usize,
) {
    let mut plus_di_idx = *plus_di_idx_ref;
    let mut minus_di_idx = *minus_di_idx_ref;
    let mut atr = *atr_ref;
    let mut dmup = *dmup_ref;
    let mut dmdown = *dmdown_ref;
    let mut truerange = 0.0;

    helper_helper_ti_di_2_1(&mut truerange, high, low, close, i);
    
    atr = (atr * per) + truerange;
    
    let mut dp = high[i] - high[i - 1];
    let mut dm = low[i - 1] - low[i];
    
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
    
    dmup = (dmup * per) + dp;
    dmdown = (dmdown * per) + dm;
    
    plus_di[plus_di_idx] = (100.0 * dmup) / atr;
    plus_di_idx += 1;
    minus_di[minus_di_idx] = (100.0 * dmdown) / atr;
    minus_di_idx += 1;
    
    *plus_di_idx_ref = plus_di_idx;
    *minus_di_idx_ref = minus_di_idx;
    *atr_ref = atr;
    *dmup_ref = dmup;
    *dmdown_ref = dmdown;
}
pub fn ti_di(
    size: usize,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices from inputs
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];

    // Get period from options
    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    // Check if size is sufficient
    let start = ti_di_start(Some(options))?;
    if size <= start as usize {
        return Some(0);
    }

    // Get mutable slices from outputs
    let (plus_di_slice, minus_di_slice) = {
        let (first, rest) = outputs.split_first_mut().unwrap();
        let (second, _) = rest.split_first_mut().unwrap();
        (first, second)
    };

    let mut plus_di_idx = 0;
    let mut minus_di_idx = 0;

    let per = ((period as f64) - 1.0) / (period as f64);
    let mut atr = 0.0;
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    // First loop
    for i in 1..period as usize {
        helper_ti_di_1(&mut atr, &mut dmup, &mut dmdown, high, low, close, i);
    }

    // Calculate initial values
    plus_di_slice[plus_di_idx] = (100.0 * dmup) / atr;
    plus_di_idx += 1;
    minus_di_slice[minus_di_idx] = (100.0 * dmdown) / atr;
    minus_di_idx += 1;

    // Second loop
    for i in period as usize..size {
        helper_ti_di_2(
            &mut plus_di_idx,
            &mut minus_di_idx,
            &mut atr,
            &mut dmup,
            &mut dmdown,
            high,
            low,
            close,
            plus_di_slice,
            minus_di_slice,
            per,
            i,
        );
    }

    // Assertions (using debug_assert! which is removed in release builds)
    debug_assert!(
        (plus_di_idx - 1) == (size - start as usize - 1),
        "plus_di length mismatch"
    );
    debug_assert!(
        (minus_di_idx - 1) == (size - start as usize - 1),
        "minus_di length mismatch"
    );

    Some(0)
}
