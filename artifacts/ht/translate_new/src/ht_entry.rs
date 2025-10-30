use crate::*;


pub struct HtEntry {
    pub key: Option<String>,
    pub value: Option<Box<dyn std::any::Any>>,
}

