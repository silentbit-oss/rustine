use crate::*;
use rand::Rng;
use std::f64::consts::PI;

pub fn ti_msw_start(options: Option<&[f64]>) -> i32 {
    match options {
        Some(opts) if !opts.is_empty() => opts[0] as i32,
        _ => 0,
    }
}
pub fn ti_msw(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let input = inputs[0];
    let period = options[0] as i32;
    
    if period < 1 {
        return 1;
    }
    
    let start = ti_msw_start(Some(options));
    if size <= start {
        return 0;
    }
    
    let pi = PI;
    let tpi = 2.0 * pi;
    
    // Use split_at_mut to get mutable references to both output slices
    let (sine_slice, rest) = outputs.split_at_mut(1);
    let sine = &mut sine_slice[0];
    let lead = &mut rest[0];
    
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
            phase + pi
        } else {
            phase
        };
        
        phase += pi / 2.0;
        
        if phase < 0.0 {
            phase += tpi;
        }
        
        if phase > tpi {
            phase -= tpi;
        }
        
        let idx = (i - start) as usize;
        sine[idx] = phase.sin();
        lead[idx] = (phase + (pi / 4.0)).sin();
    }
    
    0
}
