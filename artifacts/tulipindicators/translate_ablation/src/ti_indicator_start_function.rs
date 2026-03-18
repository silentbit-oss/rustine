use crate::*;

pub type TiIndicatorStartFunction = Option<Box<dyn Fn(&[f64]) -> i32>>;

