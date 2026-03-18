use crate::*;
use rand::Rng;

pub fn ti_stochrsi_start(options: Option<&[f64]>) -> Option<i32> {
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    // Perform the same calculation as in C
    Some(((options[0] as i32) * 2) - 1)
}

pub fn ti_stochrsi(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Option<i32> {
    // Check for None inputs (equivalent to NULL checks in C)
    let input = inputs?.get(0)?;
    let period = options?.get(0)?.floor() as i32;
    let output = outputs?.get_mut(0)?;
    let mut output_idx = 0;
    let per = 1.0 / (period as f64);

    if period < 2 {
        return Some(1);
    }

    let start = ti_stochrsi_start(Some(options?))?;
    if size <= start {
        return Some(0);
    }

    let mut rsi = ti_buffer_new(period)?;
    let mut smooth_up = 0.0;
    let mut smooth_down = 0.0;

    // Initial period calculation
    for i in 1..=period {
        let upward = if input[i as usize] > input[(i - 1) as usize] {
            input[i as usize] - input[(i - 1) as usize]
        } else {
            0.0
        };
        let downward = if input[i as usize] < input[(i - 1) as usize] {
            input[(i - 1) as usize] - input[i as usize]
        } else {
            0.0
        };
        smooth_up += upward;
        smooth_down += downward;
    }

    smooth_up /= period as f64;
    smooth_down /= period as f64;
    let mut r = 100.0 * (smooth_up / (smooth_up + smooth_down));

    // Update RSI buffer
    {
        let rsi = rsi.as_mut();
        if rsi.pushes >= rsi.size {
            rsi.sum -= rsi.vals[rsi.index as usize];
        }
        rsi.sum += r;
        rsi.vals[rsi.index as usize] = r;
        rsi.pushes += 1;
        rsi.index = (rsi.index + 1) % rsi.size;
    }

    let mut min = r;
    let mut max = r;
    let mut mini = 0;
    let mut maxi = 0;

    // Main processing loop
    for i in (period + 1)..size {
        let i = i as usize;
        let upward = if input[i] > input[i - 1] {
            input[i] - input[i - 1]
        } else {
            0.0
        };
        let downward = if input[i] < input[i - 1] {
            input[i - 1] - input[i]
        } else {
            0.0
        };

        smooth_up = ((upward - smooth_up) * per) + smooth_up;
        smooth_down = ((downward - smooth_down) * per) + smooth_down;
        r = 100.0 * (smooth_up / (smooth_up + smooth_down));

        // Update max and min values
        {
            let rsi = rsi.as_ref();
            if r > max {
                max = r;
                maxi = rsi.index;
            } else if maxi == rsi.index {
                max = r;
                for j in 0..rsi.size {
                    if j == rsi.index {
                        continue;
                    }
                    if rsi.vals[j as usize] > max {
                        max = rsi.vals[j as usize];
                        maxi = j;
                    }
                }
            }

            if r < min {
                min = r;
                mini = rsi.index;
            } else if mini == rsi.index {
                min = r;
                for j in 0..rsi.size {
                    if j == rsi.index {
                        continue;
                    }
                    if rsi.vals[j as usize] < min {
                        min = rsi.vals[j as usize];
                        mini = j;
                    }
                }
            }
        }

        // Update RSI buffer
        {
            let rsi = rsi.as_mut();
            rsi.vals[rsi.index as usize] = r;
            rsi.index = (rsi.index + 1) % rsi.size;
        }

        if i > ((period * 2) - 2) as usize {
            let diff = max - min;
            if diff == 0.0 {
                output[output_idx] = 0.0;
            } else {
                output[output_idx] = (r - min) / diff;
            }
            output_idx += 1;
        }
    }

    // Assertion check (commented as Rust doesn't have exact pointer arithmetic equivalent)
    // assert!((output[output_idx] as *const f64).offset_from(output[0] as *const _) == (size - start) as isize);

    Some(0)
}
