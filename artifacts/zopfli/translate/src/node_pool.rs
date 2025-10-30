use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct NodePool {
    pub next: Option<Box<Node>>,
}

