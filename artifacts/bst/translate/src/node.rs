use crate::*;

#[derive(Clone)]
pub struct Node {
    pub key: i32,
    pub left: Option<Box<Node>>,
    pub right: Option<Box<Node>>,
}

