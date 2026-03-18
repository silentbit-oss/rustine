use crate::*;
use rand::Rng;

pub fn ti_ao_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_ao_start");
    let _ = options; // Explicitly ignore the parameter to match C behavior
    33
}

pub fn ti_ao(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_ao");
    let inputs = inputs.unwrap();
    let outputs = outputs.unwrap();
    
    if inputs.len() < 2 {
        return 0;
    }
    let high = inputs[0];
    let low = inputs[1];
    let period = 34;
    let output = &mut outputs[0];
    let mut output_idx = 0;

    if size <= ti_ao_start(options) {
        return 0;
    }

    let mut sum34 = 0.0;
    let mut sum5 = 0.0;
    let per34 = 1.0 / 34.0;
    let per5 = 1.0 / 5.0;

    for i in 0..34 {
        let hl = 0.5 * (high[i] + low[i]);
        sum34 += hl;
        if i >= 29 {
            sum5 += hl;
        }
    }

    output[output_idx] = (per5 * sum5) - (per34 * sum34);
    output_idx += 1;

    for i in period..size {
        let hl = 0.5 * (high[i as usize] + low[i as usize]);
        sum34 += hl;
        sum5 += hl;
        sum34 -= 0.5 * (high[(i - 34) as usize] + low[(i - 34) as usize]);
        sum5 -= 0.5 * (high[(i - 5) as usize] + low[(i - 5) as usize]);
        output[output_idx] = (per5 * sum5) - (per34 * sum34);
        output_idx += 1;
    }

    assert!((&output[output_idx] as *const f64 as usize - outputs[0].as_ptr() as usize) / std::mem::size_of::<f64>() == (size - ti_ao_start(options)) as usize);
    0
}
