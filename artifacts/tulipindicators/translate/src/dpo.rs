use crate::*;

pub fn ti_dpo_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}
pub fn ti_dpo(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let mut outputs = outputs.unwrap();

    let input = inputs[0];
    let period = options[0] as i32;
    let back = (period / 2) + 1;
    let output = &mut outputs[0];
    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

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

    let mut sum = 0.0;
    for i in 0..period {
        sum += input[i as usize];
    }

    output[output_idx] = input[(period - 1 - back) as usize] - (sum * scale);
    output_idx += 1;

    for i in period..size {
        let i_usize = i as usize;
        sum += input[i_usize];
        sum -= input[(i - period) as usize];
        output[output_idx] = input[(i - back) as usize] - (sum * scale);
        output_idx += 1;
    }

    // Assertion check (Rust's assert! macro is similar to C's assert)
    assert!((output.as_ptr() as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - start) as usize);

    Some(0)
}
