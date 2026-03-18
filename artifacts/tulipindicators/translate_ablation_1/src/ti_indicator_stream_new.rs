use crate::*;

pub type TiIndicatorStreamNew = fn(options: Option<&[f64]>, stream: &mut Option<Box<TiStream>>) -> i32;

