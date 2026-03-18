use crate::*;


pub struct AvlNode {
    pub left: Option<Box<AvlNode>>,
    pub right: Option<Box<AvlNode>>,
    pub parent: Option<Box<AvlNode>>,
    pub bf: i8,  // char in C is typically i8 in Rust
    pub data: Option<Box<dyn std::any::Any>>,  // void* in C is represented as a trait object
}

