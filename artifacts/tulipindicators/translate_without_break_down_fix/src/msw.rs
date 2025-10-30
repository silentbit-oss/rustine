use crate::*;
use rand::Rng;
use std::f64::consts::PI;

pub fn ti_msw_start(options: Option<&[f64]>) -> i32 {
	println!("\n* ti_msw_start");
    match options {
        Some(opts) => opts[0] as i32,
        None => 0, // Default behavior when NULL is passed
    }
}
pub fn ti_msw(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>
) -> i32 {
	println!("\n* ti_msw");
    // Check for None values (equivalent to NULL checks in C)
    let inputs = match inputs {
        Some(i) => i,
        None => return 1,
    };
    let options = match options {
        Some(o) => o,
        None => return 1,
    };
    let outputs = match outputs {
        Some(o) => o,
        None => return 1,
    };

    // Get input and output slices using split_at_mut to avoid multiple mutable borrows
    let input = inputs[0];
    let (sine_slice, rest) = outputs.split_at_mut(1);
    let sine = &mut sine_slice[0];
    let lead = &mut rest[0];

    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_msw_start(Some(options));
    if size <= start {
        return 0;
    }

    let tpi = 2.0 * PI;
    let mut sine_idx = 0;
    let mut lead_idx = 0;

    for i in period..size {
        let mut rp = 0.0;
        let mut ip = 0.0;

        for j in 0..period {
            let weight = input[(i - j) as usize];
            rp += ((tpi * j as f64) / period as f64).cos() * weight;
            ip += ((tpi * j as f64) / period as f64).sin() * weight;
        }

        let phase = if rp.abs() > 0.001 {
            (ip / rp).atan()
        } else {
            (tpi / 2.0) * if ip < 0.0 { -1.0 } else { 1.0 }
        };

        let mut phase = if rp < 0.0 {
            phase + PI
        } else {
            phase
        };

        phase += PI / 2.0;
        if phase < 0.0 {
            phase += tpi;
        }
        if phase > tpi {
            phase -= tpi;
        }

        sine[sine_idx] = phase.sin();
        sine_idx += 1;
        lead[lead_idx] = (phase + (PI / 4.0)).sin();
        lead_idx += 1;
    }

    // In Rust, we don't need the asserts since the bounds are checked by the type system
    0
}
