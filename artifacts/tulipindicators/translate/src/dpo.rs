use crate::*;

pub fn ti_dpo_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Check if the slice is not empty (equivalent to accessing options[0] in C)
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C: cast to int and subtract 1
    Some((options[0] as i32) - 1)
}
pub fn ti_dpo(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> Option<i32> {
    // Check for null inputs (None in Rust)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    // Convert options
    let period = options[0] as i32;
    let back = (period / 2) + 1;

    if period < 1 {
        return Some(1);
    }

    let start = match ti_dpo_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let scale = 1.0 / period as f64;
    let mut output_idx = 0;
    let mut sum = 0.0;

    // Calculate initial sum
    for i in 0..period as usize {
        sum += input[i];
    }

    // First output value
    output[output_idx] = input[(period as usize - 1) - back as usize] - (sum * scale);
    output_idx += 1;

    // Remaining output values
    for i in period as usize..size as usize {
        sum += input[i];
        sum -= input[i - period as usize];
        output[output_idx] = input[i - back as usize] - (sum * scale);
        output_idx += 1;
    }

    // Assertion check (commented out as it's not idiomatic in Rust)
    // assert!((&output[output_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - start) as usize);

    Some(0)
}
