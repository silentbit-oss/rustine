use crate::*;


pub struct AvlTree
{
    pub compare: fn(Option<&Mydata>, Option<&Mydata>) -> i32,//Option<Box<dyn Fn(&dyn std::any::Any, &dyn std::any::Any) -> i32>>,
    pub print: fn(Option<&Mydata>),//Option<Box<dyn Fn(&dyn std::any::Any)>>,
    pub destroy: fn(Option<Box<Mydata>>),//Option<Box<dyn Fn(&dyn std::any::Any)>>,
    pub root: Option<Box<AvlNode>>,
    pub nil: Option<Box<AvlNode>>,
    pub min: Option<Box<AvlNode>>,
}

