use crate::*;
use std::usize;


#[derive(Clone)]
pub struct NodePool {
    pub next: Vec<Box<Node>>,
    pub index: usize,
}

