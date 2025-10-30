use crate::*;

#[derive(Clone)]
pub struct TcResult {
    pub progress: i32,
    pub space: i32,
    pub count: i32,
    pub pattern_count: i32,
    pub hits: Option<Vec<TcHit>>,
}

