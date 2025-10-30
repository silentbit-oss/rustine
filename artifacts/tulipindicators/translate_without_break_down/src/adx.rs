use crate::*;
use std::f64;

pub fn ti_adx_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C, but safely
    Some(((options[0] as i32) - 1) * 2)
}

pub fn ti_adx(size: usize, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let high = inputs[0];
    let low = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 2 {
        return 1;
    }

    let ti_adx_start_value = match ti_adx_start(Some(options)) {
        Some(val) => val,
        None => return 0,
    };

    if size <= ti_adx_start_value as usize {
        return 0;
    }

    let per = (period as f64 - 1.0) / period as f64;
    let invper = 1.0 / period as f64;
    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    for i in 1..period as usize {
        let (dp, dm) = {
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

            (dp, dm)
        };

        dmup += dp;
        dmdown += dm;
    }

    let mut adx = {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        dx
    };

    for i in period as usize..size {
        let (dp, dm) = {
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

            (dp, dm)
        };

        dmup = dmup * per + dp;
        dmdown = dmdown * per + dm;

        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;

        let period_diff = i - period as usize;
        if period_diff < (period - 2) as usize {
            adx += dx;
        } else if period_diff == (period - 2) as usize {
            adx += dx;
            output[output_idx] = adx * invper;
            output_idx += 1;
        } else {
            adx = adx * per + dx;
            output[output_idx] = adx * invper;
            output_idx += 1;
        }
    }

    assert!((output_idx) == (size - ti_adx_start_value as usize));
    0
}
