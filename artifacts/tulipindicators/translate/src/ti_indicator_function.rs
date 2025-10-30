use crate::*;

pub type TiIndicatorFunction = fn(
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) -> i32;

