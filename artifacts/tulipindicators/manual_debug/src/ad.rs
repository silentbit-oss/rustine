use crate::*;

pub fn ti_ad_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_ad_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}

pub fn ti_ad(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_ad");
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    if inputs.len() < 4 {
        return 0;
    }
    // Extract input slices
    let high = inputs[0];
    let low = inputs[1];
    let close = inputs[2];
    let volume = inputs[3];
    
    // Get mutable reference to output slice
    let output = &mut outputs[0];
    
    let mut sum = 0.0;
    
    for i in 0..size as usize {
        let hl = high[i] - low[i];
        if hl != 0.0 {
            sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
        }
        output[i] = sum;
    }
    
    0
}
