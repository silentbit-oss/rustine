use crate::*;

#[derive(Clone)]
pub struct Aptx_QMF_Analysis {
    pub outer_filter_signal: [Aptx_Filter_Signal; 2],
    pub inner_filter_signal: [[Aptx_Filter_Signal; 2]; 2],
}

