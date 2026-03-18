use crate::*;
use std::usize;


#[derive(Clone)]
pub struct NodePool {
    pub next: Option<Box<Node>>,
}

