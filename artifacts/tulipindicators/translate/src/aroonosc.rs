use crate::*;

pub fn ti_aroonosc_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access the first element or default to 0.0
    options.and_then(|opts| opts.first()).map_or(0, |&val| val as i32)
}
pub fn helper_ti_aroonosc_1(
    output_idx_ref: &mut u32,
    maxi_ref: &mut i32,
    mini_ref: &mut i32,
    max_ref: &mut f64,
    min_ref: &mut f64,
    j_ref: &mut i32,
    high: &[f64],
    low: &[f64],
    output: &mut [f64],
    scale: f64,
    trail: i32,
    i: i32,
) {
    let mut output_idx = *output_idx_ref;
    let mut maxi = *maxi_ref;
    let mut mini = *mini_ref;
    let mut max = *max_ref;
    let mut min = *min_ref;
    let mut j = *j_ref;
    
    let mut bar = high[i as usize];
    
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
    
    output[output_idx as usize] = (maxi - mini) as f64 * scale;
    output_idx += 1;
    
    *output_idx_ref = output_idx;
    *maxi_ref = maxi;
    *mini_ref = mini;
    *max_ref = max;
    *min_ref = min;
    *j_ref = j;
}
pub fn ti_aroonosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for NULL equivalents in Rust (None)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let outputs = outputs.ok_or(1)?;

    // Get slices from inputs and outputs
    let high = inputs[0];
    let low = inputs[1];
    let output = &mut outputs[0];

    let mut output_idx: u32 = 0;
    let period = options[0] as i32;

    if period < 1 {
        return Err(1);
    }

    let start = ti_aroonosc_start(Some(options));
    if size <= start {
        return Ok(());
    }

    let scale = 100.0 / period as f64;
    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = high[0];
    let mut min = low[0];

    for i in period..size {
        helper_ti_aroonosc_1(
            &mut output_idx,
            &mut maxi,
            &mut mini,
            &mut max,
            &mut min,
            &mut 0, // j is initialized to 0 in C code (line 23)
            high,
            low,
            output,
            scale,
            trail,
            i,
        );
        trail += 1;
    }

    // Assert equivalent in Rust
    debug_assert!(
        (output[output_idx as usize] - outputs[0][0]) == (size - ti_aroonosc_start(Some(options))) as f64
    );

    Ok(())
}
