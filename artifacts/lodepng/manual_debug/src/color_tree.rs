use crate::*;

#[derive(Clone)]
pub struct ColorTree {
    pub children: [Option<Box<ColorTree>>; 16],
    pub index: i32,
}

