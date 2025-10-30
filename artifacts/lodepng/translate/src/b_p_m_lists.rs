use crate::*;

#[derive(Clone)]
pub struct BPMLists {
    pub memsize: u32,
    pub memory: Option<Vec<BPMNode>>,
    pub numfree: u32,
    pub nextfree: u32,
    pub freelist: Option<Vec<Option<Box<BPMNode>>>>,
    pub listsize: u32,
    pub chains0: Option<Vec<Option<Box<BPMNode>>>>,
    pub chains1: Option<Vec<Option<Box<BPMNode>>>>,
}

