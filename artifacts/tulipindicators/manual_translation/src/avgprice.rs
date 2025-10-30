use crate::*;

pub fn ti_avgprice_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_avgprice_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    0
}
pub fn ti_avgprice(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_avgprice");
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    
    if inputs.len() < 2 {
        return 0;
    }
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let _ = options; // Explicitly ignore options to match C behavior
    let output = &mut outputs[0];

    for i in 0..size as usize {
        output[i] = (open[i] + high[i] + low[i] + close[i]) * 0.25;
    }

    0
}
