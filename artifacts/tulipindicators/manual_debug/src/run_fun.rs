use crate::*;

pub type RunFun = fn(info: &TiIndicatorInfo, options: Option<&[f64]>, goal: i32) -> i32;

