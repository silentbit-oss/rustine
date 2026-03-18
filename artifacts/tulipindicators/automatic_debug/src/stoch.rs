use crate::*;
use rand::Rng;

pub fn ti_stoch_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_stoch_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;

    // Ensure the slice has at least 3 elements to avoid panic
    if options.len() < 3 {
        return None;
    }

    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;

    Some(((kperiod + kslow) + dperiod) - 3)
}
pub fn ti_stoch(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_stoch");
    // Check for None inputs
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    // Unwrap the input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];

    // Extract options with bounds checking
    if options.len() < 3 {
        return Some(1);
    }
    let kperiod = options[0] as i32;
    let kslow = options[1] as i32;
    let dperiod = options[2] as i32;

    // Validate parameters
    if kperiod < 1 || kslow < 1 || dperiod < 1 {
        return Some(1);
    }

    let kper = 1.0 / kslow as f64;
    let dper = 1.0 / dperiod as f64;

    // Get output slices with bounds checking
    if outputs.len() < 2 {
        return Some(1);
    }
    let (stoch, stoch_ma) = {
        let (first, rest) = outputs.split_at_mut(1);
        (&mut first[0], &mut rest[0])
    };

    let start = ti_stoch_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar;

    let mut k_sum = ti_buffer_new(kslow)?;
    let mut d_sum = ti_buffer_new(dperiod)?;

    for i in 0..size as usize {
        if i >= kperiod as usize {
            trail += 1;
        }

        // Find max
        bar = high[i];
        if maxi < trail {
            maxi = trail;
            max = high[maxi as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = high[j as usize];
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i as i32;
            max = bar;
        }

        // Find min
        bar = low[i];
        if mini < trail {
            mini = trail;
            min = low[mini as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = low[j as usize];
                if bar <= min {
                    min = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min {
            mini = i as i32;
            min = bar;
        }

        let kdiff = max - min;
        let kfast = if kdiff == 0.0 {
            0.0
        } else {
            100.0 * ((close[i] - min) / kdiff)
        };

        // Update k_sum buffer
        {
            if k_sum.pushes >= k_sum.size {
                k_sum.sum -= k_sum.vals[k_sum.index as usize];
            }
            k_sum.sum += kfast;
            k_sum.vals[k_sum.index as usize] = kfast;
            k_sum.pushes += 1;
            k_sum.index += 1;
            if k_sum.index >= k_sum.size {
                k_sum.index = 0;
            }
        }

        if i >= ((kperiod - 1) + kslow - 1) as usize {
            let k = k_sum.sum * kper;

            // Update d_sum buffer
            {
                if d_sum.pushes >= d_sum.size {
                    d_sum.sum -= d_sum.vals[d_sum.index as usize];
                }
                d_sum.sum += k;
                d_sum.vals[d_sum.index as usize] = k;
                d_sum.pushes += 1;
                d_sum.index += 1;
                if d_sum.index >= d_sum.size {
                    d_sum.index = 0;
                }
            }

            if i >= (((kperiod - 1) + kslow - 1) + dperiod - 1) as usize {
                let stoch_idx = (i - (((kperiod - 1) + kslow - 1) + dperiod - 1) as usize);
                let stoch_ma_idx = stoch_idx;

                if stoch_idx < stoch.len() && stoch_ma_idx < stoch_ma.len() {
                    stoch[stoch_idx] = k;
                    stoch_ma[stoch_ma_idx] = d_sum.sum * dper;
                }
            }
        }
    }

    Some(0)
}
