use crate::*;

#[derive(Clone)]
pub struct BPMNode {
    pub weight: i32,
    pub index: u32,
    pub tail: Option<Box<BPMNode>>,
    pub in_use: i32,
}

