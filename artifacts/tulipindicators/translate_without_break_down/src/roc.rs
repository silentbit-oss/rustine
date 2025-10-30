use crate::*;
use rand::Rng;

pub fn ti_roc_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) => opts[0] as i32,
        None => 0, // Default behavior when NULL is passed
    }
}

pub fn ti_roc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<(), i32> {
    // Check for None in inputs, options, and outputs (equivalent to NULL checks in C)
    let inputs = inputs.ok_or(1)?;
    let options = options.ok_or(1)?;
    let mut outputs = outputs.ok_or(1)?;

    // Get input and output slices (equivalent to C pointer dereferencing)
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    // Early returns for invalid conditions (lines 7-14 in C)
    if period < 1 {
        return Err(1);
    }
    let start = ti_roc_start(Some(options));
    if size <= start {
        return Ok(());
    }

    // Calculate ROC values (lines 16-20 in C)
    let mut output_idx = 0;
    for i in period..size {
        let denominator = input[(i - period) as usize];
        output[output_idx] = (input[i as usize] - denominator) / denominator;
        output_idx += 1;
    }

    // Assertion check (line 22 in C)
    debug_assert_eq!(
        output_idx as i32,
        size - ti_roc_start(Some(options))
    );

    Ok(())
}
