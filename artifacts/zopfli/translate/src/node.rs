use crate::*;
use std::usize;


#[derive(Clone)]
pub struct Node {
    pub weight: usize,
    pub tail: Option<Box<Node>>,
    pub count: i32,
}

