use crate::*;
use std::usize;


#[derive(Clone)]
pub struct Node {
    pub weight: usize,
    pub tail: Option<Box<Node>>,
    pub count: i32,
}

impl Default for Node {
    fn default() -> Self {
        Node {
            weight: 0,
            tail: None,
            count: 0,
        }
    }
}
