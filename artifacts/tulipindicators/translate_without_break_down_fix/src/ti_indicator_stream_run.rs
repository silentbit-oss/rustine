use crate::*;

pub type TiIndicatorStreamRun = Option<Box<dyn Fn(&TiStream, i32, &[&[f64]], &mut [&mut [f64]]) -> i32>>;

