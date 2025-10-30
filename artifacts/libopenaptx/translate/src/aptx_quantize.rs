use crate::*;

#[derive(Clone)]
pub struct Aptx_Quantize {
    pub quantized_sample: i32,
    pub quantized_sample_parity_change: i32,
    pub error: i32,
}

