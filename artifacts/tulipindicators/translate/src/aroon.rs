use crate::*;
use std::assert;

pub fn ti_aroon_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}
pub fn helper_ti_aroon_1(
    adown_idx_ref: &mut u32,
    aup_idx_ref: &mut u32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    bar_ref: &mut f64,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    adown: &mut [f64],
    aup: &mut [f64],
    period: i32,
    scale: f64,
    trail: i32,
    i: i32,
) {
    let mut adown_idx = *adown_idx_ref;
    let mut aup_idx = *aup_idx_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut bar = *bar_ref;
    let mut j = *j_ref;

    bar = high[i as usize];
    if maxi < trail {
        maxi = trail;
        max = high[maxi as usize];
        j = trail;
        let mut current_j = j + 1;
        while current_j <= i {
            bar = high[current_j as usize];
            if bar >= max {
                max = bar;
                maxi = current_j;
            }
            current_j += 1;
        }
    } else if bar >= max {
        maxi = i;
        max = bar;
    }

    bar = low[i as usize];
    if mini < trail {
        mini = trail;
        min = low[mini as usize];
        j = trail;
        let mut current_j = j + 1;
        while current_j <= i {
            bar = low[current_j as usize];
            if bar <= min {
                min = bar;
                mini = current_j;
            }
            current_j += 1;
        }
    } else if bar <= min {
        mini = i;
        min = bar;
    }

    adown[adown_idx as usize] = ((f64::from(period)) - (i - mini) as f64) * scale;
    adown_idx += 1;
    aup[aup_idx as usize] = ((f64::from(period)) - (i - maxi) as f64) * scale;
    aup_idx += 1;

    *adown_idx_ref = adown_idx;
    *aup_idx_ref = aup_idx;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *bar_ref = bar;
    *j_ref = j;
}
pub fn ti_aroon(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Unwrap inputs safely
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let high = inputs[0];
    let low = inputs[1];

    // Unwrap outputs safely and split into two mutable parts
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };
    let (adown_slice, aup_slice) = outputs.split_at_mut(1);
    let adown = &mut adown_slice[0];
    let mut adown_idx: u32 = 0;
    let aup = &mut aup_slice[0];
    let mut aup_idx: u32 = 0;

    // Unwrap options safely
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    if size <= ti_aroon_start(Some(options)) {
        return 0;
    }

    let scale = 100.0 / period as f64;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];
    let mut bar = 0.0;
    let mut j = 0;

    for i in period..size {
        helper_ti_aroon_1(
            &mut adown_idx,
            &mut aup_idx,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut bar,
            &mut j,
            high,
            low,
            adown,
            aup,
            period,
            scale,
            trail,
            i,
        );
        trail += 1;
    }

    // Convert assertions to debug assertions
    debug_assert!((adown.as_ptr().wrapping_offset(adown_idx as isize) as usize - adown_slice[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_aroon_start(Some(options))) as usize);
    debug_assert!((aup.as_ptr().wrapping_offset(aup_idx as isize) as usize - aup_slice[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_aroon_start(Some(options))) as usize);

    0
}
