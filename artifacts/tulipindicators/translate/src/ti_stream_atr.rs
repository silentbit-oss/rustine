use crate::*;

#[derive(Clone)]
pub struct TiStreamAtr {
    pub index: i32,
    pub progress: i32,
    pub period: i32,
    pub sum: f64,
    pub last: f64,
    pub last_close: f64,
}

