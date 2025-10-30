use crate::*;
use std::f64::consts::SQRT_2;
use std::assert;

pub fn ti_stddev_start(options: Option<&[f64]>) -> Option<i32> {
    options.map(|opts| opts[0] as i32 - 1)
}

pub fn ti_stddev(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None in all Option parameters
    let input = inputs?.get(0)?;
    let period = options?.get(0).map(|&x| x as i32)?;
    let output = outputs?.get_mut(0)?;
    
    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return Some(1);
    }

    let start = ti_stddev_start(options)?;
    if size <= start {
        return Some(0);
    }

    let mut sum = 0.0;
    let mut sum2 = 0.0;

    // Initial window calculation
    for i in 0..period as usize {
        let val = input.get(i)?;
        sum += val;
        sum2 += val * val;
    }

    // First output calculation
    {
        let s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        let s2s2 = if s2s2 > 0.0 { s2s2.sqrt() } else { s2s2 };
        *output.get_mut(output_idx)? = s2s2;
        output_idx += 1;
    }

    // Rolling window calculation
    for i in period as usize..size as usize {
        let new_val = input.get(i)?;
        let old_val = input.get(i - period as usize)?;

        sum += new_val;
        sum2 += new_val * new_val;
        sum -= old_val;
        sum2 -= old_val * old_val;

        let s2s2 = (sum2 * scale) - ((sum * scale) * (sum * scale));
        let s2s2 = if s2s2 > 0.0 { s2s2.sqrt() } else { s2s2 };
        *output.get_mut(output_idx)? = s2s2;
        output_idx += 1;
    }

    // Assertion check (Rust's assert! macro)
    assert!((output_idx as i32) == (size - start));

    Some(0)
}
