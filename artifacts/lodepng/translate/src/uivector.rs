use crate::*;

#[derive(Clone)]
pub struct Uivector {
    pub data: Option<Vec<u32>>,
    pub size: usize,
    pub allocsize: usize,
}

