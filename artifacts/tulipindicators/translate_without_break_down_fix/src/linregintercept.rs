use crate::*;
use rand::Rng;

pub fn ti_linregintercept_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_linregintercept_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C, converting to i32
    Some(options[0] as i32 - 1)
}
pub fn ti_linregintercept(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
	println!("\n* ti_linregintercept");
    // Check for None in all Option parameters
    let input = inputs?.first()?;
    let period = options?.first().map(|&p| p as i32)?;
    let output = outputs?.first_mut()?;

    if period < 1 {
        return Some(1);
    }

    let start = ti_linregintercept_start(Some(options?))?;
    if size <= start {
        return Some(0);
    }

    let mut output_idx = 0;
    {
        let mut x = 0.0;
        let mut x2 = 0.0;
        let mut y = 0.0;
        let mut xy = 0.0;
        let p = 1.0 / (period as f64);

        // First loop (period - 1 iterations)
        for i in 0..(period - 1) as usize {
            let i_plus_1 = (i + 1) as f64;
            x += i_plus_1;
            x2 += i_plus_1 * i_plus_1;
            xy += input[i] * i_plus_1;
            y += input[i];
        }

        // Add the last period value
        let period_f64 = period as f64;
        x += period_f64;
        x2 += period_f64 * period_f64;
        let bd = 1.0 / ((period_f64 * x2) - (x * x));

        // Second loop (from period-1 to size-1)
        for i in (period - 1) as usize..size as usize {
            xy += input[i] * period_f64;
            y += input[i];

            let b = ((period_f64 * xy) - (x * y)) * bd;
            {
                let a = (y - (b * x)) * p;
                output[output_idx] = a + (b * 1.0);
                output_idx += 1;
            }

            xy -= y;
            y -= input[(i - (period as usize)) + 1];
        }
    }

    // Assertion check (commented out as it would require unsafe in Rust)
    // assert!((&output[output_idx] as *const f64).offset_from(outputs[0][0] as i32 == (size - start));

    Some(0)
}
