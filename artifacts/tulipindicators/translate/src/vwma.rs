use crate::*;

pub fn ti_vwma_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL check in C)
    // If options is None, return 0 as a safe default (since we can't subtract 1 from nothing)
    // Alternatively, we could return an Option<i32> if the caller needs to handle this case
    let options = match options {
        Some(opts) => opts,
        None => return 0,
    };

    // Check if the slice is not empty before accessing index 0
    if options.is_empty() {
        return 0;
    }

    // Convert the first element to i32 and subtract 1 (same as C cast)
    (options[0] as i32) - 1
}
pub fn ti_vwma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for None (equivalent to NULL checks in C)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let mut outputs = outputs.ok_or(1)?;

    let input = inputs[0];
    let volume = inputs[1];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Err(1);
    }

    let start = ti_vwma_start(Some(options));
    if size <= start {
        return Ok(());
    }

    let mut sum = 0.0;
    let mut vsum = 0.0;
    let mut output_idx = 0;

    // Initial window calculation
    for i in 0..period as usize {
        sum += input[i] * volume[i];
        vsum += volume[i];
    }

    output[output_idx] = sum / vsum;
    output_idx += 1;

    // Rolling window calculation
    for i in period as usize..size as usize {
        sum += input[i] * volume[i];
        sum -= input[i - period as usize] * volume[i - period as usize];
        vsum += volume[i];
        vsum -= volume[i - period as usize];
        output[output_idx] = sum / vsum;
        output_idx += 1;
    }

    // Assertion check
    debug_assert!((output_idx as i32) == (size - start));
    
    Ok(())
}
