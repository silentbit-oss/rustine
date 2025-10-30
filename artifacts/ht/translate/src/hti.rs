use crate::*;


pub struct Hti {
    pub key: Option<String>,
    pub value: Option<Box<dyn std::any::Any>>,
    pub _table: Option<Box<Ht>>,
    pub _index: usize,
}

