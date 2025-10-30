use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct Node {
    pub weight: usize,
    pub tail: Option<Box<Node>>,
    pub count: i32,
}

