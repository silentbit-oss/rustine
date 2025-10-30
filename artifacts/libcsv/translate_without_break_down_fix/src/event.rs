use crate::*;

#[derive(Clone)]
pub struct Event {
    pub event_type: i32,
    pub retval: i32,
    pub size: usize,
    pub data: Option<Vec<u8>>,
}

