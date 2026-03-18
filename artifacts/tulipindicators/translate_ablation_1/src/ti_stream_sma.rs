use crate::*;

#[derive(Clone)]
pub struct TiStreamSma {
    pub index: i32,
    pub progress: i32,
    pub period: i32,
    pub per: f64,
    pub sum: f64,
    pub buffer_idx: i32,
    pub buffer: Option<Vec<f64>>,
}

