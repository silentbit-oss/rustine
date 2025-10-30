use crate::*;

pub fn ti_pvi_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_pvi(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let close = inputs[0];
    let volume = inputs[1];
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if size <= ti_pvi_start(options) {
        return 0;
    }

    let mut pvi = 1000.0;
    output[output_idx] = pvi;
    output_idx += 1;

    for i in 1..size as usize {
        if volume[i] > volume[i - 1] {
            pvi += ((close[i] - close[i - 1]) / close[i - 1]) * pvi;
        }
        output[output_idx] = pvi;
        output_idx += 1;
    }

    debug_assert!((&output[output_idx - 1] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_pvi_start(options)) as usize);
    0
}
