use crate::*;

pub fn ti_mom_start(options: Option<&[f64]>) -> i32 {
    // Use Option<&[f64]> to safely handle potential NULL pointer
    // Unwrap the Option or return 0 (default behavior when NULL in C)
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0,
    }
}
pub fn ti_mom(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Result<(), i32> {
    // Check for null inputs (equivalent to NULL checks in C)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let mut outputs = outputs.ok_or(1)?;

    // Get the input and output slices
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    // Validate period (line 7-10)
    if period < 1 {
        return Err(1);
    }

    // Check size condition (line 11-14)
    let start = ti_mom_start(Some(options));
    if size <= start {
        return Ok(());
    }

    // Calculate momentum (line 15-20)
    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[i as usize] - input[(i - period) as usize];
        output_idx += 1;
    }

    // Assertion check (line 22)
    debug_assert!((output_idx as i32) == (size - start));

    Ok(())
}
