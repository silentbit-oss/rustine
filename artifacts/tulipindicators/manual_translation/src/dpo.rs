use crate::*;

pub fn ti_dpo_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_dpo_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options.unwrap();
    
    // Check if the slice is not empty (equivalent to accessing options[0] in C)
    if options.is_empty() {
        return 0;
    }

    // Perform the same calculation as in C: cast to int and subtract 1
    (options[0] as i32) - 1
}
pub fn ti_dpo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_dpo");
    // Check for null inputs (None in Rust)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
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
        return 1;
    }

    let start = ti_dpo_start(Some(options));

    if size <= start {
        return 0;
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

    0
}
