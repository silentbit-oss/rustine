use crate::*;

#[derive(Clone)]
pub struct BpmNode {
    pub weight: i32,
    pub index: u32,
    pub tail: Option<Box<BpmNode>>,
    pub in_use: i32,
}

