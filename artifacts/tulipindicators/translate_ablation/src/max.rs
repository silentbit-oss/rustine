use crate::*;
use rand::Rng;

pub fn ti_max_start(options: Option<&[f64]>) -> Option<i32> {
    options.and_then(|opts| {
        if opts.is_empty() {
            None
        } else {
            Some(opts[0] as i32 - 1)
        }
    })
}

pub fn ti_max(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    let ti_max_start_value = ti_max_start(Some(options)).unwrap_or(0);
    if size <= ti_max_start_value {
        return 0;
    }
    
    let mut trail = 0;
    let mut maxi = -1;
    let mut max_val = input[0];
    let mut output_idx = 0;
    
    for i in (period - 1)..size {
        let bar = input[i as usize];
        
        if maxi < trail {
            maxi = trail;
            max_val = input[maxi as usize];
            let mut j = trail;
            
            while j <= i {
                let current_bar = input[j as usize];
                if current_bar >= max_val {
                    max_val = current_bar;
                    maxi = j;
                }
                j += 1;
            }
        } else if bar >= max_val {
            maxi = i;
            max_val = bar;
        }
        
        output[output_idx] = max_val;
        output_idx += 1;
        trail += 1;
    }
    
    let expected_output_len = (size - ti_max_start_value) as usize;
    assert!(output_idx == expected_output_len);
    
    0
}
pub fn ti_max_ref(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
    // Check for None values in inputs, options, and outputs
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }
    
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let mut outputs = outputs.unwrap();
    
    // Check if inputs and outputs arrays have at least one element
    if inputs.is_empty() || outputs.is_empty() {
        return 1;
    }
    
    let input = inputs[0];
    let period = options[0] as i32;
    let output = &mut outputs[0];
    
    if period < 1 {
        return 1;
    }
    
    // Use the dependency function ti_max_start
    let start = match ti_max_start(Some(options)) {
        Some(val) => val,
        None => return 1,
    };
    
    if size <= start {
        return 0;
    }
    
    let mut output_idx = 0;
    for i in (period - 1)..size {
        let mut max_val = input[((i - period) + 1) as usize];
        
        for j in ((i - period) + 2)..=i {
            let current_val = input[j as usize];
            if current_val > max_val {
                max_val = current_val;
            }
        }
        
        if output_idx < output.len() {
            output[output_idx] = max_val;
            output_idx += 1;
        } else {
            return 1; // Output buffer overflow
        }
    }
    
    0
}
