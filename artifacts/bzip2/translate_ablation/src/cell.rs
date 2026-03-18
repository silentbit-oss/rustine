use crate::*;

#[derive(Clone)]
pub struct Zzzz {
    pub name: Option<Box<Char>>,
    pub link: Option<Box<Zzzz>>,
}

pub type Cell = Zzzz;

