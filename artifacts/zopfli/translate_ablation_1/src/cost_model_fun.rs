use crate::*;

/// Function pointer type for cost model calculations
pub type CostModelFun = fn(litlen: u32, dist: u32, context: Option<Box<dyn std::any::Any>>) -> f64;

