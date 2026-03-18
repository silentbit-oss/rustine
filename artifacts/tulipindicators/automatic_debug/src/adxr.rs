use crate::*;
use std::f64;

pub fn ti_adxr_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_adxr_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(((options[0] as i32) - 1) * 3)
}
pub fn ti_adxr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_adxr");
    // Early return if any required input is None
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Get slices from inputs and outputs
    let high = inputs[0];
    let low = inputs[1];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    if period < 2 {
        return Some(1);
    }

    let first_adxr = ti_adxr_start(Some(options))?;
    if size <= first_adxr {
        return Some(0);
    }

    let per = (period as f64 - 1.0) / period as f64;
    let invper = 1.0 / period as f64;

    let mut dmup = 0.0;
    let mut dmdown = 0.0;

    // Initial period calculation
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
        (dm_diff / dm_sum) * 100.0
    };

    let mut adxr = *ti_buffer_new(period - 1)?;
    let mut output_idx = 0;

    for i in period as usize..size as usize {
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

        if (i - period as usize) < (period - 2) as usize {
            adx += dx;
        } else if (i - period as usize) == (period - 2) as usize {
            adx += dx;
            {
                adxr.vals[adxr.index as usize] = adx * invper;
                adxr.index = (adxr.index + 1) % adxr.size;
            }
        } else {
            adx = adx * per + dx;
            if i >= first_adxr as usize {
                output[output_idx] = 0.5
                    * ((adx * invper)
                        + adxr.vals[((adxr.index + adxr.size - 1) % adxr.size) as usize]);
                output_idx += 1;
            }
            {
                adxr.vals[adxr.index as usize] = adx * invper;
                adxr.index = (adxr.index + 1) % adxr.size;
            }
        }
    }

    ti_buffer_free(adxr);
    Some(0)
}
