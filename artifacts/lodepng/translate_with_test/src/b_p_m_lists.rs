use crate::*;

#[derive(Clone)]
pub struct BpmLists {
    pub memsize: u32,
    pub memory: Option<Vec<BpmNode>>,
    pub numfree: u32,
    pub nextfree: u32,
    pub freelist: Option<Vec<Option<Box<BpmNode>>>>,
    pub listsize: u32,
    pub chains0: Option<Vec<Option<Box<BpmNode>>>>,
    pub chains1: Option<Vec<Option<Box<BpmNode>>>>,
}

