use crate::*;
use std::any::Any;



pub struct Quadtree {
    pub root: Option<Box<QuadtreeNode>>,
    pub key_free: Option<Box<dyn FnMut(Box<dyn Any>)>>,
    pub length: u32,
}

