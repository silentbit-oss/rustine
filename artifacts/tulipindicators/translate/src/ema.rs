use crate::*;

pub fn ti_ema_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_ema(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Result<(), i32> {
    // Check for null inputs/outputs (Option::None case)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let outputs = outputs.ok_or(1)?;

    // Get slices from inputs and outputs
    let input = inputs[0];
    let output = &mut outputs[0];

    // Check period validity
    let period = options[0] as i32;
    if period < 1 {
        return Err(1);
    }

    // Check size validity
    let start = ti_ema_start(Some(options));
    if size <= start {
        return Ok(());
    }

    let per = 2.0 / (period as f64 + 1.0);
    let mut val = input[0];
    let mut output_idx = 0;

    output[output_idx] = val;
    output_idx += 1;

    for i in 1..size as usize {
        val = ((input[i] - val) * per) + val;
        output[output_idx] = val;
        output_idx += 1;
    }

    // Assertion check (using debug_assert! since it's a debugging aid)
    debug_assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>() - output.as_ptr() as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    Ok(())
}
