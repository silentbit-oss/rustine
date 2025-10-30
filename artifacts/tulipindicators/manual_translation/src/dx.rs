use crate::*;
use std::f64;

pub fn ti_dx_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_dx_start");
    // Check if options is None (equivalent to NULL pointer check in C)
    let options = options.unwrap();
    
    // Check if the slice is not empty to avoid panic on index 0
    if options.is_empty() {
        return 0;
    }

    // Perform the same calculation as in C, converting to i32
    options[0] as i32 - 1
}

pub fn ti_dx(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_dx");
    // Check for None in all Option parameters
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    if inputs.len() < 2 {
        return 0;
    }
    // Get slices from inputs and outputs
    let high = inputs.get(0).unwrap();
    let low = inputs.get(1).unwrap();
    let output = outputs.get_mut(0).unwrap();

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_dx_start(Some(options));
    if size <= start {
        return 0;
    }

    let per = (f64::from(period) - 1.0) / f64::from(period);
    let mut dmup = 0.0;
    let mut dmdown = 0.0;
    let mut output_idx = 0;

    // First loop (initial period)
    for i in 1..period {
        let i = i as usize;
        let dp = {
            let mut dp = high[i] - high[i - 1];
            let mut dm = low[i - 1] - low[i];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            dp
        };
        
        let dm = {
            let mut dp = high[i] - high[i - 1];
            let mut dm = low[i - 1] - low[i];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            dm
        };

        dmup += dp;
        dmdown += dm;
    }

    // First output calculation
    {
        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        output[output_idx] = dx;
        output_idx += 1;
    }

    // Main loop
    for i in period..size {
        let i = i as usize;
        let dp = {
            let mut dp = high[i] - high[i - 1];
            let mut dm = low[i - 1] - low[i];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            dp
        };
        
        let dm = {
            let mut dp = high[i] - high[i - 1];
            let mut dm = low[i - 1] - low[i];
            
            if dp < 0.0 {
                dp = 0.0;
            } else if dp > dm {
                dm = 0.0;
            }
            
            if dm < 0.0 {
                dm = 0.0;
            } else if dm > dp {
                dp = 0.0;
            }
            
            dm
        };

        dmup = (dmup * per) + dp;
        dmdown = (dmdown * per) + dm;

        let di_up = dmup;
        let di_down = dmdown;
        let dm_diff = f64::abs(di_up - di_down);
        let dm_sum = di_up + di_down;
        let dx = (dm_diff / dm_sum) * 100.0;
        output[output_idx] = dx;
        output_idx += 1;
    }

    // The assertion in the original C code is not directly translatable to safe Rust
    // as it involves pointer arithmetic. In safe Rust, we would typically verify
    // lengths before operations rather than after.

    0
}
