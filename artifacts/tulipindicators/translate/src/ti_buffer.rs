use crate::*;

#[derive(Clone)]
pub struct TiBuffer {
    pub size: i32,
    pub pushes: i32,
    pub index: i32,
    pub sum: f64,
    pub vals: Vec<f64>,
}

