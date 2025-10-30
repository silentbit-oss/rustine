use crate::*;

#[derive(Clone)]
pub struct ColorArray {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub capacity: usize,
}

