use crate::*;

#[derive(Clone)]
pub struct Aptx_Channel {
    pub codeword_history: i32,
    pub dither_parity: i32,
    pub dither: [i32; 4],
    pub qmf: Aptx_QMF_Analysis,
    pub quantize: [Aptx_Quantize; 4],
    pub invert_quantize: [Aptx_Invert_Quantize; 4],
    pub prediction: [Aptx_Prediction; 4],
}

