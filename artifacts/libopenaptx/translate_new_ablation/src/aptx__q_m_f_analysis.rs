use crate::*;

#[derive(Clone)]
pub struct AptxQmfAnalysis {
    pub outer_filter_signal: [AptxFilterSignal; 2],
    pub inner_filter_signal: [[AptxFilterSignal; 2]; 2],
}

