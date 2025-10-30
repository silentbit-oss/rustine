use crate::*;
use rand::Rng;

pub fn ti_ultosc_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_ultosc_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    // If options is Some, safely access index 2 (Rust will panic if out of bounds)
    options.map_or(0, |opts| opts[2] as i32)
}
pub fn ti_ultosc(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_ultosc");
    // Check for None inputs (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];

    // Get options
    let short_period = options[0] as i32;
    let medium_period = options[1] as i32;
    let long_period = options[2] as i32;

    // Get output slice
    let output = &mut outputs[0];

    let mut output_idx = 0;

    // Validate periods
    if short_period < 1 || medium_period < short_period || long_period < medium_period {
        return 1;
    }

    if size <= ti_ultosc_start(Some(options)) {
        return 0;
    }

    // Create buffers
    let mut bp_buf = match ti_buffer_new(long_period) {
        Some(buf) => buf,
        None => return 1,
    };
    let mut r_buf = match ti_buffer_new(long_period) {
        Some(buf) => buf,
        None => return 1,
    };

    let mut bp_short_sum = 0.0;
    let mut bp_medium_sum = 0.0;
    let mut r_short_sum = 0.0;
    let mut r_medium_sum = 0.0;

    for i in 1..size as usize {
        let true_low = if low[i] < close[i - 1] { low[i] } else { close[i - 1] };
        let true_high = if high[i] > close[i - 1] { high[i] } else { close[i - 1] };
        let bp = close[i] - true_low;
        let r = true_high - true_low;

        bp_short_sum += bp;
        bp_medium_sum += bp;
        r_short_sum += r;
        r_medium_sum += r;

        // Update bp buffer
        {
            if bp_buf.pushes >= bp_buf.size {
                bp_buf.sum -= bp_buf.vals[bp_buf.index as usize];
            }
            bp_buf.sum += bp;
            bp_buf.vals[bp_buf.index as usize] = bp;
            bp_buf.pushes += 1;
            bp_buf.index = (bp_buf.index + 1) % bp_buf.size;
        }

        // Update r buffer
        {
            if r_buf.pushes >= r_buf.size {
                r_buf.sum -= r_buf.vals[r_buf.index as usize];
            }
            r_buf.sum += r;
            r_buf.vals[r_buf.index as usize] = r;
            r_buf.pushes += 1;
            r_buf.index = (r_buf.index + 1) % r_buf.size;
        }

        if i > short_period as usize {
            let mut short_index = (bp_buf.index - short_period) - 1;
            if short_index < 0 {
                short_index += long_period;
            }
            bp_short_sum -= bp_buf.vals[short_index as usize];
            r_short_sum -= r_buf.vals[short_index as usize];

            if i > medium_period as usize {
                let mut medium_index = (bp_buf.index - medium_period) - 1;
                if medium_index < 0 {
                    medium_index += long_period;
                }
                bp_medium_sum -= bp_buf.vals[medium_index as usize];
                r_medium_sum -= r_buf.vals[medium_index as usize];
            }
        }

        if i >= long_period as usize {
            let first = (4.0 * bp_short_sum) / r_short_sum;
            let second = (2.0 * bp_medium_sum) / r_medium_sum;
            let third = (1.0 * bp_buf.sum) / r_buf.sum;
            let ult = ((first + second + third) * 100.0) / 7.0;

            output[output_idx] = ult;
            output_idx += 1;
        }
    }

    // Free buffers
    ti_buffer_free(*bp_buf);
    ti_buffer_free(*r_buf);

    assert!((output.as_ptr() as usize + output_idx * std::mem::size_of::<f64>()) - 
            outputs[0].as_ptr() as usize == 
            ((size - ti_ultosc_start(Some(options))) as usize * std::mem::size_of::<f64>()));

    0
}
