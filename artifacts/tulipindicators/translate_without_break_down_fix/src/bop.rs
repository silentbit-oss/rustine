use crate::*;

pub fn ti_bop_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_bop_start");
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_bop(
    size: usize,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32 {
	println!("\n* ti_bop");
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let _ = options; // unused, silence warning
    let output = &mut outputs[0];

    for i in 0..size {
        let hl = high[i] - low[i];
        if hl <= 0.0 {
            output[i] = 0.0;
        } else {
            output[i] = (close[i] - open[i]) / hl;
        }
    }

    0
}
