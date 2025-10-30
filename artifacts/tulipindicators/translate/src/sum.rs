use crate::*;

pub fn ti_sum_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32 - 1,
        _ => -1, // Return -1 if options is None or empty (similar to NULL/empty array case in C)
    }
}
pub fn ti_sum(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None values (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let start = ti_sum_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut output_idx = 0;
    let mut sum = 0.0;

    // Calculate initial sum
    for i in 0..period {
        sum += input[i as usize];
    }

    output[output_idx] = sum;
    output_idx += 1;

    // Calculate rolling sum
    for i in period..size {
        let i_usize = i as usize;
        sum += input[i_usize];
        sum -= input[(i - period) as usize];
        output[output_idx] = sum;
        output_idx += 1;
    }

    // Assertion check (using debug_assert! which is removed in release builds)
    debug_assert!(
        (output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>())
            - output.as_ptr() as usize
            == ((size - start) as usize) * std::mem::size_of::<f64>()
    );

    0
}
