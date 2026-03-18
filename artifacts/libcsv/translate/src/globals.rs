use crate::*;
use lazy_static::lazy_static;


lazy_static! {
    pub static ref CSV_ERRORS: [&'static str; 5] = [
        "success",
        "error parsing data while strict checking enabled",
        "memory exhausted while increasing buffer size",
        "data size too large",
        "invalid status code"
    ];
}

pub static mut EVENT_IDX: i32 = 0;

pub type size_t = usize;
pub static mut row: size_t = 0;

pub static col: usize = 0;

pub struct EventPtr {
    pub event_ptr: Option<Box<Event>>,
}

