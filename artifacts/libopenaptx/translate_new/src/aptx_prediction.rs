use crate::*;

#[derive(Clone)]
pub struct AptxPrediction {
    pub prev_sign: [i32; 2],
    pub s_weight: [i32; 2],
    pub d_weight: [i32; 24],
    pub pos: i32,
    pub reconstructed_differences: [i32; 48],
    pub previous_reconstructed_sample: i32,
    pub predicted_difference: i32,
    pub predicted_sample: i32,
}

