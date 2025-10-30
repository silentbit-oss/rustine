use crate::*;
use libm::fabs;
use rand::Rng;
pub fn ti_vhf_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL pointer check in C)
    match options {
        Some(opts) => {
            // Safely access the first element, default to 0.0 if empty
            opts.first().map_or(0, |&val| val as i32)
        }
        None => 0, // Return 0 if options is None (NULL)
    }
}
pub fn ti_vhf(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Check if inputs and outputs have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }

    let in_ = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];

    if period < 1 {
        return 1;
    }

    let start = ti_vhf_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut output_idx = 0;
    let mut trail = 1;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = in_[0];
    let mut min = in_[0];
    let mut bar;
    let mut sum = 0.0;
    let mut yc = in_[0];
    let mut c;

    // First loop: sum absolute differences
    for i in 1..period as usize {
        c = in_[i];
        sum += unsafe { fabs(c - yc) };
        yc = c;
    }

    // Second loop: main processing
    for i in period as usize..size as usize {
        c = in_[i];
        sum += unsafe { fabs(c - yc) };
        yc = c;

        if i > period as usize {
            sum -= unsafe { fabs(in_[i - period as usize] - in_[i - period as usize - 1]) };
        }

        bar = c;

        // Handle max tracking
        if maxi < trail {
            maxi = trail;
            max = in_[maxi as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = in_[j as usize];
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i as i32;
            max = bar;
        }

        bar = c;

        // Handle min tracking
        if mini < trail {
            mini = trail;
            min = in_[mini as usize];
            let mut j = trail;
            while j <= i as i32 {
                bar = in_[j as usize];
                if bar <= min {
                    min = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min {
            mini = i as i32;
            min = bar;
        }

        output[output_idx] = unsafe { fabs(max - min) } / sum;
        output_idx += 1;
        trail += 1;
    }

    // Assertion check - fixed by adding ! to assert macro
    unsafe {
        assert!((output.as_ptr().add(output_idx) as isize - outputs[0].as_ptr() as isize)
            == (size - ti_vhf_start(Some(options))) as isize);
    }

    0
}
