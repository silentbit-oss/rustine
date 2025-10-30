use crate::*;

#[derive(Clone)]
pub struct HemanImageS {
    pub width: i32,
    pub height: i32,
    pub nbands: i32,
    pub data: Option<Vec<f32>>,
}

