use crate::*;
use libm::sqrt;


pub fn ti_hma_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    let periodsqrt = sqrt(options[0]) as i32;
    Some((period + periodsqrt) - 2)
}
pub fn helper_ti_hma_1(
    output_idx_ref: &mut u32,
    sum_ref: &mut f64,
    weight_sum_ref: &mut f64,
    sum2_ref: &mut f64,
    weight_sum2_ref: &mut f64,
    sumsqrt_ref: &mut f64,
    weight_sumsqrt_ref: &mut f64,
    input: &[f64],
    period: i32,
    output: &mut [f64],
    period2: i32,
    periodsqrt: i32,
    weights: f64,
    weights2: f64,
    weightssqrt: f64,
    i: i32,
    buff: &mut TiBuffer,
) {
    let mut output_idx = *output_idx_ref;
    let mut sum = *sum_ref;
    let mut weight_sum = *weight_sum_ref;
    let mut sum2 = *sum2_ref;
    let mut weight_sum2 = *weight_sum2_ref;
    let mut sumsqrt = *sumsqrt_ref;
    let mut weight_sumsqrt = *weight_sumsqrt_ref;

    let i_usize = i as usize;
    weight_sum += input[i_usize] * period as f64;
    sum += input[i_usize];
    weight_sum2 += input[i_usize] * period2 as f64;
    sum2 += input[i_usize];

    let wma = weight_sum / weights;
    let wma2 = weight_sum2 / weights2;
    let diff = (2.0 * wma2) - wma;

    weight_sumsqrt += diff * periodsqrt as f64;
    sumsqrt += diff;

    {
        buff.vals[buff.index as usize] = diff;
        buff.index += 1;
        if buff.index >= buff.size {
            buff.index = 0;
        }
    }

    if i >= ((period - 1) + (periodsqrt - 1)) {
        output[output_idx as usize] = weight_sumsqrt / weightssqrt;
        output_idx += 1;
        weight_sumsqrt -= sumsqrt;
        let buff_size = buff.size as usize;
        let index = ((buff.index + buff.size - 1) + 1) as usize % buff_size;
        sumsqrt -= buff.vals[index];
    } else {
        weight_sumsqrt -= sumsqrt;
    }

    weight_sum -= sum;
    sum -= input[(i - period + 1) as usize];
    weight_sum2 -= sum2;
    sum2 -= input[(i - period2 + 1) as usize];

    *output_idx_ref = output_idx;
    *sum_ref = sum;
    *weight_sum_ref = weight_sum;
    *sum2_ref = sum2;
    *weight_sum2_ref = weight_sum2;
    *sumsqrt_ref = sumsqrt;
    *weight_sumsqrt_ref = weight_sumsqrt;
}

pub fn ti_hma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for null inputs/outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return Some(1);
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start = match ti_hma_start(Some(options)) {
        Some(s) => s,
        None => return Some(1),
    };

    if size <= start {
        return Some(0);
    }

    let period2 = (period / 2) as i32;
    let periodsqrt = sqrt(period as f64) as i32;
    let weights = (period * (period + 1)) as f64 / 2.0;
    let weights2 = (period2 * (period2 + 1)) as f64 / 2.0;
    let weightssqrt = (periodsqrt * (periodsqrt + 1)) as f64 / 2.0;

    let mut sum = 0.0;
    let mut weight_sum = 0.0;
    let mut sum2 = 0.0;
    let mut weight_sum2 = 0.0;
    let mut sumsqrt = 0.0;
    let mut weight_sumsqrt = 0.0;
    let mut output_idx = 0;

    for i in 0..(period - 1) as usize {
        weight_sum += input[i] * (i + 1) as f64;
        sum += input[i];

        if i >= (period - period2) as usize {
            weight_sum2 += input[i] * ((i + 1) - (period - period2) as usize) as f64;
            sum2 += input[i];
        }
    }

    let mut buff = match ti_buffer_new(periodsqrt) {
        Some(b) => b,
        None => return Some(1),
    };

    for i in (period - 1)..size {
        helper_ti_hma_1(
            &mut output_idx,
            &mut sum,
            &mut weight_sum,
            &mut sum2,
            &mut weight_sum2,
            &mut sumsqrt,
            &mut weight_sumsqrt,
            input,
            period,
            output,
            period2,
            periodsqrt,
            weights,
            weights2,
            weightssqrt,
            i,
            &mut buff,
        );
    }

    ti_buffer_free(*buff);

    assert!((output[output_idx as usize] - outputs[0][0]) == (size - start) as f64);
    Some(0)
}
