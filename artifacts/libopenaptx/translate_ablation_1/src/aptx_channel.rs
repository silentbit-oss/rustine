use crate::*;

#[derive(Clone)]
pub struct AptxChannel {
    pub codeword_history: i32,
    pub dither_parity: i32,
    pub dither: [i32; 4],
    pub qmf: AptxQmfAnalysis,
    pub quantize: [AptxQuantize; 4],
    pub invert_quantize: [AptxInvertQuantize; 4],
    pub prediction: [AptxPrediction; 4],
}

