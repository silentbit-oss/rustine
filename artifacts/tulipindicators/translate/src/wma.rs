use crate::*;

pub fn ti_wma_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if !opts.is_empty() {
            Some(opts[0] as i32 - 1)
        } else {
            None
        }
    })
}
pub fn ti_wma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in all Option parameters
    let input = inputs?.get(0)?;
    let period = options?.get(0).map(|&p| p as i32)?;
    let output = outputs?.get_mut(0)?;

    if period < 1 {
        return Some(1);
    }

    let start = ti_wma_start(options)?;
    if size <= start {
        return Some(0);
    }

    let weights = (period * (period + 1)) as f64 / 2.0;
    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    let mut output_idx = 0;

    // First loop: period - 1 iterations
    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * (i + 1) as f64;
        sum += input[i];
    }

    // Second loop: from period-1 to size-1
    for i in (period - 1) as usize..size as usize {
        weight_sum += input[i] * period as f64;
        sum += input[i];
        output[output_idx] = weight_sum / weights;
        output_idx += 1;
        weight_sum -= sum;
        sum -= input[(i - (period as usize - 1))];
    }

    // Assert equivalent - in Rust we'd normally use debug_assert! but since we're returning Option,
    // we'll just verify the condition matches expected behavior
    debug_assert_eq!(
        output_idx,
        (size - start) as usize,
        "Output index mismatch"
    );

    Some(0)
}
