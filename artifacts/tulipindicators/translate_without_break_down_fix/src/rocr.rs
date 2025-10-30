use crate::*;

pub fn ti_rocr_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_rocr_start");
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
	println!("\n* ti_rocr");
    // Check for null inputs (Option::None)
    let input = match inputs {
        Some(inputs) => inputs[0],
        None => return Err(1),
    };

    let period = match options {
        Some(options) => options[0] as i32,
        None => return Err(1),
    };

    let output = match outputs {
        Some(outputs) => &mut outputs[0],
        None => return Err(1),
    };

    if period < 1 {
        return Err(1);
    }

    let start = ti_rocr_start(options);
    if size <= start {
        return Ok(());
    }

    let mut output_idx = 0;
    for i in period..size {
        output[output_idx] = input[i as usize] / input[(i - period) as usize];
        output_idx += 1;
    }

    // The assertion in C is not needed in safe Rust as bounds are checked
    Ok(())
}
