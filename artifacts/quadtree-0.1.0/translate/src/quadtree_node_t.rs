use crate::*;


pub struct QuadtreeNode {
    pub ne: Option<Box<QuadtreeNode>>,
    pub nw: Option<Box<QuadtreeNode>>,
    pub se: Option<Box<QuadtreeNode>>,
    pub sw: Option<Box<QuadtreeNode>>,
    pub bounds: Option<Box<QuadtreeBounds>>,
    pub point: Option<Box<QuadtreePoint>>,
    pub key: Option<Box<dyn std::any::Any>>,
}

