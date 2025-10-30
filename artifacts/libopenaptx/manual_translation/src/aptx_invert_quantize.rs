use crate::*;

#[derive(Clone)]
pub struct AptxInvertQuantize {
    pub quantization_factor: i32,
    pub factor_select: i32,
    pub reconstructed_difference: i32,
}

