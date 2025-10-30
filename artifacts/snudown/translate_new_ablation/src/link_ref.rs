use crate::*;

#[derive(Clone)]
pub struct LinkRef {
    pub id: u32,
    pub link: Option<Box<Buf>>,
    pub label: Option<Box<Buf>>,
    pub title: Option<Box<Buf>>,
    pub next: Option<Box<LinkRef>>,
}

