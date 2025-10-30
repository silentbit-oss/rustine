use crate::*;
use std::f64::consts::PI;

pub fn ti_msw_start(options: Option<&[f64]>) -> i32 {
    // Check if options is None (equivalent to NULL check in C)
    // and if the slice has at least one element
    match options {
        Some(opt) if !opt.is_empty() => opt[0] as i32,
        _ => 0, // Default return value when options is None or empty
    }
}

pub fn helper_ti_msw_1(
    sine_idx_ref: &mut u32,
    lead_idx_ref: &mut u32,
    weight_ref: &mut f64,
    phase_ref: &mut f64,
    rp_ref: &mut f64,
    ip_ref: &mut f64,
    j_ref: &mut i32,
    input: &[f64],
    sine: &mut [f64],
    lead: &mut [f64],
    period: i32,
    pi: f64,
    tpi: f64,
    i: i32,
) {
    let mut sine_idx = *sine_idx_ref;
    let mut lead_idx = *lead_idx_ref;
    let mut weight = *weight_ref;
    let mut phase = *phase_ref;
    let mut rp = *rp_ref;
    let mut ip = *rp_ref;
    let mut j = *j_ref;

    rp = 0.0;
    ip = 0.0;

    for j in 0..period {
        weight = input[(i - j) as usize];
        rp += (f64::cos((tpi * j as f64) / period as f64) * weight);
        ip += (f64::sin((tpi * j as f64) / period as f64) * weight);
    }

    if f64::abs(rp) > 0.001 {
        phase = f64::atan(ip / rp);
    } else {
        phase = (tpi / 2.0) * if ip < 0.0 { -1.0 } else { 1.0 };
    }

    if rp < 0.0 {
        phase += pi;
    }

    phase += pi / 2.0;

    if phase < 0.0 {
        phase += tpi;
    }

    if phase > tpi {
        phase -= tpi;
    }

    sine[sine_idx as usize] = f64::sin(phase);
    sine_idx += 1;
    lead[lead_idx as usize] = f64::sin(phase + (pi / 4.0));
    lead_idx += 1;

    *sine_idx_ref = sine_idx;
    *lead_idx_ref = lead_idx;
    *weight_ref = weight;
    *phase_ref = phase;
    *rp_ref = rp;
    *ip_ref = ip;
    *j_ref = j;
}
pub fn ti_msw(
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Check for None options (equivalent to NULL checks in C)
    let options = match options {
        Some(opts) => opts,
        None => return 1,
    };
    
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    let start = ti_msw_start(Some(options));
    if size <= start {
        return 0;
    }

    // Unwrap inputs and outputs safely
    let input = match inputs {
        Some(inp) => inp[0],
        None => return 1,
    };
    
    let outputs = match outputs {
        Some(out) => out,
        None => return 1,
    };
    
    // Get the original outputs pointers before mutable borrow
    let outputs_ptr0 = outputs[0].as_ptr();
    let outputs_ptr1 = outputs[1].as_ptr();
    
    // Split the outputs into separate mutable slices
    let (sine_slice, rest) = outputs.split_at_mut(1);
    let sine = &mut sine_slice[0];
    let lead = &mut rest[0];
    
    let pi = PI;
    let tpi = 2.0 * pi;
    let mut weight = 0.0;
    let mut phase = 0.0;
    let mut rp = 0.0;
    let mut ip = 0.0;
    let mut j = 0;
    let mut sine_idx = 0;
    let mut lead_idx = 0;

    for i in period..size {
        helper_ti_msw_1(
            &mut sine_idx,
            &mut lead_idx,
            &mut weight,
            &mut phase,
            &mut rp,
            &mut ip,
            &mut j,
            input,
            sine,
            lead,
            period,
            pi,
            tpi,
            i,
        );
    }

    // Assertions translated to debug_assert! (only active in debug builds)
    debug_assert!((&sine[sine_idx as usize] as *const f64 as isize - outputs_ptr0 as isize) / std::mem::size_of::<f64>() as isize == (size - start) as isize);
    debug_assert!((&lead[lead_idx as usize] as *const f64 as isize - outputs_ptr1 as isize) / std::mem::size_of::<f64>() as isize == (size - start) as isize);

    0
}
