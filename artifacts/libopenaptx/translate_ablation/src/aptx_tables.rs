use crate::*;

#[derive(Clone)]
pub struct AptxTables {
    pub quantize_intervals: Option<Vec<i32>>,
    pub invert_quantize_dither_factors: Option<Vec<i32>>,
    pub quantize_dither_factors: Option<Vec<i32>>,
    pub quantize_factor_select_offset: Option<Vec<i16>>,
    pub tables_size: i32,
    pub factor_max: i32,
    pub prediction_order: i32,
}

