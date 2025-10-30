use crate::*;

pub fn ti_nvi_start(options: Option<&[f64]>) -> i32 {
    let _ = options; // Explicitly ignore the parameter
    0
}
pub fn ti_nvi(size: i32, inputs: &[&[f64]], options: Option<&[f64]>, outputs: &mut [&mut [f64]]) -> i32 {
    let close = inputs[0];
    let volume = inputs[1];
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if size <= ti_nvi_start(options) {
        return 0;
    }

    let mut nvi = 1000.0;
    output[output_idx] = nvi;
    output_idx += 1;

    for i in 1..size as usize {
        if volume[i] < volume[i - 1] {
            nvi += ((close[i] - close[i - 1]) / close[i - 1]) * nvi;
        }
        output[output_idx] = nvi;
        output_idx += 1;
    }

    debug_assert!((output.as_ptr().wrapping_offset(output_idx as isize) as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_nvi_start(options)) as usize);
    0
}
