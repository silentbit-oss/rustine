use crate::*;

pub type TcCandleFunction = fn(
    size: i32,
    inputs: Option<&[&[TC_REAL]]>,
    options: &TcConfig,
    output: &mut TcResult,
) -> i32;

