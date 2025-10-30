use crate::*;


pub struct Ht_Entry {
    pub key: Option<String>,
    pub value: Option<Box<dyn std::any::Any>>,
}

