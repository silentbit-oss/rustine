use crate::*;


pub struct AvlTree {
    pub compare: Option<Box<dyn Fn(&dyn std::any::Any, &dyn std::any::Any) -> i32>>,
    pub print: Option<Box<dyn Fn(&dyn std::any::Any)>>,
    pub destroy: Option<Box<dyn Fn(&dyn std::any::Any)>>,
    pub root: Option<Box<AvlNode>>,
    pub nil: Option<Box<AvlNode>>,
    pub min: Option<Box<AvlNode>>,
}

