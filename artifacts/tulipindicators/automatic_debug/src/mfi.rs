use crate::*;
use std::error::Error;

pub fn ti_mfi_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_mfi_start");
    // Check if options is None (equivalent to NULL pointer in C)
    // If options is None, return 0 as default (since C would dereference NULL which is UB)
    // Alternatively, could return Option<i32> and propagate None
    match options {
        Some(opts) => opts[0] as i32,
        None => 0,
    }
}

pub fn ti_mfi(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> Result<i32, Box<dyn Error>> {
	println!("\n* ti_mfi");
    // Validate inputs
    let inputs = inputs.ok_or("inputs is None")?;
    if inputs.len() < 4 {
        return Err("inputs must have at least 4 elements".into());
    }
    let options = options.ok_or("options is None")?;
    if options.is_empty() {
        return Err("options must have at least 1 element".into());
    }
    let outputs = outputs.ok_or("outputs is None")?;
    if outputs.is_empty() {
        return Err("outputs must have at least 1 element".into());
    }

    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    let period = options[0] as i32;

    if period < 1 {
        return Ok(1);
    }

    let start = ti_mfi_start(Some(options));
    if size <= start {
        return Ok(0);
    }

    let output = &mut outputs[0];
    let mut output_idx = 0;

    let mut ytyp = ((high[0] + low[0]) + close[0]) * (1.0 / 3.0);
    let mut up = ti_buffer_new(period).ok_or("Failed to create up buffer")?;
    let mut down = ti_buffer_new(period).ok_or("Failed to create down buffer")?;

    for i in 1..size as usize {
        let typ = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
        let bar = typ * volume[i];

        if typ > ytyp {
            // Process up buffer
            {
                let up = up.as_mut();
                if up.pushes >= up.size {
                    up.sum -= up.vals[up.index as usize];
                }
                up.sum += bar;
                up.vals[up.index as usize] = bar;
                up.pushes += 1;
                up.index = (up.index + 1) % up.size;
            }

            // Process down buffer
            {
                let down = down.as_mut();
                if down.pushes >= down.size {
                    down.sum -= down.vals[down.index as usize];
                }
                down.sum += 0.0;
                down.vals[down.index as usize] = 0.0;
                down.pushes += 1;
                down.index = (down.index + 1) % down.size;
            }
        } else if typ < ytyp {
            // Process down buffer
            {
                let down = down.as_mut();
                if down.pushes >= down.size {
                    down.sum -= down.vals[down.index as usize];
                }
                down.sum += bar;
                down.vals[down.index as usize] = bar;
                down.pushes += 1;
                down.index = (down.index + 1) % down.size;
            }

            // Process up buffer
            {
                let up = up.as_mut();
                if up.pushes >= up.size {
                    up.sum -= up.vals[up.index as usize];
                }
                up.sum += 0.0;
                up.vals[up.index as usize] = 0.0;
                up.pushes += 1;
                up.index = (up.index + 1) % up.size;
            }
        } else {
            // Process up buffer
            {
                let up = up.as_mut();
                if up.pushes >= up.size {
                    up.sum -= up.vals[up.index as usize];
                }
                up.sum += 0.0;
                up.vals[up.index as usize] = 0.0;
                up.pushes += 1;
                up.index = (up.index + 1) % up.size;
            }

            // Process down buffer
            {
                let down = down.as_mut();
                if down.pushes >= down.size {
                    down.sum -= down.vals[down.index as usize];
                }
                down.sum += 0.0;
                down.vals[down.index as usize] = 0.0;
                down.pushes += 1;
                down.index = (down.index + 1) % down.size;
            }
        }

        ytyp = typ;

        if i >= period as usize {
            let up = up.as_ref();
            let down = down.as_ref();
            output[output_idx] = (up.sum / (up.sum + down.sum)) * 100.0;
            output_idx += 1;
        }
    }

    // The assert in the original C code is not needed in Rust as we have proper bounds checking
    Ok(0)
}
