use crate::*;
use libm::sqrt;
use rand::Rng;


pub fn ti_hma_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None or empty (equivalent to NULL check in C)
    let options = options?;
    if options.is_empty() {
        return None;
    }

    let period = options[0] as i32;
    let periodsqrt = sqrt(period as f64) as i32;
    Some((period + periodsqrt) - 2)
}

pub fn ti_hma(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs
    let inputs = inputs?;
    let options = options?;
    let outputs = outputs?;

    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return Some(1);
    }

    let start = ti_hma_start(Some(options))?;
    if size <= start {
        return Some(0);
    }

    let period2 = period / 2;
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

    // Initialize sums for the first period-1 elements
    for i in 0..(period - 1) {
        weight_sum += input[i as usize] * (i + 1) as f64;
        sum += input[i as usize];
        if i >= (period - period2) {
            weight_sum2 += input[i as usize] * ((i + 1) - (period - period2)) as f64;
            sum2 += input[i as usize];
        }
    }

    let mut buff = ti_buffer_new(periodsqrt)?;
    for i in (period - 1)..size {
        let i_usize = i as usize;
        let period_usize = period as usize;
        let period2_usize = period2 as usize;
        let periodsqrt_usize = periodsqrt as usize;

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
            let buff = buff.as_mut();
            buff.vals[buff.index as usize] = diff;
            buff.index = (buff.index + 1) % buff.size;
        }

        if i >= ((period - 1) + (periodsqrt - 1)) {
            output[output_idx] = weight_sumsqrt / weightssqrt;
            output_idx += 1;
            weight_sumsqrt -= sumsqrt;
            {
                let buff = buff.as_ref();
                let index = (((buff.index + buff.size) - 1) + 1) % buff.size;
                sumsqrt -= buff.vals[index as usize];
            }
        } else {
            weight_sumsqrt -= sumsqrt;
        }

        weight_sum -= sum;
        sum -= input[(i - period + 1) as usize];
        weight_sum2 -= sum2;
        sum2 -= input[(i - period2 + 1) as usize];
    }

    ti_buffer_free(*buff);
    Some(0)
}
