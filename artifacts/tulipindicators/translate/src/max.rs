use crate::*;

pub fn ti_max_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}
pub fn ti_max(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let input = inputs.unwrap()[0];
    let period = options.unwrap()[0] as i32;
    let output = &mut outputs.unwrap()[0];

    if period < 1 {
        return Some(1);
    }

    let ti_max_start = match ti_max_start(options) {
        Some(val) => val,
        None => return Some(1),
    };

    if size <= ti_max_start {
        return Some(0);
    }

    let mut output_idx = 0;
    let mut trail = 0;
    let mut maxi = -1;
    let mut max = input[0];

    for i in period - 1..size {
        let bar = input[i as usize];
        if maxi < trail {
            maxi = trail;
            max = input[maxi as usize];
            let mut j = trail;
            while j <= i {
                let bar = input[j as usize];
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i;
            max = bar;
        }

        output[output_idx as usize] = max;
        output_idx += 1;
        trail += 1;
    }

    // In Rust, we don't typically use asserts for control flow
    // The original C assert is removed as it's not idiomatic in Rust
    // and would panic rather than return an error code

    Some(0)
}
pub fn ti_max_ref(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Early return if any input is None
    let inputs = match inputs {
        Some(inputs) => inputs,
        None => return 1,
    };
    let options = match options {
        Some(options) => options,
        None => return 1,
    };
    let outputs = match outputs {
        Some(outputs) => outputs,
        None => return 1,
    };

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if period < 1 {
        return 1;
    }

    if let Some(start) = ti_max_start(Some(options)) {
        if size <= start {
            return 0;
        }
    } else {
        return 1;
    }

    for i in (period - 1)..size {
        let mut max = input[(i - period + 1) as usize];
        for j in (i - period + 2)..=i {
            let val = input[j as usize];
            if val > max {
                max = val;
            }
        }

        output[output_idx as usize] = max;
        output_idx += 1;
    }

    0
}
