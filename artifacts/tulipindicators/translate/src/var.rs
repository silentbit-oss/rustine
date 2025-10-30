use crate::*;

pub fn ti_var_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}
pub fn ti_var(
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
    let outputs = outputs.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return Some(1);
    }

    let input = inputs[0];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    if period < 1 {
        return Some(1);
    }

    let ti_start = match ti_var_start(Some(options)) {
        Some(val) => val,
        None => return Some(1),
    };

    if size <= ti_start {
        return Some(0);
    }

    let scale = 1.0 / period as f64;
    let mut output_idx = 0;
    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // First window calculation
    for i in 0..period {
        let val = input[i as usize];
        sum += val;
        sum2 += val * val;
    }

    output[output_idx as usize] = (sum2 * scale) - ((sum * scale) * (sum * scale));
    output_idx += 1;

    // Rolling window calculation
    for i in period..size {
        let new_val = input[i as usize];
        let old_val = input[(i - period) as usize];

        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;

        output[output_idx as usize] = (sum2 * scale) - ((sum * scale) * (sum * scale));
        output_idx += 1;
    }

    // Assert equivalent - we'll just check the condition and return an error if it fails
    if (output_idx as i32) != (size - ti_start) {
        return Some(1);
    }

    Some(0)
}
