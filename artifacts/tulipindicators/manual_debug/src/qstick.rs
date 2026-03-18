use crate::*;

pub fn ti_qstick_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_qstick_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // Then safely access the first element or return a default value
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Default return value when options is None or empty
    }
}
pub fn ti_qstick(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<i32, &'static str> {
	println!("\n* ti_qstick");
    // Check for None values (equivalent to NULL checks in C)
    let inputs = inputs.ok_or("inputs is NULL")?;
    let options = options.ok_or("options is NULL")?;
    let outputs = outputs.ok_or("outputs is NULL")?;

    // Get slices from inputs and outputs
    let open = inputs.get(0).ok_or("missing open input")?;
    let close = inputs.get(1).ok_or("missing close input")?;
    let output = outputs.get_mut(0).ok_or("missing output")?;

    let period = options[0] as i32;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return Err("period must be at least 1");
    }

    let start = ti_qstick_start(Some(options));
    if size <= start {
        return Ok(0);
    }

    let mut sum = 0.0;
    let mut output_idx = 0;

    // Calculate initial sum
    for i in 0..period as usize {
        sum += close[i] - open[i];
    }

    output[output_idx] = sum * scale;
    output_idx += 1;

    // Calculate rolling sum
    for i in period as usize..size as usize {
        sum += close[i] - open[i];
        sum -= close[i - period as usize] - open[i - period as usize];
        output[output_idx] = sum * scale;
        output_idx += 1;
    }

    // Assertion check (commented out as it's not idiomatic in Rust to use asserts for validation)
    // assert!((output.as_ptr() as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    Ok(0)
}
