use crate::*;
use std::f64::consts::LN_2;

pub fn ti_fisher_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_fisher_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options.unwrap();
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return 0;
    }

    // Perform the same calculation as in C, converting to i32
    options[0] as i32 - 1
}
pub fn ti_fisher(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_fisher");
    // Check for None inputs
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    if inputs.len() < 2 {
        return 0;
    }
    // Get slices from inputs
    let high = inputs[0];
    let low = inputs[1];

    // Split outputs into two mutable slices
    let (fisher, signal) = {
        let (first, second) = outputs.split_at_mut(1);
        (&mut first[0], &mut second[0])
    };

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_fisher_start(Some(options));
    if size <= start {
        return 0;
    }

    let mut trail = 0;
    let mut maxi = -1;
    let mut mini = -1;
    let mut max = 0.5 * (high[0] + low[0]);
    let mut min = 0.5 * (high[0] + low[0]);
    let mut val1 = 0.0;
    let mut fish = 0.0;

    for i in period - 1..size {
        let mut bar = 0.5 * (high[i as usize] + low[i as usize]);

        if maxi < trail {
            maxi = trail;
            max = 0.5 * (high[maxi as usize] + low[maxi as usize]);
            let mut j = trail;
            while j <= i {
                bar = 0.5 * (high[j as usize] + low[j as usize]);
                if bar >= max {
                    max = bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max {
            maxi = i;
            max = bar;
        }

        bar = 0.5 * (high[i as usize] + low[i as usize]);
        if mini < trail {
            mini = trail;
            min = 0.5 * (high[mini as usize] + low[mini as usize]);
            let mut j = trail;
            while j <= i {
                bar = 0.5 * (high[j as usize] + low[j as usize]);
                if bar <= min {
                    min = bar;
                    mini = j;
                }
                j += 1;
            }
        } else if bar <= min {
            mini = i;
            min = bar;
        }

        let mut mm = max - min;
        if mm == 0.0 {
            mm = 0.001;
        }

        val1 = ((0.33 * 2.0) * ((((0.5 * (high[i as usize] + low[i as usize])) - min) / mm) - 0.5))
            + (0.67 * val1);
        val1 = val1.clamp(-0.999, 0.999);

        let signal_idx = (i - start) as usize;
        signal[signal_idx] = fish;
        fish = (0.5 * ((1.0 + val1) / (1.0 - val1)).ln() / LN_2) + (0.5 * fish);
        fisher[signal_idx] = fish;

        trail += 1;
    }

    0
}
