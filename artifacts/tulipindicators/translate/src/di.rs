use crate::*;
use std::f64;

pub fn ti_di_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if the slice is not empty to avoid panic on index 0
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(options[0] as i32 - 1)
}
pub fn ti_di(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let period = options[0] as i32;
    
    // Use split_at_mut to get two separate mutable slices
    let (first, second) = outputs.split_at_mut(1);
    let plus_di = &mut first[0];
    let mut plus_di_idx = 0;
    let minus_di = &mut second[0];
    let mut minus_di_idx = 0;

    if period < 1 {
        return 1;
    }

    let start = match ti_di_start(Some(options)) {
        Some(s) => s,
        None => return 0,
    };

    if size <= start {
        return 0;
    }

    let per = (period as f64 - 1.0) / period as f64;
    let mut atr = 0.0;
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    for i in 1..period {
        let truerange = {
            let l = low[i as usize];
            let h = high[i as usize];
            let c = close[(i - 1) as usize];
            let ych = (h - c).abs();
            let ycl = (l - c).abs();
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };
        atr += truerange;

        let (dp, dm) = {
            let dp = high[i as usize] - high[(i - 1) as usize];
            let dm = low[(i - 1) as usize] - low[i as usize];
            let dp = if dp < 0.0 { 0.0 } else { dp };
            let dm = if dm < 0.0 { 0.0 } else { dm };
            let (dp, dm) = if dp > dm { (dp, 0.0) } else { (0.0, dm) };
            (dp, dm)
        };

        dmup += dp;
        dmdown += dm;
    }

    plus_di[plus_di_idx] = (100.0 * dmup) / atr;
    plus_di_idx += 1;
    minus_di[minus_di_idx] = (100.0 * dmdown) / atr;
    minus_di_idx += 1;

    for i in period..size {
        let truerange = {
            let l = low[i as usize];
            let h = high[i as usize];
            let c = close[(i - 1) as usize];
            let ych = (h - c).abs();
            let ycl = (l - c).abs();
            let mut v = h - l;
            if ych > v {
                v = ych;
            }
            if ycl > v {
                v = ycl;
            }
            v
        };
        atr = (atr * per) + truerange;

        let (dp, dm) = {
            let dp = high[i as usize] - high[(i - 1) as usize];
            let dm = low[(i - 1) as usize] - low[i as usize];
            let dp = if dp < 0.0 { 0.0 } else { dp };
            let dm = if dm < 0.0 { 0.0 } else { dm };
            let (dp, dm) = if dp > dm { (dp, 0.0) } else { (0.0, dm) };
            (dp, dm)
        };

        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;

        plus_di[plus_di_idx] = (100.0 * dmup) / atr;
        plus_di_idx += 1;
        minus_di[minus_di_idx] = (100.0 * dmdown) / atr;
        minus_di_idx += 1;
    }

    // Note: The original C assertions are omitted as they're debug checks
    0
}
