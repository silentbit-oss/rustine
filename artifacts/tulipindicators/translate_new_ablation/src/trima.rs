use crate::*;
use rand::Rng;

pub fn ti_trima_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_trima_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // Also ensure the slice has at least one element to avoid panic
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32 - 1,
        _ => -1, // Return -1 for invalid input (similar to NULL/error case in C)
    }
}

pub fn ti_trima(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_trima");
    // Early return if any input is None
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    if size <= ti_trima_start(Some(options)) {
        return 0;
    }

    if period <= 2 {
        return ti_sma(size, Some(inputs), Some(options), Some(outputs));
    }

    let weights = 1.0 / ((if period % 2 != 0 {
        ((period / 2) + 1) * ((period / 2) + 1)
    } else {
        ((period / 2) + 1) * (period / 2)
    }) as f64);

    let mut weight_sum = 0.0;
    let mut lead_sum = 0.0;
    let mut trail_sum = 0.0;

    let lead_period = if period % 2 != 0 {
        period / 2
    } else {
        (period / 2) - 1
    };
    let trail_period = lead_period + 1;

    let mut output_idx = 0;
    let mut w = 1;

    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * w as f64;

        if (i + 1) > (period - lead_period) as usize {
            lead_sum += input[i];
        }
        if (i + 1) <= trail_period as usize {
            trail_sum += input[i];
        }
        if (i + 1) < trail_period as usize {
            w += 1;
        }
        if (i + 1) >= (period - lead_period) as usize {
            w -= 1;
        }
    }

    let mut lsi = ((period - 1) - lead_period + 1) as usize;
    let mut tsi1 = (((period - 1) - period + 1) + trail_period) as usize;
    let mut tsi2 = ((period - 1) - period + 1) as usize;

    for i in (period - 1) as usize..size as usize {
        weight_sum += input[i];
        output[output_idx] = weight_sum * weights;
        output_idx += 1;

        lead_sum += input[i];
        weight_sum += lead_sum;
        weight_sum -= trail_sum;
        lead_sum -= input[lsi];
        lsi += 1;

        trail_sum += input[tsi1];
        tsi1 += 1;
        trail_sum -= input[tsi2];
        tsi2 += 1;
    }

    assert!((&output[output_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>()
        == (size - ti_trima_start(Some(options))) as usize);

    0
}
