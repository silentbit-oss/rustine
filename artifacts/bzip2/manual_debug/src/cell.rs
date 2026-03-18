use crate::*;

#[derive(Clone, Debug)]
pub struct Zzzz {
    pub name: Option<Box<String>>,
    pub link: Option<Box<Zzzz>>,
}

pub type Cell = Zzzz;

