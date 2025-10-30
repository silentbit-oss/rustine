use crate::*;

pub fn ti_rocr_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    // and if the slice has at least one element
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32,
        _ => 0, // Default return value when options is None or empty
    }
}
pub fn ti_rocr(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for None values (equivalent to NULL checks in C)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let outputs = outputs.ok_or(1)?;

    // Get the input and output slices
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    // Early returns for invalid conditions (lines 7-14)
    if period < 1 {
        return Err(1);
    }

    let start = ti_rocr_start(Some(options));
    if size <= start {
        return Ok(());
    }

    // Calculate the output values (lines 16-20)
    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[i as usize] / input[(i - period) as usize];
        output_idx += 1;
    }

    // Assertion check (line 22)
    debug_assert!(
        (output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - outputs[0].as_ptr() as usize
            == ((size - start) as usize) * std::mem::size_of::<f64>()
    );

    Ok(())
}
